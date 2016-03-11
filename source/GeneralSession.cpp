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
* Description   : Basic events.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/27
* Modifed       : When      | Who       | What
***********************************************************************************/

#include <GeneralSession.h>
#include <MessageHub.h>
#include <memory>

void GeneralSession::OnConnect()
{
}

void GeneralSession::SendOut( uptr<::google::protobuf::Message> message )
{
    uptr<MRT::Buffer> head      = make_uptr( MRT::Buffer , "YH" );
    uptr<MRT::Buffer> length    = make_uptr( MRT::Buffer , 4    );
    uptr<MRT::Buffer> body      = Protocal::MessageHub::Instance()->Build( move_ptr( message ) );

    *( ( int* )length->Data() ) = ( int )body->Size();

    this->Send( move_ptr( head   ) );
    this->Send( move_ptr( length ) );
    this->Send( move_ptr( body   ) );
}

void GeneralSession::OnRead( uptr<MRT::Buffer> data )
{
    this->circle_buffer_.Push( move_ptr( data ) );
    while ( true )
    {
        switch ( this->parse_state_ )
        {
            case MessageParseState::kHeader:
            {
                auto buf = circle_buffer_.Pop( 2 );

                if ( buf == nullptr )return;

                if ( buf->Data()[ 0 ] == 'Y' &&
                     buf->Data()[ 1 ] == 'H' )
                {
                    this->parse_state_ = MessageParseState::kLength;
                }
            }break;
            case MessageParseState::kLength:
            {
                auto buf = circle_buffer_.Pop( 4 );

                if ( buf == nullptr )return;

                int len = *( ( int * )buf->Data() );

                if ( len > MAX_CIRCLE_BUFFER_SIZE )
                {
                    this->parse_state_ = MessageParseState::kHeader;
                    break;
                }

                body_length_        = len;
                this->parse_state_  = MessageParseState::kBody;

            }break;
            case MessageParseState::kBody:
            {
                auto buf = circle_buffer_.Pop( body_length_ );

                if ( buf == nullptr )return;

                auto result = Protocal::MessageHub::Instance()->Handle( this ,
                                                                        buf->Data() ,
                                                                        buf->Size() );

                if ( result < 0 )
                {
                    this->close();
                    return;
                }

                body_length_        = 0;
                this->parse_state_  = MessageParseState::kHeader;
            }break;
            default:
                break;
        }
    }
}

void GeneralSession::OnWrite( uptr<MRT::Buffer> data )
{
}

void GeneralSession::OnClose()
{
}