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
 SOURCES += operations/trainsscriptaction.cpp \
    operations/trainsscriptframe.cpp \
    jynstrument.cpp \
    jynstrumentfactory.cpp


HEADERS +=     operations/trainscriptaction.h \
    operations/trainscriptframe.h \
    jynstrument.h \
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
    jlist.cpp \
    defaultinstanceinitializer.cpp \
    jmripreferencesprovider.cpp \
    nodeidentity.cpp \
    profilemanager.cpp \
    profile.cpp \
    myapplication.cpp \
    operations/trainmanifesttext.cpp \
    createbuttonmodel.cpp \
    splashwindow.cpp \
    toolsmenu.cpp \
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
    operationsxml.cpp \
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
    operations/exporttrains.cpp \
    operations/abstractoperationsserver.cpp \
    profileutils.cpp \
    jmriconfigurationprovider.cpp \
    abstractconfigurationprovider.cpp \
    jmriuserinterfaceconfigurationprovider.cpp \
    jmriconfiguration.cpp \
    operations/activetrain.cpp \
    operations/dispatcherframe.cpp \
    operations/autoactivetrain.cpp \
    operations/autotrainaction.cpp \
    operations/dispatcheraction.cpp \
    operations/allocationrequest.cpp \
    operations/allocatedsection.cpp \
    operations/autoturnouts.cpp \
    operations/autoallocate.cpp \
    operations/activatetrainframe.cpp \
    operations/traininfofile.cpp \
    operations/traininfo.cpp \
    operations/allocationplan.cpp \
    operations/autotrainsframe.cpp \
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
    operations/traincsvmanifest.cpp \
    operations/traincsvcommon.cpp \
    operations/buildfailedexception.cpp \
    operations/traincustommanifest.cpp \
    operations/traincustomcommon.cpp \
    operations/setupexcelprogramframeaction.cpp \
    operations/setupexcelprogrammanifestframe.cpp \
    operations/setupexcelprogramframe.cpp \
    operations/optionsmenu.cpp \
    operations/yardmasterbytrackpanel.cpp \
    operations/yardmasterbytrackframe.cpp \
    operations/yardmasterbytrackaction.cpp \
    jynstrumentpopupmenu.cpp \
    preferencesbean.cpp \
    editconnectionpreferencesdialog.cpp \
    editconnectionpreferences.cpp \
    firsttimestartupwizard.cpp \
    firsttimestartupwizardaction.cpp \
    profileconfiguration.cpp \
    nullprofile.cpp \
    tests/junitutil.cpp \
    tests/temporaryfolder.cpp \
    tests/RosterTest/rosterentrytestaction.cpp \
    tests/RosterTest/rostertest.cpp \
    tests/RosterTest/rostertestaction.cpp \
    tests/RosterTest/rosterentrytest.cpp \
    tests/RosterTest/rostertestutil.cpp \
    tests/assert1.cpp \
    tests/RosterTest/rosterentrypanetest.cpp \
    tests/RosterTest/rosterentrypanetestaction.cpp \
    tests/ProfileTest/profiletest.cpp \
    tests/ProfileTest/profiletestaction.cpp \
    tests/ProfileTest/profilemanagertest.cpp \
    tests/ProfileTest/profilemanagertestaction.cpp \
    tests/loconet/slotmanagertest.cpp \
    tests/loconet/loconetinterfacescaffold.cpp \
    tests/loconet/slotmanagertestaction.cpp \
    tests/loconet/loconetslottest.cpp \
    tests/loconet/loconetslottestaction.cpp \
    tests/junitappender.cpp \
    tests/loconet/lnopsmodeprogrammertest.cpp \
    tests/assume.cpp \
    tests/proglistenerscaffold.cpp \
    tests/loconet/lnopsmodeprogrammertestaction.cpp \
    tests/loconet/loconetmessagetest.cpp \
    tests/loconet/loconetmessagetestaction.cpp \
    tests/testsmenu.cpp \
    tests/loconet/lntrafficcontrollertest.cpp \
    tests/loconet/lntrafficcontrollertestaction.cpp \
    tests/abstractmessagetestbase.cpp \
    tests/sprog/sprogmessagetest.cpp \
    tests/sprog/sprogmessagetestaction.cpp \
    tests/loconet/lnpacketizertest.cpp \
    tests/loconet/lnportcontrollertestaction.cpp \
    tests/loconet/lnportcontrollertest.cpp \
    tests/abstractserialportcontrollertestbase.cpp \
    tests/abstractportcontrollertestbase.cpp \
    tests/loconet/lnpacketizertestaction.cpp \
    tests/abstractthrottletest.cpp \
    tests/loconet/loconetthrottletest.cpp \
    tests/ProfileTest/profileutilstest.cpp \
    tests/ProfileTest/profileutilstestaction.cpp \
    tests/loconet/lntrafficroutertest.cpp \
    tests/loconet/lntrafficroutertestaction.cpp \
    tests/loconet/loconetconsisttest.cpp \
    tests/loconet/loconetconsisttestaction.cpp \
    tests/loconet/lnpowermanagertest.cpp \
    tests/abstractpowermanagertestbase.cpp \
    tests/loconet/lnpowermanagertestaction.cpp \
    tests/abstractturnouttestbase.cpp \
    tests/loconet/lnturnouttest.cpp \
    tests/loconet/lnturnouttestaction.cpp \
    tests/abstractreportertest.cpp \
    tests/abstractsensortestbase.cpp \
    tests/abstractconsisttestbase.cpp \
    tests/loconet/lnsensortest.cpp \
    tests/loconet/lnsensortestaction.cpp \
    tests/addressedprogrammertestbase.cpp \
    tests/programmertestbase.cpp \
    tests/loconet/lnreportertest.cpp \
    tests/abstractreportertestbase.cpp \
    tests/loconet/lnreportertestaction.cpp \
    tests/loconet/lnsensoraddresstest.cpp \
    tests/loconet/lnsensoraddresstestaction.cpp \
    tests/loconet/lnsensormanagertest.cpp \
    tests/abstractsensormgrtestbase.cpp \
    tests/abstractmanagertestbase.cpp \
    tests/loconet/lnsensormanagertestaction.cpp \
    tests/loconet/lndeferprogranmmertest.cpp \
    tests/abstractprovidingturnoutmanagertestbase.cpp \
    tests/abstractturnoutmgrtestbase.cpp \
    tests/loconet/lnturnoutmanagertest.cpp \
    tests/testuserpreferencesmanager.cpp \
    tests/loconet/lndeferprogrammertestaction.cpp \
    tests/loconet/lnturnoutmanagertestaction.cpp \
    tests/misc/proxyturnoutmanagertest.cpp \
    tests/misc/proxyturnoutmanagertestaction.cpp \
    tests/loconet/lnlighttest.cpp \
    tests/loconet/lnlighttestaction.cpp \
    tests/misc/proxysensormanagertest.cpp \
    tests/misc/proxysensormanagertestaction.cpp \
    tests/misc/proxyreportermanagertest.cpp \
    tests/abstractreportermgrtestbase.cpp \
    tests/abstractprovidingreportermanagertestbase.cpp \
    tests/misc/proxyreportmanagertestaction.cpp \
    tests/misc/proxylightmanagertest.cpp \
    tests/misc/proxylightmanagertestaction.cpp \
    tests/misc/multiindexprogrammerfacadetest.cpp \
    tests/misc/multiindexprogrammerfacadetestaction.cpp \
    tests/misc/addressedhighcvprogranmmerfacadetest.cpp \
    tests/misc/addressedhighcvprogranmmerfacadetestaction.cpp \
    tests/misc/opsmodedelayedprogrammerfacadetest.cpp \
    tests/misc/opsmodedelayedprogrammerfacadetestaction.cpp \
    tests/misc/verifywriteprogrammerfacadetest.cpp \
    tests/misc/verifywriteprogrammerfacadetestaction.cpp \
    tests/misc/twoindextcsprogrammerfacadetest.cpp \
    tests/misc/twoindextcsprogrammerfacadetestaction.cpp \
    tests/misc/paneprogpanetest.cpp \
    tests/misc/paneprogpanetestaction.cpp \
    tests/misc/paneprogframetest.cpp \
    tests/misc/decoderfiletest.cpp \
    tests/misc/paneprogframetestaction.cpp \
    tests/misc/decoderfiletestaction.cpp

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
    operations/exporttrains.h \
    operations/abstractoperationsserver.h \
    profileutils.h \
    auxiliaryconfiguration.h \
    jmriconfigurationprovider.h \
    abstractconfigurationprovider.h \
    nodeidentity.h \
    jmriuserinterfaceconfigurationprovider.h \
    jmriconfiguration.h \
    operations/activetrain.h \
    operations/dispatcherframe.h \
    operations/autoactivetrain.h \
    operations/autotrainaction.h \
    operations/dispatcheraction.h \
    operations/allocationrequest.h \
    operations/allocatedsection.h \
    operations/autoturnouts.h \
    operations/autoallocate.h \
    operations/activatetrainframe.h \
    operations/traininfofile.h \
    operations/traininfo.h \
    operations/allocationplan.h \
    operations/autotrainsframe.h \
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
    jlist.h \
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
    operations/traincsvmanifest.h \
    operations/traincsvcommon.h \
    operations/buildfailedexception.h \
    operations/traincustommanifest.h \
    operations/traincustomcommon.h \
    operations/setupexcelprogramframeaction.h \
    operations/setupexcelprogrammanifestframe.h \
    operations/setupexcelprogramframe.h \
    operations/optionsmenu.h \
    operations/yardmasterbytrackpanel.h \
    operations/yardmasterbytrackframe.h \
    operations/yardmasterbytrackaction.h \
    jynstrumentpopupmenu.h \
    preferencesbean.h \
    editconnectionpreferencesdialog.h \
    editconnectionpreferences.h \
    firsttimestartupwizard.h \
    firsttimestartupwizardaction.h \
    profileconfiguration.h \
    nullprofile.h \
    tests/junitutil.h \
    tests/temporaryfolder.h \
    tests/RosterTest/rosterentrytestaction.h \
    tests/RosterTest/rostertest.h \
    tests/RosterTest/rostertestaction.h \
    tests/RosterTest/rosterentrytest.h \
    tests/RosterTest/rostertestutil.h \
    tests/assert1.h \
    tests/RosterTest/rosterentrypanetest.h \
    tests/RosterTest/rosterentrypanetestaction.h \
    tests/ProfileTest/profiletest.h \
    tests/ProfileTest/profiletestaction.h \
    tests/ProfileTest/profilemanagertest.h \
    tests/ProfileTest/profilemanagertestaction.h \
    tests/loconet/slotmanagertest.h \
    tests/loconet/loconetinterfacescaffold.h \
    tests/loconet/slotmanagertestaction.h \
    tests/loconet/loconetslottest.h \
    tests/loconet/loconetslottestaction.h \
    tests/junitappender.h \
    tests/loconet/lnopsmodeprogrammertest.h \
    tests/assume.h \
    tests/proglistenerscaffold.h \
    tests/loconet/lnopsmodeprogrammertestaction.h \
    tests/loconet/loconetmessagetest.h \
    tests/loconet/loconetmessagetestaction.h \
    tests/testsmenu.h \
    tests/loconet/lntrafficcontrollertest.h \
    tests/loconet/lntrafficcontrollertestaction.h \
    tests/abstractmessagetestbase.h \
    tests/sprog/sprogmessagetest.h \
    tests/sprog/sprogmessagetestaction.h \
    tests/loconet/lnpacketizertest.h \
    tests/loconet/lnportcontrollertestaction.h \
    tests/loconet/lnportcontrollertest.h \
    tests/abstractserialportcontrollertestbase.h \
    tests/abstractportcontrollertestbase.h \
    tests/loconet/lnpacketizertestaction.h \
    tests/abstractthrottletest.h \
    tests/loconet/loconetthrottletest.h \
    tests/ProfileTest/profileutilstest.h \
    tests/ProfileTest/profileutilstestaction.h \
    tests/loconet/lntrafficroutertest.h \
    tests/loconet/lntrafficroutertestaction.h \
    tests/loconet/loconetconsisttest.h \
    tests/loconet/loconetconsisttestaction.h \
    tests/loconet/lnpowermanagertest.h \
    tests/abstractpowermanagertestbase.h \
    tests/loconet/lnpowermanagertestaction.h \
    tests/abstractturnouttestbase.h \
    tests/loconet/lnturnouttest.h \
    tests/loconet/lnturnouttestaction.h \
    tests/abstractreportertest.h \
    tests/abstractsensortestbase.h \
    tests/abstractconsisttestbase.h \
    tests/loconet/lnsensortest.h \
    tests/loconet/lnsensortestaction.h \
    tests/addressedprogrammertestbase.h \
    tests/programmertestbase.h \
    tests/loconet/lnreportertest.h \
    tests/abstractreportertestbase.h \
    tests/loconet/lnreportertestaction.h \
    tests/loconet/lnsensoraddresstest.h \
    tests/loconet/lnsensoraddresstestaction.h \
    tests/loconet/lnsensormanagertest.h \
    tests/abstractsensormgrtestbase.h \
    tests/abstractmanagertestbase.h \
    tests/loconet/lnsensormanagertestaction.h \
    tests/loconet/lndeferprogranmmertest.h \
    tests/abstractprovidingturnoutmanagertestbase.h \
    tests/abstractturnoutmgrtestbase.h \
    tests/loconet/lnturnoutmanagertest.h \
    tests/testuserpreferencesmanager.h \
    tests/loconet/lndeferprogrammertestaction.h \
    tests/loconet/lnturnoutmanagertestaction.h \
    tests/misc/proxyturnoutmanagertest.h \
    tests/misc/proxyturnoutmanagertestaction.h \
    tests/loconet/lnlighttest.h \
    tests/loconet/lnlighttestaction.h \
    tests/misc/proxysensormanagertest.h \
    tests/misc/proxysensormanagertestaction.h \
    tests/misc/proxyreportermanagertest.h \
    tests/abstractreportermgrtestbase.h \
    tests/abstractprovidingreportermanagertestbase.h \
    tests/misc/proxyreportmanagertestaction.h \
    tests/misc/proxylightmanagertest.h \
    tests/misc/proxylightmanagertestaction.h \
    tests/misc/multiindexprogrammerfacadetest.h \
    tests/misc/multiindexprogrammerfacadetestaction.h \
    tests/misc/addressedhighcvprogranmmerfacadetest.h \
    tests/misc/addressedhighcvprogranmmerfacadetestaction.h \
    tests/misc/opsmodedelayedprogrammerfacadetest.h \
    tests/misc/opsmodedelayedprogrammerfacadetestaction.h \
    tests/misc/verifywriteprogrammerfacadetest.h \
    tests/misc/verifywriteprogrammerfacadetestaction.h \
    tests/misc/twoindextcsprogrammerfacadetest.h \
    tests/misc/twoindextcsprogrammerfacadetestaction.h \
    tests/misc/paneprogpanetest.h \
    tests/misc/paneprogpanetestaction.h \
    tests/misc/paneprogframetest.h \
    tests/misc/decoderfiletest.h \
    tests/misc/paneprogframetestaction.h \
    tests/misc/decoderfiletestaction.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

DEPENDPATH +=  operations tests
INCLUDEPATH +=  operations tests

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

