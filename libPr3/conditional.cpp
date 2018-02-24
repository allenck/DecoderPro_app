#include "conditional.h"

//Condtional::Condtional(QObject *parent) :
//    NamedBean(parent)
//{
//  TEST_TO_ITEM  = {TYPE_NONE,    // TYPE_NONE                0
//                     ITEM_TYPE_SENSOR,       // TYPE_SENSOR_ACTIVE       1
//                     ITEM_TYPE_SENSOR,       // TYPE_SENSOR_INACTIVE     2
//                     ITEM_TYPE_TURNOUT,      // TYPE_TURNOUT_THROWN      3
//                     ITEM_TYPE_TURNOUT,      // TYPE_TURNOUT_ClOSED      4
//                     ITEM_TYPE_CONDITIONAL,  // TYPE_CONDITIONAL_TRUE    5
//                     ITEM_TYPE_CONDITIONAL,  // TYPE_CONDITIONAL_FALSE   6
//                     ITEM_TYPE_LIGHT,        // TYPE_LIGHT_ON            7
//                     ITEM_TYPE_LIGHT,        // TYPE_LIGHT_OFF           8
//                     ITEM_TYPE_MEMORY,       // TYPE_MEMORY_EQUALS       9
//                     ITEM_TYPE_CLOCK,        // TYPE_FAST_CLOCK_RANGE    10
//                     ITEM_TYPE_SIGNALHEAD,   // TYPE_SIGNAL_HEAD_RED     11
//                     ITEM_TYPE_SIGNALHEAD,   // TYPE_SIGNAL_HEAD_YELLOW  12
//                     ITEM_TYPE_SIGNALHEAD,   // TYPE_SIGNAL_HEAD_GREEN   13
//                     ITEM_TYPE_SIGNALHEAD,   // TYPE_SIGNAL_HEAD_DARK    14
//                     ITEM_TYPE_SIGNALHEAD,   // TYPE_SIGNAL_HEAD_FLASHRED 15
//                     ITEM_TYPE_SIGNALHEAD,   // TYPE_SIGNAL_HEAD_FLASHYELLOW
//                     ITEM_TYPE_SIGNALHEAD,   // TYPE_SIGNAL_HEAD_FLASHGREEN 17
//                     ITEM_TYPE_SIGNALHEAD,   // TYPE_SIGNAL_HEAD_LIT     18
//                     ITEM_TYPE_SIGNALHEAD,   // TYPE_SIGNAL_HEAD_HELD    19
//                     ITEM_TYPE_MEMORY,       // TYPE_MEMORY_COMPARE      20
//                     ITEM_TYPE_SIGNALHEAD,   // TYPE_SIGNAL_HEAD_LUNAR   21
//                     ITEM_TYPE_SIGNALHEAD,   // TYPE_SIGNAL_HEAD_FLASHLUNAR 22
//                     ITEM_TYPE_MEMORY,       // TYPE_MEMORY_EQUALS_INSENSITIVE 23
//                     ITEM_TYPE_MEMORY,       // TYPE_MEMORY_COMPARE_INSENSITIVE
//                     ITEM_TYPE_WARRANT,      // TYPE_ROUTE_FREE          25
//                     ITEM_TYPE_WARRANT,      // TYPE_ROUTE_OCCUPIED      26
//                     ITEM_TYPE_WARRANT,      // TYPE_ROUTE_ALLOCATED     27
//                     ITEM_TYPE_WARRANT,      // TYPE_ROUTE_SET           28
//                     ITEM_TYPE_WARRANT,      // TYPE_TRAIN_RUNNING       29
//                     ITEM_TYPE_SIGNALMAST,   // TYPE_SIGNAL_MAST_ASPECT_EQUALS 30
//                     ITEM_TYPE_SIGNALMAST,   // TYPE_SIGNAL_MAST_LIT = 31;
//                     ITEM_TYPE_SIGNALMAST,   // TYPE_SIGNAL_MAST_HELD = 32
//                     ITEM_TYPE_SIGNALHEAD,   // TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS = 33;
//                     ITEM_TYPE_OBLOCK,        // TYPE_BLOCK_STATUS_EQUALS = 34
//                     ITEM_TYPE_ENTRYEXIT,        // TYPE_ENTRYEXIT_ACTIVE = 35
//                     ITEM_TYPE_ENTRYEXIT        // TYPE_ENTRYEXIT_INACTIVE = 36
//                     };
//}
/*static*/ QList<int> Conditional::TEST_TO_ITEM  = QList<int> ()
        << TYPE_NONE    // TYPE_NONE                0
        << ITEM_TYPE_SENSOR       // TYPE_SENSOR_ACTIVE       1
        << ITEM_TYPE_SENSOR       // TYPE_SENSOR_INACTIVE     2
        << ITEM_TYPE_TURNOUT      // TYPE_TURNOUT_THROWN      3
        << ITEM_TYPE_TURNOUT      // TYPE_TURNOUT_ClOSED      4
        << ITEM_TYPE_CONDITIONAL  // TYPE_CONDITIONAL_TRUE    5
        << ITEM_TYPE_CONDITIONAL  // TYPE_CONDITIONAL_FALSE   6
        << ITEM_TYPE_LIGHT        // TYPE_LIGHT_ON            7
        << ITEM_TYPE_LIGHT        // TYPE_LIGHT_OFF           8
        << ITEM_TYPE_MEMORY       // TYPE_MEMORY_EQUALS       9
        << ITEM_TYPE_CLOCK        // TYPE_FAST_CLOCK_RANGE    10
        << ITEM_TYPE_SIGNALHEAD   // TYPE_SIGNAL_HEAD_RED     11
        << ITEM_TYPE_SIGNALHEAD   // TYPE_SIGNAL_HEAD_YELLOW  12
        << ITEM_TYPE_SIGNALHEAD   // TYPE_SIGNAL_HEAD_GREEN   13
        << ITEM_TYPE_SIGNALHEAD   // TYPE_SIGNAL_HEAD_DARK    14
        << ITEM_TYPE_SIGNALHEAD   // TYPE_SIGNAL_HEAD_FLASHRED 15
        << ITEM_TYPE_SIGNALHEAD   // TYPE_SIGNAL_HEAD_FLASHYELLOW
        << ITEM_TYPE_SIGNALHEAD   // TYPE_SIGNAL_HEAD_FLASHGREEN 17
        << ITEM_TYPE_SIGNALHEAD   // TYPE_SIGNAL_HEAD_LIT     18
        << ITEM_TYPE_SIGNALHEAD   // TYPE_SIGNAL_HEAD_HELD    19
        << ITEM_TYPE_MEMORY       // TYPE_MEMORY_COMPARE      20
        << ITEM_TYPE_SIGNALHEAD   // TYPE_SIGNAL_HEAD_LUNAR   21
        << ITEM_TYPE_SIGNALHEAD   // TYPE_SIGNAL_HEAD_FLASHLUNAR 22
        << ITEM_TYPE_MEMORY       // TYPE_MEMORY_EQUALS_INSENSITIVE 23
        << ITEM_TYPE_MEMORY       // TYPE_MEMORY_COMPARE_INSENSITIVE
        << ITEM_TYPE_WARRANT      // TYPE_ROUTE_FREE          25
        << ITEM_TYPE_WARRANT      // TYPE_ROUTE_OCCUPIED      26
        << ITEM_TYPE_WARRANT      // TYPE_ROUTE_ALLOCATED     27
        << ITEM_TYPE_WARRANT      // TYPE_ROUTE_SET           28
        << ITEM_TYPE_WARRANT      // TYPE_TRAIN_RUNNING       29
        << ITEM_TYPE_SIGNALMAST   // TYPE_SIGNAL_MAST_ASPECT_EQUALS 30
        << ITEM_TYPE_SIGNALMAST   // TYPE_SIGNAL_MAST_LIT = 31;
        << ITEM_TYPE_SIGNALMAST   // TYPE_SIGNAL_MAST_HELD = 32
        << ITEM_TYPE_SIGNALHEAD   // TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS = 33;
        << ITEM_TYPE_OBLOCK        // TYPE_BLOCK_STATUS_EQUALS = 34
        << ITEM_TYPE_ENTRYEXIT        // TYPE_ENTRYEXIT_ACTIVE = 35
        << ITEM_TYPE_ENTRYEXIT;        // TYPE_ENTRYEXIT_INACTIVE = 36
