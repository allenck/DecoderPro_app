#ifndef WRONGNUMBEROFPARAMETERSEXCEPTION_H
#define WRONGNUMBEROFPARAMETERSEXCEPTION_H
#include "parserexception.h"

/**
 * Wrong number of parameters to a function.
 *
 * @author Daniel Bergqvist 2019
 */
/*public*/ class WrongNumberOfParametersException : ParserException {

 public:
    /**
     * Constructs an instance of <code>CalculateException</code> with the specified detail message.
     * @param msg the detail message.
     */
    /*public*/ WrongNumberOfParametersException(QString msg) : ParserException(msg){
        //super(msg);
    }
};

#endif // WRONGNUMBEROFPARAMETERSEXCEPTION_H
