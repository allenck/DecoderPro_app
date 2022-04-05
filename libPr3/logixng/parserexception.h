#ifndef PARSEREXCEPTION_H
#define PARSEREXCEPTION_H
#include "exceptions.h"
#include "jmriexception.h"
/**
 * The parent of all parser exceptions.
 *
 * @author Daniel Bergqvist 2019
 */
/*public*/ class ParserException : public JmriException {
public:
    /**
     * Creates a new instance of <code>ParserException</code> without detail message.
     */
    /*public*/ ParserException() :  JmriException(){
     name = "ParserException";
    }


    /**
     * Constructs an instance of <code>ParserException</code> with the specified detail message.
     * @param msg the detail message.
     */
    /*public*/ ParserException(QString msg) :  JmriException(msg){
        //super(msg);
     name = "ParserException";

    }
};
#endif // PARSEREXCEPTION_H