const /*static*/  QList<int> Conditional::ACTION_TO_ITEM = QList<int>() << TYPE_NONE <<
                                    TYPE_NONE <<             // ACTION_NONE              1
                                    ITEM_TYPE_TURNOUT <<      // ACTION_SET_TURNOUT       2
                                    ITEM_TYPE_SIGNALHEAD <<   // ACTION_SET_SIGNAL_APPEARANCE
                                    ITEM_TYPE_SIGNALHEAD <<   // ACTION_SET_SIGNAL_HELD   4
                                    ITEM_TYPE_SIGNALHEAD <<   // ACTION_CLEAR_SIGNAL_HELD 5
                                    ITEM_TYPE_SIGNALHEAD <<   // ACTION_SET_SIGNAL_DARK   6
                                    ITEM_TYPE_SIGNALHEAD <<   // ACTION_SET_SIGNAL_LIT    7
                                    ITEM_TYPE_OTHER <<        // ACTION_TRIGGER_ROUTE     8
                                    ITEM_TYPE_SENSOR <<       // ACTION_SET_SENSOR        9
                                    ITEM_TYPE_SENSOR <<       // ACTION_DELAYED_SENSOR    10
                                    ITEM_TYPE_LIGHT <<        // ACTION_SET_LIGHT         11
                                    ITEM_TYPE_MEMORY <<       // ACTION_SET_MEMORY        12
                                    ITEM_TYPE_LOGIX <<        // ACTION_ENABLE_LOGIX      13
                                    ITEM_TYPE_LOGIX <<        // ACTION_DISABLE_LOGIX     14
                                    ITEM_TYPE_AUDIO <<        // ACTION_PLAY_SOUND        15
                                    ITEM_TYPE_SCRIPT <<       // ACTION_RUN_SCRIPT        16
                                    ITEM_TYPE_TURNOUT <<      // ACTION_DELAYED_TURNOUT   17
                                    ITEM_TYPE_TURNOUT <<      // ACTION_LOCK_TURNOUT      18
                                    ITEM_TYPE_SENSOR <<       // ACTION_RESET_DELAYED_SENSOR
                                    ITEM_TYPE_SENSOR <<       // ACTION_CANCEL_SENSOR_TIMERS 20
                                    ITEM_TYPE_TURNOUT <<      // ACTION_RESET_DELAYED_TURNOUT
                                    ITEM_TYPE_TURNOUT <<      // ACTION_CANCEL_TURNOUT_TIMERS
                                    ITEM_TYPE_CLOCK <<        // ACTION_SET_FAST_CLOCK_TIME 23
                                    ITEM_TYPE_CLOCK <<        // ACTION_START_FAST_CLOCK  24
                                    ITEM_TYPE_CLOCK <<        // ACTION_STOP_FAST_CLOCK   25
                                    ITEM_TYPE_MEMORY <<       // ACTION_COPY_MEMORY       26
                                    ITEM_TYPE_LIGHT <<        // ACTION_SET_LIGHT_INTENSITY 27
                                    ITEM_TYPE_LIGHT <<        // ACTION_SET_LIGHT_TRANSITION_TIME
                                    ITEM_TYPE_AUDIO <<        // ACTION_CONTROL_AUDIO     29
                                    ITEM_TYPE_SCRIPT <<       // ACTION_JYTHON_COMMAND    30
                                    ITEM_TYPE_WARRANT <<      // ACTION_ALLOCATE_WARRANT_ROUTE 31
                                    ITEM_TYPE_WARRANT <<      // ACTION_DEALLOCATE_WARRANT_ROUTE
                                    ITEM_TYPE_WARRANT <<      // ACTION_SET_ROUTE_TURNOUTS 33
                                    ITEM_TYPE_WARRANT <<      // ACTION_AUTO_RUN_WARRANT       34
                                    ITEM_TYPE_WARRANT <<      // ACTION_CONTROL_TRAIN     35
                                    ITEM_TYPE_WARRANT <<      // ACTION_SET_TRAIN_ID      36
                                    ITEM_TYPE_SIGNALMAST <<   // ACTION_SET_SIGNALMAST_ASPECT 37
                                    ITEM_TYPE_WARRANT <<      // ACTION_THROTTLE_FACTOR   38
                                    ITEM_TYPE_SIGNALMAST <<   // ACTION_SET_SIGNALMAST_HELD = 39;
                                    ITEM_TYPE_SIGNALMAST <<   // ACTION_CLEAR_SIGNALMAST_HELD = 40
                                    ITEM_TYPE_SIGNALMAST <<   // ACTION_SET_SIGNALMAST_DARK = 41
                                    ITEM_TYPE_SIGNALMAST <<   // ACTION_SET_SIGNALMAST_LIT = 42
                                    ITEM_TYPE_OBLOCK <<       // ACTION_ALLOCATE_BLOCK_PATH = 43;
                                    ITEM_TYPE_OBLOCK <<       //  ACTION_SET_BLOCK_PATH_TURNOUTS = 44;
                                    ITEM_TYPE_OBLOCK <<       //  ACTION_DEALLOCATE_BLOCK = 45;
                                    ITEM_TYPE_OBLOCK <<       //  ACTION_SET_BLOCK_OUT_OF_SERVICE = 46;
                                    ITEM_TYPE_OBLOCK <<       //  ACTION_SET_BLOCK_IN_SERVICE = 47;
                                    ITEM_TYPE_WARRANT <<      // ACTION_MANUAL_RUN_WARRANT 48
                                    ITEM_TYPE_WARRANT;       // ACTION_SET_TRAIN_NAME 49
