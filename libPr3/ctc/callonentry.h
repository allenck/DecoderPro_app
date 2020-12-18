#ifndef CALLONENTRY_H
#define CALLONENTRY_H

#include <QObject>

class CallOnEntry : public QObject
{
  Q_OBJECT
 public:
  explicit CallOnEntry(QString csvString, QObject *parent = nullptr);
  /*public*/ /*final*/ QString _mExternalSignal;
  /*public*/ /*final*/ QString _mSignalFacingDirection;
  /*public*/ /*final*/ QString _mSignalAspectToDisplay;
  /*public*/ /*final*/ QString _mCalledOnExternalSensor;
  /*public*/ /*final*/ QString _mExternalBlock;
  /*public*/ /*final*/ QString _mSwitchIndicator1;
  /*public*/ /*final*/ QString _mSwitchIndicator2;
  /*public*/ /*final*/ QString _mSwitchIndicator3;
  /*public*/ /*final*/ QString _mSwitchIndicator4;
  /*public*/ /*final*/ QString _mSwitchIndicator5;
  /*public*/ /*final*/ QString _mSwitchIndicator6;

 signals:

 public slots:

 private:
  /*private*/ static const  /*final*/ int EXTERNAL_SIGNAL_INDEX = 0;
  /*private*/ static const  /*final*/ int SIGNAL_FACING_DIRECTION_INDEX = 1;
  /*private*/ static const  /*final*/ int SIGNAL_ASPECT_TO_DISPLAY_INDEX = 2;
  /*private*/ static const  /*final*/ int CALLED_ON_EXTERNAL_SENSOR_INDEX = 3;
  /*private*/ static const  /*final*/ int EXTERNAL_BLOCK_INDEX = 4;
  /*private*/ static const  /*final*/ int SWITCHINDICATOR1_INDEX = 5;
  /*private*/ static const  /*final*/ int SWITCHINDICATOR2_INDEX = 6;
  /*private*/ static const  /*final*/ int SWITCHINDICATOR3_INDEX = 7;
  /*private*/ static const  /*final*/ int SWITCHINDICATOR4_INDEX = 8;
  /*private*/ static const  /*final*/ int SWITCHINDICATOR5_INDEX = 9;
  /*private*/ static const  /*final*/ int SWITCHINDICATOR6_INDEX = 10;
  /*private*/ static const  /*final*/ int ARRAY_SIZE = 11;

};

#endif // CALLONENTRY_H
