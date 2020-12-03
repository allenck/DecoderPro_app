#include "manager.h"
#include "nmrapacket.h"
#include "loggerfactory.h"
#include "namedbeanpropertydescriptor.h"

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


/**
 * Returns the user-readable name of the type of NamedBean handled by this
 * manager.
 * <p>
 * For instance, in the code where we are dealing with just a bean and a
 * message that needs to be passed to the user or in a log.
 *
 * @param plural true to return plural form of the type; false to return
 *               singular form
 *
 * @return a string of the bean type that the manager handles, eg Turnout,
 *         Sensor etc
 */
//@CheckReturnValue
//@Nonnull
/*public*/ QString Manager::getBeanTypeHandled(bool /*plural*/) const { return "??";}

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
 * Provides the system prefix of the given system name.
 * <p>
 * This is a common operation across JMRI, as the system prefix can be
 * parsed out without knowledge of the type of NamedBean involved.
 *
 * @param inputName System name to provide the prefix
 * @throws NamedBean.BadSystemNameException If the inputName can't be
 *                                          converted to normalized form
 * @return The system-prefix part of the system name in standard normalized
 *         form
 */
//@CheckReturnValue
//@Nonnull
/*public*/ /*static*/ QString Manager::getSystemPrefix(/*@Nonnull*/ QString inputName) {
    return inputName.mid(0, getSystemPrefixLength(inputName));
}

/*public*/ /*default*/ QString Manager::makeSystemName(/*@Nonnull*/ QString name) const {
        return makeSystemName(name, true);
}


/**
 * Create a SystemName by prepending the system name prefix to the name if
 * not already present.
 * <p>
 * The {@code logErrors} parameter is present to allow user interface input
 * validation to use this method without logging system name validation
 * errors as the user types.
 * <p>
 * <strong>Note:</strong> implementations <em>must</em> call
 * {@link #validateSystemNameFormat(java.lang.String, java.util.Locale)} to ensure
 * the returned name is valid.
 *
 * @param name      the item to make the system name for
 * @param logErrors true to log errors; false to not log errors
 * @return a valid system name
 * @throws BadSystemNameException if a valid name can't be created
 */
//@Nonnull
/*public*/ /*default*/ QString Manager::makeSystemName(/*@Nonnull*/ QString name, bool logErrors) const {
    return makeSystemName(name, logErrors, QLocale());
}

/**
 * Create a SystemName by prepending the system name prefix to the name if
 * not already present.
 * <p>
 * The {@code logErrors} parameter is present to allow user interface input
 * validation to use this method without logging system name validation
 * errors as the user types.
 * <p>
 * <strong>Note:</strong> implementations <em>must</em> call
 * {@link #validateSystemNameFormat(java.lang.String, java.util.Locale)} to ensure
 * the returned name is valid.
 *
 * @param name      the item to make the system name for
 * @param logErrors true to log errors; false to not log errors
 * @param locale    the locale for a localized exception; this is needed for
 *                      the JMRI web server, which supports multiple locales
 * @return a valid system name
 * @throws BadSystemNameException if a valid name can't be created
 */
//@Nonnull
/*public*/ /*default*/ QString Manager::makeSystemName(/*@Nonnull*/ QString name, bool /*logErrors*/, QLocale locale) const {
    QString prefix = getSystemNamePrefix();
    // the one special case that is not caught by validation here
    if (name.trimmed().isEmpty()) { // In Java 9+ use name.isBlank() instead
        //throw NamedBean::BadSystemNameException(locale, "InvalidSystemNameInvalidPrefix", prefix);
     throw NamedBean::BadSystemNameException(locale, QString("System name must start with \"%21\".").arg(prefix), name, prefix);
    }
    return validateSystemNameFormat(name.startsWith(prefix) ? name : prefix + name, locale);
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
/*public*/ /*default*/ QString Manager::validateSystemNameFormat(/*@Nonnull*/ QString name) const throw (NamedBean::BadSystemNameException)
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
/*public*/ /*default*/ QString Manager::validateSystemNameFormat(/*@Nonnull*/ QString name, /*@Nonnull*/ QLocale locale) const throw (NamedBean::BadSystemNameException)
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
/*public*/ /*default*/ QString Manager::validateSystemNamePrefix(/*@Nonnull*/ QString name, /*@Nonnull*/ QLocale locale) const throw (NamedBean::BadSystemNameException) {
    QString prefix = getSystemNamePrefix();
    if (name == (prefix)) {
        throw NamedBean::BadSystemNameException(locale, tr("System name \"%1\" is missing suffix.").arg(name),name);
    }
    if (!name.startsWith(prefix)) {
        throw NamedBean::BadSystemNameException(locale, tr("System name must start with \"%1\".").arg(prefix),prefix);
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
        throw NamedBean::BadSystemNameException(locale, tr("System name \"%1\" contains trailing white space characters, but should not.").arg(name),name, prefix);
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
        throw NamedBean::BadSystemNameException(locale, tr("System name \"%1\" contains lowercase characters, but must be all uppercase.").arg(name), name, prefix);
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
            throw NamedBean::BadSystemNameException(locale, tr("Number in \"%1\" must be greater than or equal to %2.").arg(name).arg(min), name, QString::number(min));
        } else if (number > max) {
            throw NamedBean::BadSystemNameException(locale, tr("Number in \"%1\" must be less than or equal to %2.").arg(name).arg(max), name, QString::number(max));
        }
    } catch (NumberFormatException ex) {
        throw NamedBean::BadSystemNameException(locale, tr("\"%1\" must be an integer after \"%2\".").arg(name).arg(prefix), name, prefix);
    }
    return name;
}

