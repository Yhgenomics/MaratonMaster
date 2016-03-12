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
* Description   : Message hub for all message session receive.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/2
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef MESSAGE_HUB_H_
#define MESSAGE_HUB_H_

#include "MessageHandler.h"
#include "GeneralSession.h"
#include "MRT.h"
#include <string>
#include <map>
#include <iostream>
#include <functional>
#include <google/protobuf/message.h>

namespace Protocal
{
    // @Description : Basic Class for kinds of message handler used by MessageHub 
    //                automaticly after be add to the MessageHub.Check MessageHub
    //                for more details.
    // @Example     : namespace Protocal
    //                {
    //                    class SomeMessageHandler : public MessageHandler
    //                    {
    //                    public:
    //                        MessageGreetingHandler()
    //                        {
    //                            MessageType("SomeMessage");
    //                            Method = []( GeneralSession* session , 
    //                                         const void* pData , 
    //                                         size_t length )     
    //                            {
    //                                //TODO add your codes here
    //                                return true;
    //                            };
    //                        }
    //                    };
    //                }              
    // @Note        : Add the derived class to MessageHub to handle message automaticly.
    //                the message is in pData,it can be a protobuf message, or any
    //                other type determined by the original sender.
    class MessageHub : public MRT::Singleton<MessageHub>
    {
    public:
        // Constructor
        MessageHub()  {};

        // Deconstructor
        ~MessageHub() {};

        // Add one handler to the Hub
        bool AddHandler( uptr<MessageHandler> oneHandler );

        // Gloable Message handlers management
        // @note    : Implement in AddAllHandler.cpp seprately.
        bool AddAllHandlers();

        // Handle one message arcoding to the handler map
        int Handle( GeneralSession* session , const void* pData , size_t length );
        
        // Build the protobuf message to buffer
        uptr<MRT::Buffer> Build( uptr<::google::protobuf::Message> message );

    private:
        // Handler map keep the messageID and Handler in a 1:1 relationship
        std::map<size_t , uptr<MessageHandler> > handler_map_;

        // Hash the name of a message
        size_t HashName( std::string messageType );

        friend MRT::Singleton<MessageHub>;
    };

}
#endif // !MESSAGE_HUB_H_