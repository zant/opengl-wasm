#!/bin/sh -x
mkdir -p -- embuild
cd embuild
emcmake cmake -GNinja ..
ninja
mv main.html index.html
python3 -m http.server
