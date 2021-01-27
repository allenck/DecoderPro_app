#-------------------------------------------------
#
# Project created by QtCreator 2019-11-01T12:18:15
#
#-------------------------------------------------

QT       += widgets xml websockets

TARGET = operations
TEMPLATE = lib

MOC_DIR = moc_obj
OBJECTS_DIR += moc_obj

PROJ_DIR=$$(PROJ_DIR) # get project directory from env
isEmpty( PROJ_DIR ) {
  win32:PROJ_DIR=C:/Projects
  unix:PROJ_DIR=/home/allen/Projects
}

DEFINES += OPERATIONS_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

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
    message(operations: found $$PYTHONQT_PREFIX/lib/libPythonQt-Qt5-Python$${PYTHON_VERSION}_d.so)
} else {
    message(operations: not found $$PYTHONQT_PREFIX/lib/libPythonQt-Qt5-Python$${PYTHON_VERSION}_d.so)
}
#CONFIG += scripts
equals(ENABLE_SCRIPTING, "Y") {
    DEFINES += SCRIPTING_ENABLED

SOURCES += \
    trainsscriptaction.cpp \
    trainsscriptframe.cpp

HEADERS += \
    trainsscriptaction.h \
    trainscriptframe.h

    message("operations: scripting enabled")
} else {
    message("operations: scripting disabled")
}

