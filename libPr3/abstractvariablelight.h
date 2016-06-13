#ifndef ABSTRACTVARIABLELIGHT_H
#define ABSTRACTVARIABLELIGHT_H
#include <QDateTime>
#include <QTimer>
#include "timebase.h"
#include "abstractlight.h"

class PropertyChangeListener;
class LIBPR3SHARED_EXPORT AbstractVariableLight : public AbstractLight
{
    Q_OBJECT
public:
    //explicit AbstractVariableLight(QObject *parent = 0);
    /*public*/ AbstractVariableLight(QString systemName, QString userName, QObject *parent = 0);
    /*public*/ AbstractVariableLight(QString systemName, QObject *parent = 0);
    /*public*/ void setState(int newState);
    /*public*/ void setTargetIntensity(double intensity);
    /*public*/ bool isIntensityVariable();
    /*public*/ bool isTransitionAvailable();
    /*public*/ void setTransitionTime(double minutes);
    /*public*/ double getTransitionTime();
    /*public*/ bool isTransitioning();

signals:

public slots:
private:
 void init();
 Logger* log;
 /*private*/ void initClocks();

private slots:
 void newInternalMinute();


protected:
/**
 * Variables needed for saved values
 */
/*protected*/ double mTransitionDuration;// = 0.0;

/**
 * Variables needed but not saved to files/panels
 */
/*protected*/ double mTransitionTargetIntensity;// = 0.0;
/*protected*/ QDateTime* mLastTransitionDate;// = NULL;
/*protected*/ long mNextTransitionTs;// = 0;
/*protected*/ Timebase* internalClock;// = NULL;
/*protected*/ QTimer* alarmSyncUpdate;// = NULL;
/*protected*/ PropertyChangeListener* minuteChangeListener;// = NULL;
/*protected*/ void startTransition(double intensity);
virtual /*abstract*/ /*protected*/ void sendIntensity(double intensity);
virtual /*abstract*/ /*protected*/ void sendOnOffCommand(int newState);
// /*protected*/ void newInternalMinute(); // see slots!
 virtual /*abstract*/ /*protected*/ int getNumberOfSteps();
 /*protected*/ void notifyTargetIntensityChange(double intensity);
 /*protected*/ void forwardCommandChangeToLayout(int s);

};

#endif // ABSTRACTVARIABLELIGHT_H
