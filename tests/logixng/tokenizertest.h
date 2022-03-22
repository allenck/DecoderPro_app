#ifndef TOKENIZERTEST_H
#define TOKENIZERTEST_H

#include <QObject>
#include "tokenizer.h"

class Logger;
class TokenizerTest : public QObject
{
  Q_OBJECT
 public:
  explicit TokenizerTest(QObject *parent = nullptr) :QObject(parent) {}
  Q_INVOKABLE /*public*/ void setUp();
  Q_INVOKABLE /*public*/ void tearDown();


 public slots:
  /*public*/  void testCtor();
  /*public*/  void testGetTokens() /*throws InvalidSyntaxException*/;

 signals:

 private:
  /*private*/ void checkFirstToken(
          QList<Token*>* tokens,
          TokenType::TTYPE tokenType, QString string);
  static Logger* log;
};

#endif // TOKENIZERTEST_H
