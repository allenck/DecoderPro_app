#ifndef IMPORTOTHERDATA_H
#define IMPORTOTHERDATA_H

#include <QObject>

class ImportOtherData : public QObject
{
  Q_OBJECT
 public:
  /*public*/ class CTC_PANEL_TYPE {
   public:
  // The values in paren's are the RadioGroup values set by "CommonSubs.numberButtonGroup",
  // gotten by calling "CommonSubs.getButtonSelectedInt".
    enum CTC_PANEL_TYPES
    {
      USS = 0, OTHER = 1
    };
      /*private*/ /*final*/ int _mRadioGroupValue;
      /*private*/ /*final*/ static QMap<int, CTC_PANEL_TYPE> map;// = QMap<int, CTC_PANEL_TYPE>();
      /*private*/ CTC_PANEL_TYPE (int radioGroupValue =0) { _mRadioGroupValue = radioGroupValue; }
      //static { for (CTC_PANEL_TYPE value : CTC_PANEL_TYPE.values()) { map.put(value._mRadioGroupValue, value); }}
   public:
    /*public*/  QString toString();
    /*public*/ static CTC_PANEL_TYPE valueOf(QString t);
  };

  /*public*/ class SIGNALS_ON_PANEL {
  // The values in paren's are the RadioGroup values set by "CommonSubs.numberButtonGroup",
  // gotten by calling "CommonSubs.getButtonSelectedInt".
   public:
    enum SIGNALS_ON_PANELS
    {
      ALL = 0, GREEN_OFF =1, NONE =2
    };
      /*private*/ /*final*/ int _mRadioGroupValue;
      /*private*/ /*final*/ static QMap<int, SIGNALS_ON_PANEL> map;// = QMap<int, SIGNALS_ON_PANEL>();
      /*private*/ SIGNALS_ON_PANEL (int radioGroupValue = 0) { _mRadioGroupValue = radioGroupValue; }
  //    static { for (SIGNALS_ON_PANEL value : SIGNALS_ON_PANEL.values()) { map.put(value._mRadioGroupValue, value); }}
    /*public*/ QString toString();
    /*public*/ static SIGNALS_ON_PANEL valueOf(QString);

  };

  /*public*/ class VERTICAL_SIZE {
  // The values in paren's are the RadioGroup values set by "CommonSubs.numberButtonGroup",
  // gotten by calling "CommonSubs.getButtonSelectedInt".
   public:
    enum VERTICAL_SIZES
    {
      SMALL = 0, MEDIUM =1, LARGE =2
    };
      /*private*/ /*final*/ int _mRadioGroupValue;
      /*private*/ /*final*/ static QMap<int, VERTICAL_SIZE> map;// = QMap<int, VERTICAL_SIZE>();
      /*private*/ VERTICAL_SIZE (int radioGroupValue =0) { _mRadioGroupValue = radioGroupValue; }
  //    static { for (VERTICAL_SIZE value : VERTICAL_SIZE.values()) { map.put(value._mRadioGroupValue, value); }}
    /*public*/ QString toString();

  };

  /*public*/ class SIGNAL_SYSTEM_TYPE {
   public:
  // The values in paren's are the RadioGroup values set by "CommonSubs.numberButtonGroup",
  // gotten by calling "CommonSubs.getButtonSelectedInt".
    enum SIGNAL_SYSTEM_TYPES
    {
      SIGNALHEAD = 0, SIGNALMAST =1
    };
   //private:
      /*private*/ /*final*/ int _mRadioGroupValue;
      /*private*/ /*final*/ static QMap<int, SIGNAL_SYSTEM_TYPE> map;// = QMap<int, SIGNAL_SYSTEM_TYPE>();
      /*private*/ SIGNAL_SYSTEM_TYPE (int radioGroupValue = 0) { _mRadioGroupValue = radioGroupValue; }
  //    static { for (SIGNAL_SYSTEM_TYPE value : SIGNAL_SYSTEM_TYPE.values()) { map.put(value._mRadioGroupValue, value); }}
   public:
    /*public*/ QString toString();
  };
  /*
  Because of "getAllInternalSensorStringFields", ANY JMRI sensor object that we
  create should have "InternalSensor" (case sensitive) as ANY PART of their
  variable name and declared as type String.
  */
  //     /*private*/ static /*final*/ String INTERNAL_SENSOR = "InternalSensor";             // NOI18N
  //  Version of this file for supporting upgrade paths from prior versions:
  /*public*/ int      _mFileVersion;
  //  Fleeting:
  /*public*/ QString   _mFleetingToggleInternalSensor;
  /*public*/ bool  _mDefaultFleetingEnabled;
  //  Global startup:
  /*public*/ bool  _mTUL_EnabledAtStartup = true;
  /*public*/ SIGNAL_SYSTEM_TYPE _mSignalSystemType;
  /*public*/ int      _mTUL_SecondsToLockTurnouts = 0;
  //  Next unique # for each created Column:
  /*public*/ int      _mNextUniqueNumber = 0;
  //  CTC Debugging:
  /*public*/ QString   _mCTCDebugSystemReloadInternalSensor;
  /*public*/ QString   _mCTCDebug_TrafficLockingRuleTriggeredDisplayInternalSensor;
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
  explicit ImportOtherData(QObject *parent = nullptr);
  /*public*/ void upgradeSelf();

 signals:

 public slots:

 private:
  /*private*/ /*final*/ static int FILE_VERSION;// = 0;

};

#endif // IMPORTOTHERDATA_H
