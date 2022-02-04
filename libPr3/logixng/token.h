#ifndef TOKEN_H
#define TOKEN_H
#include "tokentype.h"

/**
 * A token used by the tokenizer and the parser
 */
 /*public*/  /*final*/ class Token  : public QObject{

    TokenType::TTYPE _tokenType = TokenType::NONE;
    QString _string;
    int _pos;
public:
    /*public*/  Token() {
        _tokenType =  TokenType::NONE;
        _string = "";
        _pos = 0;
    }

    /*public*/  Token(TokenType::TTYPE tokenType, QString string, int pos) {
        _tokenType = tokenType;
        _string = string;
        _pos = pos;
    }

//    /*public*/  TokenType getTokenType() {
//        return _tokenType;
//    }

    /*public*/  QString getString() {
        return _string;
    }

    /*public*/  int getPos() {
        return _pos;
    }
 friend class RecursiveDescentParser;
 friend class Tokenizer;
};

#endif // TOKEN_H
