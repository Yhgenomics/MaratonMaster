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
* Description   : Cotrollor for one servant node
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/29
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef SERVANT_H_
#define SERVANT_H_ 

#include "TaskDescriptor.h"
#include "ServantSession.h"
#include "Error.h"
#include <string.h>

using std::string;

// @Description : Logcial Servant infomation on its status.
//                Mostly Used through the servant manager.
//                Added to the Servant Manager at the ServantListener's OnSessionOpen.
//                See ServantManager and ServantListener for more details.
class Servant
{
public:

    // Constructor
    // @note    : Use the raw pointer as the constrains from Maraton Framework. 
    Servant( ServantSession * session );
    
    // Destructor.
    ~Servant();

    // Periodically called function for updating the servant status.
    void Update();
    
    // Evaluate the servant's ability
    // @note    : the evalutation method should be fair for every servants.
    void SelfEvaluate();

    // Update the last update time
    // @note    : be called when reciving a heartbeat message from servant.
    void Refresh()
    {
       this->last_update_time_ = Timer::Tick();
    };

    // Stop the current runing task.
    void StopTask();

    // Launch a task specified by a TaskDescriptor.
    // @task    : The task descriptor for a substak
    Error LaunchTask( sptr<TaskDescriptor> task );

    // Getter for servant session's raw pointer.
    // @note    : Do not delete the pointer. 
    ServantSession* Session();
    
    // Getter for the status show whether the servant is still alive.
    bool Connected()                               { return this->connected_;     }

    // Getter and Setter for CPU cores.                                           
    size_t CPU()                                   { return cpu_;                 }
    void CPU( const size_t& value )                { cpu_ = value;                }

    // Getter and Setter for Memory size in KBs.                                  
    size_t MemorySize()                            { return memory_size_;         }
    void MemorySize( const size_t& value )         { memory_size_ = value;        }

    // Getter and Setter for Disk size in MBs.                                    
    size_t DiskSize()                              { return disk_size_;           }
    void DiskSize( const size_t value )            { disk_size_ = value;          }

    // Getter and Setter for the Servant ID.                                      
    // @note    £º Servant ID is given by the Servant via a MessageRegist.        
    string ID()                                    { return id_;                  }
    void ID( const string& value )                 { id_ = value;                 }

    // Getter and Setter for a servant's ablility.                                
    // @note    : The value is given by evalutaion method.                        
    size_t Ability()                               { return ability_;             }
    void Ability( const size_t& value )            { ability_ = value;            }

    // Getter and Setter for servant's status.                                    
    ServantStatus Status()                         { return status_;              }
    void Status( const ServantStatus& value )      { status_ = value;             }

    // Getter and Setter for servant's type.                                      
    ServantTypes Type()                            { return type_;                }  
    void Type(const ServantTypes& value)           { type_ = value;               }

    // Getter and Settter for current task asigned to this servant.                     
    sptr<TaskDescriptor> CurrentTask()             { return current_task_;        }
    void CurrentTask( sptr<TaskDescriptor> value ) { this->current_task_ = value; }

private:

    // Check time out and kick the dead session from ServantManager.
    bool            CheckTimeout();

    // Pointer to the Servant's session.
    ServantSession* session_;
                    
    // Last time tick when servant still alive
    size_t          last_update_time_  = 0;

    // status on whether the servant is still alive.
    bool            connected_         = true;
    
    //  Memory size in KBs.                                   
    size_t          memory_size_       = 0;

    // Disk size in MBs.
    size_t          disk_size_         = 0;
    
    // CPU cores.
    size_t          cpu_               = 0;

    // Servant's ID.
    // note     £º Not the Session ID.
    string          id_                = "";

    // Servant's ablility evaluated in Master.
    size_t          ability_           = 0;
    
    // Servant's status.
    ServantStatus   status_            = ServantStatus::kUnknow;
    
    // Servant's type.
    ServantTypes    type_              = ServantTypes::kOther;

    // Current asigned task.
    sptr<TaskDescriptor> current_task_ = nullptr;

};

#endif // !SERVANT_H_ 