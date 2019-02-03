#ifndef CONDITIONAL_H
#define CONDITIONAL_H
#include "abstractnamedbean.h"
#include "propertychangelistener.h"
#include "libPr3_global.h"

//class QList;
class ConditionalAction;
class ConditionalVariable;
class LIBPR3SHARED_EXPORT Conditional : public AbstractNamedBean
{
    Q_OBJECT
public:
 /*public*/ enum Operator {
         NONE,
         AND,
         OR
 };
 explicit Conditional(QObject *parent = 0) :AbstractNamedBean(parent) {}
 Conditional(QString sysName, QString userName, QObject*parent = 0) : AbstractNamedBean(sysName, userName, parent) {}
    /**
     * A Conditional is layout control logic, consisting of a logical
     * expression and an action.
     * <P>
     * A Conditional does not exist on its own, but is part of a Logix.
     * The system name of each Conditional is set automatically when
     * the conditional is created.  It begins with the system name of
     * its parent Logix.  There is no Conditional Table.  Conditionals
     * are created, editted, and deleted via the Logix Table.
     * <P>
     * A Conditional has a "state", which changes depending on whether its
     * logical expression calculates to TRUE or FALSE. The "state" may not
     * be changed by the user. It only changes in response to changes in
     * the "state variables" used in its logical expression.
     * <P>
     * Listeners may be set to monitor a change in the state of a
     * conditional.
     *
     * <hr>
     * This file is part of JMRI.
     * <P>
     * JMRI is free software; you can redistribute it and/or modify it under
     * the terms of version 2 of the GNU General Public License as published
     * by the Free Software Foundation. See the "COPYING" file for a copy
     * of this license.
     * <P>
     * JMRI is distributed in the hope that it will be useful, but WITHOUT
     * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
     * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
     * for more details.
     * <P>
     * @author			Dave Duchamp Copyright (C) 2007, 2008
     * @author			Pete Cressman Copyright (C) 2009, 2010, 2011
     * @author                      Matthew Harris copyright (c) 2009
     * @version			$Revision 1.0 $
     */

//    public interface Conditional extends NamedBean {


        // states
    enum STATES
    {
        _TRUE      = 0x01,
        _FALSE     = 0x02,
         UNKNOWN   = 0x04,
        _TEST      = -1
    };
        // logic operators used in antecedent
    enum OPERATORS
    {
     ALL_AND     = 0x01,
     ALL_OR      = 0x02,
     MIXED       = 0x03
    };
        // state variable definitions
    enum SVARIABLES
    {
     OPERATOR_AND = 1,
     OPERATOR_NOT = 2,
     OPERATOR_AND_NOT = 3,
     OPERATOR_NONE = 4,
     OPERATOR_OR = 5,
     OPERATOR_OR_NOT = 6
    };
        // state variable types
    enum SVTYPES
    {
     TYPE_NONE = 0,
     TYPE_SENSOR_ACTIVE = 1,
     TYPE_SENSOR_INACTIVE = 2,
     TYPE_TURNOUT_THROWN = 3,
     TYPE_TURNOUT_CLOSED = 4,
     TYPE_CONDITIONAL_TRUE = 5,
     TYPE_CONDITIONAL_FALSE = 6,
     TYPE_LIGHT_ON = 7,
     TYPE_LIGHT_OFF = 8,
     TYPE_MEMORY_EQUALS = 9,
     TYPE_FAST_CLOCK_RANGE = 10,
    // Note - within the TYPE_SIGNAL_HEAD definitions, all must be together,
    //		RED must be first, and HELD must be last
     TYPE_SIGNAL_HEAD_RED = 11,
     TYPE_SIGNAL_HEAD_YELLOW = 12,
     TYPE_SIGNAL_HEAD_GREEN = 13,
     TYPE_SIGNAL_HEAD_DARK = 14,
     TYPE_SIGNAL_HEAD_FLASHRED = 15,
     TYPE_SIGNAL_HEAD_FLASHYELLOW = 16,
     TYPE_SIGNAL_HEAD_FLASHGREEN = 17,
     TYPE_SIGNAL_HEAD_LIT = 18,
     TYPE_SIGNAL_HEAD_HELD = 19,
     TYPE_MEMORY_COMPARE = 20,
     TYPE_SIGNAL_HEAD_LUNAR = 21,
     TYPE_SIGNAL_HEAD_FLASHLUNAR = 22,
     TYPE_MEMORY_EQUALS_INSENSITIVE = 23,
     TYPE_MEMORY_COMPARE_INSENSITIVE = 24,
        // Warrant variables
     TYPE_ROUTE_FREE = 25,
     TYPE_ROUTE_OCCUPIED = 26,
     TYPE_ROUTE_ALLOCATED = 27,
     TYPE_ROUTE_SET = 28,
     TYPE_TRAIN_RUNNING = 29,
     TYPE_SIGNAL_MAST_ASPECT_EQUALS = 30,
     TYPE_SIGNAL_MAST_LIT = 31,
     TYPE_SIGNAL_MAST_HELD = 32,
     TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS = 33,
     TYPE_BLOCK_STATUS_EQUALS = 34,

