TEMPLATE = subdirs

SUBDIRS += appslib AutoIncreaseBuildNr DecoderPro3 \
    ftdilib LayoutEditor libPr3 libPref \
    LocoIO LocoNetMonitor PanelPro JavaQt \
<<<<<<< HEAD
    Tables QtWebApp
appslib.depends += JavaQt libPr3 libPref Tables LayoutEditor
libPr3.depends += JavaQt QtWebApp
=======
    Tables
appslib.depends += JavaQt libPr3 libPref Tables LayoutEditor
libPr3.depends += JavaQt
>>>>>>> 3ea6a431ea042a12f11e9da7f00bc94fae7de1aa
libPref.depends += JavaQt
PanelPro.depends += appslib LayoutEditor libPr3 libPref LocoIO Tables
DecoderPro3.depends += appslib LayoutEditor libPr3 libPref LocoIO Tables
LocoNetMonitor.depends += appslib LayoutEditor libPr3 libPref LocoIO Tables
