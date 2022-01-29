#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <QObject>
#include "token.h"
#include "tokentype.h"

class Tokenizer : public QObject
{
  Q_OBJECT
 public:
  explicit Tokenizer(QObject *parent = nullptr){}
  /*public*/ static QList<Token*> getTokens(QString expression) /*throws InvalidSyntaxException*/;

 signals:

 private:     /*private*/ static void addToken(Token* currentToken, QList<Token*> tokens);
  /*private*/ static TokenType::TTYPE getTokenType(Token* currentToken, QChar ch, QChar nextChar, std::atomic<bool> eatNextChar);
  /*private*/ static bool isIntegerNumber(QString str);
  /*private*/ static bool isFloatingNumber(QString str);

};

#endif // TOKENIZER_H
