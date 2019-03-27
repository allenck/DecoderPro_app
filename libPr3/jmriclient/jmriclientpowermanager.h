#ifndef JMRICLIENTPOWERMANAGER_H
#define JMRICLIENTPOWERMANAGER_H
#include "powermanager.h"
#include "propertychangesupport.h"

class AbstractMRListener;
class JMRIClientReply;
class JMRIClientMessage;
class JMRIClientSystemConnectionMemo;
class JMRIClientTrafficController;
class JMRIClientPowerManager : public PowerManager
{
public:
 /*public*/ JMRIClientPowerManager(JMRIClientSystemConnectionMemo* memo, QObject* parent = nullptr);
 /*public*/ QString getUserName();
 /*public*/ void setPower(int v) throw (JmriException);
 /*public*/ int getPower();
 /*public*/ void dispose() throw (JmriException);
 // to hear of changes
 PropertyChangeSupport* pcs;// = new java.beans.PropertyChangeSupport(this);
 /*public*/  void addPropertyChangeListener(PropertyChangeListener* l);
 /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);
 /*public*/ void message(JMRIClientMessage* m);
 /*public*/ void reply(JMRIClientReply* m);


private:
 /*private*/ JMRIClientTrafficController* tc = nullptr;
 /*private*/ JMRIClientSystemConnectionMemo* memo = nullptr;
 int power = UNKNOWN;
 /*private*/ void checkTC() throw (JmriException);

protected:
 /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);


};

#endif // JMRICLIENTPOWERMANAGER_H
