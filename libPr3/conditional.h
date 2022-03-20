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
  // items
public:
  /*public*/ class Operator {
   public:
  enum TYPE{ NONE, AND, OR };

  // This method is used by DefaultConditionalManagerXml.store() for backward compatibility
  /*public*/static int getIntValue(TYPE t) {
      switch (t) {
          case NONE: return OPERATOR_NONE;
          case AND: return OPERATOR_AND;
          case OR: return OPERATOR_OR;
          default: throw new IllegalArgumentException(QString("operator %1 is unknown").arg(t));
      }
   }
  };
 /*public*/ /*enum*/ class AntecedentOperator {
//         ALL_AND(Conditional.ALL_AND, Bundle.getMessage("LogicAND")),
//         ALL_OR(Conditional.ALL_OR, Bundle.getMessage("LogicOR")),
//         MIXED(Conditional.MIXED, Bundle.getMessage("LogicMixed"));
 public:
  enum VALS
  {
   ALL_AND,
   ALL_OR,
   MIXED
  };
  AntecedentOperator(int val)
  {
   if(val < 0 || val >= values.count()) throw new IllegalArgumentException("ItemType is unknown");

   _value = val;
   _string = values.at(val);
  }
  static VALS fromInt(int i)
  {
   switch (i)
   {
   case 0: return ALL_AND;
   case 1: return ALL_OR;
   case 2: return MIXED;
   }
   throw new IllegalArgumentException("invalid AntecedentOperator");
  }

  private:
      /*private*/ /*final*/ int _value;
      /*private*/ /*final*/ QString _string;
  QStringList values = QStringList() << "AND" << "OR" << "Mixed";

      /*private*/ AntecedentOperator(int value, QString string) {
          _value = value;
          _string = string;
      }
 public:
      /*public*/ int getIntValue() {
          return _value;
      }

      /*public*/ static AntecedentOperator getOperatorFromIntValue(int value) {
//       if(value < 0 || value >= values.count()) throw new IllegalArgumentException("ItemType is unknown");
//          for (AntecedentOperator antecedentOperators : values()) {
//              if (antecedentOperators.getIntValue() == value) {
//                  return antecedentOperators;
//              }
           return AntecedentOperator(value);
       }


      //@Override
      /*public*/ QString toString() {
          return _string;
      }
  };
  // state variable definitions. Keep these since they are needed
  // for backward compatibility in DefaultConditionalManagerXml.
  // But they are not used elsewhere.
