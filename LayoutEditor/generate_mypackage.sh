#!/bin/bash

# run this script to generate python bindings for classes specified in "wrappers.h" and "typesystem_jmri.xml"

export QTDIR=/home/allen/Qt/5.15.2/gcc_64
~/Projects/PythonQt/pythonqt-code/generator/pythonqt_generator  --debug-level=sparse --include-paths=../libPr3/:./libPr3/Roster/:..LibPr3/Signal:../libPr3/loconet:../libPr3/LocoIO:../libPr3/rfid:../LayoutEditor/:../appslib/:../JavaQt/:../libPref/:../Tables:../LocoIO/:../QtWebApp --output-directory=. wrappers.h typesystem_jmri.xml

