#include "programmingmode.h"

//ProgrammingMode::ProgrammingMode(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Denote a single programming mode.
 * <P>
 * User code gets a list of available modes from the {@link Programmer} or
 * {@link AddressedProgrammer} in use. It then selects a mode to use and
 * indicates it via a setMode() call.
 * <p>
 * A ProgrammingMode has a user-readable name to help humans select it.
 *<P>
 * We define a number of modes as constants in {@link jmri.managers.DefaultProgrammerManager}
 * because they are common across so
 * many DCC-specific implementations, they've become defacto standards.
 * <p>
 * More specific definitions (and Bundle entries) should
 * retreat to specific Programmer implementations.  The whole idea
 * is to have code deal with the modes that a specific {@link Programmer} provides,
 * not make assumptions about global values.
 *
 * @see         jmri.Programmer
 * @see         jmri.ProgrammerManager
 * @see         jmri.managers.DefaultProgrammerManager
 * @author	Bob Jacobsen Copyright (C) 2014
 */
//@net.jcip.annotations.Immutable
///*public*/ final class ProgrammingMode  {

/**
 * NMRA "Paged" mode
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* ProgrammingMode::PAGEMODE = new ProgrammingMode("PAGEMODE");

/**
 * NMRA "Operations" or "Programming on the main" mode, using only the
 * bit-wise operations
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* ProgrammingMode::OPSBITMODE = new ProgrammingMode("OPSBITMODE");

/**
 * NMRA "Programming on the main" mode for stationary decoders, using only
 * the byte-wise operations and "extended" addressing.
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* ProgrammingMode::OPSACCEXTBYTEMODE = new ProgrammingMode("OPSACCEXTBYTEMODE");

/**
 * NMRA "Programming on the main" mode for stationary decoders, using only
 * the bit-wise operations. Note that this is defined as using the "normal",
 * not "extended" addressing.
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* ProgrammingMode::OPSACCBITMODE = new ProgrammingMode("OPSACCBITMODE");

/**
 * NMRA "Programming on the main" mode for stationary decoders, using only
 * the bit-wise operations and "extended" addressing.
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* ProgrammingMode::OPSACCEXTBITMODE = new ProgrammingMode("OPSACCEXTBITMODE");

/**
 * NMRA "Programming on the main" mode for stationary decoders, using only
 * the byte-wise operations. Note that this is defined as using the
 * "normal", not "extended" addressing.
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* ProgrammingMode::OPSACCBYTEMODE = new ProgrammingMode("OPSACCBYTEMODE");

/**
 * NMRA "Address-only" mode. Often implemented as a proper subset of
 * "Register" mode, as the underlying operation is the same.
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* ProgrammingMode::ADDRESSMODE = new ProgrammingMode("ADDRESSMODE");

/**
 * NMRA "Operations" or "Programming on the main" mode, using only the
 * byte-wise operations.
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* ProgrammingMode::OPSBYTEMODE = new ProgrammingMode("OPSBYTEMODE");

/**
 * NMRA "Direct" mode, using only the byte-wise operations.
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* ProgrammingMode::DIRECTBYTEMODE = new ProgrammingMode("DIRECTBYTEMODE");

/**
 * NMRA "Register" mode.
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* ProgrammingMode::REGISTERMODE = new ProgrammingMode("REGISTERMODE");

/**
 * NMRA "Direct" mode, using only the bit-wise operations.
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* ProgrammingMode::DIRECTBITMODE = new ProgrammingMode("DIRECTBITMODE");

/**
 * NMRA "Direct" mode, using both the bit-wise and byte-wise operations.
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* ProgrammingMode::DIRECTMODE = new ProgrammingMode("DIRECTMODE");

//    /*public*/ ProgrammingMode(QString standardName) {
//        this.standardName = standardName;
//        this.localName = Bundle.getMessage(standardName);  // note in jmri package
//    }

/**
 * Create a ProgrammingMode instance.
 *
 * @param standardName a name, not to be translated, for internal use
 */
/*public*/ ProgrammingMode::ProgrammingMode(/*@Nonnull*/ QString standardName,QObject* parent) : QObject(parent)
{
 this->standardName = standardName;
    //this.localName = Bundle.getMessage(standardName);  // note in jmri package
 if(standardName == "PAGEMODE")
  localName = "Paged";
 else if(standardName == "OPSBITMODE")
  localName = "Ops Bit";
 else if(standardName == "OPSACCEXTBYTEMODE")
  localName = "Ops Accessory Extended Byte";
 else if(standardName == "OPSACCBITMODE")
  localName = "Ops Accessory Bit";
 else if(standardName == "OPSACCEXTBITMODE")
  localName = "Ops Accessory Extended Bit";
 else if(standardName == "OPSACCBYTEMODE")
  localName = "Ops Accessory Byte";
 else if(standardName == "ADDRESSMODE")
  localName = "Address";
 else if(standardName == "OPSBYTEMODE")
  localName = "Ops Byte";
 else if(standardName == "DIRECTBYTEMODE")
  localName = "Direct Byte";
 else if(standardName == "REGISTERMODE")
  localName = "Register";
 else if(standardName == "DIRECTBITMODE")
  localName = "Direct Bit";
 else if(standardName == "DIRECTMODE")
  localName = "Direct";
}

/*
 * Create an instance where you directly
 * provide the localized name.
 * <p>
 * This is useful when you want to create a ProgrammingMode deep
 * within some system-specific code, and don't want to add
 * translations to the top-level jmri.Bundle.
 */
/*public*/ ProgrammingMode::ProgrammingMode(QString standardName, QString localName,QObject *parent ) : QObject(parent)
{
 this->standardName = standardName;
 this->localName = localName;
}

/**
 * Display the localized (human readable) name
 */
//@Override
/*public*/ QString ProgrammingMode::toString() { return localName; }

/**
 * Return the standard (not localized, human readable) name
 */
/*public*/ QString ProgrammingMode::getStandardName() { return standardName; }

//@Override
/*public*/ bool ProgrammingMode::equals(QObject* o)
{
 if (this == o ) return true;
 if (qobject_cast<ProgrammingMode*>(o)==NULL) return false;
 ProgrammingMode* that = (ProgrammingMode*) o;
 return this->standardName==(that->standardName);
}

//@Override
/*public*/ int ProgrammingMode::hashCode() {
    return qHash(this->standardName);
}

/*public*/ bool ProgrammingMode::operator==(QObject* o)
{
 return this->equals(o);
}
