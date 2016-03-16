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
* Description   : Listener for session's event on create, open and close.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/2
* Modifed       : When      | Who       | What
***********************************************************************************/

#include "ServantListener.h"
#include "ServantManager.h"
#include "Servant.h"
#include <iostream>

ServantListener::ServantListener( const std::string& ip )
    : Listener( ip , LISTEN_PORT )
{
}

ServantListener::~ServantListener()
{
}

MRT::Session * ServantListener::CreateSession()
{
    return new ServantSession();
}

void ServantListener::OnSessionOpen( MRT::Session * session )
{
    ServantManager::Instance()->Push( make_sptr( Servant , scast<ServantSession*>( session ) ) );
}

void ServantListener::OnSessionClose( MRT::Session * session )
{
    auto s   = scast<ServantSession*>( session );
    auto exe = ServantManager::Instance()->FindBySessionID( s->ID() );

    if ( exe != nullptr )
    {
        ServantManager::Instance()->Pop( exe );
    }
    SAFE_DELETE( session );
}
