#ifndef POWERMANAGER_H
#define POWERMANAGER_H

#include <QObject>
#include <QString>
#include "libPr3_global.h"
#include "propertychangelistener.h"

class LIBPR3SHARED_EXPORT PowerManager : public QObject
{
    Q_OBJECT
 public:
    explicit PowerManager(QObject *parent = 0);
 ~PowerManager() {}
 PowerManager(const PowerManager&) :QObject() {}
    const static int UNKNOWN; //= 0;
    const static int ON; //     = 2;
    const static int OFF; //     = 4;

    virtual void 	setPower(int /*v*/) {} // 	throws JmriException;
    virtual int	 	getPower() {return 0;} //  	throws JmriException;

    // to free resources when no longer used
    virtual void dispose() {} // throws JmriException;

    // to hear of changes
    virtual void addPropertyChangeListener(PropertyChangeListener* /*p*/) {}
    virtual void removePropertyChangeListener(PropertyChangeListener* /*p*/) {}

    virtual QString getUserName() {return "";}
 signals:
    void propertyChange(PropertyChangeEvent*);
 public slots:
private:
    
};
Q_DECLARE_METATYPE(PowerManager)
#endif // POWERMANAGER_H
