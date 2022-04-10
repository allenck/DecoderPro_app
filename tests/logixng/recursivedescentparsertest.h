#ifndef RECURSIVEDESCENTPARSERTEST_H
#define RECURSIVEDESCENTPARSERTEST_H

#include <QObject>
#include "variable.h"

class Logger;
class RecursiveDescentParserTest : public QObject
{
  Q_OBJECT
 public:
  explicit RecursiveDescentParserTest(QObject *parent = nullptr) :QObject() {}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();

 public slots:
  /*public*/  void testCtor();
  /*public*/  void testParseAndCalculate();

 signals:
private:
  static Logger* log;
  /*private*/ /*static*/ class MyVariable : public Variable {

      /*private*/ /*final*/ QString _name;
      /*private*/ /*final*/ QVariant _value;

      /*private*/ MyVariable(QString name, QVariant value) {
          _name = name;
          _value = value;
      }
public:
    //QObject* vself() override {return (QObject*)this;}
      //@Override
      /*public*/  QString getName() {
          return _name;
      }

      //@Override
      /*public*/  QVariant getValue(SymbolTable* symbolTable) {
          return _value;
      }

      //@Override
      /*public*/  void setValue(SymbolTable* symbolTable, QVariant value) {
          throw new UnsupportedOperationException("Not supported");
      }
    friend class  RecursiveDescentParserTest;

  };
};

#endif // RECURSIVEDESCENTPARSERTEST_H
