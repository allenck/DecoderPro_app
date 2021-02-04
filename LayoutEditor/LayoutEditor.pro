#-------------------------------------------------
#
# Project created by QtCreator 2013-10-09T12:33:32
#
#-------------------------------------------------

QT       += core gui xml   printsupport dbus webengine webenginewidgets multimedia #webkitwidgets webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport  printsupport  gui  #webkitwidgets webkit

TARGET = LayoutEditor
TEMPLATE = lib

DEFINES += LIBLAYOUTEDITOR_LIBRARY
MOC_DIR = moc_obj
OBJECTS_DIR += moc_obj

PROJ_DIR=$$(PROJ_DIR) # get project directory from env
isEmpty( PROJ_DIR ) {
  win32:PROJ_DIR=C:/Projects
  unix:PROJ_DIR=/home/allen/Projects
}


PYTHONQT_PREFIX=$$(PYTHONQT_PREFIX)
isEmpty( PYTHONQT_PREFIX ) {
  win32:PYTHONQT_PREFIX=C:/Program Files (x86)/local/lib
  unix:PYTHONQT_PREFIX=$${PROJ_DIR}/PythonQt/pythonqt-code
}

include($$PYTHONQT_PREFIX/build/python.prf)

win32:exists($$PYTHONQT_PREFIX/lib/PythonQt_d.dll){
ENABLE_SCRIPTING = "Y"
}
unix:exists($$PYTHONQT_PREFIX/lib/libPythonQt-Qt5-Python$${PYTHON_VERSION}_d.so) {
ENABLE_SCRIPTING = "Y"
}
equals(ENABLE_SCRIPTING, "Y") {
 DEFINES += SCRIPTING_ENABLED
 message("LayoutEditor: Scripting is enabled")
 include($$PWD/generated_cpp/Jmri/Jmri.pri)
 SOURCES +=     jythonsiglet.cpp \
    jythonautomaton.cpp \
    jythonautomatonaction.cpp \
    jythonsigletaction.cpp \
    runjythonscript.cpp \
    inputwindowaction.cpp \
    inputwindow.cpp \
    jythonwindow.cpp \
    pythonwrappers.cpp  \
    scripts/jmriscriptenginemanager.cpp \
    scripts/scriptenginemanager.cpp \
    scripts/simplebindings.cpp \
    scripts/scriptengine.cpp \
    scripts/pythoninterpreter.cpp \
    scripts/scriptoutput.cpp \
    scripts/scriptcontext.cpp

 HEADERS +=     jythonsiglet.h \
    jythonautomaton.h \
    jythonautomatonaction.h \
    jythonsigletaction.h \
    runjythonscript.h \
    inputwindowaction.h \
    inputwindow.h \
    jythonwindow.h \
    pythonwrappers.h \
    scripts/jmriscriptenginemanager.h \
    scripts/scriptenginemanager.h \
    scripts/scriptenginefactory.h \
    scripts/simplebindings.h \
    scripts/bindings.h \
    scripts/scriptengine.h \
    scripts/pythoninterpreter.h \
    scripts/scriptoutput.h \
    scripts/scriptcontext.h

    #include(../python.prf)

    win32:CONFIG(debug, debug|release): LIBS += -L$$PYTHONQT_PREFIX/lib -lPythonQt
    else:unix: LIBS += -L/$$PYTHONQT_PREFIX/lib/ -lPythonQt-Qt5-Python$${PYTHON_VERSION}_d

    INCLUDEPATH += $$PYTHONQT_PREFIX/src $$PYTHONQT_PREFIX/extensions/PythonQt_QtAll
    DEPENDPATH +=  $$PYTHONQT_PREFIX/src $$PYTHONQT_PREFIX/extensions/PythonQt_QtAll


message("Qt path=" + $$(QTDIR))


} else {
 message("LayoutEditor: Scripting is disabled")
}


