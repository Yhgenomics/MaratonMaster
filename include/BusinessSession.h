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

#ifndef BUSINESS_SESSION_H_
#define BUSINESS_SESSION_H_ 

#include "GeneralSession.h"
#include "MRT.h"
#include <vector>
#include <mutex>
#include <string>

// @Description : Business session is the session responseable to a business node.
// @Example     : Be created and use in Business listener. See BusinessListener for
//                more deatails              
// @Note        : It is under one-time use and no-hold strategy, which means master 
//                will not manage them.
class BusinessSession : public GeneralSession
{
public:

    //Constructor
    BusinessSession() {};

    // Destructor.
    ~BusinessSession() override {};

    // Callback when receiving REST data from net
    // @data    : Buffer in unique pointer
    virtual void OnRead( uptr<MRT::Buffer> data )  override;

    MRT::HTTPRequest request_;

};

#endif //!BUSINESS_SESSION_H_ 