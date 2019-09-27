#ifndef SPEEDSTEPMODE_H
#define SPEEDSTEPMODE_H

#include <QObject>

class SpeedStepMode : public QObject
{
 Q_OBJECT
public:
 enum SSMODDES
 {
  UNKNOWN = 0, //("unknown", 1, 0.0f),
  // NMRA DCC standard speed step modes.
  NMRA_DCC_128 =126, //("128", 126), // Remember there are only 126 non-stop values in 128 speed.
  NMRA_DCC_28 = 28, //("28", 28),
  NMRA_DCC_27 = 27, //("27", 27),
  NMRA_DCC_14 = 14, //("14", 14),
  // Non-DCC speed step modes.
  MOTOROLA_28 = 28, //("motorola_28", 28), // Motorola 28 speed step mode.
  TMCC_32 = 32, //("tmcc_32", 32), // Lionel TMCC 32 speed step mode.
  INCREMENTAL = 1 //("incremental", 1, 1.0f);
 };
 /*public*/ /*final*/ QString name;
 /*public*/ /*final*/ int numSteps;
 /*public*/ /*final*/ float increment;

 explicit SpeedStepMode(QObject *parent = nullptr);
 SpeedStepMode(QString name, int numSteps, QObject *parent = nullptr);
 SpeedStepMode(QString name, int numSteps, float increment, QObject *parent = nullptr);
 static /*public*/ SpeedStepMode::SSMODDES getByName(QString name);

signals:

public slots:
private:
 void common(QString name, int numSteps, float increment);


};

#endif // SPEEDSTEPMODE_H
