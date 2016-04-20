#!/bin/sh
rm -rf cmakebuild/
CMaker project:MaratonMaster compiler:clang++ head:*.h src:*.cpp,*.c,*.cc,*.hpp lib:/usr/local/lib/libprotobuf.a,./lib/libMaratonFramework.a,./lib/libuv.a
cd cmakebuild
cmake .
make -j 4
cp MaratonMaster ../
cd ../
chmod 777 MaratonMaster
