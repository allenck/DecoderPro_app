#-------------------------------------------------
#
# Project created by QtCreator 2010-08-26T14:47:03
#
#-------------------------------------------------

QT       += core
QT       -= gui

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TARGET = AutoIncreaseBuildNr
TEMPLATE = app

CONFIG   += console
CONFIG   -= app_bundle
CONFIG += stl warn_on qt

static { # everything below takes effect with CONFIG += static
    CONFIG += static staticlib
    DEFINES += STATIC
    message("~~~ static build ~~~")
    unix: TARGET = $$join(TARGET,,,s)
    mac: TARGET = $$join(TARGET,,,_static)
    win32: TARGET = $$join(TARGET,,,s)
    CONFIG -= debug
    CONFIG += release static
}
else {
    CONFIG += debug_and_release build_all
}

SOURCES += main.cpp

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# change the nama of the binary, if it is build in debug mode
CONFIG(debug, debug|release) {
     unix: TARGET = $$join(TARGET,,,d)
     mac: TARGET = $$join(TARGET,,,_debug)
     win32: TARGET = $$join(TARGET,,,d)
}

#define the directory, where the binary is placed
CONFIG(debug, debug|release) {
    DESTDIR = ../debug
}
else {
    DESTDIR = ../release
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
VERSION = 01.00.00
