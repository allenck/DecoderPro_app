#ifndef ABSTRACTPOWERSERVER_H
#define ABSTRACTPOWERSERVER_H

#include <QObject>
#include "exceptions.h"

class PropertyChangeEvent;
class PowerManager;
class Logger;
class AbstractPowerServer : public QObject
{
 Q_OBJECT
public:
 explicit AbstractPowerServer(QObject *parent = nullptr);
 /*public*/ void setOnStatus();
 /*public*/ void setOffStatus();
 /*public*/ void dispose();

 /*abstract*/ virtual /*public*/ void sendStatus(int /*Status*/) /*throw (IOException)*/ {}

 /*abstract*/ virtual /*public*/ void sendErrorStatus() /*throw (IOException)*/ {}

 /*abstract*/ virtual /*public*/ void parseStatus(QString /*statusString*/) /*throw (JmriException, IOException)*/ {}

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* ev);

private:
 static Logger* log;

protected:
 /*protected*/ bool mgrOK();
 /*protected*/ PowerManager* p = nullptr;

};

#endif // ABSTRACTPOWERSERVER_H
