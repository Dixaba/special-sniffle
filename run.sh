#!/bin/bash

qmake -v
cd /project/build
qmake /project/source
make -j $(nproc)