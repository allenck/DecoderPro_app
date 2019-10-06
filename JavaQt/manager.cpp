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

/**
 * Validate the format of a system name, returning it unchanged if valid.
 * <p>
 * Although further restrictions may be added by system-specific
 * implementations, at a minimum, the implementation must consider a name
 * that does not start with the System Name prefix for this manager to be
 * invalid, and must consider a name that is the same as the System Name
 * prefix to be invalid.
 * <p>
 * This method should not be overridden;
 * {@link #validateSystemNameFormat(java.lang.String, java.util.Locale)}
 * should be overridden instead.
 *
 * @param name      the system name to validate
 * @return the system name unchanged from its input so that this method can
 *         be chained or used as an parameter to another method
 * @throws BadSystemNameException if the name is not valid with error
 *                                      messages in the default locale
 */
//@Nonnull
/*public*/ /*default*/ QString Manager::validateSystemNameFormat(/*@Nonnull*/ QString name) throw (NamedBean::BadSystemNameException)
{
    return validateSystemNameFormat(name, /*Locale.getDefault()*/QLocale());
}

/**
 * Validate the format of name, returning it unchanged if valid.
 * <p>
 * Although further restrictions may be added by system-specific
 * implementations, at a minimum, the implementation must consider a name
 * that does not start with the System Name prefix for this manager to be
 * invalid, and must consider a name that is the same as the System Name
 * prefix to be invalid.
 * <p>
 * Overriding implementations may rely on
 * {@link #validSystemNameFormat(java.lang.String)}, however they must
 * provide an actionable message in the thrown exception if that method does
 * not return {@link NameValidity#VALID}. Implementations of
 * this method <em>must not</em> throw an exception, log an error, or
 * otherwise disrupt the user.
 *
 * @param name      the system name to validate
 * @param locale    the locale for a localized exception; this is needed for
 *                      the JMRI web server, which supports multiple locales
 * @return the unchanged value of the name parameter
 * @throws BadSystemNameException if provided name is an invalid format
 */
//@Nonnull
/*public*/ /*default*/ QString Manager::validateSystemNameFormat(/*@Nonnull*/ QString name, /*@Nonnull*/ QLocale locale) throw (NamedBean::BadSystemNameException)
{
    return validateSystemNamePrefix(name, locale);
}

/**
 * Basic validation that the system name prefix is correct. Used within the
 * default implementation of
 * {@link #validateSystemNameFormat(java.lang.String, java.util.Locale)} and
 * abstracted out of that method so this can be used by validation
 * implementations in {@link jmri.jmrix.SystemConnectionMemo}s to avoid
 * duplicating code in all managers relying on a single subclass of
 * SystemConnectionMemo.
 *
 * @param name      the system name to validate
 * @param locale    the locale for a localized exception; this is needed for
 *                      the JMRI web server, which supports multiple locales
 * @return the unchanged value of the name parameter
 * @throws BadSystemNameException if provided name is an invalid format
 */
//@Nonnull
/*public*/ /*default*/ QString Manager::validateSystemNamePrefix(/*@Nonnull*/ QString name, /*@Nonnull*/ QLocale locale) throw (NamedBean::BadSystemNameException) {
    QString prefix = getSystemNamePrefix();
    if (name == (prefix)) {
        throw NamedBean::BadSystemNameException(locale, "InvalidSystemNameMatchesPrefix", name);
    }
    if (!name.startsWith(prefix)) {
        throw NamedBean::BadSystemNameException(locale, "InvalidSystemNameInvalidPrefix", prefix);
    }
    return name;
}

/**
 * Convenience implementation of
 * {@link #validateSystemNameFormat(java.lang.String, java.util.Locale)}
 * that verifies name has no trailing white space and no white space between
 * the prefix and suffix.
 * <p>
 * <strong>Note</strong> this <em>must</em> only be used if the connection
 * type is externally documented to require these restrictions.
 *
 * @param name   the system name to validate
 * @param locale the locale for a localized exception; this is needed for
 *               the JMRI web server, which supports multiple locales
 * @return the unchanged value of the name parameter
 * @throws BadSystemNameException if provided name is an invalid format
 */
//@Nonnull
/*public*/ /*default*/ QString Manager::validateTrimmedSystemNameFormat(/*@Nonnull*/ QString name, /*@Nonnull*/ QLocale locale) {
    name = validateSystemNamePrefix(name, locale);
    QString prefix = getSystemNamePrefix();
    QString suffix = name.mid(prefix.length());
    if (suffix !=(suffix.trimmed())) {
        throw NamedBean::BadSystemNameException(locale, "InvalidSystemNameTrailingWhitespace", name, prefix);
    }
    return name;
}

/**
 * Convenience implementation of
 * {@link #validateSystemNameFormat(java.lang.String, java.util.Locale)}
 * that verifies name is upper case and has no trailing white space and not
 * white space between the prefix and suffix.
 * <p>
 * <strong>Note</strong> this <em>must</em> only be used if the connection
 * type is externally documented to require these restrictions.
 *
 * @param name   the system name to validate
 * @param locale the locale for a localized exception; this is needed for
 *               the JMRI web server, which supports multiple locales
 * @return the unchanged value of the name parameter
 * @throws BadSystemNameException if provided name is an invalid format
 */
//@Nonnull
/*public*/ /*default*/ QString Manager::validateUppercaseTrimmedSystemNameFormat(/*@Nonnull*/ QString name, /*@Nonnull*/ QLocale locale) {
    name = validateTrimmedSystemNameFormat(name, locale);
    QString prefix = getSystemNamePrefix();
    QString suffix = name.mid(prefix.length());
    if (suffix != (suffix.toUpper())) {
        throw NamedBean::BadSystemNameException(locale, "InvalidSystemNameNotUpperCase", name, prefix);
    }
    return name;
}

/**
 * Convenience implementation of
 * {@link #validateSystemNameFormat(java.lang.String, java.util.Locale)}
 * that verifies name is an integer after the prefix.
 * <p>
 * <strong>Note</strong> this <em>must</em> only be used if the connection
 * type is externally documented to require these restrictions.
 *
 * @param name   the system name to validate
 * @param min    the minimum valid integer value
 * @param max    the maximum valid integer value
 * @param locale the locale for a localized exception; this is needed for
 *               the JMRI web server, which supports multiple locales
 * @return the unchanged value of the name parameter
 * @throws BadSystemNameException if provided name is an invalid format
 */
//@Nonnull
/*public*/ /*default*/ QString Manager::validateIntegerSystemNameFormat(/*@Nonnull*/ QString name, int min, int max, /*@Nonnull*/ QLocale locale) {
    name = validateTrimmedSystemNameFormat(name, locale);
    QString prefix = getSystemNamePrefix();
    QString suffix = name.mid(prefix.length());
    try {
        int number = (suffix.toInt());
        if (number < min) {
            throw NamedBean::BadSystemNameException(locale, "InvalidSystemNameIntegerLessThan", name, QString::number(min));
        } else if (number > max) {
            throw NamedBean::BadSystemNameException(locale, "InvalidSystemNameIntegerGreaterThan", name, QString::number(max));
        }
    } catch (NumberFormatException ex) {
        throw NamedBean::BadSystemNameException(locale, "InvalidSystemNameNotInteger", name, prefix);
    }
    return name;
}
