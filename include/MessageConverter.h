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
* Description   : Conveter message between REST API and Protobuf message.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/30
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef MESSAGE_CONVERTER_H_
#define MESSAGE_CONVERTER_H_

#include "TaskDescriptor.h"
#include "MessageTaskDeliver.pb.h"
#include "json.hpp"
#include "MRT.h"
#include <string>

using nlohmann::json;
using std::string;

namespace Protocal
{

    class MessageConverter : public MRT::Singleton<MessageConverter>
    {
    public:

        uptr<MessageTaskDeliver> GenerateTaskDescriptor( const string& jsonContent )//;
        {
            auto result = make_uptr( MessageTaskDeliver );

            auto taskJson = json::parse( jsonContent );

            result->set_id( taskJson["id"] );
            result->set_originalid( taskJson["originalID"] );
            result->set_isparallel( taskJson[ "isParallel" ] );
            result->mutable_pipeline()->set_id( taskJson[ "pipeline" ][ "id" ] );
            result->mutable_pipeline()->set_name( taskJson[ "pipeline" ][ "name" ] );

            for ( auto& item : taskJson[ "resources" ])
            {
                result->add_resources( item );
            }

            for ( auto& item : taskJson[ "input" ] )
            {
                result->add_input( item );
            }

            for ( auto item : taskJson[ "servants" ] )
            {
                result->add_servants( item );
            }

            for ( auto item : taskJson[ "pipeline" ]["pipes"]  )
            {
                auto tempPipe = result->mutable_pipeline()->add_pipes();
                tempPipe->set_id( item[ "id" ] );
                tempPipe->set_name( item[ "name" ] );
                tempPipe->set_executor( item[ "executor" ] );
                tempPipe->set_multipleinput( item[ "multipleInput" ] );
                tempPipe->set_multiplethread( item[ "multipleThread"] );

                for ( auto param : item[ "parameters" ] )
                {
                    tempPipe->add_parameters( param );
                }
            }

            return move_ptr( result );
        }

    }; // end of class MessageConverter : public MRT::Singleton<MessageConverter>
} //  end of namespace Protocal

#endif // !MESSAGE_CONVERTER_H_