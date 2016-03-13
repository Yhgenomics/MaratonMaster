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
    
    // Status on the servant session.
    // @note    : note the status of the task running on it.  
    enum ServantStatus
    {
        kUnknow              = 0 ,
        kBooting             = 1 ,
        kSelfTesting         = 2 ,
        kStandby             = 3 ,
        kError               = 4 ,
        kResourceDownloading = 10 ,
        kTaskDataPreparing   = 11 ,
        kComputing           = 12 ,
        kUploading           = 13 ,
        kTaskFinished        = 14 ,
        kException           = 20
    };

    // Servants with differents may offer variances. 
    enum ServantTypes
    {
        kSoftware  = 0 ,
        kOther     = 10
    };

    // Constructor
    // @note    : Use the raw pointer as the constrains from Maraton Framework. 
    Servant( ServantSession * session );
    
    // Destructor.
    ~Servant();

    // Periodic function for updating the servant status.
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
    Error LaunchTask( sptr<TaskDescriptor> task );

    // Getter for servant session's raw pointer.
    // @note    : Do not delete the pointer. 
    ServantSession* Session();
    
    // Getter for the status show whether the servant is still alive.
    bool Connected()                   { return this->connected_; }
    
    // Getter and Setter for CPU cores.
    void CPU( size_t value )           { cpu_ = value;            }
    size_t CPU()                       { return cpu_;             }
    
    // Getter and Setter for Memory size in KBs.
    void MemorySize( size_t value )    { memory_size_ = value;    }
    size_t MemorySize()                { return memory_size_;     }
                                               
    // Getter and Setter for Disk size in MBs.                 
    void DiskSize( size_t value )      { disk_size_ = value;      }
    size_t DiskSize()                  { return disk_size_;       }
    
    // Getter and Setter for the Servant ID.
    // @note    £º Servant ID is given by the Servant via a MessageRegist.
    void ID( string value )            { id_ = value;             }
    string ID()                        { return id_;              }
                                                                  
    // Getter and Setter for a servant's ablility.
    // @note    : The value is given by evalutaion method. 
    void Ability( size_t value )       { ability_ = value;        }
    size_t Ability()                   { return ability_;         }
                                                                  
    // Getter and Setter for servant's status.
    void Status( ServantStatus value ) { status_ = value;         }
    ServantStatus Status()             { return status_;          }
    
    // Getter and Setter for servant's type.
    void Type(ServantTypes value)      { type_ = value;           }
    ServantTypes Type()                { return type_;            }  
                                           
    // Getter and Settter for current task asigned to this servant.                     
    void CurrentTask( sptr<TaskDescriptor> value ) { this->current_task_ = value; }
    sptr<TaskDescriptor> CurrentTask()             { return current_task_;        }

private:
    // Check time out and kick the session from ServantManager.
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