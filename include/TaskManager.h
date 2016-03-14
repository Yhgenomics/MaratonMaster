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

#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_ 

#include <string>
#include <vector>

#include "maraton.h"
#include "TaskDescriptor.h"
#include "Task.h"

// @Description : Manager for tasks from business layer.
class TaskManager : 
    public MRT::Manager<Task>,
    public MRT::Singleton<TaskManager> 
{
public:

    // Update each task status launching it if is pending. 
    void  Update();

    // Stop task
    // @param   : taskID
    void  Stop( std::string taskID );
    
    // Launch task
    // @param   : taskID
    Error Launch( std::string taskID );

    // UpdateSubtaskStatus
    void  UpdateSubtaskStatus( std::string taskID , Task::TaskStatus status );

private:

    friend Singleton<TaskManager>; 
};

#endif // !TASK_MANAGER_H_ 