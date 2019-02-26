#-------------------------------------------------
#
# Project created by QtCreator 2013-03-22T17:32:56
#
#-------------------------------------------------
unix:{
QTSERIALPORT_PROJECT_ROOT = ~/Projects/qtserialport
}
win32:{
QTSERIALPORT_PROJECT_ROOT =C:/Users/Allen/Projects/qt-qtserialport-stable/qt-qtserialport
}
greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets gui serialport multimedia websockets testlib #webkitwidgets
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}

win32_msvc: {
 QMAKE_CXXFLAGS += /wd4290
 QMAKE_CFLAGS_DEBUG += /wd4290
}

APPNAME = "LocoNetMonitor"
APPVERSION = 0.1

PREFIX = /home/allen/pythonqt-code

MOC_DIR = moc_obj
OBJECTS_DIR += moc_obj

#QT       -= gui
QT       += core xml  gui printsupport   sql network  multimedia #webkitwidgets

TARGET = Pr3
TEMPLATE = lib
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
  message("libPr3: libQtWebAppd found!")
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

win32:exists("C:/Program Files (x86)/local/lib/PythonQt.dll") {
 ENABLE_SCRIPTING = "Y"
}
unix:exists(~/Projects/PythonQt-master/lib/libPythonQt_d.so) {
 ENABLE_SCRIPTING = "Y"
}
#CONFIG += scripts
equals(ENABLE_SCRIPTING, "Y") {
    DEFINES += SCRIPTING_ENABLED
}

DEFINES += USE_THREAD

SOURCES += \
    loconetmessage.cpp \
    lnconstants.cpp \
    llnmon.cpp \
    serialport.cpp \
    dccmanufacturerlist.cpp \
    lnconnectiontypelist.cpp \
    activeflag.cpp \
    loconetlistener.cpp \
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
    systemconnectionmemomanager.cpp \
    systemconnectionmemo.cpp \
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
    abstractproxymanager.cpp \
    pr3systemconnectionmemo.cpp \
    proxyreportermanager.cpp \
    proxysensormanager.cpp \
    proxyturnoutmanager.cpp \
    internalsensormanager.cpp \
    internalturnoutmanager.cpp \
    abstractmemory.cpp \
    physicallocation.cpp \
    scale.cpp \
    defaultmemorymanager.cpp \
    abstractmemorymanager.cpp \
    defaultmemory.cpp \
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
    basicrosterentry.cpp \
    abstractthrottle.cpp \
    commandstation.cpp \
    nmrapacket.cpp \
    dccconsist.cpp \
    throttle.cpp \
    dccconsistmanager.cpp \
    abstractthrottlemanager.cpp \
    lnthrottlemanager.cpp \
    proglistener.cpp \
    throttlemanager.cpp \
    consistlistener.cpp \
    rfid/rfidusb.cpp \
    defaultroutemanager.cpp \
    defaultroute.cpp \
    decimalformat.cpp \
    blockvaluefile.cpp \
    abstractlightmanager.cpp \
    lnlightmanager.cpp \
    lnlight.cpp \
    abstractlight.cpp \
    lightcontrol.cpp \
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
    Roster/indexedcvtablemodel.cpp \
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
    Roster/indexedenumvariablevalue.cpp \
    Roster/indexedvariablevalue.cpp \
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
    Roster/indexedcombocheckbox.cpp \
    Roster/indexedpairvariablevalue.cpp \
    Roster/decvarslider.cpp \
    Roster/comboonradiobutton.cpp \
    Roster/combooffradiobutton.cpp \
    Roster/indexedvarslider.cpp \
    Roster/rosterentrypane.cpp \
    Roster/decoderindexfile.cpp \
    Roster/defaultcomboboxmodel.cpp \
    Roster/busyglasspane.cpp \
    Roster/dccaddresspanel.cpp \
    Roster/paneprogpane.cpp \
    Roster/watchinglabel.cpp \
    Roster/vartextfield.cpp \
    Roster/fnmappanel.cpp \
    Roster/paneprogframe.cpp \
    Roster/paneopsprogframe.cpp \
    Roster/rosterframe.cpp \
    connectionstatus.cpp \
    Roster/abstractidentify.cpp \
    Roster/identifyloco.cpp \
    Roster/dcclocoaddressselector.cpp \
    Roster/factoryresetaction.cpp \
    Roster/rostermedia.cpp \
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
    memorymanager.cpp \
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
    Throttle/learnthrottleframe.cpp \
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
    LocoIO/lnpanel.cpp \
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
    loconet/Pr3/connectionconfigxml.cpp \
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
    loconet/jeditorpane.cpp \
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
    storexmlvsdecoderaction.cpp \
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
    rostergroupselector.cpp \
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
    consistlistlistener.cpp \
    Web/stringescapeutils.cpp \
    Throttle/windowpreferences.cpp \
    Throttle/locoaddressxml.cpp \
    loconetmenustartupaction.cpp \
    Web/aboutservlet.cpp \
    sprog/serialdriveradapter.cpp \
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
    zeroconfservice.cpp \
    zeroconfserviceevent.cpp \
    stacknxpanel.cpp \
    sound.cpp \
    mixerprovider.cpp

 !contains(FTDI, 1) {
    SOURCES +=
 }