        //Entry Exit Rules
     TYPE_ENTRYEXIT_ACTIVE = 35,
     TYPE_ENTRYEXIT_INACTIVE = 36
    };
        // action definitions
    enum ACTIONS
    {
     ACTION_OPTION_ON_CHANGE_TO_TRUE = 1,
     ACTION_OPTION_ON_CHANGE_TO_FALSE = 2,
     ACTION_OPTION_ON_CHANGE = 3,
     NUM_ACTION_OPTIONS = 3
    };
        // action types
    enum ACTIONTYPES
    {
     ACTION_NONE = 1,
     ACTION_SET_TURNOUT = 2,
        // allowed settings for turnout are Thrown and Closed (in data)
     ACTION_SET_SIGNAL_APPEARANCE = 3,
        // allowed settings for signal head are the seven Appearances (in data)
     ACTION_SET_SIGNAL_HELD = 4,
     ACTION_CLEAR_SIGNAL_HELD = 5,
     ACTION_SET_SIGNAL_DARK = 6,
     ACTION_SET_SIGNAL_LIT = 7,
     ACTION_TRIGGER_ROUTE = 8,
     ACTION_SET_SENSOR = 9,
        // allowed settings for sensor are active and inactive (in data)
     ACTION_DELAYED_SENSOR = 10,
        // allowed settings for timed sensor are active and inactive (in data)
        //   time in seconds before setting sensor should be in delay
     ACTION_SET_LIGHT = 11,
        // allowed settings for light are ON and OFF (in data)
     ACTION_SET_MEMORY = 12,
        // text to set into the memory variable should be in string
     ACTION_ENABLE_LOGIX = 13,
     ACTION_DISABLE_LOGIX = 14,
     ACTION_PLAY_SOUND = 15,
        // reference to sound should be in string
     ACTION_RUN_SCRIPT = 16,
        // reference to script should be in string
     ACTION_DELAYED_TURNOUT = 17,
        // allowed settings for timed turnout are Thrown and Closed (in data)
        //   time in seconds before setting turnout should be in delay
     ACTION_LOCK_TURNOUT = 18,
     ACTION_RESET_DELAYED_SENSOR = 19,
        // allowed settings for timed sensor are active and inactive (in data)
        //   time in seconds before setting sensor should be in delay
     ACTION_CANCEL_SENSOR_TIMERS = 20,
        // cancels all timers delaying setting of specified sensor
     ACTION_RESET_DELAYED_TURNOUT = 21,
        // allowed settings for timed sensor are active and inactive (in data)
        //   time in seconds before setting sensor should be in delay
     ACTION_CANCEL_TURNOUT_TIMERS = 22,
        // cancels all timers delaying setting of specified sensor
     ACTION_SET_FAST_CLOCK_TIME = 23,
        // sets the fast clock time to the time specified
     ACTION_START_FAST_CLOCK = 24,
        // starts the fast clock
     ACTION_STOP_FAST_CLOCK = 25,
        // stops the fast clock
     ACTION_COPY_MEMORY = 26,
        // copies value from memory variable (in name) to memory variable (in string)
     ACTION_SET_LIGHT_INTENSITY = 27,
     ACTION_SET_LIGHT_TRANSITION_TIME = 28,
        // control the specified audio object
     ACTION_CONTROL_AUDIO = 29,
        // execute a jython command
     ACTION_JYTHON_COMMAND = 30,
        // Warrant actions
     ACTION_ALLOCATE_WARRANT_ROUTE = 31,
     ACTION_DEALLOCATE_WARRANT_ROUTE = 32,
     ACTION_SET_ROUTE_TURNOUTS = 33,
     ACTION_AUTO_RUN_WARRANT = 34,
     ACTION_CONTROL_TRAIN = 35,
     ACTION_SET_TRAIN_ID = 36,
     ACTION_SET_SIGNALMAST_ASPECT = 37,
     ACTION_THROTTLE_FACTOR = 38,
     ACTION_SET_SIGNALMAST_HELD = 39,
     ACTION_CLEAR_SIGNALMAST_HELD = 40,
     ACTION_SET_SIGNALMAST_DARK = 41,
     ACTION_SET_SIGNALMAST_LIT = 42,
     ACTION_SET_BLOCK_ERROR = 43,
     ACTION_CLEAR_BLOCK_ERROR = 44,
     ACTION_DEALLOCATE_BLOCK = 45,
     ACTION_SET_BLOCK_OUT_OF_SERVICE = 46,
     ACTION_SET_BLOCK_IN_SERVICE = 47,
     ACTION_MANUAL_RUN_WARRANT = 48,
     ACTION_SET_TRAIN_NAME = 49,
     ACTION_SET_BLOCK_VALUE = 50,
     ACTION_SET_NXPAIR_ENABLED = 51,
     ACTION_SET_NXPAIR_DISABLED = 52,
     ACTION_SET_NXPAIR_SEGMENT = 53,
     NUM_ACTION_TYPES = 53
   };
    /**************************************************************************************/
    /* New Variable and Action type scheme for Logix UI
    * State Variables and actions are grouped according to type.  Variable and action
    * types share the following group categories:
    */
        // state variable and action items used by logix.
        // When a new type is added, insert at proper location and update 'LAST' numbers
    enum ITEM_TYPES
    {
     ITEM_TYPE_SENSOR    = 1,
     ITEM_TYPE_TURNOUT   = 2,
     ITEM_TYPE_LIGHT     = 3,
     ITEM_TYPE_SIGNALHEAD = 4,
     ITEM_TYPE_SIGNALMAST = 5,
     ITEM_TYPE_MEMORY    = 6,
     ITEM_TYPE_CONDITIONAL = 7,  // used only by ConditionalVariable
     ITEM_TYPE_LOGIX = 7,        // used only by ConditionalAction
     ITEM_TYPE_WARRANT  = 8,
     ITEM_TYPE_CLOCK    = 9,
     ITEM_TYPE_OBLOCK  = 10,
     ITEM_TYPE_ENTRYEXIT  = 11,
     ITEM_TYPE_LAST_STATE_VAR = 11,

