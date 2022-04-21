#-------------------------------------------------
#
# Project created by QtCreator 2013-03-22T17:32:56
#
#-------------------------------------------------
unix:{
QTSERIALPORT_PROJECT_ROOT = ~/Projects/qtserialportlogixng
}
win32:{
QTSERIALPORT_PROJECT_ROOT =C:/Users/Allen/Projects/qt-qtserialport-stable/qt-qtserialport
}
greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += core widgets gui serialport multimedia websockets testlib #webkitwidgets
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}



win32_msvc: {
 QMAKE_CXXFLAGS += /wd4290
 QMAKE_CFLAGS_DEBUG += /wd4290
}

APPNAME = "JMRI"
APPVERSION = 0.1

PREFIX = /home/allen/pythonqt-code

MOC_DIR = moc_obj
OBJECTS_DIR = moc_obj

#QT       -= gui
QT       += core xml  gui printsupport   sql network  multimedia #webkitwidgets

TARGET = Pr3
TEMPLATE = lib

# Windows and Unix get the suffix "d" to indicate a debug version of the library.
# Mac OS gets the suffix "_debug".
CONFIG(debug, debug|release) {
    win32:      TARGET = $$join(TARGET,,,d)
    mac:        TARGET = $$join(TARGET,,,_debug)
    unix:!mac:  TARGET = $$join(TARGET,,,d)
    MOC_DIR = moc_objd
    OBJECTS_DIR = moc_objd
}

unix{
 isEmpty(PREFIX): PREFIX_USR = /usr
 isEmpty(PREFIX): PREFIX_LOCAL = $${PREFIX_USR}/local
 isEmpty(LIB_INSTALL_DIR): LIB_INSTALL_DIR = $${PREFIX_LOCAL}/lib
 exists($$PWD/../ftdilib/libftdilib.so) {
  isEmpty(FTDI): FTDI = 1
  DEFINES += HAVE_FTDI
  message("libPr3: ftdilib found!")
 }
 exists($$PWD/../QtWebApp/libQtWebAppd.so) {
 isEmpty(WEBAPP): WEBAPP = 1
  DEFINES += QTWEBAPP
  message("libPr3: libQtWebAppd found! define QTWEBAPP is set")
 } else {
  message("libPr3: libQtWebAppd not found! define QTWEBAPP not set")
 }
}

win32{
 isEmpty(PREFIX): PREFIX_USR = "C:/"
 isEmpty(PREFIX): PREFIX_LOCAL = $${PREFIX_USR}QGeomColl
 isEmpty(PREFIX): PREFIX_LOCAL = C:/$${APPNAME}
 isEmpty(DLL_INSTALL_DIR): DLL_INSTALL_DIR = C:/$${APPNAME}build_nr
 exists($$PWD/../ftdilib/debug/ftdilib.dll) {
  isEmpty(FTDI): FTDI = 1
  DEFINES += HAVE_FTDI
  message("libPr3: ftdilib.dll found!")
 }
}

#isEmpty(SECTION_LOGIC): SECTION_LOGIC = 1 # set = 1 to compile Section and Block logic
#isEmpty(LAYOUT_LOGIC): LAYOUT_LOGIC = 0 # set = 1 to compile Layout logic

DEFINES += LIBPR3_LIBRARY
#build_nr.commands = $$PWD/../release/AutoIncreaseBuildNr $$PWD/build_number.h
#build_nr.depends = FORCE
#QMAKE_EXTRA_TARGETS += build_nr
#PRE_TARGETDEPS += build_nr

PROJ_DIR=$$(PROJ_DIR) # get project directory from env
isEmpty( PROJ_DIR ) {
  win32:PROJ_DIR=C:/Projects
  unix:PROJ_DIR=/home/allen/Projects
}

include(../scripts_config.prf)

# NOTE: The PYTHONQT_PREFIX path should be exported in the environment like thi:
# On Unix, "export PYTHON_VERSION=2.7"
# and "export PYTHONQT_PREFIX=/home/allen/Projects/PythonQt/pythonqt-code"
#
#PYTHONQT_PREFIX=$$(PYTHONQT_PREFIX)
#isEmpty( PYTHONQT_PREFIX ) {
#  win32:PYTHONQT_PREFIX=C:/Program Files (x86)/local/lib
#  unix:PYTHONQT_PREFIX=$${PROJ_DIR}/PythonQt/pythonqt-code
#}
#include($$PYTHONQT_PREFIX/build/python.prf)

#win32:exists($$PYTHONQT_PREFIX/lib/PythonQt_d.dll){
#ENABLE_SCRIPTING = "Y"
#}
#unix:exists($$PYTHONQT_PREFIX/lib/libPythonQt-Qt5-Python$${PYTHON_VERSION}_d.so) {
#ENABLE_SCRIPTING = "Y"
# message(libPr3: found $$PYTHONQT_PREFIX/lib/libPythonQt-Qt5-Python$${PYTHON_VERSION}_d.so)
#} else {
# message(libPr3: not found $$PYTHONQT_PREFIX/lib/libPythonQt-Qt5-Python$${PYTHON_VERSION}_d.so)
#}

#message(libPr3: PYTHON_VERSION = $$PYTHON_VERSION)
#message(libPr3: PYTHONQT_PREFIX = $$PYTHONQT_PREFIX)

#CONFIG += scripts
equals(ENABLE_SCRIPTING, "Y") {
    DEFINES += SCRIPTING_ENABLED
}

DEFINES += USE_THREAD

