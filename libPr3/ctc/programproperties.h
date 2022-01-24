#ifndef PROGRAMPROPERTIES_H
#define PROGRAMPROPERTIES_H

#include <QObject>

class Logger;
class ProgramProperties : public QObject
{
  Q_OBJECT
 public:
  explicit ProgramProperties(QObject *parent = nullptr);
  /*public*/ QString _mCodeButtonInternalSensorPattern = CODE_BUTTON_INTERNAL_SENSOR_PATTERN_DEFAULT;
  /*public*/ int _mSIDI_CodingTimeInMilliseconds = (SIDI_CODING_TIME_IN_MILLISECONDS_DEFAULT).toInt();
  /*public*/ QString _mSIDI_LeftInternalSensorPattern = SIDI_LEFT_INTERNAL_SENSOR_PATTERN_DEFAULT;
  /*public*/ QString _mSIDI_NormalInternalSensorPattern = SIDI_NORMAL_INTERNAL_SENSOR_PATTERN_DEFAULT;
  /*public*/ QString _mSIDI_RightInternalSensorPattern = SIDI_RIGHT_INTERNAL_SENSOR_PATTERN_DEFAULT;
  /*public*/ int _mSIDI_TimeLockingTimeInMilliseconds = (SIDI_TIME_LOCKING_TIME_IN_MILLISECONDS_DEFAULT).toInt();
  /*public*/ QString _mSIDL_LeftInternalSensorPattern = SIDL_LEFT_INTERNAL_SENSOR_PATTERN_DEFAULT;
  /*public*/ QString _mSIDL_NormalInternalSensorPattern = SIDL_NORMAL_INTERNAL_SENSOR_PATTERN_DEFAULT;
  /*public*/ QString _mSIDL_RightInternalSensorPattern = SIDL_RIGHT_INTERNAL_SENSOR_PATTERN_DEFAULT;
  /*public*/ int _mSWDI_CodingTimeInMilliseconds = (SWDI_CODING_TIME_IN_MILLISECONDS_DEFAULT).toInt();
  /*public*/ QString _mSWDI_NormalInternalSensorPattern = SWDI_NORMAL_INTERNAL_SENSOR_PATTERN_DEFAULT;
  /*public*/ QString _mSWDI_ReversedInternalSensorPattern = SWDI_REVERSED_INTERNAL_SENSOR_PATTERN_DEFAULT;
  /*public*/ QString _mSWDL_InternalSensorPattern = SWDL_INTERNAL_SENSOR_PATTERN_DEFAULT;
  /*public*/ QString _mCO_CallOnToggleInternalSensorPattern = CO_CALL_ON_TOGGLE_INTERNAL_SENSOR_PATTERN_DEFAULT;
  /*public*/ QString _mTUL_DispatcherInternalSensorLockTogglePattern = TUL_DISPATCHER_INTERNAL_SENSOR_LOCK_TOGGLE_PATTERN_DEFAULT;
  /*public*/ QString _mTUL_DispatcherInternalSensorUnlockedIndicatorPattern = TUL_DISPATCHER_INTERNAL_SENSOR_UNLOCKED_INDICATOR_PATTERN_DEFAULT;
  /*public*/ int _mCodeButtonDelayTime = (NO_CODE_BUTTON_DELAY_TIME_IN_MILLISECONDS_DEFAULT).toInt();

  /*public*/ void importExternalProgramProperties();

 signals:

 public slots:

