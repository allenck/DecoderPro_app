#-------------------------------------------------
#
# Project created by QtCreator 2019-11-01T12:16:18
#
#-------------------------------------------------

QT       += widgets xml network

TARGET = tests
TEMPLATE = lib

MOC_DIR = moc_obj
OBJECTS_DIR += moc_obj

DEFINES += TESTS_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        tests.cpp \
        junitutil.cpp \
        temporaryfolder.cpp \
        RosterTest/rosterentrytestaction.cpp \
        RosterTest/rostertest.cpp \
        RosterTest/rostertestaction.cpp \
        RosterTest/rosterentrytest.cpp \
        RosterTest/rostertestutil.cpp \
        assert1.cpp \
        RosterTest/rosterentrypanetest.cpp \
        RosterTest/rosterentrypanetestaction.cpp \
        ProfileTest/profiletest.cpp \
        ProfileTest/profiletestaction.cpp \
        ProfileTest/profilemanagertest.cpp \
        ProfileTest/profilemanagertestaction.cpp \
        loconet/slotmanagertest.cpp \
        loconet/loconetinterfacescaffold.cpp \
        loconet/slotmanagertestaction.cpp \
        loconet/loconetslottest.cpp \
        loconet/loconetslottestaction.cpp \
        junitappender.cpp \
        loconet/lnopsmodeprogrammertest.cpp \
        assume.cpp \
        proglistenerscaffold.cpp \
        loconet/lnopsmodeprogrammertestaction.cpp \
        loconet/loconetmessagetest.cpp \
        loconet/loconetmessagetestaction.cpp \
        testsmenu.cpp \
        loconet/lntrafficcontrollertest.cpp \
        loconet/lntrafficcontrollertestaction.cpp \
        abstractmessagetestbase.cpp \
        sprog/sprogmessagetest.cpp \
        sprog/sprogmessagetestaction.cpp \
        loconet/lnpacketizertest.cpp \
        loconet/lnportcontrollertestaction.cpp \
        loconet/lnportcontrollertest.cpp \
        abstractserialportcontrollertestbase.cpp \
        abstractportcontrollertestbase.cpp \
        loconet/lnpacketizertestaction.cpp \
        abstractthrottletest.cpp \
        loconet/loconetthrottletest.cpp \
        ProfileTest/profileutilstest.cpp \
        ProfileTest/profileutilstestaction.cpp \
        loconet/lntrafficroutertest.cpp \
        loconet/lntrafficroutertestaction.cpp \
        loconet/loconetconsisttest.cpp \
        loconet/loconetconsisttestaction.cpp \
        loconet/lnpowermanagertest.cpp \
        abstractpowermanagertestbase.cpp \
        loconet/lnpowermanagertestaction.cpp \
        abstractturnouttestbase.cpp \
        loconet/lnturnouttest.cpp \
        loconet/lnturnouttestaction.cpp \
        abstractreportertest.cpp \
        abstractsensortestbase.cpp \
        abstractconsisttestbase.cpp \
        loconet/lnsensortest.cpp \
        loconet/lnsensortestaction.cpp \
        addressedprogrammertestbase.cpp \
        programmertestbase.cpp \
        loconet/lnreportertest.cpp \
        abstractreportertestbase.cpp \
        loconet/lnreportertestaction.cpp \
        loconet/lnsensoraddresstest.cpp \
        loconet/lnsensoraddresstestaction.cpp \
        loconet/lnsensormanagertest.cpp \
        abstractsensormgrtestbase.cpp \
        abstractmanagertestbase.cpp \
        loconet/lnsensormanagertestaction.cpp \
        loconet/lndeferprogranmmertest.cpp \
        abstractprovidingturnoutmanagertestbase.cpp \
        abstractturnoutmgrtestbase.cpp \
        loconet/lnturnoutmanagertest.cpp \
        testuserpreferencesmanager.cpp \
        loconet/lndeferprogrammertestaction.cpp \
        loconet/lnturnoutmanagertestaction.cpp \
        misc/proxyturnoutmanagertest.cpp \
        misc/proxyturnoutmanagertestaction.cpp \
        loconet/lnlighttest.cpp \
        loconet/lnlighttestaction.cpp \
        misc/proxysensormanagertest.cpp \
        misc/proxysensormanagertestaction.cpp \
        misc/proxyreportermanagertest.cpp \
        abstractreportermgrtestbase.cpp \
        abstractprovidingreportermanagertestbase.cpp \
        misc/proxyreportmanagertestaction.cpp \
        misc/proxylightmanagertest.cpp \
        misc/proxylightmanagertestaction.cpp \
        misc/multiindexprogrammerfacadetest.cpp \
        misc/multiindexprogrammerfacadetestaction.cpp \
        misc/addressedhighcvprogranmmerfacadetest.cpp \
        misc/addressedhighcvprogranmmerfacadetestaction.cpp \
        misc/opsmodedelayedprogrammerfacadetest.cpp \
        misc/opsmodedelayedprogrammerfacadetestaction.cpp \
        misc/verifywriteprogrammerfacadetest.cpp \
        misc/verifywriteprogrammerfacadetestaction.cpp \
        misc/twoindextcsprogrammerfacadetest.cpp \
        misc/twoindextcsprogrammerfacadetestaction.cpp \
        misc/paneprogpanetest.cpp \
        misc/paneprogpanetestaction.cpp \
        misc/paneprogframetest.cpp \
        misc/decoderfiletest.cpp \
        misc/paneprogframetestaction.cpp \
        misc/decoderfiletestaction.cpp \
        loconet/loconetmessageinterprettest.cpp \
        loconet/loconetmessageinterprettestaction.cpp \
        loconet/lnreportermanagertest.cpp \
        loconet/lnreportermanagertestaction.cpp \
        loconet/loconetsystemconnectionmemotest.cpp \
        systemconnectionmemotestbase.cpp \
        loconet/loconetsystemconnectionmemotestaction.cpp \
        abstractprovidingmemorymanagertestbase.cpp \
        misc/defaultmemorymanagertest.cpp \
        misc/defaultmemorymanagertestaction.cpp \
        misc/lightcontroltest.cpp \
        misc/lightcontroltestaction.cpp \
    NamedBeans/namedbeanusernamecomparatortest.cpp \
    NamedBeans/namedbeanusernamecomparatortestaction.cpp \
    loconet/loconetmessageexceptiontest.cpp \
    loconet/loconetmessageexceptiontestaction.cpp \
    loconet/loconetthrottletestaction.cpp \
    misc/nmrapackettest.cpp \
    misc/nmrapackettestaction.cpp \
    misc/accessoryopsmodeprogrammerfacadetest.cpp \
    mockcommandstation.cpp \
    misc/accessoryopsmodeprogrammerfacadetestaction.cpp \
    signals/dccsignalheadtest.cpp \
    abstractsignalheadtestbase.cpp \
    signals/dccsignalheadtestaction.cpp \
    signals/singleturnoutsignalheadtest.cpp \
    signals/singleturnoutsignalheadtestaction.cpp \
    signals/doubleturnoutsignalheadtest.cpp \
    propertychangelistenerscaffold.cpp \
    signals/doubleturnoutsignalheadtestaction.cpp \
    signals/virtualsignalheadtest.cpp \
    signals/virtualsignalheadtestaction.cpp \
    signals/signalheadsignalmasttest.cpp \
    signals/signalheadsignalmasttestaction.cpp \
    signals/signalheadsignalmastaddpanetest.cpp \
    signals/abstractsignalmastaddpanetestbase.cpp \
    signals/signalheadsignalmastaddpanetestaction.cpp \
    signals/matrixsignalmasttest.cpp \
    signals/matrixsignalmasttestaction.cpp \
    signals/matrixsignalmastaddpanetest.cpp \
    signals/virtualsignalmastaddpanetest.cpp \
    signals/matrixsignalmastaddpanetestaction.cpp \
    signals/virtualsignalmastaddpanetestaction.cpp \
    signals/tripleturnoutsignalheadtest.cpp \
    signals/tripleoutputsignalheadtest.cpp \
    signals/dccsignalmastaddpanetest.cpp \
    signals/tripleoutputsignalheadtestaction.cpp \
    signals/tripleturnoutsignalheadtestaction.cpp \
    signals/dccsignalmastaddpanetestaction.cpp \
    signals/turnoutsignalmastaddpanetest.cpp \
    signals/turnoutsignalmastaddpanetestaction.cpp \
    signals/turnoutsignalmasttest.cpp \
    signals/turnoutsignalmasttestaction.cpp \
    logix/logixactiontest.cpp \
    logix/logixactiontestaction.cpp \
    logix/configxmlmanagertest.cpp \
    warrants/warranttest.cpp \
    mockshutdownmanager.cpp \
    warrants/warranttestaction.cpp \
    warrants/warrantpreferencespaneltest.cpp \
    warrants/warrantpreferencespaneltestaction.cpp \
    misc/jmriuserpreferencesmanagertest.cpp \
    misc/jmriuserpreferencesmanagertestaction.cpp \
    operations/optionsmenutest.cpp \
    operations/optionsmenutestaction.cpp \
    positionables/signalmasticontest.cpp \
    positionables/positionableicontest.cpp \
    positionables/positionabletestbase.cpp \
    positionables/editorscaffold.cpp \
    positionables/editorframeoperator.cpp \
    positionables/signalmasticontestaction.cpp \
    misc/colorchooserpaneltest.cpp \
    misc/colorchooserpaneltestaction.cpp \
    misc/dcclocoaddresstest.cpp \
    misc/dcclocoaddresstestaction.cpp \
    jmrijframetestbase.cpp \
    misc/controllerfilterframetest.cpp \
    misc/controllerfilterframetestaction.cpp \
    consisttoolframetest.cpp \
    consisttoolscaffold.cpp \
    jframeoperator.cpp \
    throttleoperator.cpp \
    consisttoolframetestaction.cpp \
    jemmyutil.cpp \
    testconsistmanager.cpp \
    namecomponentchooser.cpp \
    loconet/enterreporterdialogtest.cpp \
    cabsignals/cabsignaltablemodeltest.cpp \
    cabsignals/defaultcabsignaltest.cpp \
    cabsignals/defaultcabsignaltestaction.cpp \
    cabsignals/cabsignaltablemodeltestaction.cpp \
    entryexit/entryexitpairstest.cpp \
    entryexittesttools.cpp \
    entryexit/entryexitpairstestaction.cpp \
    entryexit/destinationpointstest.cpp \
    entryexit/destinationpointstestaction.cpp \
    entryexit/pointdetailstest.cpp \
    entryexit/pointdetailstestaction.cpp \
    entryexit/sectiontest.cpp \
    entryexit/sectiontestaction.cpp \
    entryexit/sourcetest.cpp \
    entryexit/sourcetestaction.cpp \
    layouteditor/layouteditortoolstest.cpp \
    layouteditor/layouteditortoolstestaction.cpp \
    layouteditor/layoutshapetest.cpp \
    layouteditor/layoutshapetestaction.cpp \
    entryexit/circuitbuildertest.cpp \
    entryexit/circuitbuildertestaction.cpp \
    loconet/controlpaneltest.cpp \
    loconet/controlpaneltestaction.cpp \
    misc/meterframetest.cpp \
    loconet/lnpredefinedmeterstest.cpp \
    loconet/lnpredefinedmeterstestaction.cpp \
    loconet/lniplimplementationtest.cpp \
    loconet/lniplimplementationtestaction.cpp \
    tables/oblocktableactiontest.cpp \
    tables/oblocktableactiontestaction.cpp \
    loconet/lncvdevicetest.cpp \
    loconet/lncvdevicetestaction.cpp \
    loconet/lncvmessagecontentsclasstest.cpp \
    loconet/lncvmessagecontentsclasstestaction.cpp \
    jmripaneltest.cpp \
    loconet/lncvprogpanetestaction.cpp \
    loconet/lncvprogtablemodeltest.cpp \
    loconet/lncvprogtablemodeltestaction.cpp \
    loconet/lncvprogpanetest.cpp \
    misc/identifydecodertest.cpp \
    misc/identifydecodertestaction.cpp \
    misc/cvutiltest.cpp \
    misc/cvutiltestaction.cpp