SOURCES += \
    jmrijframe.cpp \
    layouteditorviewcontext.cpp \
    layoutturnout.cpp \
    levelxing.cpp \
    layoutblock.cpp \
    layoutconnectivity.cpp \
    tracknode.cpp \
    tracksegment.cpp \
    positionablepoint.cpp \
    layouteditorauxtools.cpp \
    layouteditortools.cpp \
    layoutblockmanager.cpp \
    positionablelabel.cpp \
    positionableicon.cpp \
    sensoricon.cpp \
    multiiconeditor.cpp \
    createeditblock.cpp \
    positionablepopuputil.cpp \
    positionablepropertiesutil.cpp \
    coordinateedit.cpp \
    sensortextedit.cpp \
    sensorpopuputil.cpp \
    iconadder.cpp \
    inputdialog.cpp \
    locoicon.cpp \
    inputangledlg.cpp \
    settrackwidthdlg.cpp \
    reportericon.cpp \
    layoutblockconnectivitytools.cpp \
    editlevelxingdlg.cpp \
    layoutslip.cpp \
    memoryiconcoordinateedit.cpp \
    turnoutoperationmanagerxml.cpp \
    turnoutoperationxml.cpp \
    commonturnoutoperationxml.cpp \
    commonturnoutoperation.cpp \
    abstractlightmanagerconfigxml.cpp \
    abstractnamedbeanmanagerconfigxml.cpp \
    abstractxmladapter.cpp \
    configxmlmanager.cpp \
    errorhandler.cpp \
    errormemo.cpp \
    locoiconxml.cpp \
    positionablelabelxml.cpp \
    editor.cpp \
    paneleditor.cpp \
    paneleditorxml.cpp \
    panelmenu.cpp \
    sensoriconxml.cpp \
    lighticonxml.cpp \
    lighticon.cpp \
    positionablejcomponent.cpp \
    analogclock2display.cpp \
    analogclock2displayxml.cpp \
    simpletimebasexml.cpp \
    addpaneleditordialog.cpp \
    turnouticon.cpp \
    turnouticonxml.cpp \
    reportericonxml.cpp \
    lcdclockframe.cpp \
    nixieclockframe.cpp \
    signalheadicon.cpp \
    signalmasticon.cpp \
    connectivityutil.cpp \
    catalogpane.cpp \
    automatsummary.cpp \
    abstractautomaton.cpp \
    siglet.cpp \
    blockbosslogic.cpp \
    signalmasticonxml.cpp \
    blockbossframe.cpp \
    signallingguitools.cpp \
    blockbosslogicxml.cpp \
    savemenu.cpp \
    layoutblockmanagerxml.cpp \
    lnturnoutmanagerxml.cpp \
    abstractturnoutmanagerconfigxml.cpp \
    internalturnoutmanagerxml.cpp \
    lnsensormanagerxml.cpp \
    internalsensormanagerxml.cpp \
    abstractsensormanagerconfigxml.cpp \
    sensorturnoutoperationxml.cpp \
    storexmlconfigaction.cpp \
    storexmluseraction.cpp \
    loadstorebaseaction.cpp \
    windowmenu.cpp \
    slipturnouticon.cpp \
    slipturnouticonxml.cpp \
    defaultlogixmanagerxml.cpp \
    sensorgroupframe.cpp \
    defaultconditionalmanagerxml.cpp \
    maintenance.cpp \
    picklistmodel.cpp \
    pickpanel.cpp \
    treeset.cpp \
    addnewdevicepanel.cpp \
    beantabledatamodel.cpp \
    blockmanagerxml.cpp \
    abstractmemorymanagerconfigxml.cpp \
    doubleturnoutsignalheadxml.cpp \
    virtualsignalheadxml.cpp \
    abstractsignalheadmanagerxml.cpp \
    singleturnoutsignalheadxml.cpp \
    signalheadsignalmastxml.cpp \
    defaultsignalmastmanagerxml.cpp \
    defaultsignalmastlogicmanagerxml.cpp \
    turnoutsignalmastxml.cpp \
    virtualsignalmastxml.cpp \
    signalheadiconxml.cpp \
    sectionmanager.cpp \
    section.cpp \
    transit.cpp \
    transitmanager.cpp \
    transitsection.cpp \
    rawturnoutoperationxml.cpp \
    rawturnoutoperator.cpp \
    warrantframe.cpp \
    oblockmanagerxml.cpp \
    warrantmanagerxml.cpp \
    entryexitpairsxml.cpp \
    multisensoricon.cpp \
    multisensoriconxml.cpp \
    multisensoriconframe.cpp \
    multisensoriconwidget.cpp \
    sensorentrywidget.cpp \
    droppushbutton.cpp \
    sensorlineedit.cpp \
    turnoutlineedit.cpp \
    decoratorpanel.cpp \
    controlpaneleditor.cpp \
    itempalette.cpp \
    portalicon.cpp \
    itempanel.cpp \
    familyitempanel.cpp \
    defaultcatalogtreemanager.cpp \
    signalheaditempanel.cpp \
    tableitempanel.cpp \
    imageindexeditor.cpp \
    catalogpanel.cpp \
    catalogtreeindex.cpp \
    abstractcatalogtree.cpp \
    clockitempanel.cpp \
    iconitempanel.cpp \
    catalogtreefs.cpp \
    catalogtreemanager.cpp \
    signalmastitempanel.cpp \
    memoryitempanel.cpp \
    memoryinputicon.cpp \
    positionablejpanel.cpp \
    memorycomboicon.cpp \
    memoryspinnericon.cpp \
    dragjcomponent.cpp \
    reporteritempanel.cpp \
    textitempanel.cpp \
    multisensoritempanel.cpp \
    indicatoritempanel.cpp \
    detectionpanel.cpp \
    indicatortrackicon.cpp \
    indicatortrackpaths.cpp \
    itempalettewidget.cpp \
    memoryinputiconxml.cpp \
    memorycomboiconxml.cpp \
    memoryspinnericonxml.cpp \
    controlpaneleditorxml.cpp \
    portaliconxml.cpp \
    circuitbuilder.cpp \
    editcircuitframe.cpp \
    editportalframe.cpp \
    indicatorturnouticon.cpp \
    indicatortoitempanel.cpp \
    indicatorturnouticonxml.cpp \
    indicatortrackiconxml.cpp \
    backgrounditempanel.cpp \
    defaultcatalogtreemanagerxml.cpp \
    directorysearcher.cpp \
    previewdialog.cpp \
    mygraphicsproxywidget.cpp \
    positionable.cpp \
    shapedrawer.cpp \
    drawframe.cpp \
    drawrectangle.cpp \
    positionableshape.cpp \
    positionablerectangle.cpp \
    drawcircle.cpp \
    drawellipse.cpp \
    drawroundrect.cpp \
    positionablecircle.cpp \
    positionableellipse.cpp \
    positionableroundrect.cpp \
    positionableshapexml.cpp \
    positionablecirclexml.cpp \
    positionablerectanglexml.cpp \
    positionableellipsexml.cpp \
    positionableroundrectxml.cpp \
    nofeedbackturnoutoperationxml.cpp \
    turnoutoperationframe.cpp \
    turnoutoperationconfig.cpp \
    nofeedbackturnoutoperationconfig.cpp \
    commonturnoutoperationconfig.cpp \
    rawturnoutoperationconfig.cpp \
    sensorturnoutoperationconfig.cpp \
    simpleclockframe.cpp \
    analogclockframe.cpp \
    icondialog.cpp \
    itemdialog.cpp \
    slipiconadder.cpp \
    transferhandler.cpp \
    multisensoriconadder.cpp \
    warranttableaction.cpp \
    editcircuitpaths.cpp \
    powerpane.cpp \
    powermanagermenu.cpp \
    powerpanelframe.cpp \
    simpleturnoutctrlframe.cpp \
    slipturnouttextedit.cpp \
    quadoutputsignalheadxml.cpp \
    tripleturnoutsignalheadxml.cpp \
    defaultsignalgroupmanagerxml.cpp \
    sensortabledatamodel.cpp \
    beantableframe.cpp \
    sectionmanagerxml.cpp \
    lnreportermanagerxml.cpp \
    rfidreportermanagerxml.cpp \
    abstractreportermanagerconfigxml.cpp \
    internalreportermanagerxml.cpp \
    se8csignalheadxml.cpp \
    locomonpane.cpp \
    abstractmonpane.cpp \
    abstractconnectionconfigxml.cpp \
    abstractserialconnectionconfigxml.cpp \
    dialogerrorhandler.cpp \
    filehistory.cpp \
    filehistoryxml.cpp \
    abstractaudiomanagerconfigxml.cpp \
    defaultaudiomanagerxml.cpp \
    paneleditoraction.cpp \
    controlpaneleditoraction.cpp \
    layouteditoraction.cpp \
    loadxmluseraction.cpp \
    loadxmlconfigaction.cpp \
    internallightmanagerxml.cpp \
    defaultmemorymanagerxml.cpp \
    rosterconfigpanexml.cpp \
    layouteditorxml.cpp \
    defaultroutemanagerxml.cpp \
    consisttoolframe.cpp \
    tracksegmentxml.cpp \
    positionablepointxml.cpp \
    layoutturnoutxml.cpp \
    levelxingxml.cpp \
    layoutturntable.cpp \
    lnlightmanagerxml.cpp \
    layoutblockroutetableaction.cpp \
    layoutblockroutetable.cpp \
    layoutblockneighbourtablemodel.cpp \
    layoutblockthroughpathstablemodel.cpp \
    layoutblockroutetablemodel.cpp \
    automattableaction.cpp \
    automattableframe.cpp \
    automattabledatamodel.cpp \
    layoutslipxml.cpp \
    storexmlallaction.cpp \
    filehistoryaction.cpp \
    addentryexitpairaction.cpp \
    addentryexitpairframe.cpp \
    addentryexitpairpanel.cpp \
    helpbroker.cpp \
    trainicon.cpp \
    dccsignalmastxml.cpp \
    opsessionlog.cpp \
    warranttableframe.cpp \
    warranttablemodel.cpp \
    editportaldirection.cpp \
    portalmanager.cpp \
    newpanelaction.cpp \
    blockbossaction.cpp \
    sensorgroupaction.cpp \
    sensortablemodel.cpp \
    beantablemodel.cpp \
    sensorgroup.cpp \
    simplelightctrlframe.cpp \
    simplelightctrlaction.cpp \
    speedometerframe.cpp \
    speedometeraction.cpp \
    sendpacketaction.cpp \
    sendpacketframe.cpp \
    vsdconfigdialog.cpp \
    vsdcontrol.cpp \
    busydialog.cpp \
    vsdoptionsdialog.cpp \
    dragjlabel.cpp \
    dropjlabel.cpp \
    jmriabstractaction.cpp \
    jmrijframeinterface.cpp \
    layouteditorfinditems.cpp \
    layoutturntablexml.cpp \
    layouteditor.cpp \
    xmlfilelocationaction.cpp \
    reportcontextaction.cpp \
    twopanetbwindow.cpp \
    drawpolygon.cpp \
    positionablepolygon.cpp \
    polygon.cpp \
    affinetransform.cpp \
    positionablepolygonxml.cpp \
    generalpath.cpp \
    path2d.cpp \
    transitmanagerxml.cpp \
    jframe.cpp \
    hardcopywriter.cpp \
    jframeinterface.cpp \
    treeframe.cpp \
    treeaction.cpp \
    jmrijframeaction.cpp \
    treepanel.cpp \
    usbnode.cpp \
    controller.cpp \
    usbtreemodel0.cpp \
    abstractcontroller.cpp \
    linuxabstractcontroller.cpp \
    keyboard.cpp \
    linuxeventdevice.cpp \
    linuxinputid.cpp \
    usb_bus.cpp \
    usb_device.cpp \
    usbtreemodel.cpp \
    usbview.cpp \
    usbviewaction.cpp \
    clientif.cpp \
    helputil.cpp \
    rpspositionicon.cpp \
    scriptfilechooser.cpp \
    layouttrack.cpp \
    rpsreporter.cpp \
    region.cpp \
    model.cpp \
    rpsreportermanager.cpp \
    distributor.cpp \
    reading.cpp \
    measurement.cpp \
    engine.cpp \
    transmitter.cpp \
    receiver.cpp \
    rpsmenu.cpp \
    blockcontentsiconxml.cpp \
    abstractmonframe.cpp \
    multisensoricondialog.cpp \
    displayframe.cpp \
    portalitempanel.cpp \
    jmripanel.cpp \
    switchboardeditoraction.cpp \
    switchboardeditor.cpp \
    switchboardeditorxml.cpp \
    beanswitch.cpp \
    layouttrackdrawingoptionsxml.cpp \
    layouttrackdrawingoptions.cpp \
    defaultusermessagepreferencesxml.cpp \
    layouttrackexpectedstate.cpp \
    rpsitempanel.cpp \
    signalheadicondialog.cpp \
    test/testbase.cpp \
    generated_cpp/test/test_init.cpp \
    generated_cpp/test/test0.cpp \
    colordialog.cpp \
    linkinglabel.cpp \
    layouteditorchecks.cpp \
    layouttrackdrawingoptionsdialog.cpp \
    rpssystemconnectionmemo.cpp \
    rpscomponentfactory.cpp \
    rpssensormanager.cpp \
    rpssensor.cpp \
    namedicon.cpp \
    lememoryicon.cpp \
    memoryicon.cpp \
    lememoryiconxml.cpp \
    memoryiconxml.cpp \
    leblockcontentsicon.cpp \
    blockcontentsicon.cpp \
    leblockcontentsiconxml.cpp \
    fontpanel.cpp \
    consistdatamodel.cpp \
    enterreporterdialog.cpp \
    layouteditortoolbarpanel.cpp \
    layouteditorhorizontaltoolbarpanel.cpp \
    layouteditorverticaltoolbarpanel.cpp \
    layouteditorfloatingtoolbarpanel.cpp \
    layoutshape.cpp \
    layoutshapexml.cpp \
    scaletrackdiagramdialog.cpp \
    editormanager.cpp \
    pragotronclockframe.cpp \
    pragotronclockaction.cpp \
    editframe.cpp \
    portallist.cpp \
    editsignalframe.cpp \
    openpicklistbutton.cpp \
    lengthpanel.cpp \
    convertdialog.cpp \
    indicatortoicondialog.cpp \
    previewpanel.cpp \
    layoutrhturnout.cpp \
    layoutlhturnout.cpp \
    layoutwye.cpp \
    layoutrhxover.cpp \
    layoutlhxover.cpp \
    layoutdoubleslip.cpp \
    layoutsingleslip.cpp \
    layoutdoublexover.cpp \
    layoutdoubleslipeditor.cpp \
    layoutslipeditor.cpp \
    layoutturnouteditor.cpp \
    layouttrackeditor.cpp \
    layoutrhturnouteditor.cpp \
    layoutlhturnouteditor.cpp \
    layoutwyeeditor.cpp \
    layoutsingleslipeditor.cpp \
    layouttrackview.cpp \
    layoutrhturnoutview.cpp \
    layoutxover.cpp \
    layoutxovereditor.cpp \
    layoutlhxovereditor.cpp \
    layoutturnoutview.cpp \
    layoutrhxovereditor.cpp \
    layoutdoublexovereditor.cpp \
    tracksegmenteditor.cpp \
    positionablepointeditor.cpp \
    levelxingeditor.cpp \
    layoutturntableeditor.cpp \
    layoutlhturnoutview.cpp \
    layoutwyeview.cpp \
    layoutrhxoverview.cpp \
    layoutxoverview.cpp \
    layoutlhxoverview.cpp \
    layoutdoublexoverview.cpp \
    layoutslipview.cpp \
    layoutsingleslipview.cpp \
    layoutdoubleslipview.cpp \
    tracksegmentview.cpp \
    levelxingview.cpp \
    positionablepointview.cpp \
    layoutturntableview.cpp \
    layouteditorcomponent.cpp \
    entergridsizesdialog.cpp \
    moveselectiondialog.cpp \
    ../JavaQt/jradiobuttonmenuitem.cpp \
    blockbosslogicprovider.cpp \
    createxmlfiles.cpp \
    hitpointtype.cpp \
    abstractnamedbeanmanager.cpp

