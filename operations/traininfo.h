#ifndef TRAININFO_H
#define TRAININFO_H

#include <QObject>

class Sensor;
class TrainInfo : public QObject
{
 Q_OBJECT
public:
 explicit TrainInfo(QObject *parent = 0);

signals:

public slots:
private:
 // instance variables for both manual and automatic operation
 /*private*/ QString transitName; // =  "";
 /*private*/ QString trainName; // =  "";
 /*private*/ QString dccAddress; // =  "";
 /*private*/ bool trainInTransit; // =  false;
 /*private*/ QString startBlockName; // =  "";
 /*private*/ QString destinationBlockName; // =  "";
 /*private*/ bool trainFromRoster; // =  true;
 /*private*/ bool trainFromTrains; // =  false;
 /*private*/ bool trainFromUser; // =  false;
 /*private*/ int priority; // =  5;
 /*private*/ bool autoRun; // =  false;
 /*private*/ bool resetWhenDone; // =  false;
 /*private*/ bool allocateAllTheWay; // =  false;
 /*private*/ bool reverseAtEnd; // =  false;
 /*private*/ int delayedStart; // =  ActiveTrain.NODELAY;
 /*private*/ int delayedRestart; // =  ActiveTrain.NODELAY;
 /*private*/ int departureTimeHr; // =  8;
 /*private*/ int departureTimeMin; // =  00;
 /*private*/ QString delaySensorName; // =  null;
 /*private*/ QString restartSensorName; // =  null;
 /*private*/ int restartDelayMin; // =  0;
 /*private*/ QString trainType; // =  "";
 /*private*/ bool terminateWhenDone; // =  false;
 /*private*/ bool loadAtStartup; // =  false;

 // instance variables for automatic operation
 /*private*/ float speedFactor; // =  1.0f;
 /*private*/ float maxSpeed; // =  0.6f;
 /*private*/ QString rampRate; // =  rb.getString("RAMP_NONE");
 /*private*/ bool resistanceWheels; // =  true;
 /*private*/ bool runInReverse; // =  false;
 /*private*/ bool soundDecoder; // =  false;
 /*private*/ float maxTrainLength; // =  200.0f;

protected:
 /*protected*/ void setTransitName(QString s);
 /*protected*/ QString getTransitName() ;
 /*protected*/ void setTrainName(QString s);
 /*protected*/ QString getTrainName();
 /*protected*/ void setDCCAddress(QString s);
 /*protected*/ QString getDCCAddress();
 /*protected*/ void setTrainInTransit(bool b);
 /*protected*/ bool getTrainInTransit();
 /*protected*/ void setStartBlockName(QString s);
 /*protected*/ QString getStartBlockName();
 /*protected*/ void setDestinationBlockName(QString s);
 /*protected*/ QString getDestinationBlockName();
 /*protected*/ void setTrainFromRoster(bool b);
 /*protected*/ bool getTrainFromRoster() ;
 /*protected*/ void setTrainFromTrains(bool b);
 /*protected*/ bool getTrainFromTrains();
 /*protected*/ void setTrainFromUser(bool b);
 /*protected*/ bool getTrainFromUser();
 /*protected*/ void setTerminateWhenDone(bool b);
 /*protected*/ bool getTerminateWhenDone();
 /*protected*/ void setPriority(int pri) ;
 /*protected*/ int getPriority();
 /*protected*/ void setAutoRun(bool b);
 /*protected*/ bool getAutoRun();
 /*protected*/ void setResetWhenDone(bool b);
 /*protected*/ bool getResetWhenDone() ;
 /*protected*/ void setAllocateAllTheWay(bool b);
 /*protected*/ bool getAllocateAllTheWay();
 /*protected*/ void setReverseAtEnd(bool b);
 /*protected*/ bool getReverseAtEnd();
 /*protected*/ void setDelayedStart(int ds) ;
 /*protected*/ int getDelayedStart();
 /*protected*/ void setDepartureTimeHr(int hr);
 /*protected*/ int getDepartureTimeHr() ;
 /*protected*/ void setDepartureTimeMin(int min) ;
 /*protected*/ int getDepartureTimeMin();
 /*protected*/ void setDelaySensorName(QString sen);
 /*protected*/ QString getDelaySensorName();
 /*protected*/ Sensor* getDelaySensor();
 /*protected*/ void setTrainType(QString s);
 /*protected*/ QString getTrainType() ;
 /*protected*/ void setDelayedRestart(int ds);
 /*protected*/ int getDelayedRestart();
 /*protected*/ void setRestartSensorName(QString sen) ;
 /*protected*/ QString getRestartSensorName();
 /*protected*/ Sensor* getRestartSensor();
 /*protected*/ void setRestartDelayMin(int s);
 /*protected*/ int getRestartDelayMin();
 /*protected*/ bool getLoadAtStartup();
 /*protected*/ void setLoadAtStartup(bool loadAtStartup);
 /*protected*/ void setSpeedFactor(float f) ;
 /*protected*/ float getSpeedFactor();
 /*protected*/ void setMaxSpeed(float f);
 /*protected*/ float getMaxSpeed();
 /*protected*/ void setRampRate(QString s);
 /*protected*/ QString getRampRate();
 /*protected*/ void setResistanceWheels(bool b) ;
 /*protected*/ bool getResistanceWheels();
 /*protected*/ void setRunInReverse(bool b);
 /*protected*/ bool getRunInReverse() ;
 /*protected*/ void setSoundDecoder(bool b);
 /*protected*/ bool getSoundDecoder();
 /*protected*/ void setMaxTrainLength(float f) ;
 /*protected*/ float getMaxTrainLength();

 friend class TrainInfoFile;
 friend class DispatcherFrame;
 friend class ActivateTrainFrame;
};

#endif // TRAININFO_H
