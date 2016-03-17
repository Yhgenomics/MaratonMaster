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
* Date          : 2016/2/29
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef SERVANT_LISTENER_H_
#define SERVANT_LISTENER_H_

#include "ServantSession.h"
#include "MRT.h"
#include <string>

// @Description : Listener to a servant session.
//                Keep the servant session into Servant manager when session open,
//                and pop and delete it when session close.            
// @Example     : 
//                {
//                    ...
//                    MRT::Maraton::Instance()->Regist
//                    (
//                        make_uptr( ServantListener , "0.0.0.0" ) 
//                    );
//                    ...
//                    MRT::Maraton::Instance()->Run();   
//                }            
// @Note        : As a listener, three interfaces must be override is the CreatSession
//                OnSessionOpen and the OnSessionClose.
//                Do not use a smart pointer on the session as a constrain from
//                the Maraton framewrok. 
class ServantListener : public MRT::Listener
{
public:
    
    // Constructor
    // @ip      : The IP address of the servant session. Set 0.0.0.0 to listen
    //            to any IP address.  
    // @example : 
    //            {
    //                make_uptr( BusinessListener , "0.0.0.0" ) ;
    //            }   
    ServantListener( const std::string& ip );
    
    // Destructor.
    ~ServantListener( );

protected:

private:
    
    // Callback when the servant session is connected.
    virtual MRT::Session * CreateSession( ) override;

    // Callback when the servant session opening.
    // @session : The pointer to the session and can be cast to 
    //            the pointer to ServantSession by static cast. 
    virtual void OnSessionOpen( MRT::Session * session ) override;

    // Callback when the servant session closing.
    // @session : The pointer to the session and can be cast to 
    //            the pointer to ServantSession by static cast. 
    virtual void OnSessionClose( MRT::Session * session ) override;

};

#endif // !SERVANT_LISTENER_H_