     ITEM_TYPE_AUDIO = 12,
     ITEM_TYPE_SCRIPT= 13,
     ITEM_TYPE_OTHER = 14,
     ITEM_TYPE_LAST_ACTION = 14
    };

        /***************** ConditionalVariable Maps ********************************/
        // Map state variable types to their item type
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        //static const int TEST_TO_ITEM[];
    static QList<int> TEST_TO_ITEM ;

        // Map SignalHead comboBox items to SignalHead Conditional variable types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
    const static  QList<int> ITEM_TO_SIGNAL_HEAD_TEST; /*= {TYPE_NONE,
                                        TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS,
                                        TYPE_SIGNAL_HEAD_LIT,
                                        TYPE_SIGNAL_HEAD_HELD }*/

//         Map SignalMAst comboBox items to SignalMast Conditional variable types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ITEM_TO_SIGNAL_MAST_TEST;/*= {TYPE_NONE,
                                                TYPE_SIGNAL_MAST_ASPECT_EQUALS,
                                                TYPE_SIGNAL_MAST_LIT,
                                                TYPE_SIGNAL_MAST_HELD}*/;

        // Map Sensor state comboBox items to Sensor Conditional variable types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ITEM_TO_SENSOR_TEST; /*= {TYPE_SENSOR_ACTIVE, TYPE_SENSOR_INACTIVE}*/

        // Map Turnout state comboBox items to Turnout Conditional variable types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ITEM_TO_TURNOUT_TEST;/* = {TYPE_TURNOUT_THROWN, TYPE_TURNOUT_CLOSED}*/

        // Map Conditional state comboBox items to  Condition ConditionalVvariable types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ITEM_TO_CONDITIONAL_TEST;/*= {TYPE_CONDITIONAL_TRUE, TYPE_CONDITIONAL_FALSE}*/

        // Map Memory state comboBox items to Light ConditionalVariable types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ITEM_TO_LIGHT_TEST; /*= {TYPE_LIGHT_ON, TYPE_LIGHT_OFF}*/

        // Map Warrant state comboBox items to Warrant ConditionalVariable types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ITEM_TO_WARRANT_TEST; /*= {TYPE_ROUTE_FREE, TYPE_ROUTE_SET, TYPE_ROUTE_ALLOCATED,
                                                            TYPE_ROUTE_OCCUPIED, TYPE_TRAIN_RUNNING}*/

        // Map Memory Compare Type comboBox items to Memory ConditionalVariable types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ITEM_TO_MEMORY_TEST; /* = {TYPE_MEMORY_EQUALS, TYPE_MEMORY_EQUALS_INSENSITIVE,
                                                TYPE_MEMORY_COMPARE, TYPE_MEMORY_COMPARE_INSENSITIVE}*/