include(../logixng_config.prf)
equals(ENABLE_LOGIXNG, "Y" ) {
   message("libPr3: LogixNG enabled")
} else {
   message("libPr3: LogixNG disabled")
}
SOURCES += \
    Signal/abstractmrnodetrafficcontroller.cpp \
    Signal/abstractnode.cpp \
    Signal/acelaaddress.cpp \
    Signal/acelaconnectiontypelist.cpp \
    Signal/acelanode.cpp \
    Signal/acelareply.cpp \
    Signal/acelasignalhead.cpp \
    Signal/acelasystemconnectionmemo.cpp \
    Signal/acelatrafficcontroller.cpp \
    Signal/lsdecsignalhead.cpp \
    Signal/lsdecsignalheadxml.cpp \
    Signal/mergsd2signalhead.cpp \
    Signal/mergsd2signalheadxml.cpp \
    #Signal/serialsignalhead.cpp \
    abstractanalogiomanager.cpp \
    abstractprovidingproxymanager.cpp \
    abstractproxymanager.cpp \
    acelamessage.cpp \
    acelasignalheadxml.cpp \
    addeditsinglelightcontrolframe.cpp \
    defaultlightcontrol.cpp \
   # direct/defaultthrottle.cpp \
   # direct/defaultthrottlemanager.cpp \
   # direct/directcomponentfactory.cpp \
   # direct/directmenu.cpp \
   # direct/directsystemconnectionmemo.cpp \
   # direct/portcontroller.cpp \
   # direct/serialdriveradapter.cpp \
   # direct/trafficcontroller.cpp \
    internalanalogiomanager.cpp \
    lightcontrolpane.cpp \
    lightcontroltablemodel.cpp \
    lighteditaction.cpp \
    lightintensitypane.cpp \
    loconetmessage.cpp \
    lnconstants.cpp \
    llnmon.cpp \
 logixng/actionblock.cpp \
 logixng/actionblockswing.cpp \
 logixng/actionblockxml.cpp \
 logixng/actionclock.cpp \
 logixng/actionclockswing.cpp \
 logixng/actionclockxml.cpp \
 logixng/actionlistenonbeans.cpp \
 logixng/actionlistenonbeansswing.cpp \
 logixng/actionlistenonbeansxml.cpp \
 logixng/actionlocalvariable.cpp \
 logixng/actionlocalvariableswing.cpp \
 logixng/actionlocalvariablexml.cpp \
 logixng/actionsensorswing.cpp \
 logixng/actionsensorxml.cpp \
 logixng/digitalformulaxml.cpp \
 logixng/holdswing.cpp \
 logixng/ifthenelsexml.cpp \
 logixng/listenonbeanstablemodel.cpp \
 logixng/notxml.cpp \
 logixng/stringexpressionconstantswing.cpp \
    namedbeancombobox.cpp \
    otherconnectiontypelist.cpp \
    serialport.cpp \
    dccmanufacturerlist.cpp \
    lnconnectiontypelist.cpp \
    activeflag.cpp \
    lnportcontroller.cpp \
    lntrafficcontroller.cpp \
    abstractserialportcontroller.cpp \
    abstractportcontroller.cpp \
    lnpacketizer.cpp \
    locobufferadapter.cpp \
    masterthread.cpp \
    locobufferusbadapter.cpp \
    libpr3version.cpp \
    language.cpp \
    dcclocoaddress.cpp \
    slotmanager.cpp \
    abstractprogrammer.cpp \
    loconetslot.cpp \
    sprog/sprogserialdriveradapter.cpp \
    systemconnectionmemomanager.cpp \
    loconetsystemconnectionmemo.cpp \
    abstractpowermanager.cpp \
    lnpowermanager.cpp \
    loconetthrottledtransmitter.cpp \
    lnprogrammermanager.cpp \
    defaultprogrammermanager.cpp \
    abstractturnout.cpp \
    turnout.cpp \
    namedbeanhandlemanager.cpp \
    turnoutoperation.cpp \
    turnoutoperationmanager.cpp \
    abstractturnoutmanager.cpp \
    abstractmanager.cpp \
    lnturnoutmanager.cpp \
    lnturnout.cpp \
    abstractsensor.cpp \
    sensormanager.cpp \
    abstractsensormanager.cpp \
    lnsensormanager.cpp \
    lnsensoraddress.cpp \
    lnsensor.cpp \
    abstractreportermanager.cpp \
    abstractreporter.cpp \
    lnreporter.cpp \
    lnreportermanager.cpp \
    timebase.cpp \
    pr3systemconnectionmemo.cpp \
    proxyreportermanager.cpp \
    proxysensormanager.cpp \
    proxyturnoutmanager.cpp \
    internalsensormanager.cpp \
    internalturnoutmanager.cpp \
    abstractmemory.cpp \
    defaultmemorymanager.cpp \
    abstractmemorymanager.cpp \
    internalreportermanager.cpp \
    Roster/roster.cpp \
    Roster/rosterentry.cpp \
    dcclocoaddressxml.cpp \
    Roster/rosterentrycombobox.cpp \
    Roster/rostergroupcombobox.cpp \
    Roster/rosterentryselectorpanel.cpp \
    turnoutoperator.cpp \
    nofeedbackturnoutoperation.cpp \
    commonturnoutoperation.cpp \
    nofeedbackturnoutoperator.cpp \
    abstractidtag.cpp \
    rfid/rfidreporter.cpp \
    defaultidtagmanager.cpp \
    defaultidtag.cpp \
    defaultshutdownmanager.cpp \
    shutdownmanager.cpp \
    rfid/rfidsensormanager.cpp \
    rfid/rfidsensor.cpp \
    sensor.cpp \
    rfid/rfidreportermanager.cpp \
    abstractthrottle.cpp \
    dccconsist.cpp \
    throttle.cpp \
    dccconsistmanager.cpp \
    abstractthrottlemanager.cpp \
    lnthrottlemanager.cpp \
    proglistener.cpp \
    rfid/rfidusb.cpp \
    defaultroutemanager.cpp \
    defaultroute.cpp \
    decimalformat.cpp \
    blockvaluefile.cpp \
    abstractlightmanager.cpp \
    lnlightmanager.cpp \
    lnlight.cpp \
    abstractlight.cpp \
    proxylightmanager.cpp \
    internallightmanager.cpp \
    loconetconsistmanager.cpp \
    lnclockcontrol.cpp \
    defaultclockcontrol.cpp \
    abstractconsistmanager.cpp \
    abstractvariablelight.cpp \
    simpletimebase.cpp \
    loconetthrottle.cpp \
    Throttle/throttlewindow.cpp \
    Roster/locofile.cpp \
    Roster/cvtablemodel.cpp \
    Roster/abstractvalue.cpp \
    Roster/cvvalue.cpp \
    Roster/variabletablemodel.cpp \
    Roster/variablevalue.cpp \
    Roster/abstractqualifier.cpp \
    Roster/valuequalifier.cpp \
    Roster/enumvariablevalue.cpp \
    Roster/compositevariablevalue.cpp \
    Roster/decvariablevalue.cpp \
    Roster/hexvariablevalue.cpp \
    Roster/longaddrvariablevalue.cpp \
    Roster/shortaddrvariablevalue.cpp \
    Roster/speedtablevarvalue.cpp \
    Roster/splitvariablevalue.cpp \
    Roster/constantvalue.cpp \
    Roster/qualifiercombiner.cpp \
    Roster/decoderfile.cpp \
    Roster/resettablemodel.cpp \
    Roster/combocheckbox.cpp \
    Roster/comboradiobuttons.cpp \
    Roster/decvarslider.cpp \
    Roster/comboonradiobutton.cpp \
    Roster/combooffradiobutton.cpp \
    Roster/rosterentrypane.cpp \
    Roster/decoderindexfile.cpp \
    Roster/busyglasspane.cpp \
    Roster/dccaddresspanel.cpp \
    Roster/paneprogpane.cpp \
    Roster/watchinglabel.cpp \
    Roster/fnmappanel.cpp \
    Roster/paneprogframe.cpp \
    Roster/paneopsprogframe.cpp \
    Roster/rosterframe.cpp \
    connectionstatus.cpp \
    Roster/abstractidentify.cpp \
    Roster/identifyloco.cpp \
    Roster/dcclocoaddressselector.cpp \
    Roster/factoryresetaction.cpp \
    Roster/optionsdialog.cpp \
    Signal/defaultsignalhead.cpp \
    Signal/abstractsignalhead.cpp \
    Signal/abstractsignalheadmanager.cpp \
    Signal/defaultsignalmastlogic.cpp \
    Signal/signalmastlogic.cpp \
    Signal/signalspeedmap.cpp \
    Signal/defaultsignalappearancemap.cpp \
    Signal/defaultsignalmastmanager.cpp \
    Signal/signalheadsignalmast.cpp \
    Signal/abstractsignalmast.cpp \
    Signal/defaultsignalsystem.cpp \
    Signal/defaultsignalsystemmanager.cpp \
    Signal/se8csignalhead.cpp \
    Signal/defaultsignalmastlogicmanager.cpp \
    Signal/singleturnoutsignalhead.cpp \
    Signal/doubleturnoutsignalhead.cpp \
    Signal/virtualsignalhead.cpp \
    Signal/turnoutsignalmast.cpp \
    Signal/virtualsignalmast.cpp \
    Signal/addsignalmastpanel.cpp \
    sensorturnoutoperator.cpp \
    Signal/signalmastrepeater.cpp \
    defaultlogix.cpp \
    jmrisimplepropertylistener.cpp \
    defaultlogixmanager.cpp \
    conditionalvariable.cpp \
    conditionalmanager.cpp \
    jmritwostatepropertylistener.cpp \
    jmriclockpropertylistener.cpp \
    jmrimultistatepropertylistener.cpp \
    conditional.cpp \
    defaultconditionalmanager.cpp \
    defaultconditional.cpp \
    sensorgroupconditional.cpp \
    defaultconditionalaction.cpp \
    connectionnamefromsystemname.cpp \
    oblock.cpp \
    portal.cpp \
    warrant.cpp \
    blockorder.cpp \
    opath.cpp \
    throttlesetting.cpp \
    oblockmanager.cpp \
    engineer.cpp \
    warrantmanager.cpp \
    entryexitpairs.cpp \
    source.cpp \
    pointdetails.cpp \
    destinationpoints.cpp \
    Throttle/throttleslistpanel.cpp \
    memory.cpp \
    timeunit.cpp \
    pushbuttonpacket.cpp \
    rawturnoutoperation.cpp \
    sensorturnoutoperation.cpp \
    Signal/tripleturnoutsignalhead.cpp \
    Signal/quadoutputsignalhead.cpp \
    timertask.cpp \
    Signal/defaultsignalgroupmanager.cpp \
    Signal/defaultsignalgroup.cpp \
    Throttle/throttlestablemodel.cpp \
    Throttle/throttlestablecellrenderer.cpp \
    Roster/rostericonfactory.cpp \
    Throttle/throttleframemanager.cpp \
    Throttle/addresspanel.cpp \
    Roster/nceconsistroster.cpp \
    Roster/nceconsistrosterentry.cpp \
    Throttle/throttleframepropertyeditor.cpp \
    Throttle/throttlecreationaction.cpp \
    Throttle/powermanagerbutton.cpp \
    Throttle/smallpowermanagerbutton.cpp \
    Throttle/largepowermanagerbutton.cpp \
    Throttle/controlpanel.cpp \
    Throttle/functionpanel.cpp \
    Throttle/functionbutton.cpp \
    Roster/createrostergroupaction.cpp \
    Roster/rostermenu.cpp \
    Roster/panenewprogaction.cpp \
    Roster/paneeditaction.cpp \
    Roster/locoselpane.cpp \
    Roster/knownlocoselpane.cpp \
    Roster/progdefault.cpp \
    Roster/xmlfilenamefilter.cpp \
    Roster/locoseltreepane.cpp \
    Roster/combinedlocoseltreepane.cpp \
    Roster/combinedlocoselpane.cpp \
    Roster/globalrosterentrycombobox.cpp \
    Roster/identifydecoder.cpp \
    Roster/copyrosteritemaction.cpp \
    Roster/abstractrosteritemaction.cpp \
    Roster/deleterosteritemaction.cpp \
    Roster/rosterframeaction.cpp \
    Roster/paneserviceprogframe.cpp \
    Roster/progmodeselector.cpp \
    Roster/progservicemodecombobox.cpp \
    Roster/simpleprogaction.cpp \
    Roster/simpleprogframe.cpp \
    Roster/progmodepane.cpp \
    Roster/progservicemodepane.cpp \
    Roster/progopsmodepane.cpp \
    Roster/paneprogaction.cpp \
    Roster/paneopsprogaction.cpp \
    LocoIO/cmdstnconfigpane.cpp \
    LocoIO/lncommandstationtype.cpp \
    Roster/qualifieradder.cpp \
    Roster/field.cpp \
    Roster/fnmappanelesu.cpp \
    Roster/arithmeticqualifier.cpp \
    Roster/jcomponentqualifier.cpp \
    Roster/dccaddressvarhandler.cpp \
    Roster/printaction.cpp \
    Roster/printcvaction.cpp \
    Roster/printrosterentry.cpp \
    lnopsmodeprogrammer.cpp \
    programmingmode.cpp \
    abstractserialconnectionconfig.cpp \
    loconet/Pr3/pr3connectionconfig.cpp \
    pr3adapter.cpp \
    Roster/twoindexprogrammerfacade.cpp \
    Roster/accessoryopsmodeprogrammerfacade.cpp \
    Roster/abstractprogrammerfacade.cpp \
    Roster/programmerfacadeselector.cpp \
    Roster/multiindexprogrammerfacade.cpp \
    loconet/Locobuffer/locobufferconnectionconfig.cpp \
    loconet/LocobufferUsb/locobufferusbconnectionconfig.cpp \
    loconet/LocobufferUsb/locobufferusbconnectionconfigxml.cpp \
    loconet/Locobuffer/locobufferconnectionconfigxml.cpp \
    resourcebundle.cpp \
    loconet/HexFile/hexfileserver.cpp \
    loconet/HexFile/hexfileframe.cpp \
    loconet/HexFile/lnhexfileport.cpp \
    loconet/HexFile/debugprogrammermanager.cpp \
    loconet/HexFile/debugthrottlemanager.cpp \
    loconet/HexFile/debugthrottle.cpp \
    nmraconsistmanager.cpp \
    nmraconsist.cpp \
    loconet/HexFile/progdebugger.cpp \
    loconet/HexFile/hexfileconnectionconfigxml.cpp \
    loconet/HexFile/hexfileconnectionconfig.cpp \
    abstractsimulatorconnectionconfig.cpp \
    jmriuserpreferencesmanager.cpp \
    preferencesmanager.cpp \
    abstractpreferencesmanager.cpp \
    audiocommand.cpp \
    abstractaudiothread.cpp \
    defaultaudiomanager.cpp \
    abstractaudiomanager.cpp \
    audio.cpp \
    abstractaudio.cpp \
    abstractaudiobuffer.cpp \
    nullaudiofactory.cpp \
    abstractaudiofactory.cpp \
    nullaudiosource.cpp \
    nullaudiobuffer.cpp \
    nullaudiolistener.cpp \
    abstractaudiolistener.cpp \
    abstractaudiosource.cpp \
    audiocommandthread.cpp \
    audiosource.cpp \
    qtsoundaudiofactory.cpp \
    qtsoundaudiobuffer.cpp \
    audioinputstream.cpp \
    audiosystem.cpp \
    wavfilereader.cpp \
    qtsoundaudiosource.cpp \
    qtsoundaudiolistener.cpp \
    floatcontrol.cpp \
    clip.cpp \
    dataline.cpp \
    line.cpp \
    mixer.cpp \
    audiofileformat.cpp \
    audioformat.cpp \
    LocoIO/locostatspanel.cpp \
    LocoIO/jmrinamedpaneaction.cpp \
    LocoIO/lnnamedpaneaction.cpp \
    LocoIO/slotmonpane.cpp \
    LocoIO/abstractboardprogpanel.cpp \
    LocoIO/ds64panel.cpp \
    LocoIO/clockmonpane.cpp \
    LocoIO/locoidpanel.cpp \
    messagepanel.cpp \
    lnmessagemanager.cpp \
    pr3selectpane.cpp \
    loaderpane.cpp \
    memorycontents.cpp \
    loconet/lnovertcppacketizer.cpp \
    loconet/lnnetworkportcontroller.cpp \
    abstractnetworkportcontroller.cpp \
    loconet/lntcpdriveradapter.cpp \
    loconet/jmriserver.cpp \
    loconet/clientrxhandler.cpp \
    loconet/LnOverTcp/lnovertcpconnectionconfig.cpp \
    abstractnetworkconnectionconfig.cpp \
    abstractnetworkconnectionconfigxml.cpp \
    loconet/LnOverTcp/lnovertcpconnectionconfigxml.cpp \
    Roster/importrosteritemaction.cpp \
    Roster/exportrosteritemaction.cpp \
    Roster/deleterostergroupaction.cpp \
    Roster/rosterentrytogroupaction.cpp \
    Roster/removerosterentrytogroupaction.cpp \
    Roster/rostergrouptableaction.cpp \
    Roster/rostergrouptablemodel.cpp \
    Roster/rostergrouptableframe.cpp \
    Roster/fullbackupexportaction.cpp \
    Roster/fullbackupimportaction.cpp \
    Roster/speedprofilepanel.cpp \
    Roster/rosterspeedprofile.cpp \
    Roster/speedprofileframe.cpp \
    Roster/speedprofileaction.cpp \
    loconet/soundloaderpane.cpp \
    loconet/loaderengine.cpp \
    loconet/spjfile.cpp \
    loconet/sdfbuffer.cpp \
    loconet/sdfmacro.cpp \
    loconet/channelstart.cpp \
    loconet/skemestart.cpp \
    loconet/sdlversion.cpp \
    loconet/endsound.cpp \
    loconet/generatetrigger.cpp \
    loconet/sdfconstants.cpp \
    loconet/delaysound.cpp \
    loconet/twobytemacro.cpp \
    loconet/fourbytemacro.cpp \
    loconet/skipontrigger.cpp \
    loconet/initiatesound.cpp \
    loconet/play.cpp \
    loconet/maskcompare.cpp \
    loconet/loadmodifier.cpp \
    loconet/branchto.cpp \
    loconet/editorfilepane.cpp \
    loconet/editortabledatamodel.cpp \
    loconet/editorpane.cpp \
    loconet/wavbuffer.cpp \
    loconet/editorframe.cpp \
    loconet/sdfeditorpane.cpp \
    loconet/sdfmacroeditor.cpp \
    loconet/monitoringlabel.cpp \
    loconet/defaultmutabletreemodel.cpp \
    loconet/channelstarteditor.cpp \
    loconet/sdlversioneditor.cpp \
    loconet/skemestarteditor.cpp \
    loconet/generatetriggereditor.cpp \
    loconet/initiatesoundeditor.cpp \
    loconet/loadmodifiereditor.cpp \
    loconet/playeditor.cpp \
    loconet/maskcompareeditor.cpp \
    loconet/branchtoeditor.cpp \
    loconet/endsoundeditor.cpp \
    loconet/delaysoundeditor.cpp \
    loconet/skipontriggereditor.cpp \
    loconet/twobytemacroeditor.cpp \
    loconet/fourbytemacroeditor.cpp \
    loconet/qtsoundaudioclip.cpp \
    loconet/loconetmsgdialog.cpp \
    loconet/querycvdialog.cpp \
    loconet/loconetmenu.cpp \
    Throttle/throttleslistaction.cpp \
    Roster/rostergroupspanel.cpp \
    Roster/decoderindexcreateaction.cpp \
    Roster/updatedecoderdefinitionaction.cpp \
    Roster/recreaterosteraction.cpp \
    Roster/rostergroup.cpp \
    Roster/paneprogdp3action.cpp \
    Roster/printrosteraction.cpp \
    Roster/copyrostergroupaction.cpp \
    Roster/renamerostergroupaction.cpp \
    Roster/installdecoderfileaction.cpp \
    Roster/installdecoderurlaction.cpp \
    Signal/dccsignalmast.cpp \
    deferringprogrammermanager.cpp \
    vsdecodermanager.cpp \
    vsdecoderpreferences.cpp \
    listeningspot.cpp \
    vsdlistener.cpp \
    addressedhighcvprogrammerfacade.cpp \
    vsdecodermanagerthread.cpp \
    vsdecoder.cpp \
    vsdmanagerframe.cpp \
    vsdconfig.cpp \
    vsdfile.cpp \
    zipfile.cpp \
    vsdsound.cpp \
    vsdecoderevent.cpp \
    trigger.cpp \
    soundevent.cpp \
    momentarysoundevent.cpp \
    togglesoundevent.cpp \
    enginesoundevent.cpp \
    configurablesound.cpp \
    steamsound.cpp \
    enginesound.cpp \
    dieselsound.cpp \
    diesel3sound.cpp \
    buttontrigger.cpp \
    enginepane.cpp \
    dieselpane.cpp \
    soundbite.cpp \
    notchtransition.cpp \
    audioutil.cpp \
    triggerlistener.cpp \
    booltrigger.cpp \
    throttletrigger.cpp \
    floattrigger.cpp \
    notchtrigger.cpp \
    inttrigger.cpp \
    control.cpp \
    managerdefaultselector.cpp \
    managerdefaultselectorxml.cpp \
    path.cpp \
    block.cpp \
    beansetting.cpp \
    blockmanager.cpp \
    entrypoint.cpp \
    reportcontext.cpp \
    rostertablemodel.cpp \
    Roster/imagedelegate.cpp \
    Throttle/functionbuttonpropertyeditor.cpp \
    internalsystemconnectionmemo.cpp \
    defaultpowermanager.cpp \
    Roster/namecheckaction.cpp \
    Roster/progcheckaction.cpp \
    Roster/namefile.cpp \
    Throttle/stopallbutton.cpp \
    Throttle/serversocket.cpp \
    Json/jsonserverpreferences.cpp \
    Json/jsonserverpreferencespanel.cpp \
    WiThrottle/abstractcontroller.cpp \
    WiThrottle/abstractwithrottlepreferences.cpp \
    WiThrottle/consistcontroller.cpp \
    WiThrottle/consistfunctioncontroller.cpp \
    WiThrottle/controllerfilteraction.cpp \
    WiThrottle/controllerfilterframe.cpp \
    WiThrottle/deviceserver.cpp \
    WiThrottle/multithrottle.cpp \
    WiThrottle/multithrottlecontroller.cpp \
    WiThrottle/routecontroller.cpp \
    WiThrottle/throttlecontroller.cpp \
    WiThrottle/trackpowercontroller.cpp \
    WiThrottle/turnoutcontroller.cpp \
    WiThrottle/userinterface.cpp \
    WiThrottle/wificonsist.cpp \
    WiThrottle/wificonsistfile.cpp \
    WiThrottle/wificonsistmanager.cpp \
    WiThrottle/withrottlecreationaction.cpp \
    WiThrottle/withrottlemanager.cpp \
    WiThrottle/withrottlepreferences.cpp \
    WiThrottle/withrottleprefspanel.cpp \
    WiThrottle/withrottleslistmodel.cpp \
    Throttle/consistfile.cpp \
    Json/jsonthrottle.cpp \
    Json/jsonthrottlemanager.cpp \
    Json/jsonthrottlesocketservice.cpp \
    Json/jsonqt.cpp \
    Web/jmriconnection.cpp \
    Json/jsonconnection.cpp \
    Json/jsonexception.cpp \
    Json/jsonsensorsocketservice.cpp \
    Json/jsonsensorhttpservice.cpp \
    Json/jsonnamedbeanhttpservice.cpp \
    Json/jsonsensor.cpp \
    Json/jsonclienthandler.cpp \
    Json/jsonthrottleservicefactory.cpp \
    Json/jsonsensorservicefactory.cpp \
    Json/jsonutilservicefactory.cpp \
    Json/jsonutilsocketservice.cpp \
    Json/jsonutilhttpservice.cpp \
    Json/jsonpowerhttpservice.cpp \
    Json/jsonpowersocketservice.cpp \
    Json/jsonturnouthttpservice.cpp \
    Json/jsonturnoutsocketservice.cpp \
    Json/jsonturnoutservicefactory.cpp \
    Json/jsonpowerservicefactory.cpp \
    Json/jsontimeservicefactory.cpp \
    Json/jsontimesocketservice.cpp \
    Json/jsontimehttpservice.cpp \
    Json/jsonrosterhttpservice.cpp \
    Json/jsonroster.cpp \
    Json/jsonrosterservicefactory.cpp \
    Json/jsonrostersocketservice.cpp \
    Web/webserver.cpp \
    Web/webserveraction.cpp \
    Web/requesthandler.cpp \
    Web/httpservlet.cpp \
    Web/genericservlet.cpp \
    Web/servletexception.cpp \
    Json/jsonwebsocket.cpp \
    Web/httpservletrequest.cpp \
    Web/servletoutputstream.cpp \
    Web/servletcontext.cpp \
    Web/rosterservlet.cpp \
    Web/servletutil.cpp \
    Web/httpservletresponse.cpp \
    Web/servletrequest.cpp \
    Web/configservlet.cpp \
    Web/jmrijframeservlet.cpp \
    Web/homeservlet.cpp \
    Web/denialservlet.cpp \
    Web/redirectionservlet.cpp \
    Web/abstractpanelservlet.cpp \
    Web/panelservlet.cpp \
    Web/controlpanelservlet.cpp \
    Web/layoutpanelservlet.cpp \
    Web/directoryhandler.cpp \
    Web/directoryresource.cpp \
    Web/resource.cpp \
    Web/resourcehandler.cpp \
    Web/uriutil.cpp \
    Json/jsonblock.cpp \
    Json/jsonblockhttpservice.cpp \
    Json/jsonblockservicefactory.cpp \
    Json/jsonblocksocketservice.cpp \
    Json/jsonservlet.cpp \
    Web/websocketservlet.cpp \
    Web/messagedigest.cpp \
    Web/messagedigestspi.cpp \
    Web/websocketservletfactory.cpp \
    Json/jsonlightservicefactory.cpp \
    Json/jsonlightsocketservice.cpp \
    Json/jsonlighthttpservice.cpp \
    Json/jsonlayoutblock.cpp \
    Json/jsonlayoutblockhttpservice.cpp \
    Json/jsonlayoutblockservicefactory.cpp \
    Json/jsonlayoutblocksocketservice.cpp \
    Json/jsonmemory.cpp \
    Json/jsonmemoryhttpservice.cpp \
    Json/jsonmemorysocketservice.cpp \
    Json/jsonmemoryservicefactory.cpp \
    Json/jsonsignalhead.cpp \
    Json/jsonsignalheadhttpservice.cpp \
    Json/jsonsignalheadservicefactory.cpp \
    Json/jsonsignalheadsocketservice.cpp \
    Json/jsonsignalmast.cpp \
    Json/jsonsignalmasthttpservice.cpp \
    Json/jsonsignalmastservicefactory.cpp \
    Json/jsonsignalmastsocketservice.cpp \
    Json/jsonreporter.cpp \
    Json/jsonreporterhttpservice.cpp \
    Json/jsonreportersocketservice.cpp \
    Json/jsonreporterservicefactory.cpp \
    Json/jsonserver.cpp \
    Json/jsonserveraction.cpp \
    Web/operationsservlet.cpp \
    Json/jsonoperations.cpp \
    Json/jsonutil.cpp \
    Json/jsonoperationsservicefactory.cpp \
    Json/jsonoperationssocketservice.cpp \
    Json/jsonoperationshttpservice.cpp \
    Web/htmltraincommon.cpp \
    Web/htmlmanifest.cpp \
    Json/jsonmanifest.cpp \
    Web/htmlconductor.cpp \
    Json/jsonconsisthttpservice.cpp \
    Json/jsonconsistmanager.cpp \
    Json/jsonconsistservicefactory.cpp \
    Json/jsonconsistsocketservice.cpp \
    Web/defaultservletcontext.cpp \
    Web/defaultservletconfig.cpp \
    Web/stringescapeutils.cpp \
    Throttle/windowpreferences.cpp \
    Throttle/locoaddressxml.cpp \
    loconetmenustartupaction.cpp \
    Web/aboutservlet.cpp \
    sprog/sprogportcontroller.cpp \
    sprog/sprogsystemconnectionmemo.cpp \
    sprog/sprogtrafficcontroller.cpp \
    sprog/sprogmessage.cpp \
    abstractmrmessage.cpp \
    abstractmessage.cpp \
    sprog/sprogreply.cpp \
    sprog/sprogtype.cpp \
    abstractconnectionconfig.cpp \
    sprog/sprogconnectionconfig.cpp \
    sprog/sprogconnectiontypelist.cpp \
    sprog/sprogversion.cpp \
    sprog/sprogprogrammermanager.cpp \
    sprog/sprogpowermanager.cpp \
    sprog/sprogversionquery.cpp \
    sprog/sprogcomponentfactory.cpp \
    sprog/sprogprogrammer.cpp \
    sprog/sprogcommandstation.cpp \
    sprog/sprogslot.cpp \
    sprog/sproginterface.cpp \
    abstractmrreply.cpp \
    sprog/sprogconnectionconfigxml.cpp \
    sprog/sprogcsserialdriveradapter.cpp \
    sprog/sprogcsconnectionconfigxml.cpp \
    sprog/sprogcsconnectionconfig.cpp \
    sprog/sprogturnout.cpp \
    sprog/sprogthrottle.cpp \
    sprog/sprogthrottlemanager.cpp \
    sprog/sprogturnoutmanager.cpp \
    sprog/sprogcsturnout.cpp \
    sprog/sprogcsthrottlemanager.cpp \
    sprog/sprogcsthrottle.cpp \
    sprog/sprogversionlistener.cpp \
    sprog/sprogslotlistener.cpp \
    sprog/sprogcsmenu.cpp \
    sprog/sprogconsoleaction.cpp \
    sprog/sprogconsoleframe.cpp \
    sprog/sprogversionaction.cpp \
    sprog/sprogversionframe.cpp \
    sprog/sprogmenu.cpp \
    loconet/lncomponentfactory.cpp \
    abstractmrtrafficcontroller.cpp \
    sprog/sprogpacketgenframe.cpp \
    sprog/sprogpacketgenaction.cpp \
    sprog/sprogmonframe.cpp \
    sprog/sprogmonaction.cpp \
    sprog/pisprognanoserialdriveradapter.cpp \
    sprog/sprogupdateframe.cpp \
    sprog/sprogiiupdateframe.cpp \
    sprog/sprogiiupdateaction.cpp \
    sprog/sprogupdateaction.cpp \
    sprog/sproghexfile.cpp \
    sprog/sprogslotmonaction.cpp \
    sprog/sprogslotmonframe.cpp \
    sprog/sprogslotmondatamodel.cpp \
    Roster/opsmodedelayedprogrammerfacade.cpp \
    loconet/csopswaccess.cpp \
    verifywriteprogrammerfacade.cpp \
    Roster/csvimportaction.cpp \
    Roster/genericimportaction.cpp \
    Roster/csvimporter.cpp \
    Roster/csvexportaction.cpp \
    Roster/offsethighcvprogrammerfacade.cpp \
    Roster/resettingoffsethighcvprogrammerfacade.cpp \
    Throttle/storexmlthrottleslayoutaction.cpp \
    Throttle/storedefaultxmlthrottleslayoutaction.cpp \
    Throttle/loadxmlthrottleslayoutaction.cpp \
    Throttle/loaddefaultxmlthrottleslayoutaction.cpp \
    Throttle/speedpanel.cpp \
    Throttle/backgroundpanel.cpp \
    Roster/functionlabelpane.cpp \
    Throttle/controlpanelpropertyeditor.cpp \
    Roster/loconetconsist.cpp \
    loconet/LnOverTcp/lntcppreferences.cpp \
    loconet/lntcppreferencespanel.cpp \
    loconet/lntcpserver.cpp \
    loconet/lntcpserverframe.cpp \
    loconet/lntcpserveraction.cpp \
    lnsv2messagecontents.cpp \
    loconet/loconetmessageinterpret.cpp \
    internalconsistmanager.cpp \
    powermanager.cpp \
    Signal/signalmastaddpane.cpp \
    Signal/dccsignalmastaddpane.cpp \
    Signal/lncpsignalmast.cpp \
    Signal/turnoutsignalmastaddpane.cpp \
    Signal/virtualsignalmastaddpane.cpp \
    Signal/signalheadsignalmastaddpane.cpp \
    Signal/matrixsignalmast.cpp \
    Signal/matrixsignalmastxml.cpp \
    Signal/matrixsignalmastaddpane.cpp \
    Signal/dccsignalheadxml.cpp \
    warrantshutdowntask.cpp \
    mergeprompt.cpp \
    Signal/dccsignalhead.cpp \
    Signal/tripleoutputsignalhead.cpp \
    Signal/tripleoutoutsignalheadxml.cpp \
    loconet/PR2/pr2adapter.cpp \
    loconet/PR2/pr2systemconnectionmemo.cpp \
    loconet/PR2/lnpr2powermanager.cpp \
    loconet/PR2/lnpr2throttlemanager.cpp \
    loconet/PR2/pr2throttle.cpp \
    loconet/PR2/pr2connectionconfig.cpp \
    loconet/PR2/pr2connectionconfigxml.cpp \
    loconet/PR2/lnpr2packetizer.cpp \
    rfid/rfidtrafficcontroller.cpp \
    rfid/rfidsystemconnectionmemo.cpp \
    rfid/rfidcomponentfactory.cpp \
    rfid/rfidmenu.cpp \
    rfid/rfidnamedpaneaction.cpp \
    rfid/rfidconnectiontypelist.cpp \
    rfid/standalonetrafficcontroller.cpp \
    rfid/rfidprotocol.cpp \
    rfid/standalonereply.cpp \
    rfid/rfidreply.cpp \
    rfid/rfidreportermanagerxml.cpp \
    rfid/rfidsensormanagerxml.cpp \
    rfid/rfidserialconnectionconfigxml.cpp \
    rfid/rfidserialconnectionconfig.cpp \
    rfid/rfidserialdriveradapter.cpp \
    rfid/standalonesensormanager.cpp \
    rfid/standalonereportermanager.cpp \
    rfid/timeoutrfidreporter.cpp \
    rfid/rfidportcontroller.cpp \
    rfid/coreidrfidprotocol.cpp \
    rfid/timeoutrfidsensor.cpp \
    rfid/rfidmessage.cpp \
    rfid/olimexrfidprotocol.cpp \
    rfid/id12larfidprotocol.cpp \
    rfid/standalonemessage.cpp \
    stacknxpanel.cpp \
    sound.cpp \
    mixerprovider.cpp \
    jmriclient/jmriclientportcontroller.cpp \
    jmriclient/jmriclientsystemconnectionmemo.cpp \
    jmriclient/jmriclienttrafficcontroller.cpp \
    jmriclient/jmriclientmessage.cpp \
    jmriclient/jmriclientreply.cpp \
    jmriclient/networkdriveradapter.cpp \
    zeroconfclient.cpp \
    zeroconfservice.cpp \
    zeroconfserviceevent.cpp \
    jmriclient/jmriclientconnectionconfig.cpp \
    jmriclient/jmriclientconnectionconfigxml.cpp \
    jmriclientconnectiontypelist.cpp \
    jmriclient/jmriclientpowermanager.cpp \
    jmriclient/jmriclientturnoutmanagerxml.cpp \
    jmriclient/jmriclientturnoutmanager.cpp \
    jmriclient/jmriclientsensormanagerxml.cpp \
    jmriclient/jmriclientsensormanager.cpp \
    jmriclient/jmriclientsensor.cpp \
    jmriclient/jmriclientturnout.cpp \
    jmriclient/jmriclientlight.cpp \
    jmriclient/jmriclientlightmanager.cpp \
    jmriclient/jmriclientlightmanagerxml.cpp \
    jmriclient/jmriclientreporter.cpp \
    jmriclient/jmriclientreportermanager.cpp \
    jmriclient/jmriclientreportermanagerxml.cpp \
    simpleserver.cpp \
    simpleservermanager.cpp \
    simpleserveraction.cpp \
    simpleserverpreferences.cpp \
    abstractserverpreferences.cpp \
    simpleservermenu.cpp \
    simpleserver/abstractpowerserver.cpp \
    simpleserver/simplepowerserver.cpp \
    simpleserver/abstractsensorserver.cpp \
    simpleserver/abstractturnoutserver.cpp \
    simpleserver/simpleturnoutserver.cpp \
    simpleserver/simplesensorserver.cpp \
    jmriclient/jmriclientcomponentfactory.cpp \
    jmriclient/jmriclientmenu.cpp \
    jmriclient/jmriclientmonpane.cpp \
    jmriclient/packetgenaction.cpp \
    jmriclient/packetgenframe.cpp \
    servermenu.cpp \
    jmrisrcpservermenu.cpp \
    jmrisrcpserveraction.cpp \
    jmrisrcpservermanager.cpp \
    jmrisrcpserverpreferences.cpp \
    jmrisrcpserver.cpp \
    loconet/lnmessageserveraction.cpp \
    simpleserver/abstractlightserver.cpp \
    simpleserver/simplelightserver.cpp \
    simpleserver/abstractsignalheadserver.cpp \
    simpleserver/simplesignalheadserver.cpp \
    simpleserver/abstractreporterserver.cpp \
    simpleserver/simplereporterserver.cpp \
    lnpacketizerstrict.cpp \
    loconet/lntrafficrouter.cpp \
    consistpreferencesmanager.cpp \
    speedstepmode.cpp \
    rfid/defaultidtagmanagerxml.cpp \
    rfid/transpondingtagmanager.cpp \
    rfid/conflictingsystemconnectionmemo.cpp \
    rfid/transpondingtag.cpp \
    rfid/proxyidtagmanager.cpp \
    rfid/abstractidtagreporter.cpp \
    rfid/idtaglistener.cpp \
    loconet/lndeferprogrammer.cpp \
    proxyturnoutmanagerxml.cpp \
    proxysensormanagerxml.cpp \
