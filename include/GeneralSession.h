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

// @Description : General Session for handle the protobuf messages.                      
// @Note        : The messages are transed by TCP. 
class GeneralSession : public MRT::Session
{
public:

    // Contructor
    GeneralSession();
    
    // Destructor
    virtual ~GeneralSession() override {};

    // Getter for ID
    // @note    : ID is set in constructor automaticly in an increaing way.
    //            No ID setter here.
    size_t  ID()                       { return id_; };
    
    // Send an porotobuf message out in Maraton's style
    virtual void SendOut( uptr<::google::protobuf::Message> );

protected:
    
    // Callback when session connecting
    virtual void OnConnect()                       override;

    // Callback when receiving data from net
    virtual void OnRead( uptr<MRT::Buffer> data )  override;

    // Callback when write adata to net
    virtual void OnWrite( uptr<MRT::Buffer> data ) override;

    // Callback when session closing
    virtual void OnClose()                         override;

private:

    // The TCP package may not delivered at one time
    // so it's important to remember what have done. 
    enum MessageParseState
    {
        kHeader = 1,
        kLength ,
        kBody
    };

    // Restore the raw data from net
    MRT::CircleBuffer   circle_buffer_;
    
    // Current parse staste 
    MessageParseState   parse_state_     = MessageParseState::kHeader;
    
    // Message body's length
    size_t              body_length_     = 0;

    // [NOT IN USE NOW]Orignal message's size
    size_t              original_size_   = 0;

    // [NOT IN USE NOW]Compressed message's size
    size_t              compressed_size_ = 0;

    // General session's ID
    size_t              id_              = -1;

    // [NOT IN USE NOW]
    void TryPopMessage( );
};

#endif // !GENERAL_SESSION_H_