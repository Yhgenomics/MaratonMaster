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

// Constructor
// @ip      : The IP address of the servant session. Set 0.0.0.0 to listen
//            to any IP address.  
ServantListener::ServantListener( const std::string& ip )
    : Listener( ip , LISTEN_PORT )
{
}

// Destructor.
ServantListener::~ServantListener()
{
}

// Callback when the servant session is connected.
// @note    : A servant listener may listen to multi servants, so the raw pointer
//            need to be deleted manually.
MRT::Session * ServantListener::CreateSession()
{
    return new ServantSession();
}

// Callback when the servant session opening.
// @session  : The pointer to the session and can be cast to 
//            the pointer to ServantSession by static cast. 
// @note    : need to be pushed into servant manager here.
void ServantListener::OnSessionOpen( MRT::Session * session )
{
    ServantManager::Instance()->Push( make_sptr( Servant , scast<ServantSession*>( session ) ) );
}

// Callback when the servant session closing.
// @session : The pointer to the session and can be cast to 
//            the pointer to ServantSession by static cast. 
// @note    : pop from servant manager and delete the session.
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
