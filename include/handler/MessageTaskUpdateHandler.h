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

#ifndef MESSAGETASKUPDATE_HANDLER_H_
#define MESSAGETASKUPDATE_HANDLER_H_

#include "MessageTaskUpdate.pb.h"
#include "MessageHandler.h"
#include "TaskManager.h"
#include "GeneralSession.h"
#include <functional>
#include <string>
#include <memory>

namespace Protocal
{
    class MessageTaskUpdateHandler : public MessageHandler
    {
    public:
        MessageTaskUpdateHandler()
        {
            MessageType("MessageTaskUpdate");
            Method = []( GeneralSession* session , const void* pData , size_t length )
            {
                char* dataContent = ( char* )pData;
                dataContent += sizeof( size_t );
                int msgLength = scast<int>( length - sizeof( size_t ) );

                auto msg = make_uptr( MessageTaskUpdate );
                msg->ParseFromArray( dataContent , msgLength );

                auto servant = ServantManager::Instance()->FindBySessionID( session->ID() );

                if ( servant )
                {
                   auto subtaskID = servant->CurrentTask()->ID();
                   std::vector<std::string> outputs;
                   for( const auto& item : msg->output() )
                   {
                       outputs.push_back( item );
                   }
                   TaskManager::Instance()->UpdateSubtaskStatus( subtaskID , 
                                                                 Task::TaskStatus( msg->status() ) ,
                                                                 outputs);
                }
                return true;
            };
        }
    };
}

#endif //!MESSAGETASKUPDATE_HANDLER_H_

