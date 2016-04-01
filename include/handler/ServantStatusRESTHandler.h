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
* Date          : 2016/3/30
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef SERVANT_STATUS_REST_HANDLER_H_
#define SERVANT_STATUS_REST_HANDLER_H_

#include "MessageConverter.h"
#include "ServantManager.h"
#include "RESTHandler.h"
#include "GeneralSession.h"
#include "json.hpp"
#include <functional>
#include <string>
#include <memory>

using nlohmann::json;

namespace Protocal
{
    class ServantStatusRESTHandler : public RESTHandler
    {
    public:
        ServantStatusRESTHandler()
        {
            MessageType( "/servant/status" );
            Method = []( GeneralSession* session , const string& content )
            {
                // Send the reply 
                auto response = make_uptr(MRT::HTTPResponse) ;
                response->Status( 200 );
                response->Header( "Server" , WEB_SERVER_NAME );
                response->Header( "Connection" , "Close" );

                json replyBody;

                for ( auto item : ServantManager::Instance()->AllServants() )
                {

                    json oneServant;
                    oneServant["id"] = item->ID();
                    oneServant["state"] = item->Status();
                    oneServant["cpu"] = ( int )item->CPU();
                    oneServant["memory"] = ( int )item->MemorySize();
                    oneServant["type"] = item->Type();
                    replyBody.push_back(oneServant);
                }
                auto body = make_uptr( MRT::Buffer , replyBody.dump() );
                response->Content( move_ptr( body ) );
                session->SendRESTResponse( move_ptr( response ) );
                session->Close();

                return true;
            };
        }
    };
}

#endif //!SERVANT_STATUS_REST_HANDLER_H_

