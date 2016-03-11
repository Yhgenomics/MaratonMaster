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
* Description   : 
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/29
* Modifed       : When      | Who       | What
***********************************************************************************/
#ifndef MARATON_GLOABLE_H_
#define MARATON_GLOABLE_H_ 

#include <stdio.h> 
#include "MRT.h"

#ifdef DEBUB_ONLY
#define SERVANT_TIMEOUT     9999999

#else
#define SERVANT_TIMEOUT     10000000
#endif

#define LISTEN_PORT         90
#define BUSINESS_PORT       91
#define RESTAPI_PORT        8080

#define WEB_SERVER_NAME         "YHGenomics/Maraton"
#define CONF_KEY_WEBSUBSCRIBER  "web_subscriber"

#endif // !MARATON_GLOABLE_H_ 