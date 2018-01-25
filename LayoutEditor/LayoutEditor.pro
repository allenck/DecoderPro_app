#-------------------------------------------------
#
# Project created by QtCreator 2013-10-09T12:33:32
#
#-------------------------------------------------

QT       += core gui xml   printsupport dbus webenginewidgets #webkitwidgets webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport  printsupport  gui  #webkitwidgets webkit

TARGET = LayoutEditor
TEMPLATE = lib

DEFINES += LIBLAYOUTEDITOR_LIBRARY

unix:PREFIX = /home/allen/Projects/PythonQt-master
win32:PREFIX = "C:/Program Files (x86)/local"

win32:exists($$PREFIX/lib/PythonQt.dll){
ENABLE_SCRIPTING = "Y"
}
unix:exists($$PREFIX/lib/libPythonQt.so){
ENABLE_SCRIPTING = "Y"
}
equals(ENABLE_SCRIPTING, "Y") {
 DEFINES += SCRIPTING_ENABLED
 message("LayoutEditor: Scripting is enabled")
 include($$PWD/generated_cpp/jmri/jmri.pri)
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
    scripts/scriptcontext.h

    include(../python.prf)

    win32:CONFIG(debug, debug|release): LIBS += -L$$PREFIX/lib -lPythonQt
    else:unix: LIBS += -L/$$PREFIX/lib/ -lPythonQt_d

    INCLUDEPATH += /usr/local/include/PythonQt
    DEPENDPATH += /usr/local/include/PythonQt

#    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../Qt/5.4/gcc/plugins/designer/release/ -lpyqt5
#    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../Qt/5.4/gcc/plugins/designer/debug/ -lpyqt5
#    else:unix: LIBS += -L$$(QTDIR)/plugins/designer/ -lpyqt5
message("Qt path=" + $$(QTDIR))

    INCLUDEPATH += $$PWD/../../../../../Qt/5.4/gcc/plugins/designer
    DEPENDPATH += $$PWD/../../../../../Qt/5.4/gcc/plugins/designer

#    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../PythonQt3.0/lib/release/ -lPythonQt_QtAll_d
#    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../PythonQt3.0/lib/debug/ -lPythonQt_QtAll_d
#    else:unix: LIBS += -L$$PWD/../../../../PythonQt3.0/lib/ -lPythonQt_QtAll_d

#    INCLUDEPATH += $$PWD/../../../../PythonQt3.0/src
#    DEPENDPATH += $$PWD/../../../../PythonQt3.0/src

}
else {
 message("LayoutEditor: Scripting is disabled")
}


SOURCES += \
    jmrijframe.cpp \
    editscene.cpp \
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
    edittracksegmentdlg.cpp \
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
    addreporterdlg.cpp \
    reportericon.cpp \
    layoutblockconnectivitytools.cpp \
    loadxml.cpp \
    editlevelxingdlg.cpp \
    layoutslip.cpp \
    savexml.cpp \
    memoryiconcoordinateedit.cpp \
    turnoutoperationmanagerxml.cpp \
    turnoutoperationxml.cpp \
    commonturnoutoperationxml.cpp \
    commonturnoutoperation.cpp \
    displaymemoryicon.cpp \
    memoryicon.cpp \
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
    memoryiconxml.cpp \
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
    abstractspinnermodel.cpp \
    spinnernumbermodel.cpp \
    controlpaneleditor.cpp \
    itempalette.cpp \
    itempanel.cpp \
    familyitempanel.cpp \
    #defaultmutabletreenode.cpp \
    #catalogtreenode.cpp \
    defaultcatalogtreemanager.cpp \
    signalheaditempanel.cpp \
    tableitempanel.cpp \
    imageindexeditor.cpp \
    catalogpanel.cpp \
    #defaulttreemodel.cpp \
    catalogtreeindex.cpp \
    #treepath.cpp \
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
    portalicon.cpp \
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
    rfidsensormanagerxml.cpp \
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
    vsdconfigpanel.cpp \
    vsdconfigdialog.cpp \
    vsdcontrol.cpp \
    busydialog.cpp \
    vsdoptionsdialog.cpp \
    jlabel.cpp \
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
    layouttrack.cpp

HEADERS += liblayouteditor_global.h \
    jmrijframeinterface.h \
    jmrijframe.h \
    editscene.h \
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
    edittracksegmentdlg.h \
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
    addreporterdlg.h \
    reportericon.h \
    layoutblockconnectivitytools.h \
    loadxml.h \
    editlevelxingdlg.h \
    layoutslip.h \
    savexml.h \
    addreporterdlg.h \
    memoryiconcoordinateedit.h \
    turnoutoperationmanagerxml.h \
    turnoutoperationxml.h \
    commonturnoutoperationxml.h \
    commonturnoutoperation.h \
    displaymemoryicon.h \
    memoryicon.h \
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
    memoryiconxml.h \
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
    spinnermodel.h \
    abstractspinnermodel.h \
    spinnernumbermodel.h \
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
    rfidsensormanagerxml.h \
    simpleclockframe.h \
    analogclockframe.h \
    icondialog.h \
    itemdialog.h \
    #componentpeer.h \
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
    vsdconfigpanel.h \
    vsdconfigdialog.h \
    vsdcontrol.h \
    busydialog.h \
    vsdoptionsdialog.h \
    jlabel.h \
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
    layouttrack.h


FORMS    += \
    edittracksegmentdlg.ui \
    createeditblock.ui \
    setxydlg.ui \
    sensortextedit.ui \
    iconadder.ui \
    inputdialog.ui \
    editturnout.ui \
    inputangledlg.ui \
    positionablepropertiesutil.ui \
    settrackwidthdlg.ui \
    addreporterdlg.ui \
    editlevelxingdlg.ui \
    paneleditor.ui \
    addpaneleditordialog.ui \
    catalogpane.ui \
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

INCLUDEPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/Signal $$PWD/../Tables
DEPENDPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/Signal $$PWD/../Tables

#DEFINES += BLOCKS_AND_SECTIONS

TRANSLATIONS += \
    languages/libLayoutEditor_de.ts \
    languages/libLayoutEditor_en.ts

win32_msvc: {
 QMAKE_CXXFLAGS += /wd4290
 QMAKE_CFLAGS_DEBUG += /wd4290
}

OTHER_FILES += \
    libLayoutEditor.so.1.0


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPref/release/ -lPref
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPref/debug/ -lPref
else:unix: LIBS += -L$$PWD/../libPref/ -lPref

INCLUDEPATH += $$PWD/../libPref
DEPENDPATH += $$PWD/../libPref


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/release/ -lappslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/debug/ -lappslib
else:unix: LIBS += -L$$PWD/../appslib/ -lappslib

INCLUDEPATH += $$PWD/../appslib $$PWD/../appslib/operations
DEPENDPATH += $$PWD/../appslib $$PWD/../appslib/operations

DISTFILES += \
    drawroundrect.o

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

