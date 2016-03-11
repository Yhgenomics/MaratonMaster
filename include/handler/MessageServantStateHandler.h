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

#ifndef MESSAGESERVANTSTATE_HANDLER_H_
#define MESSAGESERVANTSTATE_HANDLER_H_

#include "MessageServantState.pb.h"
#include "MessageServantStateReply.pb.h"
#include "GeneralSession.h"
#include "MessageHandler.h"
#include "ServantManager.h"
#include <functional>
#include <string>
#include <memory>

namespace Protocal
{
    class MessageServantStateHandler : public MessageHandler
    {
    public:
        MessageServantStateHandler()
        {
            MessageType( "MessageServantState" );
            Method = [] ( GeneralSession* session , const void* pData , size_t length )
            {
                //TODO add your codes here
                auto reply = make_uptr( MessageServantStateReply );

                for ( auto item : ServantManager::Instance()->AllServants() )
                {
                    reply->add_id( item->ID() );
                    reply->add_cpu( item->CPU() );
                    reply->add_state( item->Status() );
                    reply->add_memory( item->MemorySize() );
                    reply->add_type( item->Type() );
                }
                session->SendOut( std::move( reply ) );
                return true;
            };
        }
    };
}

#endif //!MESSAGESERVANTSTATE_HANDLER_H_

