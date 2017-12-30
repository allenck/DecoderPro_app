#ifndef WITHROTTLEMANAGER_H
#define WITHROTTLEMANAGER_H

#include <QObject>

class TrackPowerController;
class TurnoutController;
class RouteController;
class ConsistController;
class WiThrottlePreferences;
class WiThrottleManager : public QObject
{
 Q_OBJECT
public:
 explicit WiThrottleManager(QObject *parent = 0);
 static /*public*/ TrackPowerController* trackPowerControllerInstance();
 static /*public*/ TurnoutController* turnoutControllerInstance();
 static /*public*/ RouteController* routeControllerInstance() ;
 static /*public*/ ConsistController* consistControllerInstance();
 static /*public*/ WiThrottlePreferences* withrottlePreferencesInstance();

signals:

public slots:

private:
  static /*private*/ WiThrottleManager* instance();
 /*private*/ TrackPowerController* trackPowerController;// = null;
 /*private*/ TurnoutController* turnoutController;// = null;
 /*private*/ RouteController* routeController;// = null;
 /*private*/ ConsistController* consistController;// = null;

 /*private*/ WiThrottlePreferences* withrottlePreferences;// = null;
 static /*private*/ WiThrottleManager* root;

};

#endif // WITHROTTLEMANAGER_H
