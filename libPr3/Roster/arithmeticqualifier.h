#ifndef ARITHMETICQUALIFIER_H
#define ARITHMETICQUALIFIER_H
#include "abstractqualifier.h"

class Test : QObject
{
 Q_OBJECT
public:
  enum RELATIONS
  {
   INVALID,
   GE,  //("ge"), // greater than or equal
   LE,  //("le"),
   GT,  //("gt"),
   LT,  //("lt"),
   EQ,  //("eq"),
   NE,  //("ne"),
   EXISTS //("exists");
  };
  Test(QString relation, QObject* parent = 0);
  static RELATIONS decode(QString relation);
  static QString toString(RELATIONS test);

private:
  QString relation;

};

class ArithmeticQualifier : public AbstractQualifier
{
    Q_OBJECT
public:
    //explicit ArithmeticQualifier(QObject *parent = 0);
    /*public*/ ArithmeticQualifier(VariableValue* watchedVal, int value, QString relation, QObject *parent = 0);
    /*public*/ bool currentDesiredState();
    /*public*/ void update();

signals:
private:
    Test::RELATIONS test;
    int value;
    Logger* log;
    /*private*/ bool returnFromExistsLogic();
    bool warnedDoesntExist;// = false;
    /*private*/ bool valueOfExistsLogic();

public slots:
protected:
    /*protected*/ bool availableStateFromValue(int now);

};

#endif // ARITHMETICQUALIFIER_H
