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
* Description   : Listener for Business session.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/12
* Modifed       : When      | Who       | What
***********************************************************************************/

#include "BusinessListener.h"

// Callback when the business session opening.
// @note    : use naked new and raw pointer under the constrains from Maraton's
//            framework.      
MRT::Session * BusinessListener::CreateSession()
{
    return new BusinessSession();   
}

// Callback when the business session opening.
void BusinessListener::OnSessionOpen( MRT::Session * session )
{
    LOG_SYS( "Business session in. IP Address :[ %ld ]\r\n" , session->ip_address() );
}

// Callback when the business session closing.
// @note    : Maraton's Listener must delete the session pointer in the OnsessionClose
//            method, as the listener may manage multi sessions. 
void BusinessListener::OnSessionClose( MRT::Session * session )
{
    SAFE_DELETE( session ); 
    LOG_SYS( "Business session close. IP Address :[ %ld ]\r\n" , session->ip_address() );
}
