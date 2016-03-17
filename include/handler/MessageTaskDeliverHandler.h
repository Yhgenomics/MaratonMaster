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

#ifndef MESSAGETASKDELIVER_HANDLER_H_
#define MESSAGETASKDELIVER_HANDLER_H_

#include "TaskManager.h"
#include "MessageTaskDeliver.pb.h"
#include "MessageTaskDeliverReply.pb.h"
#include "TaskDescriptor.h"
#include "GeneralSession.h"
#include "MessageHandler.h"
#include "MasterGloable.h"
#include <functional>
#include <string>
#include <memory>

namespace Protocal
{
    class MessageTaskDeliverHandler : public MessageHandler
    {
    public:

        MessageTaskDeliverHandler()
        {
            MessageType("MessageTaskDeliver");

            Method = []( GeneralSession* session , const void* pData , size_t length )
            {
                // Take the task in
                char* dataContent = ( char* )pData;
                dataContent += sizeof( size_t );
                int msgLength = scast<int>( length - sizeof( size_t ) );

                auto msg = make_uptr( MessageTaskDeliver );
                msg->ParseFromArray( dataContent , msgLength );

                auto task = make_sptr( Task , move_ptr( msg ) );
                task->Status( TaskStatus::kPending );
                TaskManager::Instance()->Push( task );

                // Send the task received 
                auto deliverReply = make_uptr( MessageTaskDeliverReply );
                deliverReply->set_taskid( task->ID() );
                deliverReply->set_code( 0 );
                deliverReply->set_message( "task received!" );
                session->SendOut( std::move( deliverReply ) );

                return true;
            };
        }
    };
}

#endif //!MESSAGETASKDELIVER_HANDLER_H_

