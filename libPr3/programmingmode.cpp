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


//    /*public*/ ProgrammingMode(QString standardName) {
//        this.standardName = standardName;
//        this.localName = Bundle.getMessage(standardName);  // note in jmri package
//    }

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
    //return standardName.hashCode();
    return 0;
}