//  static /*final*/const int OPERATOR_AND = 1;
//  static /*final*/ const int OPERATOR_NONE = 4;
//  static /*final*/ const int OPERATOR_OR = 5;

  // state variable and action items used by logix.
     /*enum*/class ItemType {
//         NONE(TYPE_NONE, IsStateVar.IS_STATE_VAR, "ItemTypeNone"),        // There is no ITEM_TYPE_NONE so use TYPE_NONE instead
//         SENSOR(ITEM_TYPE_SENSOR, IsStateVar.IS_STATE_VAR, "ItemTypeSensor"),
//         TURNOUT(ITEM_TYPE_TURNOUT, IsStateVar.IS_STATE_VAR, "ItemTypeTurnout"),
//         LIGHT(ITEM_TYPE_LIGHT, IsStateVar.IS_STATE_VAR, "ItemTypeLight"),
//         SIGNALHEAD(ITEM_TYPE_SIGNALHEAD, IsStateVar.IS_STATE_VAR, "ItemTypeSignalHead"),
//         SIGNALMAST(ITEM_TYPE_SIGNALMAST, IsStateVar.IS_STATE_VAR, "ItemTypeSignalMast"),
//         MEMORY(ITEM_TYPE_MEMORY, IsStateVar.IS_STATE_VAR, "ItemTypeMemory"),
//         CONDITIONAL(ITEM_TYPE_CONDITIONAL, IsStateVar.IS_STATE_VAR, "ItemTypeConditional"),  // used only by ConditionalVariable
//         LOGIX(ITEM_TYPE_LOGIX, IsStateVar.IS_STATE_VAR, "ItemTypeLogix"),                    // used only by ConditionalAction
//         WARRANT(ITEM_TYPE_WARRANT, IsStateVar.IS_STATE_VAR, "ItemTypeWarrant"),
//         CLOCK(ITEM_TYPE_CLOCK, IsStateVar.IS_STATE_VAR, "ItemTypeClock"),
//         OBLOCK(ITEM_TYPE_OBLOCK, IsStateVar.IS_STATE_VAR, "ItemTypeOBlock"),
//         ENTRYEXIT(ITEM_TYPE_ENTRYEXIT, IsStateVar.IS_STATE_VAR, "ItemTypeEntryExit"),

//         AUDIO(ITEM_TYPE_AUDIO, IsStateVar.IS_NOT_STATE_VAR, "ItemTypeAudio"),
//         SCRIPT(ITEM_TYPE_SCRIPT, IsStateVar.IS_NOT_STATE_VAR, "ItemTypeScript"),
//         OTHER(ITEM_TYPE_OTHER, IsStateVar.IS_NOT_STATE_VAR, "ItemTypeOther");
   public:
    enum TYPE {
     NONE,      // There is no ITEM_TYPE_NONE so use TYPE_NONE instead
     SENSOR,
     TURNOUT,
     LIGHT,
     SIGNALHEAD,
     SIGNALMAST,
     MEMORY,
     CONDITIONAL,         // used only by ConditionalVariable
     LOGIX,               // used only by ConditionalAction
     WARRANT,
     CLOCK,
     OBLOCK,
     ENTRYEXIT,

     AUDIO,
     SCRIPT,
     OTHER
    };
    QList<TYPE> values = {
     NONE,      // There is no ITEM_TYPE_NONE so use TYPE_NONE instead
     SENSOR,
     TURNOUT,
     LIGHT,
     SIGNALHEAD,
     SIGNALMAST,
     MEMORY,
     CONDITIONAL,         // used only by ConditionalVariable
     LOGIX,               // used only by ConditionalAction
     WARRANT,
     CLOCK,
     OBLOCK,
     ENTRYEXIT,

     AUDIO,
     SCRIPT,
     OTHER
    };
 private:
    // This enum is only used within the outer enum ItemType.
//    /*private*/ enum IsStateVar {
//        IS_STATE_VAR,
//        IS_NOT_STATE_VAR
//    };
//     /*private*/ /*final*/ int _type;
//     /*private*/ IsStateVar _isStateVar;
//     /*private*/ /*final*/ QString _bundleKey;

     /*private*/ static /*final*/ QList<ItemType> stateVarList;
#if 0
//     //static
//     {
//         stateVarList = QList<ItemType>();

         for (ItemType::TYPE itemType : ItemType::values()) {
             if (itemType::_isStateVar == IsStateVar::IS_STATE_VAR) {
                 stateVarList.add(itemType);
             }
         }
//     }
#endif
//     /*private*/ ItemType(int type, IsStateVar isStateVar, QString bundleKey) {
//         _type = type;
//         _isStateVar = isStateVar;
//         _bundleKey = bundleKey;
//     }
public:
     /*public*/ static QList<ItemType> getStateVarList() {
         return stateVarList;
     }

     /*public*/static int getIntValue(TYPE _type) {
         return (int)_type;
     }

     /*public*/ ItemType::TYPE getOperatorFromIntValue(int itemTypeInt) {
//         for (ItemType::TYPE itemType : values) {
//             if (itemType->getIntValue() == itemTypeInt) {
//                 return itemType;
//             }
//         }

//         throw new IllegalArgumentException("ItemType is unknown");
       return (ItemType::TYPE)itemTypeInt;
     }

     //@Override
     /*public*/static QString toString(TYPE t) {
//         return Bundle.getMessage(_bundleKey);
      switch (t) {
      case NONE: return tr("None");     // There is no ITEM_TYPE_NONE so use TYPE_NONE instead
      case SENSOR: return tr("Sensor");
      case TURNOUT: return tr("Turnout");
      case LIGHT: return tr("Light");
      case SIGNALHEAD: return tr("Signal Head");
      case SIGNALMAST: return tr("Signal Mast");
      case MEMORY: return tr("Memory");
      case CONDITIONAL: return tr("Conditional");          // used only by ConditionalVariable
      case LOGIX: return tr("Logix");                // used only by ConditionalAction
      case WARRANT: return tr("Warrant");
      case CLOCK: return tr("Clock");
      case OBLOCK: return tr("OBlock");
      case ENTRYEXIT: return tr("EntryExit");

      case AUDIO: return tr("Audio");
      case SCRIPT: return tr("Script");
      case OTHER: return tr("Other");

      }
      throw IllegalArgumentException();
     }


 };

     // items
  /*enum*/class Type {
//        ERROR(TYPE_ERROR, ItemType.NONE, "", ""), // NOI18N
//        NONE(TYPE_NONE, ItemType.NONE, "", ""), // NOI18N
//        SENSOR_ACTIVE(TYPE_SENSOR_ACTIVE, ItemType.SENSOR, Bundle.getMessage("SensorStateActive"), rbx.getString("TypeSensorActive")), // NOI18N
//        SENSOR_INACTIVE(TYPE_SENSOR_INACTIVE, ItemType.SENSOR, Bundle.getMessage("SensorStateInactive"), rbx.getString("TypeSensorInactive")), // NOI18N
//        TURNOUT_THROWN(TYPE_TURNOUT_THROWN, ItemType.TURNOUT, Bundle.getMessage("TurnoutStateThrown"), rbx.getString("TypeTurnoutThrown")), // NOI18N
//        TURNOUT_CLOSED(TYPE_TURNOUT_CLOSED, ItemType.TURNOUT, Bundle.getMessage("TurnoutStateClosed"), rbx.getString("TypeTurnoutClosed")), // NOI18N
//        CONDITIONAL_TRUE(TYPE_CONDITIONAL_TRUE, ItemType.CONDITIONAL, Bundle.getMessage("True"), rbx.getString("TypeConditionalTrue")), // NOI18N
//        CONDITIONAL_FALSE(TYPE_CONDITIONAL_FALSE, ItemType.CONDITIONAL, Bundle.getMessage("False"), rbx.getString("TypeConditionalFalse")), // NOI18N
//        LIGHT_ON(TYPE_LIGHT_ON, ItemType.LIGHT, rbx.getString("LightOn"), rbx.getString("TypeLightOn")), // NOI18N
//        LIGHT_OFF(TYPE_LIGHT_OFF, ItemType.LIGHT, rbx.getString("LightOff"), rbx.getString("TypeLightOff")), // NOI18N
//        MEMORY_EQUALS(TYPE_MEMORY_EQUALS, ItemType.MEMORY, rbx.getString("StateMemoryEquals"), rbx.getString("TypeMemoryEquals")), // NOI18N
//        MEMORY_COMPARE(TYPE_MEMORY_COMPARE, ItemType.MEMORY, rbx.getString("StateMemoryCompare"), rbx.getString("TypeMemoryCompare")), // NOI18N
//        MEMORY_EQUALS_INSENSITIVE(TYPE_MEMORY_EQUALS_INSENSITIVE, ItemType.MEMORY, rbx.getString("StateMemoryEqualsInsensitive"), rbx.getString("TypeMemoryEqualsInsensitive")), // NOI18N
//        MEMORY_COMPARE_INSENSITIVE(TYPE_MEMORY_COMPARE_INSENSITIVE, ItemType.MEMORY, rbx.getString("StateMemoryCompareInsensitive"), rbx.getString("TypeMemoryCompareInsensitive")), // NOI18N
//        FAST_CLOCK_RANGE(TYPE_FAST_CLOCK_RANGE, ItemType.CLOCK, rbx.getString("TypeFastClockRange"), rbx.getString("TypeFastClockRange")), // NOI18N

//        // Note the set signalHeadAppearanceSet below which holds those SignalHead types that are appearances.
//        SIGNAL_HEAD_RED(TYPE_SIGNAL_HEAD_RED, ItemType.SIGNALHEAD, Bundle.getMessage("SignalHeadStateRed"), Bundle.getMessage("SignalHeadStateRed")), // NOI18N
//        SIGNAL_HEAD_YELLOW(TYPE_SIGNAL_HEAD_YELLOW, ItemType.SIGNALHEAD, Bundle.getMessage("SignalHeadStateYellow"), Bundle.getMessage("SignalHeadStateYellow")), // NOI18N
//        SIGNAL_HEAD_GREEN(TYPE_SIGNAL_HEAD_GREEN, ItemType.SIGNALHEAD, Bundle.getMessage("SignalHeadStateGreen"), Bundle.getMessage("SignalHeadStateGreen")), // NOI18N
//        SIGNAL_HEAD_DARK(TYPE_SIGNAL_HEAD_DARK, ItemType.SIGNALHEAD, Bundle.getMessage("SignalHeadStateDark"), Bundle.getMessage("SignalHeadStateDark")), // NOI18N
//        SIGNAL_HEAD_FLASHRED(TYPE_SIGNAL_HEAD_FLASHRED, ItemType.SIGNALHEAD, Bundle.getMessage("SignalHeadStateFlashingRed"), Bundle.getMessage("SignalHeadStateFlashingRed")), // NOI18N
//        SIGNAL_HEAD_FLASHYELLOW(TYPE_SIGNAL_HEAD_FLASHYELLOW, ItemType.SIGNALHEAD, Bundle.getMessage("SignalHeadStateFlashingYellow"), Bundle.getMessage("SignalHeadStateFlashingYellow")), // NOI18N
//        SIGNAL_HEAD_FLASHGREEN(TYPE_SIGNAL_HEAD_FLASHGREEN, ItemType.SIGNALHEAD, Bundle.getMessage("SignalHeadStateFlashingGreen"), Bundle.getMessage("SignalHeadStateFlashingGreen")), // NOI18N
//        SIGNAL_HEAD_LIT(TYPE_SIGNAL_HEAD_LIT, ItemType.SIGNALHEAD, Bundle.getMessage("SignalHeadStateLit"), Bundle.getMessage("SignalHeadStateLit")), // NOI18N
//        SIGNAL_HEAD_HELD(TYPE_SIGNAL_HEAD_HELD, ItemType.SIGNALHEAD, Bundle.getMessage("SignalHeadStateHeld"), Bundle.getMessage("SignalHeadStateHeld")), // NOI18N
//        SIGNAL_HEAD_LUNAR(TYPE_SIGNAL_HEAD_LUNAR, ItemType.SIGNALHEAD, Bundle.getMessage("SignalHeadStateLunar"), Bundle.getMessage("SignalHeadStateLunar")), // NOI18N
//        SIGNAL_HEAD_FLASHLUNAR(TYPE_SIGNAL_HEAD_FLASHLUNAR, ItemType.SIGNALHEAD, Bundle.getMessage("SignalHeadStateFlashingLunar"), Bundle.getMessage("SignalHeadStateFlashingLunar")), // NOI18N
//        // Warrant variables
//        ROUTE_FREE(TYPE_ROUTE_FREE, ItemType.WARRANT, rbx.getString("StateRouteFree"), rbx.getString("TypeWarrantRouteFree")), // NOI18N
//        ROUTE_OCCUPIED(TYPE_ROUTE_OCCUPIED, ItemType.WARRANT, rbx.getString("stateRouteOccupied"), rbx.getString("TypeWarrantRouteOccupied")), // NOI18N
//        ROUTE_ALLOCATED(TYPE_ROUTE_ALLOCATED, ItemType.WARRANT, rbx.getString("StateRouteReserved"), rbx.getString("TypeWarrantRouteAllocated")), // NOI18N
//        ROUTE_SET(TYPE_ROUTE_SET, ItemType.WARRANT, rbx.getString("StateRouteIsSet"), rbx.getString("TypeRouteIsSet")), // NOI18N
//        TRAIN_RUNNING(TYPE_TRAIN_RUNNING, ItemType.WARRANT, rbx.getString("StateTrainRunning"), rbx.getString("TypeTrainRunning")), // NOI18N
//        SIGNAL_MAST_ASPECT_EQUALS(TYPE_SIGNAL_MAST_ASPECT_EQUALS, ItemType.SIGNALMAST, rbx.getString("TypeSignalMastAspectEquals"), rbx.getString("TypeSignalMastAspectEquals")), // NOI18N
//        SIGNAL_MAST_LIT(TYPE_SIGNAL_MAST_LIT, ItemType.SIGNALMAST, Bundle.getMessage("SignalMastStateLit"), Bundle.getMessage("SignalMastStateLit")), // NOI18N
//        SIGNAL_MAST_HELD(TYPE_SIGNAL_MAST_HELD, ItemType.SIGNALMAST, Bundle.getMessage("SignalMastStateHeld"), Bundle.getMessage("SignalMastStateHeld")), // NOI18N
//        SIGNAL_HEAD_APPEARANCE_EQUALS(TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS, ItemType.SIGNALHEAD, rbx.getString("TypeSignalHeadAspectEquals"), rbx.getString("TypeSignalHeadAspectEquals")), // NOI18N
//        BLOCK_STATUS_EQUALS(TYPE_BLOCK_STATUS_EQUALS, ItemType.OBLOCK, "", ""), // NOI18N
//        //Entry Exit Rules
//        ENTRYEXIT_ACTIVE(TYPE_ENTRYEXIT_ACTIVE, ItemType.ENTRYEXIT, rbx.getString("TypeEntryExitActive"), rbx.getString("TypeEntryExitActive")), // NOI18N
//        ENTRYEXIT_INACTIVE(TYPE_ENTRYEXIT_INACTIVE, ItemType.ENTRYEXIT, rbx.getString("TypeEntryExitInactive"), rbx.getString("TypeEntryExitInactive")), // NOI18N
//        // OBlock
//        OBLOCK_UNOCCUPIED(TYPE_OBLOCK_UNOCCUPIED, ItemType.OBLOCK, rbxWarrant.getString("unoccupied"), rbxWarrant.getString("unoccupied")), // NOI18N
//        OBLOCK_OCCUPIED(TYPE_OBLOCK_OCCUPIED, ItemType.OBLOCK, rbxWarrant.getString("occupied"), rbxWarrant.getString("occupied")), // NOI18N
//        OBLOCK_ALLOCATED(TYPE_OBLOCK_ALLOCATED, ItemType.OBLOCK, rbxWarrant.getString("allocated"), rbxWarrant.getString("allocated")), // NOI18N
//        OBLOCK_RUNNING(TYPE_OBLOCK_RUNNING, ItemType.OBLOCK, rbxWarrant.getString("running"), rbxWarrant.getString("running")), // NOI18N
//        OBLOCK_OUT_OF_SERVICE(TYPE_OBLOCK_OUT_OF_SERVICE, ItemType.OBLOCK, rbxWarrant.getString("outOfService"), rbxWarrant.getString("outOfService")), // NOI18N
//        OBLOCK_DARK(TYPE_OBLOCK_DARK, ItemType.OBLOCK, rbxWarrant.getString("dark"), rbxWarrant.getString("dark")), // NOI18N
//        OBLOCK_POWER_ERROR(TYPE_OBLOCK_POWER_ERROR, ItemType.OBLOCK, rbxWarrant.getString("powerError"), rbxWarrant.getString("powerError")), // NOI18N
//        // This is used by ConditionalListEdit and ConditionalTreeEdit
//        XXXXXXX(TYPE_XXXXXXX, ItemType.NONE, "XXXXXXX", "XXXXXXX"); // NOI18N
   public:
      enum TYPE {
   ERROR,
   NONE,
   SENSOR_ACTIVE,
   SENSOR_INACTIVE,
   TURNOUT_THROWN,
   TURNOUT_CLOSED,
   CONDITIONAL_TRUE,
   CONDITIONAL_FALSE,
   LIGHT_ON,
   LIGHT_OFF,
   MEMORY_EQUALS,
   MEMORY_COMPARE,
   MEMORY_EQUALS_INSENSITIVE,
   MEMORY_COMPARE_INSENSITIVE,
   FAST_CLOCK_RANGE,

   // Note the set signalHeadAppearanceSet below which holds those SignalHead types that are appearances.
   SIGNAL_HEAD_RED,
   SIGNAL_HEAD_YELLOW,
   SIGNAL_HEAD_GREEN,
   SIGNAL_HEAD_DARK,
   SIGNAL_HEAD_FLASHRED,
   SIGNAL_HEAD_FLASHYELLOW,
   SIGNAL_HEAD_FLASHGREEN,
   SIGNAL_HEAD_LIT,
   SIGNAL_HEAD_HELD,
   SIGNAL_HEAD_LUNAR,
   SIGNAL_HEAD_FLASHLUNAR,
   // Warrant variables
   ROUTE_FREE,
   ROUTE_OCCUPIED,
   ROUTE_ALLOCATED,
   ROUTE_SET,
   TRAIN_RUNNING,
   SIGNAL_MAST_ASPECT_EQUALS,
   SIGNAL_MAST_LIT,
   SIGNAL_MAST_HELD,
   SIGNAL_HEAD_APPEARANCE_EQUALS,
   BLOCK_STATUS_EQUALS,
   //Entry Exit Rules
   ENTRYEXIT_ACTIVE,
   ENTRYEXIT_INACTIVE,
   // OBlock
   OBLOCK_UNOCCUPIED,
   OBLOCK_OCCUPIED,
   OBLOCK_ALLOCATED,
   OBLOCK_RUNNING,
   OBLOCK_OUT_OF_SERVICE,
   OBLOCK_DARK,
   OBLOCK_POWER_ERROR,
   // This is used by ConditionalListEdit and ConditionalTreeEdit
   XXXXXXX
  };
#if 0
      private /*final*/ int _item;
      private /*final*/ ItemType _itemType;
      private /*final*/ String _string;
      private /*final*/ String _testTypeString;

      private static /*final*/ List<Type> sensorItemsList;
      private static /*final*/ List<Type> turnoutItemsList;
      private static /*final*/ List<Type> conditionalItemsList;
      private static /*final*/ List<Type> lightItemsList;
      private static /*final*/ List<Type> warrantItemsList;
      private static /*final*/ List<Type> memoryItemsList;
      private static /*final*/ List<Type> entryExitItemsList;
      private static /*final*/ List<Type> signalHeadStateMachineItemsList;
      private static /*final*/ List<Type> signalMastItemsList;
      private static /*final*/ List<Type> oblockItemsList;

      private static /*final*/ Set<Type> signalHeadAppearanceSet;


      static
      {
          Type[] typeArray1 = {SENSOR_ACTIVE, SENSOR_INACTIVE};
          sensorItemsList = Collections.unmodifiableList(Arrays.asList(typeArray1));

          Type[] typeArray2 = {TURNOUT_THROWN, TURNOUT_CLOSED};
          turnoutItemsList = Collections.unmodifiableList(Arrays.asList(typeArray2));

          Type[] typeArray3 = {CONDITIONAL_TRUE, CONDITIONAL_FALSE};
          conditionalItemsList = Collections.unmodifiableList(Arrays.asList(typeArray3));

          Type[] typeArray4 = {LIGHT_ON, LIGHT_OFF};
          lightItemsList = Collections.unmodifiableList(Arrays.asList(typeArray4));

          Type[] typeArray5 = {ROUTE_FREE, ROUTE_SET, ROUTE_ALLOCATED, ROUTE_OCCUPIED, TRAIN_RUNNING};
          warrantItemsList = Collections.unmodifiableList(Arrays.asList(typeArray5));

          Type[] typeArray6 = {MEMORY_EQUALS, MEMORY_EQUALS_INSENSITIVE,
              MEMORY_COMPARE, MEMORY_COMPARE_INSENSITIVE};
          memoryItemsList = Collections.unmodifiableList(Arrays.asList(typeArray6));

          Type[] typeArray7 = {ENTRYEXIT_ACTIVE, ENTRYEXIT_INACTIVE};
          entryExitItemsList = Collections.unmodifiableList(Arrays.asList(typeArray7));

          Type[] typeArray8 = {NONE, SIGNAL_HEAD_APPEARANCE_EQUALS, SIGNAL_HEAD_LIT, SIGNAL_HEAD_HELD};
          signalHeadStateMachineItemsList = Collections.unmodifiableList(Arrays.asList(typeArray8));

          Type[] typeArray9 = {SIGNAL_HEAD_RED, SIGNAL_HEAD_YELLOW, SIGNAL_HEAD_GREEN,
              SIGNAL_HEAD_DARK, SIGNAL_HEAD_FLASHRED, SIGNAL_HEAD_FLASHYELLOW,
              SIGNAL_HEAD_FLASHGREEN, SIGNAL_HEAD_LUNAR, SIGNAL_HEAD_FLASHLUNAR,
          };
          signalHeadAppearanceSet = Collections.unmodifiableSet(new HashSet<>(Arrays.asList(typeArray9)));

          Type[] typeArray10 = {NONE, SIGNAL_MAST_ASPECT_EQUALS, SIGNAL_MAST_LIT, SIGNAL_MAST_HELD};
          signalMastItemsList = Collections.unmodifiableList(Arrays.asList(typeArray10));

          Type[] typeArray11 = {OBLOCK_UNOCCUPIED, OBLOCK_OCCUPIED, OBLOCK_ALLOCATED,
              OBLOCK_RUNNING, OBLOCK_OUT_OF_SERVICE, OBLOCK_DARK, OBLOCK_POWER_ERROR};
          oblockItemsList = Collections.unmodifiableList(Arrays.asList(typeArray11));
      }

      private Type(int state, ItemType itemType, String string, String testTypeString) {
          _item = state;
          _itemType = itemType;
          _string = string;
          _testTypeString = testTypeString;
      }
#endif
      public:
      /*public*/static ItemType::TYPE getItemType(Type::TYPE t) {
       switch ( t)
       {
       case ERROR: return ItemType::NONE;
       case NONE: return ItemType::NONE;
       case SENSOR_ACTIVE: return ItemType::SENSOR;
       case SENSOR_INACTIVE: return ItemType::SENSOR;
       case TURNOUT_THROWN: return ItemType::TURNOUT;
       case TURNOUT_CLOSED: return ItemType::TURNOUT;
       case CONDITIONAL_TRUE: return  ItemType::CONDITIONAL;
       case CONDITIONAL_FALSE: return  ItemType::CONDITIONAL;
       case LIGHT_ON: return ItemType::LIGHT;
       case LIGHT_OFF: return ItemType::LIGHT;
       case MEMORY_EQUALS: return ItemType::MEMORY;
       case MEMORY_COMPARE: return ItemType::MEMORY;
       case MEMORY_EQUALS_INSENSITIVE: return ItemType::MEMORY;
       case MEMORY_COMPARE_INSENSITIVE: return ItemType::MEMORY;
       case FAST_CLOCK_RANGE: return ItemType::CLOCK;
       case SIGNAL_HEAD_RED:
       case SIGNAL_HEAD_YELLOW:
       case SIGNAL_HEAD_GREEN:
       case SIGNAL_HEAD_DARK:
       case SIGNAL_HEAD_FLASHRED:
       case SIGNAL_HEAD_FLASHYELLOW:
       case SIGNAL_HEAD_FLASHGREEN:
       case SIGNAL_HEAD_LIT:
       case SIGNAL_HEAD_HELD:
       case SIGNAL_HEAD_LUNAR:
       case SIGNAL_HEAD_FLASHLUNAR:return ItemType::SIGNALHEAD;
       // Warrant variables
       case ROUTE_FREE:
       case ROUTE_OCCUPIED:
       case ROUTE_ALLOCATED:
       case ROUTE_SET:
       case TRAIN_RUNNING: return ItemType::WARRANT;
       case SIGNAL_MAST_ASPECT_EQUALS:
       case SIGNAL_MAST_LIT:
       case SIGNAL_MAST_HELD:
       case SIGNAL_HEAD_APPEARANCE_EQUALS: return ItemType::SIGNALMAST;
       case BLOCK_STATUS_EQUALS: return ItemType::OBLOCK;
       //Entry Exit Rules
      case ENTRYEXIT_ACTIVE:
      case ENTRYEXIT_INACTIVE: return ItemType::ENTRYEXIT;
      // OBlock
      case OBLOCK_UNOCCUPIED:
      case OBLOCK_OCCUPIED:
      case OBLOCK_ALLOCATED:
      case OBLOCK_RUNNING:
      case OBLOCK_OUT_OF_SERVICE:
      case OBLOCK_DARK:
      case OBLOCK_POWER_ERROR: return ItemType::OBLOCK;
      // This is used by ConditionalListEdit and ConditionalTreeEdit
      case XXXXXXX: return ItemType::NONE;
      }
     }

//      /*public*/ int getIntValue() {
//          return _item;
//      }
#if 0
      public static List<Type> getSensorItems() {
          return sensorItemsList;
      }

      public static List<Type> getTurnoutItems() {
          return turnoutItemsList;
      }

      public static List<Type> getConditionalItems() {
          return conditionalItemsList;
      }

      public static List<Type> getLightItems() {
          return lightItemsList;
      }

      public static List<Type> getWarrantItems() {
          return warrantItemsList;
      }

      public static List<Type> getMemoryItems() {
          return memoryItemsList;
      }

      public static List<Type> getEntryExitItems() {
          return entryExitItemsList;
      }

      public static List<Type> getSignalHeadStateMachineItems() {
          return signalHeadStateMachineItemsList;
      }

      public static boolean isSignalHeadApperance(Type type) {
          return signalHeadAppearanceSet.contains(type);
      }

      public static List<Type> getSignalMastItems() {
          return signalMastItemsList;
      }

      public static List<Type> getOBlockItems() {
          return oblockItemsList;
      }

      public static int getIndexInList(List<Type> table, Type entry) {
          for (int i = 0; i < table.size(); i++) {
              if (entry == table.get(i)) {
                  return i;
              }
          }
          return -1;
      }

      public static Type getOperatorFromIntValue(int typeInt) {
          for (Type type : Type.values()) {
              if (type.getIntValue() == typeInt) {
                  return type;
              }
          }

          throw new IllegalArgumentException("Type is unknown");
      }
#endif
      // Some items uses Bundle.getString() and some items uses rbx.getString()
      // and therefore the items must call getString() in the call to the constructor.
      //@Override
      /*public*/ static QString toString(TYPE t) {
          switch(t)
          {
          case ERROR: return tr("");
          case NONE: return tr("");
          case SENSOR_ACTIVE: return tr("Active");
          case SENSOR_INACTIVE: return tr("Inactive");
          case TURNOUT_THROWN: return tr("Thrown");
          case TURNOUT_CLOSED: return tr("Closed");
          case CONDITIONAL_TRUE: return tr("True");
          case CONDITIONAL_FALSE: return tr("False");
          case LIGHT_ON: return tr("On");
          case LIGHT_OFF: return tr("Off");
          case MEMORY_EQUALS: return tr("(case sensitive) Value");
          case MEMORY_COMPARE: return tr("(case sensitive) Memory");
          case MEMORY_EQUALS_INSENSITIVE: return tr("(case insensitive) Value");
          case MEMORY_COMPARE_INSENSITIVE: return tr("");
          case FAST_CLOCK_RANGE: return tr("(case insensitive) Memory");

          // Note the set signalHeadAppearanceSet below which holds those SignalHead types that are appearances.
          case SIGNAL_HEAD_RED: return tr("Red");
          case SIGNAL_HEAD_YELLOW: return tr("Yellow");
          case SIGNAL_HEAD_GREEN: return tr("Green");
          case SIGNAL_HEAD_DARK: return tr("Dark");
          case SIGNAL_HEAD_FLASHRED: return tr("");
          case SIGNAL_HEAD_FLASHYELLOW: return tr("Flashing Yellow");
          case SIGNAL_HEAD_FLASHGREEN: return tr("Flashing Green");
          case SIGNAL_HEAD_LIT: return tr("Lit");
          case SIGNAL_HEAD_HELD: return tr("Held");
          case SIGNAL_HEAD_LUNAR: return tr("Lunar");
          case SIGNAL_HEAD_FLASHLUNAR: return tr("");
          // Warrant variables
          case ROUTE_FREE: return tr("Route Free");
          case ROUTE_OCCUPIED: return tr("Route Occupied");
          case ROUTE_ALLOCATED: return tr("RouteAllocated");
          case ROUTE_SET: return tr("RouteSet");
          case TRAIN_RUNNING: return tr("Train Running");
          case SIGNAL_MAST_ASPECT_EQUALS: return tr("Signal Mast Aspect equals");
          case SIGNAL_MAST_LIT: return tr("Signal Mast Lit");
          case SIGNAL_MAST_HELD: return tr("Signal Mast Held");
          case SIGNAL_HEAD_APPEARANCE_EQUALS: return tr("Signal Head Appearance equals");
          case BLOCK_STATUS_EQUALS: return tr("");
          //Entry Exit Rules
          case ENTRYEXIT_ACTIVE: return tr("Active");
          case ENTRYEXIT_INACTIVE: return tr("Inactive");
          // OBlock
          case OBLOCK_UNOCCUPIED: return tr("unoccupied");
          case OBLOCK_OCCUPIED: return tr("occupied");
          case OBLOCK_ALLOCATED: return tr("allocated");
          case OBLOCK_RUNNING: return tr("running");
          case OBLOCK_OUT_OF_SERVICE: return tr("outOfService");
          case OBLOCK_DARK: return tr("dark");
          case OBLOCK_POWER_ERROR: return tr("powerError");
          // This is used by ConditionalListEdit and ConditionalTreeEdit
          case XXXXXXX: return "XXXXXXX";
          }
      }

  /*public*/ static QString getItemTypeName(TYPE t) {
      switch(t)
      {
      case ERROR: return tr("");
      case NONE: return tr("");
      case SENSOR_ACTIVE:
      case SENSOR_INACTIVE: return ItemType::toString(ItemType::SENSOR);
      case TURNOUT_THROWN:
      case TURNOUT_CLOSED: return ItemType::toString(ItemType::TURNOUT);
      case CONDITIONAL_TRUE:
      case CONDITIONAL_FALSE: return ItemType::toString(ItemType::CONDITIONAL);
      case LIGHT_ON: return tr("On");
      case LIGHT_OFF: return tr("Off");
      case MEMORY_EQUALS: return tr("(case sensitive) Value");
      case MEMORY_COMPARE: return tr("(case sensitive) Memory");
      case MEMORY_EQUALS_INSENSITIVE: return tr("(case insensitive) Value");
      case MEMORY_COMPARE_INSENSITIVE: return tr("");
      case FAST_CLOCK_RANGE: return tr("(case insensitive) Memory");

      // Note the set signalHeadAppearanceSet below which holds those SignalHead types that are appearances.
      case SIGNAL_HEAD_RED: return tr("Red");
      case SIGNAL_HEAD_YELLOW: return tr("Yellow");
      case SIGNAL_HEAD_GREEN: return tr("Green");
      case SIGNAL_HEAD_DARK: return tr("Dark");
      case SIGNAL_HEAD_FLASHRED: return tr("");
      case SIGNAL_HEAD_FLASHYELLOW: return tr("Flashing Yellow");
      case SIGNAL_HEAD_FLASHGREEN: return tr("Flashing Green");
      case SIGNAL_HEAD_LIT: return tr("Lit");
      case SIGNAL_HEAD_HELD: return tr("Held");
      case SIGNAL_HEAD_LUNAR: return tr("Lunar");
      case SIGNAL_HEAD_FLASHLUNAR: return tr("");
      // Warrant variables
      case ROUTE_FREE: return tr("Route Free");
      case ROUTE_OCCUPIED: return tr("Route Occupied");
      case ROUTE_ALLOCATED: return tr("RouteAllocated");
      case ROUTE_SET: return tr("RouteSet");
      case TRAIN_RUNNING: return tr("Train Running");
      case SIGNAL_MAST_ASPECT_EQUALS: return tr("Signal Mast Aspect equals");
      case SIGNAL_MAST_LIT: return tr("Signal Mast Lit");
      case SIGNAL_MAST_HELD: return tr("Signal Mast Held");
      case SIGNAL_HEAD_APPEARANCE_EQUALS: return tr("Signal Head Appearance equals");
      case BLOCK_STATUS_EQUALS: return tr("");
      //Entry Exit Rules
      case ENTRYEXIT_ACTIVE: return tr("Active");
      case ENTRYEXIT_INACTIVE: return tr("Inactive");
      // OBlock
      case OBLOCK_UNOCCUPIED: return tr("unoccupied");
      case OBLOCK_OCCUPIED: return tr("occupied");
      case OBLOCK_ALLOCATED: return tr("allocated");
      case OBLOCK_RUNNING: return tr("running");
      case OBLOCK_OUT_OF_SERVICE: return tr("outOfService");
      case OBLOCK_DARK: return tr("dark");
      case OBLOCK_POWER_ERROR: return tr("powerError");
      // This is used by ConditionalListEdit and ConditionalTreeEdit
      case XXXXXXX: return "XXXXXXX";
      }
  }
      /*public*/ QString getTestTypeString(TYPE t) {
       switch(t)
       {
       case ERROR: return tr("");
       case NONE: return tr("");
       case SENSOR_ACTIVE: return tr("Sensor Active");
       case SENSOR_INACTIVE: return tr("Sensor Inactive");
       case TURNOUT_THROWN: return tr("Turnout Thrown");
       case TURNOUT_CLOSED: return tr("Turnout Closed");
       case CONDITIONAL_TRUE: return tr("Conditional True");
       case CONDITIONAL_FALSE: return tr("");
       case LIGHT_ON: return tr("Light On");
       case LIGHT_OFF: return tr("Light Off");
       case MEMORY_EQUALS: return tr("Memory Compare to Value (Case Sensitive)");
       case MEMORY_COMPARE: return tr("Memory Compare to Memory (Case Sensitive)");
       case MEMORY_EQUALS_INSENSITIVE: return tr("Memory Compare to Value (Case Insensitive)");
       case MEMORY_COMPARE_INSENSITIVE: return tr("Memory Compare to Memory (Case Insensitive)");
       case FAST_CLOCK_RANGE: return tr("Fast Clock Range");

       // Note the set signalHeadAppearanceSet below which holds those SignalHead types that are appearances.
       case SIGNAL_HEAD_RED: return tr("Red");
       case SIGNAL_HEAD_YELLOW: return tr("Yellow");
       case SIGNAL_HEAD_GREEN: return tr("Green");
       case SIGNAL_HEAD_DARK: return tr("Dark");
       case SIGNAL_HEAD_FLASHRED: return tr("Flashing Red");
       case SIGNAL_HEAD_FLASHYELLOW: return tr("Flashing Yellow");
       case SIGNAL_HEAD_FLASHGREEN: return tr("Flashing Green");
       case SIGNAL_HEAD_LIT: return tr("Lit");
       case SIGNAL_HEAD_HELD: return tr("Held");
       case SIGNAL_HEAD_LUNAR: return tr("Lunar");
       case SIGNAL_HEAD_FLASHLUNAR: return tr("FlasingLunar");
       // Warrant variables
       case ROUTE_FREE: return tr("");
       case ROUTE_OCCUPIED: return tr("");
       case ROUTE_ALLOCATED: return tr("");
       case ROUTE_SET: return tr("");
       case TRAIN_RUNNING: return tr("");
       case SIGNAL_MAST_ASPECT_EQUALS: return tr("");
       case SIGNAL_MAST_LIT: return tr("");
       case SIGNAL_MAST_HELD: return tr("");
       case SIGNAL_HEAD_APPEARANCE_EQUALS: return tr("");
       case BLOCK_STATUS_EQUALS: return tr("");
       //Entry Exit Rules
       case ENTRYEXIT_ACTIVE: return tr("Active");
       case ENTRYEXIT_INACTIVE: return tr("Inactive");
       // OBlock
       case OBLOCK_UNOCCUPIED: return tr("unoccupied");
       case OBLOCK_OCCUPIED: return tr("occupied");
       case OBLOCK_ALLOCATED: return tr("allocated");
       case OBLOCK_RUNNING: return tr("running");
       case OBLOCK_OUT_OF_SERVICE: return tr("outOfService");
       case OBLOCK_DARK: return tr("dark");
       case OBLOCK_POWER_ERROR: return tr("powerError");
       // This is used by ConditionalListEdit and ConditionalTreeEdit
       case XXXXXXX: return "XXXXXXX";
       }
      }

  };
