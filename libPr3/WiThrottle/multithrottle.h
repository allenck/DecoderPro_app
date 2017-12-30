#ifndef MULTITHROTTLE_H
#define MULTITHROTTLE_H

#include <QObject>

class Logger;
class ThrottleControllerListener;
class ControllerInterface;
class MultiThrottleController;
class MultiThrottle : public QObject
{
 Q_OBJECT
public:
 explicit MultiThrottle(QObject *parent = 0);
 /*public*/ MultiThrottle(QChar id, ThrottleControllerListener* tcl, ControllerInterface* ci, QObject *parent = 0);
 /*public*/ void dispose();
 /*public*/ bool addThrottleController(QString key, QString action);   //  key is address format L#### or S##
 /*public*/ bool removeThrottleController(QString key, QString action);
 /*public*/ void passActionsToControllers(QString key, QString action);
 /*public*/ void eStop();

signals:

public slots:
 /*public*/ void handleMessage(QString message);

private:
     /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(MultiThrottle.class.getName());
 /*private*/ ThrottleControllerListener* parentTCL;// = null;
 /*private*/ ControllerInterface* parentController;// = null;
 QChar whichThrottle;
 QHash<QString, MultiThrottleController*>* throttles;
 friend class DeviceServer;
};

#endif // MULTITHROTTLE_H
