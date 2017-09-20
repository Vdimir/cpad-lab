#!/bin/bash

cmake -DCMAKE_INSTALL_PREFIX=./_install ../

make

# cmake -D COMPONENT=user -P cmake_install.cmake
cmake -D COMPONENT=developer -P cmake_install.cmake