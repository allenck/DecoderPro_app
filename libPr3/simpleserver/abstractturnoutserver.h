#ifndef ABSTRACTTURNOUTSERVER_H
#define ABSTRACTTURNOUTSERVER_H

#include <QObject>
#include "propertychangelistener.h"
#include "exceptions.h"

class SSTurnoutListener;
class Turnout;
class Logger;
class AbstractTurnoutServer : public QObject
{
 Q_OBJECT
public:
 explicit AbstractTurnoutServer(QObject *parent = nullptr);
 /*abstract*/ virtual /*public*/ void sendStatus(QString turnoutName, int Status) /*throw (IOException)*/ {}

 /*abstract*/ virtual  /*public*/ void sendErrorStatus(QString turnoutName) /*throw (IOException)*/ {}

 /*abstract*/ virtual  /*public*/ void parseStatus(QString statusString) /*throw (JmriException, IOException)*/ {}
 /*public*/ Turnout* initTurnout(QString turnoutName) /*throw (IllegalArgumentException)*/;
 /*public*/ void closeTurnout(QString turnoutName);
 /*public*/ void throwTurnout(QString turnoutName);
 /*public*/ void dispose();

signals:

public slots:

private:
 static Logger* log;
 friend class SSTurnoutListener;
protected:
 /*protected*/ /*final*/ QMap<QString, SSTurnoutListener*> turnouts;
 /*synchronized*/ /*protected*/ void addTurnoutToList(QString turnoutName) ;
 /*synchronized*/ /*protected*/ void removeTurnoutFromList(QString turnoutName);
 /*protected*/ SSTurnoutListener* getListener(QString turnoutName);

};

/*protected*/ class SSTurnoutListener : public QObject,public PropertyChangeListener {
Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 AbstractTurnoutServer* abstractTurnoutServer;
 QString name;// = null;
 Turnout* turnout = nullptr;

public:
    /*protected*/ SSTurnoutListener(QString turnoutName, AbstractTurnoutServer* abstractTurnoutServer);
 QObject* self() override{return (QObject*)this;}
public slots:
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e);
};
#endif // ABSTRACTTURNOUTSERVER_H
