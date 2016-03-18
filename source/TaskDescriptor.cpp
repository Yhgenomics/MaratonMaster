#include "..\include\TaskDescriptor.h"
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
* Description   : Describe one task from bussiness level.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/29
* Modifed       : When      | Who       | What
***********************************************************************************/

// Constructor from the protobuf message
TaskDescriptor::TaskDescriptor( const MessageTaskDeliver & orignalMessage )
{
    this->id_             = orignalMessage.id();
    this->original_id_    = orignalMessage.originalid();
    this->is_parallel_    = orignalMessage.isparallel();
    this->pipeline_.id_   = orignalMessage.pipeline().id();
    this->pipeline_.name_ = orignalMessage.pipeline().name();

    for ( auto item : orignalMessage.resources() )
    {
        this->resources_.push_back( item );
    }

    for ( auto item : orignalMessage.input() )
    {
        this->input_.push_back( item );
    }

    for ( auto item : orignalMessage.servants() )
    {
        this->servants_.push_back( item );
    }

    for ( auto item : orignalMessage.pipeline().pipes() )
    {
        PipeDescriptor tempPipe;
        tempPipe.id_              = item.id();
        tempPipe.name_            = item.name();
        tempPipe.executor_        = item.executor();
        tempPipe.multiple_input_  = item.multipleinput();
        tempPipe.multiple_thread_ = item.multiplethread();

        for ( auto param : item.parameters() )
        {
            tempPipe.parameters_.push_back( param );
        }

        this->pipeline_.pipes_.push_back( tempPipe );
    }
}

// Constructor from another task descriptor
// @note    : Useful to make sub tasks
TaskDescriptor::TaskDescriptor( const TaskDescriptor & other )
{
    this->id_          = other.id_;
    this->original_id_ = other.original_id_;
    this->is_parallel_ = other.is_parallel_;
    this->resources_   = other.resources_;
    this->input_       = other.input_;
    this->servants_    = other.servants_;
    this->pipeline_    = other.pipeline_;
}

// Make a protobuf message
uptr<MessageTaskDeliver> TaskDescriptor::MakeMessage()
{
    auto result = make_uptr( MessageTaskDeliver );
    result->set_id( this->id_ );
    result->set_originalid( this->original_id_ );
    result->set_isparallel( this->is_parallel_ );
    result->mutable_pipeline()->set_id( this->pipeline_.id_ );
    result->mutable_pipeline()->set_name( this->pipeline_.name_ );

    for ( auto item : this->resources_ )
    {
        result->add_resources( item );
    }

    for ( auto item : this->input_ )
    {
        result->add_input( item );
    }

    for ( auto item : this->servants_ )
    {
        result->add_servants( item );
    }

    for ( auto item : this->pipeline_.pipes_ )
    {
        auto tempPipe = result->mutable_pipeline()->add_pipes();
        tempPipe->set_id( item.id_ );
        tempPipe->set_name( item.name_ );
        tempPipe->set_executor( item.executor_ );
        tempPipe->set_multipleinput( item.multiple_input_ );
        tempPipe->set_multiplethread( item.multiple_thread_ );

        for ( auto param : item.parameters_ )
        {
            tempPipe->add_parameters( param );
        }
    }

    return move_ptr( result );
}

// Make a task a new ID, and ready for resign the input and servant
void TaskDescriptor::PrepareAsSubtask()
{
    ResetInput();
    ResetServants();
    ID( MRT::UUID::Create() );
}