HEADERS += \
    loconetmessage.h \
    lnconstants.h \
    llnmon.h \
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
    slotmanager.h \
    abstractprogrammer.h \
    programmer.h \
    loconetslot.h \
    slotlistener.h \
    systemconnectionmemomanager.h \
    systemconnectionmemo.h \
    loconetsystemconnectionmemo.h \
    powermanager.h \
    abstractpowermanager.h \
    lnpowermanager.h \
    loconetthrottledtransmitter.h \
    programmermanager.h \
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
    abstractproxymanager.h \
    pr3systemconnectionmemo.h \
    proxyreportermanager.h \
    proxysensormanager.h \
    proxyturnoutmanager.h \
    internalsensormanager.h \
    internalturnoutmanager.h \
    runnable.h \
    sensor.h \
    abstractmemory.h \
    physicallocationreporter.h \
    physicallocation.h \
    initializer.h \
    scale.h \
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
    nmrapacket.h \
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
    Roster/indexedcvtablemodel.h \
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
    Roster/indexedenumvariablevalue.h \
    Roster/indexedvariablevalue.h \
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
    Roster/indexedcombocheckbox.h \
    Roster/indexedpairvariablevalue.h \
    Roster/decvarslider.h \
    Roster/comboonradiobutton.h \
    Roster/combooffradiobutton.h \
    Roster/indexedvarslider.h \
    Roster/rosterentrypane.h \
    Roster/decoderindexfile.h \
    Roster/defaultcomboboxmodel.h \
    Roster/paneprogpane.h \
    Roster/itemlistener.h \
    Roster/panecontainer.h \
    Roster/busyglasspane.h \
    Roster/dccaddresspanel.h \
    Roster/watchinglabel.h \
    Roster/vartextfield.h \
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
    Roster/rostermedia.h \
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
    warrant.h \
    blockorder.h \
    opath.h \
    throttlesetting.h \
    oblockmanager.h \
    engineer.h \
    Throttle/learnthrottleframe.h \
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
    LocoIO/lnpanel.h \
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
    loconet/Pr3/connectionconfigxml.h \
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
    loconet/jeditorpane.h \
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
    beaninterface.h \
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
    storexmlvsdecoderaction.h \
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
    sprog/serialdriveradapter.h \
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
    mixerprovider.h

 !contains(FTDI, 1) {
    HEADERS +=
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
    Roster/rostermedia.ui \
    Roster/optionsdialog.ui \
    Throttle/addresspanel.ui \
    Throttle/functionpanel.ui \
    loconet/loconetmsgdialog.ui \
    loconet/querycvdialog.ui


OTHER_FILES += \
    proglistener. \
    turnouts.sip \
    configure.py

DEPENDPATH += . Signal ./Throttle Roster LocoIO loconet/Pr3 loconet Json WiThrottle Web
INCLUDEPATH += . Signal ./Throttle Roster LocoIO loconet/Pr3 loconet Json WiThrottle Web

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
else:unix: LIBS += -L$$PWD/../appslib/ -lappslib

INCLUDEPATH += $$PWD/../appslib $$PWD/../appslib/operations
DEPENDPATH += $$PWD/../appslib $$PWD/../appslib/operations

INCLUDEPATH += $$PWD/../appslib $$PWD/../appslib/operations
DEPENDPATH += $$PWD/../appslib $$PWD/../appslib/operations

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LocoIO/release/ -lLocoIO
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LocoIO/debug/ -lLocoIO
else:unix: LIBS += -L$$PWD/../LocoIO/ -lLocoIO

INCLUDEPATH += $$PWD/../LocoIO
DEPENDPATH += $$PWD/../LocoIO



#win32:INCLUDEPATH += C:/Users/Allen/Downloads/zlib127/zlib-1.3.4/

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/release/ -lJavaQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/debug/ -lJavaQt
else:unix: LIBS += -L$$PWD/../JavaQt/ -lJavaQt

INCLUDEPATH += $$PWD/../JavaQt
DEPENDPATH += $$PWD/../JavaQt


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LayoutEditor/release/ -lLayoutEditor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LayoutEditor/debug -lLayoutEditor
else:unix: LIBS += -L$$PWD/../LayoutEditor/ -lLayoutEditor

INCLUDEPATH += $$PWD/../LayoutEditor $$PWD/../LayoutEditor/scripts
DEPENDPATH += $$PWD/../LayoutEditor $$PWD/../LayoutEditor/scripts

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPref/release/ -lPref
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPref/debug/ -lPref
else:unix: LIBS += -L$$PWD/../libPref/ -lPref

INCLUDEPATH += $$PWD/../libPref/
DEPENDPATH += $$PWD/../libPref

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Tables/release/ -lTables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Tables/debug/ -lTables
else:unix: LIBS += -L$$PWD/../Tables/ -lTables

INCLUDEPATH += $$PWD/../Tables
DEPENDPATH += $$PWD/../Tables

DISTFILES +=

contains(WEBAPP, 1) {

unix:!macx: LIBS += -L$$PWD/../QtWebApp/ -lQtWebAppd

INCLUDEPATH += $$PWD/../QtWebApp $$PWD/../QtWebApp/httpserver/
DEPENDPATH += $$PWD/../QtWebApp $$PWD/../QtWebApp/httpserver/
message("libPr3: link to libQtWebAppd")
}

DEFINES += QZEROCONF_STATIC


unix|win32: LIBS += -L$$PWD/../../../../QtZeroConf-master/ -lQtZeroConf

INCLUDEPATH += $$PWD/../../../../QtZeroConf-master
DEPENDPATH += $$PWD/../../../../QtZeroConf-master

unix:exists($$PWD/../../../../QtZeroConf-master/libQtZeroConf.so.1) {
message($$PWD/../../../../QtZeroConf-master/libQtZeroConf.so.1 found)
} else {
message(LibPr3: $$PWD/../../../../QtZeroConf-master/libQtZeroConf.so.1 not found)
}





#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../QtWebApp/release/ -lQtWebAppd
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../QtWebApp/debug/ -lQtWebAppd
#else:unix: LIBS += -L$$PWD/../QtWebApp/ -lQtWebAppd

#INCLUDEPATH += $$PWD/../QtWebApp $$PWD/../QtWebApp/httpserver/
#DEPENDPATH += $$PWD/../QtWebApp $$PWD/../QtWebApp/httpserver/

unix|win32: LIBS += -L$$PWD/../QtWebApp/ -lQtWebAppd

INCLUDEPATH += $$PWD/../QtWebApp $$PWD/../QtWebApp/httpserver/
DEPENDPATH += $$PWD/../QtWebApp $$PWD/../QtWebApp/httpserver/

exists($$PWD/../QtWebApp/libQtWebAppd.so.1) {
message(libPr3: $$PWD/../QtWebApp/libQtWebAppd.so.1 found)
} else {
message(libPr3: $$PWD/../QtWebApp/libQtWebAppd.so.1 not found)
}

