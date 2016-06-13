TEMPLATE = subdirs

SUBDIRS += appslib AutoIncreaseBuildNr DecoderPro3 \
    ftdilib LayoutEditor libPr3 libPref \
    LocoIO LocoNetMonitor PanelPro JavaQt \
    Tables
appslib.depends += JavaQt libPr3 libPref Tables LayoutEditor
libPr3.depends += JavaQt
libPref.depends += JavaQt
PanelPro.depends += appslib LayoutEditor libPr3 libPref LocoIO Tables
DecoderPro3.depends += appslib LayoutEditor libPr3 libPref LocoIO Tables
LocoNetMonitor.depends += appslib LayoutEditor libPr3 libPref LocoIO Tables