 private:
  static Logger* log;
  /*private*/ static /*final*/ QString PROPERTIES_FILENAME;// = "ProgramProperties.xml";  // NOI18N
  /*private*/ static /*final*/ QString CODE_BUTTON_INTERNAL_SENSOR_PATTERN;// = "_mCodeButtonInternalSensorPattern";  // NOI18N
  /*private*/ static /*final*/ QString CODE_BUTTON_INTERNAL_SENSOR_PATTERN_DEFAULT;// = "IS#:CB"; // NOI18N
  /*private*/ static /*final*/ QString SIDI_CODING_TIME_IN_MILLISECONDS;// = "_mSIDI_CodingAndResponseTime";  // NOI18N
  /*private*/ static /*final*/ QString SIDI_CODING_TIME_IN_MILLISECONDS_DEFAULT;// = Integer.toString(2000);
  /*private*/ static /*final*/ QString SIDI_LEFT_INTERNAL_SENSOR_PATTERN;// = "_mSIDI_LeftInternalSensorPattern"; // NOI18N
  /*private*/ static /*final*/ QString SIDI_LEFT_INTERNAL_SENSOR_PATTERN_DEFAULT;// = "IS#:LDGK";// NOI18N
  /*private*/ static /*final*/ QString SIDI_NORMAL_INTERNAL_SENSOR_PATTERN;// = "_mSIDI_NormalInternalSensorPattern";// NOI18N
  /*private*/ static /*final*/ QString SIDI_NORMAL_INTERNAL_SENSOR_PATTERN_DEFAULT;// = "IS#:NGK";// NOI18N
  /*private*/ static /*final*/ QString SIDI_RIGHT_INTERNAL_SENSOR_PATTERN;// = "_mSIDI_RightInternalSensorPattern";// NOI18N
  /*private*/ static /*final*/ QString SIDI_RIGHT_INTERNAL_SENSOR_PATTERN_DEFAULT;// = "IS#:RDGK";// NOI18N
  /*private*/ static /*final*/ QString SIDI_TIME_LOCKING_TIME_IN_MILLISECONDS;// = "_mSIDI_TimeLockingTimeInMilliseconds";// NOI18N
  /*private*/ static /*final*/ QString SIDI_TIME_LOCKING_TIME_IN_MILLISECONDS_DEFAULT;// = Integer.toString(3000);
  /*private*/ static /*final*/ QString SIDL_LEFT_INTERNAL_SENSOR_PATTERN;// = "_mSIDL_LeftInternalSensorPattern";// NOI18N
  /*private*/ static /*final*/ QString SIDL_LEFT_INTERNAL_SENSOR_PATTERN_DEFAULT;// = "IS#:LDGL";// NOI18N
  /*private*/ static /*final*/ QString SIDL_NORMAL_INTERNAL_SENSOR_PATTERN;// = "_mSIDL_NormalInternalSensorPattern";// NOI18N
  /*private*/ static /*final*/ QString SIDL_NORMAL_INTERNAL_SENSOR_PATTERN_DEFAULT;// = "IS#:NGL";// NOI18N
  /*private*/ static /*final*/ QString SIDL_RIGHT_INTERNAL_SENSOR_PATTERN;// = "_mSIDL_RightInternalSensorPattern";// NOI18N
  /*private*/ static /*final*/ QString SIDL_RIGHT_INTERNAL_SENSOR_PATTERN_DEFAULT;// = "IS#:RDGL";// NOI18N
  /*private*/ static /*final*/ QString SWDI_CODING_TIME_IN_MILLISECONDS;// = "_mSWDI_CodingTimeInMilliseconds";// NOI18N
  /*private*/ static /*final*/ QString SWDI_CODING_TIME_IN_MILLISECONDS_DEFAULT;// = Integer.toString(2000);
  /*private*/ static /*final*/ QString SWDI_NORMAL_INTERNAL_SENSOR_PATTERN;// = "_mSWDI_NormalInternalSensorPattern";// NOI18N
  /*private*/ static /*final*/ QString SWDI_NORMAL_INTERNAL_SENSOR_PATTERN_DEFAULT;// = "IS#:SWNI";// NOI18N
  /*private*/ static /*final*/ QString SWDI_REVERSED_INTERNAL_SENSOR_PATTERN;// = "_mSWDI_ReversedInternalSensorPattern";// NOI18N
  /*private*/ static /*final*/ QString SWDI_REVERSED_INTERNAL_SENSOR_PATTERN_DEFAULT;// = "IS#:SWRI";// NOI18N
  /*private*/ static /*final*/ QString SWDL_INTERNAL_SENSOR_PATTERN;// = "_mSWDL_InternalSensorPattern";// NOI18N
  /*private*/ static /*final*/ QString SWDL_INTERNAL_SENSOR_PATTERN_DEFAULT;// = "IS#:LEVER";// NOI18N
  /*private*/ static /*final*/ QString CO_CALL_ON_TOGGLE_INTERNAL_SENSOR_PATTERN;// = "_mCO_CallOnToggleInternalSensorPattern";// NOI18N
  /*private*/ static /*final*/ QString CO_CALL_ON_TOGGLE_INTERNAL_SENSOR_PATTERN_DEFAULT;// = "IS#:CALLON";// NOI18N
  /*private*/ static /*final*/ QString TUL_DISPATCHER_INTERNAL_SENSOR_LOCK_TOGGLE_PATTERN;// = "_mTUL_DispatcherInternalSensorLockTogglePattern";// NOI18N
  /*private*/ static /*final*/ QString TUL_DISPATCHER_INTERNAL_SENSOR_LOCK_TOGGLE_PATTERN_DEFAULT;// = "IS#:LOCKTOGGLE";// NOI18N
  /*private*/ static /*final*/ QString TUL_DISPATCHER_INTERNAL_SENSOR_UNLOCKED_INDICATOR_PATTERN;// = "_mTUL_DispatcherInternalSensorUnlockedIndicatorPattern";// NOI18N
  /*private*/ static /*final*/ QString TUL_DISPATCHER_INTERNAL_SENSOR_UNLOCKED_INDICATOR_PATTERN_DEFAULT;// = "IS#:UNLOCKEDINDICATOR";// NOI18N
  /*private*/ static /*final*/ QString NO_CODE_BUTTON_DELAY_TIME_IN_MILLISECONDS;// = "_mCodeButtonDelayTime";// NOI18N
  /*private*/ static /*final*/ QString NO_CODE_BUTTON_DELAY_TIME_IN_MILLISECONDS_DEFAULT;// = QString::number(0);

};

#endif // PROGRAMPROPERTIES_H
