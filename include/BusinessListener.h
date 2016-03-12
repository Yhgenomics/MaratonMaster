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
* Date          : 2016/3/4
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef BUSINESS_LISTENER_H_
#define BUSINESS_LISTENER_H_

#include "BusinessSession.h"
#include "MasterGloable.h"
#include "MRT.h"
#include <string>

// @Description : Listener to a business session( given by ip and port ). 
//                The businiess session will not be hold.
//                The Business Listerner should be regist into the Maraton's
//                framework first, then it will work after the framework
//                start to run.            
// @Example     : 
//                {
//                    ...
//                    MRT::Maraton::Instance()->Regist
//                    (
//                        make_uptr( BusinessListener , "0.0.0.0" ) 
//                    );
//                    ...
//                    MRT::Maraton::Instance()->Run();   
//                }            
// @Note        : As a listener, three interfaces must be override is the CreatSession
//                OnSessionOpen and the OnSessionClose.
//                Do not use a smart pointer on the session as a constrain from
//                the Maraton framewrok. 
class BusinessListener : public MRT::Listener
{
public:

    // Constructor takes an IP address as the input, but the port is predefined.
    // @param   : ip is the IP address of the business session. Set 0.0.0.0 to listen
    //            to any IP address.  
    // @example : 
    //            {
    //                make_uptr( BusinessListener , "0.0.0.0" ) ;
    //            }   
    BusinessListener( std::string ip ) :MRT::Listener( ip , BUSINESS_PORT ) {};

    // Deconstructor.
    ~BusinessListener() {};

private:

    // Callback when the business session is connected.
    virtual MRT::Session * CreateSession()                override;            
    
    // Callback when the business session opening.
    // @param   : session is the pointer to the session and can be cast to 
    //            the pointer to BusinessSession by static cast.                                                      
    virtual void OnSessionOpen( MRT::Session * session )  override; 

    // Callback when the business session closing.
    // @param   : session is the pointer to the session and can be cast to 
    //            the pointer to BusinessSession by static cast. 
    virtual void OnSessionClose( MRT::Session * session ) override;

};

#endif // !BUSINESS_LISTENER_H_
