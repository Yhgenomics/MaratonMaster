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
* Description   : Error code.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/29
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef ERROR_H_
#define ERROR_H_ 

#include <string>

class Error
{
public:

    Error() {}

    Error( size_t code , std::string message )
    {
        this->code_     = code;
        this->message_  = message_;
    }

    Error( Error & error )
    {
        this->code_     = error.code_;
        this->message_  = error.message_;
    }

    Error( Error && error )
    {
        this->code_     = error.code_;
        this->message_  = error.message_;
        error.message_  = "";
        error.code_     = 0;
    }

    size_t      Code()               { return this->code_;  };
    void        Code( size_t value ) { this->code_ = value; };

    std::string Message() { return this->message_; };
    void        Message( std::string value )
    {
        this->message_ = value;
        if ( this->code_ != 0 )
            printf( "Error:%s\r\n" , this->message_.c_str() );
    }

private:

    size_t      code_    = 0;
    std::string message_ = "";
};

#endif // !ERROR_H_ 
