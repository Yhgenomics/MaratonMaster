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
                while ( sentialMark != originalServants.end() )
                {
                    /*ServantManager::Instance()->FindByServantID( *sentialMark )->Status( ServantStatus::kStandby );*/
                    ServantManager::Instance()->FreePreoccupied( *sentialMark );
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
void Task::UpdateSubtaskStatus( const string&           subTaskID ,
                                const TaskStatus::Code& status ,
                                const vector<string>&   outputs )
{
    if ( sub_tasks_status_.count( subTaskID ) > 0 )
    {
        for ( const auto& item : outputs )
        {
            outputs_.push_back( item );
        }
        sub_tasks_status_[ subTaskID ] = status;
    }
}

// Initialization
void Task::Init()
{
    original_task_     = nullptr;
    original_message_  = nullptr;
    is_finished_       = false;
    is_sub_tasks_ready = false;
    upper_layer_abort_ = false;
    status_            = TaskStatus::kUnknown;

    sub_tasks_.clear();
    sub_tasks_status_.clear();
    outputs_.clear();
}

// Free all preoccupied servants
void Task::FreePreOccupiedServants()
{
    for ( auto item : sub_tasks_status_ )
    {
        ServantManager::Instance()->FreePreoccupied( item.first );
    }
}

// Set Error message to make a report
void Task::SetErrorMessage( Error& msg )
{
    error_message_ = msg;
    if ( ErrorCode::kNoError != msg.Code() )
    {
        Status( TaskStatus::kError );
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
   /* Logger::Log( "Servants snapshot before make sub tasks!" );
    ServantManager::Instance()->ShowServants();*/

    Error taskLaunchResult( ErrorCode::kNoError , "No Errors" );

    if ( !is_sub_tasks_ready )
    {
        MakeSubtasks();
    }

   /* Logger::Log( "After make sub tasks!" );
    ServantManager::Instance()->ShowServants();*/

    // kFinished here for re-start a task
    if ( this->status_ != TaskStatus::kFinished &&
         this->status_ != TaskStatus::kPending )
    {
        FreePreOccupiedServants();
        Status( TaskStatus::kError );
        taskLaunchResult.Code( ErrorCode::kTaskNotReady );
        taskLaunchResult.Message( "task is not ready" );
        return taskLaunchResult;
    }

    Status( TaskStatus::kRunning );

    for ( auto subtask : sub_tasks_ )
    {
        auto servant = ServantManager::Instance()->FindByServantID( *subtask->Servants().begin() );

        if ( ErrorCode::kNoError != servant->LaunchTask( subtask ).Code() )
        {
            taskLaunchResult.Code( ErrorCode::kSubTaskError );
            taskLaunchResult.Message( "Servant ID:"
                                      + *subtask->Servants().begin()
                                      + "return Error when launching task" );
            Logger::Log( "Error %" , taskLaunchResult.Message() );

            sub_tasks_status_[ subtask->ID() ] = TaskStatus::kError;
            Status( TaskStatus::kError );
            break;
        }

        else
        {
            sub_tasks_status_[ subtask->ID() ] = TaskStatus::kRunning;
        }
    }
    return taskLaunchResult;
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

// return if error happens
// 1. subtask error
// 2. servant no longger exsited and it's work not finished.
bool Task::IsAnyError()
{
    bool result = false;

    for ( const auto& subtask : sub_tasks_status_ )
    {
        // Error happened
        if ( subtask.second == TaskStatus::kError )
        {
            result = true;
        }

        // Running task's servant is no longer existed
        else if ( subtask.second == TaskStatus::kRunning 
        && !ServantManager::Instance()->FindByServantID( subtask.first ) )
        {
            result = true;
        }

    }

    return result;
}

// Check 
// 1. if all subtasks have been finished
// 2. if any eror happens(that will cause an abort operation.
void Task::CheckRunningTask()
{
    if ( IsAllSubtasksFinished() )
    {
        Status( TaskStatus::kFinished );
        return;// return as no need for considering about aborting
    }

    if ( IsAnyError() || UpperLayerAbort() )
    {
        Abort();
    }
    return;
}

// check if this task can finish
// two constrains
// 1. task finished
// 2. servant at a final status
bool Task::CanFinish()
{
    bool result = true;

    if ( TaskStatus::kFinished != Status() )
    {
        result = false;
    }

    else
    {
        bool isAllFinal = true;
        for ( auto item : sub_tasks_ )
        {
            //break when on sub task's servant(s) is not at a final status
            if ( !isAllFinal ) { break; }           

            isAllFinal = ServantManager::Instance()->IsFinal( item->Servants() ) && isAllFinal;
        }
        result = isAllFinal && result;
    }

    return result;
}

// On every subtask finished
void Task::OnFinish()
{
    Logger::Log( "All Subtasks finished!" );

    json result;

    result[ "status" ]     = Status();//TaskStatus::kFinished;
    result[ "taskid" ]     = original_message_->id();
    result[ "pipelineid" ] = original_message_->pipeline().id();
    result[ "data" ]       = outputs_;

    Logger::Log( "Task result \n % " , result.dump( 4 ) );

    Protocal::MessageHub::Instance()->SendRESTInfo( Protocal::MessageHub::Instance()->GetRESTReportFullPath() ,
                                                    result.dump() /*,
                                                    "Result of Task ID " + original_message_->id()*/ );

}

// Abort task
void Task::Abort()
{
    // in case some subtasks not launched
    FreePreOccupiedServants();

    Status( TaskStatus::kAborting );

    for ( auto item : sub_tasks_ )
    {
        // Abort all running subtasks on esxist servants
        for ( auto item : sub_tasks_ )
        {
            if ( TaskStatus::kRunning == sub_tasks_status_[ item->ID() ] )
            {
                auto servant = ServantManager::Instance()->FindByServantID( *item->Servants().begin() );
                if(servant)
                {
                    servant->AbortTask();
                }
            }         
        }
        
        // for other situation
        // Finished tasks OK
        // error tasks OK
        // Aborted tasks OK
        // servant no longer exsited OK
    }

    return;
}


