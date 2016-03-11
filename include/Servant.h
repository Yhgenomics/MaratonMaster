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

using namespace std;

class Servant
{
public:

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

    enum ServantTypes
    {
        kSoftware  = 0 ,
        kOther = 10
    };

    Servant( ServantSession * session );
    ~Servant();

    //functions
    void Update();
    
    void SelfEvaluate();

    void Refresh()
    {
       this->last_update_time_ = Timer::Tick();
    };

    void StopTask();

    Error LaunchTask( sptr<TaskDescriptor> task );

    //getter & setter
    ServantSession* Session();
    bool Connected()                   { return this->connected_; }
    
    void CPU( size_t value )           { cpu_ = value;            }
    size_t CPU()                       { return cpu_;             }
    
    void MemorySize( size_t value )    { memory_size_ = value;    }
    size_t MemorySize()                { return memory_size_;     }
                                                                  
    void DiskSize( size_t value )      { disk_size_ = value;      }
    size_t DiskSize()                  { return disk_size_;       }
                                                                  
    void ID( string value )            { id_ = value;             }
    string ID()                        { return id_;              }
                                                                  
    void Ability( size_t value )       { ability_ = value;        }
    size_t Ability()                   { return ability_;         }
                                                                  
    void Status( ServantStatus value ) { status_ = value;         }
    ServantStatus Status()             { return status_;          }
    
    void Type(ServantTypes value)      { type_ = value;           }
    ServantTypes Type()                { return type_;            }  
                                                                
    void CurrentTask( sptr<TaskDescriptor> value ) { this->current_task_ = value; }
    sptr<TaskDescriptor> CurrentTask()             { return current_task_;        }

private:

    ServantSession* session_;
                    
    size_t          last_update_time_  = 0;
    bool            connected_         = true;
                                       
    size_t          memory_size_       = 0;
    size_t          disk_size_         = 0;
    size_t          cpu_               = 0;
    string          id_                = "";
    size_t          ability_           = 0;
    ServantStatus   status_            = ServantStatus::kUnknow;
    sptr<TaskDescriptor> current_task_ = nullptr;
    ServantTypes    type_              = ServantTypes::kOther;

    bool            CheckTimeout();
};

#endif // !SERVANT_H_ 