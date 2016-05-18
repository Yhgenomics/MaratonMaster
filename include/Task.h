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
#include "ServantManager.h"
#include "Servant.h"
#include "Error.h"
#include "MRT.h"
#include "MessageTaskDeliver.pb.h"
#include "MasterGloable.h"
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;

// @Description : Logical task be managed by TaskManager.
// @note        : Task should first be binded to servants, then can be executed.
//                Task from business layer may be remaped to multi servants if the
//                task can be parallel.
class Task
{
public:

    // Constructor from a task descriptor.
    // @task : Task descriptor in a unique pointer.
    Task( uptr<TaskDescriptor> task );

    // Constructor from a protobuf message MessageTaskDeliver.
    // @message : task deliver message in a unique pointer
    Task( uptr<MessageTaskDeliver> message );

    // Destructor
    ~Task();

    // Launch task
    Error Launch();

    // return true when all subtasks finished successfully, flase otherwise.
    bool  IsAllSubtasksFinished();

    // return if error happens
    // 1. subtask error
    // 2. servant no longger exsited and it's work not finished.
    bool  IsAnyError();

    // check 
    // 1. if all subtasks have been finished
    // 2. if any eror happens(that will cause an abort operation.
    void  CheckRunningTask();

    // check if this task can finish
    // two constrains
    // 1. task finished
    // 2. servant at a final status
    bool  CanFinish();

    // On every subtask finished
    void  OnFinish();

    // Abort task
    void  Abort();

    // Make sub tasks
    // @note    : The original task from Business to Master is in 1:1 relationship.
    //            the subtask is the task from Master to Servants it is 1:1 when 
    //            the original task is not parallel, 1:n otherwise.
    bool  MakeSubtasks();

    // Update the status of the tasks executed by Servant.
    // @subTaskID : The ID for subtask not the task
    // @status    : The status for subtask
    // @outputs   : The subtask's output information witch should be append to
    //              the task.
    void  UpdateSubtaskStatus( const string&         subTaskID ,
                               const TaskStatus::Code&     status ,
                               const vector<string>& outputs );

    // Getter and Setter for task status
    TaskStatus::Code Status()                    { return this->status_;                }
    void Status( const TaskStatus::Code& value ) { this->status_ = value;               }

    // Getter of the task ID
    std::string MainTaskID()                     { return original_task_->OriginalID(); }

    // Getter and Setter for Abort mark
    bool UpperLayerAbort()                       { return upper_layer_abort_;           }
    void UpperLayerAbort( const bool& value )    { upper_layer_abort_ = value;          }

    // Initialization
    void Init();

    // Free all preoccupied servants
    void FreePreOccupiedServants();

    // Set Error message to make a report
    void SetErrorMessage( Error& msg );

private:

    // Task descriptor of the original task from Business.
    uptr<TaskDescriptor>         original_task_;

    // Task message of the original task from Business.
    uptr<MessageTaskDeliver>     original_message_;

    // Flag for task finishing.
    // @note    : be true only when all task is finished.
    bool                         is_finished_;

    // Flag for sub task ready
    // @note    : Be true after MakeSubtasks at least once.
    bool                         is_sub_tasks_ready;

    // Flag for abort running task 
    // @note    : no use to finished task.
    bool                         upper_layer_abort_;

    // The Status for the task.
    TaskStatus::Code             status_;

    // The descriptor for all subtasks
    vector<sptr<TaskDescriptor>> sub_tasks_;

    // The status for all subtasks
    std::map<std::string ,
        TaskStatus::Code>        sub_tasks_status_;

    // List gathering all subtasks' products information
    vector<std::string>          outputs_;

    // Error informations to be report out
    Error                        error_message_;

};

#endif // !TASK_H_ 