#    namedbeancombobox.cpp \
    trackreporter.cpp \
    loconet/bluetooth/loconetbluetoothadapter.cpp \
    scwarrant.cpp \
    Roster/rosterframestartupactionfactory.cpp \
    rostergroupselector.cpp \
    Roster/rostermediapane.cpp \
    loconet/Pr4/pr4adapter.cpp \
    loconet/Pr4/pr4systemconnectionmemo.cpp \
    loconet/Pr4/pr4selectpane.cpp \
    loconet/Pr4/pr4connectionconfig.cpp \
    loconet/Pr4/pr4connectionconfigxml.cpp \
    consisttable.cpp \
    loconet/Pr3/pr3connectionconfigxml.cpp \
    loconet/HexFile/hexfilesystemconnectionmemo.cpp \
    multimeter.cpp \
    abstractmultimeter.cpp \
    loconet/lnmultimeter.cpp \
    loconet/locostatsfunc.cpp \
    loconet/rawstatus.cpp \
    loconet/LocoBufferII/locobufferiistatus.cpp \
    loconet/PR2/pr2status.cpp \
    loconet/pr3ms100modestatus.cpp \
    loconet/DCS240/dcs240connectionconfig.cpp \
    loconet/DCS240/usbdcs240adapter.cpp \
    loconet/DCS240/dcs240connectionconfigxml.cpp \
    loconet/DCS240/usbdcs240systemconnectionmemo.cpp \
    loconet/LocoBufferII/locobufferiiadapter.cpp \
    loconet/LocoBufferII/locobufferiiconnectionconfig.cpp \
    loconet/LocoBufferII/locobufferiiconnectionconfigxml.cpp \
    loconet/DCS52/dcs52usbmodeselectpane.cpp \
    loconet/lnpanel.cpp \
    loconet/DCS240/dcs240usbmodeselectpane.cpp \
    loconet/DCS52/dcs52connectionconfig.cpp \
    loconet/DCS52/dcs52connectionconfigxml.cpp \
    loconet/DCS52/usbdcs52adapter.cpp \
    loconet/DCS52/usbdcs52systemconnectionmemo.cpp \
    defaultcabsignal.cpp \
    abstractcabsignalmanager.cpp \
    loconet/lncabsignalmanager.cpp \
    loconet/lncabsignal.cpp \
    hasconnectionbutunabletoconnectexception.cpp \
    cabsignaltablemodel.cpp \
    defaultcabsignalmanager.cpp \
    timerutil.cpp \
    cabsignalpane.cpp \
    cabsignalaction.cpp \
    zeroconfservicemanager.cpp \
    zeroconfpreferences.cpp \
    logix/learnthrottleframe.cpp \
    defaultsystemconnectionmemo.cpp \
    lnpredefinedmeters.cpp \
    meterupdatetask.cpp \
    loconet/lnmeterinittask.cpp \
    abstractanalogio.cpp \
    defaultmeter.cpp \
    loconet/lniplimplementation.cpp \
    loconet/lndplxgrpinfoimpl.cpp \
    meterframe.cpp \
    meterframemanager.cpp \
    meterframemanagerxml.cpp \
    meteraction.cpp \
    proxymetermanager.cpp \
    internalmetermanager.cpp \
    abstractmetermanager.cpp \
    internalmetermanagerxml.cpp \
    abstractmetermanagerxml.cpp \
    ctc/nbhsensor.cpp \
    ctc/ctcexception.cpp \
    ctc/ctcexceptionbuffer.cpp \
    ctc/ctcmanager.cpp \
    ctc/projectscommonsubs.cpp \
    ctc/programproperties.cpp \
    ctc/ctcserialdata.cpp \
    ctc/nbhsignal.cpp \
    ctc/nbhturnout.cpp \
    ctc/otherdata.cpp \
    ctc/codebuttonhandlerdata.cpp \
    ctc/trafficlockingdata.cpp \
    ctc/frmtrl_rules.cpp \
    ctc/ctcfiles.cpp \
    ctc/callondata.cpp \
    ctc/topologyinfo.cpp \
    ctc/commonsubs.cpp \
    ctc/awtwindowproperties.cpp \
    ctc/checkjmriobject.cpp \
    ctc/ctcmain.cpp \
    ctc/codebuttonhandler.cpp \
    ctc/lockedroutesmanager.cpp \
    ctc/turnoutlock.cpp \
    ctc/ctceditoraction.cpp \
    ctc/frmmainform.cpp \
    ctc/columns.cpp \
    ctc/frmswdi.cpp \
    ctc/codebuttonhandlerdataroutines.cpp \
    ctc/ctcrunaction.cpp \
    ctc/ctcmanagerxml.cpp \
    ctc/frmaddmodifyctccolumn.cpp \
    ctc/frmcb.cpp \
    ctc/frmabout.cpp \
    ctc/frmguidesign.cpp \
    ctc/frmco.cpp \
    ctc/importexternaldata.cpp \
    ctc/importotherdata.cpp \
    ctc/importcodebuttonhandlerdata.cpp \
    ctc/callonentry.cpp \
    ctc/trafficlockingentry.cpp \
    ctc/createguiobjectsxmlfile.cpp \
    ctc/frmdefaults.cpp \
    ctc/frmdebugging.cpp \
    ctc/frmsidi.cpp \
    ctc/frmswdl.cpp \
    ctc/frmtrl.cpp \
    ctc/topology.cpp \
    ctc/frmsidl.cpp \
    ctc/frmtul.cpp \
    ctc/frmil.cpp \
    ctc/frmfleeting.cpp \
    ctc/frmpatterns.cpp \
    ctc/frmfixerrors.cpp \
    ctc/lockedroute.cpp \
    ctc/reentrantlock.cpp \
    ctc/signaldirectionindicators.cpp \
    ctc/requesteddirectionobserved.cpp \
    ctc/codebuttonsimulator.cpp \
    ctc/switchdirectionlever.cpp \
    ctc/signaldirectionlever.cpp \
    ctc/switchdirectionindicators.cpp \
    ctc/trafficlockinginfo.cpp \
    ctc/fleeting.cpp \
    ctc/callon.cpp \
    ctc/switchindicatorsroute.cpp \
    ctc/indicationlockingsignals.cpp \
    ctc/trafficlocking.cpp \
    storemenu.cpp \
    systemconnectionmemo.cpp \
    managercombobox.cpp \
    abstractblockmanager.cpp \
    abstractsectionmanager.cpp \
    abstractnamedbeanhandlemanager.cpp \
    abstractroutemanager.cpp \
    loconet/lncvdevicesmanager.cpp \
    loconet/lncvdevices.cpp \
    loconet/lncvdevice.cpp \
    loconet/lncvmessagecontents.cpp \
    loconet/lncvprogtablemodel.cpp \
    loconet/lncvprogpane.cpp \
    loconet/lncvprogaction.cpp \
    abstractprogrammerserver.cpp \
    searchbar.cpp \
    cvutil.cpp \
    logix/learnfunctionpanel.cpp \
    logix/learncontrolpanel.cpp \
    logix/learnspeedpanel.cpp


