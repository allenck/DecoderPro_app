#-------------------------------------------------
#
# Project created by QtCreator 2013-08-05T14:16:21
#
#-------------------------------------------------

QT       -= gui

TARGET = ftdilib
TEMPLATE = lib

MOC_DIR = moc_obj
OBJECTS_DIR += moc_obj

DEFINES += FTDILIB_LIBRARY

SOURCES += ftdilib.cpp \
    ftdithread.cpp

HEADERS += ftdilib.h\
    ftdilib_global.h \
    ftdithread.h \
    WinTypes.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE22394ED
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = ftdilib.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}



unix:!macx:!symbian: LIBS += -lftd2xx

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/win32/ -lftd2xx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/win32/ -lftd2xx


INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
