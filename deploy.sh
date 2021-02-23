#!/bin/bash

cp -d appslib/libappslib.so* ~/Jmri_apps
cp -d JavaQt/libJavaQt.so.* ~/Jmri_apps
cp -d libPr3/libPr3.so.* ~/Jmri_apps
cp -d LayoutEditor/libLayoutEditor.so.* ~/Jmri_apps
cp -d libPref/libPref.so.* ~/Jmri_apps
cp -d LocoIO/libLocoIO.so.* ~/Jmri_apps
cp -d operations/liboperations.so.* ~/Jmri_apps
cp -d Tables/libTables.so.* ~/Jmri_apps
cp -d tests/libtests.so.* ~/Jmri_apps
cp PanelPro/PanelPro ~/Jmri_apps
cp DecoderPro3/DecoderPro3 ~/Jmri_apps

cp -d appslib/libappslibd.so* ~/Jmri_apps
cp -d JavaQt/libJavaQtd.so.* ~/Jmri_apps
cp -d libPr3/libPr3d.so.* ~/Jmri_apps
cp -d LayoutEditor/libLayoutEditord.so.* ~/Jmri_apps
cp -d libPref/libPrefd.so.* ~/Jmri_apps
cp -d LocoIO/libLocoIOd.so.* ~/Jmri_apps
cp -d operations/liboperationsd.so.* ~/Jmri_apps
cp -d Tables/libTablesd.so.* ~/Jmri_apps
cp -d tests/libtestsd.so.* ~/Jmri_apps
cp PanelPro/PanelProd ~/Jmri_apps
cp DecoderPro3/DecoderPro3d ~/Jmri_apps

ldconfig

