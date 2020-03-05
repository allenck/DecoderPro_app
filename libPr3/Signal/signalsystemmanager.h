#ifndef SIGNALSYSTEMMANAGER_H
#define SIGNALSYSTEMMANAGER_H
#include "abstractmanager.h"
#include "signalsystem.h"

/**
 * Interface for obtaining information about signal systems.
 * <p>
 * Each NamedBean here represents a single signal system.
 * The actual objects are SignalAspectTable objects; that's
 * a current anachronism, soon to be fixed.
 * <P>
 * See the common implementation for information on how loaded, etc.
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
 * @author   Bob Jacobsen Copyright (C) 2009
 * @version	$Revision: 17977 $
 */
/*public*/ /*interface*/ class LIBPR3SHARED_EXPORT SignalSystemManager : public AbstractManager
{
 Q_OBJECT
 public:
    SignalSystemManager(QObject* parent = nullptr) : AbstractManager(parent) {}
    /*public*/ virtual SignalSystem* getSystem(QString name) = 0;

    /*public*/ virtual SignalSystem* getBySystemName(QString name)const = 0;

    /*public*/ virtual SignalSystem* getByUserName(QString name)const = 0;
};

#endif // SIGNALSYSTEMMANAGER_H
