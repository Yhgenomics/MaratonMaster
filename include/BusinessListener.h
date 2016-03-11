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
* Description   : Listener for Business events.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/4
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef BUSINESS_LISTENER_H_
#define BUSINESS_LISTENER_H_

#include <string>

#include "MRT.h"
#include "BusinessSession.h"

class BusinessListener : public MRT::Listener
{
public:

    BusinessListener( std::string ip ) :MRT::Listener( ip , BUSINESS_PORT ) {};
    ~BusinessListener() {};

protected:

private:

    virtual MRT::Session * CreateSession() override { return new BusinessSession(); };

    virtual void OnSessionOpen( MRT::Session * session ) override { std::cout << "Business session in" << std::endl; };

    virtual void OnSessionClose( MRT::Session * session ) override { SAFE_DELETE( session ); std::cout << "Business session close" << std::endl; };

};

#endif // !BUSINESS_LISTENER_H_
