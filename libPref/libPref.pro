#-------------------------------------------------
#
# Project created by QtCreator 2015-02-25T08:06:19
#
#-------------------------------------------------

QT       += widgets xml gui network

TARGET = Pref
TEMPLATE = lib

DEFINES += LIBPREF_LIBRARY

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

SOURCES += libpref.cpp \
    tabbedpreferencesframe.cpp \
    tabbedpreferences.cpp \
    tabbedpreferencesaction.cpp \
    tabbedpreferencesprofileaction.cpp \
    usermessagepreferencespane.cpp \
    programmerconfigpane.cpp \
    performfilepanel.cpp \
    performfilemodel.cpp \
    performactionmodel.cpp \
    rosterconfigpane.cpp \
    managerdefaultsconfigpanexml.cpp \
    managerdefaultsconfigpane.cpp \
    guilocalepreferencespanel.cpp \
    guilafconfigpane.cpp \
    abstractactionmodel.cpp \
    filelocationpane.cpp \
    jmrixconfigpane.cpp \
    throttlespreferencespane.cpp \
    throttlespreferences.cpp \
    throttlespreferencesaction.cpp \
    filelocationpanexml.cpp \
    programmerconfigpanexml.cpp \
    guilafconfigpanexml.cpp \
    railroadnamepreferencespanel.cpp \
    profilepreferencespanel.cpp \
    profiletablemodel.cpp \
    profilefileview.cpp \
    fileview.cpp \
    profilefilefilter.cpp \
    profilemanagerdialog.cpp \
    profilelistmodel.cpp \
    performscriptpanel.cpp \
    warrantpreferencespanel.cpp \
    performfilepanelxml.cpp \
    performscriptpanelxml.cpp \
    connectionspreferencespanel.cpp \
    warrantpreferences.cpp \
    warrantroute.cpp \
    nxframe.cpp \
    jmrixconfigpanexml.cpp \
    routefinder.cpp \
    webserverpreferences.cpp \
    webserverpreferencespanel.cpp \
    startupactionspreferencespanel.cpp \
    speedutil.cpp \
    rampdata.cpp


HEADERS += libpref.h\
        libpref_global.h \
    tabbedpreferences.h \
    tabbedpreferencesframe.h \
    tabbedpreferencesaction.h \
    tabbedpreferencesprofileaction.h \
    usermessagepreferencespane.h \
#    appconfigbase.h \
    preferencessubpanel.h \
    preferencespanel.h \
    programmerconfigpane.h \
    performfilepanel.h \
    performfilemodel.h \
    performactionmodel.h \
    managerdefaultsconfigpanexml.h \
    managerdefaultsconfigpane.h \
    abstractactionmodel.h \
    guilocalepreferencespanel.h \
    guilafconfigpane.h \
    filelocationpane.h \
    jmrixconfigpane.h \
    throttlespreferencespane.h \
    throttlespreferences.h \
    throttlespreferencesaction.h \
    rosterconfigpane.h \
    filelocationpanexml.h \
#    appsbase.h \
    programmerconfigpanexml.h \
    guilafconfigpanexml.h \
    railroadnamepreferencespanel.h \
    profilepreferencespanel.h \
    profiletablemodel.h \
    profilefileview.h \
    fileview.h \
    profilefilefilter.h \
    profilemanagerdialog.h \
    profilelistmodel.h \
    performscriptpanel.h \
    warrantpreferencespanel.h \
    performfilepanelxml.h \
    performscriptpanelxml.h \
    connectionspreferencespanel.h \
    managingpreferencespanel.h \
    warrantpreferences.h \
    warrantroute.h \
    nxframe.h \
    jmrixconfigpanexml.h \
    routefinder.h \
    webserverpreferences.h \
    webserverpreferencespanel.h \
    startupactionspreferencespanel.h \
    speedutil.h \
    rampdata.h


unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

TRANSLATIONS += \
    languages/libPref_de.ts \
    languages/libPref_en.ts

INCLUDEPATH += ../libPr3 ../LayoutEditor
INCLUDEPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/Throttle $$PWD/../libPr3/Signal
DEPENDPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/Throttle $$PWD/../libPr3/Signal

INCLUDEPATH += $$PWD/../ftdilib
DEPENDPATH += $$PWD/../ftdilib

INCLUDEPATH += $$PWD/../Tables
DEPENDPATH += $$PWD/../Tables

#INCLUDEPATH += $$PWD/../LocoNetMonitor
#DEPENDPATH += $$PWD/../LocoNetMonitor


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3/release/ -lPr3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3/debug/ -lPr3
else:unix:!macx:!symbian:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3/ -lPr3
else:unix:!macx:!symbian:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3/ -lPr3d


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/release/ -lappslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/debug/ -lappslib
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/ -lappslib
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/ -lappslibd


INCLUDEPATH += $$PWD/../appslib
DEPENDPATH += $$PWD/../appslib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/release/ -lJavaQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/debug/ -lJavaQt
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/ -lJavaQt
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/ -lJavaQtd


INCLUDEPATH += $$PWD/../JavaQt
DEPENDPATH += $$PWD/../JavaQt


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LayoutEditor/release/ -lLayoutEditor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LayoutEditor/debug/ -lLayoutEditor
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../LayoutEditor/ -lLayoutEditor
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LayoutEditor/ -lLayoutEditord


INCLUDEPATH += $$PWD/../LayoutEditor
DEPENDPATH += $$PWD/../LayoutEditor


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Tables/release/ -lTables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Tables/debug/ -lTables
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../Tables/ -lTables
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Tables/ -lTablesd


INCLUDEPATH += $$PWD/../Tables
DEPENDPATH += $$PWD/../Tables


