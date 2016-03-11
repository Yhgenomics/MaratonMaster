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
    class MessageHandler
    {
    public:
        typedef std::function<bool( GeneralSession* session ,
                                    const void*     pData   ,
                                    size_t          length )> HandlerMethod;

        std::string MessageType()                    { return message_type_;  }
        void        MessageType( std::string value ) { message_type_ = value; }

        HandlerMethod   Method = nullptr;
        std::string     message_type_;
    };
}

#endif //!MESSAGE_HANDLER_H_