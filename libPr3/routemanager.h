#ifndef ROUTEMANAGER_H
#define ROUTEMANAGER_H

#include "abstractmanager.h"
#include "route.h"
#include "libPr3_global.h"
/**
 * Interface for obtaining Routes
 * <P>
 * This doesn't have a "new" method, since Routes are
 * separately implemented, instead of being system-specific.
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author      Dave Duchamp Copyright (C) 2004
 * @version	$Revision: 17977 $
 */

class LIBPR3SHARED_EXPORT RouteManager : public AbstractManager
{
    Q_OBJECT
public:
    //explicit RouteManager(QObject *parent = 0);
 RouteManager(QObject* parent = nullptr) : AbstractManager(parent) {}
 RouteManager(SystemConnectionMemo* memo, QObject* parent = nullptr) : AbstractManager(memo, parent) {}
    // to free resources when no longer used
 /*public*/ void dispose() override {}

    /**
     * Method to create a new Route if the route does not exist
     *   Returns null if a Route with the same systemName or userName
     *       already exists, or if there is trouble creating a new Route.
     */
 /*public*/ virtual Route* provideRoute(QString /*systemName*/, QString /*userName*/) const {return nullptr;}

    /**
     * For use with User GUI, to allow the auto generation of systemNames,
     * where the user can optionally supply a username.
     * Method to create a new Route if the route does not exist
     *   Returns null if a Route with the same userName
     *       already exists, or if there is trouble creating a new Route.
     */
    /*public*/ virtual Route* newRoute(QString /*userName*/)  {return nullptr;}

    /**
     * Locate via user name, then system name if needed.
     * Does not create a new one if nothing found
     *
     * @param name
     * @return null if no match found
     */
    /*public*/ virtual Route* getRoute(QString /*name*/) {return nullptr;}

    virtual /*public*/ Route* getByUserName(QString /*s*/) const =0;
    virtual /*public*/ Route* getBySystemName(QString /*s*/) const =0;

    /**
     * Get a list of all Route system names.
     */
 // /*public*/ virtual QStringList getSystemNameList() {return QStringList();}

    /**
     * Delete Route by removing it from
     * the manager.
     * The Route must first be deactivated so it
     * stops processing.
     */
    virtual void deleteRoute(Route* /*r*/) {}

    virtual /*public*/ Route* provide(QString name) throw (IllegalArgumentException)=0;

signals:

public slots:

};

#endif // ROUTEMANAGER_H


