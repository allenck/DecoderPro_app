#ifndef SIGNALMASTREPEATER_H
#define SIGNALMASTREPEATER_H

#include <QObject>
#include "logger.h"
#include "namedbeanhandle.h"

class NamedBeanHandleManager;
class SignalMast;
class PropertyChangeEvent;
class LIBPR3SHARED_EXPORT SignalMastRepeater : public QObject
{
    Q_OBJECT
public:
    //explicit SignalMastRepeater(QObject *parent = 0);
 enum repeaterModes
 {
     /*public*/ /*final*/ /*static*/ /*int*/ BOTHWAY = 0x00,
     /*public*/ /*final*/ /*static*/ /*int*/ MASTERTOSLAVE = 0x01,
     /*public*/ /*final*/ /*static*/ /*int*/ SLAVETOMASTER = 0x02
 };
 /*public*/ SignalMastRepeater(SignalMast* master, SignalMast* slave, QObject *parent = 0);
 /*public*/ SignalMastRepeater(QString master, QString slave, QObject *parent = 0);
 /*public*/ SignalMast* getMasterMast();
 /*public*/ SignalMast* getSlaveMast();
 /*public*/ QString getMasterMastName();
 /*public*/ QString getSlaveMastName();
 /*public*/ int getDirection();
 /*public*/ void setDirection(int dir);
 /*public*/ void setEnabled(bool en);
 /*public*/ bool getEnabled();
 /*public*/ void initialise();
 /*public*/ void dispose();

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e); // SLOT[]

private:
 bool _enabled;// = true;
 int _direction;// = BOTHWAY;
 void init();
 Logger* log;
 bool disposed;// = false;
 void updateStatus(SignalMast* mastFrom, SignalMast* mastTo);

protected:
 /*protected*/ NamedBeanHandleManager* nbhm;// = InstanceManager::getDefault("NamedBeanHandleManager");

 /*protected*/ NamedBeanHandle<SignalMast*>* _master;
 /*protected*/ NamedBeanHandle<SignalMast*>* _slave;

};

#endif // SIGNALMASTREPEATER_H
