TEMPLATE = subdirs

SUBDIRS += appslib AutoIncreaseBuildNr DecoderPro3 \
    ftdilib LayoutEditor libPr3 libPref \
    LocoIO PanelPro JavaQt \
    Tables QtWebApp InstallTest
LayoutEditor.depends += JavaQt AutoIncreaseBuildNr
appslib.depends += JavaQt libPr3 libPref Tables LayoutEditor
libPr3.depends += JavaQt QtWebApp
libPref.depends += JavaQt
LocoIO.depends += JavaQt
PanelPro.depends += appslib LayoutEditor libPr3 libPref LocoIO Tables AutoIncreaseBuildNr
DecoderPro3.depends += appslib LayoutEditor libPr3 libPref LocoIO Tables

