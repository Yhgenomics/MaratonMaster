/***********************************************************************************
This file is part of Project for MaratonMaster
For the latest info, see  https://github.com/Yhgenomics/MaratonMaster.git

Copyright 2016 Yhgenomics

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***********************************************************************************/

/***********************************************************************************
* Description   : One task from bussiness level.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/3
* Modifed       : When      | Who       | What
***********************************************************************************/

#include "Task.h"
#include "ServantManager.h"
#include "MessageHub.h"
#include "MRT.h"
#include "json.hpp"
#include <vector>
#include <string>

using nlohmann::json;
using std::vector;
using std::string;

// Make sub tasks
// @note    : The original task from Business to Master is in 1:1 relationship.
//            the subtask is the task from Master to Servants it is 1:1 when 
//            the original task is not parallel, 1:n otherwise.
bool Task::MakeSubtasks()
{
    // Design for remake subtask(will not happen for now)
    if ( true == is_sub_tasks_ready )
    {
        // drop all the current task
        sub_tasks_.clear();
        sub_tasks_status_.clear();
    }

    if ( !original_task_->IsParallel() )
    {
        auto tempSubtask = make_sptr( TaskDescriptor , *original_task_ );
        tempSubtask->ID( MRT::UUID::Instance()->Create() );
        sub_tasks_.push_back( tempSubtask );
        sub_tasks_status_[ tempSubtask->ID() ] = TaskStatus::kPending;
    }

    else // parallel
    {
        auto totalScore       = ServantManager::Instance()->GetScore( original_task_->Servants() );
        auto totalInputs      = original_task_->Input().size();
        auto leftInputs       = totalInputs;
        auto originalInput    = original_task_->Input();
        auto lastEnd          = originalInput.begin();
        auto originalServants = original_task_->Servants();
        auto sentialMark      = originalServants.begin();

        for ( const auto& item : originalServants )
        {
            // All inputs has been asigned to srvants
            if ( leftInputs <= 0 )
            {
                while(sentialMark != originalServants.end() )
                {
                    ServantManager::Instance()->FindByServantID( *sentialMark )->Status(ServantStatus::kStandby);
                    sentialMark++;
                }
                break;
            }

            // Watch out for zero inputs when a executor with very low ability is assigned
            size_t tempInputNum = ( size_t )ceil( ( double )ServantManager::Instance()->FindByServantID( item )->Ability()
                                                  / ( double )totalScore
                                                  * totalInputs );

            if ( sentialMark != originalServants.end() - 1 && tempInputNum == 0 )
            {
                // Servant's ability is too low to use
                continue;
            }

            // Take all the left
            if ( tempInputNum > leftInputs )
            {
                tempInputNum = leftInputs;
            }

            // Make subtask descprtionbased on score 
            auto tempSubtask = make_sptr( TaskDescriptor , *original_task_ );
            tempSubtask->PrepareAsSubtask();
            tempSubtask->Servants( vector<string>( { item } ) );

            // Last servant must get all the left files
            if ( sentialMark == originalServants.end() - 1 )
            {
                tempSubtask->Input( vector<string>( lastEnd , originalInput.end() ) );
            }

            else
            {
                tempSubtask->Input( vector<string>( lastEnd , lastEnd + tempInputNum ) );
            }

            leftInputs -= tempInputNum;
            lastEnd    += tempInputNum;
            sentialMark++;
            // Add the subtask descprtion
            sub_tasks_.push_back( tempSubtask );

            // Add the subtask watch list
            sub_tasks_status_[ tempSubtask->ID() ] = TaskStatus::kPending;
        } // end of for ( const auto& item : originalServants )
    } // end of else

    is_sub_tasks_ready = true;

    return is_sub_tasks_ready;
}

// Update the status of the tasks executed by Servant.
// @subTaskID : The ID for subtask not the task
// @status    : The status for subtask
// @outputs   : The subtask's output information witch should be append to
//              the task.
void Task::UpdateSubtaskStatus( const string&         subTaskID ,
                                const TaskStatus::Code&     status ,
                                const vector<string>& outputs )
{
    if ( sub_tasks_status_.count( subTaskID ) > 0 )
    {
        for ( const auto& item : outputs )
        {
            outputs_.push_back( item );
        }

        sub_tasks_status_[ subTaskID ] = status;

        if ( IsAllSubtasksFinished() )
        {
            OnFinish();
        }

    }
}

// Constructor from a task descriptor.
// @task : Task descriptor in a unique pointer.
Task::Task( uptr<TaskDescriptor> task )
{
    Init();
    original_task_    = move_ptr( task );
    original_message_ = original_task_->MakeMessage();
}

// Constructor from a protobuf message MessageTaskDeliver.
// @message : task deliver message in a unique pointer
Task::Task( uptr<MessageTaskDeliver> message )
{   
    Init();
    original_task_    = make_uptr( TaskDescriptor , *( message.get() ) );
    original_message_ = move_ptr( message );
}

Task::~Task()
{
}

// Launch task
// @note    : Launch all subtasks
Error Task::Launch()
{
    Logger::Log( "Servants snapshot before make sub tasks!" );
    ServantManager::Instance()->ShowServants();
    
    Error TaskLaunchResult( ErrorCode::kNoError , "" );

    if ( !is_sub_tasks_ready )
    {
        MakeSubtasks();
    }

    Logger::Log( "After make sub tasks!" );
    ServantManager::Instance()->ShowServants();

    // kFinished here for re-start a task
    if ( this->status_ != TaskStatus::kFinished &&
         this->status_ != TaskStatus::kPending )
    {
        Abort();
        TaskLaunchResult.Code( ErrorCode::kTaskNotReady );
        TaskLaunchResult.Message( "task is not ready" );

        return TaskLaunchResult;
    }

    Status( TaskStatus::kRunning );

    for ( auto subtask : sub_tasks_ )
    {
        auto servant = ServantManager::Instance()->FindByServantID( *subtask->Servants().begin() );

        if ( ErrorCode::kNoError != servant->LaunchTask( subtask ).Code() )
        {
            TaskLaunchResult.Code( ErrorCode::kSubTaskError );
            TaskLaunchResult.Message( "Servant ID:"
                                      + *subtask->Servants().begin()
                                      + "return Error when launching task" );
            Logger::Log( "Error %",TaskLaunchResult.Message() );
            Status( TaskStatus::kError );
            break;
        }
    }

    //TODO report to business layer
    return TaskLaunchResult;
}

// return true when all subtasks finished successfully, flase otherwise.
bool Task::IsAllSubtasksFinished()
{
    bool result = true;

    for ( const auto& subtask : sub_tasks_status_ )
    {
        result = result && subtask.second == TaskStatus::kFinished;
    }

    return result;
}

// On every subtask finished
void Task::OnFinish()
{
    Logger::Log( "All Subtasks finished!");

    json result;

    result[ "status" ]     = TaskStatus::kFinished;
    result[ "taskid" ]     = original_message_->id();
    result[ "pipelineid" ] = original_message_->pipeline().id();
    result[ "data" ]       = outputs_;

    Logger::Log( "Task result \n % ", result.dump(4) );
    
    Protocal::MessageHub::Instance()->SendRESTInfo( Protocal::MessageHub::Instance()->GetRESTReportFullPath() ,
                                                    result.dump() /*,
                                                    "Result of Task ID " + original_message_->id()*/ );

}

// Abort task
void Task::Abort()
{
    Status( TaskStatus::kError );

    for ( auto& item : sub_tasks_status_ )
    {
        //TODO cancel task each servants by a cancel task message
        item.second = TaskStatus::kError;
    }

    return;
}


