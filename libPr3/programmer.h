#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include "commandstation.h"
#include "proglistener.h"
#include "exceptions.h"
#include "propertychangelistener.h"
#include "exceptions.h"

/**
 * Provide access to the hardware DCC decoder programming capability.
 * <P>
 * Programmers come in multiple types:
 * <UL>
 * <LI>Global, previously Service Mode, e.g. on a programming track
 * <LI>Addressed, previously Ops Mode, e.g. "programming on the main"
 * </UL>
 * Different equipment may also require different programmers:
 * <LI>DCC CV programming, on service mode track or on the main
 * <LI>CBUS Node Variable programmers
 * <LI>LocoNet System Variable programmers
 * <LI>LocoNet Op Switch programmers
 * </UL>
 * Depending on which type you have, only certain modes can
 * be set. Valid modes are specified by the class static constants.
 * <P>
 * You get a Programmer object from a {@link ProgrammerManager},
 * which in turn can be located from the {@link InstanceManager}.
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
 * @see         jmri.ProgrammerManager
 * @author	Bob Jacobsen Copyright (C) 2001, 2008
 * @version	$Revision: 17977 $
 */

class ProgrammingMode;
class Programmer //: public CommandStation
{
 //Q_OBJECT
// Q_ENUMS(programmerMode)
public:
 //explicit Programmer(QObject *parent = 0) : CommandStation(parent) {}
// enum programmerMode
// {
//  // mode e.g. register, direct, paged

//  /**
//   * No programming mode available
//   */
//  NONE  = 0,
//  /**
//   * NMRA "Register" mode
//   */
//  REGISTERMODE = 11,

//     /**
//      * NMRA "Paged" mode
//      */
//     PAGEMODE = 21,

//     /**
//      * NMRA "Direct" mode, using only the bit-wise operations
//      */
//     DIRECTBITMODE  = 31,

//     /**
//      * NMRA "Direct" mode, using only the byte-wise operations
//      */
//     DIRECTBYTEMODE = 32,
//     /**
//      * NMRA "Address-only" mode. Often implemented as
//      * a proper subset of "Register" mode, as the
//      * underlying operation is the same.
//      */
//     ADDRESSMODE = 41,

//     /**
//      * NMRA "Operations" or "Programming on the main" mode, using only the byte-wise operations
//      */
//     OPSBYTEMODE  = 101,
//     /**
//      * NMRA "Operations" or "Programming on the main" mode, using only the bit-wise operations
//      */
//     OPSBITMODE  = 102,
//     /**
//      * NMRA "Programming on the main" mode for stationary decoders,
//      * using only the byte-wise operations. Note that this is
//      * defined as using the "normal", not "extended" addressing.
//      */
//     OPSACCBYTEMODE  = 111,

//     /**
//      * NMRA "Programming on the main" mode for stationary decoders,
//      * using only the bit-wise operations. Note that this is
//      * defined as using the "normal", not "extended" addressing.
//      */
//     OPSACCBITMODE   = 112,
//     /**
//      * NMRA "Programming on the main" mode for stationary decoders,
//      * using only the byte-wise operations and "extended" addressing.
//      */
//     OPSACCEXTBYTEMODE = 121,
//     /**
//      * NMRA "Programming on the main" mode for stationary decoders,
//      * using only the bit-wise operations and "extended" addressing.
//      */
//     OPSACCEXTBITMODE  = 122,

//     /**
//      * CBUS mode for programming node variables.
//      */
//     CBUSNODEVARMODE  = 140
//    };