/*enum*/class Action {
//      NONE(ACTION_NONE, ItemType.NONE, ""), // NOI18N
//      SET_TURNOUT(ACTION_SET_TURNOUT, ItemType.TURNOUT, rbx.getString("ActionSetTurnout")), // NOI18N
//      // allowed settings for turnout are Thrown and Closed (in data)
//      SET_SIGNAL_APPEARANCE(ACTION_SET_SIGNAL_APPEARANCE, ItemType.SIGNALHEAD, rbx.getString("ActionSetSignal")), // NOI18N
//      // allowed settings for signal head are the seven Appearances (in data)
//      SET_SIGNAL_HELD(ACTION_SET_SIGNAL_HELD, ItemType.SIGNALHEAD, rbx.getString("ActionSetSignalHeld")), // NOI18N
//      CLEAR_SIGNAL_HELD(ACTION_CLEAR_SIGNAL_HELD, ItemType.SIGNALHEAD, rbx.getString("ActionClearSignalHeld")), // NOI18N
//      SET_SIGNAL_DARK(ACTION_SET_SIGNAL_DARK, ItemType.SIGNALHEAD, rbx.getString("ActionSetSignalDark")), // NOI18N
//      SET_SIGNAL_LIT(ACTION_SET_SIGNAL_LIT, ItemType.SIGNALHEAD, rbx.getString("ActionSetSignalLit")), // NOI18N
//      TRIGGER_ROUTE(ACTION_TRIGGER_ROUTE, ItemType.OTHER, rbx.getString("ActionTriggerRoute")), // NOI18N
//      SET_SENSOR(ACTION_SET_SENSOR, ItemType.SENSOR, rbx.getString("ActionSetSensor")), // NOI18N
//      // allowed settings for sensor are active and inactive (in data)
//      DELAYED_SENSOR(ACTION_DELAYED_SENSOR, ItemType.SENSOR, rbx.getString("ActionDelayedSensor")), // NOI18N
//      // allowed settings for timed sensor are active and inactive (in data)
//      //   time in seconds before setting sensor should be in delay
//      SET_LIGHT(ACTION_SET_LIGHT, ItemType.LIGHT, rbx.getString("ActionSetLight")), // NOI18N
//      // allowed settings for light are ON and OFF (in data)
//      SET_MEMORY(ACTION_SET_MEMORY, ItemType.MEMORY, rbx.getString("ActionSetMemory")), // NOI18N
//      // text to set into the memory variable should be in string
//      ENABLE_LOGIX(ACTION_ENABLE_LOGIX, ItemType.LOGIX, rbx.getString("ActionEnableLogix")), // NOI18N
//      DISABLE_LOGIX(ACTION_DISABLE_LOGIX, ItemType.LOGIX, rbx.getString("ActionDisableLogix")), // NOI18N
//      PLAY_SOUND(ACTION_PLAY_SOUND, ItemType.AUDIO, rbx.getString("ActionPlaySound")), // NOI18N
//      // reference to sound should be in string
//      RUN_SCRIPT(ACTION_RUN_SCRIPT, ItemType.SCRIPT, rbx.getString("ActionRunScript")), // NOI18N
//      // reference to script should be in string
//      DELAYED_TURNOUT(ACTION_DELAYED_TURNOUT, ItemType.TURNOUT, rbx.getString("ActionDelayedTurnout")), // NOI18N
//      // allowed settings for timed turnout are Thrown and Closed (in data)
//      //   time in seconds before setting turnout should be in delay
//      LOCK_TURNOUT(ACTION_LOCK_TURNOUT, ItemType.TURNOUT, rbx.getString("ActionTurnoutLock")), // NOI18N
//      RESET_DELAYED_SENSOR(ACTION_RESET_DELAYED_SENSOR, ItemType.SENSOR, rbx.getString("ActionResetDelayedSensor")), // NOI18N
//      // allowed settings for timed sensor are active and inactive (in data)
//      //   time in seconds before setting sensor should be in delay
//      CANCEL_SENSOR_TIMERS(ACTION_CANCEL_SENSOR_TIMERS, ItemType.SENSOR, rbx.getString("ActionCancelSensorTimers")), // NOI18N
//      // cancels all timers delaying setting of specified sensor
//      RESET_DELAYED_TURNOUT(ACTION_RESET_DELAYED_TURNOUT, ItemType.TURNOUT, rbx.getString("ActionResetDelayedTurnout")), // NOI18N
//      // allowed settings for timed sensor are active and inactive (in data)
//      //   time in seconds before setting sensor should be in delay
//      CANCEL_TURNOUT_TIMERS(ACTION_CANCEL_TURNOUT_TIMERS, ItemType.TURNOUT, rbx.getString("ActionCancelTurnoutTimers")), // NOI18N
//      // cancels all timers delaying setting of specified sensor
//      SET_FAST_CLOCK_TIME(ACTION_SET_FAST_CLOCK_TIME, ItemType.CLOCK, rbx.getString("ActionSetFastClockTime")), // NOI18N
//      // sets the fast clock time to the time specified
//      START_FAST_CLOCK(ACTION_START_FAST_CLOCK, ItemType.CLOCK, rbx.getString("ActionStartFastClock")), // NOI18N
//      // starts the fast clock
//      STOP_FAST_CLOCK(ACTION_STOP_FAST_CLOCK, ItemType.CLOCK, rbx.getString("ActionStopFastClock")), // NOI18N
//      // stops the fast clock
//      COPY_MEMORY(ACTION_COPY_MEMORY, ItemType.MEMORY, rbx.getString("ActionCopyMemory")), // NOI18N
//      // copies value from memory variable (in name) to memory variable (in string)
//      SET_LIGHT_INTENSITY(ACTION_SET_LIGHT_INTENSITY, ItemType.LIGHT, rbx.getString("ActionSetLightIntensity")), // NOI18N
//      SET_LIGHT_TRANSITION_TIME(ACTION_SET_LIGHT_TRANSITION_TIME, ItemType.LIGHT, rbx.getString("ActionSetLightTransitionTime")), // NOI18N
//      // control the specified audio object
//      CONTROL_AUDIO(ACTION_CONTROL_AUDIO, ItemType.AUDIO, rbx.getString("ActionControlAudio")), // NOI18N
//      // execute a jython command
//      JYTHON_COMMAND(ACTION_JYTHON_COMMAND, ItemType.SCRIPT, rbx.getString("ActionJythonCommand")), // NOI18N
//      // Warrant actions
//      ALLOCATE_WARRANT_ROUTE(ACTION_ALLOCATE_WARRANT_ROUTE, ItemType.WARRANT, rbx.getString("ActionAllocateWarrant")), // NOI18N
//      DEALLOCATE_WARRANT_ROUTE(ACTION_DEALLOCATE_WARRANT_ROUTE, ItemType.WARRANT, rbx.getString("ActionDeallocateWarrant")), // NOI18N
//      SET_ROUTE_TURNOUTS(ACTION_SET_ROUTE_TURNOUTS, ItemType.WARRANT, rbx.getString("ActionSetWarrantTurnouts")), // NOI18N
//      AUTO_RUN_WARRANT(ACTION_AUTO_RUN_WARRANT, ItemType.WARRANT, rbx.getString("ActionAutoRunWarrant")), // NOI18N
//      MANUAL_RUN_WARRANT(ACTION_MANUAL_RUN_WARRANT, ItemType.WARRANT, rbx.getString("ActionManualRunWarrant")), // NOI18N
//      CONTROL_TRAIN(ACTION_CONTROL_TRAIN, ItemType.WARRANT, rbx.getString("ActionControlTrain")), // NOI18N
//      SET_TRAIN_ID(ACTION_SET_TRAIN_ID, ItemType.WARRANT, rbx.getString("ActionSetTrainId")), // NOI18N
//      SET_TRAIN_NAME(ACTION_SET_TRAIN_NAME, ItemType.WARRANT, rbx.getString("ActionSetTrainName")), // NOI18N
//      SET_SIGNALMAST_ASPECT(ACTION_SET_SIGNALMAST_ASPECT, ItemType.SIGNALMAST, rbx.getString("ActionSetSignalMastAspect")), // NOI18N
//      THROTTLE_FACTOR(ACTION_THROTTLE_FACTOR, ItemType.WARRANT, rbx.getString("ActionSetThrottleFactor")), // NOI18N
//      SET_SIGNALMAST_HELD(ACTION_SET_SIGNALMAST_HELD, ItemType.SIGNALMAST, rbx.getString("ActionSetSignalMastHeld")), // NOI18N
//      CLEAR_SIGNALMAST_HELD(ACTION_CLEAR_SIGNALMAST_HELD, ItemType.SIGNALMAST, rbx.getString("ActionClearSignalMastHeld")), // NOI18N
//      SET_SIGNALMAST_DARK(ACTION_SET_SIGNALMAST_DARK, ItemType.SIGNALMAST, rbx.getString("ActionSetSignalMastDark")), // NOI18N
//      SET_SIGNALMAST_LIT(ACTION_SET_SIGNALMAST_LIT, ItemType.SIGNALMAST, rbx.getString("ActionClearSignalMastDark")), // NOI18N
//      SET_BLOCK_VALUE(ACTION_SET_BLOCK_VALUE, ItemType.OBLOCK, rbx.getString("ActionSetBlockValue")), // NOI18N
//      SET_BLOCK_ERROR(ACTION_SET_BLOCK_ERROR, ItemType.OBLOCK, rbx.getString("ActionSetBlockError")), // NOI18N
//      CLEAR_BLOCK_ERROR(ACTION_CLEAR_BLOCK_ERROR, ItemType.OBLOCK, rbx.getString("ActionClearBlockError")), // NOI18N
//      DEALLOCATE_BLOCK(ACTION_DEALLOCATE_BLOCK, ItemType.OBLOCK, rbx.getString("ActionDeallocateBlock")), // NOI18N
//      SET_BLOCK_OUT_OF_SERVICE(ACTION_SET_BLOCK_OUT_OF_SERVICE, ItemType.OBLOCK, rbx.getString("ActionSetBlockOutOfService")), // NOI18N
//      SET_BLOCK_IN_SERVICE(ACTION_SET_BLOCK_IN_SERVICE, ItemType.OBLOCK, rbx.getString("ActionBlockInService")), // NOI18N
//      // EntryExit Actions
//      SET_NXPAIR_ENABLED(ACTION_SET_NXPAIR_ENABLED, ItemType.ENTRYEXIT, rbx.getString("ActionNXPairEnabled")), // NOI18N
//      SET_NXPAIR_DISABLED(ACTION_SET_NXPAIR_DISABLED, ItemType.ENTRYEXIT, rbx.getString("ActionNXPairDisabled")), // NOI18N
//      SET_NXPAIR_SEGMENT(ACTION_SET_NXPAIR_SEGMENT, ItemType.ENTRYEXIT, rbx.getString("ActionNXPairSegment")); // NOI18N
 public:
  enum ACTS {
   NONE,
   SET_TURNOUT,
   // allowed settings for turnout are Thrown and Closed (in data)
   SET_SIGNAL_APPEARANCE,
   // allowed settings for signal head are the seven Appearances (in data)
   SET_SIGNAL_HELD,
   CLEAR_SIGNAL_HELD,
   SET_SIGNAL_DARK,
   SET_SIGNAL_LIT,
   TRIGGER_ROUTE,
   SET_SENSOR,
   // allowed settings for sensor are active and inactive (in data)
   DELAYED_SENSOR,
   // allowed settings for timed sensor are active and inactive (in data)
   //   time in seconds before setting sensor should be in delay
   SET_LIGHT,
   // allowed settings for light are ON and OFF (in data)
   SET_MEMORY,
   // text to set into the memory variable should be in string
   ENABLE_LOGIX,
   DISABLE_LOGIX,
   PLAY_SOUND,
   // reference to sound should be in string
   RUN_SCRIPT,
   // reference to script should be in string
   DELAYED_TURNOUT,
   // allowed settings for timed turnout are Thrown and Closed (in data)
   //   time in seconds before setting turnout should be in delay
   LOCK_TURNOUT,
   RESET_DELAYED_SENSOR,
   // allowed settings for timed sensor are active and inactive (in data)
   //   time in seconds before setting sensor should be in delay
   CANCEL_SENSOR_TIMERS,
   // cancels all timers delaying setting of specified sensor
   RESET_DELAYED_TURNOUT,
   // allowed settings for timed sensor are active and inactive (in data)
   //   time in seconds before setting sensor should be in delay
   CANCEL_TURNOUT_TIMERS,
   // cancels all timers delaying setting of specified sensor
   SET_FAST_CLOCK_TIME,
   // sets the fast clock time to the time specified
   START_FAST_CLOCK,
   // starts the fast clock
   STOP_FAST_CLOCK,
   // stops the fast clock
   COPY_MEMORY,
   // copies value from memory variable (in name) to memory variable (in string)
   SET_LIGHT_INTENSITY,
   SET_LIGHT_TRANSITION_TIME,
   // control the specified audio object
   CONTROL_AUDIO,
   // execute a jython command
   JYTHON_COMMAND,
   // Warrant actions
   ALLOCATE_WARRANT_ROUTE,
   DEALLOCATE_WARRANT_ROUTE,
   SET_ROUTE_TURNOUTS,
   AUTO_RUN_WARRANT,
   MANUAL_RUN_WARRANT,
   CONTROL_TRAIN,
   SET_TRAIN_ID,
   SET_TRAIN_NAME,
   SET_SIGNALMAST_ASPECT,
   THROTTLE_FACTOR,
   SET_SIGNALMAST_HELD,
   CLEAR_SIGNALMAST_HELD,
   SET_SIGNALMAST_DARK,
   SET_SIGNALMAST_LIT,
   SET_BLOCK_VALUE,
   SET_BLOCK_ERROR,
   CLEAR_BLOCK_ERROR,
   DEALLOCATE_BLOCK,
   SET_BLOCK_OUT_OF_SERVICE,
   SET_BLOCK_IN_SERVICE,
   // EntryExit Actions
   SET_NXPAIR_ENABLED,
   SET_NXPAIR_DISABLED,
   SET_NXPAIR_SEGMENT
  };
  static QList<ACTS> values;
#if 0
    private final int _item;
    private final ItemType _itemType;
    private final String _string;

    private static final List<Action> sensorItemsList;
    private static final List<Action> turnoutItemsList;
    private static final List<Action> lightItemsList;
    private static final List<Action> warrantItemsList;
    private static final List<Action> memoryItemsList;
    private static final List<Action> oblockItemsList;
    private static final List<Action> entryExitItemsList;
    private static final List<Action> signalHeadItemsList;
    private static final List<Action> signalMastItemsList;
    private static final List<Action> clockItemsList;
    private static final List<Action> logixItemsList;
    private static final List<Action> audioItemsList;
    private static final List<Action> scriptItemsList;
    private static final List<Action> otherItemsList;


    static
    {
        Action[] typeArray1 = {SET_SENSOR, DELAYED_SENSOR,
            RESET_DELAYED_SENSOR, CANCEL_SENSOR_TIMERS};
        sensorItemsList = Collections.unmodifiableList(Arrays.asList(typeArray1));

        Action[] typeArray2 = {SET_TURNOUT, DELAYED_TURNOUT, LOCK_TURNOUT,
            CANCEL_TURNOUT_TIMERS, RESET_DELAYED_TURNOUT};
        turnoutItemsList = Collections.unmodifiableList(Arrays.asList(typeArray2));

        Action[] typeArray3 = {SET_LIGHT, SET_LIGHT_INTENSITY,
            SET_LIGHT_TRANSITION_TIME};
        lightItemsList = Collections.unmodifiableList(Arrays.asList(typeArray3));

        Action[] typeArray4 = {ALLOCATE_WARRANT_ROUTE, DEALLOCATE_WARRANT_ROUTE,
            SET_ROUTE_TURNOUTS, AUTO_RUN_WARRANT, MANUAL_RUN_WARRANT, CONTROL_TRAIN,
            SET_TRAIN_ID, SET_TRAIN_NAME, THROTTLE_FACTOR};
        warrantItemsList = Collections.unmodifiableList(Arrays.asList(typeArray4));

        Action[] typeArray5 = {SET_MEMORY, COPY_MEMORY};
        memoryItemsList = Collections.unmodifiableList(Arrays.asList(typeArray5));

        Action[] typeArray6 = {SET_NXPAIR_ENABLED, SET_NXPAIR_DISABLED,
            SET_NXPAIR_SEGMENT};
        entryExitItemsList = Collections.unmodifiableList(Arrays.asList(typeArray6));

        Action[] typeArray7 = {SET_SIGNAL_APPEARANCE, SET_SIGNAL_HELD,
            CLEAR_SIGNAL_HELD, SET_SIGNAL_DARK, SET_SIGNAL_LIT};
        signalHeadItemsList = Collections.unmodifiableList(Arrays.asList(typeArray7));

        Action[] typeArray8 = {SET_SIGNALMAST_ASPECT, SET_SIGNALMAST_HELD,
            CLEAR_SIGNALMAST_HELD, SET_SIGNALMAST_DARK, SET_SIGNALMAST_LIT};
        signalMastItemsList = Collections.unmodifiableList(Arrays.asList(typeArray8));

        Action[] typeArray9 = {SET_FAST_CLOCK_TIME, START_FAST_CLOCK,
            STOP_FAST_CLOCK};
        clockItemsList = Collections.unmodifiableList(Arrays.asList(typeArray9));

        Action[] typeArray10 = {ENABLE_LOGIX, DISABLE_LOGIX};
        logixItemsList = Collections.unmodifiableList(Arrays.asList(typeArray10));

        Action[] typeArray11 = {DEALLOCATE_BLOCK, SET_BLOCK_VALUE,
            SET_BLOCK_ERROR, CLEAR_BLOCK_ERROR, SET_BLOCK_OUT_OF_SERVICE,
            SET_BLOCK_IN_SERVICE};
        oblockItemsList = Collections.unmodifiableList(Arrays.asList(typeArray11));

        Action[] typeArray12 = {PLAY_SOUND, CONTROL_AUDIO};
        audioItemsList = Collections.unmodifiableList(Arrays.asList(typeArray12));

        Action[] typeArray13 = {RUN_SCRIPT, JYTHON_COMMAND};
        scriptItemsList = Collections.unmodifiableList(Arrays.asList(typeArray13));

        Action[] typeArray14 = {TRIGGER_ROUTE};
        otherItemsList = Collections.unmodifiableList(Arrays.asList(typeArray14));
    }

    private Action(int state, ItemType itemType, String string) {
        _item = state;
        _itemType = itemType;
        _string = string;
    }

    public ItemType getItemType() {
        return _itemType;
    }

    public int getIntValue() {
        return _item;
    }

    public static List<Action> getSensorItems() {
        return sensorItemsList;
    }

    public static List<Action> getTurnoutItems() {
        return turnoutItemsList;
    }

    public static List<Action> getLightItems() {
        return lightItemsList;
    }

    public static List<Action> getWarrantItems() {
        return warrantItemsList;
    }

    public static List<Action> getMemoryItems() {
        return memoryItemsList;
    }

    public static List<Action> getOBlockItems() {
        return oblockItemsList;
    }

    public static List<Action> getEntryExitItems() {
        return entryExitItemsList;
    }

    public static List<Action> getSignalHeadItems() {
        return signalHeadItemsList;
    }

    public static List<Action> getSignalMastItems() {
        return signalMastItemsList;
    }

    public static List<Action> getClockItems() {
        return clockItemsList;
    }

    public static List<Action> getLogixItems() {
        return logixItemsList;
    }

    public static List<Action> getAudioItems() {
        return audioItemsList;
    }

    public static List<Action> getScriptItems() {
        return scriptItemsList;
    }

    public static List<Action> getOtherItems() {
        return otherItemsList;
    }
#endif
    /*public*/ static Action::ACTS getOperatorFromIntValue(int actionInt) {
//        for (Action action : Action.values()) {
//            if (action.getIntValue() == actionInt) {
//                return action;
//            }
//        }

//        throw new IllegalArgumentException("Action is unknown");
      return (Action::ACTS) actionInt;
    }

    // Some items uses Bundle.getString() and some items uses rbx.getString()
    // and therefore the items must call getString() in the call to the constructor.
   //@Override
    /*public*/static QString toString(ACTS a) {
     switch (a) {
      case NONE: return tr("");
      case SET_TURNOUT: return tr("Set Turnout");
          // allowed settings for turnout are Thrown and Closed (in data)
          case SET_SIGNAL_APPEARANCE: return tr("Set Signal Head Appearance");
          // allowed settings for signal head are the seven Appearances (in data)
          case SET_SIGNAL_HELD: return tr("Set Signal Head Held");
          case CLEAR_SIGNAL_HELD: return tr("Clear Signal Head Held");
          case SET_SIGNAL_DARK: return tr("Set Signal Head Dark");
          case SET_SIGNAL_LIT: return tr("Set Signal Head Lit");
          case TRIGGER_ROUTE: return tr("Trigger Route");
          case SET_SENSOR: return tr("Set Sensor");
          // allowed settings for sensor are active and inactive (in data)
          case DELAYED_SENSOR: return tr("Delayed Set Sensor");
          // allowed settings for timed sensor are active and inactive (in data)
          //   time in seconds before setting sensor should be in delay
          case SET_LIGHT: return tr("Set Light");
          // allowed settings for light are ON and OFF (in data)
          case SET_MEMORY: return tr("Set Memory");
          // text to set into the memory variable should be in string
          case ENABLE_LOGIX: return tr("Enable Logix");
          case DISABLE_LOGIX: return tr("Disable Logix");
          case PLAY_SOUND: return tr("Play Sound");
          // reference to sound should be in string
          case RUN_SCRIPT: return tr("Run Script");
          // reference to script should be in string
          case DELAYED_TURNOUT: return tr("Delayed Set Turnout");
          // allowed settings for timed turnout are Thrown and Closed (in data)
          //   time in seconds before setting turnout should be in delay
          case LOCK_TURNOUT: return tr("Turnout Lock");
          case RESET_DELAYED_SENSOR: return tr("Reset Delayed Set Sensor");
          // allowed settings for timed sensor are active and inactive (in data)
          //   time in seconds before setting sensor should be in delay
          case CANCEL_SENSOR_TIMERS: return tr("Cancel Timers for Sensor");
          // cancels all timers delaying setting of specified sensor
          case RESET_DELAYED_TURNOUT: return tr("Reset Delayed Set Turnout");
          // allowed settings for timed sensor are active and inactive (in data)
          //   time in seconds before setting sensor should be in delay
          case CANCEL_TURNOUT_TIMERS: return tr("Cancel Timers for Turnout");
          // cancels all timers delaying setting of specified sensor
          case SET_FAST_CLOCK_TIME: return tr("Set Fast Clock Time");
          // sets the fast clock time to the time specified
          case START_FAST_CLOCK: return tr("Start Fast Clock");
          // starts the fast clock
          case STOP_FAST_CLOCK: return tr("Stop Fast Clock");
          // stops the fast clock
          case COPY_MEMORY: return tr("Copy Memory To Memory");
          // copies value from memory variable (in name) to memory variable (in string)
          case SET_LIGHT_INTENSITY: return tr("Set Light Intensity");
          case SET_LIGHT_TRANSITION_TIME: return tr("Set Light Transition Time");
          // control the specified audio object
          case CONTROL_AUDIO: return tr("Control Audio object");
          // execute a jython command
          case JYTHON_COMMAND: return tr("Execute Jython Command");
          // Warrant actions
          case ALLOCATE_WARRANT_ROUTE: return tr("Allocate Warrant Route");
          case DEALLOCATE_WARRANT_ROUTE: return tr("Deallocate Warrant");
          case SET_ROUTE_TURNOUTS: return tr("et Route Turnouts");
          case AUTO_RUN_WARRANT: return tr("Auto Run Train");
          case MANUAL_RUN_WARRANT: return tr("Manually Run Train");
          case CONTROL_TRAIN: return tr("Control Auto Train");
          case SET_TRAIN_ID: return tr("Set Train ID");
          case SET_TRAIN_NAME: return tr("Set Train Name");
          case SET_SIGNALMAST_ASPECT: return tr("Set Signal Mast Aspect");
          case THROTTLE_FACTOR: return tr("Set Throttle Factor");
          case SET_SIGNALMAST_HELD: return tr("Set Signal Mast Held");
          case CLEAR_SIGNALMAST_HELD: return tr("");
          case SET_SIGNALMAST_DARK: return tr("Set Signal Mast Dark");
          case SET_SIGNALMAST_LIT: return tr("Clear Signal Mast Dark");
          case SET_BLOCK_VALUE: return tr("Set Block Value");
          case SET_BLOCK_ERROR: return tr("");
          case CLEAR_BLOCK_ERROR: return tr("Set Block Error");
          case DEALLOCATE_BLOCK: return tr("Deallocate Block");
          case SET_BLOCK_OUT_OF_SERVICE: return tr("Set Block OutOfService");
          case SET_BLOCK_IN_SERVICE: return tr("Clear Block OutOfService");
          // EntryExit Actions
          case SET_NXPAIR_ENABLED: return tr("Set NX Pair Enabled");
          case SET_NXPAIR_DISABLED: return tr("Set NX Pair Disabled");
          case SET_NXPAIR_SEGMENT: return tr("Set NX Pair Segment Active / Inactive");

     }
    }
/*public*/static QString getItemTypeName(ACTS a) {
 switch (a) {
  case NONE: return tr("");
  case SET_TURNOUT: return tr(" Turnout");
      // allowed settings for turnout are Thrown and Closed (in data)
      case SET_SIGNAL_APPEARANCE: return tr("Set Signal Head Appearance");
      // allowed settings for signal head are the seven Appearances (in data)
      case SET_SIGNAL_HELD: return tr("Set Signal Head Held");
      case CLEAR_SIGNAL_HELD: return tr("Clear Signal Head Held");
      case SET_SIGNAL_DARK: return tr("Set Signal Head Dark");
      case SET_SIGNAL_LIT: return tr("Set Signal Head Lit");
      case TRIGGER_ROUTE: return tr("Trigger Route");
      case SET_SENSOR: return tr("Set Sensor");
      // allowed settings for sensor are active and inactive (in data)
      case DELAYED_SENSOR: return tr("Delayed Set Sensor");
      // allowed settings for timed sensor are active and inactive (in data)
      //   time in seconds before setting sensor should be in delay
      case SET_LIGHT: return tr("Set Light");
      // allowed settings for light are ON and OFF (in data)
      case SET_MEMORY: return tr("Set Memory");
      // text to set into the memory variable should be in string
      case ENABLE_LOGIX: return tr("Enable Logix");
      case DISABLE_LOGIX: return tr("Disable Logix");
      case PLAY_SOUND: return tr("Play Sound");
      // reference to sound should be in string
      case RUN_SCRIPT: return tr("Run Script");
      // reference to script should be in string
      case DELAYED_TURNOUT: return tr("Delayed Set Turnout");
      // allowed settings for timed turnout are Thrown and Closed (in data)
      //   time in seconds before setting turnout should be in delay
      case LOCK_TURNOUT: return tr("Turnout Lock");
      case RESET_DELAYED_SENSOR: return tr("Reset Delayed Set Sensor");
      // allowed settings for timed sensor are active and inactive (in data)
      //   time in seconds before setting sensor should be in delay
      case CANCEL_SENSOR_TIMERS: return tr("Cancel Timers for Sensor");
      // cancels all timers delaying setting of specified sensor
      case RESET_DELAYED_TURNOUT: return tr("Reset Delayed Set Turnout");
      // allowed settings for timed sensor are active and inactive (in data)
      //   time in seconds before setting sensor should be in delay
      case CANCEL_TURNOUT_TIMERS: return tr("Cancel Timers for Turnout");
      // cancels all timers delaying setting of specified sensor
      case SET_FAST_CLOCK_TIME: return tr("Set Fast Clock Time");
      // sets the fast clock time to the time specified
      case START_FAST_CLOCK: return tr("Start Fast Clock");
      // starts the fast clock
      case STOP_FAST_CLOCK: return tr("Stop Fast Clock");
      // stops the fast clock
      case COPY_MEMORY: return tr("Copy Memory To Memory");
      // copies value from memory variable (in name) to memory variable (in string)
      case SET_LIGHT_INTENSITY: return tr("Set Light Intensity");
      case SET_LIGHT_TRANSITION_TIME: return tr("Set Light Transition Time");
      // control the specified audio object
      case CONTROL_AUDIO: return tr("Control Audio object");
      // execute a jython command
      case JYTHON_COMMAND: return tr("Execute Jython Command");
      // Warrant actions
      case ALLOCATE_WARRANT_ROUTE: return tr("Allocate Warrant Route");
      case DEALLOCATE_WARRANT_ROUTE: return tr("Deallocate Warrant");
      case SET_ROUTE_TURNOUTS: return tr("et Route Turnouts");
      case AUTO_RUN_WARRANT: return tr("Auto Run Train");
      case MANUAL_RUN_WARRANT: return tr("Manually Run Train");
      case CONTROL_TRAIN: return tr("Control Auto Train");
      case SET_TRAIN_ID: return tr("Set Train ID");
      case SET_TRAIN_NAME: return tr("Set Train Name");
      case SET_SIGNALMAST_ASPECT: return tr("Set Signal Mast Aspect");
      case THROTTLE_FACTOR: return tr("Set Throttle Factor");
      case SET_SIGNALMAST_HELD: return tr("Set Signal Mast Held");
      case CLEAR_SIGNALMAST_HELD: return tr("");
      case SET_SIGNALMAST_DARK: return tr("Set Signal Mast Dark");
      case SET_SIGNALMAST_LIT: return tr("Clear Signal Mast Dark");
      case SET_BLOCK_VALUE: return tr("Set Block Value");
      case SET_BLOCK_ERROR: return tr("");
      case CLEAR_BLOCK_ERROR: return tr("Set Block Error");
      case DEALLOCATE_BLOCK: return tr("Deallocate Block");
      case SET_BLOCK_OUT_OF_SERVICE: return tr("Set Block OutOfService");
      case SET_BLOCK_IN_SERVICE: return tr("Clear Block OutOfService");
      // EntryExit Actions
      case SET_NXPAIR_ENABLED: return tr("Set NX Pair Enabled");
      case SET_NXPAIR_DISABLED: return tr("Set NX Pair Disabled");
      case SET_NXPAIR_SEGMENT: return tr("Set NX Pair Segment Active / Inactive");

 }
}
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
