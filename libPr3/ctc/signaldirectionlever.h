#ifndef SIGNALDIRECTIONLEVER_H
#define SIGNALDIRECTIONLEVER_H

#include <QObject>
#include "nbhsensor.h"

class LNR_NBHSensors;
class SignalDirectionLever : public QObject
{
  Q_OBJECT
 public:
  /*public*/ /*static*/ class LNR_NBHSensors {   // L = Left, N = Normal, R = Right.
  public:
      /*public*/ /*final*/ NBHSensor* _mLeftSensor;
      /*public*/ /*final*/ NBHSensor* _mNormalSensor;
      /*public*/ /*final*/ NBHSensor* _mRightSensor;
      /*public*/ LNR_NBHSensors(NBHSensor* leftSensor, NBHSensor* normalSensor, NBHSensor* rightSensor, QObject* parent = nullptr) {
          _mLeftSensor = leftSensor;
          _mNormalSensor = normalSensor;
          _mRightSensor = rightSensor;
      }
  };
  /*public*/ SignalDirectionLever(QString userIdentifier, NBHSensor* leftSensor, NBHSensor* normalSensor, NBHSensor* rightSensor, QObject* parent = nullptr);
  /*public*/ void removeAllListeners();
  /*public*/ LNR_NBHSensors* getLevers();

  /*public*/ int getPresentSignalDirectionLeverState();


 signals:

 public slots:

 private:
  /*private*/ NBHSensor* _mLeftSensor;
  /*private*/ NBHSensor* _mNormalSensor;
  /*private*/ NBHSensor* _mRightSensor;

};

#endif // SIGNALDIRECTIONLEVER_H