equals(ENABLE_LOGIXNG, "Y") {
 DEFINES += HAVE_LOGIXNG
 SOURCES += \
 #logixng/manager.cpp\
    logixng/stringexpressionconstantxml.cpp \
    logixng/stringexpressionmemoryxml.cpp \
    logixng/defaultconditionalngmanagerxml.cpp \
    logixng/actiontimer.cpp \
    logixng/logix_emulator.cpp \
    logixng/logixngmoduletableaction.cpp \
    logixng/moduleeditor.cpp \
    logixng/moduleeditormalesocket.cpp \
    logixng/andswing.cpp \
    logixng/expressionlight.cpp \
    logixng/expressionlightxml.cpp \
    logixng/expressionsensorxml.cpp \
    logixng/expressionturnoutxml.cpp \
    logixng/falsexml.cpp \
    logixng/hold.cpp \
    logixng/holdxml.cpp \
    logixng/notswing.cpp \
    logixng/orxml.cpp \
    logixng/triggeroncexml.cpp \
    logixng/stringformula.cpp \
    logixng/stringformulaswing.cpp \
    logixng/stringformulaxml.cpp \
    logixng/defaultmaleanalogactionsocketxml.cpp \
    logixng/defaultmaledigitalactionsocketxml.cpp \
    logixng/defaultmaledigitalbooleanactionsocketxml.cpp \
    logixng/defaultmaledigitalexpressionsocketxml.cpp \
    logixng/defaultmalestringactionsocketxml.cpp \
    logixng/defaultmalestringexpressionsocketxml.cpp \
    logixng/abstractmalesocketxml.cpp \
    logixng/defaultmaleanalogexpressionsocketxml.cpp \
    logixng/actionfactory_loconet.cpp \
    logixng/digitalmanyswing.cpp \
    logixng/triggeronceswing.cpp \
    logixng/ifthenelseswing.cpp \
    logixng/for.cpp \
    logixng/forswing.cpp \
    logixng/analogactionmemoryxml.cpp \
    logixng/analogfactory_expressions.cpp \
    logixng/analogmanyxml.cpp \
    logixng/defaultmaledigitalexpressionsocketswing.cpp \
    logixng/actions/digitalfactory.cpp \
    logixng/expressions/digitalfactory_expressions.cpp \
    logixng/tableforeach.cpp \
    logixng/tableforeachxml.cpp \
    logixng/convertfunctions.cpp \
    logixng/mathfunctions.cpp \
    logixng/false.cpp \
    logixng/falseswing.cpp \
    logixng/logixng_metatypes.cpp \
    logixng/tableforeachswing.cpp \
    logixng/actionsensor.cpp \
    logixng/digitalformula.cpp \
    logixng/digitalformulaswing.cpp \
    logixng/orswing.cpp \
    logixng/trueswing.cpp \
    logixng/truexml.cpp \
    logixng/actionturnoutlock.cpp \
    logixng/andxml.cpp \
    logixng/antecedent.cpp \
    logixng/antecedentswing.cpp \
    logixng/antecedentxml.cpp \
    logixng/executedelayed.cpp \
    logixng/not.cpp \
    logixng/protectedtimertask.cpp \
    logixng/triggeronce.cpp \
    logixng/true.cpp \
    logixng/expressionsensor.cpp \
    logixng/expressionsensorswing.cpp \
    logixng/and.cpp \
    logixng/expressionmemory.cpp \
    logixng/actionmemory.cpp \
    logixng/abstractanalogactionswing.cpp \
    logixng/analogactionlightintensity.cpp \
    logixng/analogactionlightintensityswing.cpp \
    logixng/analogactionmemoryswing.cpp \
    logixng/analogexpressionanalogioswing.cpp \
    logixng/analogexpressionconstantswing.cpp \
    logixng/analogformulaswing.cpp \
    logixng/analogmanyswing.cpp \
    logixng/digitalbooleanmany.cpp \
    logixng/digitalbooleanmanyswing.cpp \
    logixng/digitalbooleanonchangeswing.cpp \
    logixng/expressionturnout.cpp \
    logixng/timesincemidnightswing.cpp \
    logixng/debuggermaleanalogexpressionsocketfactory.cpp \
    logixng/stringexpressionmemory.cpp \
    logixng/actionturnout.cpp \
    logixng/stringactionmemory.cpp \
    logixng/analogactionmemory.cpp \
    logixng/abstractdigitalbooleanaction.cpp \
    logixng/abstractstringaction.cpp \
    logixng/abstractstringexpression.cpp \
    logixng/debuggerinstanceinitializer.cpp \
    logixng/digitalbooleanonchange.cpp \
    logixng/dostringaction.cpp \
    logixng/lastresultofdigitalexpression.cpp \
    #logixng/logix.cpp \
    logixng/stringexpressionconstant.cpp \
    logixng/stringmany.cpp \
    logixng/abstractanalogaction.cpp \
    logixng/analogmany.cpp \
    logixng/logixng_manager.cpp \
    logixng/abstractdigitalexpression.cpp \
    logixng/digitalmany.cpp \
    logixng/doanalogaction.cpp \
    logixng/ifthenelse.cpp \
    logixng/or.cpp \
    logixng/actionfactory.cpp \
    logixng/categoryloconet.cpp \
    logixng/importconditional.cpp \
    logixng/logixnginitializationtable.cpp \
    logixng/importlogix.cpp \
    logixng/importlogixaction.cpp \
    logixng/importlogixframe.cpp \
    logixng/logixnginitializationtableaction.cpp \
    logixng/logixngmenu.cpp \
    logixng/startstopalllogixngsaction.cpp \
    logixng/debuggermaleanalogactionsocket.cpp \
    logixng/debuggermaleanalogactionsocketfactory.cpp \
    logixng/debuggermaledigitalactionsocket.cpp \
    logixng/debuggermaledigitalactionsocketfactory.cpp \
    logixng/debuggermaledigitalbooleanactionsocket.cpp \
    logixng/debuggermaledigitalbooleanactionsocketfactory.cpp \
    logixng/debuggermaledigitalexpressionsocket.cpp \
    logixng/debuggermaledigitalexpressionsocketfactory.cpp \
    logixng/debuggermalestringactionsocket.cpp \
    logixng/debuggermalestringactionsocketfactory.cpp \
    logixng/debuggermalestringexpressionsocket.cpp \
    logixng/debuggermalestringexpressionsocketfactory.cpp \
    logixng/defaultanalogactionmanager.cpp \
    logixng/defaultconditionalngmanager.cpp \
    logixng/defaultdigitalactionmanager.cpp \
    logixng/defaultdigitalbooleanactionmanager.cpp \
    logixng/defaultdigitalexpressionmanager.cpp \
    logixng/defaultfemaledigitalbooleanactionsocket.cpp \
    logixng/defaultstringactionmanager.cpp \
    logixng/defaultstringexpressionmanager.cpp \
    logixng/digitalbooleanfactory.cpp \
    logixng/expressionfactory.cpp \
    logixng/logixng_analoginstanceinitializer.cpp \
    logixng/logixng_digitalinstanceinitializer.cpp \
    logixng/logixng_stringinstanceinitializer.cpp \
    logixng/stringfactory.cpp \
    logixng/abstractdebuggermalesocketswing.cpp \
    logixng/abstractdigitalexpressionswing.cpp \
    logixng/abstractstringactionswing.cpp \
    logixng/abstractstringexpressionswing.cpp \
    logixng/defaultfemalestringactionsocket.cpp \
    logixng/defaultmoduleswing.cpp \
    logixng/abstractbooleanactionswing.cpp \
    logixng/abstractanalogexpressionswing.cpp \
    logixng/abstractmalesocketswing.cpp \
    logixng/analogexpressionmemoryswing.cpp \
    logixng/defaultinternalnamedtable.cpp \
    logixng/defaultmaleanalogactionsocket.cpp \
    logixng/defaultmaledigitalactionsocket.cpp \
    logixng/defaultmaledigitalbooleanactionsocket.cpp \
    logixng/defaultmaledigitalexpressionsocket.cpp \
    logixng/defaultmalestringactionsocket.cpp \
    logixng/defaultnamedtablemanager.cpp \
    logixng/defaultmodule.cpp \
    logixng/defaultmodulemanager.cpp \
    logixng/defaultmodulexml.cpp \
    logixng/abstractmanagerxml.cpp \
    logixng/defaultanalogactionmanagerxml.cpp \
    logixng/defaultanalogexpressionmanagerxml.cpp \
    logixng/defaultdigitalactionmanagerxml.cpp \
    logixng/defaultdigitalbooleanactionmanagerxml.cpp \
    logixng/defaultdigitalexpressionmanagerxml.cpp \
    logixng/defaultmalestringexpressionsocket.cpp \
    logixng/defaultmodulemanagerxml.cpp \
    logixng/defaultnamedtablemanagerxml.cpp \
    logixng/defaultstringactionmanagerxml.cpp \
    logixng/defaultstringexpressionmanagerxml.cpp \
    logixng/defaultmaleanalogexpressionsocket.cpp \
    logixng/defaultfemalestringexpressionsocket.cpp \
    logixng/genericexpressionvariable.cpp \
    logixng/abstractanalogexpression.cpp \
    logixng/analogexpressionanalogio.cpp \
    logixng/analogexpressionconstant.cpp \
    logixng/analogexpressionmemory.cpp \
    logixng/analogfactory.cpp \
    logixng/analogformula.cpp \
    logixng/debuggermaleanalogexpressionsocket.cpp \
    logixng/defaultanalogexpressionmanager.cpp \
    logixng/defaultfemaleanalogactionsocket.cpp \
    logixng/defaultfemaleanalogactionsocketfactory.cpp \
    logixng/defaultfemaleanalogexpressionsocket.cpp \
    logixng/defaultfemaleanalogexpressionsocketfactory.cpp \
    logixng/defaultfemaledigitalactionsocketfactory.cpp \
    logixng/defaultfemaledigitalexpressionsocket.cpp \
    logixng/defaultfemaledigitalexpressionsocketfactory.cpp \
    logixng/defaultfemalegenericexpressionsocket.cpp \
    logixng/defaultfemalesocketmanager.cpp \
    logixng/defaultfemalestringactionsocketfactory.cpp \
    logixng/defaultfemalestringexpressionsocketfactory.cpp \
    logixng/timesincemidnight.cpp \
    logixng/actionatomicboolean.cpp \
    logixng/defaultconditionalng.cpp \
    logixng/defaultconditionalngscaffold.cpp \
    logixng/defaultfemaledigitalactionsocket.cpp \
    logixng/defaultlogixngpreferences.cpp \
    logixng/executelock.cpp \
    logixng/logixng_instanceinitializer.cpp \
    logixng/actionsignalheadswing.cpp \
    logixng/abstractbasemanager.cpp \
    logixng/abstractnamedtable.cpp \
    logixng/defaultanonymoustable.cpp \
    logixng/defaultcsvnamedtable.cpp \
    logixng/defaultlogixnginitializationmanager.cpp \
    logixng/editcommentdialog.cpp \
    logixng/functionshelpdialog.cpp \
    logixng/localvariabletablemodel.cpp \
    logixng/abstractdebuggermalesocket.cpp \
    logixng/abstractdigitalactionswing.cpp \
    logixng/abstractswingconfigurator.cpp \
    logixng/actionpositionable.cpp \
    logixng/actionpositionableswing.cpp \
    logixng/categorydisplay.cpp \
    logixng/debuggersymboltablemodel.cpp \
    logixng/swingconfiguratorinterface.cpp \
    logixng/swingtools.cpp \
    logixng/clipboardeditor.cpp \
    logixng/conditionalngdebugger.cpp \
    logixng/conditionalngeditor.cpp \
    logixng/debugger.cpp \
    logixng/treeeditor.cpp \
    logixng/treepane.cpp \
    logixng/treeviewer.cpp \
    logixng/logixngeditor.cpp \
    logixng/logixngtableaction.cpp \
    logixng/abstractdigitalaction.cpp \
    logixng/abstractlogixngtableaction.cpp \
    logixng/clockfunctions.cpp \
    logixng/constant.cpp \
    logixng/defaultstack.cpp \
    logixng/defaultsymboltable.cpp \
    logixng/expressionnodearithmeticoperator.cpp \
    logixng/expressionnodeassignmentoperator.cpp \
    logixng/expressionnodebooleanoperator.cpp \
    logixng/expressionnodecomparingoperator.cpp \
    logixng/expressionnodefloatingnumber.cpp \
    logixng/expressionnodefunction.cpp \
    logixng/expressionnodeidentifier.cpp \
    logixng/expressionnodeintegernumber.cpp \
    logixng/expressionnodestring.cpp \
    logixng/expressionnodeternaryoperator.cpp \
    logixng/functionmanager.cpp \
    logixng/localvariableexpressionvariable.cpp \
    logixng/logixngtabletableaction.cpp \
    logixng/recursivedescentparser.cpp \
    logixng/referenceutil.cpp \
    logixng/stringfunctions.cpp \
    logixng/tableeditor.cpp \
    logixng/tokenizer.cpp \
    logixng/typeconversionutil.cpp \
    logixng/abortconditionalngexecutionexception.cpp \
    logixng/abstractmalesocket.cpp \
    logixng/base.cpp \
    logixng/category.cpp \
    logixng/defaultlogixng.cpp \
    logixng/defaultlogixngmanager.cpp \
    logixng/defaultlogixngmanagerxml.cpp \
    logixng/errorhandlingdialog.cpp \
    logixng/errorhandlingdialog_multiline.cpp \
    logixng/logixng_thread.cpp \
    logixng/socketalreadyconnectedexception.cpp \
    logixng/abstractbase.cpp \
    logixng/abstractfemalesocket.cpp \
    logixng/clipboardmany.cpp \
    logixng/defaultclipboard.cpp \
    logixng/defaultfemaleanysocket.cpp
} else {
DEFINES -= HAVE_LOGIXNG
}

 !contains(FTDI, 1) {
    SOURCES +=
 }
HEADERS += \
 Signal/abstractmrnodetrafficcontroller.h \
 Signal/abstractnode.h \
 Signal/acelaaddress.h \
 Signal/acelaconnectiontypelist.h \
 Signal/acelalistener.h \
 Signal/acelamessage.h \
 Signal/acelanode.h \
 Signal/acelareply.h \
 Signal/acelasignalhead.h \
 Signal/acelasystemconnectionmemo.h \
 Signal/acelatrafficcontroller.h \
 Signal/lsdecsignalhead.h \
 Signal/lsdecsignalheadxml.h \
 Signal/mergsd2signalhead.h \
 Signal/mergsd2signalheadxml.h \
 #Signal/serialsignalhead.h \
 abstractanalogiomanager.h \
 abstractprovidingproxymanager.h \
 abstractproxymanager.h \
 acelasignalheadxml.h \
 addeditsinglelightcontrolframe.h \
 analogiomanager.h \
 collectingReporter.h \
 defaultlightcontrol.h \
 digitalio.h \
