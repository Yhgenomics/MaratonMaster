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
* Description   : Kinds of find method add and pop.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/29
* Modifed       : When      | Who       | What
***********************************************************************************/

#include "ServantManager.h"
#include "Servant.h"

// Find Servant by a session's shared pointer.
// @session : a shared pointer to a GeneralSession
sptr<Servant> ServantManager::FindBySeesion( sptr<GeneralSession> session )
{
    return FindBySessionID( session->ID() );
}

// Find Servant by a session ID.
// @sessionID : ID of a session.
// @note      : used mostly in message handler, which always known the session ID.
sptr<Servant> ServantManager::FindBySessionID( const size_t& sessionID )
{
    for ( auto item : this->Instances() )
    {
        if ( sessionID == item->Session()->ID() )
        {
            return item;
        }
    }

    return sptr<Servant>();
}

// Find Servnat by a servant ID.
// @servantID : ID of a servant
sptr<Servant> ServantManager::FindByServantID( const std::string& ServantID )
{
    for ( auto item : this->Instances() )
    {
        if ( ServantID == item->ID() )
        {
            return item;
        }
    }

    return sptr<Servant>();
}

// Find Servant which is handling the given task
// @taskID : ID of a task(not a sub task).
std::vector<sptr<Servant>> ServantManager::FindByTaskID( const std::string& taskID )
{
    auto result = std::vector<sptr<Servant>>();

    for ( auto item : this->Instances() )
    {
        if ( nullptr != item->CurrentTask() && taskID == item->CurrentTask()->ID() )
        {
            result.push_back( item );
        }
    }

    return result;
}

// Get sum score for a list of Servants' ID 
// @servantIDList : ID of servants need to be counted in.
size_t ServantManager::GetScore(const vector<std::string>& servantIDList )
{
    size_t result = 0;

    for ( const auto& item : servantIDList )
    {
        auto tempServant = FindByServantID( item );
        if ( tempServant )
        {
            result += tempServant->Ability();
        }        
    }

    return result;
}

// Get the score for one Servant.
// @servantID : ID of a servant
size_t ServantManager::GetScore( const std::string & servantID )
{
    size_t result      = 0;
    auto   tempServant = FindByServantID( servantID );

    if ( tempServant )
    {
        result = tempServant->Ability();
    }

    return result;
}

// Access to all alived servants.
std::vector<sptr<Servant>> ServantManager::AllServants()
{
    return Instances();
}

// Update each Servant's status
// @note : the Update data for each servant will cause the 
//         seesion to close if time out. But the OnClose, which will
//         pop the servant out the servant manager, is guaranteed to 
//         be called only after this for loop by the Maraton Framework.
void ServantManager::Update()
{
    for ( auto item : this->Instances() )
    {
        item->Update();
    }
}

