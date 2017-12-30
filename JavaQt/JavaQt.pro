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

SOURCES += javaqt.cpp \
    fileutil.cpp \
    calendar.cpp \
    box.cpp \
    gridbaglayout.cpp \
    jtextarea.cpp \
    jseparator.cpp \
    jmripanel.cpp \
    abstractaction.cpp \
    logger.cpp \
    gridbagconstraints.cpp \
    insets.cpp \
    jtextfield.cpp \
    eventlistener.cpp \
    jtextcomponent.cpp \
    jslider.cpp \
    jtogglebutton.cpp \
    dataflavor.cpp \
    exceptions.cpp \
    tablecolumn.cpp \
    xtablecolumnmodel.cpp \
    properties.cpp \
    propertychangeevent.cpp \
    propertychangelistener.cpp \
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
    namedicon.cpp \
    borderlayout.cpp \
    flowlayout.cpp \
    jfilechooser.cpp \
    matcher.cpp \
    stringutil.cpp \
    mimetype.cpp \
    mimetypeparameterlist.cpp \
    indexedpropertychangeevent.cpp \
    actionevent.cpp \
    xmlfile.cpp \
    sleeperthread.cpp \
    level.cpp \
    quietshutdowntask.cpp \
    swingshutdowntask.cpp \
    jtree.cpp \
    gregoriancalendar.cpp \
    printwriter.cpp \
    writer.cpp \
    json.cpp \
    htmltextedit.cpp \
    defaultlistmodela.cpp \
    system.cpp \
    bean.cpp \
    fileutilsupport.cpp \
    defaulttreemodel.cpp \
    catalogtreenode.cpp \
    treepath.cpp \
    defaultmutabletreenode.cpp \
    catalogtreeleaf.cpp \
    abstractnamedbean.cpp \
    namedbean.cpp \
    namedbeanhandle.cpp \
    treeselectionmodel.cpp \
    treeselectionevent.cpp \
    defaulttreeselectionmodel.cpp \
    resizableimagepanel.cpp \
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
    loggerbase.cpp \
    loggerfactory.cpp \
    catalogtreemodel.cpp \
    defaulttreemodel1.cpp \
    vetoablechangelistener.cpp \
    colorutil.cpp \
    filenameextensionfilter.cpp
    #pattern.cpp \
    #charsequence.cpp \
    #patternsyntaxexception.cpp

HEADERS += javaqt.h\
        javaqt_global.h \
    calendar.h \
    box.h \
    gridbaglayout.h \
    jtextarea.h \
    jseparator.h \
    jmripanel.h \
    abstractaction.h \
    logger.h \
    gridbagconstraints.h \
    insets.h \
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
    properties.h \
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
    fileutil.h \
    namedicon.h \
    borderlayout.h \
    flowlayout.h \
    jfilechooser.h \
    matcher.h \
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
    fileutilsupport.h \
    treemodel.h \
    defaulttreemodel.h \
    mutabletreenode.h \
    catalogtreenode.h \
    treepath.h \
    treenode.h \
    defaultmutabletreenode.h \
    catalogtreeleaf.h \
    abstractnamedbean.h \
    namedbean.h \
    namedbeanhandle.h \
    manager.h \
    treeselectionmodel.h \
    treeselectionevent.h \
    defaulttreeselectionmodel.h \
    rowmapper.h \
    treeselectionlistener.h \
    resizableimagepanel.h \
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
    filenameextensionfilter.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

TRANSLATIONS += \
    languages/JavaQt_de.ts \
    languages/JavaQt_en.ts
