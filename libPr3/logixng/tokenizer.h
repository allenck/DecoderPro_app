#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <QObject>
#include "token.h"
#include "tokentype.h"
#include "atomicboolean.h"

class Tokenizer : public QObject
{
  Q_OBJECT
 public:
  explicit Tokenizer(QObject *parent = nullptr){setObjectName("Tokenizer");}
  /*public*/ static QList<Token *> *getTokens(QString expression) /*throws InvalidSyntaxException*/;

 signals:

 private:     /*private*/ static void addToken(Token* currentToken, QList<Token*>* tokens);
  /*private*/ static TokenType::TTYPE getTokenType(Token* currentToken, QChar ch, QChar nextChar, AtomicBoolean* eatNextChar);
  /*private*/ static bool isIntegerNumber(QString str);
  /*private*/ static bool isFloatingNumber(QString str);

};

#endif // TOKENIZER_H
