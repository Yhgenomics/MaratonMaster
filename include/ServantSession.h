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
* Description   : Servant session is special kind of session.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/27
* Modifed       : When      | Who       | What
***********************************************************************************/
#ifndef SERVANT_SESSION_H_
#define SERVANT_SESSION_H_ 

#include <vector>
#include <mutex>
#include <string>

#include "GeneralSession.h"
#include "MRT.h"

class ServantSession :
    public GeneralSession
{
public:

    ServantSession();
    virtual ~ServantSession() override;

protected: 

private: 

};

#endif //!SERVANT_SESSION_H_ 