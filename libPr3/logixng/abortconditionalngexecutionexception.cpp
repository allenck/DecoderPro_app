#include "abortconditionalngexecutionexception.h"

/**
 * This exception is thrown when the current excection of a ConditionalNG
 * should be aborted.
 *
 * @author Daniel Bergqvist 2020
 */
//public class AbortConditionalNGExecutionException extends JmriException {

    /**
     * Creates a new instance of <code>AbortConditionalNGExecutionException</code> without detail message.
     */
    /*public*/ AbortConditionalNGExecutionException::AbortConditionalNGExecutionException() : JmriException(){
    }

    /**
     * Constructs an instance of <code>AbortConditionalNGExecutionException</code> with the specified detail message.
     * @param msg the detail message.
     */
    /*public*/ AbortConditionalNGExecutionException::AbortConditionalNGExecutionException(QString msg) : JmriException(msg){
        //super(msg);
    }

    /**
     * Constructs an instance of <code>AbortConditionalNGExecutionException</code>
     * with a cause exception.
     * @param e the cause of this exception
     */
    /*public*/ AbortConditionalNGExecutionException::AbortConditionalNGExecutionException(Exception e) : JmriException(e){
        //super(e);
    }
