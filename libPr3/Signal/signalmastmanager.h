#ifndef SIGNALMASTMANAGER_H
#define SIGNALMASTMANAGER_H
#include "signalmast.h"
#include "abstractmanager.h"

/**
 * Interface for obtaining signal masts.
 * <P>
 * This doesn't have a "new" method, as SignalMasts
 * are separately implemented, instead of being system-specific.
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
 * @author      Bob Jacobsen Copyright (C) 2009
 * @version	$Revision: 19910 $
 */
/*public*/ /*interface*/ class LIBPR3SHARED_EXPORT SignalMastManager : public AbstractManager
{
  Q_OBJECT
public:
 SignalMastManager(QObject* parent = 0) : AbstractManager(parent) {}
    // to free resources when no longer used
    /*public*/ void dispose() override {}

    /**
     * Locate via user name, then system name if needed.
     * Does not create a new one if nothing found
     *
     * @param name
     * @return null if no match found
     */
    /*public*/ virtual SignalMast* getSignalMast(QString /*name*/) {return NULL;}

    /**
     * Locate via user name, then system name if needed.
     * Create new one from system name if needed
     *
     * @param name User name, system name, or address which
     *      can be promoted to system name
     * @return Never null
     * @throws IllegalArgumentException if SignalMast doesn't
     * already exist and the manager cannot create the SignalMast
     * due to e.g. an illegal name or name that can't be parsed.
     */
    /*public*/ virtual SignalMast* provideSignalMast(QString ) {return NULL;}

    /*public*/ virtual SignalMast* provideSignalMast(QString /*prefix*/, // nominally IF$shsm
                                        QString /*signalSystem*/,
                                        QString /*mastName*/,
                                        QStringList /*heads*/)  {return NULL;}

    /*public*/ virtual SignalMast* getBySystemName(QString /*s*/)  const =0;
    /*public*/ virtual SignalMast* getByUserName(QString /*s*/)  const = 0;
    virtual /*public*/ SignalMast* provide(QString name) throw (IllegalArgumentException)=0;

friend class SignalMastIcon;
friend class LayoutBlockManager;
friend class MyLayoutEditpr;
};
#endif // SIGNALMASTMANAGER_H