 /**
  * Perform a CV write in the system-specific manner, and using the specified
  * programming mode.
  * <P>
  * Handles a general address space through a String address. Each programmer
  * defines the acceptable formats.
  * <P>
  * Note that this returns before the write is complete; you have to provide
  * a ProgListener to hear about completion. For simplicity, expect the return to be on the
  * <a href="http://jmri.org/help/en/html/doc/Technical/Threads.shtml">GUI thread</a>.
  * <p>
  * Exceptions will only be
  * thrown at the start, not during the actual programming sequence. A
  * typical exception would be due to an invalid mode (though that should be
  * prevented earlier)
  *
  * @param CV  the CV to write
  * @param val the value to write
  * @param p   the listener that will be notified of the write
  * @throws jmri.ProgrammerException if unable to communicate
  */
 virtual /*public*/ void writeCV(QString /*CV*/, int /*val*/, ProgListener* /*p*/) throw (ProgrammerException) =0;
 /**
      * Perform a CV read in the system-specific manner, and using the specified
  * programming mode.
  * <P>
  * Handles a general address space through a String address. Each programmer
  * defines the acceptable formats.
  * <P>
  * Note that this returns before the write is complete; you have to provide
  * a ProgListener to hear about completion. For simplicity, expect the return to be on the
  * <a href="http://jmri.org/help/en/html/doc/Technical/Threads.shtml">GUI thread</a>.
  * <p>
  * Exceptions will only be
  * thrown at the start, not during the actual programming sequence. A
  * typical exception would be due to an invalid mode (though that should be
  * prevented earlier)
  *
  * @param CV the CV to read
  * @param p  the listener that will be notified of the read
  * @throws jmri.ProgrammerException if unable to communicate
  */
 virtual /*public*/ void readCV(QString /*CV*/, ProgListener* /*p*/) throw (ProgrammerException) =0;
 /**
  * Confirm the value of a CV using the specified programming mode. On some
  * systems, this is faster than a read.
  * <P>
  * Handles a general address space through a String address. Each programmer
  * defines the acceptable formats.
  * <P>
  * Note that this returns before the write is complete; you have to provide
  * a ProgListener to hear about completion. For simplicity, expect the return to be on the
  * <a href="http://jmri.org/help/en/html/doc/Technical/Threads.shtml">GUI thread</a>.
  * <p>
  * Exceptions will only be
  * thrown at the start, not during the actual programming sequence. A
  * typical exception would be due to an invalid mode (though that should be
  * prevented earlier)
  *
  * @param CV  the CV to confirm
  * @param val the value to confirm
  * @param p   the listener that will be notified of the confirmation
  * @throws jmri.ProgrammerException if unable to communicate
  */
  virtual /*public*/ void confirmCV(QString /*CV*/, int /*val*/, ProgListener* /*p*/) throw (ProgrammerException) =0;
/**
 * Get the list of {@link ProgrammingMode} supported by this
 * Programmer. If the order is significant, earlier modes are better.
 */
    /*public*/ virtual QList<QString> getSupportedModes() {return QList<QString>();}
  virtual void setMode(ProgrammingMode* /*mode*/) =0;
  virtual ProgrammingMode*  getMode() =0;
//virtual bool hasMode(int mode) {return false;}
  virtual bool getCanRead() =0;
/**
 * Checks the general read capability, regardless of mode,
 * for a specific address
 */
  virtual /*public*/ bool getCanRead(QString /*addr*/) =0;

/**
 * Checks the general write capability, regardless of mode
 */
 virtual /*public*/ bool getCanWrite() =0;
/**
 * Checks the general write capability, regardless of mode,
 * for a specific address
 */
 virtual /*public*/ bool getCanWrite(QString /*addr*/) =0;

 /**
* Learn about whether the programmer does any kind of verification of write
* operations
*
* @param addr A CV address to check (in case this varies with CV range) or
*             null for any
* @return The confirmation behavior that can be counted on (might be better
*         in some cases)
*/
enum WriteConfirmMode {
/**
* No verification available, writes are blind
*/
NotVerified,
/**
* Programmer signals error if there's no reply from the device
*/
DecoderReply,
/**
* Programmer does a read after write to verify
*/
ReadAfterWrite
};
//@Nonnull
/*public*/ virtual WriteConfirmMode getWriteConfirmMode(QString /*addr*/) {return NotVerified;}
/**
 * wrapper to call {@link jmri.ProgListener#programmingOpReply} that verifies
 * the specified progListener is not null.
 *
 * @param p listener to notify
 * @param value result value
 * @param status code from jmri.ProgListener
 */
/*default*/ /*public*/ virtual void notifyProgListenerEnd(ProgListener* p, int value, int status)
{
 if ( p != nullptr ) {
    p->programmingOpReply(value, status);
 }
}

virtual void addPropertyChangeListener(PropertyChangeListener* /*p*/) =0;
virtual void removePropertyChangeListener(PropertyChangeListener* /*p*/) =0;

// error handling on request is via exceptions
// results are returned via the ProgListener callback

 virtual QString decodeErrorCode(int /*i*/) =0;
 virtual QObject* self() =0;
signals:
    
public slots:
    
};
Q_DECLARE_INTERFACE(Programmer, "Programmer")
#endif // PROGRAMMER_H
