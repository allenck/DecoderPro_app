#-------------------------------------------------
#
# Project created by QtCreator 2015-08-17T16:58:43
#
#-------------------------------------------------

QT       += core
greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport gui webkitwidgets
} else {
QT       += gui
}
TARGET = PanelPro
TEMPLATE = app


unix:PREFIX = /usr/local

SOURCES += \
    main.cpp \
    panelpro.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/release/ -lJavaQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/debug/ -lJavaQt
else:unix: LIBS += -L$$PWD/../JavaQt/ -lJavaQt

INCLUDEPATH += $$PWD/../JavaQt
DEPENDPATH += $$PWD/../JavaQt


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/release/ -lappslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/debug/ -lappslib
else:unix: LIBS += -L$$PWD/../appslib/ -lappslib

INCLUDEPATH += $$PWD/../appslib
DEPENDPATH += $$PWD/../appslib

HEADERS += \
    panelpro.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3/release/ -lPr3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3/debug/ -lPr3
else:unix: LIBS += -L$$PWD/../libPr3/ -lPr3

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

unix:exists($$PREFIX/lib/libPythonQt.so){
 ENABLE_SCRIPTING = "Y"
}
#CONFIG += scripts
equals(ENABLE_SCRIPTING, "Y") {
    DEFINES += SCRIPTING_ENABLED

    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/lib/release/ -lPythonQt_d
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/lib/debug/ -lPythonQt_d
    else:unix: LIBS += -L/usr/local/lib/ -lPythonQt -lPythonQt_QtAll

    INCLUDEPATH += $$PREFIX/include/PythonQt
    DEPENDPATH += $$PREFIX/include/Python

#    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../PythonQt3.0/lib/release/ -lPythonQt_d
#    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../PythonQt3.0/lib/ -lPythonQt
#    else:unix: LIBS += -L$$PWD/../../../../PythonQt3.0/lib/ -lPythonQt_d

#    INCLUDEPATH += $$PWD/../../../../PythonQt3.0/extensions/PythonQt_QtAll
#    DEPENDPATH += $$PWD/../../../../PythonQt3.0/extensions/PythonQt_QtAll
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
