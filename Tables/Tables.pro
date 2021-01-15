#-------------------------------------------------
#
# Project created by QtCreator 2013-10-12T15:05:56
#
#-------------------------------------------------

QT       += gui core widgets xml network

TARGET = Tables
TEMPLATE = lib

DEFINES += LIBTABLES_LIBRARY

MOC_DIR = moc_obj

OBJECTS_DIR += moc_obj

SOURCES +=  slotmonitor.cpp \
    beanselectcreatepanel.cpp \
    jmribeancombobox.cpp \
    dialogsignalgroupstablewidget.cpp \
    logixtableaction.cpp \
    #defaultconditionalaction.cpp \
    pickframe.cpp \
    lroutetableaction.cpp \
    sectiontableaction.cpp \
    signalheadtableaction.cpp \
    signallingsourcepanel.cpp \
    signallingsourceframe.cpp \
    signallingsourceaction.cpp \
    signallingaction.cpp \
    signallingframe.cpp \
    signallingpanel.cpp \
    signalgrouptableaction.cpp \
    signalgroupsubtableaction.cpp \
    addnewhardwaredevicepanel.cpp \
    sensortableaction.cpp \
    slotmondatamodel.cpp \
    abstracttableaction.cpp \
    turnouttableaction.cpp \
    abstracttabletabaction.cpp \
    turnouttabletabaction.cpp \
    turnouteditaction.cpp \
    beaneditaction.cpp \
    beanitempanel.cpp \
    beanedititem.cpp \
    audiotableaction.cpp \
    audiosourceframe.cpp \
    abstractaudioframe.cpp \
    audiobufferframe.cpp \
    audiolistenerframe.cpp \
    audiotablepanel.cpp \
    audiotableframe.cpp \
    blocktableaction.cpp \
    addnewbeanpanel.cpp \
    trackertableaction.cpp \
    tracker.cpp \
    oblocktableaction.cpp \
    tableframes.cpp \
    oblocktablemodel.cpp \
    blockportaltablemodel.cpp \
    signaltablemodel.cpp \
    jinternalframe.cpp \
    jdesktoppane.cpp \
    portaltablemodel.cpp \
    blockpathtablemodel.cpp \
    internalframeevent.cpp \
    pathturnouttablemodel.cpp \
    blockeditaction.cpp \
    sensordebounceeditaction.cpp \
    sensortabletabaction.cpp \
    lighttabletabaction.cpp \
    lighttableaction.cpp \
    routetableaction.cpp \
    listedtableframe.cpp \
    listedtableaction.cpp \
    signalmasttableaction.cpp \
    signalmastrepeaterjframe.cpp \
    signalmastrepeaterpanel.cpp \
    signalmasttabledatamodel.cpp \
    addsignalmastjframe.cpp \
    reportertableaction.cpp \
    memorytableaction.cpp \
    idtagtableaction.cpp \
    signalmastlogictableaction.cpp \
    transittableaction.cpp \
    transitsectionaction.cpp \
    conditionaltreeedit.cpp \
    conditionaleditbase.cpp \
    conditionallistedit.cpp \
    picksinglepanel.cpp \
    addnewdevicepanel.cpp \
    oblocktableframe.cpp \
    oblocktablepanel.cpp \
    portaleditframe.cpp \
    signaleditframe.cpp \
    oblockeditaction.cpp \
    blockpatheditframe.cpp \
    sensoreditaction.cpp \
    routetabledatamodel.cpp \
    routeeditframe.cpp \
    abstractrouteaddeditframe.cpp \
    routeturnout.cpp \
    routesensor.cpp \
    routeelement.cpp \
    routesensormodel.cpp \
    routeturnoutmodel.cpp \
    routeaddframe.cpp \
    routeoutputmodel.cpp \
    routeexporttologix.cpp

