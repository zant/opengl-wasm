#!/bin/sh -x
mkdir -p -- build
cd build
cmake -GNinja ..
ninja && ./main