SOURCES += \
        operations.cpp \
        operationsmenu.cpp \
        trainmanifesttext.cpp \
        operationsxml.cpp \
        trainswitchlisttext.cpp \
        schedule.cpp \
        scheduleitem.cpp \
        setup.cpp \
        routemanagerxml.cpp \
        routemanager.cpp \
        operationssetupxml.cpp \
        route.cpp \
        trainstablemodel.cpp \
        trainstableframe.cpp \
        trainmanager.cpp \
        trainmanagerxml.cpp \
        train.cpp \
        cartypes.cpp \
        enginetypes.cpp \
        routelocation.cpp \
        location.cpp \
        track.cpp \
        schedulemanager.cpp \
        trainschedulemanager.cpp \
        locationmanager.cpp \
        carowners.cpp \
        carcolors.cpp \
        carroads.cpp \
        rollingstock.cpp \
        engine.cpp \
        rollingstockmanager.cpp \
        enginemodels.cpp \
        enginemanager.cpp \
        enginestablemodel.cpp \
        rollingstockgroup.cpp \
        consist.cpp \
        pool.cpp \
        traincommon.cpp \
        rollingstockattribute.cpp \
        locationmanagerxml.cpp \
        enginemanagerxml.cpp \
        enginestableaction.cpp \
        enginestableframe.cpp \
        operationsframe.cpp \
        operationspanel.cpp \
        engineeditframe.cpp \
        engineattributeeditframe.cpp \
        carmanager.cpp \
        carmanagerxml.cpp \
        car.cpp \
        kernel.cpp \
        operationssetupaction.cpp \
        operationssetupframe.cpp \
        operationssetuppanel.cpp \
        operationspreferencespanel.cpp \
        autobackup.cpp \
        backupbase.cpp \
        control.cpp \
        backupdialog.cpp \
        defaultbackup.cpp \
        restoredialog.cpp \
        backupset.cpp \
        operationsmanager.cpp \
        carstableaction.cpp \
        carstableframe.cpp \
        carstablemodel.cpp \
        carloads.cpp \
        carload.cpp \
        careditframe.cpp \
        carattributeeditframe.cpp \
        carattributeaction.cpp \
        cardeleteattributeaction.cpp \
        carlengths.cpp \
        carrostermenu.cpp \
        showcheckboxescarstableaction.cpp \
        resetcheckboxescarstableaction.cpp \
        carsetframe.cpp \
        rollingstocksetframe.cpp \
        enginelengths.cpp \
        enginesetframe.cpp \
        locationstableaction.cpp \
        locationstableframe.cpp \
        locationstablemodel.cpp \
        locationeditframe.cpp \
        tracktablemodel.cpp \
        yardtablemodel.cpp \
        spurtablemodel.cpp \
        interchangetablemodel.cpp \
        stagingtablemodel.cpp \
        editcartypeaction.cpp \
        trackeditframe.cpp \
        yardeditframe.cpp \
        spureditframe.cpp \
        interchangeeditframe.cpp \
        stagingeditframe.cpp \
        trackeditcommentsaction.cpp \
        trackeditcommentsframe.cpp \
        modifylocationsaction.cpp \
        locationsbycartypeframe.cpp \
        changetrackstypeaction.cpp \
        changetracksframe.cpp \
        yardmasterframe.cpp \
        yardmasterpanel.cpp \
        commonconductoryardmasterpanel.cpp \
        trainstableaction.cpp \
        trainmanifestheadertext.cpp \
        carloadeditframe.cpp \
        autosave.cpp \
        routestableaction.cpp \
        routestablemodel.cpp \
        routestableframe.cpp \
        routeeditframe.cpp \
        routeedittablemodel.cpp \
        routecopyaction.cpp \
        settrainiconrouteaction.cpp \
        settrainiconrouteframe.cpp \
        settrainiconpositionaction.cpp \
        settrainiconpositionframe.cpp \
        enginerostermenu.cpp \
        importrosterengineaction.cpp \
        importrosterengines.cpp \
        importcarrosteraction.cpp \
        importcars.cpp \
        importrollingstock.cpp \
        locationtrackpair.cpp \
        scheduleeditframe.cpp \
        scheduletablemodel.cpp \
        schedulestableaction.cpp \
        schedulestableframe.cpp \
        schedulestablemodel.cpp \
        locationcopyframe.cpp \
        locationcopyaction.cpp \
        showcarsbylocationaction.cpp \
        showtrainsservinglocationaction.cpp \
        showtrainsservinglocationframe.cpp \
        trainschedule.cpp \
        traineditframe.cpp \
        trainconductorframe.cpp \
        trainconductorpanel.cpp \
        trainconductoraction.cpp \
        printtrainaction.cpp \
        trackroadeditframe.cpp \
        trackroadeditaction.cpp \
        trackloadeditframe.cpp \
        trackloadeditaction.cpp \
        optionframe.cpp \
        optionaction.cpp \
        trainmanifest.cpp \
        trainprintutilities.cpp \
        printtrainsaction.cpp \
        trainbuilder.cpp \
        carssetframe.cpp \
        carssetframeaction.cpp \
        trainsbycartypeframe.cpp \
        trainsbycartypeaction.cpp \
        optionpanel.cpp \
        printoptionframe.cpp \
        printoptionaction.cpp \
        printoptionpanel.cpp \
        trainswitchlisteditframe.cpp \
        trainswitchlists.cpp \
        loaddemoaction.cpp \
        restorefilesaction.cpp \
        backupfilesaction.cpp \
        resetaction.cpp \
        buildreportoptionpanel.cpp \
        buildreportoptionframe.cpp \
        buildreportoptionaction.cpp \
        router.cpp \
        managebackupsdialog.cpp \
        managebackupsaction.cpp \
        trackcopyframe.cpp \
        trackcopyaction.cpp \
        printrouteaction.cpp \
        printroutesaction.cpp \
        printcarloadsaction.cpp \
        enabledestinationaction.cpp \
        editmanifestheadertextaction.cpp \
        editmanifestheadertextframe.cpp \
        editmanifesttextframe.cpp \
        editswitchlisttextframe.cpp \
        editswitchlisttextaction.cpp \
        editmanifesttextaction.cpp \
        editswitchlisttextpanel.cpp \
        changetracktypeaction.cpp \
        changetrackframe.cpp \
        printlocationsaction.cpp \
        modifylocationscarloadsaction.cpp \
        locationsbycarloadframe.cpp \
        printmoreoptionaction.cpp \
        printmoreoptionframe.cpp \
        printmoreoptionpanel.cpp \
        carloadattributeaction.cpp \
        ignoreusedtrackaction.cpp \
        ignoreusedtrackframe.cpp \
        trackdestinationeditaction.cpp \
        trackdestinationeditframe.cpp \
        pooltrackaction.cpp \
        pooltrackframe.cpp \
        printlocationsbycartypesaction.cpp \
        routecopyframe.cpp \
        schedulesbyloadaction.cpp \
        schedulesbyloadframe.cpp \
        scheduleresethitsaction.cpp \
        schedulesresethitsaction.cpp \
        schedulecopyframe.cpp \
        schedulecopyaction.cpp \
        scheduleoptionsaction.cpp \
        scheduleoptionsframe.cpp \
        printtrainmanifestaction.cpp \
        printtrainbuildreportaction.cpp \
        traineditbuildoptionsaction.cpp \
        traineditbuildoptionsframe.cpp \
        printtrainsbycartypesaction.cpp \
        printswitchlistaction.cpp \
        trainbycartypeframe.cpp \
        trainbycartypeaction.cpp \
        trainstablesetcolorframe.cpp \
        trainstablesetcoloraction.cpp \
        changedeparturetimesaction.cpp \
        changedeparturetimesframe.cpp \
        trainsscheduleaction.cpp \
        trainsscheduletableframe.cpp \
        trainsscheduletablemodel.cpp \
        traincopyaction.cpp \
        traincopyframe.cpp \
        trainsscheduleeditaction.cpp \
        trainsscheduleeditframe.cpp \
        alternatetrackaction.cpp \
        alternatetrackframe.cpp \
        showcarsintrainaction.cpp \
        showcarsintrainframe.cpp \
        locationtrackblockingorderaction.cpp \
        locationtrackblockingorderframe.cpp \
        locationtrackblockingordertablemodel.cpp \
        trainloadoptionsaction.cpp \
        trainloadoptionsframe.cpp \
        trainroadoptionsaction.cpp \
        trainmanifestoptionaction.cpp \
        trainroadoptionsframe.cpp \
        trainmanifestoptionframe.cpp \
        trainscriptaction.cpp \
        trainscriptframe.cpp \
        exportcarrosteraction.cpp \
        exportcars.cpp \
        printcarrosteraction.cpp \
        deletecarrosteraction.cpp \
        resetcarmovesaction.cpp \
        exporttrainrosteraction.cpp \
        exporttrains.cpp \
        abstractoperationsserver.cpp \
        activetrain.cpp \
        dispatcherframe.cpp \
        autoactivetrain.cpp \
        autotrainaction.cpp \
        dispatcheraction.cpp \
        allocationrequest.cpp \
        allocatedsection.cpp \
        autoturnouts.cpp \
        autoallocate.cpp \
        activatetrainframe.cpp \
        traininfofile.cpp \
        traininfo.cpp \
        allocationplan.cpp \
        autotrainsframe.cpp \
        traincsvmanifest.cpp \
        traincsvcommon.cpp \
        buildfailedexception.cpp \
        traincustommanifest.cpp \
        traincustomcommon.cpp \
        setupexcelprogramframeaction.cpp \
        setupexcelprogrammanifestframe.cpp \
        setupexcelprogramframe.cpp \
        optionsmenu.cpp \
        yardmasterbytrackpanel.cpp \
        yardmasterbytrackframe.cpp \
        yardmasterbytrackaction.cpp \
    optionsfile.cpp \
    timetable/timetableprintgraph.cpp \
    timetable/timetableaction.cpp \
    timetable/timetabledatamanager.cpp \
    timetable/timetableframe.cpp \
    timetable/timetablexml.cpp \
    timetable/layout.cpp \
    timetable/station.cpp \
    timetable/stop.cpp \
    timetable/traintype.cpp \
    timetable/segment.cpp \
    timetable/tttrain.cpp \
    timetable/ttschedule.cpp \
    timetable/timetableimport.cpp \
    timetable/timetabledisplaygraph.cpp \
    timetable/timetablegraphcommon.cpp \
    timetable/exporttimetable.cpp \
    rollingstockattributeeditframe.cpp \
    taskallocaterelease.cpp

