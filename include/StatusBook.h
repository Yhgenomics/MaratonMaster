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
* Description   : Constant values table. 
*                 The status are divided to different namespaces.
*                 Each namespace has an unique number range.
*                 Each status has an unique number.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/18
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef STATUS_BOOK_
#define STATUS_BOOK_

// System reserved status range
// @note  : 0 is reversed for ErrorCode::kNoError
// @range : 1-99 

// On Servant's session work status
// @note  : not the status of the task running on it. 
// @range : 100-299
namespace ServantStatus
{  
    enum Code
    {
        kUnknown    = 100 ,
        kStandby    = 101 ,
        kWorking    = 102 ,
        kRecovering = 103 ,
        kException  = 104 ,  
        kError      = 105     
    };
}

// Task status
// @range : 300-499
namespace TaskStatus
{
    enum Code
    {
        kUnknown  = 300 ,
        kPending  = 301 ,
        kRunning  = 302 ,
        kFinished = 303 ,
        kStopped  = 304 ,
        kError    = 305
    };
}

// Servants with differents may offer variances. 
// @range : 500-699
namespace ServantTypes
{
    enum Code
    {
        kSoftware = 500,
        kOther    = 699
    };
}

// Error Code
// @note  : 0 is reversed for ErrorCode::kNoError
// @range : 10000-19999
namespace ErrorCode 
{
    enum Code
    {
        kNoError      = 0 ,

        // 10100-10299 Servant Error
        kServantBusy  = 10100,

        // 10300-10499 Task Error
        kTaskNotReady = 10300,
        kSubTaskError = 10301,

        kUndefined    = 19999 ,
    };
}

#endif // !STATUS_BOOK_