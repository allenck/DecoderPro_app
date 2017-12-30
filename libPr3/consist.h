#ifndef CONSIST_H
#define CONSIST_H

#include <QObject>
#include "dcclocoaddress.h"
#include "consistlistener.h"

class Consist : public QObject
{
    Q_OBJECT
public:
    //explicit Consist(QObject *parent = 0);
    /**
     * Interface for a Consist Object, describing one or more
     * cooperatively-operating locomotives.
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
     * @author              Paul Bender Copyright (C) 2003-2008
     * @version             $Revision: 17977 $
     */
//    public interface Consist {

        // Constants for the ConsistType
        // For Advanced Consists
            const static int ADVANCED_CONSIST = 0;

        // For Command Station Consists
            // This is for a: Digitrax Universal Consist,
            // or Lenz Double Header,or NCE "old Style Consist",etc
            const static int CS_CONSIST = 1;

            // Position Constants
            // 0x00 represents the lead locomotive
            // 0xFF represents the trailing (or rear) locomotive in the consist
            // All other values in between are middle locomotives
            const static int POSITION_LEAD = 0x00;
            const static int POSITION_TRAIL = 0xFF;

        // A method for cleaning up the consist
        virtual void dispose() const {}

        // Set the Consist Type
        virtual void setConsistType(int /*consist_type*/) const {}

        // get the Consist Type
        virtual int getConsistType() const {return 0;}

        // get the Consist Address
        virtual DccLocoAddress* getConsistAddress() const {return NULL;}

        // is the specific address allowed? (needed for system specific
        // restrictions)
        virtual bool isAddressAllowed(DccLocoAddress* /*address*/) const {return false;}

        /**
         * is there a size limit for this type of consist?
         * returns -1 if no limit
         * returns 0 if the Consist Type is not supported
         * returns the total number of useable spaces if the consist has a
             * limit (do not subtract used spaces).
         */
        virtual int sizeLimit() const {return 0;}

        // get a list of the locomotives in the consist
            virtual QList<DccLocoAddress*> getConsistList() const { return  QList<DccLocoAddress*>();}

        // does the consist contain the specified locomotive address?
        virtual bool contains(DccLocoAddress* /*address*/) const {return false;}

        // get the relative direction setting for a specific
        // locomotive in the consist
        virtual bool getLocoDirection(DccLocoAddress* /*address*/) const {return false;}

            /*
         * Add a Locomotive to a Consist
         * @param LocoAddress is the Locomotive address to add to the locomotive
         * @param directionNormal is True if the locomotive is traveling
             *        the same direction as the consist, or false otherwise.
             */
        virtual void add(DccLocoAddress* /*LocoAddress*/, bool  /*directionNormal*/) const {}

            /*
         *  Restore a Locomotive to a Consist, but don't write to the command
             *  station.  This is used for restoring the consist from a file
             *  or adding a consist read from the command station.
         *  @param LocoAddress is the Locomotive address to add to the consist
         *  @param directionNormal is True if the locomotive is traveling
             *        the same direction as the consist, or false otherwise.
             */
        virtual void restore(DccLocoAddress* /*LocoAddress*/, bool  /*directionNormal*/) const {}

            /*
         *  Remove a Locomotive from this Consist
         *  @param address is the Locomotive address to add to the locomotive
             */
        virtual void remove(DccLocoAddress* /*LocoAddress*/) const {}

            /*
             *  Set the position of a locomotive within the consist
             *  @param address is the Locomotive address
             *  @param position is a constant representing the position within
             *         the consist.
             */
            virtual void setPosition(DccLocoAddress* /*address*/,int /*position*/) const {}

            /*
             * Get the position of a locomotive within the consist
             * @param address is the Locomotive address of interest
             * @return integer equal to jmri.Consist.POSITION_LEAD for the
             *                                      designated lead locomotive.
             *                equal to jmri.Consist.POSITION_TRAIL for the
             *                                      designated trailing locomotive.
             *                between 1 and 254 for other locomotives in the consist
             */
            virtual int getPosition(DccLocoAddress* /*address*/) const {return 0;}
        /**
         * Set the roster entry of a locomotive within the consist
         *
         * @param address  is the Locomotive address
         * @param rosterId is the roster Identifer of the associated roster entry.
         */
            /*public*/ virtual void setRosterId(DccLocoAddress* /*address*/, QString /*rosterId*/) {}

        /**
         * Get the rosterId of a locomotive within the consist
         *
         * @param address is the Locomotive address of interest
         * @return string roster Identifier associated with the given address
         *         in the consist.  Returns null if no roster entry is associated
         *         with this entry.
         */
        /*public*/ virtual QString getRosterId(DccLocoAddress* /*address*/) {return "";}
/*
         * Add a Listener for consist events
         * @param Listener is a consistListener object
             */
        virtual void addConsistListener(ConsistListener* /*Listener*/) const {}

        /*
         * Remove a Listener for consist events
         * @param Listener is a consistListener object
             */
        virtual void removeConsistListener(ConsistListener* /*Listener*/) const {}


        /*
         * Set the text ID associated with the consist
             * @param String is a string identifier for the consist
             */
        virtual void setConsistID(QString /*ID*/) const {}

        /*
         * Get the text ID associated with the consist
             * @return String identifier for the consist
             * 	   default value is the string Identifier for the
         *	   consist address.
             */
            virtual QString getConsistID() const {return "";}

        /*
             * Reverse the order of the consist and the direction
         * the locomotives are traveling
         */
        virtual void reverse() const {}

signals:
    
public slots:
    
};

#endif // CONSIST_H
