#ifndef COMMANDSTATION_H
#define COMMANDSTATION_H

#include <QObject>
#include <QByteArray>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT CommandStation //: public QObject
{
    //Q_OBJECT
public:
    //explicit CommandStation(QObject *parent = 0);
    /**
     * Represents a DCC command station.
     * <P>
     * System-specific implementations can be obtained via the InstanceManager
     * class.
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
     * @author      Bob Jacobsen Copyright (C) 2003
     * @version     $Revision: 19084 $
     */
//    public interface CommandStation {

        /**
         * Send a specific packet to the rails.
         *
         * @param packet Byte array representing the packet, including
         * the error-correction byte.  Must not be null.
         * @param repeats Number of times to repeat the transmission.
         */
        virtual bool sendPacket(QByteArray /*packet*/, int /*repeats*/) =0;

        virtual QString getUserName() =0;

        virtual QString getSystemPrefix() =0;

        virtual QObject* self() =0;

signals:
    
public slots:
    
};
Q_DECLARE_INTERFACE(CommandStation, "CommandStation")
#endif // COMMANDSTATION_H
