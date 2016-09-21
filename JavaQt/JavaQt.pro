#-------------------------------------------------
#
# Project created by QtCreator 2016-05-02T10:59:42
#
#-------------------------------------------------

#QT       -= gui
QT += xml printsupport
greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets gui
}
TARGET = JavaQt
TEMPLATE = lib

DEFINES += JAVAQT_LIBRARY

SOURCES += javaqt.cpp \
    calendar.cpp \
    box.cpp \
    gridbaglayout.cpp \
    jtextarea.cpp \
    jtable.cpp \
    jseparator.cpp \
    jmripanel.cpp \
    jframe.cpp \
    abstractaction.cpp \
    abstracttablemodel.cpp \
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
    defaulttablemodel.cpp \
    bitset.cpp \
    windowinterface.cpp \
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
    fileutil.cpp \
    namedicon.cpp \
    borderlayout.cpp \
    flowlayout.cpp \
    jfilechooser.cpp \
    dndjtable.cpp \
    matcher.cpp \
    stringutil.cpp \
    mimetype.cpp \
    mimetypeparameterlist.cpp \
    indexedpropertychangeevent.cpp \
    actionevent.cpp \
    jframeinterface.cpp \
    xmlfile.cpp \
    sleeperthread.cpp \
    level.cpp \
    quietshutdowntask.cpp \
    swingshutdowntask.cpp \
    jtree.cpp \
    gregoriancalendar.cpp \
    hardcopywriter.cpp \
    printwriter.cpp \
    writer.cpp \
    json.cpp \
    htmltextedit.cpp \
    jlist.cpp \
    defaultlistmodela.cpp \
    system.cpp \
    bean.cpp \
    fileutilsupport.cpp

HEADERS += javaqt.h\
        javaqt_global.h \
    calendar.h \
    box.h \
    gridbaglayout.h \
    dndjtable.h \
    jtextarea.h \
    jtable.h \
    jseparator.h \
    jmripanel.h \
    jframeinterface.h \
    jframe.h \
    abstractaction.h \
    abstracttablemodel.h \
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
    defaulttablemodel.h \
    listselectionmodel.h \
    bitset.h \
    windowinterface.h \
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
    hardcopywriter.h \
    printwriter.h \
    writer.h \
    json.h \
    htmltextedit.h \
    jlist.h \
    defaultlistmodela.h \
    system.h \
    bean.h \
    fileutilsupport.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

TRANSLATIONS += \
    languages/JavaQt_de.ts \
    languages/JavaQt_en.ts