/**
     * Convenience implementation of
     * {@link #validateSystemNameFormat(java.lang.String, java.util.Locale)}
     * that verifies name is a valid NMRA Accessory address after the prefix. A
     * name is considered a valid NMRA accessory address if it is an integer
     * between {@value NmraPacket#accIdLowLimit} and
     * {@value NmraPacket#accIdHighLimit}, inclusive.
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
    /*public*/ /*default*/ QString Manager::validateNmraAccessorySystemNameFormat(/*@Nonnull*/ QString name, /*@Nonnull*/ QLocale locale) {
        return this->validateIntegerSystemNameFormat(name, NmraPacket::accIdLowLimit, NmraPacket::accIdHighLimit, locale);
    }

    /**
     * Test if a given name is in a valid format for this Manager.
     *
     * @param systemName the name to check
     * @return {@code true} if {@link #validSystemNameFormat(java.lang.String)}
     *         equals {@link NameValidity#VALID}; {@code false} otherwise
     */
    /*public*/ /*default*/ bool Manager::isValidSystemNameFormat(/*@Nonnull*/ QString systemName) {
        return validSystemNameFormat(systemName) == NameValidity::VALID;
    }


// needed for deprecationWarning call above
/*static*/ /*final*/ Logger* Manager::deprecatedManagerLogger = LoggerFactory::getLogger("Manager");

/**
 * Locate an existing instance based on a system name.
 *
 * @param systemName System Name of the required NamedBean
 * @return requested NamedBean object or null if none exists
 * @throws IllegalArgumentException if provided name is invalid
 */
//@CheckReturnValue
//@CheckForNull
// /*public*/ NamedBean* Manager::getBySystemName(/*@Nonnull*/ QString systemName)  {return nullptr;}

/**
 * Locate an existing instance based on a user name.
 *
 * @param userName System Name of the required NamedBean
 * @return requested NamedBean object or null if none exists
 */
//@CheckReturnValue
//@CheckForNull
// /*public*/ NamedBean* Manager::getByUserName(/*@Nonnull*/ QString userName {return nullptr;}

/**
 * Return the descriptors for the system-specific properties of the
 * NamedBeans that are kept in this manager.
 *
 * @return list of known properties, or empty list if there are none
 */
//@Nonnull
/*default*/ /*public*/ QList<NamedBeanPropertyDescriptor*> Manager::getKnownBeanProperties() {
    return QList<NamedBeanPropertyDescriptor*>();
}

/**
  * Defines an event that encapsulates changes to a list.
  * <p>
  * Intended to be equivalent to {@link javax.swing.event.ListDataEvent}
  * without introducing a Swing dependency into core JMRI.
  *
  * @param <E> the type to support in the event
  * @since JMRI 4.11.4
  */
 //@javax.annotation.concurrent.Immutable
// /*public*/ /*final*/ class ManagerDataEvent  /*<E extends NamedBean>*/: public EventObject
// {
//  public:
     /**
      * Equal to {@link javax.swing.event.ListDataEvent#CONTENTS_CHANGED}
      */
     /*final*/ /*static*/ /*public*/ int Manager::ManagerDataEvent::CONTENTS_CHANGED = 0;
     /**
      * Equal to {@link javax.swing.event.ListDataEvent#INTERVAL_ADDED}
      */
     /*final*/ /*static*/ /*public*/ int Manager::ManagerDataEvent::INTERVAL_ADDED = 1;
     /**
      * Equal to {@link javax.swing.event.ListDataEvent#INTERVAL_REMOVED}
      */
     /*final*/ /*static*/ /*public*/ int Manager::ManagerDataEvent::INTERVAL_REMOVED = 2;
