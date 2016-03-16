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

sptr<Servant> ServantManager::FindBySeesion( sptr<GeneralSession> session )
{
    return FindBySessionID( session->ID() );
}

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

std::vector<sptr<Servant>> ServantManager::AllServants()
{
    return Instances();
}

void ServantManager::Update()
{
    for ( auto item : this->Instances() )
    {
        item->Update();
    }
}

