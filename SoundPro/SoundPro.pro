APPNAME = "SoundPro"
APPVERSION = 0.1
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SoundPro
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

CONFIG += c++11

PROJ_DIR=$$(PROJ_DIR) # get project directory from env
isEmpty( PROJ_DIR ) {
  win32:PROJ_DIR=C:/Projects
  unix:PROJ_DIR=/home/allen/Projects
}
include(../scripts_config.prf)
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    #main.cpp \
    main.cpp \
    soundpro.cpp

HEADERS += \
    soundpro.h

TRANSLATIONS += \
    SoundPro_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/release/ -lJavaQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/debug/ -lJavaQt
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/ -lJavaQt
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/ -lJavaQtd


INCLUDEPATH += $$PWD/../JavaQt
DEPENDPATH += $$PWD/../JavaQt

include(../jmri_libs.prf)

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/release/ -lappslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/debug/ -lappslib
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/ -lappslib
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/ -lappslibd


INCLUDEPATH += $$PWD/../appslib/
#DEPENDPATH += $$PWD/../appslib/

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3/release/ -lPr3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3/debug/ -lPr3
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3 -lPr3
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3 -lPr3d

INCLUDEPATH += $$PWD/../libPr3
DEPENDPATH += $$PWD/../libPr3

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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../QtWebApp/QtWebApp/ -lQtWebAppd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../QtWebApp/QtWebApp/ -lQtWebAppdd
else:unix: LIBS += -L$$PWD/../../../../QtWebApp/QtWebApp/ -lQtWebAppd

INCLUDEPATH += $$PWD/../../../../QtWebApp/QtWebApp
DEPENDPATH += $$PWD/../../../../QtWebApp/QtWebApp