//   private:
//     /*final*/ /*private*/ int type;
//     /*final*/ /*private*/ int index0;
//     /*final*/ /*private*/ int index1;
//     /*final*/ /*private*/ /*E*/NamedBean* changedBean; // used when just one bean is added or removed as an efficiency measure
//     /*final*/ /*private*/ Manager/*<E>*/ source;
//        public:
     /**
      * Creates a <code>ListDataEvent</code> object.
      *
      * @param source      the source of the event (<code>null</code> not
      *                    permitted).
      * @param type        the type of the event (should be one of
      *                    {@link #CONTENTS_CHANGED}, {@link #INTERVAL_ADDED}
      *                    or {@link #INTERVAL_REMOVED}, although this is not
      *                    enforced).
      * @param index0      the index for one end of the modified range of
      *                    list elements.
      * @param index1      the index for the other end of the modified range
      *                    of list elements.
      * @param changedBean used when just one bean is added or removed,
      *                    otherwise null
      */
     /*public*/ Manager::ManagerDataEvent::ManagerDataEvent(/*@Nonnull*/ Manager/*<E>*/* source, int type, int index0, int index1, /*E*/NamedBean* changedBean)
     : EventObject(source)
     {
         //super(source);
         this->source = source;
         this->type = type;
         this->index0 = qMin(index0, index1);  // from javax.swing.event.ListDataEvent implementation
         this->index1 = qMax(index0, index1);  // from javax.swing.event.ListDataEvent implementation
         this->changedBean = changedBean;
     }

     /**
      * Returns the source of the event in a type-safe manner.
      *
      * @return the event source
      */
     //@Override
     /*public*/ Manager/*<E>*/* Manager::ManagerDataEvent::getSource() {
         return source;
     }

     /**
      * Returns the index of the first item in the range of modified list
      * items.
      *
      * @return The index of the first item in the range of modified list
      *         items.
      */
     /*public*/ int Manager::ManagerDataEvent::getIndex0() {
         return index0;
     }

     /**
      * Returns the index of the last item in the range of modified list
      * items.
      *
      * @return The index of the last item in the range of modified list
      *         items.
      */
     /*public*/ int Manager::ManagerDataEvent::getIndex1() {
         return index1;
     }

     /**
      * Returns the changed bean or null
      *
      * @return null if more than one bean was changed
      */
     /*public*/ /*E*/NamedBean* Manager::ManagerDataEvent::getChangedBean() {
         return changedBean;
     }

     /**
      * Returns a code representing the type of this event, which is usually
      * one of {@link #CONTENTS_CHANGED}, {@link #INTERVAL_ADDED} or
      * {@link #INTERVAL_REMOVED}.
      *
      * @return The event type.
      */
     /*public*/ int Manager::ManagerDataEvent::getType() {
         return type;
     }

     /**
      * Returns a string representing the state of this event.
      *
      * @return A string.
      */
     //@Override
     /*public*/ QString Manager::ManagerDataEvent::toString() {
         return /*getClass().getName()*/QString(this->metaObject()->className()) + "[type=" + QString::number(type) + ",index0=" + QString::number(index0) + ",index1=" + QString::number(index1) + "]";
     }
//    }; // end class definition ManagerDataEvent
    /**
     * Register a {@link ManagerDataListener} to hear about adding or removing
     * items from the list of NamedBeans.
     *
     * @param e the data listener to add
     */
     /*public*/ void Manager::addDataListener(/*ManagerDataListener<E>*/QObject* /*e*/) {}

    /**
     * Unregister a previously-added {@link ManagerDataListener}.
     *
     * @param e the data listener to remove
     */
    /*public*/ void Manager::removeDataListener(/*ManagerDataListener<E>*/QObject* /*e*/) {}

    /**
     * Temporarily suppress DataListener notifications.
     * <p>
     * This avoids O(N^2) behavior when doing bulk updates, i.e. when loading
     * lots of Beans. Note that this is (1) optional, in the sense that the
     * manager is not required to mute and (2) if present, its' temporary, in
     * the sense that the manager must do a cumulative notification when done.
     *
     * @param muted true if notifications should be suppressed; false otherwise
     */
    /*public*/ /*default*/ void Manager::setDataListenerMute(bool /*muted*/) {
    }
