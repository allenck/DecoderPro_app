#ifndef DEFAULTPOWERMANAGER_H
#define DEFAULTPOWERMANAGER_H
#include "powermanager.h"

class PropertyChangeSupport;
class DefaultPowerManager : public PowerManager
{
public:
 DefaultPowerManager();
 /*public*/ void setPower(int v) ;
 /*public*/ QString getUserName() ;
 /*public*/ int getPower();
 /*public*/ void dispose();
 /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
 /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);

private:
 // to hear of changes
// PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
 int power;// = UNKNOWN;
protected:
 /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);

};

#endif // DEFAULTPOWERMANAGER_H
