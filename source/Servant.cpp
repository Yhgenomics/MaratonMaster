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

Servant::Servant( ServantSession * session )
{
    this->session_ = session;

    auto msg = make_uptr( MessageGreeting );
    msg->set_code(91);
    session->SendOut( move_ptr( msg ) );
    this->Refresh();
}

Servant::~Servant()
{
}

void Servant::Update()
{
    if ( !this->Connected() ) return;

    if ( this->CheckTimeout() ) return;
}

// Just for test
void Servant::SelfEvaluate()
{
    Ability( CPU() * 1000 + MemorySize() );
}

void Servant::StopTask()
{
    /*if ( this->current_task_ == nullptr ) return;

    uptr<Protocol::MessageTaskCancel> msg = make_uptr( Protocol::MessageTaskCancel );
    msg->task_id( this->current_task_->id() );

    this->session()->send_message( move_ptr( msg ) );*/
}

ServantSession * Servant::Session()
{
    return this->session_;
}

Error Servant::LaunchTask( sptr<TaskDescriptor> task )
{
    Error launchResult;
    launchResult.Code( 0 );

    if (status_ != ServantStatus::kStandby )
    {
        launchResult.Code( 1 );
        launchResult.Message( this->ID() + ": task running" );
        return launchResult;
    }

    this->CurrentTask( task );
    auto msg = task->MakeMessage();
    this->Session()->SendOut( move_ptr( msg ) );

    return launchResult;
}

bool Servant::CheckTimeout()
{
    size_t delta = Timer::Tick() - this->last_update_time_;

    if ( delta >= SERVANT_TIMEOUT )
    {
        this->last_update_time_ = Timer::Tick();
        this->connected_        = false;
        this->session_->close();
        LOG_SYS( "Kick Servant Session ID: [ %ld ] \r\n" , this->Session()->ID() );
        return true;
    }

    return false;
}
