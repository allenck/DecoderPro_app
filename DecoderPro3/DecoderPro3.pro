#-------------------------------------------------
#
# Project created by QtCreator 2015-08-23T00:11:05
#
#-------------------------------------------------
APPNAME = "DecoderPro3"
APPVERSION = 0.1
QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DecoderPro3
TEMPLATE = app

MOC_DIR = moc_obj
OBJECTS_DIR = moc_obj

# Windows and Unix get the suffix "d" to indicate a debug version of the library.
# Mac OS gets the suffix "_debug".
CONFIG(debug, debug|release) {
    win32:      TARGET = $$join(TARGET,,,d)
    mac:        TARGET = $$join(TARGET,,,_debug)
    unix:!mac:  TARGET = $$join(TARGET,,,d)
    MOC_DIR = moc_objd
    OBJECTS_DIR = moc_objd
}

PROJ_DIR=$$(PROJ_DIR) # get project directory from env
isEmpty( PROJ_DIR ) {
  win32:PROJ_DIR=C:/Projects
  unix:PROJ_DIR=/home/allen/Projects
}

include(../scripts_config.prf)
#PYTHONQT_PREFIX=$$(PYTHONQT_PREFIX)
#isEmpty( PYTHONQT_PREFIX ) {
#  win32:PYTHONQT_PREFIX=C:/Program Files (x86)/local/lib
#  unix:PYTHONQT_PREFIX=$${PROJ_DIR}/PythonQt/pythonqt-code
#}

#include($$PYTHONQT_PREFIX/build/python.prf)

SOURCES += main.cpp\
        mainwindow.cpp \
    decoderpro3.cpp \
    decoderpro3window.cpp \
    decoder3action.cpp

HEADERS  += mainwindow.h \
    decoderpro3.h \
    decoderpro3window.h \
    decoder3action.h

FORMS    += mainwindow.ui

unix:exists($$PYTHONQT_PREFIX/lib/libPythonQt-Qt5-Python$${PYTHON_VERSION}_d.so) {
 ENABLE_SCRIPTING = "Y"
 message(DecoderPro3: $$PYTHONQT_PREFIX/lib/libPythonQt-Qt5-Python$${PYTHON_VERSION}_d.so + "found OK")
} else:unix: {
 message(DecoderPro3: $$PYTHONQT_PREFIX/lib/libPythonQt-Qt5-Python$${PYTHON_VERSION}_d.so + "not found")
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/release/ -lappslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/debug/ -lappslib
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/ -lappslib
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/ -lappslibd

INCLUDEPATH += $$PWD/../appslib
DEPENDPATH += $$PWD/../appslib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3/release/ -lPr3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3/debug/ -lPr3
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3/ -lPr3
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3/ -lPr3d

INCLUDEPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster
DEPENDPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LayoutEditor/release/ -lLayoutEditor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LayoutEditor/debug/ -lLayoutEditor
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../LayoutEditor/ -lLayoutEditor
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LayoutEditor/ -lLayoutEditord

INCLUDEPATH += $$PWD/../LayoutEditor
DEPENDPATH += $$PWD/../LayoutEditor


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPref/release/ -lPref
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPref/debug/ -lPref
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPref/ -lPref
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPref/ -lPrefd

INCLUDEPATH += $$PWD/../libPref
DEPENDPATH += $$PWD/../libPref


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Tables/release/ -lTables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Tables/debug/ -lTables
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../Tables/ -lTables
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Tables/ -lTablesd

INCLUDEPATH += $$PWD/../Tables
DEPENDPATH += $$PWD/../Tables

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LocoIO/release/ -lLocoIO
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LocoIO/debug/ -lLocoIO
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../LocoIO/ -lLocoIO
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LocoIO/ -lLocoIOd

INCLUDEPATH += $$PWD/../LocoIO
DEPENDPATH += $$PWD/../LocoIO

win32:exists($$PREFIX/lib/PythonQt.dll){
 ENABLE_SCRIPTING = "Y"
}

#unix:exists($$PREFIX/lib/libPythonQt-Qt5-Python2.7_d.so){
# ENABLE_SCRIPTING = "Y"
# message(PanelPro: $$PREFIX/lib/libPythonQt-Qt5-Python2.7_d.so + "found OK")
#} else:unix: {
# message(PanelPro: $$PREFIX/lib/libPythonQt-Qt5-Python2.7_d.so + "not found")
#}

#CONFIG += scripts
equals(ENABLE_SCRIPTING, "Y") {
    DEFINES += SCRIPTING_ENABLED

    win32:CONFIG(debug, debug|release): LIBS += -L$$PREFIX/lib/ -lPythonQt -lPythonQt_QtAll
    else:unix: LIBS += -L$$PYTHONQT_PREFIX/lib/ -lPythonQt-Qt5-Python$${PYTHON_VERSION}_d -lPythonQt_QtAll-Qt5-Python$${PYTHON_VERSION}_d

    INCLUDEPATH += $$PYTHONQT_PREFIX/src $$PYTHONQT_PREFIX/extensions/PythonQt_QtAll
    DEPENDPATH +=  $$PYTHONQT_PREFIX/src $$PYTHONQT_PREFIX/extensions/PythonQt_QtAll

 include(../python.prf)
 message(DecoderPro3: python scripts are enabled)

}
else {
 message(DecoderPro3: Python scripts will be disabled)
}

TRANSLATIONS += \
    languages/decoderpro3_de.ts \
    languages/decoderpro3_en.ts

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/release/ -lJavaQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/debug/ -lJavaQt
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/ -lJavaQt
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/ -lJavaQtd

INCLUDEPATH += $$PWD/../JavaQt
DEPENDPATH += $$PWD/../JavaQt

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../operations/release/ -loperations
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../operations/debug/ -loperations
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../operations/ -loperations
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../operations/ -loperationsd

INCLUDEPATH += $$PWD/../operations
DEPENDPATH += $$PWD/../operations


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../tests/release/ -ltests
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../tests/debug/ -ltests
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../tests/ -ltests
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../tests/ -ltestsd

INCLUDEPATH += $$PWD/../tests
DEPENDPATH += $$PWD/../tests
