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
* Description   : Manage a list of servant.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/29
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef SERVANT_MANAGER_H_
#define SERVANT_MANAGER_H_ 

#include "MRT.h"
#include "Servant.h"
#include "GeneralSession.h"

class ServantManager :
    public MRT::Manager<Servant>,
    public MRT::Singleton<ServantManager>
{
public:

    sptr<Servant>               FindBySeesion( sptr<GeneralSession> session );
    sptr<Servant>               FindBySessionID( size_t sessionID );
    sptr<Servant>               FindByServantID( std::string servantID );
    std::vector<sptr<Servant>>  FindByTaskID( std::string taskID );
    size_t                      GetScore(const vector<std::string>& servantIDList);
    size_t                      GetScore(const std::string& servantID);
    std::vector<sptr<Servant>>  AllServants();

    void                        Update();

private:

    friend Singleton<ServantManager>;

};

#endif // !SERVANT_MANAGER_H_ 