const /*static*/  QList<int> Conditional::ITEM_TO_MEMORY_ACTION =QList<int>() <<12 <<26;
const /*static*/  QList<int> Conditional::ITEM_TO_LIGHT_ACTION = QList<int>() <<Conditional::ACTION_SET_LIGHT << Conditional::ACTION_SET_LIGHT_INTENSITY <<
                         Conditional::ACTION_SET_LIGHT_TRANSITION_TIME;
const /*static*/  QList<int> Conditional::ITEM_TO_TURNOUT_ACTION=QList<int>() << Conditional::ACTION_SET_TURNOUT <<  Conditional::ACTION_DELAYED_TURNOUT <<
        Conditional::ACTION_LOCK_TURNOUT << Conditional::ACTION_CANCEL_TURNOUT_TIMERS << Conditional::ACTION_RESET_DELAYED_TURNOUT;
const /*static*/ QList<int> Conditional::ITEM_TO_WARRANT_ACTION=QList<int>() << Conditional::ACTION_ALLOCATE_WARRANT_ROUTE <<
            Conditional::ACTION_DEALLOCATE_WARRANT_ROUTE <<  Conditional::ACTION_SET_ROUTE_TURNOUTS << Conditional::ACTION_AUTO_RUN_WARRANT <<
            Conditional::ACTION_MANUAL_RUN_WARRANT << Conditional::ACTION_CONTROL_TRAIN << Conditional::ACTION_SET_TRAIN_ID <<
            Conditional::ACTION_SET_TRAIN_NAME << Conditional::ACTION_THROTTLE_FACTOR;
