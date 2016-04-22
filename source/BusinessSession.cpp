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
* Description   : Bussiness session is the bussiness controler session.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/27
* Modifed       : When      | Who       | What
***********************************************************************************/

#include "BusinessSession.h"
#include "MessageHub.h"
#include <iostream>
using namespace std;

// Callback when receiving REST data from net
// @data    : Buffer in unique pointer
void BusinessSession::OnRead( uptr<MRT::Buffer> data )
{
    Logger::Log("On Read[%] \r\n %",data->Size(), data->Data() );
    request_.Parse( move_ptr( data ) );

    if ( request_.Finish() )
    {
        auto content = string( request_.Content()->Data() , request_.Content()->Size() );
        Logger::Log("content is \r\n %", content );
        auto result  = Protocal::MessageHub::Instance()->HandleREST( this ,
                                                                     request_.RequestUrl() ,
                                                                     content );
    }
    
}
