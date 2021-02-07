#-------------------------------------------------
#
# Project created by QtCreator 2015-08-17T10:25:47
#
#-------------------------------------------------

TARGET = appslib
TEMPLATE = lib
greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport gui #webkitwidgets
}
QT += xml sql network websockets

MOC_DIR = moc_obj
OBJECTS_DIR += moc_obj

PROJ_DIR=$$(PROJ_DIR) # get project directory from env
isEmpty( PROJ_DIR ) {
  win32:PROJ_DIR=C:/Projects
  unix:PROJ_DIR=/home/allen/Projects
}


DEFINES += APPSLIB_LIBRARY

PYTHONQT_PREFIX=$$(PYTHONQT_PREFIX)
isEmpty( PYTHONQT_PREFIX ) {
  win32:PYTHONQT_PREFIX=C:/Program Files (x86)/local/lib
  unix:PYTHONQT_PREFIX=$${PROJ_DIR}/PythonQt/pythonqt-code
}

include($$PYTHONQT_PREFIX/build/python.prf)

win32:exists("C:/Program Files (x86)/local/lib/PythonQt.dll") {
 ENABLE_SCRIPTING = "Y"
}

unix:exists($$PYTHONQT_PREFIX/lib/libPythonQt-Qt5-Python$${PYTHON_VERSION}_d.so) {
 ENABLE_SCRIPTING = "Y"
 message(appslib: found $$PYTHONQT_PREFIX/lib/libPythonQt-Qt5-Python$${PYTHON_VERSION}_d.so)
} else {
 message(appslib: not found $$PYTHONQT_PREFIX/lib/libPythonQt-Qt5-Python$${PYTHON_VERSION}_d.so)
}
#CONFIG += scripts
equals(ENABLE_SCRIPTING, "Y") {
    DEFINES += SCRIPTING_ENABLED
 SOURCES += jynstrument.cpp \
    jynstrumentfactory.cpp


HEADERS += jynstrument.h \
    jynstrumentfactory.h

 message("Appslib: scripting enabled")
} else {
 message("Appslib: scripting disabled")
}

SOURCES += appslib.cpp \
    metatypes.cpp \
    instancemanager.cpp \
    apps.cpp \
    apps3.cpp \
    appsbase.cpp \
    defaultinstanceinitializer.cpp \
    jmripreferencesprovider.cpp \
    nodeidentity.cpp \
    properties.cpp \
    profilemanager.cpp \
    profile.cpp \
    fileutil.cpp \
    fileutilsupport.cpp \
    myapplication.cpp \
    createbuttonmodel.cpp \
    splashwindow.cpp \
    toolsmenu.cpp \
    jlist.cpp \
    powerpanelaction.cpp \
    simpleturnoutctrlaction.cpp \
    simpleclockaction.cpp \
    analogclockaction.cpp \
    nixieclockaction.cpp \
    consisttoolaction.cpp \
    lcdclockaction.cpp \
    dualdecodertoolaction.cpp \
    dualdecoderselectframe.cpp \
    dualdecoderselectpane.cpp \
    activesystemsmenu.cpp \
    systemconsole.cpp \
    systemconsoleconfigpanelxml.cpp \
    systemconsoleconfigpanel.cpp \
    systemconsoleaction.cpp \
    jmenuutil.cpp \
    guiutilbase.cpp \
    jtoolbarutil.cpp \
    appconfigbase.cpp \
    panelproaction.cpp \
    appslaunchframe.cpp \
    appslaunchpane.cpp \
    application.cpp \
    panelpropane.cpp \
    performscriptmodel.cpp \
    xml.cpp \
    printdecoderlistaction.cpp \
    debugmenu.cpp \
    vsdecodercreationaction.cpp \
    loadvsdfileaction.cpp \
    vsdmanagerevent.cpp \
    vsdpreferencesaction.cpp \
    vsdecoderpreferencespane.cpp \
    installdecoderurlaction.cpp \
    installdecoderfileaction.cpp \
    vsdoptionpanel.cpp \
    profileutils.cpp \
    jmriconfigurationprovider.cpp \
    abstractconfigurationprovider.cpp \
    jmriuserinterfaceconfigurationprovider.cpp \
    jmriconfiguration.cpp \
    jmriconfigurationmanager.cpp \
    jmrijtablepersistencemanager.cpp \
    startupactionsmanager.cpp \
    connectionconfigmanager.cpp \
    filelocationspreferences.cpp \
    abstractpreferences.cpp \
    version.cpp \
    addprofiledialog.cpp \
    systemconsolepreferencesmanager.cpp \
    programmerconfigmanager.cpp \
    rosterconfigmanager.cpp \
    nodechangeevent.cpp \
    preferencechangeevent.cpp \
    xmlsupport.cpp \
    preferences.cpp \
    guilafpreferencesmanager.cpp \
    jtable.cpp \
    abstracttablemodel.cpp \
    dndjtable.cpp \
    defaulttablemodel.cpp \
    mysortfilterproxymodel.cpp \
    xmlfilevalidateaction.cpp \
    logixloadaction.cpp \
    logframe.cpp \
    logpanel.cpp \
    logaction.cpp \
    profileproperties.cpp \
    transformerfactory.cpp \
    outputkeys.cpp \
    abstractactionmodelfactory.cpp \
    performactionmodelfactory.cpp \
    startupactionmodelutil.cpp \
    metadata.cpp \
    startuppausefactory.cpp \
    startuppausemodel.cpp \
    abstractstartupmodel.cpp \
    createbuttonmodelfactory.cpp \
    triggerroutemodelfactory.cpp \
    scriptbuttonmodelfactory.cpp \
    abstractfilemodelfactory.cpp \
    performfilemodelfactory.cpp \
    triggerroutemodel.cpp \
    scriptbuttonmodel.cpp \
    scriptbuttonpanel.cpp \
    performscriptmodelfactory.cpp \
    createbuttommodelxml.cpp \
    performactionmodelxml.cpp \
    startuppausemodelxml.cpp \
    performfilemodelxml.cpp \
    performscriptmodelxml.cpp \
    abstractstartupactionfactory.cpp \
    restartstartupactionfactory.cpp \
    restartaction.cpp \
    triggerroutemodelxml.cpp \
    powerbuttonaction.cpp \
    jynstrumentpopupmenu.cpp \
    preferencesbean.cpp \
    editconnectionpreferencesdialog.cpp \
    editconnectionpreferences.cpp \
    firsttimestartupwizard.cpp \
    firsttimestartupwizardaction.cpp \
    profileconfiguration.cpp \
    nullprofile.cpp \
    jlisttablemodel.cpp \
    ampmeterframe.cpp \
    ampmeteraction.cpp \
    whereusedaction.cpp \
    whereusedframe.cpp \
    entryexitwhereused.cpp \
    whereusedcollectors.cpp \
    turnoutwhereused.cpp \
    namedbeanusagereport.cpp \
    sensorwhereused.cpp \
    lightwhereused.cpp \
    signalheadwhereused.cpp \
    signalmastwhereused.cpp \
    reporterwhereused.cpp \
    blockwhereused.cpp \
    memorywhereused.cpp \
    oblockwhereused.cpp \
    routewhereused.cpp \
    sectionwhereused.cpp \
    warrantwhereused.cpp \
    transferactionlistener.cpp \
    appsconfigurationmanager.cpp

