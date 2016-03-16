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

#include "MRT.h"
#include "json.hpp"
#include "Task.h"
#include "ServantManager.h"
#include <vector>
#include <string>

using nlohmann::json;
using std::vector;
using std::string; 

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
        tempSubtask->ID( MRT::UUID::Create() );
        sub_tasks_.push_back( tempSubtask );
        sub_tasks_status_[ tempSubtask->ID() ] = TaskStatus::kPending;
    }
    else
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
                break;
            }

            // Watch out for zero inputs when a executor with very low ability is assigned
            size_t tempInputNum = ceil( ( double )ServantManager::Instance()->FindByServantID( item )->Ability()
                                        / ( double )totalScore
                                        * totalInputs );

            if ( sentialMark != originalServants.end() - 1 && tempInputNum == 0 )
            {
                // Do not need this servant
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
        }

    }
    is_sub_tasks_ready = true;
    return is_sub_tasks_ready;
}

void Task::UpdateSubtaskStatus( const string&         subTaskID ,
                                const TaskStatus&     status    ,
                                const vector<string>& outputs   )
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

Task::Task( uptr<TaskDescriptor> task)
{
    original_task_    = move_ptr( task );
    original_message_ = original_task_->MakeMessage();
}

Task::Task( uptr<MessageTaskDeliver> message)
{
    original_task_    = make_uptr( TaskDescriptor , *( message.get() ) );
    original_message_ = move_ptr( message );
}

Task::~Task()
{
}

Error Task::Launch()
{
    Error TaskLaunchResult( 0 , "" );
    
    if(!is_sub_tasks_ready)
    {
        MakeSubtasks();
    }

    if( this->status_ != TaskStatus::kFinished &&
        this->status_ != TaskStatus::kPending )
    {
        Abort();
        TaskLaunchResult.Code(1);
        TaskLaunchResult.Message( "task is not ready" );
        
        return TaskLaunchResult;
    }

    Status( Task::TaskStatus::kRunning );
    for(auto subtask : sub_tasks_)
    {
        auto servant = ServantManager::Instance()->FindByServantID( *subtask->Servants().begin() );
        if(0 != servant->LaunchTask( subtask ).Code()) 
        {
            TaskLaunchResult.Code( 1 );
            TaskLaunchResult.Message( "Servant ID:"
                                      + *subtask->Servants().begin()
                                      + "return Error when launching task" );
            Status( Task::TaskStatus::kError );
            break;
        }
    }

    //TODO report to business layer
    return TaskLaunchResult;
}

bool Task::IsAllSubtasksFinished()
{
    bool result = true;
    for( const auto& subtask : sub_tasks_status_ )
    {
        result = result && subtask.second == Task::TaskStatus::kFinished;
    }
    return result;
}

void Task::OnFinish()
{
    std::cout << "all sub task finished!" << std::endl;
    
    json result;
   
    result[ "status" ]     = Task::TaskStatus::kFinished;
    result[ "taskid" ]     = original_message_->id();
    result[ "pipelineid" ] = original_message_->pipeline().id();

    result[ "data" ]       = outputs_;
    
    std::cout << result.dump() << std::endl;

    MRT::WebClient myWebClient;
    myWebClient.Header( "Content-Type" , "application/json" );
    myWebClient.Post( "http://10.0.0.20:888/maraton/result" ,
                      result.dump() ,
                      [] ( uptr<MRT::HTTPResponse> response )
    {

    }
    );

}

void Task::Abort()
{
    Status(TaskStatus::kError);
    for ( auto& item : sub_tasks_status_ )
    {
        //TODO cancel task each servants vid a cancel task message
        item.second = TaskStatus::kError;
    }
    return;
}