//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY")
//        const static  int[] ITEM_TO_OBLOCK_TEST = {TYPE_BLOCK_STATUS_EQUALS };

//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY")
       const static  QList<int> ITEM_TO_ENTRYEXIT_TEST;// = {TYPE_ENTRYEXIT_ACTIVE, TYPE_ENTRYEXIT_INACTIVE};

//        /***************** ConditionalAction Maps ********************************/
//        // Map action type to the item type
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ACTION_TO_ITEM; /*= {TYPE_NONE,
                                            TYPE_NONE,              // ACTION_NONE              1
                                            ITEM_TYPE_TURNOUT,      // ACTION_SET_TURNOUT       2
                                            ITEM_TYPE_SIGNALHEAD,   // ACTION_SET_SIGNAL_APPEARANCE
                                            ITEM_TYPE_SIGNALHEAD,   // ACTION_SET_SIGNAL_HELD   4
                                            ITEM_TYPE_SIGNALHEAD,   // ACTION_CLEAR_SIGNAL_HELD 5
                                            ITEM_TYPE_SIGNALHEAD,   // ACTION_SET_SIGNAL_DARK   6
                                            ITEM_TYPE_SIGNALHEAD,   // ACTION_SET_SIGNAL_LIT    7
                                            ITEM_TYPE_OTHER,        // ACTION_TRIGGER_ROUTE     8
                                            ITEM_TYPE_SENSOR,       // ACTION_SET_SENSOR        9
                                            ITEM_TYPE_SENSOR,       // ACTION_DELAYED_SENSOR    10
                                            ITEM_TYPE_LIGHT,        // ACTION_SET_LIGHT         11
                                            ITEM_TYPE_MEMORY,       // ACTION_SET_MEMORY        12
                                            ITEM_TYPE_LOGIX,        // ACTION_ENABLE_LOGIX      13
                                            ITEM_TYPE_LOGIX,        // ACTION_DISABLE_LOGIX     14
                                            ITEM_TYPE_AUDIO,        // ACTION_PLAY_SOUND        15
                                            ITEM_TYPE_SCRIPT,       // ACTION_RUN_SCRIPT        16
                                            ITEM_TYPE_TURNOUT,      // ACTION_DELAYED_TURNOUT   17
                                            ITEM_TYPE_TURNOUT,      // ACTION_LOCK_TURNOUT      18
                                            ITEM_TYPE_SENSOR,       // ACTION_RESET_DELAYED_SENSOR
                                            ITEM_TYPE_SENSOR,       // ACTION_CANCEL_SENSOR_TIMERS 20
                                            ITEM_TYPE_TURNOUT,      // ACTION_RESET_DELAYED_TURNOUT
                                            ITEM_TYPE_TURNOUT,      // ACTION_CANCEL_TURNOUT_TIMERS
                                            ITEM_TYPE_CLOCK,        // ACTION_SET_FAST_CLOCK_TIME 23
                                            ITEM_TYPE_CLOCK,        // ACTION_START_FAST_CLOCK  24
                                            ITEM_TYPE_CLOCK,        // ACTION_STOP_FAST_CLOCK   25
                                            ITEM_TYPE_MEMORY,       // ACTION_COPY_MEMORY       26
                                            ITEM_TYPE_LIGHT,        // ACTION_SET_LIGHT_INTENSITY 27
                                            ITEM_TYPE_LIGHT,        // ACTION_SET_LIGHT_TRANSITION_TIME
                                            ITEM_TYPE_AUDIO,        // ACTION_CONTROL_AUDIO     29
                                            ITEM_TYPE_SCRIPT,       // ACTION_JYTHON_COMMAND    30
                                            ITEM_TYPE_WARRANT,      // ACTION_ALLOCATE_WARRANT_ROUTE 31
                                            ITEM_TYPE_WARRANT,      // ACTION_DEALLOCATE_WARRANT_ROUTE
                                            ITEM_TYPE_WARRANT,      // ACTION_SET_ROUTE_TURNOUTS 33
                                            ITEM_TYPE_WARRANT,      // ACTION_AUTO_RUN_WARRANT       34
                                            ITEM_TYPE_WARRANT,      // ACTION_CONTROL_TRAIN     35
                                            ITEM_TYPE_WARRANT,      // ACTION_SET_TRAIN_ID      36
                                            ITEM_TYPE_SIGNALMAST,   // ACTION_SET_SIGNALMAST_ASPECT 37
                                            ITEM_TYPE_WARRANT,      // ACTION_THROTTLE_FACTOR   38
                                            ITEM_TYPE_SIGNALMAST,   // ACTION_SET_SIGNALMAST_HELD = 39;
                                            ITEM_TYPE_SIGNALMAST,   // ACTION_CLEAR_SIGNALMAST_HELD = 40
                                            ITEM_TYPE_SIGNALMAST,   // ACTION_SET_SIGNALMAST_DARK = 41
                                            ITEM_TYPE_SIGNALMAST,   // ACTION_SET_SIGNALMAST_LIT = 42
                                            ITEM_TYPE_OBLOCK,       // ACTION_ALLOCATE_BLOCK_PATH = 43;
                                            ITEM_TYPE_OBLOCK,       //  ACTION_SET_BLOCK_PATH_TURNOUTS = 44;
                                            ITEM_TYPE_OBLOCK,       //  ACTION_DEALLOCATE_BLOCK = 45;
                                            ITEM_TYPE_OBLOCK,       //  ACTION_SET_BLOCK_OUT_OF_SERVICE = 46;
                                            ITEM_TYPE_OBLOCK,       //  ACTION_SET_BLOCK_IN_SERVICE = 47;
                                            ITEM_TYPE_WARRANT,      // ACTION_MANUAL_RUN_WARRANT 48
                                            ITEM_TYPE_WARRANT       // ACTION_SET_TRAIN_NAME 49
                                     }*/

        // Map Sensor Type comboBox items to Sensor action types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ITEM_TO_SENSOR_ACTION; /* = {ACTION_SET_SENSOR, ACTION_DELAYED_SENSOR,
                                    ACTION_RESET_DELAYED_SENSOR, ACTION_CANCEL_SENSOR_TIMERS}*/

        // Map Turnout Type comboBox items to Turnout action types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ITEM_TO_TURNOUT_ACTION;/* = {ACTION_SET_TURNOUT, ACTION_DELAYED_TURNOUT,
                ACTION_LOCK_TURNOUT, ACTION_CANCEL_TURNOUT_TIMERS, ACTION_RESET_DELAYED_TURNOUT}*/

        // Map Memory Type comboBox items to Memory action types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ITEM_TO_MEMORY_ACTION; /*= {12,26}*/

        // Map Light Type comboBox items to Light action types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ITEM_TO_LIGHT_ACTION;/*= {ACTION_SET_LIGHT, ACTION_SET_LIGHT_INTENSITY,
                                 ACTION_SET_LIGHT_TRANSITION_TIME}*/

        // Map FastClock Type comboBox items to FastClock action types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ITEM_TO_CLOCK_ACTION; /* = {ACTION_SET_FAST_CLOCK_TIME,
                                    ACTION_START_FAST_CLOCK, ACTION_STOP_FAST_CLOCK}*/

        // Map Logix Type comboBox items to Logix action types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ITEM_TO_LOGIX_ACTION; /* = {ACTION_ENABLE_LOGIX, ACTION_DISABLE_LOGIX}*/

        // Map Warrant Type comboBox items to Warrant action types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static QList<int> ITEM_TO_WARRANT_ACTION; /*= {ACTION_ALLOCATE_WARRANT_ROUTE,
                    ACTION_DEALLOCATE_WARRANT_ROUTE, ACTION_SET_ROUTE_TURNOUTS, ACTION_AUTO_RUN_WARRANT,
                    ACTION_MANUAL_RUN_WARRANT, ACTION_CONTROL_TRAIN, ACTION_SET_TRAIN_ID,
                    ACTION_SET_TRAIN_NAME, ACTION_THROTTLE_FACTOR }*/

