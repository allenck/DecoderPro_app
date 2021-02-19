#!/bin/bash

cp -d appslib/libappslib.so* /usr/local/lib
cp -d JavaQt/libJavaQt.so.* /usr/local/lib
cp -d libPr3/libPr3.so.* /usr/local/lib
cp -d LayoutEditor/libLayoutEditor.so.* /usr/local/lib
cp -d libPref/libPref.so.* /usr/local/lib
cp -d LocoIO/libLocoIO.so.* /usr/local/lib
cp -d operations/liboperations.so.* /usr/local/lib
cp -d Tables/libTables.so.* /usr/local/lib
cp -d tests/libtests.so.* /usr/local/lib
cp PanelPro/PanelPro /usr/bin
cp DecoderPro3/DecoderPro3 /usr/bin
ldconfig

