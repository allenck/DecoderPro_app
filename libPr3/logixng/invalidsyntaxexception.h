#ifndef INVALIDSYNTAXEXCEPTION_H
#define INVALIDSYNTAXEXCEPTION_H
#include "parserexception.h"
/**
 * Invalid syntax.
 *
 * @author Daniel Bergqvist   Copyright (C) 2020
 */
/*public*/ class InvalidSyntaxException : public ParserException {

    /*private*/ /*final*/ int _position;
    public:
    /**
     * Constructs an instance of <code>InvalidExpressionException</code> with the specified detail message.
     * @param msg the detail message.
     */
    /*public*/ InvalidSyntaxException(QString msg): ParserException(msg){
        //super(msg);
        _position = -1;
    }

    /**
     * Constructs an instance of <code>InvalidExpressionException</code> with the specified detail message.
     * @param msg the detail message.
     * @param position the position
     */
    /*public*/ InvalidSyntaxException(QString msg, int position): ParserException(msg) {
        //super(msg);
        _position = position;
    }

    /*public*/ int getPosition() {
        return _position;
    }
};
#endif // INVALIDSYNTAXEXCEPTION_H
