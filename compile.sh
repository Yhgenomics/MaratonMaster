#!/bin/sh
rm -rf cmakebuild/
CMaker project:MaratonMaster head:*.h,*.hpp src:*.cpp,*.hpp,*.cc,*.c flag:-Wall-std=c++11-pthread lib:lib/libuv.a,lib/maraton-framework-v3.a
cd cmakebuild
cmake .
make -j 4
cp MaratonMaster ../
cd ../
chmod 777 MaratonMaster