HEADERS += \
        operations.h \
        operations_global.h \
        operationsmenu.h \
        operationsxml.h \
        trainswitchlisttext.h \
        routemanagerxml.h \
        routemanager.h \
        operationssetupxml.h \
        route.h \
        trainmanager.h \
        trainmanagerxml.h \
        train.h \
        routelocation.h \
        location.h \
        track.h \
        locationmanagerxml.h \
        locationmanager.h \
        carowners.h \
        carroads.h \
        carloads.h \
        carload.h \
        carcolors.h \
        rollingstock.h \
        engine.h \
        rollingstockmanager.h \
        enginemanager.h \
        rollingstockgroup.h \
        consist.h \
        pool.h \
        traincommon.h \
        rollingstockattribute.h \
        enginemodels.h \
        enginemanagerxml.h \
        enginestableaction.h \
        enginestableframe.h \
        operationsframe.h \
        operationspanel.h \
        enginestablemodel.h \
        engineeditframe.h \
        engineattributeeditframe.h \
        carmanager.h \
        carmanagerxml.h \
        car.h \
        kernel.h \
        operationssetupaction.h \
        operationssetupframe.h \
        operationssetuppanel.h \
        operationspreferencespanel.h \
        autobackup.h \
        backupbase.h \
        cartypes.h \
        enginetypes.h \
        control.h \
        setup.cpp \
        setup.h \
        backupdialog.h \
        defaultbackup.h \
        restoredialog.h \
        backupset.h \
        operationsmanager.h \
        carstableaction.h \
        carstableframe.h \
        carstablemodel.h \
        careditframe.h \
        carattributeeditframe.h \
        carattributeaction.h \
        cardeleteattributeaction.h \
        carlengths.h \
        carrostermenu.h \
        showcheckboxescarstableaction.h \
        resetcheckboxescarstableaction.h \
        carsetframe.h \
        rollingstocksetframe.h \
        enginelengths.h \
        enginesetframe.h \
        locationstableaction.h \
        locationstableframe.h \
        locationstablemodel.h \
        locationeditframe.h \
        tracktablemodel.h \
        yardtablemodel.h \
        spurtablemodel.h \
        interchangetablemodel.h \
        stagingtablemodel.h \
        editcartypeaction.h \
        trackeditframe.h \
        yardeditframe.h \
        spureditframe.h \
        interchangeeditframe.h \
        stagingeditframe.h \
        trackeditcommentsaction.h \
        trackeditcommentsframe.h \
        modifylocationsaction.h \
        locationsbycartypeframe.h \
        changetrackstypeaction.h \
        changetracksframe.h \
        yardmasterframe.h \
        yardmasterpanel.h \
        commonconductoryardmasterpanel.h \
        trainstablemodel.h \
        trainstableframe.h \
        trainstableaction.h \
        trainmanifestheadertext.h \
        carloadeditframe.h \
        autosave.h \
        routestableaction.h \
        routestablemodel.h \
        routestableframe.h \
        routeeditframe.h \
        routeedittablemodel.h \
        routecopyaction.h \
        settrainiconrouteframe.h \
        settrainiconpositionaction.h \
        settrainiconpositionframe.h \
        enginerostermenu.h \
        importrosterengineaction.h \
        importrosterengines.h \
        importcarrosteraction.h \
        importcars.h \
        importrollingstock.h \
        schedulemanager.h \
        schedule.h \
        scheduleitem.h \
        locationtrackpair.h \
        scheduleeditframe.h \
        scheduletablemodel.h \
        schedulestableaction.h \
        schedulestableframe.h \
        schedulestablemodel.h \
        locationcopyframe.h \
        locationcopyaction.h \
        showcarsbylocationaction.h \
        showtrainsservinglocationaction.h \
        showtrainsservinglocationframe.h \
        trainschedule.h \
        traineditframe.h \
        trainconductorframe.h \
        trainconductorpanel.h \
        trainconductoraction.h \
        trainschedulemanager.h \
        printtrainaction.h \
        trackroadeditframe.h \
        trackroadeditaction.h \
        trackloadeditframe.h \
        trackloadeditaction.h \
        optionframe.h \
        optionaction.h \
        trainmanifest.h \
        trainmanifesttext.h \
        trainprintutilities.h \
        printtrainsaction.h \
        trainbuilder.h \
        carssetframe.h \
        carssetframeaction.h \
        trainsbycartypeframe.h \
        trainsbycartypeaction.h \
        optionpanel.h \
        printoptionframe.h \
        printoptionaction.h \
        printoptionpanel.h \
        trainswitchlisteditframe.h \
        trainswitchlists.h \
        loaddemoaction.h \
        restorefilesaction.h \
        backupfilesaction.h \
        resetaction.h \
        buildreportoptionpanel.h \
        buildreportoptionframe.h \
        buildreportoptionaction.h \
        router.h \
        managebackupsdialog.h \
        managebackupsaction.h \
        trackcopyframe.h \
        trackcopyaction.h \
        printrouteaction.h \
        printroutesaction.h \
        printcarloadsaction.h \
        enabledestinationaction.h \
        editmanifestheadertextaction.h \
        editmanifestheadertextframe.h \
        editmanifesttextframe.h \
        editswitchlisttextframe.h \
        editswitchlisttextaction.h \
        editmanifesttextaction.h \
        editswitchlisttextpanel.h \
        changetracktypeaction.h \
        changetrackframe.h \
        printlocationsaction.h \
        modifylocationscarloadsaction.h \
        locationsbycarloadframe.h \
        printmoreoptionaction.h \
        printmoreoptionframe.h \
        printmoreoptionpanel.h \
        carloadattributeaction.h \
        ignoreusedtrackaction.h \
        ignoreusedtrackframe.h \
        trackdestinationeditaction.h \
        trackdestinationeditframe.h \
        pooltrackaction.h \
        pooltrackframe.h \
        printlocationsbycartypesaction.h \
        routecopyframe.h \
        schedulesbyloadaction.h \
        schedulesbyloadframe.h \
        scheduleresethitsaction.h \
        schedulesresethitsaction.h \
        schedulecopyframe.h \
        schedulecopyaction.h \
        scheduleoptionsaction.h \
        scheduleoptionsframe.h \
        printtrainmanifestaction.h \
        printtrainbuildreportaction.h \
        traineditbuildoptionsaction.h \
        traineditbuildoptionsframe.h \
        printtrainsbycartypesaction.h \
        printswitchlistaction.h \
        trainbycartypeframe.h \
        trainbycartypeaction.h \
        trainstablesetcolorframe.h \
        trainstablesetcoloraction.h \
        changedeparturetimesaction.h \
        changedeparturetimesframe.h \
        trainsscheduleaction.h \
        trainsscheduletableframe.h \
        trainsscheduletablemodel.h \
        traincopyaction.h \
        traincopyframe.h \
        trainsscheduleeditaction.h \
        trainsscheduleeditframe.h \
        alternatetrackaction.h \
        alternatetrackframe.h \
        showcarsintrainaction.h \
        showcarsintrainframe.h \
        locationtrackblockingorderaction.h \
        locationtrackblockingorderframe.h \
        locationtrackblockingordertablemodel.h \
        trainloadoptionsaction.h \
        trainloadoptionsframe.h \
        trainroadoptionsaction.h \
        trainmanifestoptionaction.h \
        trainroadoptionsframe.h \
        trainmanifestoptionframe.h \
        exportcarrosteraction.h \
        exportcars.h \
        printcarrosteraction.h \
        deletecarrosteraction.h \
        resetcarmovesaction.h \
        exporttrainrosteraction.h \
        exporttrains.h \
        abstractoperationsserver.h \
        traincsvmanifest.h \
        traincsvcommon.h \
        buildfailedexception.h \
        traincustommanifest.h \
        traincustomcommon.h \
        setupexcelprogramframeaction.h \
        setupexcelprogrammanifestframe.h \
        setupexcelprogramframe.h \
        optionsmenu.h \
        yardmasterbytrackpanel.h \
        yardmasterbytrackframe.h \
        yardmasterbytrackaction.h \
        activetrain.h \
        dispatcherframe.h \
        autoactivetrain.h \
        autotrainaction.h \
        dispatcheraction.h \
        allocationrequest.h \
        allocatedsection.h \
        autoturnouts.h \
        autoallocate.h \
        activatetrainframe.h \
        traininfofile.h \
        traininfo.h \
        allocationplan.h \
        autotrainsframe.h \
    optionsfile.h \
    timetable/timetableprintgraph.h \
    timetable/timetableaction.h \
    timetable/timetabledatamanager.h \
    timetable/timetableframe.h \
    timetable/timetablexml.h \
    timetable/layout.h \
    timetable/station.h \
    timetable/stop.h \
    timetable/traintype.h \
    timetable/segment.h \
    timetable/ttschedule.h \
    timetable/tttrain.h \
    timetable/timetableimport.h \
    timetable/timetabledisplaygraph.h \
    timetable/timetablegraphcommon.h \
    timetable/exporttimetable.h \
    rollingstockattributeeditframe.h \
    taskallocaterelease.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

