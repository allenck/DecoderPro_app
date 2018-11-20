#-------------------------------------------------
#
# Project created by QtCreator 2015-08-17T16:58:43
#
#-------------------------------------------------
APPNAME = "PanelPro"
APPVERSION = 0.1

QT += widgets

TARGET = PanelPro
TEMPLATE = app


unix:PREFIX = /home/allen/Projects/PythonQt-master
win32:PREFIX = "C:/Program Files (x86)/local"

SOURCES += \
    main.cpp \
    panelpro.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/release/ -lJavaQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/debug/ -lJavaQt
else:unix: LIBS += -L$$PWD/../JavaQt/ -lJavaQt

INCLUDEPATH += $$PWD/../JavaQt
DEPENDPATH += $$PWD/../JavaQt

include(../jmri_libs.prf)


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/release/ -lappslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/debug/ -lappslib
else:unix: LIBS += -L$$PWD/../appslib/ -lappslib

INCLUDEPATH += $$PWD/../appslib
DEPENDPATH += $$PWD/../appslib

HEADERS += \
    panelpro.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3/release/ -lPr3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3/debug/ -lPr3
else:unix: LIBS += -L$$PWD/../libPr3 -lPr3

INCLUDEPATH += $$PWD/../libPr3
DEPENDPATH += $$PWD/../libPr3


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LayoutEditor/release/ -lLayoutEditor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LayoutEditor/debug/ -lLayoutEditor
else:unix: LIBS += -L$$PWD/../LayoutEditor/ -lLayoutEditor

INCLUDEPATH += $$PWD/../LayoutEditor
DEPENDPATH += $$PWD/../LayoutEditor


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPref/release/ -lPref
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPref/debug/ -lPref
else:unix: LIBS += -L$$PWD/../libPref/ -lPref

INCLUDEPATH += $$PWD/../libPref
DEPENDPATH += $$PWD/../libPref


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Tables/release/ -lTables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Tables/debug/ -lTables
else:unix: LIBS += -L$$PWD/../Tables/ -lTables

INCLUDEPATH += $$PWD/../Tables
DEPENDPATH += $$PWD/../Tables

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LocoIO/release/ -lLocoIO
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LocoIO/debug/ -lLocoIO
else:unix: LIBS += -L$$PWD/../LocoIO/ -lLocoIO

INCLUDEPATH += $$PWD/../LocoIO
DEPENDPATH += $$PWD/../LocoIO

win32:exists($$PREFIX/lib/PythonQt.dll){
 ENABLE_SCRIPTING = "Y"
 message($$PREFIX/lib/PythonQt.dll + "exists")
} else:win32: {
 message($$PREFIX/lib/PythonQt.dll + "not found")
}

unix:exists($$PREFIX/lib/libPythonQt_d.so){
 ENABLE_SCRIPTING = "Y"
} else:unix: {
 message($$PREFIX/lib/libPythonQt.so_d + "not found")
}
CONFIG += scripts
equals(ENABLE_SCRIPTING, "Y") {
    DEFINES += SCRIPTING_ENABLED

    win32:CONFIG(debug, debug|release): LIBS += -L$$PREFIX/lib/ -lPythonQt -lPythonQt_QtAll
    else:unix: LIBS += -L$$PREFIX/lib/ -lPythonQt_d -lPythonQt_QtAll_d

    INCLUDEPATH += /usr/local/include/PythonQt
    DEPENDPATH += /usr/local/include/PythonQt
#    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../PythonQt3.0/lib/release/ -lPythonQt_d

 include(../python.prf)
 message(PanelPro: python scripts are enabled)

}
else {
 message(PanelPro::Python scripts will be disabled)
}

TRANSLATIONS += \
    languages/panelpro_de.ts \
    languages/panelpro_en.ts




#win32: LIBS += -lpython27

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../Python27/libs/ -lpython27
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../Python27/libs/ -lpython27

INCLUDEPATH += $$PWD/../../../../../Python27/include
DEPENDPATH += $$PWD/../../../../../Python27/include