//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY")
        const static QList<int> ITEM_TO_OBLOCK_ACTION; /*= {ACTION_ALLOCATE_BLOCK_PATH,
                    ACTION_SET_BLOCK_PATH_TURNOUTS, ACTION_DEALLOCATE_BLOCK,
                    ACTION_SET_BLOCK_OUT_OF_SERVICE, ACTION_SET_BLOCK_IN_SERVICE }*/

//         Map Signal Head Type comboBox items to Signal Head action types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??/*
        const static  QList<int> ITEM_TO_SIGNAL_HEAD_ACTION; /*= {ACTION_SET_SIGNAL_APPEARANCE,
                    ACTION_SET_SIGNAL_HELD, ACTION_CLEAR_SIGNAL_HELD,
                    ACTION_SET_SIGNAL_DARK , ACTION_SET_SIGNAL_LIT }*/

        // Map Signal Mast Type comboBox items to Signal Mast action types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ITEM_TO_SIGNAL_MAST_ACTION; /* = {ACTION_SET_SIGNALMAST_ASPECT,
                    ACTION_SET_SIGNALMAST_HELD, ACTION_CLEAR_SIGNALMAST_HELD,
                    ACTION_SET_SIGNALMAST_DARK , ACTION_SET_SIGNALMAST_LIT}*/

        // Map Audio Type comboBox items to Audio action types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ITEM_TO_AUDIO_ACTION; /*= {ACTION_PLAY_SOUND, ACTION_CONTROL_AUDIO}*/

        // Map Script Type comboBox items to Script action types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
                                                                                // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
                                                                                // OF STATIC FINAL ELEMENTS??
        const static  QList<int> ITEM_TO_SCRIPT_ACTION; /*= {ACTION_RUN_SCRIPT, ACTION_JYTHON_COMMAND}*/

