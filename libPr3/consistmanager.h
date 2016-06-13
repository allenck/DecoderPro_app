#ifndef CONSISTMANAGER_H
#define CONSISTMANAGER_H

#include <QObject>
#include "dcclocoaddress.h"
#include "./consist.h"
#include "consistlistlistener.h"

class ConsistManager : public QObject
{
    Q_OBJECT
public:
    //explicit ConsistManager(QObject *parent = 0);

    /**
     * Interface for Consist Manager objects, which provide access to
     * the existing Consists and allows for creation and destruction.
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
     * @author              Paul Bender Copyright (C) 2003
     * @version             $Revision: 20642 $
     */
//    public interface  ConsistManager {

        /**
         *    Find a Consist with this consist address, and return it.
             *    if the Consist doesn't exit, create it.
         **/
        virtual Consist* getConsist(DccLocoAddress* address) {return NULL;}

        /**
         *    Remove an old Consist
         */
        virtual void delConsist(DccLocoAddress* address)  = 0;

        /**
         *    Does this implementation support Command Station Consists?
         */
        virtual bool isCommandStationConsistPossible()  = 0;

        /**
         *    Does a CS consist require a seperate consist address?
         */
        virtual bool csConsistNeedsSeperateAddress()  = 0;

        /**
         *    Get an ArrayList object containning the string representation
         *    of the consist addresses we know about.
         */
        virtual QList<DccLocoAddress*>* getConsistList()  = 0;

        /**
         *   Translate Error Codes recieved by a consistListener into
         *   Strings
         */
        virtual QString decodeErrorCode(int ErrorCode)  = 0;

        /* request an update from the layout, loading
         * Consists from the command station.
         */
        virtual void requestUpdateFromLayout()  = 0;

        /*
         * register a ConsistListListener object with this Consist
         * Manager
         * @param listener a Consist List Listener object.
         */
        virtual void addConsistListListener(ConsistListListener* l)  = 0;

        /*
         * remove a ConsistListListener object with this Consist
         * Manager
         * @param listener a Consist List Listener object.
         */
        virtual void removeConsistListListener(ConsistListListener* l)  = 0;

        /*
         * Notify the registered Consist List Listener objects that the
         * Consist List has changed.
         */
        virtual void notifyConsistListChanged()  = 0;
signals:
    
public slots:
    
};
Q_DECLARE_INTERFACE(ConsistManager, "Consist manager")
#endif // CONSISTMANAGER_H
