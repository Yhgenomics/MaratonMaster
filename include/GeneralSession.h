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
* Description   : Session with message parser based on a circle buffer.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/27
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef GENERAL_SESSION_H_
#define GENERAL_SESSION_H_

#include "MRT.h"
#include <google/protobuf/message.h>
#include <memory>

class GeneralSession : public MRT::Session,public std::enable_shared_from_this<GeneralSession>
{
public:

    GeneralSession           (){};
    virtual ~GeneralSession  () override {};
    size_t  ID               (){return id_ ;};
    virtual void SendOut     ( uptr<::google::protobuf::Message> );

protected:
    
    virtual void OnConnect()                       override;
    virtual void OnRead( uptr<MRT::Buffer> data )  override;
    virtual void OnWrite( uptr<MRT::Buffer> data ) override;
    virtual void OnClose()                         override;

private:

    enum MessageParseState
    {
        kHeader = 1,
        kLength ,
        kBody
    };

    MRT::CircleBuffer   circle_buffer_; 
    MessageParseState   parse_state_     = MessageParseState::kHeader;
    size_t              body_length_     = 0;
    size_t              oringal_size_    = 0;
    size_t              compressed_size_ = 0;
    size_t              id_              = -1;

    void TryPopMessage( );
};

#endif // !GENERAL_SESSION_H_