HEADERS += \
        tests.h \
        tests_global.h \
        junitutil.h \
        temporaryfolder.h \
        RosterTest/rosterentrytestaction.h \
        RosterTest/rostertest.h \
        RosterTest/rostertestaction.h \
        RosterTest/rosterentrytest.h \
        RosterTest/rostertestutil.h \
        assert1.h \
        RosterTest/rosterentrypanetest.h \
        RosterTest/rosterentrypanetestaction.h \
        ProfileTest/profiletest.h \
        ProfileTest/profiletestaction.h \
        ProfileTest/profilemanagertest.h \
        ProfileTest/profilemanagertestaction.h \
        loconet/slotmanagertest.h \
        loconet/loconetinterfacescaffold.h \
        loconet/slotmanagertestaction.h \
        loconet/loconetslottest.h \
        loconet/loconetslottestaction.h \
        junitappender.h \
        loconet/lnopsmodeprogrammertest.h \
        assume.h \
        proglistenerscaffold.h \
        loconet/lnopsmodeprogrammertestaction.h \
        loconet/loconetmessagetest.h \
        loconet/loconetmessagetestaction.h \
        loconet/lntrafficcontrollertest.h \
        loconet/lntrafficcontrollertestaction.h \
        abstractmessagetestbase.h \
        sprog/sprogmessagetest.h \
        sprog/sprogmessagetestaction.h \
        loconet/lnpacketizertest.h \
        loconet/lnportcontrollertestaction.h \
        loconet/lnportcontrollertest.h \
        abstractserialportcontrollertestbase.h \
        abstractportcontrollertestbase.h \
        loconet/lnpacketizertestaction.h \
        abstractthrottletest.h \
        loconet/loconetthrottletest.h \
        ProfileTest/profileutilstest.h \
        ProfileTest/profileutilstestaction.h \
        loconet/lntrafficroutertest.h \
        loconet/lntrafficroutertestaction.h \
        loconet/loconetconsisttest.h \
        loconet/loconetconsisttestaction.h \
        loconet/lnpowermanagertest.h \
        abstractpowermanagertestbase.h \
        loconet/lnpowermanagertestaction.h \
        abstractturnouttestbase.h \
        loconet/lnturnouttest.h \
        loconet/lnturnouttestaction.h \
        abstractreportertest.h \
        abstractsensortestbase.h \
        abstractconsisttestbase.h \
        loconet/lnsensortest.h \
        loconet/lnsensortestaction.h \
        addressedprogrammertestbase.h \
        programmertestbase.h \
        loconet/lnreportertest.h \
        abstractreportertestbase.h \
        loconet/lnreportertestaction.h \
        loconet/lnsensoraddresstest.h \
        loconet/lnsensoraddresstestaction.h \
        loconet/lnsensormanagertest.h \
        abstractsensormgrtestbase.h \
        abstractmanagertestbase.h \
        loconet/lnsensormanagertestaction.h \
        loconet/lndeferprogranmmertest.h \
        abstractprovidingturnoutmanagertestbase.h \
        abstractturnoutmgrtestbase.h \
        loconet/lnturnoutmanagertest.h \
        testuserpreferencesmanager.h \
        loconet/lndeferprogrammertestaction.h \
        loconet/lnturnoutmanagertestaction.h \
        misc/proxyturnoutmanagertest.h \
        misc/proxyturnoutmanagertestaction.h \
        loconet/lnlighttest.h \
        loconet/lnlighttestaction.h \
        misc/proxysensormanagertest.h \
        misc/proxysensormanagertestaction.h \
        misc/proxyreportermanagertest.h \
        abstractreportermgrtestbase.h \
        abstractprovidingreportermanagertestbase.h \
        misc/proxyreportmanagertestaction.h \
        misc/proxylightmanagertest.h \
        misc/proxylightmanagertestaction.h \
        misc/multiindexprogrammerfacadetest.h \
        misc/multiindexprogrammerfacadetestaction.h \
        misc/addressedhighcvprogranmmerfacadetest.h \
        misc/addressedhighcvprogranmmerfacadetestaction.h \
        misc/opsmodedelayedprogrammerfacadetest.h \
        misc/opsmodedelayedprogrammerfacadetestaction.h \
        misc/verifywriteprogrammerfacadetest.h \
        misc/verifywriteprogrammerfacadetestaction.h \
        misc/twoindextcsprogrammerfacadetest.h \
        misc/twoindextcsprogrammerfacadetestaction.h \
        misc/paneprogpanetest.h \
        misc/paneprogpanetestaction.h \
        misc/paneprogframetest.h \
        misc/decoderfiletest.h \
        misc/paneprogframetestaction.h \
        misc/decoderfiletestaction.h \
        loconet/loconetmessageinterprettest.h \
        loconet/loconetmessageinterprettestaction.h \
        loconet/lnreportermanagertest.h \
        loconet/lnreportermanagertestaction.h \
        loconet/loconetsystemconnectionmemotest.h \
        systemconnectionmemotestbase.h \
        loconet/loconetsystemconnectionmemotestaction.h \
        abstractprovidingmemorymanagertestbase.h \
        misc/defaultmemorymanagertest.h \
        misc/defaultmemorymanagertestaction.h \
        misc/lightcontroltest.h \
        misc/lightcontroltestaction.h \
    NamedBeans/namedbeanusernamecomparatortest.h \
    NamedBeans/namedbeanusernamecomparatortestaction.h \
    loconet/loconetmessageexceptiontest.h \
    loconet/loconetmessageexceptiontestaction.h \
    loconet/loconetthrottletestaction.h \
    misc/nmrapackettest.h \
    misc/nmrapackettestaction.h \
    misc/accessoryopsmodeprogrammerfacadetest.h \
    mockcommandstation.h \
    misc/accessoryopsmodeprogrammerfacadetestaction.h \
    signals/dccsignalheadtest.h \
    abstractsignalheadtestbase.h \
    signals/dccsignalheadtestaction.h \
    signals/singleturnoutsignalheadtest.h \
    signals/singleturnoutsignalheadtestaction.h \
    signals/doubleturnoutsignalheadtest.h \
    propertychangelistenerscaffold.h \
    signals/doubleturnoutsignalheadtestaction.h \
    signals/virtualsignalheadtest.h \
    signals/virtualsignalheadtestaction.h \
    signals/signalheadsignalmasttest.h \
    signals/signalheadsignalmasttestaction.h \
    signals/signalheadsignalmastaddpanetest.h \
    signals/abstractsignalmastaddpanetestbase.h \
    signals/signalheadsignalmastaddpanetestaction.h \
    signals/matrixsignalmasttest.h \
    signals/matrixsignalmasttestaction.h \
    signals/matrixsignalmastaddpanetest.h \
    signals/virtualsignalmastaddpanetest.h \
    signals/matrixsignalmastaddpanetestaction.h \
    signals/virtualsignalmastaddpanetestaction.h \
    signals/tripleturnoutsignalheadtest.h \
    signals/tripleoutputsignalheadtest.h \
    signals/dccsignalmastaddpanetest.h \
    signals/tripleoutputsignalheadtestaction.h \
    signals/tripleturnoutsignalheadtestaction.h \
    signals/dccsignalmastaddpanetestaction.h \
    signals/turnoutsignalmastaddpanetest.h \
    signals/turnoutsignalmastaddpanetestaction.h \
    signals/turnoutsignalmasttest.h \
    signals/turnoutsignalmasttestaction.h \
    logix/logixactiontest.h \
    logix/logixactiontestaction.h \
    logix/configxmlmanagertest.h \
    warrants/warranttest.h \
    mockshutdownmanager.h \
    warrants/warranttestaction.h \
    warrants/warrantpreferencespaneltest.h \
    warrants/warrantpreferencespaneltestaction.h \
    misc/jmriuserpreferencesmanagertest.h \
    misc/jmriuserpreferencesmanagertestaction.h \
    operations/optionsmenutest.h \
    operations/optionsmenutestaction.h \
    positionables/signalmasticontest.h \
    positionables/positionableicontest.h \
    positionables/positionabletestbase.h \
    positionables/editorscaffold.h \
    positionables/editorframeoperator.h \
    positionables/signalmasticontestaction.h \
    misc/colorchooserpaneltest.h \
    misc/colorchooserpaneltestaction.h \
    misc/dcclocoaddresstest.h \
    misc/dcclocoaddresstestaction.h \
    jmrijframetestbase.h \
    misc/controllerfilterframetest.h \
    misc/controllerfilterframetestaction.h \
    consisttoolframetest.h \
    consisttoolscaffold.h \
    jframeoperator.h \
    throttleoperator.h \
    consisttoolframetestaction.h \
    jemmyutil.h \
    testconsistmanager.h \
    namecomponentchooser.h \
    loconet/enterreporterdialogtest.h \
    abstracttableactionbase.h \
    cabsignals/cabsignaltablemodeltest.h \
    cabsignals/defaultcabsignaltest.h \
    cabsignals/defaultcabsignaltestaction.h \
    cabsignals/cabsignaltablemodeltestaction.h \
    entryexit/entryexitpairstest.h \
    entryexittesttools.h \
    entryexit/entryexitpairstestaction.h \
    entryexit/destinationpointstest.h \
    entryexit/destinationpointstestaction.h \
    entryexit/pointdetailstest.h \
    entryexit/pointdetailstestaction.h \
    entryexit/sectiontest.h \
    entryexit/sectiontestaction.h \
    entryexit/sourcetest.h \
    entryexit/sourcetestaction.h \
    layouteditor/layouteditortoolstest.h \
    layouteditor/layouteditortoolstestaction.h \
    layouteditor/layoutshapetest.h \
    layouteditor/layoutshapetestaction.h \
    entryexit/circuitbuildertest.h \
    entryexit/circuitbuildertestaction.h \
    loconet/controlpaneltest.h \
    loconet/controlpaneltestaction.h \
    misc/meterframetest.h \
    loconet/lnpredefinedmeterstest.h \
    loconet/lnpredefinedmeterstestaction.h \
    loconet/lniplimplementationtest.h \
    loconet/lniplimplementationtestaction.h \
    tables/oblocktableactiontest.h \
    tables/oblocktableactiontestaction.h \
    loconet/lncvdevicetest.h \
    loconet/lncvdevicetestaction.h \
    loconet/lncvmessagecontentsclasstest.h \
    loconet/lncvmessagecontentsclasstestaction.h \
    lncvprogpanetest.h \
    jmripaneltest.h \
    loconet/lncvprogpanetestaction.h \
    loconet/lncvprogtablemodeltest.h \
    loconet/lncvprogtablemodeltestaction.h \
    loconet/lncvprogpanetest.h \
    misc/identifydecodertest.h \
    misc/identifydecodertestaction.h \
    misc/cvutiltest.h \
    misc/cvutiltestaction.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/release/ -lJavaQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/debug/ -lJavaQt
