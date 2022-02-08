#ifndef ABSTRACTLIGHT_H
#define ABSTRACTLIGHT_H
#include <QList>
#include "light.h"
#include "abstractnamedbean.h"
#include "lightcontrol.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT AbstractLight :  public AbstractNamedBean, public Light
{
    Q_OBJECT
    Q_INTERFACES(Light)
public:
    //explicit AbstractLight(QObject *parent = 0);
    /*public*/ AbstractLight(QString systemName, QString userName, QObject *parent = 0);
    /*public*/ AbstractLight(QString systemName, QObject *parent = 0);
    /*public*/ bool getEnabled()override;
    /*public*/ void setEnabled(bool v) override;
    /*public*/ bool isIntensityVariable() override;
    /*public*/ void setTargetIntensity(double intensity) override;
    /*public*/ double getCurrentIntensity() override;
    /*public*/ double  getTargetIntensity() override;
    /*public*/ void setMaxIntensity(double intensity) override;
    /*public*/ double getMaxIntensity() override;
    /*public*/ void setMinIntensity(double intensity) override;
    /*public*/ double getMinIntensity() override;
    /*public*/ bool isTransitionAvailable() override;
    /*public*/ void setTransitionTime(double minutes) override;
    /*public*/ double getTransitionTime() override;
    /*public*/ bool isTransitioning() override;
    /*public*/ void setState(int newState)override;
    /*public*/ int getState()override;
    /*public*/ void activateLight()override ;
    /*public*/ void deactivateLight()override;
    /*public*/ void clearLightControls()override;
    /*public*/ void addLightControl(LightControl* c)override;
    /*public*/ QList<LightControl*> getLightControlList()override;
    /*public*/ QList<NamedBeanUsageReport*> getUsageReport(NamedBean* bean)override;

   /*public*/ QString getSystemName() const override {return AbstractNamedBean::getSystemName();}
  QObject* self() override {return (QObject*)this;}

signals:
    void propertyChange(QString propertyName, int oldState, int newState);

public slots:
private:
static Logger* log;
protected:
    /**
     *  System independent instance variables (saved between runs)
     */
    /*protected*/ QList<LightControl*> lightControlList = QList<LightControl*>();
    /*protected*/ double mMaxIntensity = 1.0;
    /*protected*/ double mMinIntensity = 0.0;

    /**
     *  System independent operational instance variables (not saved between runs)
     */
    /*protected*/ bool mActive = false;
    /*protected*/ bool mEnabled = true;
    /*protected*/ double mCurrentIntensity = 0.0;
    /*protected*/ int mState = OFF;
    /*protected*/ void updateIntensityLow(double intensity);
    /*protected*/ void updateIntensityIntermediate(double intensity);
    /*protected*/ void updateIntensityHigh(double intensity);
    /*protected*/ void notifyTargetIntensityChange(double intensity);
    /*protected*/ void notifyStateChange(int oldState, int newState);
    /*protected*/ void doNewState(int oldState, int newState);

};

#endif // ABSTRACTLIGHT_H
