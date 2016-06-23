#-------------------------------------------------
#
# Project created by QtCreator 2015-08-17T10:25:47
#
#-------------------------------------------------

TARGET = appslib
TEMPLATE = lib
greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport gui webkitwidgets
}
QT += xml sql network

DEFINES += APPSLIB_LIBRARY

win32:exists("C:/Program Files (x86)/local/lib/PythonQt.dll") {
 ENABLE_SCRIPTING = "Y"
}
unix:exists(/usr/local/lib/libPythonQt.so) {
 ENABLE_SCRIPTING = "Y"
}
#CONFIG += scripts
equals(ENABLE_SCRIPTING, "Y") {
    DEFINES += SCRIPTING_ENABLED
 SOURCES += operations/trainsscriptaction.cpp \
    operations/trainsscriptframe.cpp

HEADERS +=     operations/trainscriptaction.h \
    operations/trainscriptframe.h
 message("Appslib: scripting enabled")
} else {
 message("Appslib: scripting disabled")
}

SOURCES += appslib.cpp \
    apps.cpp \
    myapplication.cpp \
    operations/trainmanifesttext.cpp \
    createbuttonpanel.cpp \
    createbuttonmodel.cpp \
    createbuttonpanelxml.cpp \
    splashwindow.cpp \
    toolsmenu.cpp \
    powerpanelaction.cpp \
    simpleturnoutctrlaction.cpp \
    simpleclockaction.cpp \
    analogclockaction.cpp \
    listedtableaction.cpp \
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
    apps3.cpp \
    system.cpp \
    jmenuutil.cpp \
    guiutilbase.cpp \
    jtoolbarutil.cpp \
    appconfigbase.cpp \
    appsbase.cpp \
    metatypes.cpp \
    panelproaction.cpp \
    appslaunchframe.cpp \
    appslaunchpane.cpp \
    application.cpp \
    panelpropane.cpp \
    performscriptmodel.cpp \
    operationsmenu.cpp \
    xml.cpp \
    printdecoderlistaction.cpp \
    debugmenu.cpp \
    vsdecoderframe.cpp \
    vsdecoderpane.cpp \
    vsdecodercreationaction.cpp \
    loadvsdfileaction.cpp \
    vsdmanagerevent.cpp \
    vsdpreferencesaction.cpp \
    vsdecoderpreferencespane.cpp \
    loadxmlvsdecoderaction.cpp \
    installdecoderurlaction.cpp \
    installdecoderfileaction.cpp \
    vsdsoundspanel.cpp \
    vsdoptionpanel.cpp \
    operations/trainswitchlisttext.cpp \
    operations/schedule.cpp \
    operations/scheduleitem.cpp \
    operations/setup.cpp \
    operations/routemanagerxml.cpp \
    operations/routemanager.cpp \
    operations/operationssetupxml.cpp \
    operations/route.cpp \
    operations/trainstablemodel.cpp \
    operations/trainstableframe.cpp \
    operations/trainmanager.cpp \
    operations/trainmanagerxml.cpp \
    operations/train.cpp \
    operations/cartypes.cpp \
    operations/enginetypes.cpp \
    operations/routelocation.cpp \
    operations/location.cpp \
    operations/track.cpp \
    operations/schedulemanager.cpp \
    operations/trainschedulemanager.cpp \
    operations/locationmanager.cpp \
    operations/carowners.cpp \
    operations/carcolors.cpp \
    operations/carroads.cpp \
    operations/rollingstock.cpp \
    operations/engine.cpp \
    operations/rollingstockmanager.cpp \
    operations/enginemodels.cpp \
    operations/enginemanager.cpp \
    operations/enginestablemodel.cpp \
    operations/rollingstockgroup.cpp \
    operations/consist.cpp \
    operations/pool.cpp \
    operations/traincommon.cpp \
    operations/rollingstockattribute.cpp \
    operations/locationmanagerxml.cpp \
    operations/enginemanagerxml.cpp \
    operations/enginestableaction.cpp \
    operations/enginestableframe.cpp \
    operations/operationsframe.cpp \
    operations/operationspanel.cpp \
    operations/engineeditframe.cpp \
    operations/engineattributeeditframe.cpp \
    operations/carmanager.cpp \
    operations/carmanagerxml.cpp \
    operations/car.cpp \
    operations/kernel.cpp \
    operations/operationssetupaction.cpp \
    operations/operationssetupframe.cpp \
    operations/operationssetuppanel.cpp \
    operations/operationspreferencespanel.cpp \
    operations/autobackup.cpp \
    operations/backupbase.cpp \
    operations/control.cpp \
    operations/backupdialog.cpp \
    operations/defaultbackup.cpp \
    operations/restoredialog.cpp \
    operations/backupset.cpp \
    operations/operationsmanager.cpp \
    operations/carstableaction.cpp \
    operations/carstableframe.cpp \
    operations/carstablemodel.cpp \
    operations/carloads.cpp \
    operations/carload.cpp \
    operations/careditframe.cpp \
    operations/carattributeeditframe.cpp \
    operations/carattributeaction.cpp \
    operations/cardeleteattributeaction.cpp \
    operations/carlengths.cpp \
    operations/carrostermenu.cpp \
    operations/showcheckboxescarstableaction.cpp \
    operations/resetcheckboxescarstableaction.cpp \
    operations/carsetframe.cpp \
    operations/rollingstocksetframe.cpp \
    operations/enginelengths.cpp \
    operations/enginesetframe.cpp \
    operations/locationstableaction.cpp \
    operations/locationstableframe.cpp \
    operations/locationstablemodel.cpp \
    operations/locationeditframe.cpp \
    operations/tracktablemodel.cpp \
    operations/yardtablemodel.cpp \
    operations/spurtablemodel.cpp \
    operations/interchangetablemodel.cpp \
    operations/stagingtablemodel.cpp \
    operations/editcartypeaction.cpp \
    operations/trackeditframe.cpp \
    operations/yardeditframe.cpp \
    operations/spureditframe.cpp \
    operations/interchangeeditframe.cpp \
    operations/stagingeditframe.cpp \
    operations/trackeditcommentsaction.cpp \
    operations/trackeditcommentsframe.cpp \
    operations/modifylocationsaction.cpp \
    operations/locationsbycartypeframe.cpp \
    operations/changetrackstypeaction.cpp \
    operations/changetracksframe.cpp \
    operations/yardmasterframe.cpp \
    operations/yardmasterpanel.cpp \
    operations/commonconductoryardmasterpanel.cpp \
    operations/trainstableaction.cpp \
    operations/trainmanifestheadertext.cpp \
    operations/carloadeditframe.cpp \
    operations/autosave.cpp \
    operations/routestableaction.cpp \
    operations/routestablemodel.cpp \
    operations/routestableframe.cpp \
    operations/routeeditframe.cpp \
    operations/routeedittablemodel.cpp \
    operations/routecopyaction.cpp \
    operations/settrainiconrouteaction.cpp \
    operations/settrainiconrouteframe.cpp \
    operations/settrainiconpositionaction.cpp \
    operations/settrainiconpositionframe.cpp \
    operations/enginerostermenu.cpp \
    operations/importrosterengineaction.cpp \
    operations/importrosterengines.cpp \
    operations/importcarrosteraction.cpp \
    operations/importcars.cpp \
    operations/importrollingstock.cpp \
    operations/locationtrackpair.cpp \
    operations/scheduleeditframe.cpp \
    operations/scheduletablemodel.cpp \
    operations/schedulestableaction.cpp \
    operations/schedulestableframe.cpp \
    operations/schedulestablemodel.cpp \
    operations/locationcopyframe.cpp \
    operations/locationcopyaction.cpp \
    operations/showcarsbylocationaction.cpp \
    operations/showtrainsservinglocationaction.cpp \
    operations/showtrainsservinglocationframe.cpp \
    operations/trainschedule.cpp \
    operations/traineditframe.cpp \
    operations/trainconductorframe.cpp \
    operations/trainconductorpanel.cpp \
    operations/trainconductoraction.cpp \
    operations/printtrainaction.cpp \
    operations/trackroadeditframe.cpp \
    operations/trackroadeditaction.cpp \
    operations/trackloadeditframe.cpp \
    operations/trackloadeditaction.cpp \
    operations/optionframe.cpp \
    operations/optionaction.cpp \
    operations/trainmanifest.cpp \
    operations/trainprintutilities.cpp \
    operations/printtrainsaction.cpp \
    operations/trainbuilder.cpp \
    operations/carssetframe.cpp \
    operations/carssetframeaction.cpp \
    operations/trainsbycartypeframe.cpp \
    operations/trainsbycartypeaction.cpp \
    operations/optionpanel.cpp \
    operations/printoptionframe.cpp \
    operations/printoptionaction.cpp \
    operations/printoptionpanel.cpp \
    operations/trainswitchlisteditframe.cpp \
    operations/trainswitchlists.cpp \
    operations/loaddemoaction.cpp \
    operations/restorefilesaction.cpp \
    operations/backupfilesaction.cpp \
    operations/resetaction.cpp \
    operations/buildreportoptionpanel.cpp \
    operations/buildreportoptionframe.cpp \
    operations/buildreportoptionaction.cpp \
    operations/router.cpp \
    operations/managebackupsdialog.cpp \
    operations/managebackupsaction.cpp \
    operations/trackcopyframe.cpp \
    operations/trackcopyaction.cpp \
    operations/printrouteaction.cpp \
    operations/printroutesaction.cpp \
    operations/printcarloadsaction.cpp \
    operations/enabledestinationaction.cpp \
    operations/editmanifestheadertextaction.cpp \
    operations/editmanifestheadertextframe.cpp \
    operations/editmanifesttextframe.cpp \
    operations/editswitchlisttextframe.cpp \
    operations/editswitchlisttextaction.cpp \
    operations/editmanifesttextaction.cpp \
    operations/editswitchlisttextpanel.cpp \
    operations/changetracktypeaction.cpp \
    operations/changetrackframe.cpp \
    operations/printlocationsaction.cpp \
    operations/modifylocationscarloadsaction.cpp \
    operations/locationsbycarloadframe.cpp \
    operations/printmoreoptionaction.cpp \
    operations/printmoreoptionframe.cpp \
    operations/printmoreoptionpanel.cpp \
    operations/carloadattributeaction.cpp \
    operations/ignoreusedtrackaction.cpp \
    operations/ignoreusedtrackframe.cpp \
    operations/trackdestinationeditaction.cpp \
    operations/trackdestinationeditframe.cpp \
    operations/pooltrackaction.cpp \
    operations/pooltrackframe.cpp \
    operations/printlocationsbycartypesaction.cpp \
    operationsxml.cpp \
    operations/routecopyframe.cpp \
    operations/schedulesbyloadaction.cpp \
    operations/schedulesbyloadframe.cpp \
    operations/scheduleresethitsaction.cpp \
    operations/schedulesresethitsaction.cpp \
    operations/schedulecopyframe.cpp \
    operations/schedulecopyaction.cpp \
    operations/scheduleoptionsaction.cpp \
    operations/scheduleoptionsframe.cpp \
    operations/printtrainmanifestaction.cpp \
    operations/printtrainbuildreportaction.cpp \
    operations/traineditbuildoptionsaction.cpp \
    operations/traineditbuildoptionsframe.cpp \
    operations/printtrainsbycartypesaction.cpp \
    operations/printswitchlistaction.cpp \
    operations/trainbycartypeframe.cpp \
    operations/trainbycartypeaction.cpp \
    operations/trainstablesetcolorframe.cpp \
    operations/trainstablesetcoloraction.cpp \
    operations/changedeparturetimesaction.cpp \
    operations/changedeparturetimesframe.cpp \
    operations/trainsscheduleaction.cpp \
    operations/trainsscheduletableframe.cpp \
    operations/trainsscheduletablemodel.cpp \
    operations/traincopyaction.cpp \
    operations/traincopyframe.cpp \
    operations/trainsscheduleeditaction.cpp \
    operations/trainsscheduleeditframe.cpp \
    operations/alternatetrackaction.cpp \
    operations/alternatetrackframe.cpp \
    operations/showcarsintrainaction.cpp \
    operations/showcarsintrainframe.cpp \
    operations/locationtrackblockingorderaction.cpp \
    operations/locationtrackblockingorderframe.cpp \
    operations/locationtrackblockingordertablemodel.cpp \
    operations/trainloadoptionsaction.cpp \
    operations/trainloadoptionsframe.cpp \
    operations/trainroadoptionsaction.cpp \
    operations/trainmanifestoptionaction.cpp \
    operations/trainroadoptionsframe.cpp \
    operations/trainmanifestoptionframe.cpp \
    operations/trainscriptaction.cpp \
    operations/trainscriptframe.cpp \
    operations/exportcarrosteraction.cpp \
    operations/exportcars.cpp \
    operations/printcarrosteraction.cpp \
    operations/deletecarrosteraction.cpp \
    operations/resetcarmovesaction.cpp \
    operations/exporttrainrosteraction.cpp \
    operations/exporttrains.cpp