# direct/defaultthrottle.h \
# direct/defaultthrottlemanager.h \
# direct/directcomponentfactory.h \
# direct/directmenu.h \
# direct/directsystemconnectionmemo.h \
# direct/portcontroller.h \
# direct/serialdriveradapter.h \
# direct/trafficcontroller.h \
 internalanalogiomanager.h \
 lightcontrolpane.h \
 lightcontroltablemodel.h \
 lighteditaction.h \
 lightintensitypane.h \
    loconetmessage.h \
    lnconstants.h \
    llnmon.h \
 logixng/actionblock.h \
 logixng/actionblockswing.h \
 logixng/actionblockxml.h \
 logixng/actionclock.h \
 logixng/actionclockswing.h \
 logixng/actionclockxml.h \
 logixng/actionlistenonbeans.h \
 logixng/actionlistenonbeansswing.h \
 logixng/actionlistenonbeansxml.h \
 logixng/actionlocalvariable.h \
 logixng/actionlocalvariableswing.h \
 logixng/actionlocalvariablexml.h \
 logixng/actionsensorswing.h \
 logixng/actionsensorxml.h \
 logixng/digitalformulaxml.h \
 logixng/holdswing.h \
 logixng/ifthenelsexml.h \
 logixng/listenonbeanstablemodel.h \
 logixng/namedbeantype.h \
 logixng/notxml.h \
 logixng/stringexpressionconstantswing.h \
    namedbeancombobox.h \
    otherconnectiontypelist.h \
    serialport.h \
    dccmanufacturerlist.h \
    lnconnectiontypelist.h \
    activeflag.h \
    lntrafficcontroller.h \
    loconetinterface.h \
    lnpacketizer.h \
    lnportcontroller.h \
    abstractserialportcontroller.h \
    locobufferadapter.h \
    loconetlistener.h \
    pr3adapter.h \
    masterthread.h \
    libPr3_global.h \
    locobufferusbadapter.h \
    build_number.h \
    libpr3version.h \
    language.h \
    locoaddress.h \
    dcclocoaddress.h \
 silenceablepropertychangeprovider.h \
    slotmanager.h \
    abstractprogrammer.h \
    programmer.h \
    loconetslot.h \
    slotlistener.h \
 sprog/sprogserialdriveradapter.h \
    systemconnectionmemomanager.h \
    systemconnectionmemo.h \
    loconetsystemconnectionmemo.h \
    powermanager.h \
    abstractpowermanager.h \
    lnpowermanager.h \
    loconetthrottledtransmitter.h \
    lnprogrammermanager.h \
    defaultprogrammermanager.h \
    turnout.h \
    abstractturnout.h \
    namedbeanhandlemanager.h \
    turnoutoperation.h \
    turnoutmanager.h \
    turnoutoperationmanager.h \
    abstractturnoutmanager.h \
    abstractmanager.h \
    lnturnoutmanager.h \
    lnturnout.h \
    abstractsensor.h \
    sensormanager.h \
    abstractsensormanager.h \
    lnsensormanager.h \
    lnsensoraddress.h \
    lnsensor.h \
    abstractreportermanager.h \
    abstractreporter.h \
    lnreporter.h \
    reportermanager.h \
    reporter.h \
    lnreportermanager.h \
    timebase.h \
    pr3systemconnectionmemo.h \
    proxyreportermanager.h \
    proxysensormanager.h \
    proxyturnoutmanager.h \
    internalsensormanager.h \
    internalturnoutmanager.h \
    sensor.h \
    abstractmemory.h \
    physicallocationreporter.h \
    initializer.h \
    defaultmemorymanager.h \
    abstractmemorymanager.h \
    defaultmemory.h \
    internalreportermanager.h \
    Roster/roster.h \
    Roster/rosterentry.h \
    dcclocoaddressxml.h \
    Roster/rosterentryselector.h \
    Roster/rosterentrycombobox.h \
    Roster/rostergroupcombobox.h \
    Roster/rosterentryselectorpanel.h \
    turnoutoperator.h \
    nofeedbackturnoutoperation.h \
    commonturnoutoperation.h \
    nofeedbackturnoutoperator.h \
    message.h \
    idtag.h \
    abstractidtag.h \
    idtagmanager.h \
    rfid/rfidreporter.h \
    defaultidtagmanager.h \
    defaultidtag.h \
    clockcontrol.h \
    abstractportcontroller.h \
    shutdownmanager.h \
    defaultshutdownmanager.h \
    rfid/rfidsensormanager.h \
    rfid/rfidsensor.h \
    rfid/rfidlistener.h \
    abstractmrlistener.h \
    rfid/rfidreportermanager.h \
    throttle.h \
    basicrosterentry.h \
    abstractthrottle.h \
    throttlemanager.h \
    commandstation.h \
    consistmanager.h \
    dccconsistmanager.h \
    dccconsist.h \
    consist.h \
    abstractthrottlemanager.h \
    dccthrottle.h \
    lnthrottlemanager.h \
    proglistener.h \
    consistlistener.h \
    memory.h \
    rfid/rfidusb.h \
    routemanager.h \
    route.h \
    defaultroutemanager.h \
    defaultroute.h \
    decimalformat.h \
    blockvaluefile.h \
    lightmanager.h \
    abstractlightmanager.h \
    lightcontrol.h \
    lnlightmanager.h \
    lnlight.h \
    abstractlight.h \
    proxylightmanager.h \
    internallightmanager.h \
    loconetconsistmanager.h \
    defaultclockcontrol.h \
    abstractconsistmanager.h \
    lnclockcontrol.h \
    abstractvariablelight.h \
    configuremanager.h \
    simpletimebase.h \
    loconetthrottle.h \
    Throttle/throttlewindow.h \
    Roster/locofile.h \
    Roster/cvtablemodel.h \
    Roster/abstractvalue.h \
    Roster/cvvalue.h \
    Roster/variabletablemodel.h \
    Roster/variablevalue.h \
    Roster/qualifier.h \
    Roster/abstractqualifier.h \
    Roster/valuequalifier.h \
    Roster/enumvariablevalue.h \
    Roster/compositevariablevalue.h \
    Roster/decvariablevalue.h \
    Roster/hexvariablevalue.h \
    Roster/longaddrvariablevalue.h \
    Roster/shortaddrvariablevalue.h \
    Roster/speedtablevarvalue.h \
    Roster/splitvariablevalue.h \
    Roster/constantvalue.h \
    Roster/qualifiercombiner.h \
    Roster/decoderfile.h \
    Roster/resettablemodel.h \
    Roster/combocheckbox.h \
    Roster/comboradiobuttons.h \
    Roster/listdatalistener.h \
    Roster/decvarslider.h \
    Roster/comboonradiobutton.h \
    Roster/combooffradiobutton.h \
    Roster/rosterentrypane.h \
    Roster/decoderindexfile.h \
    Roster/paneprogpane.h \
    Roster/panecontainer.h \
    Roster/busyglasspane.h \
    Roster/dccaddresspanel.h \
    Roster/watchinglabel.h \
    Roster/fnmappanel.h \
    #Roster/functionlabelspane.h \
    Roster/paneprogframe.h \
    Roster/paneopsprogframe.h \
    Roster/rosterframe.h \
    connectionstatus.h \
    Roster/abstractidentify.h \
    Roster/identifyloco.h \
    Roster/factoryresetaction.h \
    Roster/dcclocoaddressselector.h \
    Roster/optionsdialog.h \
    Signal/signalheadmanager.h \
    Signal/signalmast.h \
    Signal/signalmastmanager.h \
    Signal/signalsystemmanager.h \
    Signal/signalsystem.h \
    Signal/signalgroup.h \
    Signal/signalgroupmanager.h \
    Signal/defaultsignalhead.h \
    Signal/abstractsignalhead.h \
    Signal/abstractsignalheadmanager.h \
    Signal/signalhead.h \
    Signal/signalappearancemap.h \
    Signal/signalmastlogic.h \
    Signal/defaultsignalmastlogic.h \
    Signal/signalmastlogicmanager.h \
    Signal/signalspeedmap.h \
    Signal/defaultsignalappearancemap.h \
    Signal/defaultsignalmastmanager.h \
    Signal/signalheadsignalmast.h \
    Signal/abstractsignalmast.h \
    Signal/defaultsignalsystem.h \
    Signal/defaultsignalsystemmanager.h \
    Signal/se8csignalhead.h \
    memorymanager.h \
    Signal/singleturnoutsignalhead.h \
    Signal/doubleturnoutsignalhead.h \
    Signal/virtualsignalhead.h \
    Signal/defaultsignalmastlogicmanager.h \
    Signal/turnoutsignalmast.h \
    Signal/virtualsignalmast.h \
    Signal/addsignalmastpanel.h \
    sensorturnoutoperator.h \
    Signal/signalmastrepeater.h \
    logix.h \
    defaultlogix.h \
    conditional.h \
    jmrisimplepropertylistener.h \
    logixmanager.h \
    defaultlogixmanager.h \
    conditionalvariable.h \
    conditionalmanager.h \
    jmritwostatepropertylistener.h \
    jmriclockpropertylistener.h \
    jmrimultistatepropertylistener.h \
    conditionalaction.h \
    defaultconditionalmanager.h \
    defaultconditional.h \
    sensorgroupconditional.h \
    defaultconditionalaction.h \
    connectionnamefromsystemname.h \
    audio.h \
    audiobuffer.h \
    audiomanager.h \
    defaultaudiomanager.h \
    abstractaudiomanager.h \
    abstractaudio.h \
    oblock.h \
    portal.h \
 variablelight.h \
    warrant.h \
    blockorder.h \
    opath.h \
    throttlesetting.h \
    oblockmanager.h \
    engineer.h \
    warrantmanager.h \
    entryexitpairs.h \
    source.h \
    pointdetails.h \
    destinationpoints.h \
    Throttle/throttleslistpanel.h \
    timeunit.h \
    pushbuttonpacket.h \
    rawturnoutoperation.h \
    sensorturnoutoperation.h \
    Signal/tripleturnoutsignalhead.h \
    Signal/quadoutputsignalhead.h \
    timertask.h \
    Signal/defaultsignalgroupmanager.h \
    Signal/defaultsignalgroup.h \
    Throttle/throttlestablemodel.h \
    Throttle/throttlestablecellrenderer.h \
    Roster/rostericonfactory.h \
    Throttle/throttleframemanager.h \
    Throttle/addresspanel.h \
    Throttle/addresslistener.h \
    Roster/nceconsistroster.h \
    Roster/nceconsistrosterentry.h \
    Throttle/throttleframepropertyeditor.h \
    Throttle/throttlecreationaction.h \
    Throttle/largepowermanagerbutton.h \
    Throttle/powermanagerbutton.h \
    Throttle/smallpowermanagerbutton.h \
    Throttle/controlpanel.h \
    Throttle/functionpanel.h \
    Throttle/functionbutton.h \
    Throttle/functionlistener.h \
    Roster/createrostergroupaction.h \
    Roster/rostermenu.h \
    Roster/panenewprogaction.h \
    Roster/paneeditaction.h \
    Roster/locoselpane.h \
    Roster/knownlocoselpane.h \
    Roster/progdefault.h \
    Roster/xmlfilenamefilter.h \
    Roster/locoseltreepane.h \
    Roster/combinedlocoseltreepane.h \
    Roster/combinedlocoselpane.h \
    Roster/globalrosterentrycombobox.h \
    Roster/identifydecoder.h \
    Roster/copyrosteritemaction.h \
    Roster/abstractrosteritemaction.h \
    Roster/deleterosteritemaction.h \
    Roster/rosterframeaction.h \
    Roster/paneserviceprogframe.h \
    Roster/progmodeselector.h \
    Roster/progservicemodecombobox.h \
    Roster/simpleprogaction.h \
    Roster/simpleprogframe.h \
    Roster/progmodepane.h \
    Roster/progservicemodepane.h \
    Roster/progopsmodepane.h \
    Roster/paneprogaction.h \
    Roster/paneopsprogaction.h \
    LocoIO/cmdstnconfigpane.h \
    LocoIO/lncommandstationtype.h \
    Roster/qualifieradder.h \
    Roster/field.h \
    Roster/fnmappanelesu.h \
    Roster/arithmeticqualifier.h \
    Roster/jcomponentqualifier.h \
    Roster/dccaddressvarhandler.h \
    Roster/printaction.h \
    Roster/printcvaction.h \
    Roster/printrosterentry.h \
    addressedprogrammer.h \
    lnopsmodeprogrammer.h \
    programmingmode.h \
    globalprogrammermanager.h \
    addressedprogrammermanager.h \
    abstractserialconnectionconfig.h \
    loconet/Pr3/pr3connectionconfig.h \
    Roster/twoindexprogrammerfacade.h \
    Roster/accessoryopsmodeprogrammerfacade.h \
    Roster/abstractprogrammerfacade.h \
    Roster/programmerfacadeselector.h \
    Roster/multiindexprogrammerfacade.h \
    loconet/Locobuffer/locobufferconnectionconfig.h \
    loconet/LocobufferUsb/locobufferusbconnectionconfig.h \
    loconet/LocobufferUsb/locobufferusbconnectionconfigxml.h \
    loconet/Locobuffer/locobufferconnectionconfigxml.h \
    resourcebundle.h \
    loconet/HexFile/hexfileserver.h \
    loconet/HexFile/hexfileframe.h \
    loconet/HexFile/lnhexfileport.h \
    loconet/HexFile/debugprogrammermanager.h \
    loconet/HexFile/debugthrottlemanager.h \
    loconet/HexFile/debugthrottle.h \
    nmraconsistmanager.h \
    nmraconsist.h \
    loconet/HexFile/progdebugger.h \
    loconet/HexFile/hexfileconnectionconfigxml.h \
    loconet/HexFile/hexfileconnectionconfig.h \
    abstractsimulatorconnectionconfig.h \
    audiocommand.h \
    audiofactory.h \
    audiosource.h \
    audiothread.h \
    abstractaudiothread.h \
    abstractaudiobuffer.h \
    audiolistener.h \
    nullaudiofactory.h \
    abstractaudiofactory.h \
    nullaudiosource.h \
    nullaudiobuffer.h \
    nullaudiolistener.h \
    abstractaudiosource.h \
    audiocommandthread.h \
    qtsoundaudiofactory.h \
    qtsoundaudiobuffer.h \
    audioinputstream.h \
    audiosystem.h \
    wavfilereader.h \
    qtsoundaudiosource.h \
    qtsoundaudiolistener.h \
    floatcontrol.h \
    clip.h \
    dataline.h \
    line.h \
    mixer.h \
    audiofilereader.h \
    audiofileformat.h \
    audioformat.h \
    LocoIO/locostatspanel.h \
    LocoIO/jmrinamedpaneaction.h \
    LocoIO/lnnamedpaneaction.h \
    LocoIO/lnpanelinterface.h \
    LocoIO/slotmonpane.h \
    LocoIO/abstractboardprogpanel.h \
    LocoIO/ds64panel.h \
    LocoIO/clockmonpane.h \
    LocoIO/locoidpanel.h \
    messagepanel.h \
    lnmessagemanager.h \
    pr3selectpane.h \
    loaderpane.h \
    memorycontents.h \
    abstractaudiolistener.h \
    loconet/lnovertcppacketizer.h \
    loconet/lnnetworkportcontroller.h \
    abstractnetworkportcontroller.h \
    loconet/lntcpdriveradapter.h \
    loconet/serverlistner.h \
    loconet/jmriserver.h \
    loconet/clientrxhandler.h \
    loconet/LnOverTcp/lnovertcpconnectionconfig.h \
    abstractnetworkconnectionconfig.h \
    abstractnetworkconnectionconfigxml.h \
    loconet/LnOverTcp/lnovertcpconnectionconfigxml.h \
    loconet/networkportadapter.h \
    Roster/importrosteritemaction.h \
    Roster/exportrosteritemaction.h \
    Roster/deleterostergroupaction.h \
    Roster/rosterentrytogroupaction.h \
    Roster/removerosterentrytogroupaction.h \
    Roster/rostergrouptableaction.h \
    Roster/rostergrouptablemodel.h \
    Roster/rostergrouptableframe.h \
    Roster/fullbackupexportaction.h \
    Roster/fullbackupimportaction.h \
    Roster/speedprofilepanel.h \
    Roster/rosterspeedprofile.h \
    Roster/speedprofileframe.h \
    Roster/speedprofileaction.h \
    loconet/soundloaderpane.h \
    loconet/loaderengine.h \
    loconet/spjfile.h \
    loconet/sdfbuffer.h \
    loconet/sdfmacro.h \
    loconet/sdfconstants.h \
    loconet/channelstart.h \
    loconet/skemestart.h \
    loconet/sdlversion.h \
    loconet/endsound.h \
    loconet/generatetrigger.h \
    loconet/delaysound.h \
    loconet/twobytemacro.h \
    loconet/fourbytemacro.h \
    loconet/skipontrigger.h \
    loconet/initiatesound.h \
    loconet/play.h \
    loconet/maskcompare.h \
    loconet/loadmodifier.h \
    loconet/branchto.h \
    loconet/editorfilepane.h \
    loconet/editortabledatamodel.h \
    loconet/editorpane.h \
    loconet/wavbuffer.h \
    loconet/editorframe.h \
    loconet/sdfeditorpane.h \
    loconet/sdfmacroeditor.h \
    loconet/monitoringlabel.h \
    loconet/defaultmutabletreemodel.h \
    loconet/channelstarteditor.h \
    loconet/sdlversioneditor.h \
    loconet/skemestarteditor.h \
    loconet/generatetriggereditor.h \
    loconet/initiatesoundeditor.h \
    loconet/loadmodifiereditor.h \
    loconet/playeditor.h \
    loconet/maskcompareeditor.h \
    loconet/branchtoeditor.h \
    loconet/endsoundeditor.h \
    loconet/delaysoundeditor.h \
    loconet/skipontriggereditor.h \
    loconet/twobytemacroeditor.h \
    loconet/fourbytemacroeditor.h \
    loconet/qtsoundaudioclip.h \
    loconet/loconetmsgdialog.h \
    loconet/loconetmenu.h\
    loconet/querycvdialog.h \
    Throttle/throttleslistaction.h \
    Roster/rostergroupspanel.h \
    Roster/decoderindexcreateaction.h \
    Roster/updatedecoderdefinitionaction.h \
    Roster/recreaterosteraction.h \
    Roster/rostergroup.h \
    Roster/rosterobject.h \
    Roster/paneprogdp3action.h \
    Roster/printrosteraction.h \
    light.h \
    Roster/copyrostergroupaction.h \
    Roster/renamerostergroupaction.h \
    Roster/installdecoderfileaction.h \
    Roster/installdecoderurlaction.h \
    Signal/dccsignalmast.h \
    deferringprogrammermanager.h \
    vsdecodermanager.h \
    vsdecoderpreferences.h \
    listeningspot.h \
    vsdlistener.h \
    addressedhighcvprogrammerfacade.h \
    vsdecodermanagerthread.h \
    vsdecoder.h \
    vsdmanagerframe.h \
    vsdconfig.h \
    vsdfile.h \
    zipfile.h \
    vsdsound.h \
    vsdecoderevent.h \
    trigger.h \
    soundevent.h \
    momentarysoundevent.h \
    togglesoundevent.h \
    enginesoundevent.h \
    configurablesound.h \
    steamsound.h \
    enginesound.h \
    dieselsound.h \
    diesel3sound.h \
    buttontrigger.h \
    enginepane.h \
    dieselpane.h \
    soundbite.h \
    notchtransition.h \
    audioutil.h \
    triggerlistener.h \
    booltrigger.h \
    throttletrigger.h \
    floattrigger.h \
    notchtrigger.h \
    inttrigger.h \
    control.h \
    managerdefaultselector.h \
    managerdefaultselectorxml.h \
    path.h \
     block.h \
     beansetting.h\
    blockmanager.h \
    entrypoint.h \
    reportcontext.h \
    namedbeanhandlemanager.h \
    rostertablemodel.h \
    rostergroupselector.h \
    Roster/imagedelegate.h \
    Throttle/functionbuttonpropertyeditor.h \
    jmriuserpreferencesmanager.h \
    preferencesmanager.h \
    abstractpreferencesmanager.h \
    internalsystemconnectionmemo.h \
    defaultpowermanager.h \
    Roster/namecheckaction.h \
    Roster/progcheckaction.h \
    Roster/namefile.h \
    Throttle/stopallbutton.h \
    Throttle/serversocket.h \
    Throttle/consistfile.h \
    Throttle/throttlelistener.h \
    Json/jsonserverpreferences.h \
    Json/jsonserverpreferencespanel.h \
    WiThrottle/abstractcontroller.h \
    WiThrottle/abstractwithrottlepreferences.h \
    WiThrottle/consistcontroller.h \
    WiThrottle/consistfunctioncontroller.h \
    WiThrottle/controllerfilteraction.h \
    WiThrottle/controllerfilterframe.h \
    WiThrottle/controllerinterface.h \
    WiThrottle/devicelistener.h \
    WiThrottle/devicemanager.h \
    WiThrottle/deviceserver.h \
    WiThrottle/multithrottle.h \
    WiThrottle/multithrottlecontroller.h \
    WiThrottle/routecontroller.h \
    WiThrottle/throttlecontroller.h \
    WiThrottle/throttlecontrollerlistener.h \
    WiThrottle/trackpowercontroller.h \
    WiThrottle/turnoutcontroller.h \
    WiThrottle/userinterface.h \
    WiThrottle/wificonsist.h \
    WiThrottle/wificonsistfile.h \
    WiThrottle/wificonsistmanager.h \
    WiThrottle/withrottlecreationaction.h \
    WiThrottle/withrottlemanager.h \
    WiThrottle/withrottlepreferences.h \
    WiThrottle/withrottleprefspanel.h \
    WiThrottle/withrottleslistmodel.h \
    Json/jsonthrottle.h \
    Json/jsonthrottlemanager.h \
    Json/jsonthrottlesocketservice.h \
    Json/jsonqt.h \
    Web/jmriconnection.h \
    Web/httpservletresponse.h \
    Json/jsonconnection.h \
    Json/jsonexception.h \
    Json/jsonsocketservice.h \
    Json/jsonsensor.h \
    Json/jsonsensorsocketservice.h \
    Json/jsonsensorhttpservice.h \
    Json/jsonnamedbeanhttpservice.h \
    Json/jsonhttpservice.h \
    Json/jsonservicefactory.h \
    Json/jsonclienthandler.h \
    Json/jsonthrottleservicefactory.h \
    Json/jsonsensorservicefactory.h \
    Json/jsonutilservicefactory.h \
    Json/jsonutilsocketservice.h \
    Json/jsonutilhttpservice.h \
    Json/jsonpowerhttpservice.h \
    Json/jsonpowersocketservice.h \
    Json/jsonturnouthttpservice.h \
    Json/jsonturnoutsocketservice.h \
    Json/jsonturnoutservicefactory.h \
    Json/jsonpowerservicefactory.h \
    Json/jsontimeservicefactory.h \
    Json/jsontimesocketservice.h \
    Json/jsontimehttpservice.h \
    Json/jsonrosterhttpservice.h \
    Json/jsonroster.h \
    Json/jsonrosterservicefactory.h \
    Json/jsonrostersocketservice.h \
    Web/webserver.h \
    Web/webserveraction.h \
    Web/requesthandler.h \
    Web/httpservlet.h \
    Web/genericservlet.h \
    Web/servlet.h \
    Web/servletexception.h \
    Web/servletrequest.h \
    Web/servletresponse.h \
    Json/jsonwebsocket.h \
    Web/httpservletrequest.h \
    Web/servletconfig.h \
    Web/servletoutputstream.h \
    Web/servletcontext.h \
    Web/rosterservlet.h \
    Web/servletutil.h \
    Web/configservlet.h \
    Web/jmrijframeservlet.h \
    Web/homeservlet.h \
    Web/denialservlet.h \
    Web/redirectionservlet.h \
    Web/abstractpanelservlet.h \
    Web/panelservlet.h \
    Web/controlpanelservlet.h \
    Web/layoutpanelservlet.h \
    Web/handlercontainer.h \
    Web/directoryhandler.h \
    Web/directoryresource.h \
    Web/resource.h \
    Web/resourcehandler.h \
    Web/uriutil.h \
    Json/jsonblock.h \
    Json/jsonblockhttpservice.h \
    Json/jsonblockservicefactory.h \
    Json/jsonblocksocketservice.h \
    Json/jsonservlet.h \
    Web/websocketservlet.h \
    Web/messagedigest.h \
    Web/messagedigestspi.h \
    Web/websocketservletfactory.h \
    Json/jsonlightservicefactory.h \
    Json/jsonlightsocketservice.h \
    Json/jsonlighthttpservice.h \
    Json/jsonlayoutblock.h \
    Json/jsonlayoutblockhttpservice.h \
    Json/jsonlayoutblockservicefactory.h \
    Json/jsonlayoutblocksocketservice.h \
    Json/jsonmemory.h \
    Json/jsonmemoryhttpservice.h \
    Json/jsonmemorysocketservice.h \
    Json/jsonmemoryservicefactory.h \
    Json/jsonsignalhead.h \
    Json/jsonsignalheadhttpservice.h \
    Json/jsonsignalheadservicefactory.h \
    Json/jsonsignalheadsocketservice.h \
    Json/jsonsignalmast.h \
    Json/jsonsignalmasthttpservice.h \
    Json/jsonsignalmastservicefactory.h \
    Json/jsonsignalmastsocketservice.h \
    Json/jsonreporter.h \
    Json/jsonreporterhttpservice.h \
    Json/jsonreportersocketservice.h \
    Json/jsonreporterservicefactory.h \
    Json/jsonserver.h \
    Json/jsonserveraction.h \
    Web/operationsservlet.h \
    Json/jsonoperations.h \
    Json/jsonutil.h \
    Json/jsonoperationsservicefactory.h \
    Json/jsonoperationssocketservice.h \
    Json/jsonoperationshttpservice.h \
    Web/htmltraincommon.h \
    Web/htmlmanifest.h \
    Json/jsonmanifest.h \
    Web/htmlconductor.h \
    Json/jsonconsisthttpservice.h \
    Json/jsonconsistmanager.h \
    Json/jsonconsistservicefactory.h \
    Json/jsonconsistsocketservice.h \
    Web/defaultservletcontext.h \
    Web/defaultservletconfig.h \
    consistlistlistener.h \
    Web/stringescapeutils.h \
    Throttle/windowpreferences.h \
    Throttle/locoaddressxml.h \
    loconetmenustartupaction.h \
    Web/aboutservlet.h \
    sprog/sprogportcontroller.h \
    sprog/sprogsystemconnectionmemo.h \
    sprog/sprogconstants.h \
    sprog/sproglistener.h \
    sprog/sproginterface.h \
    sprog/sprogtrafficcontroller.h \
    sprog/sprogmessage.h \
    abstractmrmessage.h \
    abstractmessage.h \
    sprog/sprogreply.h \
    sprog/sprogtype.h \
    abstractmrreply.h \
    abstractconnectionconfig.h \
    sprog/sprogconnectionconfig.h \
    sprog/sprogconnectiontypelist.h \
    sprog/sprogversion.h \
    sprog/sprogprogrammermanager.h \
    sprog/sprogpowermanager.h \
    sprog/sprogversionquery.h \
    sprog/sprogcomponentfactory.h \
    sprog/sprogprogrammer.h \
    sprog/sprogcommandstation.h \
    connectionconfig.h \
    sprog/sprogslot.h \
    sprog/sprogconnectionconfigxml.h \
    sprog/sprogcsserialdriveradapter.h \
    sprog/sprogcsconnectionconfigxml.h \
    sprog/sprogcsconnectionconfig.h \
    sprog/sprogturnout.h \
    sprog/sprogthrottle.h \
    sprog/sprogthrottlemanager.h \
    sprog/sprogturnoutmanager.h \
    sprog/sprogcsturnout.h \
    sprog/sprogcsthrottlemanager.h \
    sprog/sprogcsthrottle.h \
    sprog/sprogslotlistener.h \
    sprog/sprogversionlistener.h \
    sprog/sprogcsmenu.h \
    sprog/sprogconsoleaction.h \
    sprog/sprogconsoleframe.h \
    sprog/sprogversionaction.h \
    sprog/sprogversionframe.h \
    sprog/sprogmenu.h \
    loconet/lncomponentfactory.h \
    abstractmrtrafficcontroller.h \
    sprog/sprogpacketgenframe.h \
    sprog/sprogpacketgenaction.h \
    sprog/sprogmonframe.h \
    sprog/sprogmonaction.h \
    sprog/pisprognanoserialdriveradapter.h \
    sprog/sprogupdateframe.h \
    sprog/sprogiiupdateframe.h \
    sprog/sprogiiupdateaction.h \
    sprog/sprogupdateaction.h \
    sprog/sproghexfile.h \
    sprog/sprogslotmonaction.h \
    sprog/sprogslotmonframe.h \
    sprog/sprogslotmondatamodel.h \
    Roster/opsmodedelayedprogrammerfacade.h \
    loconet/csopswaccess.h \
    verifywriteprogrammerfacade.h \
    Roster/csvimportaction.h \
    Roster/genericimportaction.h \
    Roster/csvimporter.h \
    Roster/csvexportaction.h \
    Roster/offsethighcvprogrammerfacade.h \
    Roster/resettingoffsethighcvprogrammerfacade.h \
    Throttle/storexmlthrottleslayoutaction.h \
    Throttle/storedefaultxmlthrottleslayoutaction.h \
    Throttle/loadxmlthrottleslayoutaction.h \
    Throttle/loaddefaultxmlthrottleslayoutaction.h \
    Throttle/speedpanel.h \
    Throttle/backgroundpanel.h \
    Roster/functionlabelpane.h \
    Throttle/controlpanelpropertyeditor.h \
    Roster/loconetconsist.h \
    loconet/LnOverTcp/lntcppreferences.h \
    loconet/lntcppreferencespanel.h \
    loconet/lntcpserver.h \
    loconet/lntcpserverframe.h \
    loconet/lntcpserveraction.h \
    lnsv2messagecontents.h \
    loconet/loconetmessageinterpret.h \
    internalconsistmanager.h \
    Signal/signalmastaddpane.h \
    Signal/dccsignalmastaddpane.h \
    Signal/lncpsignalmast.h \
    Signal/turnoutsignalmastaddpane.h \
    Signal/virtualsignalmastaddpane.h \
    Signal/signalheadsignalmastaddpane.h \
    Signal/matrixsignalmast.h \
    Signal/matrixsignalmastxml.h \
    Signal/matrixsignalmastaddpane.h \
    Signal/dccsignalheadxml.h \
    warrantshutdowntask.h \
    mergeprompt.h \
    Signal/dccsignalhead.h \
    Signal/tripleoutputsignalhead.h \
    Signal/tripleoutoutsignalheadxml.h \
    loconet/PR2/pr2adapter.h \
    loconet/PR2/pr2systemconnectionmemo.h \
    loconet/PR2/lnpr2powermanager.h \
    loconet/PR2/lnpr2throttlemanager.h \
    loconet/PR2/pr2throttle.h \
    loconet/PR2/pr2connectionconfig.h \
    loconet/PR2/pr2connectionconfigxml.h \
    loconet/PR2/lnpr2packtizer.h \
    rfid/rfidinterface.h \
    rfid/rfidtrafficcontroller.h \
    rfid/rfidsystemconnectionmemo.h \
    rfid/rfidcomponentfactory.h \
    rfid/rfidmenu.h \
    rfid/rfidnamedpaneaction.h \
    rfid/rfidpanelinterface.h \
    rfid/rfidconnectiontypelist.h \
    connectiontypelist.h \
    rfid/standalonetrafficcontroller.h \
    rfid/standalonemessage.h \
    rfid/rfidprotocol.h \
    rfid/standalonereply.h \
    rfid/rfidreply.h \
    rfid/rfidreportermanagerxml.h \
    rfid/rfidsensormanagerxml.h \
    rfid/rfidserialconnectionconfigxml.h \
    rfid/rfidserialconnectionconfig.h \
    rfid/rfidserialdriveradapter.h \
    rfid/standalonesensormanager.h \
    rfid/standalonereportermanager.h \
    rfid/timeoutrfidreporter.h \
    rfid/rfidportcontroller.h \
    rfid/coreidrfidprotocol.h \
    rfid/timeoutrfidsensor.h \
    rfid/olimexrfidprotocol.h \
    rfid/id12larfidprotocol.h \
    zeroconfservice.h \
    zeroconfeventlistener.h \
    zeroconfserviceevent.h \
    stacknxpanel.h \
    sound.h \
    mixerprovider.h \
    jmriclient/jmriclientportcontroller.h \
    jmriclient/jmriclientsystemconnectionmemo.h \
    jmriclient/jmriclientinterface.h \
    jmriclient/jmriclienttrafficcontroller.h \
    jmriclient/jmriclientlistener.h \
    jmriclient/jmriclientmessage.h \
    jmriclient/jmriclientreply.h \
    jmriclient/networkdriveradapter.h \
    zeroconfclient.h \
    jmriclient/jmriclientconnectionconfig.h \
    jmriclient/jmriclientconnectionconfigxml.h \
    jmriclientconnectiontypelist.h \
    jmriclient/jmriclientpowermanager.h \
    jmriclient/jmriclientturnoutmanagerxml.h \
    jmriclient/jmriclientturnoutmanager.h \
    jmriclient/jmriclientsensormanagerxml.h \
    jmriclient/jmriclientsensormanager.h \
    jmriclient/jmriclientsensor.h \
    jmriclient/jmriclientturnout.h \
    jmriclient/jmriclientlight.h \
    jmriclient/jmriclientlightmanager.h \
    jmriclient/jmriclientlightmanagerxml.h \
    jmriclient/jmriclientreporter.h \
    jmriclient/jmriclientreportermanager.h \
    jmriclient/jmriclientreportermanagerxml.h \
    simpleserver.h \
    simpleservermanager.h \
    simpleserveraction.h \
    simpleserverpreferences.h \
    abstractserverpreferences.h \
    simpleservermenu.h \
    simpleserver/abstractpowerserver.h \
    simpleserver/simplepowerserver.h \
    simpleserver/abstractsensorserver.h \
    simpleserver/abstractturnoutserver.h \
    simpleserver/simpleturnoutserver.h \
    simpleserver/simplesensorserver.h \
    jmriclient/jmriclientcomponentfactory.h \
    jmriclient/jmriclientmenu.h \
    jmriclient/jmriclientmonpane.h \
    jmriclient/jmriclientmonaction.h \
    jmriclient/packetgenaction.h \
    jmriclient/packetgenframe.h \
    servermenu.h \
    jmrisrcpservermenu.h \
    jmrisrcpserveraction.h \
    jmrisrcpservermanager.h \
    jmrisrcpserverpreferences.h \
    jmrisrcpserver.h \
    loconet/lnmessageserveraction.h \
    simpleserver/abstractlightserver.h \
    simpleserver/simplelightserver.h \
    simpleserver/abstractsignalheadserver.h \
    simpleserver/simplesignalheadserver.h \
    simpleserver/abstractreporterserver.h \
    simpleserver/simplereporterserver.h \
    lnpacketizerstrict.h \
    loconet/lntrafficrouter.h \
    consistpreferencesmanager.h \
    speedstepmode.h \
    rfid/transpondingtagmanager.h \
    rfid/conflictingsystemconnectionmemo.h \
    rfid/transpondingtag.h \
    rfid/defaultidtagmanagerxml.h \
    rfid/proxyidtagmanager.h \
    rfid/abstractidtagreporter.h \
    rfid/idtaglistener.h \
    rfid/addressedidtag.h \
    rfid/reportervariant.h \
    loconet/lndeferprogrammer.h \
    proxyturnoutmanagerxml.h \
    proxysensormanagerxml.h \
