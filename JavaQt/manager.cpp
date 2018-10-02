#include "manager.h"

/*static*/ QStringList Manager::legacyPrefixes = QStringList() << "DX" << "DCCPP" << "DP" << "MR" << "MC" << "PI" << "TM";

/*public*/ /*static*/ bool Manager::isLegacySystemPrefix(/*@Nonnull*/ QString prefix) {
    return legacyPrefixes.contains(prefix);
}

/*public*/ /*static*/ int Manager::startsWithLegacySystemPrefix(/*@Nonnull*/ QString prefix) {
    // implementation replies on legacy suffix length properties to gain a bit of speed...
    if (prefix.length()<2) return -1;
    if (legacyPrefixes.contains(prefix.mid(0,2))) return 2;
    else if (prefix.startsWith("DCCPP"))  return 5;
    else return -1;
}

/*static*/ /*public*/ int Manager::getSystemPrefixLength(/*@Nonnull*/ QString inputName) throw (NamedBean::BadSystemNameException)
{
    if (inputName.isEmpty()) throw NamedBean::BadSystemNameException();
    //if (! Character.isLetter(inputName.charAt(0))) throw new NamedBean.BadSystemNameException();
    if(!inputName.at(0).isLetter()) throw NamedBean::BadSystemNameException();

    // As a very special case, check for legacy prefixs - to be removed
    // This is also quite a bit slower than the tuned implementation below
    int p = startsWithLegacySystemPrefix(inputName);
    if (p > 0) return p;

    // implementation for well-formed names
    int i = 1;
    for (i = 1; i < inputName.length(); i++) {
        if ( !(inputName.at(i).isDigit()))
            break;
    }
    return i;
}
