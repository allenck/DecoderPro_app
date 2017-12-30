#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include <QObject>
#include <QStringList>

class Manager;
class ControllerInterface;
class AbstractController : public QObject
{
 Q_OBJECT
public:
 explicit AbstractController(QObject *parent = 0);
 /*public*/ void buildList(Manager* manager);
 /*public*/ void filterList();
 /*public*/ void checkCanBuildList();
 /*public*/ void addControllerListener(ControllerInterface* listener);
 /*public*/ void removeControllerListener(ControllerInterface* listener);

signals:

public slots:

private:
 QVector<ControllerInterface*>* listeners;// = NULL;
 QStringList sysNameList;// = NULL;

 bool isValid;// = false;
 bool canBuildList;// = true;

 /**
  * isValid is used to indicate if the Controller is created. If false, we
  * can NULL the controller and reduce overhead.
  *
  * @return isValid
  */
 /*abstract*/ inline virtual  bool verifyCreation() {return false;}

 /**
  * Break down a message and use it.
  *
  */
 /*abstract*/ inline virtual  void handleMessage(QString /*message*/) {}

 /**
  * Register as listener of NamedBeans to be updated of changes.
  */
 /*abstract*/ inline virtual  void _register() {}

 /**
  * Deregister as listener of NamedBeans
  */
 /*abstract*/ inline virtual  void deregister() {}

 friend class TrackPowerController;
 friend class TurnoutController;
 friend class RouteController;
 friend class ConsistController;
 friend class DeviceServer;
};

#endif // ABSTRACTCONTROLLER_H
