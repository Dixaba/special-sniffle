#!/bin/bash

pwd
qmake -v
cd /project/build
pwd
qmake /project/source
make -j $(nproc)