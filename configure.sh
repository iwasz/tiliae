#!/bin/bash
#export CC=/home/iwasz/local/share/clang-3.6.0/bin/clang
#export CXX=/home/iwasz/local/share/clang-3.6.0/bin/clang++
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE='Debug' -DCMAKE_INSTALL_PREFIX:PATH=$HOME/local -DBUILD_SHARED_LIBS=on -DBUILD_TESTS=0 -DBUILD_DEMO=0 -DLLVM_ROOT="/home/iwasz/local/share/llvm/" -DBOOST_ROOT="/home/iwasz/local" ..
