#ifndef ABSTRACTMULTIMETER_H
#define ABSTRACTMULTIMETER_H

#include <QObject>
#include "multimeter.h"
#include "timertask.h"
#include "bean.h"
#include <QTimer>

class UpdateTask;
class Logger;
class AbstractMultiMeter : public Bean, public MultiMeter
{
 Q_OBJECT
 Q_INTERFACES(MultiMeter)
public:
 explicit AbstractMultiMeter(int interval, QObject *parent = nullptr);
 virtual ~AbstractMultiMeter() override {}

 /*public*/ void enable() override;
 /*public*/ void disable() override;
 /*public*/ void setCurrent(float c) override;
 /*public*/ float getCurrent() override;
 /*public*/ CurrentUnits getCurrentUnits() override;
 /*public*/ void setVoltage(float v) override;
 /*public*/ float getVoltage() override;
 /*public*/ void dispose() override;
signals:

public slots:

private:
 static Logger* log;
 QTimer* timer = nullptr;

 //private boolean is_enabled = false;
 /*private*/ UpdateTask* intervalTask = nullptr;
 /*private*/ int sleepInterval = 10000; // default to 10 second sleep interval.

protected:
 /*protected*/ float current_float = 0.0f;
 /*protected*/ float voltage_float = 0.0f;
 /*protected*/ CurrentUnits currentUnits = CurrentUnits::CURRENT_UNITS_PERCENTAGE;
 /*abstract*/ /*protected*/ virtual void requestUpdateFromLayout() =0;
 /*protected*/ void initTimer();
 void addPropertyChangeListener(PropertyChangeListener *listener){Bean::addPropertyChangeListener(listener);}
 void addPropertyChangeListener(QString propertyName, PropertyChangeListener *listener){Bean::addPropertyChangeListener(propertyName, listener);}
 QVector<PropertyChangeListener*> getPropertyChangeListeners() {return Bean::getPropertyChangeListeners();}
 QVector<PropertyChangeListener*> getPropertyChangeListeners(QString propertyName) { return Bean::getPropertyChangeListeners(propertyName);}
 void removePropertyChangeListener(PropertyChangeListener *listener){Bean::removePropertyChangeListener(listener);}
 void removePropertyChangeListener(QString propertyName, PropertyChangeListener *listener){Bean::removePropertyChangeListener(propertyName, listener);}
 friend class UpdateTask;
 friend class AmpMeterFrame;
};

/*private*/ class UpdateTask : public TimerTask
{
 Q_OBJECT
 /*private*/ bool is_enabled = false;
 AbstractMultiMeter* amm;

public:
    /*public*/ UpdateTask(AbstractMultiMeter* amm) ;
    /*public*/ void enable();
    /*public*/ void disable();

public slots:
    /*public*/ void run();

signals:

private:
 static Logger* log;
};

#endif // ABSTRACTMULTIMETER_H
