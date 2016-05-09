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
* Description   : Maraton Master main logic.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/25
* Modifed       : When      | Who       | What
***********************************************************************************/

#include "MRT.h"
#include "ServantManager.h"
#include "TaskManager.h"
#include "MessageHub.h"
#include "ServantListener.h"
#include "BusinessListener.h"
#include <memory>

#include "Base64Coder.h"
// Main function for Maraton Master
int main( int argc , char** argv )
{  
    Logger::Sys("build % %" , __DATE__ , __TIME__);

    // The first time call the MessagHub will initialise it
    Protocal::MessageHub::Instance()->SetRESTReportAddress( argv[ 1 ] , argv[ 2 ] );

    // By returning flase will keep this worker running.
    MRT::SyncWorker::Create( 1 , [] ( MRT::SyncWorker* worker )
    {
        ServantManager::Instance()->Update();
        TaskManager::Instance()->Update();
        return false;
    } , nullptr , nullptr );

    while ( true )
    {
        Logger::Log("Maraton Master's main loop begin");
        
        MRT::Maraton::Instance()->Regist( make_uptr( BusinessListener , "0.0.0.0" ) );        
        MRT::Maraton::Instance()->Regist( make_uptr( ServantListener  , "0.0.0.0" ) );
        
        MRT::Maraton::Instance()->Run();
    }

    return 0;
}