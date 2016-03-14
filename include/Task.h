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
* Description   : One task from bussiness level may be dispatched to different 
                  servants.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/29
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef TASK_H_
#define TASK_H_ 

#include "TaskDescriptor.h"
#include "Servant.h"
#include "Error.h"
#include "maraton.h"
#include "MessageTaskDeliver.pb.h"
#include <string>
#include <vector>
#include <map>

// @Description : Logical task be managed by TaskManager.
// @note        : Task should first be binded to servants, then can be executed.
//                Task from business layer may be remaped to multi servants if the
//                task can be parallel.
class Task
{
public:

    //Task Status.
    enum TaskStatus
    {
        kUnknow = 0 ,
        kPending,
        kRunning,
        kFinished,
        kStopped,
        kError
    };
    
    // Constructor from a task descriptor.
    Task( uptr<TaskDescriptor> task);

    // Constructor from a protobuf message MessageTaskDeliver.
    Task( uptr<MessageTaskDeliver> message);
        
    // Destructor
    ~Task();

    // Launch task
    Error      Launch();
    
    // If every subtasks finished
    bool       CheckFinish();

    // On every subtask finished
    void       OnFinish();

    // Abort task
    void       Abort();

    // Make sub tasks
    // @note    : The original task from Business to Master is in 1:1 relationship.
    //            the subtask is the task from Master to Servants it is 1:1 when 
    //            the original task is not parallel, 1:n otherwise.
    bool       MakeSubtasks();

    // Update the status of the tasks executed by Servant.
    void       UpdateSubtaskStatus( string     subTaskID ,
                                    TaskStatus status   );
               
    // Getter and Setter for task status
    TaskStatus Status()             { return this->status_;        }
    void Status( TaskStatus value ) { this->status_ = value;       }

    // Getter of the task ID
    std::string ID()                { return original_task_->ID(); }

private:

    // Task descriptor of the original task from Business.
    uptr<TaskDescriptor>         original_task_;

    // Task message of the original task from Business.
    uptr<MessageTaskDeliver>     original_message_;

    // Flag for task finishing.
    // @note    : be true only when all task is finished.
    bool                         is_finished_       = false;
    
    // Flag for sub task ready
    // @note    : Be true after MakeSubtasks at least once.
    bool                         is_sub_tasks_ready = false;

    // The Status for the task.
    TaskStatus                   status_            = TaskStatus::kUnknow;

    // The descriptor for all subtasks
    vector<sptr<TaskDescriptor>> sub_tasks_;

    // The status for all subtasks
    std::map<std::string ,       
        TaskStatus>              sub_tasks_status_;

};

#endif // !TASK_H_ 