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

// @Description : Manager for servants.            
// @Example     : 
//                {
//                    auto servantlist = ServantManager()->Instance()->AllServants();  
//                }            
// @Note        : Once a servant be added into ServantManager, all access to it should
//                via ServantManager.
class ServantManager :
    public MRT::Manager<Servant>,
    public MRT::Singleton<ServantManager>
{
public:
    
    // Find Servant by a session's shared pointer.
    sptr<Servant>               FindBySeesion( sptr<GeneralSession> session );
    
    // Find Servant by a session ID.
    // @note    : used mostly in message handler, which always known the session ID.
    sptr<Servant>               FindBySessionID( size_t sessionID );

    // Find Servnat by a servant ID.
    sptr<Servant>               FindByServantID( std::string servantID );
    
    // Find Servant which is handling the given task
    std::vector<sptr<Servant>>  FindByTaskID( std::string taskID );

    // Get sum score for a list of Servants' ID 
    size_t                      GetScore(const vector<std::string>& servantIDList);
    
    // Get the score for one Servant.
    size_t                      GetScore(const std::string& servantID);
    
    // Access to all alived servants.
    std::vector<sptr<Servant>>  AllServants();

    // Update each Servant's status
    void                        Update();

private:

    friend Singleton<ServantManager>;

};

#endif // !SERVANT_MANAGER_H_ 