HEADERS += libtables_global.h \
    slotmonitor.h \
    beanselectcreatepanel.h \
    jmribeancombobox.h \
    dialogsignalgroupstablewidget.h \
    routetableaction.h \
    logixtableaction.h \
    #defaultconditionalaction.h \
    pickframe.h \
    lroutetableaction.h \
    signalheadtableaction.h \
    signallingsourcepanel.h \
    signallingsourceframe.h \
    signallingsourceaction.h \
    signallingaction.h \
    signallingframe.h \
    signalgrouptableaction.h \
    sectiontableaction.h \
    signalgroupsubtableaction.h \
    addnewhardwaredevicepanel.h \
    sensortableaction.h \
    slotmondatamodel.h \
    abstracttableaction.h \
    turnouttableaction.h \
    abstracttabletabaction.h \
    turnouttabletabaction.h \
    turnouteditaction.h \
    beaneditaction.h \
    beanitempanel.h \
    beanedititem.h \
    audiotableaction.h \
    audiosourceframe.h \
    abstractaudioframe.h \
    audiobufferframe.h \
    audiolistenerframe.h \
    audiotablepanel.h \
    audiotableframe.h \
    blocktableaction.h \
    addnewbeanpanel.h \
    trackertableaction.h \
    tracker.h \
    oblocktableaction.h \
    tableframes.h \
    oblocktablemodel.h \
    blockportaltablemodel.h \
    signaltablemodel.h \
    jinternalframe.h \
    jdesktoppane.h \
    portaltablemodel.h \
    internalframelistener.h \
    blockpathtablemodel.h \
    pathturnouttablemodel.h \
    internalframeevent.h \
    blockeditaction.h \
    sensordebounceeditaction.h \
    listedtableframe.h \
    sensortabletabaction.h \
    lighttabletabaction.h \
    lighttableaction.h \
    listedtableaction.h \
    signalmasttableaction.h \
    signalmastrepeaterjframe.h \
    signalmastrepeaterpanel.h \
    signalmasttabledatamodel.h \
    addsignalmastjframe.h \
    reportertableaction.h \
    memorytableaction.h \
    idtagtableaction.h \
    signalmastlogictableaction.h \
    transittableaction.h \
    transitsectionaction.h \
    conditionaltreeedit.h \
    conditionaleditbase.h \
    conditionallistedit.h \
    signallingpanel.h \
    picksinglepanel.h \
    addnewdevicepanel.h \
    oblocktableframe.h \
    oblocktablepanel.h \
    portaleditframe.h \
    signaleditframe.h \
    oblockeditaction.h \
    blockpatheditframe.h \
    sensoreditaction.h \
    routetabledatamodel.h \
    routeeditframe.h \
    abstractrouteaddeditframe.h \
    routeturnout.h \
    routesensor.h \
    routeelement.h \
    routesensormodel.h \
    routeturnoutmodel.h \
    routeaddframe.h \
    routeoutputmodel.h \
    routeexporttologix.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    #turnoutwidget.ui \
    #turnouttablewidget.ui \
    #sensorwidget.ui \
    #sensortablewidget.ui \
#    reporterwidget.ui \
#    memorywidget.ui \
#    blockwidget.ui \
#    idtagswidget.ui \
#    addeditdialog.ui \
#    routewidget.ui \
#    lightwidget.ui \
#    lighttablewidget.ui \
#    addeditlightdialog.ui \
#    addeditlightcontroldialog.ui \
    slotmonitor.ui \
#    signalheadwidget.ui \
    dialogsignalgroupstablewidget.ui \
#    signalmastwidget.ui \
#    signalmastlogicwidget.ui \
#    signalgroupswidget.ui \
    routetableaction.ui \
#    lroutewidget.ui \
#    logixwidget.ui \
#    sectionwidget.ui \
#    transitwidget.ui \
    editconditionalframe.ui
#    addeditlightdialog1.ui \
#    audiowidget.ui \
#    tablesframe.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3/release/ -lPr3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3/debug/ -lPr3
else:unix:!macx: LIBS += -L$$PWD/../libPr3/ -lPr3

INCLUDEPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/Signal $$PWD/../LayoutEditor/ $$PWD/../appslib/operations
DEPENDPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/Signal $$PWD/../LayoutEditor/  $$PWD/../appslib/operations

TRANSLATIONS += \
    languages/libTables_de.ts \
    languages/libTables_en.ts

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/release/ -lJavaQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/debug/ -lJavaQt
else:unix: LIBS += -L$$PWD/../JavaQt/ -lJavaQt

INCLUDEPATH += $$PWD/../JavaQt
DEPENDPATH += $$PWD/../JavaQt

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LayoutEditor/release/ -lLayoutEditor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LayoutEditor/debug/ -lLayoutEditor

INCLUDEPATH += $$PWD/../LayoutEditor/debug
DEPENDPATH += $$PWD/../LayoutEditor/debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/release/ -lappslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/debug/ -lappslib
else:unix: LIBS += -L$$PWD/../appslib/ -lappslib

INCLUDEPATH += $$PWD/../appslib $$PWD/../appslib
DEPENDPATH += $$PWD/../appslib $$PWD/../appslib