HEADERS += liblayouteditor_global.h \
    jmrijframeinterface.h \
    jmrijframe.h \
    layouteditorviewcontext.h \
    layoutturnout.h \
    levelxing.h \
    layoutblock.h \
    layoutconnectivity.h \
    tracksegment.h \
    tracknode.h \
    positionablepoint.h \
    positionable.h \
    layouteditorauxtools.h \
    layouteditortools.h \
    layoutblockmanager.h \
    positionablelabel.h \
    positionableicon.h \
    sensoricon.h \
    multiiconeditor.h \
    createeditblock.h \
    positionablepopuputil.h \
    positionablepropertiesutil.h \
    coordinateedit.h \
    sensortextedit.h \
    sensorpopuputil.h \
    iconadder.h \
    inputdialog.h \
    locoicon.h \
    inputangledlg.h \
    settrackwidthdlg.h \
    reportericon.h \
    layoutblockconnectivitytools.h \
    editlevelxingdlg.h \
    layoutslip.h \
    memoryiconcoordinateedit.h \
    turnoutoperationmanagerxml.h \
    turnoutoperationxml.h \
    commonturnoutoperationxml.h \
    commonturnoutoperation.h \
    abstractlightmanagerconfigxml.h \
    abstractnamedbeanmanagerconfigxml.h \
    abstractxmladapter.h \
    configxmlmanager.h \
    errorhandler.h \
    errormemo.h \
    xmladapter.h \
    locoiconxml.h \
    positionablelabelxml.h \
    editor.h \
    paneleditor.h \
    paneleditorxml.h \
    panelmenu.h \
    sensoriconxml.h \
    lighticonxml.h \
    lighticon.h \
    positionablejcomponent.h \
    analogclock2display.h \
    analogclock2displayxml.h \
    simpletimebasexml.h \
    addpaneleditordialog.h \
    turnouticon.h \
    turnouticonxml.h \
    reportericonxml.h \
    lcdclockframe.h \
    nixieclockframe.h \
    signalheadicon.h \
    signalmasticon.h \
    connectivityutil.h \
    catalogpane.h \
    automatsummary.h \
    abstractautomaton.h \
    siglet.h \
    blockbosslogic.h \
    signalmasticonxml.h \
    blockbossframe.h \
    signallingguitools.h \
    blockbosslogicxml.h \
    savemenu.h \
    layoutblockmanagerxml.h \
    lnturnoutmanagerxml.h \
    abstractturnoutmanagerconfigxml.h \
    internalturnoutmanagerxml.h \
    lnsensormanagerxml.h \
    internalsensormanagerxml.h \
    abstractsensormanagerconfigxml.h \
    sensorturnoutoperationxml.h \
    storexmlconfigaction.h \
    storexmluseraction.h \
    loadstorebaseaction.h \
    windowmenu.h \
    slipturnouticon.h \
    slipturnouticonxml.h \
    defaultlogixmanagerxml.h \
    sensorgroupframe.h \
    defaultconditionalmanagerxml.h \
    maintenance.h \
    picklistmodel.h \
    pickpanel.h \
    treeset.h \
    navigablemap.h \
    addnewdevicepanel.h \
    beantabledatamodel.h \
    blockmanagerxml.h \
    abstractmemorymanagerconfigxml.h \
    section.h \
    sectionmanager.h \
    transit.h \
    transitmanager.h \
    transitsection.h \
    doubleturnoutsignalheadxml.h \
    virtualsignalheadxml.h \
    abstractsignalheadmanagerxml.h \
    singleturnoutsignalheadxml.h \
    signalheadsignalmastxml.h \
    defaultsignalmastmanagerxml.h \
    defaultsignalmastlogicmanagerxml.h \
    turnoutsignalmastxml.h \
    virtualsignalmastxml.h \
    signalheadiconxml.h \
    rawturnoutoperationxml.h \
    rawturnoutoperator.h \
    warrantframe.h \
    oblockmanagerxml.h \
    warrantmanagerxml.h \
    entryexitpairsxml.h \
    multisensoricon.h \
    multisensoriconxml.h \
    multisensoriconframe.h \
    multisensoriconwidget.h \
    sensorentrywidget.h \
    droppushbutton.h \
    sensorlineedit.h \
    turnoutlineedit.h \
    decoratorpanel.h \
    controlpaneleditor.h \
    itempalette.h \
    itempanel.h \
    familyitempanel.h \
    defaultcatalogtreemanager.h \
    signalheaditempanel.h \
    tableitempanel.h \
    imageindexeditor.h \
    catalogpanel.h \
    catalogtreeindex.h \
    abstractcatalogtree.h \
    clockitempanel.h \
    iconitempanel.h \
    catalogtreefs.h \
    catalogtreemanager.h \
    signalmastitempanel.h \
    memoryitempanel.h \
    memoryinputicon.h \
    positionablejpanel.h \
    memorycomboicon.h \
    memoryspinnericon.h \
    dragjcomponent.h \
    reporteritempanel.h \
    textitempanel.h \
    multisensoritempanel.h \
    indicatoritempanel.h \
    detectionpanel.h \
    indicatortrackicon.h \
    indicatortrackpaths.h \
    itempalettewidget.h \
    memoryinputiconxml.h \
    memorycomboiconxml.h \
    memoryspinnericonxml.h \
    controlpaneleditorxml.h \
    portalicon.h \
    portaliconxml.h \
    circuitbuilder.h \
    indicatortrack.h \
    editcircuitframe.h \
    editportalframe.h \
    indicatorturnouticon.h \
    indicatortoitempanel.h \
    indicatorturnouticonxml.h \
    indicatortrackiconxml.h \
    backgrounditempanel.h \
    defaultcatalogtreemanagerxml.h \
    directorysearcher.h \
    previewdialog.h \
    mygraphicsproxywidget.h \
    shapedrawer.h \
    drawframe.h \
    drawrectangle.h \
    positionableshape.h \
    positionablerectangle.h \
    drawcircle.h \
    drawellipse.h \
    drawroundrect.h \
    positionablecircle.h \
    positionableellipse.h \
    positionableroundrect.h \
    positionableshapexml.h \
    positionablecirclexml.h \
    positionablerectanglexml.h \
    positionableellipsexml.h \
    positionableroundrectxml.h \
    nofeedbackturnoutoperationxml.h \
    turnoutoperationframe.h \
    turnoutoperationconfig.h \
    nofeedbackturnoutoperationconfig.h \
    commonturnoutoperationconfig.h \
    rawturnoutoperationconfig.h \
    sensorturnoutoperationconfig.h \
    simpleclockframe.h \
    analogclockframe.h \
    icondialog.h \
    itemdialog.h \
    slipiconadder.h \
    transferhandler.h \
    multisensoriconadder.h \
    warranttableaction.h \
    editcircuitpaths.h \
    powerpane.h \
    powermanagermenu.h \
    powerpanelframe.h \
    simpleturnoutctrlframe.h \
    slipturnouttextedit.h \
    quadoutputsignalheadxml.h \
    tripleturnoutsignalheadxml.h \
    defaultsignalgroupmanagerxml.h \
    sensortabledatamodel.h \
    beantableframe.h \
    sectionmanagerxml.h \
    lnreportermanagerxml.h \
    rfidreportermanagerxml.h \
    abstractreportermanagerconfigxml.h \
    internalreportermanagerxml.h \
    se8csignalheadxml.h \
    locomonpane.h \
    abstractmonpane.h \
    abstractconnectionconfigxml.h \
    abstractserialconnectionconfigxml.h \
    dialogerrorhandler.h \
    filehistory.h \
    filehistoryxml.h \
    abstractaudiomanagerconfigxml.h \
    defaultaudiomanagerxml.h \
    paneleditoraction.h \
    controlpaneleditoraction.h \
    layouteditoraction.h \
    loadxmluseraction.h \
    loadxmlconfigaction.h \
    internallightmanagerxml.h \
    defaultmemorymanagerxml.h \
    rosterconfigpanexml.h \
    layouteditorxml.h \
    defaultroutemanagerxml.h \
    consisttoolframe.h \
    tracksegmentxml.h \
    positionablepointxml.h \
    layoutturnoutxml.h \
    levelxingxml.h \
    layoutturntable.h \
    lnlightmanagerxml.h \
    layoutblockroutetableaction.h \
    layoutblockroutetable.h \
    layoutblockneighbourtablemodel.h \
    layoutblockthroughpathstablemodel.h \
    layoutblockroutetablemodel.h \
    automattableaction.h \
    automattableframe.h \
    automattabledatamodel.h \
    layoutslipxml.h \
    storexmlallaction.h \
    filehistoryaction.h \
    addentryexitpairaction.h \
    addentryexitpairframe.h \
    addentryexitpairpanel.h \
    helpbroker.h \
    trainicon.h \
    dccsignalmastxml.h \
    opsessionlog.h \
    warranttableframe.h \
    warranttablemodel.h \
    editportaldirection.h \
    portalmanager.h \
    newpanelaction.h \
    blockbossaction.h \
    sensorgroupaction.h \
    sensortablemodel.h \
    beantablemodel.h \
    sensorgroup.h \
    simplelightctrlframe.h \
    simplelightctrlaction.h \
    speedometerframe.h \
    speedometeraction.h \
    sendpacketaction.h \
    sendpacketframe.h \
    vsdconfigdialog.h \
    vsdcontrol.h \
    busydialog.h \
    vsdoptionsdialog.h \
    dragjlabel.h \
    dropjlabel.h \
    jmriabstractaction.h \
    layouteditorfinditems.h \
    layoutturntablexml.h \
    layouteditor.h \
    xmlfilelocationaction.h \
    reportcontextaction.h \
    twopanetbwindow.h \
    drawpolygon.h \
    positionablepolygon.h \
    pathiterator.h \
    polygon.h \
    shape.h \
    affinetransform.h \
    positionablepolygonxml.h \
    generalpath.h \
    path2d.h \
    transitmanagerxml.h \
    jframe.h \
    windowinterface.h \
    hardcopywriter.h \
    jframeinterface.h \
    treeframe.h \
    treeaction.h \
    jmrijframeaction.h \
    treepanel.h \
    usbnode.h \
    controller.h \
    usbviewaction.h \
    usbview.h \
    usbtreemodel0.h \
    abstractcontroller.h \
    linuxabstractcontroller.h \
    keyboard.h \
    linuxdevice.h \
    linuxeventdevice.h \
    linuxinputid.h \
    rumbler.h \
    usbtreemodel.h \
    usb_bus.h \
    usb_device.h \
    clientif.h \
    helputil.h \
    rpspositionicon.h \
    scriptfilechooser.h \
    layouttrack.h \
    rpsreporter.h \
    region.h \
    model.h \
    rpsreportermanager.h \
    distributor.h \
    reading.h \
    measurement.h \
    engine.h \
    transmitter.h \
    receiver.h \
    calculator.h \
    rpsmenu.h \
    blockcontentsiconxml.h \
    abstractmonframe.h \
    multisensoricondialog.h \
    displayframe.h \
    portalitempanel.h \
    jmripanel.h \
    switchboardeditoraction.h \
    switchboardeditor.h \
    switchboardeditorxml.h \
    beanswitch.h \
    layouttrackdrawingoptionsxml.h \
    layouttrackdrawingoptions.h \
    defaultusermessagepreferencesxml.h \
    layouttrackexpectedstate.h \
    rpsitempanel.h \
    signalheadicondialog.h \
    test/testbase.h \
    generated_cpp/test/test0.h \
    calculator.h \
    colordialog.h \
    linkinglabel.h \
    layouteditorchecks.h \
    layouttrackdrawingoptionsdialog.h \
    rpssystemconnectionmemo.h \
    rpscomponentfactory.h \
    rpssensormanager.h \
    rpssensor.h \
    measurementlistener.h \
    namedicon.h \
    lememoryicon.h \
    memoryicon.h \
    lememoryiconxml.h \
    memoryiconxml.h \
    leblockcontentsicon.h \
    blockcontentsicon.h \
    leblockcontentsiconxml.h \
    fontpanel.h \
    consistdatamodel.h \
    enterreporterdialog.h \
    layouteditortoolbarpanel.h \
    layouteditorhorizontaltoolbarpanel.h \
    layouteditorverticaltoolbarpanel.h \
    layouteditorfloatingtoolbarpanel.h \
    layoutshape.h \
    layoutshapexml.h \
    scaletrackdiagramdialog.h \
    editormanager.h \
    pragotronclockframe.h \
    pragotronclockaction.h \
    editframe.h \
    portallist.h \
    editsignalframe.h \
    openpicklistbutton.h \
    lengthpanel.h \
    convertdialog.h \
    indicatortoicondialog.h \
    previewpanel.h \
    layoutrhturnout.h \
    layoutlhturnout.h \
    layoutwye.h \
    layoutrhxover.h \
    layoutlhxover.h \
    layoutdoubleslip.h \
    layoutsingleslip.h \
    layoutdoublexover.h \
    layoutdoubleslipeditor.h \
    layoutslipeditor.h \
    layoutturnouteditor.h \
    layouttrackeditor.h \
    layoutrhturnouteditor.h \
    layoutlhturnouteditor.h \
    layoutwyeeditor.h \
    layoutsingleslipeditor.h \
    layouttrackview.h \
    layoutrhturnoutview.h \
    layoutxover.h \
    layoutxovereditor.h \
    layoutlhxovereditor.h \
    layoutturnoutview.h \
    layoutrhxovereditor.h \
    layoutdoublexovereditor.h \
    tracksegmenteditor.h \
    positionablepointeditor.h \
    levelxingeditor.h \
    layoutturntableeditor.h \
    layoutlhturnoutview.h \
    layoutwyeview.h \
    layoutrhxoverview.h \
    layoutxoverview.h \
    layoutlhxoverview.h \
    layoutdoublexoverview.h \
    layoutslipview.h \
    layoutsingleslipview.h \
    layoutdoubleslipview.h \
    tracksegmentview.h \
    levelxingview.h \
    positionablepointview.h \
    layoutturntableview.h \
    layouteditorcomponent.h \
    entergridsizesdialog.h \
    moveselectiondialog.h \
    ../JavaQt/jradiobuttonmenuitem.h \
    blockbosslogicprovider.h \
    createxmlfiles.h \
    hitpointtype.h \
    abstractnamedbeanmanager.h

