#include "nosuchmethoderror.h"

/**
 * Thrown if an application tries to call a specified method of a
 * class (either static or instance), and that class no longer has a
 * definition of that method.
 * <p>
 * Normally, this error is caught by the compiler; this error can
 * only occur at run time if the definition of a class has
 * incompatibly changed.
 *
 * @author  unascribed
 * @since   JDK1.0
 */
//public
//class NoSuchMethodError extends IncompatibleClassChangeError {
//    private static final long serialVersionUID = -3765521442372831335L;

/**
 * Constructs a <code>NoSuchMethodError</code> with no detail message.
 */
/*public*/ NoSuchMethodError::NoSuchMethodError(QString msg) : Exception(msg)
{
    //super();
}

/**
 * Constructs a <code>NoSuchMethodError</code> with the
 * specified detail message.
 *
 * @param   s   the detail message.
 */
///*public*/ NoSuchMethodError(QString s) {
//    super(s);
//}
