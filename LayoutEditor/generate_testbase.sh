#!/bin/bash

# run this script to generate python bindings for classes specified in "wrappers.h" and "typesystem_jmri.xml"

export QTDIR=/home/allen/5.11.3/gcc_64
~/pythonqt-code/generator/pythonqt_generator  --debug-level=full --include-paths=../LayoutEditor/test --output-directory=. testwrapper.h typesystem_testbase.xml