HEADERS += appslib.h\
        appslib_global.h \
    apps.h \
    myapplication.h \
    createbuttonpanelxml.h \
    createbuttonpanel.h \
    createbuttonmodel.h \
    splashwindow.h \
    toolsmenu.h \
    powerpanelaction.h \
    simpleturnoutctrlaction.h \
    simpleclockaction.h \
    analogclockaction.h \
    listedtableaction.h \
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
    system.h \
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
    operationsmenu.h \
    operationsxml.h \
    xml.h \
    printdecoderlistaction.h \
    debugmenu.h \
    vsdecoderframe.h \
    vsdecoderpane.h \
    vsdecodercreationaction.h \
    loadvsdfileaction.h \
    vsdmanagerevent.h \
    vsdpreferencesaction.h \
    vsdecoderpreferencespane.h \
    loadxmlvsdecoderaction.h \
    installdecoderurlaction.h \
    installdecoderfileaction.h \
    vsdsoundspanel.h \
    vsdoptionpanel.h \
    operations/trainswitchlisttext.h \
    operations/routemanagerxml.h \
    operations/routemanager.h \
    operations/operationssetupxml.h \
    operations/route.h \
    operations/trainmanager.h \
    operations/trainmanagerxml.h \
    operations/train.h \
    operations/routelocation.h \
    operations/location.h \
    operations/track.h \
    operations/locationmanagerxml.h \
    operations/locationmanager.h \
    operations/carowners.h \
    operations/carroads.h \
    operations/carloads.h \
    operations/carload.h \
    operations/carcolors.h \
    operations/rollingstock.h \
    operations/engine.h \
    operations/rollingstockmanager.h \
    operations/enginemanager.h \
    operations/rollingstockgroup.h \
    operations/consist.h \
    operations/pool.h \
    operations/traincommon.h \
    operations/rollingstockattribute.h \
    operations/enginemodels.h \
    operations/enginemanagerxml.h \
    operations/enginestableaction.h \
    operations/enginestableframe.h \
    operations/operationsframe.h \
    operations/operationspanel.h \
    operations/enginestablemodel.h \
    operations/engineeditframe.h \
    operations/engineattributeeditframe.h \
    operations/carmanager.h \
    operations/carmanagerxml.h \
    operations/car.h \
    operations/kernel.h \
    operations/operationssetupaction.h \
    operations/operationssetupframe.h \
    operations/operationssetuppanel.h \
    operations/operationspreferencespanel.h \
    operations/autobackup.h \
    operations/backupbase.h \
    operations/cartypes.h \
    operations/enginetypes.h \
    operations/control.h \
    operations/setup.cpp \
    operations/setup.h \
    operations/backupdialog.h \
    operations/defaultbackup.h \
    operations/restoredialog.h \
    operations/backupset.h \
    operations/operationsmanager.h \
    operations/carstableaction.h \
    operations/carstableframe.h \
    operations/carstablemodel.h \
    operations/careditframe.h \
    operations/carattributeeditframe.h \
    operations/carattributeaction.h \
    operations/cardeleteattributeaction.h \
    operations/carlengths.h \
    operations/carrostermenu.h \
    operations/showcheckboxescarstableaction.h \
    operations/resetcheckboxescarstableaction.h \
    operations/carsetframe.h \
    operations/rollingstocksetframe.h \
    operations/enginelengths.h \
    operations/enginesetframe.h \
    operations/locationstableaction.h \
    operations/locationstableframe.h \
    operations/locationstablemodel.h \
    operations/locationeditframe.h \
    operations/tracktablemodel.h \
    operations/yardtablemodel.h \
    operations/spurtablemodel.h \
    operations/interchangetablemodel.h \
    operations/stagingtablemodel.h \
    operations/editcartypeaction.h \
    operations/trackeditframe.h \
    operations/yardeditframe.h \
    operations/spureditframe.h \
    operations/interchangeeditframe.h \
    operations/stagingeditframe.h \
    operations/trackeditcommentsaction.h \
    operations/trackeditcommentsframe.h \
    operations/modifylocationsaction.h \
    operations/locationsbycartypeframe.h \
    operations/changetrackstypeaction.h \
    operations/changetracksframe.h \
    operations/yardmasterframe.h \
    operations/yardmasterpanel.h \
    operations/commonconductoryardmasterpanel.h \
    operations/trainstablemodel.h \
    operations/trainstableframe.h \
    operations/trainstableaction.h \
    operations/trainmanifestheadertext.h \
    operations/carloadeditframe.h \
    operations/autosave.h \
    operations/routestableaction.h \
    operations/routestablemodel.h \
    operations/routestableframe.h \
    operations/routeeditframe.h \
    operations/routeedittablemodel.h \
    operations/routecopyaction.h \
    operations/settrainiconrouteframe.h \
    operations/settrainiconpositionaction.h \
    operations/settrainiconpositionframe.h \
    operations/enginerostermenu.h \
    operations/importrosterengineaction.h \
    operations/importrosterengines.h \
    operations/importcarrosteraction.h \
    operations/importcars.h \
    operations/importrollingstock.h \
    operations/schedulemanager.h \
    operations/schedule.h \
    operations/scheduleitem.h \
    operations/locationtrackpair.h \
    operations/scheduleeditframe.h \
    operations/scheduletablemodel.h \
    operations/schedulestableaction.h \
    operations/schedulestableframe.h \
    operations/schedulestablemodel.h \
    operations/locationcopyframe.h \
    operations/locationcopyaction.h \
    operations/showcarsbylocationaction.h \
    operations/showtrainsservinglocationaction.h \
    operations/showtrainsservinglocationframe.h \
    operations/trainschedule.h \
    operations/traineditframe.h \
    operations/trainconductorframe.h \
    operations/trainconductorpanel.h \
    operations/trainconductoraction.h \
    operations/trainschedulemanager.h \
    operations/printtrainaction.h \
    operations/trackroadeditframe.h \
    operations/trackroadeditaction.h \
    operations/trackloadeditframe.h \
    operations/trackloadeditaction.h \
    operations/optionframe.h \
    operations/optionaction.h \
    operations/trainmanifest.h \
    operations/trainmanifesttext.h \
    operations/trainprintutilities.h \
    operations/printtrainsaction.h \
    operations/trainbuilder.h \
    operations/carssetframe.h \
    operations/carssetframeaction.h \
    operations/trainsbycartypeframe.h \
    operations/trainsbycartypeaction.h \
    operations/optionpanel.h \
    operations/printoptionframe.h \
    operations/printoptionaction.h \
    operations/printoptionpanel.h \
    operations/trainswitchlisteditframe.h \
    operations/trainswitchlists.h \
    operations/loaddemoaction.h \
    operations/restorefilesaction.h \
    operations/backupfilesaction.h \
    operations/resetaction.h \
    operations/buildreportoptionpanel.h \
    operations/buildreportoptionframe.h \
    operations/buildreportoptionaction.h \
    operations/router.h \
    operations/managebackupsdialog.h \
    operations/managebackupsaction.h \
    operations/trackcopyframe.h \
    operations/trackcopyaction.h \
    operations/printrouteaction.h \
    operations/printroutesaction.h \
    operations/printcarloadsaction.h \
    operations/enabledestinationaction.h \
    operations/editmanifestheadertextaction.h \
    operations/editmanifestheadertextframe.h \
    operations/editmanifesttextframe.h \
    operations/editswitchlisttextframe.h \
    operations/editswitchlisttextaction.h \
    operations/editmanifesttextaction.h \
    operations/editswitchlisttextpanel.h \
    operations/changetracktypeaction.h \
    operations/changetrackframe.h \
    operations/printlocationsaction.h \
    operations/modifylocationscarloadsaction.h \
    operations/locationsbycarloadframe.h \
    operations/printmoreoptionaction.h \
    operations/printmoreoptionframe.h \
    operations/printmoreoptionpanel.h \
    operations/carloadattributeaction.h \
    operations/ignoreusedtrackaction.h \
    operations/ignoreusedtrackframe.h \
    operations/trackdestinationeditaction.h \
    operations/trackdestinationeditframe.h \
    operations/pooltrackaction.h \
    operations/pooltrackframe.h \
    operations/printlocationsbycartypesaction.h \
    operations/routecopyframe.h \
    operations/schedulesbyloadaction.h \
    operations/schedulesbyloadframe.h \
    operations/scheduleresethitsaction.h \
    operations/schedulesresethitsaction.h \
    operations/schedulecopyframe.h \
    operations/schedulecopyaction.h \
    operations/scheduleoptionsaction.h \
    operations/scheduleoptionsframe.h \
    operations/printtrainmanifestaction.h \
    operations/printtrainbuildreportaction.h \
    operations/traineditbuildoptionsaction.h \
    operations/traineditbuildoptionsframe.h \
    operations/printtrainsbycartypesaction.h \
    operations/printswitchlistaction.h \
    operations/trainbycartypeframe.h \
    operations/trainbycartypeaction.h \
    operations/trainstablesetcolorframe.h \
    operations/trainstablesetcoloraction.h \
    operations/changedeparturetimesaction.h \
    operations/changedeparturetimesframe.h \
    operations/trainsscheduleaction.h \
    operations/trainsscheduletableframe.h \
    operations/trainsscheduletablemodel.h \
    operations/traincopyaction.h \
    operations/traincopyframe.h \
    operations/trainsscheduleeditaction.h \
    operations/trainsscheduleeditframe.h \
    operations/alternatetrackaction.h \
    operations/alternatetrackframe.h \
    operations/showcarsintrainaction.h \
    operations/showcarsintrainframe.h \
    operations/trainsscriptframe.h \
    operations/trainsscriptaction.h \
    operations/locationtrackblockingorderaction.h \
    operations/locationtrackblockingorderframe.h \
    operations/locationtrackblockingordertablemodel.h \
    operations/trainloadoptionsaction.h \
    operations/trainloadoptionsframe.h \
    operations/trainroadoptionsaction.h \
    operations/trainmanifestoptionaction.h \
    operations/trainroadoptionsframe.h \
    operations/trainmanifestoptionframe.h \
    operations/exportcarrosteraction.h \
    operations/exportcars.h \
    operations/printcarrosteraction.h \
    operations/deletecarrosteraction.h \
    operations/resetcarmovesaction.h \
    operations/exporttrainrosteraction.h \
    operations/exporttrains.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

DEPENDPATH += . operations
INCLUDEPATH += . operations

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3/release/ -lPr3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3/debug/ -lPr3
else:unix: LIBS += -L$$PWD/../libPr3/ -lPr3

INCLUDEPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/Throttle $$PWD/../libPr3/loconet $$PWD/../libPr3/LocoIO
DEPENDPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/Throttle $$PWD/../libPr3/loconet $$PWD/../libPr3/LocoIO

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

OTHER_FILES += \
    libappslib.so.1.0.0

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
