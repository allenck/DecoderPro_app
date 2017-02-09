#ifndef COMPONENTPEER_H
#define COMPONENTPEER_H
#include <QObject>

/**
 * The peer interface for {@link Component}. This is the top level peer
 * interface for widgets and defines the bulk of methods for AWT component
 * peers. Most component peers have to implement this interface (via one
 * of the subinterfaces), except menu components, which implement
 * {@link MenuComponentPeer}.
 *
 * The peer interfaces are intended only for use in porting
 * the AWT. They are not intended for use by application
 * developers, and developers should not implement peers
 * nor invoke any of the peer methods directly on the peer
 * instances.
 */
/*public*/ /*interface*/ class ComponentPeer : public QObject
{
    Q_OBJECT
 public:
    ComponentPeer() {}

};

#endif // COMPONENTPEER_H
