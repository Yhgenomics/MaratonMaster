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
* Date          : 2016/3/30
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef TASK_ABORT_REST_HANDLER_H_
#define TASK_ABORT_REST_HANDLER_H_

#include "TaskManager.h"
#include "RESTHandler.h"
#include "GeneralSession.h"
#include "json.hpp"
#include <functional>
#include <string>
#include <memory>

using nlohmann::json;

namespace Protocal
{
    class TaskAbortRESTHandler : public RESTHandler
    {
    public:
        TaskAbortRESTHandler()
        {
            MessageType( "/task/abort" );
            Method = [ this ] ( GeneralSession* session , const string& content )
            {

                json taskAbortReply;
                auto taskIn = json::parse( content );     
                taskAbortReply[ "taskid" ] = taskIn[ "id" ];

                if ( IsInputValid( content ) )
                {
                    TaskManager::Instance()->Abort( taskIn[ "id" ] );
                }

                taskAbortReply[ "code"    ] = ErrorCode::kNoError;
                taskAbortReply[ "message" ] = "Abort order pushed!";
                // Send the reply and close the session
                session->SendRESTCloseSession(taskAbortReply.dump());
                return true;
            };
        }

        // Check the format of the content.
        // Such as confirming the exsitence of null empty key elements.
        // This check makes sure the message can be trans into the system.
        // @content : The content in JSON 
        virtual bool CheckFormat( const string& content ) override
        {
            return true;
        }


        // Check the constraints from higher level needs.
        // This check makes sure the meaningful and acceptable to the system.
        // @content : The content in JSON
        virtual bool CheckConstraints( const string& content ) override
        {
            return true;           
        }

    };
}

#endif //!TASK_ABORT_REST_HANDLER_H_

