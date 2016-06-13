#ifndef ABSTRACTLIGHT_H
#define ABSTRACTLIGHT_H
#include <QList>
#include "light.h"

class LightControl;
class LIBPR3SHARED_EXPORT AbstractLight : public Light
{
    Q_OBJECT
public:
    //explicit AbstractLight(QObject *parent = 0);
    /*public*/ AbstractLight(QString systemName, QString userName, QObject *parent = 0);
    /*public*/ AbstractLight(QString systemName, QObject *parent = 0);
    /*public*/ bool getEnabled();
    /*public*/ void setEnabled(bool v);
    /*public*/ bool isIntensityVariable();
    /*public*/ void setTargetIntensity(double intensity);
    /*public*/ double getCurrentIntensity();
    /*public*/ double  getTargetIntensity();
    /*public*/ void setMaxIntensity(double intensity);
    /*public*/ double getMaxIntensity();
    /*public*/ void setMinIntensity(double intensity);
    /*public*/ double getMinIntensity();
    /*public*/ bool isTransitionAvailable();
    /*public*/ void setTransitionTime(double minutes);
    /*public*/ double getTransitionTime();
    /*public*/ bool isTransitioning();
    /*public*/ void setState(int newState);
    /*public*/ int getState();
    /*public*/ void activateLight() ;
    /*public*/ void deactivateLight();
    /*public*/ void clearLightControls();
    /*public*/ void addLightControl(LightControl* c);
    /*public*/ QList<LightControl*>* getLightControlList();

signals:
    void propertyChange(QString propertyName, int oldState, int newState);

public slots:
private:
    void common();
Logger* log;
protected:
    /**
     *  System independent instance variables (saved between runs)
     */
    /*protected*/ QList<LightControl*> lightControlList;// = new QList<LightControl*>();
    /*protected*/ double mMaxIntensity;// = 1.0;
    /*protected*/ double mMinIntensity;// = 0.0;

    /**
     *  System independent operational instance variables (not saved between runs)
     */
    /*protected*/ bool mActive;// = false;
    /*protected*/ bool mEnabled;// = true;
    /*protected*/ double mCurrentIntensity;// = 0.0;
    /*protected*/ int mState;// = OFF;
    /*protected*/ void updateIntensityLow(double intensity);
    /*protected*/ void updateIntensityIntermediate(double intensity);
    /*protected*/ void updateIntensityHigh(double intensity);
    /*protected*/ void notifyTargetIntensityChange(double intensity);
    /*protected*/ void notifyStateChange(int oldState, int newState);
    /*protected*/ void doNewState(int oldState, int newState);

};

#endif // ABSTRACTLIGHT_H
