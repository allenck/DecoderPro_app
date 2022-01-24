#ifndef POWERMANAGER_H
#define POWERMANAGER_H

#include <QObject>
#include <QString>
#include "libPr3_global.h"
#include "propertychangelistener.h"
#include "swingpropertychangesupport.h"

class LIBPR3SHARED_EXPORT PowerManager : public QObject
{
 //Q_OBJECT
 public:
    inline explicit PowerManager(QObject *parent = 0) : QObject(parent) {}
 ~PowerManager() {}
 PowerManager(const PowerManager&) :QObject() {}
 enum STATES
 {
    UNKNOWN = 0,
    ON     = 2,
    OFF    = 4,
    IDLE = 0x08 // not supported by some connection types
 };
 Q_ENUM(STATES)
 static /*final*/ QString POWER;// = "Power"; // NOI18N


    virtual void 	setPower(int /*v*/) {} // 	throws JmriException;
    virtual int	 	getPower() {return 0;} //  	throws JmriException;

    // to free resources when no longer used
    virtual void dispose() {} // throws JmriException;

    // to hear of changes
    virtual void addPropertyChangeListener(PropertyChangeListener* /*p*/) {}
    virtual void removePropertyChangeListener(PropertyChangeListener* /*p*/) {}

    virtual QString getUserName() {return "";}
 SwingPropertyChangeSupport* pcs =nullptr;// = new SwingPropertyChangeSupport(this, nullptr);
 /*public*/ /*default*/ virtual bool implementsIdle();


 signals:
 public slots:
 inline void virtual propertyChange(PropertyChangeEvent*) {}

private:
    
};
Q_DECLARE_METATYPE(PowerManager)
#endif // POWERMANAGER_H
