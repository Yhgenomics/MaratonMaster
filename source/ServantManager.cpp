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
#include "json.hpp"

using nlohmann::json;

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
size_t ServantManager::GetScore(const std::vector<std::string>& servantIDList )
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

// Check if a list of servants are all in a final status
// thus, servant no longer exist or not at work.
bool ServantManager::IsFinal( const std::vector<std::string>& servantIDList )
{
    bool result = true;
    
    for ( const auto& item : servantIDList )
    {
        bool isOneFinal = false;

        // break when on not final servant exsit
        if ( !result ) { break; }

        auto tempServant = FindByServantID( item );
        
        // servant on longer exsit
        if ( !tempServant )
        {
            isOneFinal = true;
        }
        
        // servant not at work
        else if ( ServantStatus::kWorking != tempServant->Status() )
        {
            isOneFinal = true;
        }
        
        result = isOneFinal && result;

    }

    return result;
}

// check if a list of servant at least one no longer exited
bool ServantManager::AtLeastOneMissed( const std::vector<std::string>& servantIDList )
{
    bool result = false;

    for( const auto& item : servantIDList )
    {
        if ( nullptr == FindByServantID( item ) )
        {
            result = true;
            break;
        }
    }
    return result;
}

// Access to all alived servants.
std::vector<sptr<Servant>> ServantManager::AllServants()
{
    return Instances();
}


// Preocuupy the resources for a task
// @taskNeedResources : reference to task JSON from REST API
//                      the servants list will be re-confirmed in this method 
// @return : if preoccupied successed.
bool ServantManager::PreoccupyResources( string & taskNeedResources )
{
    bool IsPreOcupped = false;
    auto taskCheck    = json::parse( taskNeedResources );
    bool onlyNeedOne  = !taskCheck[ "isParallel" ];
    vector<string> preOcuppiedServants;
    preOcuppiedServants.clear();

    for ( auto const& item : taskCheck[ "servants" ] )
    {
        if ( ServantStatus::kStandby == FindByServantID( item )->Status() )
        {
            FindByServantID( item )->Status( ServantStatus::kPreOccupied );
            preOcuppiedServants.push_back( item );
            IsPreOcupped = true;
            if ( onlyNeedOne )
                break;
        }
    }

    taskCheck[ "servants" ].clear();
    taskCheck[ "servants" ] = preOcuppiedServants;

    taskNeedResources = taskCheck.dump();
    return IsPreOcupped;
}

// set preoccupied servants to standby 
bool ServantManager::FreePreoccupied( const string & servantID )
{
    bool result = false;
    auto servant = FindByServantID( servantID );
    if ( servant )
    {
        if( ServantStatus::kPreOccupied == servant->Status())
        {
            servant->Status(ServantStatus::kStandby);
            result = true;
        }
    }
    return result;
}

// Log out all servants status
void ServantManager::ShowServants()
{
    for ( auto const &item : AllServants() )
    {
        Logger::Log( "[ID, status]% ,% " , item->ID() , item->Status() );
    }
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

