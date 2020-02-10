#-------------------------------------------------
#
# Project created by QtCreator 2015-08-17T13:08:36
#
#-------------------------------------------------
greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport gui #webkitwidgets
}
QT       += xml sql network

TARGET = LocoIO
TEMPLATE = lib

DEFINES += LOCOIO_LIBRARY

MOC_DIR = moc_obj
OBJECTS_DIR += moc_obj

SOURCES += locoiodialog.cpp \
    locoio.cpp \
    locoiodata.cpp \
    locoiomode.cpp \
    locoiomodelist.cpp \
    locoioaddress.cpp \
    locoiomodules.cpp \
    inputwidget.cpp \
    outputwidget.cpp \
    registerswidget.cpp \
    inportdefinitionwidget.cpp \
    outportdefinitionwidget.cpp \
    addressportdefinitionwidget.cpp \
    extraopcodewidget.cpp \
    extraopcodedefinitionwidget.cpp \
    servowidget.cpp \
    servoregisterswidget.cpp \
    boosterinputwidget.cpp \
    boosteroutputwidget.cpp \
    boosterpanel.cpp \
    saverestoredialog.cpp \
    specialport.cpp  \
    commentsdialog.cpp \
    sql.cpp \
    turnoutdlg.cpp \
    locoiotablemodel.cpp \
    locoiopanel.cpp \
    locoioframe.cpp \
    addressvalidator.cpp \
    booster7widget.cpp \
    boosterbuttons.cpp



HEADERS += locoio_global.h \
    locoio.h \
    locoiodata.h \
    locoiomode.h \
    locoiomodelist.h \
    locoioaddress.h \
    locoiodialog.h \
    locoiomodules.h \
    inputwidget.h \
    outputwidget.h \
    registerswidget.h \
    inportdefinitionwidget.h \
    outportdefinitionwidget.h \
    addressportdefinitionwidget.h \
    extraopcodewidget.h \
    extraopcodedefinitionwidget.h \
    servowidget.h \
    servoregisterswidget.h \
    boosterinputwidget.h \
    boosteroutputwidget.h \
    boosterpanel.h \
    saverestoredialog.h \
    specialport.h \
    commentsdialog.h \
    sql.h \
    turnoutdlg.h \
    locoiodialog.h \
    locoiotablemodel.h \
    locoiopanel.h \
    locoioframe.h \
    addressvalidator.h \
    booster7widget.h \
    boosterbuttons.h


unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    locoiodialog.ui \
    inputwidget.ui \
    outputwidget.ui \
    registerswidget.ui \
    inportdefinitionwidget.ui \
    outportdefinitionwidget.ui \
    addressportdefinitionwidget.ui \
    extraopcodewidget.ui \
    extraopcodedefinitionwidget.ui \
    servowidget.ui \
    servoregisterswidget.ui \
    boosterpanel.ui \
    boosterinputwidget.ui \
    boosteroutputwidget.ui \
    saverestoredialog.ui \
    specialport.ui \
    commentsdialog.ui \
    turnoutdlg.ui \
    locoioframe.ui \
    booster7widget.ui \
    boosterbuttons.ui



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3/release/ -lPr3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3/debug/ -lPr3
#else:unix: LIBS += -L$$PWD/../libPr3/ -lPr3

INCLUDEPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/loconet
DEPENDPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster  $$PWD/../libPr3/loconet


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

TRANSLATIONS += \
    languages/libLocoIO_de.ts \
    languages/libLocoIO_en.ts

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/release/ -lJavaQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/debug/ -lJavaQt
else:unix: LIBS += -L$$PWD/../JavaQt/ -lJavaQt

INCLUDEPATH += $$PWD/../JavaQt
DEPENDPATH += $$PWD/../JavaQt

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/release/ -lappslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/debug/ -lappslib
else:unix: LIBS += -L$$PWD/../appslib/ -lappslib

INCLUDEPATH += $$PWD/../appslib $$PWD/../appslib/operations
DEPENDPATH += $$PWD/../appslib $$PWD/../appslib/operations
