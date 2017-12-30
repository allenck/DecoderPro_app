#include "servletexception.h"

/**
 * Defines a general exception a servlet can throw when it
 * encounters difficulty.
 *
 * @author 	Various
 */

///*public*/ class ServletException extends Exception {

/**
 * Constructs a new servlet exception.
 *
 */

/*public*/
//ServletException::ServletException() : Exception() {
////super();
//}

/**
 * Constructs a new servlet exception with the
 * specified message. The message can be written
 * to the server log and/or displayed for the user.
 *
 * @param message 		a <code>String</code>
 *				specifying the text of
 *				the exception message
 *
 */

///*public*/ ServletException::ServletException(QString message) : Exception(message)
//{
////super(message);
//}

/**
 * Constructs a new servlet exception when the servlet
 * needs to throw an exception and include a message
 * about the "root cause" exception that interfered with its
 * normal operation, including a description message.
 *
 *
 * @param message 		a <code>String</code> containing
 *				the text of the exception message
 *
 * @param rootCause		the <code>Throwable</code> exception
 *				that interfered with the servlet's
 *				normal operation, making this servlet
 *				exception necessary
 *
 */

/*public*/
ServletException::ServletException(QString message, Throwable* rootCause) : Exception(message, rootCause){
//super(message, rootCause);
this->rootCause = rootCause;
}

/**
 * Constructs a new servlet exception when the servlet
 * needs to throw an exception and include a message
 * about the "root cause" exception that interfered with its
 * normal operation.  The exception's message is based on the localized
 * message of the underlying exception.
 *
 * <p>This method calls the <code>getLocalizedMessage</code> method
 * on the <code>Throwable</code> exception to get a localized exception
 * message. When subclassing <code>ServletException</code>,
 * this method can be overridden to create an exception message
 * designed for a specific locale.
 *
 * @param rootCause 	the <code>Throwable</code> exception
 * 				that interfered with the servlet's
 *				normal operation, making the servlet exception
 *				necessary
 *
 */

/*public*/
//ServletException::ServletException(Throwable rootCause) : Exception(rootCause) {
////super(rootCause);
//this->rootCause = rootCause;
//}

/**
 * Returns the exception that caused this servlet exception.
 *
 *
 * @return			the <code>Throwable</code>
 *				that caused this servlet exception
 *
 */

/*public*/ Throwable* ServletException::getRootCause() {
return rootCause;
}






