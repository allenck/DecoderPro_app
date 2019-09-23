#ifndef LNSENSOR_H
#define LNSENSOR_H
#include "abstractsensor.h"
#include "lntrafficcontroller.h"
#include "lnsensoraddress.h"
#include "lnpacketizer.h"

class LIBPR3SHARED_EXPORT LnSensor : public AbstractSensor
{
 Q_OBJECT
public:
//    explicit LnSensor(QObject *parent = 0);
    LnSensor(QString systemName, QString userName, LnTrafficController* tc =NULL, QString prefix="L",QObject *parent = 0);
    LnSensor(QString systemName, LnTrafficController* tc = NULL, QString prefix="L",QObject *parent = 0);
    /**
     * request an update on status by sending a loconet message
     */
    void requestUpdateFromLayout() const;
    /**
     * User request to set the state, which means that we broadcast that to
     * all listeners by putting it out on LocoNet.
     * In turn, the code in this class should use setOwnState to handle
     * internal sets and bean notifies.
     * @param s
     * @throws JmriException
     */
    void setKnownState(int s); // throws jmri.JmriException
    /**
     * implementing classes will typically have a function/listener to get
     * updates from the layout, which will then call
     *      public void firePropertyChange(QString propertyName,
     *      					Object oldValue,
     *                                          Object newValue)
     * _once_ if anything has changed state (or set the commanded state directly)
     * @param l
     */
    void dispose();
    /*public*/ void messageFromManager(LocoNetMessage* l);

signals:
    
public slots:
    void message(LocoNetMessage* l);

private:
 LnSensorAddress* a;
 LnTrafficController* tc;
 /**
  * Common initialization for both constructors
  */
 void init(QString systemName, QString prefix);
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger(LnSensor.class);

};

#endif // LNSENSOR_H