const /*static*/  QList<int> Conditional::ITEM_TO_SENSOR_ACTION=QList<int>() <<Conditional:: ACTION_SET_SENSOR << Conditional::ACTION_DELAYED_SENSOR <<
                            Conditional::ACTION_RESET_DELAYED_SENSOR << Conditional::ACTION_CANCEL_SENSOR_TIMERS;
const /*static*/  QList<int> Conditional::ITEM_TO_SIGNAL_HEAD_ACTION=QList<int>() << Conditional::ACTION_SET_SIGNAL_APPEARANCE <<
            Conditional::ACTION_SET_SIGNAL_HELD <<  Conditional::ACTION_CLEAR_SIGNAL_HELD <<
            Conditional::ACTION_SET_SIGNAL_DARK << Conditional::ACTION_SET_SIGNAL_LIT;
const /*static*/  QList<int> Conditional::ITEM_TO_SIGNAL_MAST_ACTION=QList<int>() << Conditional::ACTION_SET_SIGNALMAST_ASPECT <<
            Conditional::ACTION_SET_SIGNALMAST_HELD<< Conditional::ACTION_CLEAR_SIGNALMAST_HELD <<
            Conditional::ACTION_SET_SIGNALMAST_DARK << Conditional::ACTION_SET_SIGNALMAST_LIT;
const /*static*/  QList<int> Conditional::ITEM_TO_MEMORY_TEST=QList<int>() << Conditional::TYPE_MEMORY_EQUALS<< Conditional::TYPE_MEMORY_EQUALS_INSENSITIVE <<
                                        Conditional::TYPE_MEMORY_COMPARE << Conditional::TYPE_MEMORY_COMPARE_INSENSITIVE;