TRANSLATIONS += \
    languages/operations_de.ts \
    languages/operations_en.ts


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../appslib/release/ -lappslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../appslib/debug/ -lappslib
else:unix: LIBS += -L$$PWD/../appslib/ -lappslib

INCLUDEPATH += $$PWD/../appslib
DEPENDPATH += $$PWD/../appslib


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../JavaQt/release/ -lJavaQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../JavaQt/debug/ -lJavaQt
else:unix: LIBS += -L$$PWD/../JavaQt/ -lJavaQt

INCLUDEPATH += $$PWD/../JavaQt
DEPENDPATH += $$PWD/../JavaQt


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LayoutEditor/release/ -lLayoutEditor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LayoutEditor/debug/ -lLayoutEditor
else:unix: LIBS += -L$$PWD/../LayoutEditor/ -lLayoutEditor

INCLUDEPATH += $$PWD/../LayoutEditor $$PWD/../LayoutEditor/scripts
DEPENDPATH += $$PWD/../LayoutEditor $$PWD/../LayoutEditor/scripts


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPr3/release/ -lPr3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPr3/debug/ -lPr3
else:unix: LIBS += -L$$PWD/../libPr3/ -lPr3

INCLUDEPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/Signal \
 $$PWD/../Tables $$PWD/../libPr3/Throttle $$PWD/../libPr3/LocoIO $$PWD/../libPr3/loconet \
 $$PWD/../libPr3/rfid $$PWD/../libPr3/Json $$PWD/../libPr3/WiThrottle
DEPENDPATH += $$PWD/../libPr3 $$PWD/../libPr3/Roster $$PWD/../libPr3/Signal \
 $$PWD/../Tables $$PWD/../libPr3/Throttle $$PWD/../libPr3/LocoIO $$PWD/../libPr3/loconet \
 $$PWD/../libPr3/rfid $$PWD/../libPr3/Json $$PWD/../libPr3/WiThrottle


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libPref/release/ -lPref
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libPref/debug/ -lPref
else:unix: LIBS += -L$$PWD/../libPref/ -lPref

INCLUDEPATH += $$PWD/../libPref
DEPENDPATH += $$PWD/../libPref
