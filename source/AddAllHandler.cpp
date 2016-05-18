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
* Description   : Do all Handlers management.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/25
* Modifed       : When      | Who       | What
***********************************************************************************/

#include "MessageHub.h"
#include "handler/MessageTaskDeliverHandler.h"
#include "handler/MessageTaskDeliverReplyHandler.h"
#include "handler/MessageGreetingHandler.h"
#include "handler/MessageRegistHandler.h"
#include "handler/MessageHeartBeatHandler.h"
#include "handler/MessageServantUpdateHandler.h"
#include "handler/MessageTaskUpdateHandler.h"
#include "handler/TaskDeliverRESTHandler.h"
#include "handler/ServantStatusRESTHandler.h"
#include "handler/TaskLogsRESTHandler.h"
#include "handler/MessageTaskLogsUpdateHandler.h"
#include "handler/TaskAbortRESTHandler.h"
#include "MRT.h"
#include <memory>

namespace Protocal
{
    bool MessageHub::AddAllHandlers()
    {
        Logger::Log( "Message Hub Add Protobuf message handlers" );
        AddHandler( std::move( make_uptr( Protocal::MessageTaskDeliverReplyHandler  ) ) );
        AddHandler( std::move( make_uptr( Protocal::MessageRegistHandler            ) ) );
        AddHandler( std::move( make_uptr( Protocal::MessageHeartBeatHandler         ) ) );
        AddHandler( std::move( make_uptr( Protocal::MessageServantUpdateHandler     ) ) );
        AddHandler( std::move( make_uptr( Protocal::MessageTaskUpdateHandler        ) ) );
        AddHandler( std::move( make_uptr( Protocal::MessageTaskLogsUpdateHandler    ) ) );

        Logger::Log( "Message Hub Add REST message handlers" );
        AddRESTHandler( std::move( make_uptr( Protocal::TaskDeliverRESTHandler   ) ) );
        AddRESTHandler( std::move( make_uptr( Protocal::ServantStatusRESTHandler ) ) );
        AddRESTHandler( std::move( make_uptr( Protocal::TaskLogsRESTHandler      ) ) );
        AddRESTHandler( std::move( make_uptr( Protocal::TaskAbortRESTHandler      ) ) );
        return true;
    }
}