const /*static*/  QList<int> Conditional::ITEM_TO_LIGHT_TEST=QList<int>() <<Conditional::TYPE_LIGHT_ON << Conditional::TYPE_LIGHT_OFF;
const /*static*/  QList<int> Conditional::ITEM_TO_TURNOUT_TEST=QList<int>() <<Conditional::TYPE_TURNOUT_THROWN <<  Conditional::TYPE_TURNOUT_CLOSED;
const /*static*/  QList<int> Conditional::ITEM_TO_WARRANT_TEST=QList<int>() <<Conditional::TYPE_ROUTE_FREE << Conditional::TYPE_ROUTE_SET << Conditional::TYPE_ROUTE_ALLOCATED <<
                                                    Conditional::TYPE_ROUTE_OCCUPIED << Conditional::TYPE_TRAIN_RUNNING;
const /*static*/  QList<int> Conditional::ITEM_TO_CONDITIONAL_TEST=QList<int>() <<Conditional::TYPE_CONDITIONAL_TRUE << Conditional::TYPE_CONDITIONAL_FALSE;
const /*static*/  QList<int> Conditional::ITEM_TO_SENSOR_TEST=QList<int>() << Conditional::TYPE_SENSOR_ACTIVE<< Conditional::TYPE_SENSOR_INACTIVE;
const /*static*/  QList<int> Conditional::ITEM_TO_SIGNAL_HEAD_TEST=QList<int>() <<Conditional::TYPE_NONE<<
                                    Conditional::TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS<<
                                    Conditional::TYPE_SIGNAL_HEAD_LIT<<
                                    Conditional::TYPE_SIGNAL_HEAD_HELD;
const /*static*/  QList<int> Conditional::ITEM_TO_SIGNAL_MAST_TEST=QList<int>() <<Conditional::TYPE_NONE<<
                                        Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS <<
                                        Conditional::TYPE_SIGNAL_MAST_HELD;
const /*static*/  QList<int> Conditional::ITEM_TO_ENTRYEXIT_TEST=QList<int>() << Conditional::TYPE_ENTRYEXIT_ACTIVE << Conditional::TYPE_ENTRYEXIT_INACTIVE;
const /*static*/ QList<int> Conditional::ITEM_TO_OBLOCK_ACTION=QList<int>() << Conditional::ACTION_DEALLOCATE_BLOCK << Conditional::ACTION_SET_BLOCK_VALUE << Conditional::ACTION_SET_BLOCK_ERROR << Conditional::ACTION_CLEAR_BLOCK_ERROR << Conditional::ACTION_SET_BLOCK_OUT_OF_SERVICE <<  Conditional::ACTION_SET_BLOCK_IN_SERVICE;
 const /*static*/  QList<int> Conditional::ITEM_TO_LOGIX_ACTION=QList<int>() <<Conditional::ACTION_ENABLE_LOGIX << Conditional::ACTION_DISABLE_LOGIX;
 const /*static*/  QList<int> Conditional::ITEM_TO_SCRIPT_ACTION=QList<int>() <<Conditional::ACTION_RUN_SCRIPT << Conditional::ACTION_JYTHON_COMMAND;
 const /*static*/ /*final*/ QList<int> Conditional::ITEM_TO_ENTRYEXIT_ACTION=QList<int>()<<
 Conditional::ACTION_SET_NXPAIR_ENABLED <<
 Conditional::ACTION_SET_NXPAIR_DISABLED<< Conditional::ACTION_SET_NXPAIR_SEGMENT;
 const /*static*/  QList<int> Conditional::ITEM_TO_AUDIO_ACTION=QList<int>() <<Conditional::ACTION_PLAY_SOUND << Conditional::ACTION_CONTROL_AUDIO;
 const /*static*/  QList<int> Conditional::ITEM_TO_OTHER_ACTION=QList<int>() <<Conditional::ACTION_TRIGGER_ROUTE;
 const /*static*/  QList<int> Conditional::ITEM_TO_CLOCK_ACTION=QList<int>() <<Conditional::ACTION_SET_FAST_CLOCK_TIME <<
                             Conditional::ACTION_START_FAST_CLOCK << Conditional::ACTION_STOP_FAST_CLOCK;