HEADERS += appslib.h\
    appslib_global.h \
    apps.h \
    myapplication.h \
    createbuttonmodel.h \
    splashwindow.h \
    toolsmenu.h \
    powerpanelaction.h \
    simpleturnoutctrlaction.h \
    simpleclockaction.h \
    analogclockaction.h \
    nixieclockaction.h \
    consisttoolaction.h \
    lcdclockaction.h \
    dualdecodertoolaction.h \
    dualdecoderselectframe.h \
    dualdecoderselectpane.h \
    activesystemsmenu.h \
    systemconsole.h \
    systemconsoleconfigpanelxml.h \
    systemconsoleconfigpanel.h \
    systemconsoleaction.h \
    apps3.h \
    jmenuutil.h \
    guiutilbase.h \
    jtoolbarutil.h \
    appconfigbase.h \
    appsbase.h \
    metatypes.h \
    panelproaction.h \
    appslaunchframe.h \
    appslaunchpane.h \
    application.h \
    panelpropane.h \
    performscriptmodel.h \
    xml.h \
    printdecoderlistaction.h \
    debugmenu.h \
    vsdecodercreationaction.h \
    loadvsdfileaction.h \
    vsdmanagerevent.h \
    vsdpreferencesaction.h \
    vsdecoderpreferencespane.h \
    installdecoderurlaction.h \
    installdecoderfileaction.h \
    vsdoptionpanel.h \
    profileutils.h \
    auxiliaryconfiguration.h \
    jmriconfigurationprovider.h \
    abstractconfigurationprovider.h \
    nodeidentity.h \
    jmriuserinterfaceconfigurationprovider.h \
    jmriconfiguration.h \
    jmriconfigurationmanager.h \
    profilemanager.h \
    jmrijtablepersistencemanager.h \
    startupactionsmanager.h \
    connectionconfigmanager.h \
    filelocationspreferences.h \
    abstractpreferences.h \
    profile.h \
    version.h \
    addprofiledialog.h \
    jmripreferencesprovider.h \
    systemconsolepreferencesmanager.h \
    programmerconfigmanager.h \
    rosterconfigmanager.h \
    nodechangeevent.h \
    preferencechangeevent.h \
    xmlsupport.h \
    preferences.h \
    guilafpreferencesmanager.h \
    jtable.h \
    abstracttablemodel.h \
    dndjtable.h \
    defaulttablemodel.h \
    jtablepersistencemanager.h \
    instancemanager.h \
    defaultinstanceinitializer.h \
    mysortfilterproxymodel.h \
    xmlfilevalidateaction.h \
    logixloadaction.h \
    logframe.h \
    logpanel.h \
    logaction.h \
    startupmodel.h \
    auxiliaryproperties.h \
    profileproperties.h \
    transformerfactory.h \
    outputkeys.h \
    startupmodelfactory.h \
    abstractactionmodelfactory.h \
    performactionmodelfactory.h \
    startupactionmodelutil.h \
    startupactionfactory.h \
    systemconnectionaction.h \
    metadata.h \
    startuppausefactory.h \
    startuppausemodel.h \
    abstractstartupmodel.h \
    createbuttonmodelfactory.h \
    triggerroutemodelfactory.h \
    scriptbuttonmodelfactory.h \
    abstractfilemodelfactory.h \
    performfilemodelfactory.h \
    triggerroutemodel.h \
    scriptbuttonmodel.h \
    scriptbuttonpanel.h \
    performscriptmodelfactory.h \
    createbuttommodelxml.h \
    performactionmodelxml.h \
    startuppausemodelxml.h \
    performfilemodelxml.h \
    performscriptmodelxml.h \
    abstractstartupactionfactory.h \
    restartstartupactionfactory.h \
    systemconnectionaction.h \
    restartaction.h \
    triggerroutemodelxml.h \
    powerbuttonaction.h \
    jynstrumentpopupmenu.h \
    preferencesbean.h \
    editconnectionpreferencesdialog.h \
    editconnectionpreferences.h \
    firsttimestartupwizard.h \
    firsttimestartupwizardaction.h \
    profileconfiguration.h \
    nullprofile.h \
   jlist.h \
    jlisttablemodel.h \
    fileutil.h \
    fileutilsupport.h \
    properties.h \
    ampmeterframe.h \
    ampmeteraction.h \
    whereusedaction.h \
    whereusedframe.h \
    entryexitwhereused.h \
    whereusedcollectors.h \
    turnoutwhereused.h \
    namedbeanusagereport.h \
    sensorwhereused.h \
    lightwhereused.h \
    signalheadwhereused.h \
    signalmastwhereused.h \
    reporterwhereused.h \
    blockwhereused.h \
    memorywhereused.h \
    oblockwhereused.h \
    routewhereused.h \
    sectionwhereused.h \
    warrantwhereused.h \
    transferactionlistener.h \
    appsconfigurationmanager.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3/release/ -lPr3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3/debug/ -lPr3
