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

#ifndef TASK_DESCRIPTOR_H_
#define TASK_DESCRIPTOR_H_ 

#include <string>
#include <vector>

#include "MRT.h"
#include "MasterGloable.h"
#include "MessageTaskDeliver.pb.h"

using std::string;
using std::vector;

class PipeDescriptor
{
public:
    string id_;
    string name_;
    string executor_;
    bool   multiple_input_;
    bool   multiple_thread_;
    vector<string> parameters_;
};

class PipelineDescriptor
{
public:
    string id_;
    string name_;
    vector<PipeDescriptor> pipes_;
};

class TaskDescriptor
{
public:

    TaskDescriptor( const MessageTaskDeliver& orignalMessage )
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

    uptr<MessageTaskDeliver> MakeMessage()
    {
        auto result = make_uptr( MessageTaskDeliver );
        result->set_id( this->id_ );
        result->set_originalid( this->original_id_);
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
            for(auto param : item.parameters_)
            {
                tempPipe->add_parameters( param );
            }
        }
        return move_ptr(result);
    }

    TaskDescriptor( const TaskDescriptor& other )
    {    
        this->id_          = other.id_;
        this->original_id_ = other.original_id_;
        this->is_parallel_ = other.is_parallel_;
        this->resources_   = other.resources_;
        this->input_       = other.input_;
        this->servants_    = other.servants_;
        this->pipeline_    = other.pipeline_;   
    }

    TaskDescriptor& operator=( const TaskDescriptor& other )
    {
        this->id_          = other.id_;
        this->id_          = other.original_id_;
        this->is_parallel_ = other.is_parallel_;
        this->resources_   = other.resources_;
        this->input_       = other.input_;
        this->servants_    = other.servants_;
        this->pipeline_    = other.pipeline_;   
        return *this;
    }    

    string ID()                               { return id_;                          }
    void ID( string value )                   { id_= value;                          }
                                                                                     
    bool IsParallel()                         { return is_parallel_;                 }
    void IsParallel( bool value )             { is_parallel_ = value;                }
                                                                                     
    vector<string> Resources()                { return vector<string>( resources_ ); }
    void Resources( vector<string> value )    { resources_ = value;                  }
                                                                                     
    void ResetInput()                         { input_.clear();                      }
    vector<string> Input()                    { return vector<string>( input_ );     }
    void Input( vector<string> value )        { input_ = value;                      }
                                                                                     
    void ResetServants()                      { servants_.clear();                   }
    vector<string> Servants()                 { return vector<string>( servants_ );  }
    void Servants( vector<string> value )     { servants_ = value;                   }
                                                                                     
    PipelineDescriptor Pipeline()             { return pipeline_;                    }
    void Pipeline( PipelineDescriptor value ) { pipeline_ = value;                   }
    
    void PrepareAsSubtask()
    {
        ResetInput();
        ResetServants();
        ID( MRT::UUID::Create() );
    }

private:

    string             id_ ;
    string             original_id_;
    bool               is_parallel_;

    vector<string>     resources_;
    vector<string>     input_;
    vector<string>     servants_;                       
    
    PipelineDescriptor pipeline_;
};

#endif // !TASK_DESCRIPTOR_H_ 