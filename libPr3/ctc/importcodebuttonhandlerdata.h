#ifndef IMPORTCODEBUTTONHANDLERDATA_H
#define IMPORTCODEBUTTONHANDLERDATA_H

#include <QObject>
#include "exceptions.h"

class QTextStream;
class ImportCodeButtonHandlerData : public QObject
{
  Q_OBJECT
 public:
  /*public*/ class LOCK_IMPLEMENTATION {
   public:
// The values in paren's are the RadioGroup values set by "CommonSubs.numberButtonGroup",
// gotten by calling "CommonSubs.getButtonSelectedInt".
    enum LOCK_IMPLEMENTATIONS
    {
      GREGS=0, OTHER=1
    };

      /*private*/ /*final*/ int _mRadioGroupValue;
      /*private*/ /*final*/ static QMap<int, LOCK_IMPLEMENTATION> map;// = QMap<int, LOCK_IMPLEMENTATION>();
      /*private*/ LOCK_IMPLEMENTATION (int radioGroupValue = 0) { _mRadioGroupValue = radioGroupValue; }
//      static { for (LOCK_IMPLEMENTATION value : LOCK_IMPLEMENTATION.values()) { map.put(value._mRadioGroupValue, value); }}
    /*public*/ QString toString();
  };

  /*public*/ class TURNOUT_TYPE {
// The values in paren's are the RadioGroup values set by "CommonSubs.numberButtonGroup",
// gotten by calling "CommonSubs.getButtonSelectedInt".
   public:
    enum TURNOUT_TYPES
  {
      TURNOUT = 0, CROSSOVER =1, DOUBLE_CROSSOVER =2
  };
//   private:
      /*private*/ /*final*/ int _mRadioGroupValue;
      /*private*/ /*final*/ static QMap<int, TURNOUT_TYPE> map;// = QMap<int, TURNOUT_TYPE>();
      /*private*/ TURNOUT_TYPE (int radioGroupValue = 0) { _mRadioGroupValue = radioGroupValue; }
      //static { for (TURNOUT_TYPE value : TURNOUT_TYPE.values()) { map.put(value._mRadioGroupValue, value); }}
   public:
    /*public*/ QString toString();
    /*public*/ static TURNOUT_TYPE valueOf(QString t);
  };
  //  This number NEVER changes, and is how this object is uniquely identified:
      /*public*/ int _mUniqueID = -1;         // FORCE serialization to write out the FIRST unique number 0 into the XML file (to make me happy!)
  //  Used by the Editor only:
      /*public*/ int _mSwitchNumber;         // Switch Indicators and lever #
      /*public*/ int _mSignalEtcNumber;      // Signal Indicators, lever, locktoggle, callon and code button number
  //  PRESENTLY (as of 10/18/18) these are ONLY used by the edit routines to TEMPORARILY get a copy.  The
  //  data is NEVER stored anywhere.  I say this because "_mUniqueID" MUST have another unique number if it is EVER
  //  stored anywhere!  For example: take the source # and add 5,000,000 to it each time.  Even copies of copies would
  //  get unique numbers!  If the user ever creates 5,000,000 objects, they must be GOD!

