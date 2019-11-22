#ifndef RAMPDATA_H
#define RAMPDATA_H

#include <QObject>

class RampData : public QObject
{
    Q_OBJECT
public:
    RampData(float throttleIncre, int timeIncre,QObject *parent = nullptr);
    static float INCRE_RATE;// = 1.10f;  // multiplier to increase throttle increments

signals:

public slots:
private:
    /*private*/ int _timeInterval;
    /*private*/ float _throttleInterval;
    /*private*/ QList<float> _settings;
    /*private*/ float _rampLength;
    /*private*/ bool _upRamp;
protected:
    /*protected*/ bool isUpRamp();
    /*protected*/ void makeThrottleSettings(float fromSet, float toSet);
    /*protected*/ void setRampLength(float rampLength);
    /*protected*/ float getRampLength();
    /*protected*/ float getMaxSpeed() ;
    /*protected*/ QListIterator<float> speedIterator(bool up);
    /*protected*/ int getRampTimeIncrement();
friend class NXFrame;
friend class SpeedUtil;
friend class ThrottleRamp;
friend class Warrant;
};

#endif // RAMPDATA_H