#    namedbeancombobox.h \
    trackreporter.h \
    loconet/bluetooth/loconetbluetoothadapter.h \
    Signal/signals.h \
    scwarrant.h \
    Roster/rosterframestartupactionfactory.h \
    Roster/rostermediapane.h \
    loconet/Pr4/pr4adapter.h \
    loconet/Pr4/pr4systemconnectionmemo.h \
    loconet/Pr4/pr4selectpane.h \
    loconet/Pr4/pr4connectionconfig.h \
    loconet/Pr4/pr4connectionconfigxml.h \
    consisttable.h \
    loconet/Pr3/pr3connectionconfigxml.h \
    loconet/HexFile/hexfilesystemconnectionmemo.h \
    multimeter.h \
    abstractmultimeter.h \
    loconet/lnmultimeter.h \
    loconet/locostatsfunc.h \
    loconet/loconetinterfacestatslistener.h \
    loconet/rawstatus.h \
    loconet/LocoBufferII/locobufferiistatus.h \
    loconet/PR2/pr2status.h \
    loconet/pr3ms100modestatus.h \
    loconet/DCS240/dcs240connectionconfig.h \
    loconet/DCS240/usbdcs240adapter.h \
    loconet/DCS240/dcs240connectionconfigxml.h \
    loconet/DCS240/usbdcs240systemconnectionmemo.h \
    loconet/LocoBufferII/locobufferiiadapter.h \
    loconet/LocoBufferII/locobufferiiconnectionconfig.h \
    loconet/LocoBufferII/locobufferiiconnectionconfigxml.h \
    loconet/DCS52/dcs52usbmodeselectpane.h \
    loconet/lnpanel.h \
    loconet/DCS240/dcs240usbmodeselectpane.h \
    loconet/DCS52/dcs52connectionconfig.h \
    loconet/DCS52/dcs52connectionconfigxml.h \
    loconet/DCS52/usbdcs52adapter.h \
    loconet/DCS52/usbdcs52systemconnectionmemo.h \
    cabsignal.h \
    defaultcabsignal.h \
    cabsignalmanager.h \
    cabsignallistlistener.h \
    abstractcabsignalmanager.h \
    loconet/lncabsignalmanager.h \
    loconet/lncabsignal.h \
    hasconnectionbutunabletoconnectexception.h \
    cabsignaltablemodel.h \
    defaultcabsignalmanager.h \
    timerutil.h \
    cabsignalpane.h \
    cabsignalaction.h \
    zeroconfservicemanager.h \
    networktopologylistener.h \
    networktopologyevent.h \
    zeroconfpreferences.h \
    logix/learnthrottleframe.h \
    defaultsystemconnectionmemo.h \
    lnpredefinedmeters.h \
    meterupdatetask.h \
    meter.h \
    loconet/lnmeterinittask.h \
    metermanager.h \
    currentmeter.h \
    voltagemeter.h \
    abstractanalogio.h \
    defaultmeter.h \
    analogio.h \
    loconet/lniplimplementation.h \
    loconet/lndplxgrpinfoimpl.h \
    loconet/lndplxgrpinfoimplconstants.h \
    loconet/duplexgroupmessagetype.h \
    meterframe.h \
    meterframemanager.h \
    meterframemanagerxml.h \
    meteraction.h \
    proxymetermanager.h \
    internalmetermanager.h \
    abstractmetermanager.h \
    internalmetermanagerxml.h \
    abstractmetermanagerxml.h \
    ctc/nbhsensor.h \
    ctc/ctcexception.h \
    ctc/ctcexceptionbuffer.h \
    ctc/ctcmanager.h \
    ctc/projectscommonsubs.h \
    ../LayoutEditor/disposable.h \
    ctc/programproperties.h \
    ctc/ctcserialdata.h \
    ctc/nbhsignal.h \
    ctc/nbhturnout.h \
    ctc/otherdata.h \
    ctc/codebuttonhandlerdata.h \
    ctc/trafficlockingdata.h \
    ctc/frmtrl_rules.h \
    ctc/ctcfiles.h \
    ctc/callondata.h \
    ctc/topologyinfo.h \
    ctc/commonsubs.h \
    ctc/awtwindowproperties.h \
    ctc/checkjmriobject.h \
    ctc/ctcmain.h \
    ctc/codebuttonhandler.h \
    ctc/ctcconstants.h \
    ctc/lockedroutesmanager.h \
    ctc/turnoutlock.h \
    ctc/ctceditoraction.h \
    ctc/frmmainform.h \
    ctc/columns.h \
    ctc/frmswdi.h \
    ctc/codebuttonhandlerdataroutines.h \
    ctc/ctcrunaction.h \
    ctc/ctcmanagerxml.h \
    ctc/frmaddmodifyctccolumn.h \
    ctc/frmcb.h \
    ctc/frmabout.h \
    ctc/frmguidesign.h \
    ctc/frmco.h \
    ctc/importexternaldata.h \
    ctc/importotherdata.h \
    ctc/importcodebuttonhandlerdata.h \
    ctc/callonentry.h \
    ctc/trafficlockingentry.h \
    ctc/createguiobjectsxmlfile.h \
    ctc/frmdefaults.h \
    ctc/frmdebugging.h \
    ctc/frmsidi.h \
    ctc/frmswdl.h \
    ctc/frmtrl.h \
    ctc/topology.h \
    ctc/frmsidl.h \
    ctc/frmtul.h \
    ctc/frmil.h \
    ctc/frmfleeting.h \
    ctc/frmpatterns.h \
    ctc/frmfixerrors.h \
    ctc/lockedroute.h \
    ctc/reentrantlock.h \
    ctc/lock.h \
    ctc/signaldirectionindicators.h \
    ctc/signaldirectionindicatorsinterface.h \
    ctc/requesteddirectionobserved.h \
    ctc/codebuttonsimulator.h \
    ctc/switchdirectionlever.h \
    ctc/signaldirectionlever.h \
    ctc/switchdirectionindicators.h \
    ctc/trafficlockinginfo.h \
    ctc/fleeting.h \
    ctc/callon.h \
    ctc/switchindicatorsroute.h \
    ctc/indicationlockingsignals.h \
    ctc/trafficlocking.h \
    storemenu.h \
    managercombobox.h \
    abstractblockmanager.h \
    abstractsectionmanager.h \
    abstractnamedbeanhandlemanager.h \
    abstractroutemanager.h \
    loconet/lncvdevicesmanager.h \
    loconet/lncvdevices.h \
    loconet/lncvdevice.h \
    loconet/lncvmessagecontents.h \
    loconet/programmingtool.h \
    loconet/lncvprogtablemodel.h \
    loconet/lncvprogpane.h \
    loconet/lncvprogaction.h \
    logix/learncontrolpanel.h \
    logix/learnfunctionpanel.h \
    logix/learnspeedpanel.h \
    abstractprogrammerserver.h \
    searchbar.h \
    cvutil.h


 !contains(FTDI, 1) {
    HEADERS +=
 }
 equals(ENABLE_LOGIXNG, "Y") {
 HEADERS += \
    logixng/stringexpressionconstantxml.h \
    logixng/stringexpressionmemoryxml.h \
    logixng/defaultconditionalngmanagerxml.h \
    logixng/logix_emulator.h \
    logixng/actiontimer.h \
    logixng/logixngmoduletableaction.h \
    logixng/moduleeditor.h \
    logixng/moduleeditormalesocket.h \
    logixng/andswing.h \
    logixng/expressionlight.h \
    logixng/expressionlightxml.h \
    logixng/expressionsensorxml.h \
    logixng/expressionturnoutxml.h \
    logixng/falsexml.h \
    logixng/hold.h \
    logixng/holdxml.h \
    logixng/notswing.h \
    logixng/orxml.h \
    logixng/triggeroncexml.h \
    logixng/stringformula.h \
    logixng/stringformulaswing.h \
    logixng/stringformulaxml.h \
    logixng/stringio.h \
    logixng/defaultmaleanalogactionsocketxml.h \
    logixng/defaultmaledigitalactionsocketxml.h \
    logixng/defaultmaledigitalbooleanactionsocketxml.h \
    logixng/defaultmaledigitalexpressionsocketxml.h \
    logixng/defaultmalestringactionsocketxml.h \
    logixng/defaultmalestringexpressionsocketxml.h \
    logixng/abstractmalesocketxml.h \
    logixng/defaultmaleanalogexpressionsocketxml.h \
    logixng/actionfactory_loconet.h \
    logixng/digitalmanyswing.h \
    logixng/triggeronceswing.h \
    logixng/ifthenelseswing.h \
    logixng/for.h \
    logixng/forswing.h \
    logixng/analogactionmemoryxml.h \
    logixng/analogfactory_expressions.h \
    logixng/analogmanyxml.h \
    logixng/defaultaledigitalactionsocketswing.h \
    logixng/defaultmaleanalogactionsocketswing.h \
    logixng/defaultmaledigitalbooleanactionsocketswing.h \
    logixng/defaultmaledigitalexpressionsocketswing.h \
    logixng/defaultmalestringexpressionsocketswing.h \
    logixng/moduleeditormalesocketswing.h \
    logixng/actions/digitalfactory.h \
    logixng/expressions/digitalfactory_expressions.h \
    logixng/tableforeach.h \
    logixng/tableforeachxml.h \
    logixng/convertfunctions.h \
    logixng/mathfunctions.h \
    logixng/false.h \
    logixng/falseswing.h \
    logixng/logixng_metatypes.h \
    logixng/tableforeachswing.h \
    logixng/digitalformula.h \
    logixng/digitalformulaswing.h \
    logixng/orswing.h \
    logixng/trueswing.h \
    logixng/truexml.h \
    logixng/actionsensor.h \
    logixng/actionturnoutlock.h \
    logixng/andxml.h \
    logixng/antecedent.h \
    logixng/antecedentswing.h \
    logixng/antecedentxml.h \
    logixng/executedelayed.h \
    logixng/not.h \
    logixng/protectedtimertask.h \
    logixng/timerunit.h \
    logixng/triggeronce.h \
    logixng/true.h \
    logixng/expressionsensor.h \
    logixng/expressionsensorswing.h \
    logixng/and.h \
    logixng/expressionmemory.h \
    logixng/actionmemory.h \
    logixng/importconditional.h \
    logixng/logixnginitializationtable.h \
    logixng/importlogix.h \
    logixng/importlogixaction.h \
    logixng/importlogixframe.h \
    logixng/logixnginitializationtableaction.h \
    logixng/logixngmenu.h \
    logixng/startstopalllogixngsaction.h \
    logixng/abstractanalogactionswing.h \
    logixng/analogactionlightintensity.h \
    logixng/analogactionlightintensityswing.h \
    logixng/analogactionmemoryswing.h \
    logixng/analogexpressionanalogioswing.h \
    logixng/analogexpressionconstantswing.h \
    logixng/analogformulaswing.h \
    logixng/analogmanyswing.h \
    logixng/digitalbooleanmany.h \
    logixng/digitalbooleanmanyswing.h \
    logixng/digitalbooleanonchangeswing.h \
    logixng/expressionturnout.h \
    logixng/timesincemidnightswing.h \
    logixng/debuggermaleanalogexpressionsocketfactory.h \
    logixng/stringexpressionmemory.h \
    logixng/actionturnout.h \
    logixng/stringactionmemory.h \
    logixng/analogactionmemory.h \
    logixng/abstractdigitalbooleanaction.h \
    logixng/abstractstringaction.h \
    logixng/abstractstringexpression.h \
    logixng/debuggerinstanceinitializer.h \
    logixng/digitalbooleanonchange.h \
    logixng/dostringaction.h \
    logixng/lastresultofdigitalexpression.h \
    #logixng/logix.h \
    logixng/stringexpressionconstant.h \
    logixng/stringmany.h \
    logixng/abstractanalogaction.h \
    logixng/analogmany.h \
    logixng/abstractdigitalexpression.h \
    logixng/digitalmany.h \
    logixng/doanalogaction.h \
    logixng/ifthenelse.h \
    logixng/or.h \
    logixng/actionfactory.h \
    logixng/categoryloconet.h \
    logixng/debuggermaleanalogactionsocket.h \
    logixng/debuggermaleanalogactionsocketfactory.h \
    logixng/debuggermaledigitalactionsocket.h \
    logixng/debuggermaledigitalactionsocketfactory.h \
    logixng/debuggermaledigitalbooleanactionsocket.h \
    logixng/debuggermaledigitalbooleanactionsocketfactory.h \
    logixng/debuggermaledigitalexpressionsocket.h \
    logixng/debuggermaledigitalexpressionsocketfactory.h \
    logixng/debuggermalestringactionsocket.h \
    logixng/debuggermalestringactionsocketfactory.h \
    logixng/debuggermalestringexpressionsocket.h \
    logixng/debuggermalestringexpressionsocketfactory.h \
    logixng/defaultanalogactionmanager.h \
    logixng/defaultconditionalngmanager.h \
    logixng/defaultdigitalactionmanager.h \
    logixng/defaultdigitalbooleanactionmanager.h \
    logixng/defaultdigitalexpressionmanager.h \
    logixng/defaultfemaledigitalbooleanactionsocket.h \
    logixng/defaultstringactionmanager.h \
    logixng/defaultstringexpressionmanager.h \
    logixng/digitalbooleanfactory.h \
    logixng/digitalexpressionfactory.h \
    logixng/expressionfactory.h \
    logixng/logixng_analoginstanceinitializer.h \
    logixng/logixng_digitalinstanceinitializer.h \
    logixng/logixng_stringinstanceinitializer.h \
    logixng/stringfactory.h \
    logixng/abstractdebuggermalesocketswing.h \
    logixng/abstractdigitalexpressionswing.h \
    logixng/abstractstringactionswing.h \
    logixng/abstractstringexpressionswing.h \
    logixng/defaultfemalestringactionsocket.h \
    logixng/defaultmoduleswing.h \
    logixng/abstractbooleanactionswing.h \
    logixng/abstractanalogexpressionswing.h \
    logixng/abstractmalesocketswing.h \
    logixng/analogexpressionmemoryswing.h \
    logixng/defaultinternalnamedtable.h \
    logixng/defaultmaleanalogactionsocket.h \
    logixng/defaultmaledigitalactionsocket.h \
    logixng/defaultmaledigitalbooleanactionsocket.h \
    logixng/defaultmaledigitalexpressionsocket.h \
    logixng/defaultmalestringactionsocket.h \
    logixng/defaultmalestringactionsocketswing.h \
    logixng/defaultnamedtablemanager.h \
    logixng/defaultmodule.h \
    logixng/defaultmodulemanager.h \
    logixng/defaultmodulexml.h \
    logixng/abstractmanagerxml.h \
    logixng/defaultanalogactionmanagerxml.h \
    logixng/defaultanalogexpressionmanagerxml.h \
    logixng/defaultdigitalactionmanagerxml.h \
    logixng/defaultdigitalbooleanactionmanagerxml.h \
    logixng/defaultdigitalexpressionmanagerxml.h \
    logixng/defaultmalestringexpressionsocket.h \
    logixng/defaultmodulemanagerxml.h \
    logixng/defaultnamedtablemanagerxml.h \
    logixng/defaultstringactionmanagerxml.h \
    logixng/defaultstringexpressionmanagerxml.h \
    logixng/malesocketxml.h \
    logixng/defaultmaleanalogexpressionsocket.h \
    logixng/defaultfemalestringexpressionsocket.h \
    logixng/genericexpressionvariable.h \
    logixng/abstractanalogexpression.h \
    logixng/analogexpressionanalogio.h \
    logixng/analogexpressionconstant.h \
    logixng/analogexpressionmemory.h \
    logixng/analogfactory.h \
    logixng/analogformula.h \
    logixng/debuggermaleanalogexpressionfactory.h \
    logixng/debuggermaleanalogexpressionsocket.h \
    logixng/defaultanalogexpressionmanager.h \
    logixng/defaultfemaleanalogactionsocket.h \
    logixng/defaultfemaleanalogactionsocketfactory.h \
    logixng/defaultfemaleanalogexpressionsocket.h \
    logixng/defaultfemaleanalogexpressionsocketfactory.h \
    logixng/defaultfemaledigitalactionsocketfactory.h \
    logixng/defaultfemaledigitalexpressionsocket.h \
    logixng/defaultfemaledigitalexpressionsocketfactory.h \
    logixng/defaultfemalegenericexpressionsocket.h \
    logixng/defaultfemalesocketmanager.h \
    logixng/defaultfemalestringactionsocketfactory.h \
    logixng/defaultfemalestringexpressionsocketfactory.h \
    logixng/maleanalogexpressionsocketfactory.h \
    logixng/timesincemidnight.h \
    logixng/actionatomicboolean.h \
    logixng/defaultconditionalng.h \
    logixng/defaultconditionalngscaffold.h \
    logixng/defaultfemaledigitalactionsocket.h \
    logixng/defaultlogixngpreferences.h \
    logixng/executelock.h \
    logixng/logixng_instanceinitializer.h \
    logixng/actionsignalheadswing.h \
    logixng/abstractbasemanager.h \
    logixng/abstractnamedtable.h \
    logixng/defaultanonymoustable.h \
    logixng/defaultcsvnamedtable.h \
    logixng/defaultlogixnginitializationmanager.h \
    logixng/editcommentdialog.h \
    logixng/functionshelpdialog.h \
    logixng/localvariabletablemodel.h \
    logixng/abstractdebuggermalesocket.h \
    logixng/abstractdigitalactionswing.h \
    logixng/abstractswingconfigurator.h \
    logixng/actionpositionable.h \
    logixng/actionpositionableswing.h \
    logixng/categorydisplay.h \
    logixng/debuggersymboltablemodel.h \
    logixng/swingconfiguratorinterface.h \
    logixng/swingtools.h \
    logixng/clipboardeditor.h \
    logixng/conditionalngdebugger.h \
    logixng/conditionalngeditor.h \
    logixng/debugger.h \
    logixng/treeeditor.h \
    logixng/treepane.h \
    logixng/treeviewer.h \
    logixng/logixngeditor.h \
    logixng/logixngtableaction.h \
    logixng/abstractdigitalaction.h \
    logixng/abstractlogixngtableaction.h \
    logixng/calculateexception.h \
    logixng/clockfunctions.h \
    logixng/constant.h \
    logixng/defaultstack.h \
    logixng/defaultsymboltable.h \
    logixng/expressionnode.h \
    logixng/expressionnodearithmeticoperator.h \
    logixng/expressionnodeassignmentoperator.h \
    logixng/expressionnodebooleanoperator.h \
    logixng/expressionnodecomparingoperator.h \
    logixng/expressionnodefloatingnumber.h \
    logixng/expressionnodefunction.h \
    logixng/expressionnodeidentifier.h \
    logixng/expressionnodeintegernumber.h \
    logixng/expressionnodestring.h \
    logixng/expressionnodeternaryoperator.h \
    logixng/function.h \
    logixng/functionfactory.h \
    logixng/functionmanager.h \
    logixng/functionnotexistsexception.h \
    logixng/invalidsyntaxexception.h \
    logixng/localvariableexpressionvariable.h \
    logixng/logixngtabletableaction.h \
    logixng/namedtablemanager.h \
    logixng/parserexception.h \
    logixng/recursivedescentparser.h \
    logixng/referenceutil.h \
    logixng/stringfunctions.h \
    logixng/tableeditor.h \
    logixng/token.h \
    logixng/tokenizer.h \
    logixng/tokentype.h \
    logixng/typeconversionutil.h \
    logixng/variable.h \
    logixng/wrongnumberofparametersexception.h \
    #logixng/manager.h\
    logixng/maleanalogactionsocketfactory.h \
    logixng/maleanalogexpressionsocket.h \
    logixng/maledigitalactionsocket.h \
    logixng/maledigitalactionsocketfactory.h \
    logixng/maledigitalbooleanactionsocketfactory.h \
    logixng/maledigitalexpressionsocketfactory.h \
    logixng/malestringactionsocket.h \
    logixng/malestringactionsocketfactory.h \
    logixng/malestringexpressionsocket.h \
    logixng/malestringexpressionsocketfactory.h \
    logixng/namedbeanaddressing.h \
    logixng/namedtable.h \
    logixng/stringaction.h \
    logixng/stringactionbean.h \
    logixng/stringactionfactory.h \
    logixng/stringactionmanager.h \
    logixng/stringexpressionbean.h \
    logixng/stringexpressionfactory.h \
    logixng/stringexpressionmanager.h \
    logixng/table.h \
    logixng/tableroworcolumn.h \
    logixng/Analogexpressionbean.h \
    logixng/abortconditionalexecutionexception.h \
    logixng/analogaction.h \
    logixng/analogactionbean.h \
    logixng/analogactionfactory.h \
    logixng/analogactionmanager.h \
    logixng/analogexpression.h \
    logixng/analogexpressionfactory.h \
    logixng/analogexpressionmanager.h \
    logixng/anonymoustable.h \
    logixng/digitalaction.h \
    logixng/digitalactionbean.h \
    logixng/digitalactionfactory.h \
    logixng/digitalactionmanager.h \
    logixng/digitalbooleanaction.h \
    logixng/digitalbooleanactionbean.h \
    logixng/digitalbooleanactionfactory.h \
    logixng/digitalbooleanactionmanager.h \
    logixng/digitalexpression.h \
    logixng/digitalexpressionbean.h \
    logixng/digitalexpressionmanager.h \
    logixng/femaleanalogactionsocket.h \
    logixng/femaleanalogexpressionsocket.h \
    logixng/femaledigitalactionsocket.h \
    logixng/femaledigitalbooleanactionsocket.h \
    logixng/femaledigitalexpressionsocket.h \
    logixng/femalegenericexpressionsocket.h \
    logixng/femalesocketfactory.h \
    logixng/femalestringactionsocket.h \
    logixng/femalestringexpressionsocket.h \
    logixng/is_isnot_enum.h \
    logixng/maleanalogactionsocket.h \
    logixng/maledigitalbooleanactionsocket.h \
    logixng/maledigitalexpressionsocket.h \
    logixng/stringexpression.h \
    logixng/abstractlogixngeditor.h \
    logixng/abortconditionalngexecutionexception.h \
    logixng/abstractmalesocket.h \
    logixng/base.h \
    logixng/basemanager.h \
    logixng/category.h \
    logixng/conditionalng.h \
    logixng/conditionalng_manager.h \
    logixng/debugable.h \
    logixng/defaultlogixng.h \
    logixng/defaultlogixngmanager.h \
    logixng/defaultlogixngmanagerxml.h \
    logixng/errorhandlingdialog.h \
    logixng/errorhandlingdialog_multiline.h \
    logixng/femalesocket.h \
    logixng/femalesocketmanager.h \
    logixng/logixng.h \
    logixng/logixng_initializationmanager.h \
    logixng/logixng_manager.h \
    logixng/logixng_thread.h \
    logixng/logixngpreferences.h \
    logixng/malesocket.h \
    logixng/malesocketfactory.h \
    logixng/module.h \
    logixng/modulemanager.h \
    logixng/socketalreadyconnectedexception.h \
    logixng/symboltable.h \
    logixng/clipboard.h \
    logixng/stack.h \
    logixng/abstractbase.h \
    logixng/abstractfemalesocket.h \
    logixng/clipboardmany.h \
    logixng/defaultclipboard.h \
    logixng/defaultfemaleanysocket.h \
    logixng/femaleanysocket.h \
    logixng/femalesocketlistener.h \
    logixng/femalesocketoperation.h
}
symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE60D7F4C
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = libPr3.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
#ifdef LAYOUTS
#include "Layout/connectivityutil.h"
#include "Layout/layoutturnout.h"
#include "Layout/layoutblock.h"
#
    }
    INSTALLS += target
}

