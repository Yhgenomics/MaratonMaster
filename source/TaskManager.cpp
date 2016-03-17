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

// Update each task status and launch it if is pending. 
void TaskManager::Update()
{
    for ( auto task : Instances() )
    {
        if ( Task::TaskStatus::kPending == task->Status() )
        {
            auto result = task->Launch();
            
            if ( 0 != result.Code() )
            {
                break;
            }
        } // end of if ( Task::TaskStatus::kPending == task->Status() )
    } // end of for ( auto task : Instances() )
}

// Try UpdateSubtaskStatus in every task
// @taskID  : The ID for subtask not the task
// @status  : The status for subtask
// @outputs : The subtask's output information witch should be append to
//            the task.
void TaskManager::UpdateSubtaskStatus( const std::string&      taskID ,
                                       const Task::TaskStatus& status ,
                                       const vector<string>&   outputs )
{
    for ( auto task : Instances() )
    {
        task->UpdateSubtaskStatus( taskID ,
                                   status ,
                                   outputs);
    }
}
