/***********************************************************************************
This file is part of Test Project for MaratonMaster
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
* Description   : Run all tests.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/25
* Modifed       : When      | Who       | What
***********************************************************************************/

#define TEST_ON

#ifdef TEST_ON
#include "RunList.h"
#include "../3rd/json.hpp"
#include <string>
#include <vector>

using nlohmann::json;
using std::string;
using std::vector;
using namespace std;

int main( int argc , char** argv )
{
    testing::InitGoogleTest( &argc , argv );
    RUN_ALL_TESTS();
    json test1;
    json big;
    vector<string> vec1= { "123" };
    vec1.clear();
    test1[ "vec1" ] = vec1;
    big["big"] = test1;
    cout << "json now is like \n" << big.dump( 4 ) << endl;
    cout << big[ "input" ].is_null() << endl;
    cout << big[ "big" ].size() << endl;
    system( "pause" );
    return 0;
}
#endif