// Map EntryExit Type comboBox items to EntryExit action types
   //@SuppressFBWarnings(value = "MS_MUTABLE_ARRAY") // with existing code structure,
   // just have to accept these exposed
   // arrays. Someday...
   // WHAT IS EXPOSED IN A STATIC FINAL ARRAY
   // OF STATIC FINAL ELEMENTS??
   /*public*/ const static /*final*/ QList<int> ITEM_TO_ENTRYEXIT_ACTION;// = {ACTION_SET_NXPAIR_ENABLED,
//       ACTION_SET_NXPAIR_DISABLED, ACTION_SET_NXPAIR_SEGMENT};// Map Misc Type comboBox items to Misc action types
//        @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="MS_MUTABLE_ARRAY") // with existing code structure,
                                                                                    // just have to accept these exposed
                                                                                    // arrays. Someday...
        const static  QList<int> ITEM_TO_OTHER_ACTION; /* = {ACTION_TRIGGER_ROUTE}*/

        /**
        * set the logic type (all AND's all OR's or mixed AND's and OR's
        * set the antecedent expression - should be a well formed boolean
        * statement with parenthesis indicating the order of evaluation
        */
        virtual void setLogicType(int type, QString antecedent) = 0;

        /**
         * Get antecedent (boolean expression) of Conditional
         */
        virtual QString getAntecedentExpression() = 0;

        /**
         * Get type of operators in the antecedent statement
         */
        virtual int getLogicType() = 0;

        /**
         * @return true if action list is executed only when state changes,
         * false if action list is executed on every calculation of state
         */
        virtual  bool getTriggerOnChange() = 0;

        /**
         * Set policy for execution of action list
         * @param trigger true execute only on change of state
         */
        virtual  void setTriggerOnChange(bool trigger) = 0;

        /**
         * Set list of actions
         */
        virtual void setAction (QList <ConditionalAction*>* /*arrayList*/) {}

        /**
         * Make deep clone of actions
         */
        virtual  QList <ConditionalAction*>* getCopyOfActions () { return NULL;}

       /**
         * Set State Variables for this Conditional. Each state variable will
         * evaluate either True or False when this Conditional is calculated.
         *<P>
         * This method assumes that all information has been validated.
         */
        virtual void setStateVariables(QList <ConditionalVariable*>* arrayList) = 0;

        /**
         * Make deep clone of variables
         */
        virtual QList <ConditionalVariable*>* getCopyOfStateVariables () = 0;

        /**
         * Calculate this Conditional, triggering either or both actions if the user
         *   specified conditions are met, and the Logix is enabled.
         *  Sets the state of the conditional.
         *  Returns the calculated state of this Conditional.
         */
        virtual int calculate (bool, PropertyChangeEvent* evt) = 0;

       /**
        *  Check that an antecedent is well formed.  If not,
        * returns an error message.  Otherwise returns null.
        */
        virtual QString validateAntecedent(QString /*ant*/, QList <ConditionalVariable*> /*variableList*/) {return QString();}


        /**
         * Stop a sensor timer if one is actively delaying setting of the specified sensor
         */
        virtual void cancelSensorTimer (QString sname)= 0;

        /**
         * Stop a turnout timer if one is actively delaying setting of the specified turnout
         */
        virtual void cancelTurnoutTimer (QString sname) = 0;

        /**
         * State of the Conditional is returned.
         * @return state value
         */
        virtual int getState() = 0;

        /**
         * Request a call-back when the bound KnownState property changes.
         */
        virtual void addPropertyChangeListener(PropertyChangeListener* /*l*/) {}

        /**
         * Remove a request for a call-back when a bound property changes.
         */
        virtual void removePropertyChangeListener(PropertyChangeListener* /*l*/) {}

        /**
         * Remove references to and from this object, so that it can
         * eventually be garbage-collected.
         */
        virtual void dispose() {}  // remove _all_ connections!

signals:
    
public slots:
    
};

#endif // CONDITIONAL_H
