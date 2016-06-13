#-------------------------------------------------
#
# Project created by QtCreator 2015-08-23T00:11:05
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DecoderPro3
TEMPLATE = app


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


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/release/ -lappslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/debug/ -lappslib
else:unix: LIBS += -L$$PWD/../appslib/ -lappslib

INCLUDEPATH += $$PWD/../appslib
DEPENDPATH += $$PWD/../appslib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3/release/ -lPr3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3/debug/ -lPr3
else:unix: LIBS += -L$$PWD/../libPr3/ -lPr3

INCLUDEPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster
DEPENDPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster



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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../PythonQt3.0/lib/release/ -lPythonQt_QtAll_d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../PythonQt3.0/lib/debug/ -lPythonQt_QtAll_d
else:unix: LIBS += -L$$PWD/../../../../PythonQt3.0/lib/ -lPythonQt_QtAll_d

INCLUDEPATH += $$PWD/../../../../PythonQt3.0/src
DEPENDPATH += $$PWD/../../../../PythonQt3.0/src



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lpython2.7
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lpython2.7
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lpython2.7

INCLUDEPATH += /usr/include/python2.7/
DEPENDPATH += /usr/include/python2.7/

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../PythonQt3.0/lib/release/ -lPythonQt_d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../PythonQt3.0/lib/debug/ -lPythonQt_d
else:unix: LIBS += -L$$PWD/../../../../PythonQt3.0/lib/ -lPythonQt_d

INCLUDEPATH += $$PWD/../../../../PythonQt3.0/extensions/PythonQt_QtAll
DEPENDPATH += $$PWD/../../../../PythonQt3.0/extensions/PythonQt_QtAll

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/Trolltech/Qt-4.8.3/plugins/designer/release/ -lpyqt4
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/Trolltech/Qt-4.8.3/plugins/designer/debug/ -lpyqt4
else:unix: LIBS += -L$$PWD/../../../../../../../usr/local/Trolltech/Qt-4.8.3/plugins/designer/ -lpyqt4

INCLUDEPATH += $$PWD/../../../../../../../usr/local/Trolltech/Qt-4.8.3/plugins/designer
DEPENDPATH += $$PWD/../../../../../../../usr/local/Trolltech/Qt-4.8.3/plugins/designer


TRANSLATIONS += \
    languages/decoderpro3_de.ts \
    languages/decoderpro3_en.ts

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/release/ -lJavaQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/debug/ -lJavaQt
else:unix: LIBS += -L$$PWD/../JavaQt/ -lJavaQt

INCLUDEPATH += $$PWD/../JavaQt
DEPENDPATH += $$PWD/../JavaQt