else:unix: LIBS += -L$$PWD/../libPr3/ -lPr3

INCLUDEPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/Throttle \
    $$PWD/../libPr3/loconet $$PWD/../libPr3/LocoIO $$PWD/../libPr3/Json \
    $$PWD/../libPr3/WiThrottle $$PWD/../libPr3/Web $$PWD/../libPr3/Signal \
    $$PWD/../libPr3/sprog $$PWD/../libPr3/loconet/HexFile
DEPENDPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/Throttle \
    $$PWD/../libPr3/loconet $$PWD/../libPr3/LocoIO $$PWD/../libPr3/Json \
    $$PWD/../libPr3/WiThrottle $$PWD/../libPr3/Web $$PWD/../libPr3/Signal \
    $$PWD/../libPr3/sprog $$PWD/../libPr3/loconet/HexFile

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



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LayoutEditor/release/ -lLayoutEditor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LayoutEditor/debug/ -lLayoutEditor
else:unix: LIBS += -L$$PWD/../LayoutEditor/ -lLayoutEditor

INCLUDEPATH += $$PWD/../LayoutEditor $$PWD/../LayoutEditor/scripts
DEPENDPATH += $$PWD/../LayoutEditor $$PWD/../LayoutEditor/scripts

OTHER_FILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LocoIO/release/ -lLocoIO
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LocoIO/debug/ -lLocoIO
else:unix: LIBS += -L$$PWD/../LocoIO/ -lLocoIO

INCLUDEPATH += $$PWD/../LocoIO
DEPENDPATH += $$PWD/../LocoIO

TRANSLATIONS += \
    languages/appslib_de.ts \
    languages/appslib_en.ts

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/release/ -lJavaQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/debug/ -lJavaQt
else:unix: LIBS += -L$$PWD/../JavaQt/ -lJavaQt

INCLUDEPATH += $$PWD/../JavaQt
DEPENDPATH += $$PWD/../JavaQt


win32:CONFIG(debug, debug|release): LIBS += -L"C:/Program Files (x86)/local/lib" -lquazip
else:unix: LIBS += -L/usr/local/lib/ -lquazip

unix: {
INCLUDEPATH += /usr/local/include/quazip
DEPENDPATH += /usr/local/include/quazip
}
win32: {
INCLUDEPATH += "C:/Program Files (x86)/local/include/quazip" "C:\Program Files (x86)\GnuWin32\include"
DEPENDPATH += "C:/Program Files (x86)/local/include/quazip"
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../operations/release/ -loperations
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../operations/debug/ -loperations
else:unix: LIBS += -L$$PWD/../operations/ -loperations

INCLUDEPATH += $$PWD/../operations
DEPENDPATH += $$PWD/../operations

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../tests/release/ -ltests
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../tests/debug/ -ltests
else:unix: LIBS += -L$$PWD/../tests/ -ltests

INCLUDEPATH += $$PWD/../tests
DEPENDPATH += $$PWD/../tests

