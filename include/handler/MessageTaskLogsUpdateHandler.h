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

#ifndef MESSAGETASKLOGSUPDATE_HANDLER_H_
#define MESSAGETASKLOGSUPDATE_HANDLER_H_

#include "MessageTaskLogsUpdate.pb.h"
#include "MessageHandler.h"
#include "GeneralSession.h"
#include "json.hpp"
#include "Base64Coder.h"
#include <functional>
#include <string>
#include <memory>

using nlohmann::json;

namespace Protocal
{
    class MessageTaskLogsUpdateHandler : public MessageHandler
    {
    public:
        MessageTaskLogsUpdateHandler()
        {
            MessageType("MessageTaskLogsUpdate");
            Method = []( GeneralSession* session , const void* pData , size_t length )
            {
                char* dataContent  = ( char* )pData;
                      dataContent += sizeof( size_t );
                int   msgLength    = scast<int>( length - sizeof( size_t ) );

                auto msg = make_uptr( MessageTaskLogsUpdate );
                msg->ParseFromArray( dataContent , msgLength );
                json RESTLog;
                RESTLog[ "errorMark" ] = msg->errormark();
                RESTLog[ "taskID"    ] = msg->taskid();
                RESTLog[ "subtaskID" ] = msg->subtaskid();
                RESTLog[ "servantID" ] = msg->servantid();

                // Encode the special charactors for transforming via HTTP                
                RESTLog[ "content" ] = *( Base64Coder::Encode( msg->content() ) );
                
                Logger::Log( "Begin to send log" );
                Protocal::MessageHub::Instance()->SendRESTInfo( Protocal::MessageHub::Instance()->GetRESTLogFulPath() ,
                                                                RESTLog.dump() /*,
                                                                "Log of Task ID " + msg->taskid()*/ );
 
                return true;
            };
        }
    };
}

#endif //!MESSAGETASKLOGSUPDATE_HANDLER_H_

