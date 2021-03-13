#-------------------------------------------------
#
# Project created by QtCreator 2016-05-02T10:59:42
#
#-------------------------------------------------

#QT       -= gui
QT += xml printsupport network
greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets gui
}
TARGET = JavaQt
TEMPLATE = lib

DEFINES += JAVAQT_LIBRARY

MOC_DIR = moc_obj
OBJECTS_DIR = moc_obj

# Windows and Unix get the suffix "d" to indicate a debug version of the library.
# Mac OS gets the suffix "_debug".
CONFIG(debug, debug|release) {
    win32:      TARGET = $$join(TARGET,,,d)
    mac:        TARGET = $$join(TARGET,,,_debug)
    unix:!mac:  TARGET = $$join(TARGET,,,d)
    MOC_DIR = moc_objd
    OBJECTS_DIR = moc_objd
}

PROJ_DIR=$$(PROJ_DIR) # get project directory from env
isEmpty( PROJ_DIR ) {
  win32:PROJ_DIR=C:/Projects
  unix:PROJ_DIR=/home/allen/Projects
}


SOURCES += javaqt.cpp \
    jvetoablechangesupport.cpp \
    loggerfactory.cpp \
    loggerbase.cpp \
    logger.cpp \
    calendar.cpp \
    box.cpp \
    gridbaglayout.cpp \
    jtextarea.cpp \
    jseparator.cpp \
    abstractaction.cpp \
    gridbagconstraints.cpp \
    insets.cpp \
    jtextfield.cpp \
    jtextcomponent.cpp \
    jslider.cpp \
    jtogglebutton.cpp \
    dataflavor.cpp \
    exceptions.cpp \
    thread.cpp \
    xmlfile.cpp \
    tablecolumn.cpp \
    xtablecolumnmodel.cpp \
    propertychangeevent.cpp \
    propertychangelistenermap.cpp \
    propertychangelistenerproxy.cpp \
    propertychangesupport.cpp \
    eventobject.cpp \
    defaultlistmodel.cpp \
    defaultlistselectionmodel.cpp \
    defaulttablecolumnmodel.cpp \
    bitset.cpp \
    windowlistener.cpp \
    abstractshutdowntask.cpp \
    action.cpp \
    pushbuttondelegate.cpp \
    buttoncolumndelegate.cpp \
    consoleinterface.cpp \
    defaultboundedrangemodel.cpp \
    jbutton.cpp \
    jdialog.cpp \
    imageicon.cpp \
    file.cpp \
    borderlayout.cpp \
    flowlayout.cpp \
    jfilechooser.cpp \
    stringutil.cpp \
    mimetype.cpp \
    mimetypeparameterlist.cpp \
    indexedpropertychangeevent.cpp \
    actionevent.cpp \
    sleeperthread.cpp \
    level.cpp \
    quietshutdowntask.cpp \
    swingshutdowntask.cpp \
    jtree.cpp \
    gregoriancalendar.cpp \
    writer.cpp \
    json.cpp \
    htmltextedit.cpp \
    defaultlistmodela.cpp \
    system.cpp \
    bean.cpp \
    defaulttreemodel.cpp \
    catalogtreenode.cpp \
    treepath.cpp \
    defaultmutabletreenode.cpp \
    catalogtreeleaf.cpp \
    abstractnamedbean.cpp \
    namedbeanhandle.cpp \
    treeselectionmodel.cpp \
    treeselectionevent.cpp \
    defaulttreeselectionmodel.cpp \
    editableresizableimagepanel.cpp \
    filedrop.cpp \
    borderfactory.cpp \
    matteborder.cpp \
    emptyborder.cpp \
    component.cpp \
    droptargetcontext.cpp \
    droptarget.cpp \
    droptargetevent.cpp \
    droptargetdropevent.cpp \
    filedownloader.cpp \
    xmlinclude.cpp \
    catalogtree.cpp \
    xmlutil.cpp \
    tablecolumnmodelevent.cpp \
    classloader.cpp \
    serviceloader.cpp \
    permission.cpp \
    basicpermission.cpp \
    runtimepermission.cpp \
    provider.cpp \
    orderedproperties.cpp \
    stringtokenizer.cpp \
    rowsorter.cpp \
    rowsorterevent.cpp \
    listselectionevent.cpp \
    rowsorterutil.cpp \
    defaultrowsorter.cpp \
    rowfilter.cpp \
    tablerowsorter.cpp \
    tablemodelevent.cpp \
    sizesequence.cpp \
    optional.cpp \
    systemnamecomparator.cpp \
    classx.cpp \
    joptionpane.cpp \
    jrootpane.cpp \
    xinclude/xinclude.cpp \
    jmrilocalentityresolver.cpp \
    inputsource.cpp \
    catalogtreemodel.cpp \
    defaulttreemodel1.cpp \
    vetoablechangelistener.cpp \
    colorutil.cpp \
    filenameextensionfilter.cpp \
    jpanel.cpp \
    lineborder.cpp \
    mathutil.cpp \
    titledborder.cpp \
    abstractborder.cpp \
    stringutils.cpp \
    eventlistenerlist.cpp \
    class.cpp \
    treemodelevent.cpp \
    matcher.cpp \
    htmldelegate.cpp \
    bufferedoutputstream.cpp \
    bufferedinputstream.cpp \
    myslider.cpp \
    resizableimagepanel.cpp \
    reader.cpp \
    inputstreamreader.cpp \
    filereader.cpp \
    fileinputstream.cpp \
    buffer.cpp \
    charbuffer.cpp \
    spliterator.cpp \
    printwriter.cpp \
    abstractlistmodel.cpp \
    compoundborder.cpp \
    listdataevent.cpp \
    systemflavormap.cpp \
    changeevent.cpp \
    appcontext.cpp \
    imagepanel.cpp \
    bufferedimage.cpp \
    userpreferencesmanager.cpp \
    imageio.cpp \
    jlayeredpane.cpp \
    jmricolorchooser.cpp \
    vetoablechangesupport.cpp \
    propertyvetoexception.cpp \
    nosuchmethoderror.cpp \
    runtimeexception.cpp \
    abstractinstanceinitializer.cpp \
    jtabbedpane.cpp \
    serviceinfo.cpp \
    serviceinfoimpl.cpp \
    jmdns.cpp \
    inetaddress.cpp \
    jmdnsimpl.cpp \
    inet4address.cpp \
    inet6address.cpp \
    glasspane.cpp \
    drawsquares.cpp \
    placewindow.cpp \
    objects.cpp \
    lineunavailableexception.cpp \
    urisyntaxexception.cpp \
    unsupportedaudiofileexception.cpp \
    scriptexception.cpp \
    jcolorchooser.cpp \
    colorchooserdialog.cpp \
    abstractcolorchooserpanel.cpp \
    jmricolorchooserpanel.cpp \
    jlabel.cpp \
    editscene.cpp \
    quickpromptutil.cpp \
    fileoutputstream.cpp \
    loggingevent.cpp \
    priority.cpp \
    loglevel.cpp \
    filteroutputstream.cpp \
    printstream.cpp \
    myfileinputstream.cpp \
    bufferedwriter.cpp \
    outputstreamwriter.cpp \
    nmrapacket.cpp \
    vetoablechangelistenerproxy.cpp \
    predicate.cpp \
    collection.cpp \
    timer.cpp \
    beans.cpp \
    scalemanager.cpp \
    scale.cpp \
    scaleconfigxml.cpp \
    constrainedbean.cpp \
    unboundbean.cpp \
    arbitrarybean.cpp \
    arbitrarypropertysupport.cpp \
    mydefaultlistselectionmodel.cpp \
    jcombobox.cpp \
    jspinner.cpp \
    abstractspinnermodel.cpp \
    spinnernumbermodel.cpp \
    defaultcolorselectionmodel.cpp \
    colorchooserpanel.cpp \
    colormodel.cpp \
    colorpanel.cpp \
    slidingspinner.cpp \
    diagramcomponent.cpp \
    defaultswatchchooserpanel.cpp \
    defaultpreviewpanel.cpp \
    colorchoosercomponentfactory.cpp \
    splitbuttoncolorchooserpanel.cpp \
    jsplitbutton.cpp \
    colorlistpopupmenu.cpp \
    externallinkcontentviewerui.cpp \
    propertychangelistener.cpp \
    jcheckbox.cpp \
    etchedborder.cpp \
    jcheckboxmenuitem.cpp \
    keyadapter.cpp \
    loggingutil.cpp \
    localdatetime.cpp \
    jformattedtextfield.cpp \
    threadingutil.cpp \
    transferactionlistener.cpp \
    togglebutton.cpp \
    defaultcomboboxmodel.cpp

