#ifndef DEFAULTFEMALEANALOGEXPRESSIONSOCKETTEST_H
#define DEFAULTFEMALEANALOGEXPRESSIONSOCKETTEST_H

#include "femalesockettestbase.h"
#include "memory.h"
#include "analogexpressionmemory.h"
#include "defaultfemaleanalogexpressionsocket.h"

class ConditionalNG;
class MyAnalogExpressionMemory;
class DefaultFemaleAnalogExpressionSocketTest : public FemaleSocketTestBase
{
  Q_OBJECT
 public:
  explicit DefaultFemaleAnalogExpressionSocketTest(QObject *parent = nullptr);
  //@Rule
//  /*public*/   /*final*/ ExpectedException thrown = ExpectedException::none();
  Q_INVOKABLE /*public*/   void setUp();
  Q_INVOKABLE /*public*/   void tearDown();

 public slots:
  /*public*/   void testGetName();
  /*public*/   void testGetDescription();
  /*public*/   void testSetValue() /*throws Exception*/;
  /*public*/   void testGetConnectableClasses();

 private:
  /*private*/ ConditionalNG* _conditionalNG;
  /*private*/ QString _memorySystemName;
  /*private*/ Memory* _memory;
  /*private*/ MyAnalogExpressionMemory* _expression;

 protected:
  /*protected*/ Manager/*<? extends NamedBean>*/* getManager()override;
  /*protected*/ FemaleSocket* getFemaleSocket(QString name)override;
  /*protected*/ bool hasSocketBeenSetup()override;

  friend class MyAnalogExpressionMemory;

};
/*private*/ class MyAnalogExpressionMemory : public AnalogExpressionMemory {

  Q_OBJECT
    /*private*/ bool _hasBeenSetup = false;
    public:
    /*public*/ MyAnalogExpressionMemory(QString systemName) :  AnalogExpressionMemory(systemName, ""){
        //super(systemName, null);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void setup() {
        _hasBeenSetup = true;
    }
  friend class DefaultFemaleAnalogExpressionSocketTest;
};

class MyFemaleSocketListener : public QObject, public FemaleSocketListener
{
  Q_OBJECT
  DefaultFemaleAnalogExpressionSocketTest* test;
 public:
  MyFemaleSocketListener(DefaultFemaleAnalogExpressionSocketTest* test) {this->test = test;}
  //@Override
  /*public*/   void connected(FemaleSocket* socket) override{
  }

  //@Override
  /*public*/   void disconnected(FemaleSocket* socket) override{
  }
};
class My2FemaleSocketListener : public QObject, public FemaleSocketListener
{
  Q_OBJECT
  DefaultFemaleAnalogExpressionSocketTest* test;
 public:
  My2FemaleSocketListener(DefaultFemaleAnalogExpressionSocketTest* test) {this->test = test;}
  //@Override
  /*public*/   void connected(FemaleSocket* socket) override{
   test->flag->set(true);
  }

  //@Override
  /*public*/   void disconnected(FemaleSocket* socket) override{
   test->flag->set(true);
  }
};

#endif // DEFAULTFEMALEANALOGEXPRESSIONSOCKETTEST_H
