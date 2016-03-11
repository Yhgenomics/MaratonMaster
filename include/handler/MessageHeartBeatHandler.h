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
* Description   : Base class for message handler.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/3
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef MESSAGEHEARTBEAT_HANDLER_H_
#define MESSAGEHEARTBEAT_HANDLER_H_

#include "MessageHeartBeat.pb.h"
#include "MessageHandler.h"
#include "GeneralSession.h"
#include <functional>
#include <string>
#include <memory>

namespace Protocal
{
    class MessageHeartBeatHandler : public MessageHandler
    {
    public:
        MessageHeartBeatHandler()
        {
            MessageType("MessageHeartBeat");
            Method = []( GeneralSession* session , const void* pData , size_t length )
            {
                ServantManager::Instance()->FindBySessionID( session->ID() )->Refresh();            
                return true;
            };
        }
    };
}

#endif //!MESSAGEHEARTBEAT_HANDLER_H_