HEADERS += javaqt.h\
        javaqt_global.h \
    calendar.h \
    box.h \
    gridbaglayout.h \
    jtextarea.h \
    jseparator.h \
    abstractaction.h \
 jvetoablechangesupport.h \
    logger.h \
    gridbagconstraints.h \
    insets.h \
 thread.h \
 vetoablechangefirer.h \
 vetoablechangeprovider.h \
    vptr.h \
    jtextfield.h \
    tablemodel.h \
    tablemodellistener.h \
    eventlistener.h \
    jtextcomponent.h \
    jslider.h \
    jtogglebutton.h \
    dataflavor.h \
    exceptions.h \
    tablecolumn.h \
    tablecolumnmodel.h \
    xtablecolumnmodel.h \
    propertychangeevent.h \
    propertychangelistener.h \
    propertychangelistenermap.h \
    propertychangelistenerproxy.h \
    propertychangesupport.h \
    eventobject.h \
    defaultlistmodel.h \
    defaultlistselectionmodel.h \
    defaulttablecolumnmodel.h \
    listselectionmodel.h \
    bitset.h \
    windowlistener.h \
    abstractshutdowntask.h \
    shutdowntask.h \
    action.h \
    pushbuttondelegate.h \
    buttoncolumndelegate.h \
    consoleinterface.h \
    defaultboundedrangemodel.h \
    jbutton.h \
    jdialog.h \
    imageicon.h \
    file.h \
    filefilter.h \
    filenamefilter.h \
    borderlayout.h \
    flowlayout.h \
    jfilechooser.h \
    stringutil.h \
    mimetype.h \
    mimetypeparameterlist.h \
    changelistenermap.h \
    eventlistenerproxy.h \
    indexedpropertychangeevent.h \
    actionevent.h \
    xmlfile.h \
    sleeperthread.h \
    actionlistener.h \
    level.h \
    quietshutdowntask.h \
    swingshutdowntask.h \
    jtree.h \
    gregoriancalendar.h \
    printwriter.h \
    writer.h \
    json.h \
    htmltextedit.h \
    defaultlistmodela.h \
    system.h \
    bean.h \
    treemodel.h \
    defaulttreemodel.h \
    mutabletreenode.h \
    catalogtreenode.h \
    treepath.h \
    treenode.h \
    defaultmutabletreenode.h \
    catalogtreeleaf.h \
    abstractnamedbean.h \
    namedbeanhandle.h \
    treeselectionmodel.h \
    treeselectionevent.h \
    defaulttreeselectionmodel.h \
    rowmapper.h \
    treeselectionlistener.h \
    editableresizableimagepanel.h \
    filedrop.h \
    border.h \
    borderfactory.h \
    matteborder.h \
    emptyborder.h \
    component.h \
    droptargetlistener.h \
    dndconstants.h \
    droptargetcontext.h \
    droptargetcontextpeer.h \
    transferable.h \
    droptarget.h \
    droptargetevent.h \
    droptargetpeer.h \
    componentpeer.h \
    droptargetdropevent.h \
    filedownloader.h \
    xmlinclude.h \
    catalogtree.h \
    xmlutil.h \
    jmriserviceproviderinterface.h \
    tablecolumnmodellistener.h \
    tablecolumnmodelevent.h \
    classloader.h \
    serviceloader.h \
    iterator.h \
    permission.h \
    basicpermission.h \
    runtimepermission.h \
    preferencesfactory.h \
    provider.h \
    orderedproperties.h \
    stringtokenizer.h \
    rowsorter.h \
    sortorder.h \
    rowsorterevent.h \
    rowsorterlistener.h \
    listselectionevent.h \
    rowsorterutil.h \
    defaultrowsorter.h \
    comparator.h \
    comparable.h \
    rowfilter.h \
    tablerowsorter.h \
    tablestringconverter.h \
    tablemodelevent.h \
    sizesequence.h \
    optional.h \
    systemnamecomparator.h \
    classx.h \
    joptionpane.h \
    jrootpane.h \
    optionpaneui.h \
    xinclude/xinclude.h \
    usbcomponent.h \
    entityresolver.h \
    jmrilocalentityresolver.h \
    inputsource.h \
    loggerfactory.h \
    loggerbase.h \
    catalogtreemodel.h \
    defaulttreemodel1.h \
    vetoablechangelistener.h \
    propertychangeprovider.h \
    consumer.h \
    colorutil.h \
    filenameextensionfilter.h \
    menu.h \
    jpanel.h \
    lineborder.h \
    mathutil.h \
    titledborder.h \
    abstractborder.h \
    listselectionlistener.h \
    stringutils.h \
    treeexpansionevent.h \
    treeexpansionlistener.h \
    eventlistenerlist.h \
    class.h \
    treemodelevent.h \
    treemodellistener.h \
    matcher.h \
    htmldelegate.h \
    componentfactory.h \
    bufferedoutputstream.h \
    bufferedinputstream.h \
    myslider.h \
    resizableimagepanel.h \
    reader.h \
    inputstreamreader.h \
    filereader.h \
    fileinputstream.h \
    buffer.h \
    charbuffer.h \
    spliterator.h \
    abstractlistmodel.h \
    listmodel.h \
    compoundborder.h \
    listdataevent.h \
    flavormap.h \
    systemflavormap.h \
    changeevent.h \
    appcontext.h \
    initeventlistener.h \
    imagepanel.h \
    bufferedimage.h \
    userpreferencesmanager.h \
    imageio.h \
    jlayeredpane.h \
    jmricolorchooser.h \
    vetoablechangesupport.h \
    propertyvetoexception.h \
    nosuchmethoderror.h \
    namedbeancomparator.h \
    runtimeexception.h \
    windowadapter.h \
    instancemanagerautodefault.h \
    instancemanagerautoinitialize.h \
    abstractinstanceinitializer.h \
    instanceinitializer.h \
    instancemanagerautodefault.h \
    instancemanagerautoinitialize.h \
    inputverifier.h \
    namedbeanpropertydescriptor.h \
    jtabbedpane.h \
    serviceinfo.h \
    serviceinfoimpl.h \
    jmdns.h \
    inetaddress.h \
    jmdnsimpl.h \
    inet4address.h \
    inet6address.h \
    glasspane.h \
    drawsquares.h \
    placewindow.h \
    objects.h \
    lineunavailableexception.h \
    urisyntaxexception.h \
    unsupportedaudiofileexception.h \
    scriptexception.h \
    jcomponent.h \
    colorchooserdialog.h \
    colorselectionmodel.h \
    abstractcolorchooserpanel.h \
    changelistener.h \
    jcolorchooser.h \
    jmricolorchooserpanel.h \
    linkingobject.h \
    jlabel.h \
    editscene.h \
    quickpromptutil.h \
    popupmenulistener.h \
    popupmenuevent.h \
    reportable.h \
    fileoutputstream.h \
    loggingevent.h \
    priority.h \
    loglevel.h \
    filteroutputstream.h \
    printstream.h \
    myfileinputstream.h \
    providingmanager.h \
    nmrapacket.h \
    vetoablechangelistenerproxy.h \
    predicate.h \
    comparatort.h \
    alphanumcomparator.h \
    collection.h \
    discoverylistener.h \
    timer.h \
    beans.h \
    scalemanager.h \
    scale.h \
    scaleconfigxml.h \
    constrainedbean.h \
    unboundbean.h \
    beaninterface.h \
    arbitrarybean.h \
    arbitrarypropertysupport.h \
    mydefaultlistselectionmodel.h \
    jcombobox.h \
    jspinner.h \
    spinnermodel.h \
    abstractspinnermodel.h \
    spinnernumbermodel.h \
    defaultcolorselectionmodel.h \
    colorchooserpanel.h \
    colormodel.h \
    colorpanel.h \
    slidingspinner.h \
    diagramcomponent.h \
    defaultswatchchooserpanel.h \
    defaultpreviewpanel.h \
    colorchoosercomponentfactory.h \
    splitbuttoncolorchooserpanel.h \
    jsplitbutton.h \
    colorlistpopupmenu.h \
    splitbuttonactionlistener.h \
    externallinkcontentviewerui.h \
    namedbeanusernamecomparator.h \
    focuslistener.h \
    focusevent.h \
    itemevent.h \
    itemlistener.h \
    jcheckbox.h \
    etchedborder.h \
    supplier.h \
    jcheckboxmenuitem.h \
    keyadapter.h \
    keylistener.h \
    loggingutil.h \
    localdatetime.h \
    jformattedtextfield.h \
    threadingutil.h \
    transferactionlistener.h \
    tablecellrenderer.h \
    tablecelleditor.h \
    tabledelegates.h \
    togglebutton.h \
    defaultcomboboxmodel.h \
    runnable.h \
    comboboxmodel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

TRANSLATIONS += \
    languages/JavaQt_de.ts \
    languages/JavaQt_en.ts


win32:CONFIG(release, debug|release): LIBS += -L$$PROJ_DIR/QtZeroConf-master/release/ -lQtZeroConf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PROJ_DIR/QtZeroConf-master/debug/ -lQtZeroConf
else:unix: LIBS += -L$$PROJ_DIR/QtZeroConf-master/ -lQtZeroConf

INCLUDEPATH += $$PROJ_DIR/QtZeroConf-master
DEPENDPATH += $$PROJ_DIR/QtZeroConf-master


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/release/ -lappslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/debug/ -lappslib
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/ -lappslib
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/ -lappslibd

INCLUDEPATH += $$PWD/../appslib
DEPENDPATH += $$PWD/../appslib