INCLUDEPATH += $$PWD LocoIObuild_nr

win32 {
QMAKE_LFLAGS += -static-libgcc
}

#win32:CONFIG(release, debug|release): LIBS += -lQtSerialPort
#else:win32:CONFIG(debug, debug|release):  LIBS += -lQtSerialPortd

unix:!symbian{
 maemo5{
  target.path = /opt$${LIB_INSTALL_DIR}
#  headers.path = /opt$${INCLUDES_INSTALL_DIR}
 }
 else{
  target.path = $${LIB_INSTALL_DIR}
#  headers.path = $${INCLUDES_INSTALL_DIR}
 }
 INSTALLS += target #headers
}
win32:{
  target.path = $${DLL_INSTALL_DIR}
#  headers.path = $${INCLUDES_INSTALL_DIR}
 INSTALLS += target #headers
}
TRANSLATIONS += \
    languages/libPr3_de.ts \
    languages/libPr3_en.ts

RESOURCES += \
    libPr3.qrc

FORMS += \
    Throttle/throttlewindow.ui \
    Roster/rosterentrypane.ui \
    Roster/paneprogframe.ui \
    Roster/rosterframe.ui \
    Roster/factoryresetaction.ui \
    Roster/optionsdialog.ui \
    Throttle/addresspanel.ui \
    Throttle/functionpanel.ui \
    loconet/loconetmsgdialog.ui \
    loconet/querycvdialog.ui \
    Roster/rostermediapane.ui