  //  Version of this file for supporting upgrade paths from prior versions:
      /*public*/ int                  _mFileVersion;
  //  Data used by the runtime (JMRI) and Editor systems:
      /*public*/ QString               _mCodeButtonInternalSensor;
      /*public*/ QString               _mOSSectionOccupiedExternalSensor;              // Required
      /*public*/ QString               _mOSSectionOccupiedExternalSensor2;             // Optional
      /*public*/ int                  _mOSSectionSwitchSlavedToUniqueID;
      /*public*/ int                  _mGUIColumnNumber;
      /*public*/ bool              _mGUIGeneratedAtLeastOnceAlready;
      /*public*/ int                  _mCodeButtonDelayTime;
  //  Signal Direction Indicators:
      /*public*/ bool              _mSIDI_Enabled;
      /*public*/ QString               _mSIDI_LeftInternalSensor;
      /*public*/ QString               _mSIDI_NormalInternalSensor;
      /*public*/ QString               _mSIDI_RightInternalSensor;
      /*public*/ int                  _mSIDI_CodingTimeInMilliseconds;
      /*public*/ int                  _mSIDI_TimeLockingTimeInMilliseconds;
      /*public*/ QString               _mSIDI_LeftRightTrafficSignalsCSVList;
      /*public*/ QString               _mSIDI_RightLeftTrafficSignalsCSVList;
  //  Signal Direction Lever:
      /*public*/ bool              _mSIDL_Enabled;
      /*public*/ QString               _mSIDL_LeftInternalSensor;
      /*public*/ QString               _mSIDL_NormalInternalSensor;
      /*public*/ QString               _mSIDL_RightInternalSensor;
  //  Switch Direction Indicators:
      /*public*/ bool              _mSWDI_Enabled;
      /*public*/ QString               _mSWDI_NormalInternalSensor;
      /*public*/ QString               _mSWDI_ReversedInternalSensor;
      /*public*/ QString               _mSWDI_ExternalTurnout;
      /*public*/ int                  _mSWDI_CodingTimeInMilliseconds;
      /*public*/ bool              _mSWDI_FeedbackDifferent;
      /*public*/ TURNOUT_TYPE         _mSWDI_GUITurnoutType;
      /*public*/ bool              _mSWDI_GUITurnoutLeftHand;
      /*public*/ bool              _mSWDI_GUICrossoverLeftHand;
  //  Switch Direction Lever:
      /*public*/ bool              _mSWDL_Enabled;
      /*public*/ QString               _mSWDL_InternalSensor;
  //  Call On:
      /*public*/ bool              _mCO_Enabled;
      /*public*/ QString               _mCO_CallOnToggleInternalSensor;
      /*public*/ QString               _mCO_GroupingsListString;
  //  Traffic Locking:
      /*public*/ bool              _mTRL_Enabled;
      /*public*/ QString               _mTRL_LeftTrafficLockingRulesSSVList;
      /*public*/ QString               _mTRL_RightTrafficLockingRulesSSVList;
  //  Turnout Locking:
      /*public*/ bool              _mTUL_Enabled;
      /*public*/ QString               _mTUL_DispatcherInternalSensorLockToggle;
      /*public*/ QString               _mTUL_ExternalTurnout;
      /*public*/ bool              _mTUL_ExternalTurnoutFeedbackDifferent;
      /*public*/ QString               _mTUL_DispatcherInternalSensorUnlockedIndicator;
      /*public*/ bool              _mTUL_NoDispatcherControlOfSwitch;
      /*public*/ bool              _mTUL_ndcos_WhenLockedSwitchStateIsClosed;
      /*public*/ LOCK_IMPLEMENTATION  _mTUL_LockImplementation;
      /*public*/ QString               _mTUL_AdditionalExternalTurnout1;
      /*public*/ bool              _mTUL_AdditionalExternalTurnout1FeedbackDifferent;
      /*public*/ QString               _mTUL_AdditionalExternalTurnout2;
      /*public*/ bool              _mTUL_AdditionalExternalTurnout2FeedbackDifferent;
      /*public*/ QString               _mTUL_AdditionalExternalTurnout3;
      /*public*/ bool              _mTUL_AdditionalExternalTurnout3FeedbackDifferent;
  //  Indication Locking (Signals):
      /*public*/ bool              _mIL_Enabled;
      /*public*/ QString               _mIL_ListOfCSVSignalNames;


  explicit ImportCodeButtonHandlerData(QObject *parent = nullptr);
  /*public*/ void upgradeSelf();
  static /*public*/ void preprocessingUpgradeSelf(QString filename);

 signals:

 public slots:

 private:
  /*private*/ /*final*/ static int FILE_VERSION;// = 6;
  /*public*/ static /*final*/ int SWITCH_NOT_SLAVED;// = -1;
  /*private*/ static /*final*/ long serialVersionUID;// = 1L;
  /*private*/ /*final*/ static QString FILE_VERSION_STRING;// = "<string>_mFileVersion</string>"; // NOI18N
  /*private*/ /*final*/ static QString LESS_THAN_SIGN;// = "<";                                   // NOI18N
  /*private*/ static /*final*/ QString TEMPORARY_EXTENSION;// = ".xmlTMP";                        // NOI18N
  static /*private*/ void upgradeVersion4FileTo5(QString filename);
  static /*private*/ void upgradeVersion5FileTo6(QString filename);
  /*private*/ /*final*/ static QString INT_START_STRING;// = "<int>"; // NOI18N
  /*private*/ /*final*/ static QString INT_END_STRING;// = "</int>";  // NOI18N
  static /*private*/ QString checkFileVersion(QTextStream* bufferedReader, QTextStream* bufferedWriter, QString aLine, QString oldVersion, QString newVersion) throw (IOException);
   /*private*/ /*final*/ static QString STRING_START_STRING;// = "<string>";   // NOI18N
   /*private*/ /*final*/ static QString STRING_END_STRING;// = "</string>";    // NOI18N
   static /*private*/ QString checkForRefactor(QTextStream* bufferedWriter, QString aLine, QString oldName, QString newName) throw (IOException);
   static /*private*/ QString checkForMultipleSemiColons(QTextStream* bufferedWriter, QString aLine) throw (IOException);
   static /*private*/ void writeLine(QTextStream* bufferedWriter, QString aLine) throw (IOException);

};

#endif // IMPORTCODEBUTTONHANDLERDATA_H
