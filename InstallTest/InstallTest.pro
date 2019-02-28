#-------------------------------------------------
#
# Project created by QtCreator 2017-10-31T17:33:50
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InstallTest
TEMPLATE = app

MOC_DIR = moc_obj
OBJECTS_DIR += moc_obj

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    installtest.cpp

HEADERS  += \
    installtest.h

FORMS    +=

PYTHONQT_PREFIX=$$(PYTHONQT_PREFIX)
isEmpty( PYTHONQT_PREFIX ) {
  win32:PYTHONQT_PREFIX=C:/Program Files (x86)/local/lib
  unix:PYTHONQT_PREFIX=/home/allen/Projects/PythonQt/pythonqt-code
}

include($$PYTHONQT_PREFIX/build/python.prf)

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

win32:exists($$PYTHONQT_PREFIX/lib/PythonQt.dll){
 ENABLE_SCRIPTING = "Y"
 message(InstallTest: $$PYTHONQT_PREFIX/lib/PythonQt.dll + "exists")
} else:win32: {
 message(InstallTest: $$PYTHONQT_PREFIX/lib/PythonQt.dll + "not found")
}

unix:exists($$PYTHONQT_PREFIX/lib/libPythonQt-Qt5-Python$${PYTHON_VERSION}_d.so){
 ENABLE_SCRIPTING = "Y"
 message(InstallTest: $$PYTHONQT_PREFIX/lib/libPythonQt-Qt5-Python$${PYTHON_VERSION}_d.so + "found OK")
} else:unix: {
 message(InstallTest: $$PREFIX/lib/libPythonQt-Qt5-Python$${PYTHON_VERSION}_d.so + "not found")
}
CONFIG += scripts
equals(ENABLE_SCRIPTING, "Y") {
    DEFINES += SCRIPTING_ENABLED

    win32:CONFIG(debug, debug|release): LIBS += -L$$PYTHONQT_PREFIX/lib/ -lPythonQt -lPythonQt_QtAll
    else:unix: LIBS += -L$$PYTHONQT_PREFIX/lib/ -lPythonQt-Qt5-Python$${PYTHON_VERSION}_d -lPythonQt_QtAll-Qt5-Python$${PYTHON_VERSION}_d

    INCLUDEPATH += $$PYTHONQT_PREFIX/src $$PYTHONQT_PREFIX/extensions/PythonQt_QtAll
    DEPENDPATH += $$PYTHONQT_PREFIXe/src $$PYTHONQT_PREFIX/extensions/PythonQt_QtAll
#    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../PythonQt3.0/lib/release/ -lPythonQt_d

 #include(../python.prf)
 message(InstallTest: python scripts are enabled)

}
else {
 message(InstallTest::Python scripts will be disabled)
}