OTHER_FILES += \
    proglistener. \
    turnouts.sip \
    configure.py

DEPENDPATH += . Signal ./Throttle Roster LocoIO loconet/Pr3 loconet Json WiThrottle Web rfid
INCLUDEPATH += . Signal ./Throttle Roster LocoIO loconet/Pr3 loconet Json WiThrottle Web rfid

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

INCLUDEPATH += "~/Qt/5.7/gcc_64/include/QtMultimedia"

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/release/ -lappslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/debug/ -lappslib
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/ -lappslib
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/ -lappslibd


INCLUDEPATH += $$PWD/../appslib $$PWD/../appslib/operations
DEPENDPATH += $$PWD/../appslib $$PWD/../appslib/operations

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LocoIO/release/ -lLocoIO
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LocoIO/debug/ -lLocoIO
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../LocoIO/ -lLocoIO
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LocoIO/ -lLocoIOd

INCLUDEPATH += $$PWD/../LocoIO
DEPENDPATH += $$PWD/../LocoIO



#win32:INCLUDEPATH += C:/Users/Allen/Downloads/zlib127/zlib-1.3.4/

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/release/ -lJavaQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/debug/ -lJavaQt
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/ -lJavaQt
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/ -lJavaQtd


INCLUDEPATH += $$PWD/../JavaQt
DEPENDPATH += $$PWD/../JavaQt


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LayoutEditor/release/ -lLayoutEditor
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LayoutEditor/debug -lLayoutEditor
#else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../LayoutEditor/ -lLayoutEditor
#else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LayoutEditor/ -lLayoutEditord


INCLUDEPATH += $$PWD/../LayoutEditor $$PWD/../LayoutEditor/scripts
DEPENDPATH += $$PWD/../LayoutEditor $$PWD/../LayoutEditor/scripts

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPref/release/ -lPref
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPref/debug/ -lPref
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPref/ -lPref
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPref/ -lPrefd


INCLUDEPATH += $$PWD/../libPref/
DEPENDPATH += $$PWD/../libPref

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Tables/release/ -lTables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Tables/debug/ -lTables
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../Tables/ -lTables
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Tables/ -lTablesd


INCLUDEPATH += $$PWD/../Tables
DEPENDPATH += $$PWD/../Tables

DISTFILES += \
 ../logixng_config.prf

#contains(WEBAPP, 1) {

#unix:!macx: LIBS += -L$$PWD/../QtWebApp/ -lQtWebAppd

#INCLUDEPATH += $$PWD/../QtWebApp $$PWD/../QtWebApp/httpserver/
#DEPENDPATH += $$PWD/../QtWebApp $$PWD/../QtWebApp/httpserver/
#message("libPr3: link to libQtWebAppd")
#}

DEFINES += QZEROCONF_STATIC


unix|win32: LIBS += -L$$PROJ_DIR/QtZeroConf-master/ -lQtZeroConf

INCLUDEPATH += $$PROJ_DIR/QtZeroConf-master
DEPENDPATH += $$PROJ_DIR/QtZeroConf-master

unix:exists($$PROJ_DIR/QtZeroConf-master/libQtZeroConf.so.1) {
message($$PROJ_DIR/QtZeroConf-master/libQtZeroConf.so.1 found)
} else {
message(LibPr3: $$PROJ_DIR/QtZeroConf-master/libQtZeroConf.so.1 not found)
}


##unix|win32: LIBS += -L$$PWD/../QtWebApp/ -lQtWebAppd

#INCLUDEPATH += $$PWD/../QtWebApp $$PWD/../QtWebApp/httpserver/
#DEPENDPATH += $$PWD/../QtWebApp $$PWD/../QtWebApp/httpserver/

#exists($$PWD/../QtWebApp/libQtWebAppd.so.1) {
#message(libPr3: $$PWD/../QtWebApp/libQtWebAppd.so.1 found)
#} else {
#message(libPr3: $$PWD/../QtWebApp/libQtWebAppd.so.1 not found)
#}



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../operations/release/ -loperations
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../operations/debug/ -loperations
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../operations/ -loperations
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../operations/ -loperationsd


INCLUDEPATH += $$PWD/../operations
DEPENDPATH += $$PWD/../operations


unix|win32: LIBS += -L$$PWD/../../../../QtZeroConf-master/ -lQtZeroConf

INCLUDEPATH += $$PWD/../../../../QtZeroConf-master
DEPENDPATH += $$PWD/../../../../QtZeroConf-master



#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../Downloads/QtWebApp/build-QtWebApp-Desktop_Qt_5_15_2_GCC_64bit-Debug/release/ -lQtWebAppd
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../Downloads/QtWebApp/build-QtWebApp-Desktop_Qt_5_15_2_GCC_64bit-Debug/debug/ -lQtWebAppd
#else:unix: LIBS += -L$$PWD/../../../../../Downloads/QtWebApp/build-QtWebApp-Desktop_Qt_5_15_2_GCC_64bit-Debug/ -lQtWebAppd

#INCLUDEPATH += $$PWD/../../../../../Downloads/QtWebApp/build-QtWebApp-Desktop_Qt_5_15_2_GCC_64bit-Debug
#DEPENDPATH += $$PWD/../../../../../Downloads/QtWebApp/build-QtWebApp-Desktop_Qt_5_15_2_GCC_64bit-Debug

unix|win32: LIBS += -L$$PWD/../../../../QtWebApp/QtWebApp/ -lQtWebAppd

INCLUDEPATH += $$PWD/../../../../QtWebApp/QtWebApp
DEPENDPATH += $$PWD/../../../../QtWebApp/QtWebApp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../QtWebApp/QtWebApp/ -lQtWebAppd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../QtWebApp/QtWebApp/ -lQtWebAppdd
else:unix: LIBS += -L$$PWD/../../../../QtWebApp/QtWebApp/ -lQtWebAppd

INCLUDEPATH += $$PWD/../../../../QtWebApp/QtWebApp
DEPENDPATH += $$PWD/../../../../QtWebApp/QtWebApp
