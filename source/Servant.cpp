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
* Description   : Cotrollor for one servant node
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/29
* Modifed       : When      | Who       | What
***********************************************************************************/

#include "Servant.h"
#include "TaskDescriptor.h"
#include "MessageGreeting.pb.h"

// Constructor
// @note    : Use the raw pointer as the constrains from Maraton Framework. 
Servant::Servant( ServantSession * session )
{
    this->session_ = session;
    auto msg = make_uptr( MessageGreeting );
    msg->set_prefix( session->ip_address() + "_");
    msg->set_code(91);
    session->SendOut( move_ptr( msg ) );
    this->Refresh();
}

Servant::~Servant()
{
}

// Periodically called function for updating the servant status.
void Servant::Update()
{
    if ( !this->Connected() )   return;

    if ( this->CheckTimeout() ) return;
}

// Just for test
void Servant::SelfEvaluate()
{
    Ability( CPU() * kCPUFactor /*+ MemorySize()*/ );
}


// Update the last update time
// @note    : be called when reciving a heartbeat message from servant.
inline void Servant::Refresh()
{
    this->last_update_time_ = Timer::Tick();
}

// Stop the current runing task.
void Servant::AbortTask()
{
}

// Getter for servant session's raw pointer.
// @note    : Do not delete the pointer. 
ServantSession * Servant::Session()
{
    return this->session_;
}

// Launch a task specified by a TaskDescriptor.
Error Servant::LaunchTask( sptr<TaskDescriptor> task )
{
    Error launchResult;
    launchResult.Code( ErrorCode::kNoError );

    //TODO
    if ( status_ != ServantStatus::kStandby && status_ != ServantStatus::kPreOccupied )
    {
        launchResult.Code( ErrorCode::kServantBusy );
        launchResult.Message( this->ID() + " servant busy. status ");
        Logger::Log( "Error % status %",launchResult.Message(), status_);
        return launchResult;
    }

    this->CurrentTask( task );
    auto msg = task->MakeMessage();
    this->Session()->SendOut( move_ptr( msg ) );

    return launchResult;
}

// Check time out and kick the dead session from ServantManager.
bool Servant::CheckTimeout()
{
    size_t delta = Timer::Tick() - this->last_update_time_;

    if ( delta >= SERVANT_TIMEOUT )
    {
        this->last_update_time_ = Timer::Tick();
        this->connected_        = false;
        this->session_->Close();
        Logger::Log( "Kick Servant Session ID: [ % ] \r\n" , this->Session()->ID() );
        return true;
    }

    return false;
}
