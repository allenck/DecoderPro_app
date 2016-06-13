#include "indexoutofboundsexception.h"

IndexOutOfBoundsException::IndexOutOfBoundsException(QObject *parent) :
    QObject(parent)
{
}
/**
 * Thrown to indicate that an index of some sort (such as to an array, to a
 * string, or to a vector) is out of range.
 * <p>
 * Applications can subclass this class to indicate similar exceptions.
 *
 * @author  Frank Yellin
 * @since   JDK1.0
 */
//public
//class IndexOutOfBoundsException extends RuntimeException {

    /**
     * Constructs an <code>IndexOutOfBoundsException</code> with no
     * detail message.
     */
//    public IndexOutOfBoundsException() {
//        super();
//    }

    /**
     * Constructs an <code>IndexOutOfBoundsException</code> with the
     * specified detail message.
     *
     * @param   s   the detail message.
     */
    /*public*/ IndexOutOfBoundsException::IndexOutOfBoundsException(QString s)
    {
        //super(s);
    msg = s;
    }
