#ifndef SIGNALHEADMANAGER_H
#define SIGNALHEADMANAGER_H
#include <QObject>
#include "signalhead.h"
#include "abstractmanager.h"
#include <QCompleter>

class LIBPR3SHARED_EXPORT SignalHeadManager : public AbstractManager
{
    Q_OBJECT
public:
    explicit SignalHeadManager(QObject *parent = 0) : AbstractManager(parent) {}
    /**
     * Interface for obtaining signal heads.
     * <P>
     * This doesn't have a "new" method, as SignalHeads
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
     * @author      Bob Jacobsen Copyright (C) 2001
     * @version	$Revision: 17977 $
     */
    //public interface SignalHeadManager extends Manager {

        // to free resources when no longer used
        virtual void dispose() {}
        /**
         * Locate via user name, then system name if needed.
         * Does not create a new one if nothing found
         *
         * @param name
         * @return null if no match found
         */
        virtual SignalHead* getSignalHead(QString name) = 0;

        virtual SignalHead* getByUserName(QString /*s*/) const = 0;
        virtual SignalHead* getBySystemName(QString /*s*/) const = 0;

        /**
         * Get a list of all SignalHead system names.
         */
//        virtual QStringList getSystemNameList() { return QStringList();}
          virtual QCompleter* getCompleter(QString /*text*/, bool /*bIncludeUserNames*/) {return NULL;}

signals:
    
public slots:
    
};
#endif // SIGNALHEADMANAGER_H
