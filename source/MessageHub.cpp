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
* Date          : 2016/3/12
* Modifed       : When      | Who       | What
fibonacci

***********************************************************************************/
#include "MessageHub.h"

using std::string;

namespace Protocal
{
    // Add one handler to the Hub
    bool MessageHub::AddHandler( uptr<MessageHandler> oneHandler )
    {
        // The handler's method cannot be empty
        if ( oneHandler->Method == nullptr )
        {
            return false;
        }

        bool result;
        size_t messageID = HashName( oneHandler->MessageType() );

        // New handler
        if ( handler_map_.find( messageID ) == handler_map_.end() )
        {
            handler_map_[ messageID ] = std::move( oneHandler );
            result = true;
        }

        // Do not allow binding different handlers for same message
        else
        {
            result = false;
        }

        return result;
    }

    bool MessageHub::AddRESTHandler( uptr<RESTHandler> oneHandler )
    {
        // The handler's method cannot be empty
        if ( oneHandler->Method == nullptr )
        {
            return false;
        }

        bool result;

        // New handler
        if ( rest_handler_map_.find( oneHandler->MessageType() ) == rest_handler_map_.end() )
        {
            rest_handler_map_[ oneHandler->MessageType() ] = std::move( oneHandler );
            result = true;
        }

        // Do not allow binding different handlers for same message
        else
        {
            result = false;
        }

        return result;
    }

    // Handle one message arcoding to the handler map
    // @note    : only parse the messageID out and pass the original data pointer
    //            to the handler
    int MessageHub::Handle( GeneralSession* session ,
                            const void* pData ,
                            size_t length )
    {
        size_t  messageID = 0;
        char*   data      = ( char* )pData;
                messageID = *( ( size_t* )data );

        handler_map_[ messageID ]->Method( session , pData , length );

        return 0;
    }

    // Handler one REST Message arcoding to the REST Handler map
    // @session : The source of the message.
    // @url     : The url of the request.
    // @content : The contentn in the request.s
    int MessageHub::HandleREST( GeneralSession * session , const string & url , const string & content )
    {
        rest_handler_map_[ url ]->Method( session , content );
        return 0;
    }

    // Build the protobuf message to buffer
    uptr<MRT::Buffer> MessageHub::Build( uptr<::google::protobuf::Message> message )
    {
        size_t            message_id = HashName( message->GetTypeName() );
        string            body       = message->SerializeAsString();
        uptr<MRT::Buffer> buffer     = make_uptr( MRT::Buffer , 
                                                  body.size() + sizeof( size_t ) );

        char*             pbuf       = buffer->Data();
            *( ( size_t* )pbuf )     = message_id;

                          pbuf      += sizeof( size_t );

#if _WIN32
        memcpy_s( pbuf , body.size() , body.c_str() , body.size() );
#else
        memcpy( pbuf , body.c_str() , body.size() );
#endif

        return move_ptr( buffer );
    }

    // Set the REST IP and Port
    int MessageHub::SetRESTReportAddress( const string & ip , const string & port )
    {
        rest_report_ip_ = ip;
        rest_report_port_= port;
        return true;
    }

    int MessageHub::SendRESTInfo( const string & destFullPath , const string & content )
    {
        Logger::Log( "send REST dest [%] content[%]" , destFullPath , content );
        MRT::WebClient myWebClient;
        myWebClient.Header( "Content-Type" , "application/json" );
        auto result = myWebClient.PostSync( destFullPath , content );
        int maxTry = kMaxRESTRetry;
        
        while( 200 != result->Status() && maxTry--)
        {
            result = myWebClient.PostSync( destFullPath , content );
        }

        Logger::Log("Task Result final response status [ % ]",result->Status() );

        return 0;
    }

    // Send the rest report to remote ip adn port
    // @report : in json format
    // @logInfo: log to be printed when message deliverd.
    /*int MessageHub::SendRESTReport( const string & report , const string & logInfo )
    {
        MRT::WebClient myWebClient;
        myWebClient.Header( "Content-Type" , "application/json" );
        myWebClient.Post( GetRESTReportFullPath() ,
                          report ,
                          [ this , logInfo ] ( uptr<MRT::HTTPResponse> response )
        {
            Logger::Log( "REST Message Delivered! % " , logInfo );
        }
        );
        return 0;
    }*/

    // Send the rest log to remote ip and port
    // @log    : task's log in json format 
    // @logInfo: log to be printed when message deliverd.
    /*int MessageHub::SendRESTLog( const string & log , const string & logInfo )
    {
        MRT::WebClient myWebClient;
        myWebClient.Header( "Content-Type" , "application/json" );
        myWebClient.Post( GetRESTLogFulPath() ,
                          log ,
                          [ this , logInfo ] ( uptr<MRT::HTTPResponse> response )
        {
            Logger::Log( "Log Message Delivered! % " , logInfo );
        }
        );
        return 0;
    }*/

    // Constructor
    MessageHub::MessageHub() 
    {
        Init();
    }

    // Destructor
    inline MessageHub::~MessageHub() {}
    
    // Initialization
    void MessageHub::Init()
    {
        Logger::Log( "Message Hub Initializing." );
        rest_report_ip_       = "";
        rest_report_port_     = "80";
        rest_report_path_     = "/maraton/result";
        rest_log_path_        = "/maraton/log";
        rest_report_protocal_ = "http://";
        AddAllHandlers();
        Logger::Log( "Message Hub Initialized" );
    }

    // Hash the name of a message
    size_t MessageHub::HashName( const std::string& messageType )
    {
        size_t result = 0;

        for ( int i = 0; i < messageType.length(); i++ )
        {
            char    b         = ( char )messageType[ i ];
            size_t  v         = ( ( ( size_t )b << ( ( i % ( char )8 ) * ( char )8 ) ) | i );
                    result   |= ( size_t )( v );
        }

        return result;
    }
}
