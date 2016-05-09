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
* Description   : Base 64 code convertor for transform strings via URL
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/5/6
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef BASE64_CODER_H_
#define BASE64_CODER_H_

#include <string>
#include <memory>
#include <MRT.h>
using std::string;

static const char kBase64Table[ 64 ] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/',
};

class Base64Coder
{
public:
    static uptr<string> Encode( const string& source )
    {
        auto result = make_uptr( string );
        auto sourceLength = ( int )source.length();
        auto resultLength = ( ( sourceLength + 2 ) / 3 * 4 )
            + 1;
        
        result->resize( resultLength );

        int i = 0;
        int j = 0;

        for ( i = 0 , j = 0; i <= sourceLength - 3; i += 3 )
        {
            ( *result )[ j++ ] = kBase64Table[ source[ i ] >> 0x02U ];
            ( *result )[ j++ ] = kBase64Table[ ( ( source[ i + 0 ] & 0x03 ) << 0x04U ) | ( source[ i + 1 ] >> 0x04U ) ];
            ( *result )[ j++ ] = kBase64Table[ ( ( source[ i + 1 ] & 0x0F ) << 0x02U ) | ( source[ i + 2 ] >> 0x06U ) ];
            ( *result )[ j++ ] = kBase64Table[ source[ i + 2 ] & 0x3F ];
        }

        if ( 1 == ( sourceLength % 3 ) )
        {
            ( *result )[ j++ ] = kBase64Table[ source[ i ] >> 0x02U ];
            ( *result )[ j++ ] = kBase64Table[ ( source[ i ] & 0x03 ) << 0x04U ];
            ( *result )[ j++ ] = '=';
            ( *result )[ j++ ] = '=';
        }

        else if ( 2 == ( sourceLength % 3 ) )
        {
            ( *result )[ j++ ] = kBase64Table[ source[ i ] >> 0x02U ];
            ( *result )[ j++ ] = kBase64Table[ ( ( source[ i + 0 ] & 0x03 ) << 0x04U ) | ( source[ i + 1 ] >> 0x04U ) ];
            ( *result )[ j++ ] = kBase64Table[ ( source[ i + 1 ] & 0x0F ) << 0x02U ];
            ( *result )[ j++ ] = '=';
        }

        if ( j < resultLength ) { ( *result )[ j ] = '\0'; }

        return std::move( result );    
    }



};
#endif // !BASE64_CODER_H_