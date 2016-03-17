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

// @Description : Error with error code and message            
// @Example     : 
//                {
//                   Error runningResult(0,"Every thing is fine!");
//                   ...
//                   runingResult.Code( 1 );
//                   runingResult.Message( "Something went wrong!" );
//                }            
// @Note        : set message after code will ensure the error message be printed
//                to standard output automaticly.
class Error
{
public:

    // Constructor
    Error() {}
    
    // Constructor with the error code and message.
    // @code    : The error code with 0 for no error,
    //            while other value's meaning determinded by upper layer.
    // @message : A readable string.
    Error( const size_t& code , const std::string& message )
    {
        this->code_     = code;
        this->message_  = message_;
    }

    // Copy Constructor
    Error( Error & error )
    {
        this->code_     = error.code_;
        this->message_  = error.message_;
    }

    // Move Consturcotr
    Error( Error && error )
    {
        this->code_     = error.code_;
        this->message_  = error.message_;
        error.message_  = "";
        error.code_     = 0;
    }

    //Getter and Setter for error code
    size_t Code()                    { return this->code_;    };
    void Code( const size_t& value ) { this->code_ = value;   };

    //Getter and Setter for error message
    //@note     : Any message assigned to a non zero Error will be printed 
    //            to standard ouput automaticly. 
    std::string Message()            { return this->message_; };
    void Message( const std::string& value )
    {
        this->message_ = value;
        if ( this->code_ != 0 )
            printf( "Error:%s\r\n" , this->message_.c_str() );
    }

private:
    // Error code
    size_t      code_    = 0;

    // Readable error message
    std::string message_ = "";

};

#endif // !ERROR_H_ 
