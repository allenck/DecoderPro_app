#ifndef OTHERDATA_H
#define OTHERDATA_H

#include <QObject>
#include <QMap>
#include <QButtonGroup>
#include "nbhsensor.h"
#include "nbhsignal.h"
#include "nbhturnout.h"
#include "projectscommonsubs.h"

class OtherData : public QObject
{
  Q_OBJECT
 public:
  /*public*/ /*enum*/class CTC_PANEL_TYPE {
// The values in paren's are the RadioGroup values set by "CommonSubs.numberButtonGroup",
// gotten by calling "CommonSubs.getButtonSelectedInt".
   public:
    enum CTC_PANEL_TYPES
    {
      USS = 0, OTHER =1
    };
    /*private*/ /*final*/ static QMap<int, CTC_PANEL_TYPE> map;// = QMap<int, CTC_PANEL_TYPE>();
   public:
      /*private*/ /*final*/ int _mRadioGroupValue;
      /*private*/ CTC_PANEL_TYPE (int radioGroupValue = 0) { _mRadioGroupValue = radioGroupValue; }
//      static { for (CTC_PANEL_TYPE value : CTC_PANEL_TYPE.values()) { map.put(value._mRadioGroupValue, value); }}
   public:
     /*public*/ int getRadioGroupValue() { return _mRadioGroupValue; }
     /*public*/ static CTC_PANEL_TYPE getRadioGroupValue(int radioGroupValue);// { return map.value(radioGroupValue); }
   friend class OtherData;
  };

  /*public*/ /*enum*/class SIGNALS_ON_PANEL {
// The values in paren's are the RadioGroup values set by "CommonSubs.numberButtonGroup",
// gotten by calling "CommonSubs.getButtonSelectedInt".
   public:
      enum SIGNALS_ON_PANELS{
          ALL = 0, GREEN_OFF =1, NONE =2
      };
      /*private*/ /*final*/ static QMap<int, SIGNALS_ON_PANEL> map;// = new HashMap<>();
   public:
      /*private*/ /*final*/ int _mRadioGroupValue;
      /*private*/ SIGNALS_ON_PANEL (int radioGroupValue = 0) { _mRadioGroupValue = radioGroupValue; }
//      static { for (SIGNALS_ON_PANEL value : SIGNALS_ON_PANEL.values()) { map.put(value._mRadioGroupValue, value); }}
   public:
      /*public*/ int getRadioGroupValue() { return _mRadioGroupValue; }
      /*public*/ static SIGNALS_ON_PANEL getRadioGroupValue(int radioGroupValue);// { return map.value(radioGroupValue); }
      friend class OtherData;
  };

  /*public*/ /*enum*/class VERTICAL_SIZE {
   public:
// The values in paren's are the RadioGroup values set by "CommonSubs.numberButtonGroup",
// gotten by calling "CommonSubs.getButtonSelectedInt".
   enum VERTICAL_SIZES
   {
      SMALL = 0, MEDIUM = 1, LARGE= 2
   };
      /*private*/ /*final*/ int _mRadioGroupValue;
      /*private*/ /*final*/ static QMap<int, VERTICAL_SIZE> map;// = new HashMap<>();
      /*private*/ VERTICAL_SIZE (int radioGroupValue = 0) { _mRadioGroupValue = radioGroupValue; }
//      static { for (VERTICAL_SIZE value : VERTICAL_SIZE.values()) { map.put(value._mRadioGroupValue, value); }}
      /*public*/ int getRadioGroupValue() { return _mRadioGroupValue; }
      /*public*/ static VERTICAL_SIZE getRadioGroupValue(int radioGroupValue);// { return map.value(radioGroupValue); }
   friend class OtherData;
  };


  /*public*/ /*enum*/ class SIGNAL_SYSTEM_TYPE {
   public:
// The values in paren's are the RadioGroup values set by "CommonSubs.numberButtonGroup",
// gotten by calling "CommonSubs.getButtonSelectedInt".
    enum SIGNAL_SYSTEM_TYPES
    {
       SIGNALHEAD = 0, SIGNALMAST =1
    };
    /*private*/ /*final*/ static QMap<int, SIGNAL_SYSTEM_TYPE> map;// = new HashMap<>();
   public:
      /*private*/ /*final*/ int _mRadioGroupValue;
      /*private*/ SIGNAL_SYSTEM_TYPE (int radioGroupValue = 0) { _mRadioGroupValue = radioGroupValue; }
//      static { for (SIGNAL_SYSTEM_TYPE value : SIGNAL_SYSTEM_TYPE.values()) { map.put(value._mRadioGroupValue, value); }}
   public:
      /*public*/ int getInt() { return _mRadioGroupValue; }
      /*public*/ static SIGNAL_SYSTEM_TYPE getSignalSystemType(int radioGroupValue);// { return map.value(radioGroupValue); }
      /*public*/ static SIGNAL_SYSTEM_TYPE getSignalSystemType(QButtonGroup* buttonGroup);// { return map.value(ProjectsCommonSubs::getButtonSelectedInt(buttonGroup)); }
    friend class OtherData;
  };
  explicit OtherData(QObject *parent = nullptr);
  /*public*/ /*final*/ static QString CTC_VERSION;// = "v2.0";
  /*public*/ int getNextUniqueNumber();
  /*public*/ void possiblySetToHighest(int value);
  //  Fleeting:
      /*public*/ NBHSensor*   _mFleetingToggleInternalSensor;
      /*public*/ bool  _mDefaultFleetingEnabled;
  //  Global startup:
      /*public*/ bool  _mTUL_EnabledAtStartup = true;
      /*public*/ SIGNAL_SYSTEM_TYPE::SIGNAL_SYSTEM_TYPES _mSignalSystemType;
      /*public*/ int      _mTUL_SecondsToLockTurnouts = 0;
  //  Next unique # for each created Column:
      /*public*/ int      _mNextUniqueNumber = 0;
  //  CTC Debugging:
      /*public*/ NBHSensor*   _mCTCDebugSystemReloadInternalSensor;
      /*public*/ NBHSensor*   _mCTCDebug_TrafficLockingRuleTriggeredDisplayInternalSensor;
  //  GUI design:
      /*public*/ int      _mGUIDesign_NumberOfEmptyColumnsAtEnd;
      /*public*/ CTC_PANEL_TYPE   _mGUIDesign_CTCPanelType;
      /*public*/ bool  _mGUIDesign_BuilderPlate;
      /*public*/ SIGNALS_ON_PANEL _mGUIDesign_SignalsOnPanel;
      /*public*/ bool  _mGUIDesign_FleetingToggleSwitch;
      /*public*/ bool  _mGUIDesign_AnalogClockEtc;
      /*public*/ bool  _mGUIDesign_ReloadCTCSystemButton;
      /*public*/ bool  _mGUIDesign_CTCDebugOnToggle;
      /*public*/ bool  _mGUIDesign_CreateTrackPieces;
      /*public*/ VERTICAL_SIZE _mGUIDesign_VerticalSize;
      /*public*/ bool  _mGUIDesign_OSSectionUnknownInconsistentRedBlink;
      /*public*/ bool  _mGUIDesign_TurnoutsOnPanel;
 signals:

 public slots:
};

#endif // OTHERDATA_H
