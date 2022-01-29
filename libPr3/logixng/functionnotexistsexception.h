#ifndef FUNCTIONNOTEXISTSEXCEPTION_H
#define FUNCTIONNOTEXISTSEXCEPTION_H
#include "parserexception.h"
/**
 * The function does not exists.
 *
 * @author Daniel Bergqvist   Copyright (C) 2020
 */
/*public*/ class FunctionNotExistsException : public  ParserException {

  public:
    /**
     * Constructs an instance of <code>FunctionNotExistsException</code> with the specified detail message.
     * @param msg the detail message.
     * @param functionName the name of the function
     */
    /*public*/ FunctionNotExistsException(QString msg, QString functionName) : ParserException(msg){
        //super(msg);
        _functionName = functionName;
    }

    /*public*/ QString  getFunctionName() {
        return _functionName;
    }
  private:
  /*private*/ /*final*/ QString _functionName;

    };
#endif // FUNCTIONNOTEXISTSEXCEPTION_H