FORMS    += \
    createeditblock.ui \
    setxydlg.ui \
    sensortextedit.ui \
    iconadder.ui \
    inputdialog.ui \
    editturnout.ui \
    inputangledlg.ui \
    positionablepropertiesutil.ui \
    settrackwidthdlg.ui \
    editlevelxingdlg.ui \
    paneleditor.ui \
    addpaneleditordialog.ui \
    multisensoriconwidget.ui \
    sensorentrywidget.ui \
    itempalettewidget.ui \
    form.ui \
    layouteditor.ui

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

RESOURCES += \
    LayoutEditor.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3/release/ -lPr3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3/debug/ -lPr3
else:unix:!macx: LIBS += -L$$PWD/../libPr3/ -lPr3

INCLUDEPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/Signal \
 $$PWD/../Tables $$PWD/../libPr3/Throttle $$PWD/../libPr3/LocoIO $$PWD/../libPr3/loconet $$PWD/../libPr3/rfid
DEPENDPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/Signal \
 $$PWD/../Tables $$PWD/../libPr3/Throttle $$PWD/../libPr3/LocoIO $$PWD/../libPr3/loconet $$PWD/../libPr3/rfid


TRANSLATIONS += \
    languages/libLayoutEditor_de.ts \
    languages/libLayoutEditor_en.ts

