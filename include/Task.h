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

#include <string>
#include <vector>
#include <map>

#include "TaskDescriptor.h"
#include "Servant.h"
#include "Error.h"
#include "maraton.h"
#include "MessageTaskDeliver.pb.h"

class Task
{
public:

    enum TaskStatus
    {
        kUnknow = 0 ,
        kPending,
        kRunning,
        kMerging,
        kFinished,
        kStopped,
        kError
    };

    Task( uptr<TaskDescriptor> task);
    Task( uptr<MessageTaskDeliver> message);
        
    ~Task();

    Error      Launch();
    void       Abort();
    bool       MakeSubtasks();
               
    TaskStatus Status()                   { return this->status_;  };
    void       Status( TaskStatus value ) { this->status_ = value; };

    std::string     ID() {return original_task_->ID();}
               
    void       UpdateSubtaskStatus( string     subTaskID ,
                                    TaskStatus status   );

private:

    uptr<TaskDescriptor>         original_task_;
    uptr<MessageTaskDeliver>     original_message_;

    bool                         is_finished_       = false;
    bool                         is_sub_tasks_ready = false;
    TaskStatus                   status_            = TaskStatus::kUnknow;

    vector<sptr<TaskDescriptor>> sub_tasks_;

    std::map<std::string ,       
        TaskStatus>              sub_tasks_status_;

};

#endif // !TASK_H_ 