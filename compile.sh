#!/bin/sh

rm -rf build
meson setup build
ninja -C build

if [ "$#" -ne 0 ]; then
    cd build
    ninja doc/doxygen_doc
fi
