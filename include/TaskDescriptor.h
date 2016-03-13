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

#include "MRT.h"
#include "MasterGloable.h"
#include "MessageTaskDeliver.pb.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

// @Description : Description for a pipe.
//                A pipe is one contianer run for one time. 
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

// @Description : Description for a pipeline.
//                A pipeline serval pipes run one by one. 
class PipelineDescriptor
{
public:
    string id_;
    string name_;
    vector<PipeDescriptor> pipes_;
};


// @Description : Description for a task. 
class TaskDescriptor
{
public:

    // Constructor from the protobuf message
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

    // Constructor from another task descriptor
    // @note    : Useful to make sub tasks
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

    // Make a protobuf message
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

    // Copy from other task descriptor
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

    // Getter and Setter for task ID.
    string ID()                               { return id_;                          }
    void ID( string value )                   { id_= value;                          }
    
    // Getter and Setter for Parallel mark
    bool IsParallel()                         { return is_parallel_;                 }
    void IsParallel( bool value )             { is_parallel_ = value;                }
    
    // Getter and Setter for resource list
    vector<string> Resources()                { return vector<string>( resources_ ); }
    void Resources( vector<string> value )    { resources_ = value;                  }

    // Clear the input list
    // @note    : use for making a sub task.
    void ResetInput()                         { input_.clear();                      }
    
    // Getter and Setter for input list
    vector<string> Input()                    { return vector<string>( input_ );     }
    void Input( vector<string> value )        { input_ = value;                      }
                                                                                     
    // Clear the servants list
    // @note    : use for making a sub task.
    void ResetServants()                      { servants_.clear();                   }
    
    // Getter and Setter servants list
    // @note    : subtask only have one servant.
    vector<string> Servants()                 { return vector<string>( servants_ );  }
    void Servants( vector<string> value )     { servants_ = value;                   }
    
    // Getter and Setter for pipeline
    PipelineDescriptor Pipeline()             { return pipeline_;                    }
    void Pipeline( PipelineDescriptor value ) { pipeline_ = value;                   }
    
    // Make a task a new ID, and ready for resign the input and servant
    void PrepareAsSubtask()
    {
        ResetInput();
        ResetServants();
        ID( MRT::UUID::Create() );
    }

private:
    
    // Task ID
    string             id_ ;
    
    // Origninal task ID
    // @note    : use for connect a sub task to an original task,
    //            such as uploading processed data to the original task. 
    string             original_id_;

    // if true, task may be remapped into substasks.
    bool               is_parallel_;

    // Resource list
    vector<string>     resources_;

    // Input list
    vector<string>     input_;

    // Servant list
    vector<string>     servants_;                       
    
    // Pipeline used in this task.
    PipelineDescriptor pipeline_;
};

#endif // !TASK_DESCRIPTOR_H_ 