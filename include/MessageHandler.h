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
* Date          : 2016/3/2
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef MESSAGE_HANDLER_H_
#define MESSAGE_HANDLER_H_

#include <functional>
#include <string>
#include "GeneralSession.h"

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
    // @Note        : Add it to MessageHub to handle message automaticly.
    //                the message is in pData,it can be a protobuf message, or any
    //                other type determined by the original sender.
    class MessageHandler
    {
    public:
        
        // The handler typedefine
        // @param   : session is the source of the message.
        // @param   : pData is the content of the message.
        // @param   : length is the size of message.
        // @note    : should translate from the pData to certain message first.
        typedef std::function<bool( GeneralSession* session ,
                                    const void*     pData   ,
                                    size_t          length )> HandlerMethod;

        // Getter and Setter for message types
        std::string MessageType()                    { return message_type_;  }
        void        MessageType( std::string value ) { message_type_ = value; }

        // Handler method on the message type
        // @note    : Be given in the constructor for each dervied class. 
        HandlerMethod   Method = nullptr;

        // Name of the message
        std::string     message_type_;

    };
}

#endif //!MESSAGE_HANDLER_H_