#ifndef FLAVORMAP_H
#define FLAVORMAP_H
#include <QObject>
#include "dataflavor.h"
#include <QMap>

/**
 * A two-way Map between "natives" (Strings), which correspond to platform-
 * specific data formats, and "flavors" (DataFlavors), which correspond to
 * platform-independent MIME types. FlavorMaps need not be symmetric, but
 * typically are.
 *
 *
 * @since 1.2
 */
/*public*/ /*interface*/ class FlavorMap : public QObject
{

    /**
     * Returns a <code>Map</code> of the specified <code>DataFlavor</code>s to
     * their corresponding <code>String</code> native. The returned
     * <code>Map</code> is a modifiable copy of this <code>FlavorMap</code>'s
     * internal data. Client code is free to modify the <code>Map</code>
     * without affecting this object.
     *
     * @param flavors an array of <code>DataFlavor</code>s which will be the
     *        key set of the returned <code>Map</code>. If <code>null</code> is
     *        specified, a mapping of all <code>DataFlavor</code>s currently
     *        known to this <code>FlavorMap</code> to their corresponding
     *        <code>String</code> natives will be returned.
     * @return a <code>java.util.Map</code> of <code>DataFlavor</code>s to
     *         <code>String</code> natives
     */
    QMap<DataFlavor*,QString> getNativesForFlavors(QList<DataFlavor*> flavors);

    /**
     * Returns a <code>Map</code> of the specified <code>String</code> natives
     * to their corresponding <code>DataFlavor</code>. The returned
     * <code>Map</code> is a modifiable copy of this <code>FlavorMap</code>'s
     * internal data. Client code is free to modify the <code>Map</code>
     * without affecting this object.
     *
     * @param natives an array of <code>String</code>s which will be the
     *        key set of the returned <code>Map</code>. If <code>null</code> is
     *        specified, a mapping of all <code>String</code> natives currently
     *        known to this <code>FlavorMap</code> to their corresponding
     *        <code>DataFlavor</code>s will be returned.
     * @return a <code>java.util.Map</code> of <code>String</code> natives to
     *         <code>DataFlavor</code>s
     */
    QMap<QString,DataFlavor*> getFlavorsForNatives(QStringList natives);
};
#endif // FLAVORMAP_H
