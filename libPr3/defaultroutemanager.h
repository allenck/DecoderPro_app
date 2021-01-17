#ifndef DEFAULTROUTEMANAGER_H
#define DEFAULTROUTEMANAGER_H

#include "abstractroutemanager.h"
#include "route.h"
#include "defaultroute.h"
#include "decimalformat.h"

class LIBPR3SHARED_EXPORT DefaultRouteManager : public AbstractRouteManager //, public RouteManager, public Route
{
    Q_OBJECT
public:
    /*Q_INVOKABLE*/ explicit DefaultRouteManager(InternalSystemConnectionMemo* memo, QObject *parent = 0);
    ~DefaultRouteManager() {}
    DefaultRouteManager(const DefaultRouteManager& other) : AbstractRouteManager(other.memo) {}
    /*public*/ int getXMLOrder() const override;
//    /*public*/ QString getSystemPrefix() const override;
    /*public*/ char typeLetter() const override;

    /**
     * Method to provide a  Route
     * whether or not is already exists.
     */
    /*public*/ Route* provideRoute(QString systemName, QString userName)const override;
    /*public*/ Route* newRoute(QString userName) override;

    /**
     * Remove an existing route. Route must have been deactivated
     * before invoking this.
     */
    /*public*/ void deleteRoute(Route* r)  override;
    /**
     * Method to get an existing Route.  First looks up assuming that
     *      name is a User Name.  If this fails looks up assuming
     *      that name is a System Name.  If both fail, returns NULL.
     */
    /*public*/ Route* getRoute(QString name) override;
//    /*public*/ Route* getBySystemName(QString name)  override;
//    /*public*/ Route* getByUserName(QString key) override;
    QT_DEPRECATED static /*public*/ DefaultRouteManager* instance();
//    int getLastAutoRouteRef();
    /*public*/ Route* provide(QString name) throw (IllegalArgumentException) override;
    /*public*/ QString getBeanTypeHandled(bool plural) const override;
    /*public*/ QString getNamedBeanClass()const override;


signals:
 //void newRouteCreated(Route*);
public slots:
private:
 DecimalFormat* paddedNumber;

 //int lastAutoRouteRef;// = 0;
 QObject *parent;
 Logger* log;
};
//Q_DECLARE_METATYPE(DefaultRouteManager)
#endif // DEFAULTROUTEMANAGER_H
