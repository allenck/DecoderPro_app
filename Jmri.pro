TEMPLATE = subdirs

SUBDIRS += appslib AutoIncreaseBuildNr DecoderPro3 \
    ftdilib LayoutEditor libPr3 libPref \
    LocoIO PanelPro JavaQt operations \
    Tables QtWebApp InstallTest tests
LayoutEditor.depends += JavaQt AutoIncreaseBuildNr
appslib.depends += JavaQt libPr3 libPref Tables LayoutEditor
libPr3.depends += JavaQt QtWebApp
libPref.depends += JavaQt
LocoIO.depends += JavaQt
PanelPro.depends += appslib LayoutEditor libPr3 libPref LocoIO Tables AutoIncreaseBuildNr
DecoderPro3.depends += appslib LayoutEditor libPr3 libPref LocoIO Tables
operations.depends += appslib JavaQt
tests.depends += appslib LayoutEditor libPr3 libPref JavaQt
