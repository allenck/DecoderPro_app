#include "missingresourceexception.h"

MissingResourceException::MissingResourceException(QObject *parent)
{
}
/**
 * Signals that a resource is missing.
 * @see java.lang.Exception
 * @see ResourceBundle
 * @author      Mark Davis
 * @since       JDK1.1
 */

/**
 * Constructs a MissingResourceException with the specified information.
 * A detail message is a String that describes this particular exception.
 * @param s the detail message
 * @param className the name of the resource class
 * @param key the key for the missing resource.
 */
 MissingResourceException::MissingResourceException(QString s, QString className, QString key, QObject *parent)
 {
    //super(s);
    this->className = className;
    this->key = key;
}
 MissingResourceException::~MissingResourceException()
 {}

/**
 * Constructs a <code>MissingResourceException</code> with
 * <code>message</code>, <code>className</code>, <code>key</code>,
 * and <code>cause</code>. This constructor is package private for
 * use by <code>ResourceBundle.getBundle</code>.
 *
 * @param message
 *        the detail message
 * @param className
 *        the name of the resource class
 * @param key
 *        the key for the missing resource.
 * @param cause
 *        the cause (which is saved for later retrieval by the
 *        {@link Throwable.getCause()} method). (A null value is
 *        permitted, and indicates that the cause is nonexistent
 *        or unknown.)
 */
//    MissingResourceException::MissingResourceException(QString message, QString className, QString key, Throwable cause) {
//        //super(message, cause);
//        this->className = className;
//        this->key = key;
//    }

/**
 * Gets parameter passed by constructor.
 *
 * @return the name of the resource class
 */
QString MissingResourceException::getClassName()
{
    return className;
}

/**
 * Gets parameter passed by constructor.
 *
 * @return the key for the missing resource
 */
QString MissingResourceException::getKey()
{
    return key;
}
//void MissingResourceException::raise() const { throw *this; }
//std::exception *clone() const { return new MissingResourceException(*this); }
