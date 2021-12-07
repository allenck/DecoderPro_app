#ifndef ABSTRACTVARIABLELIGHT_H
#define ABSTRACTVARIABLELIGHT_H
#include <QDateTime>
#include <QTimer>
#include "timebase.h"
#include "abstractlight.h"
#include "variablelight.h"
class PropertyChangeListener;
class LIBPR3SHARED_EXPORT AbstractVariableLight : /*public AbstractLight,*/ public VariableLight
{
    Q_OBJECT
  //Q_INTERFACES(VariableLight);
public:
    //explicit AbstractVariableLight(QObject *parent = 0);
    /*public*/ AbstractVariableLight(QString systemName, QString userName, QObject *parent = 0);
    /*public*/ AbstractVariableLight(QString systemName, QObject *parent = 0);
    /*public*/ void setState(int newState) override;
    /*public*/ void setTargetIntensity(double intensity) override;
    /*public*/ bool isIntensityVariable() override;
    /*public*/ bool isTransitionAvailable() override;
    /*public*/ void setTransitionTime(double minutes) override;
    /*public*/ double getTransitionTime() override;
    /*public*/ bool isTransitioning() override;
    /*public*/ double getCurrentIntensity() override;
    /*public*/ double getTargetIntensity() override;
    /*public*/ void setCommandedAnalogValue(double value) throw (JmriException) override;
    /*public*/ double getMinIntensity() override;
    /*public*/ void setMinIntensity(double intensity) override;
    /*public*/ double getMaxIntensity() override;
    /*public*/ void setMaxIntensity(double intensity) override;
    /*public*/ double getState(double v);
    /*public*/ void setState(double newState) throw (JmriException) override;
    /*public*/ double getResolution() override;
    /*public*/ double getCommandedAnalogValue() override;
    /*public*/ double getMin() override;
    /*public*/ double getMax() override;
    /*public*/ AbsoluteOrRelative::TYPE getAbsoluteOrRelative() override;
    QObject* self() override {return this;}
    //QString getSystemName() const override{return AbstractNamedBean::getSystemName();}

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