win32_msvc: {
 QMAKE_CXXFLAGS += /wd4290
 QMAKE_CFLAGS_DEBUG += /wd4290
}

OTHER_FILES +=


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPref/release/ -lPref
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPref/debug/ -lPref
else:unix: LIBS += -L$$PWD/../libPref/ -lPref

INCLUDEPATH += $$PWD/../libPref
DEPENDPATH += $$PWD/../libPref


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/release/ -lappslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/debug/ -lappslib
else:unix: LIBS += -L$$PWD/../appslib/ -lappslib

INCLUDEPATH += $$PWD/../appslib
DEPENDPATH += $$PWD/../appslib

DISTFILES += \
    generated_cpp/test/test.pri

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/release/ -lJavaQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/debug/ -lJavaQt
else:unix: LIBS += -L$$PWD/../JavaQt/ -lJavaQt

INCLUDEPATH += $$PWD/../JavaQt
DEPENDPATH += $$PWD/../JavaQt

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../Python27/libs/ -lpython27
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../Python27/libs/ -lpython27

INCLUDEPATH += $$PWD/../../../../../Python27/include
DEPENDPATH += $$PWD/../../../../../Python27/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Tables/release/ -lTables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Tables/debug/ -lTables
else:unix: LIBS += -L$$PWD/../Tables/ -lTables

INCLUDEPATH += $$PWD/../Tables/debug
DEPENDPATH += $$PWD/../Tables/debug



win32:CONFIG(release, debug|release): LIBS += -L$$PROJ_DIR/QtZeroConf-master/release/ -lQtZeroConf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PROJ_DIR/QtZeroConf-master/debug/ -lQtZeroConf
else:unix: LIBS += -L$$PROJ_DIR/QtZeroConf-master/ -lQtZeroConf

INCLUDEPATH += $$PROJ_DIR/QtZeroConf-master
DEPENDPATH += $$PROJ_DIR/QtZeroConf-master


unix:exists($$PROJ_DIR/QtZeroConf-master/libQtZeroConf.so.1) {
message($$PROJ_DIR/QtZeroConf-master/libQtZeroConf.so.1 found)
} else {
message(LayoutEditor: $$PROJ_DIR/QtZeroConf-master/libQtZeroConf.so.1 not found)
}



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../operations/release/ -loperations
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../operations/debug/ -loperations
else:unix: LIBS += -L$$PWD/../operations/ -loperations

INCLUDEPATH += $$PWD/../operations
DEPENDPATH += $$PWD/../operations