else:unix: LIBS += -L$$PWD/../JavaQt/ -lJavaQt

INCLUDEPATH += $$PWD/../JavaQt
DEPENDPATH += $$PWD/../JavaQt

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/release/ -lappslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/debug/ -lappslib
else:unix: LIBS += -L$$PWD/../appslib/ -lappslib

INCLUDEPATH += $$PWD/../appslib
DEPENDPATH += $$PWD/../appslib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPref/release/ -lPref
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPref/debug/ -lPref
else:unix: LIBS += -L$$PWD/../libPref/ -lPref

INCLUDEPATH += $$PWD/../libPref
DEPENDPATH += $$PWD/../libPref

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3/release/ -lPr3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3/debug/ -lPr3
else:unix: LIBS += -L$$PWD/../libPr3/ -lPr3

INCLUDEPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/Signal \
 $$PWD/../Tables $$PWD/../libPr3/Throttle $$PWD/../libPr3/LocoIO $$PWD/../libPr3/loconet \
 $$PWD/../libPr3/rfid $$PWD/../libPr3/Json $$PWD/../libPr3/WiThrottle $$PWD/../libPr3/sprog \
 $$PWD/../libPr3/loconet/HexFile
DEPENDPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/Signal \
 $$PWD/../Tables $$PWD/../libPr3/Throttle $$PWD/../libPr3/LocoIO $$PWD/../libPr3/loconet \
 $$PWD/../libPr3/rfid $$PWD/../libPr3/Json $$PWD/../libPr3/WiThrottle $$PWD/../libPr3/sprog |
 $$PWD/../libPr3/loconet/HexFile

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LayoutEditor/release/ -lLayoutEditor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LayoutEditor/debug/ -lLayoutEditor
else:unix: LIBS += -L$$PWD/../LayoutEditor/ -lLayoutEditor

INCLUDEPATH += $$PWD/../LayoutEditor $$PWD/../LayoutEditor/scripts
DEPENDPATH += $$PWD/../LayoutEditor $$PWD/../LayoutEditor/scripts
