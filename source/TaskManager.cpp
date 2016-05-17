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
* Description   : Operation on tasks.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/29
* Modifed       : When      | Who       | What
***********************************************************************************/

#include "TaskManager.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

// Update and do the operations by the status
// No directly control of task's status in Task Manager
void TaskManager::Update()
{   
    if( task_need_pop_ )
    {
        for( auto item : pop_list_ )
        {
            Logger::Log("Pop");
            Pop( item );
        }
        pop_list_.clear();
        task_need_pop_ = false;
        Logger::Log( "TaskManager Size is %" , Instances().size() );
    }

    for ( auto item : Instances() )
    {
        // launch pending task
        if ( TaskStatus::kPending == item->Status() )
        {
            auto result = item->Launch();
            
            if ( ErrorCode::kNoError != result.Code() )
            {
                break;
            }
        } // end of kPending
        
        // a running task can finally finished or get errors
        else if( TaskStatus::kRunning == item->Status() )
        {
            item->CheckRunningTask(); 
        }

        else if( TaskStatus::kFinished == item->Status() )
        {
            // A task can finish after the resources not at working status
            if ( item->CanFinish() )
            {
                item->OnFinish();

                pop_list_.push_back( item);
                task_need_pop_ = true;
            }
        }// end of kFinished

        else if( TaskStatus::kAborting == item->Status() )
        {
             // check all task is final
             // kfinished or kerror or aborted or servant no longer existed
             // all pass task will be kError
        }// end of kAborting

        else if( TaskStatus::kError == item->Status() )
        {
            // 1.check if all servants is released 
            // 2.Send back a task report
            // 3.add the task to pop list            
        }// end of kError

    } // end of for ( auto task : Instances() )
}

// Abort specified task by setting the abort mark
// @taskID   : taskID
void TaskManager::Abort( const std::string & taskID )
{
    for ( auto item : Instances() )
    {
        if ( taskID == item->MainTaskID() )
        {
            item->UpperLayerAbort( true );
        }
    }
}

// Try UpdateSubtaskStatus in every task
// @taskID  : The ID for subtask not the task
// @status  : The status for subtask
// @outputs : The subtask's output information witch should be append to
//            the task.
void TaskManager::UpdateSubtaskStatus( const std::string&      subtaskID ,
                                       const TaskStatus::Code& status    ,
                                       const vector<string>&   outputs   )
{
    for ( auto task : Instances() )
    {
        task->UpdateSubtaskStatus( subtaskID ,
                                   status    ,
                                   outputs   );
    }
}

// Constructor
TaskManager::TaskManager()
{
    Init();
}

// Destructor
TaskManager::~TaskManager()
{
}

// Initialization
void TaskManager::Init()
{
    pop_list_.clear();
    task_need_pop_ = false;
}
