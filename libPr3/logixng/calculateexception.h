#ifndef CALCULATEEXCEPTION_H
#define CALCULATEEXCEPTION_H
#include "parserexception.h"

/**
 * Exception thrown when the calculation failed.
 *
 * @author Daniel Bergqvist 2019
 */
/*public*/ class CalculateException : public ParserException {
public:
    /**
     * Constructs an instance of <code>CalculateException</code> with the specified detail message.
     * @param msg the detail message.
     */
    /*public*/ CalculateException(QString msg) : ParserException(msg){
        //super(msg);
    }
};

#endif // CALCULATEEXCEPTION_H
