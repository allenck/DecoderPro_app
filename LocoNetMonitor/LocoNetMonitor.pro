unix:{
QTSERIALPORT_PROJECT_ROOT = /home/allen/Projects/qtserialport
}
win32:{
QTSERIALPORT_PROJECT_ROOT =C:/Users/Allen/Projects/qt-qtserialport-stable/qt-qtserialport
}
greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport gui webkitwidgets
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}
APPNAME = "LocoNetMonitor"
APPVERSION = 0.1

QT += core gui xml sql
CONFIG += serialport
TARGET = loconetmonitor
TEMPLATE = app

unix{
 isEmpty(PREFIX): PREFIX_USR = /usr
 isEmpty(PREFIX): PREFIX_LOCAL = $${PREFIX_USR}/local
 isEmpty(INSTALL_DIR): INSTALL_DIR = $${PREFIX_LOCAL}/bin
 exists($$PWD/../ftdilib/libftdilib.so) {
 DEFINES += HAVE_FTDI
  message("ftdilib.dll found!")
 isEmpty(FTDI): FTDI = 1
 }
}
win32{
 isEmpty(PREFIX): PREFIX_USR = "C:/"
 isEmpty(PREFIX): PREFIX_LOCAL = $${PREFIX_USR}QGeomColl
 isEmpty(PREFIX): PREFIX_LOCAL = C:/$${APPNAME}
 isEmpty(INSTALL_DIR): INSTALL_DIR = $${PREFIX_LOCAL}
 exists($$PWD/../ftdilib/debug/ftdilib.dll) {
  isEmpty(FTDI): FTDI = 1
  DEFINES += HAVE_FTDI
  message("ftdilib.dll found!")
 }
}

INCLUDEPATH += ../libPr3 ../LayoutEditor

isEmpty(EXTENDED_FUNCTIONS): EXTENDED_FUNCTIONS=1 #1 to enable additional functions

#build_nr.commands = $$PWD/build_number.sh
build_nr.commands = $$PWD/../release/AutoIncreaseBuildNr $$PWD/build_number.h
#build_nr.depends = FORCE
QMAKE_EXTRA_TARGETS += build_nr
PRE_TARGETDEPS += build_nr

HEADERS += \
    dialog.h \
    mainwindow.h \
    build_number.h \
    aboutdialog.h \
    ObjectViewer/objectviewerdialog.h \
    ObjectViewer/ovtablemodel.h


SOURCES += \
    main.cpp \
    dialog.cpp \
    mainwindow.cpp \
    aboutdialog.cpp \
    ObjectViewer/objectviewerdialog.cpp \
    ObjectViewer/ovtablemodel.cpp

contains(EXTENDED_FUNCTIONS, 1) {
DEFINES += EXTENDED=1
HEADERS += \

}

FORMS += \
    mainwindow.ui \
    aboutdialog.ui \
    ObjectViewer/objectviewerdialog.ui


DEFINES += BLOCKS_AND_SECTIONS
DEFINES += LOCONETMONITOR

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3/release/ -lPr3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3/debug/ -lPr3
else:unix:!macx:!symbian: LIBS += -L$$PWD/../libPr3/ -lPr3

INCLUDEPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/loconet
DEPENDPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/loconet
#unix:{
# files.files += $(QTDIR)/lib/QtCored4.so \
#    $(QTDIR)/lib/QtGuid4.so \
#    $(QTDIR)/lib/QtSeriald.so \
#    $$PWD/../libPr3/debug/libpr3.so
#}
win32:{
 files.files += $$QTDIR/lib/QtCored4.dll \
    $(QTDIR)\\lib\\QtGuid4.dll \
    $(QTDIR)\\lib\\QtSerialPort.dll \
    $$PWD/../libPr3/debug/Pr3.dll
}

unix:!symbian{
 maemo5{
  target.path = /opt$${INSTALL_DIR}
#  headers.path = /opt$${INCLUDES_INSTALL_DIR}
 }
 else{
  target.path = $${INSTALL_DIR}
  files.path = $${INSTALL_DIR}
#  headers.path = $${INCLUDES_INSTALL_DIR}
 }
 INSTALLS += target \
    files  #headers
}
win32:{
  target.path = $${INSTALL_DIR}
  files.path = $${INSTALL_DIR}
#  headers.path = $${INCLUDES_INSTALL_DIR}
 INSTALLS += target \
   files #headers
}

OTHER_FILES += \
    build_number.sh
TRANSLATIONS += \
    languages/loconetmonitor_de.ts \
    languages/loconetmonitor_en.ts \
    qt_de.ts

RESOURCES += \
    loconetmonitor.qrc \
    ../LayoutEditor/LayoutEditor.qrc

contains(FTDI, 1) {
 win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ftdilib/release/ -lftdilib
 else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ftdilib/debug/ -lftdilib
 else:unix:!macx: LIBS += -L$$PWD/../ftdilib/ -lftdilib

 INCLUDEPATH += $$PWD/../ftdilib
 DEPENDPATH += $$PWD/../ftdilib
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LayoutEditor/release/ -lLayoutEditor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LayoutEditor/debug/ -lLayoutEditor
else:unix: LIBS += -L$$PWD/../LayoutEditor/ -lLayoutEditor

INCLUDEPATH += $$PWD/../LayoutEditor
DEPENDPATH += $$PWD/../LayoutEditor


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Tables/release/ -lTables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Tables/debug/ -lTables
else:unix: LIBS += -L$$PWD/../Tables/ -lTables

INCLUDEPATH += $$PWD/../Tables
DEPENDPATH += $$PWD/../Tables

INCLUDEPATH += $$PWD/../libPref
DEPENDPATH += $$PWD/../libPref

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPref/release/ -lPref
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPref/debug/ -lPref
else:unix:!macx:!symbian: LIBS += -L$$PWD/../libPref/ -lPref


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


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/release/ -lappslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/debug/ -lappslib
else:unix: LIBS += -L$$PWD/../appslib/ -lappslib

INCLUDEPATH += $$PWD/../appslib
DEPENDPATH += $$PWD/../appslib



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LocoIO/release/ -lLocoIO
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LocoIO/debug/ -lLocoIO
else:unix: LIBS += -L$$PWD/../LocoIO/ -lLocoIO

INCLUDEPATH += $$PWD/../LocoIO
DEPENDPATH += $$PWD/../LocoIO

unix|win32: LIBS += -L$$PWD/../JavaQt/ -lJavaQt

INCLUDEPATH += $$PWD/../JavaQt
DEPENDPATH += $$PWD/../JavaQt
