#ifndef DEFAULTFEMALEGENERICEXPRESSIONSOCKET2_TEST_H
#define DEFAULTFEMALEGENERICEXPRESSIONSOCKET2_TEST_H

#include <QObject>
#include "femalesocketlistener.h"
#include "stringexpressionconstant.h"
#include "expressionmemory.h"
#include "analogexpressionconstant.h"

class ConditionalNG;
class DefaultFemaleGenericExpressionSocket2_Test : public QObject
{
  Q_OBJECT
 public:
  explicit DefaultFemaleGenericExpressionSocket2_Test(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();


 signals:
public slots:
  /*public*/  void testEvaluateGeneric();

 private:
  /*private*/ ConditionalNG* _conditionalNG;
  /*private*/ FemaleSocketListener* _listener;
  class MyFemaleSocketListener : public FemaleSocketListener
  {
    //@Override
    /*public*/  void connected(FemaleSocket* socket) {
        // Do nothing
    }

    //@Override
    /*public*/  void disconnected(FemaleSocket* socket) {
        // Do nothing
    }

  };
  /*private*/ /*static*/ class MyAnalogExpression : public AnalogExpressionConstant {

      /*private*/ double _value;
      public:
      /*public*/  MyAnalogExpression(QString sys, QString user) : AnalogExpressionConstant(sys, user){
          //super(sys, user);
      }

      /** {@inheritDoc} */
      //@Override
      /*public*/  double evaluate() {
          return _value;
      }
      friend class DefaultFemaleGenericExpressionSocket2_Test;
  };


  /*private*/ /*static*/ class MyDigitalExpression : public ExpressionMemory {

      /*private*/ bool _value;
      public:
      /*public*/  MyDigitalExpression(QString sys, QString user) :  ExpressionMemory(sys, user){
          //super(sys, user);
      }

      /** {@inheritDoc} */
      //@Override
      /*public*/  bool evaluate() {
          return _value;
      }
    friend class DefaultFemaleGenericExpressionSocket2_Test;

  };


  /*private*/ /*static*/ class MyStringExpression : public StringExpressionConstant {

      /*private*/ QString _value;
      public:
      /*public*/  MyStringExpression(QString sys, QString user) : StringExpressionConstant(sys, user){
          //super(sys, user);
      }

      /** {@inheritDoc} */
      //@Override
      /*public*/  QString evaluate() {
          return _value;
      }
    friend class DefaultFemaleGenericExpressionSocket2_Test;

  };
};

#endif // DEFAULTFEMALEGENERICEXPRESSIONSOCKET2_TEST_H
