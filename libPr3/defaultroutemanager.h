#ifndef DEFAULTROUTEMANAGER_H
#define DEFAULTROUTEMANAGER_H
#include "routemanager.h"
#include "route.h"
#include "defaultroute.h"
#include "decimalformat.h"

class LIBPR3SHARED_EXPORT DefaultRouteManager : public RouteManager //, public RouteManager, public Route
{
    Q_OBJECT
public:
    explicit DefaultRouteManager(QObject *parent = 0);
    /*public*/ int getXMLOrder();
    /*public*/ QString getSystemPrefix();
    /*public*/ char typeLetter();

    /**
     * Method to provide a  Route
     * whether or not is already exists.
     */
    /*public*/ Route* provideRoute(QString systemName, QString userName);
    /*public*/ Route* newRoute(QString userName);

    /**
     * Remove an existing route. Route must have been deactivated
     * before invoking this.
     */
    /*public*/ void deleteRoute(Route* r) ;
    /**
     * Method to get an existing Route.  First looks up assuming that
     *      name is a User Name.  If this fails looks up assuming
     *      that name is a System Name.  If both fail, returns NULL.
     */
    /*public*/ Route* getRoute(QString name);
    /*public*/ Route* getBySystemName(QString name) ;
    /*public*/ Route* getByUserName(QString key);
    static /*public*/ DefaultRouteManager* instance();
    int getLastAutoRouteRef();

signals:
 void newRouteCreated(Route*);
public slots:
private:
 DecimalFormat* paddedNumber;
 static DefaultRouteManager* _instance;// = NULL;

 int lastAutoRouteRef;// = 0;
 QObject *parent;
 Logger* log;
};

#endif // DEFAULTROUTEMANAGER_H
