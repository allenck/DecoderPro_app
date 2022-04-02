#ifndef DEFAULTFEMALESTRINGEXPRESSIONSOCKETTEST_H
#define DEFAULTFEMALESTRINGEXPRESSIONSOCKETTEST_H

#include "femalesockettestbase.h"
#include "stringexpressionmemory.h"
#include "femalesocketlistener.h"

class MyStringExpressionMemory;
class DefaultFemaleStringExpressionSocketTest : public FemaleSocketTestBase
{
  Q_OBJECT
 public:
  explicit DefaultFemaleStringExpressionSocketTest(QObject *parent = nullptr) : FemaleSocketTestBase(parent) {}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();

 public slots:
  /*public*/  void testGetName();
  /*public*/  void testGetDescription();
  /*public*/  void testSetValue() /*throws Exception*/;
  /*public*/  void testGetConnectableClasses();

 private:
  /*private*/ ConditionalNG* _conditionalNG;
  /*private*/ QString _memorySystemName;
  /*private*/ Memory* _memory;
  /*private*/ MyStringExpressionMemory* _expression;

 protected:
  /*protected*/  Manager/*<? extends NamedBean>*/* getManager()override;
  /*protected*/  FemaleSocket* getFemaleSocket(QString name)override;
  /*protected*/  bool hasSocketBeenSetup()override;

};

/*private*/ class MyStringExpressionMemory : public StringExpressionMemory {

    /*private*/ bool _hasBeenSetup = false;

    /*public*/ MyStringExpressionMemory(QString systemName) : StringExpressionMemory(systemName, "") {
        //super(systemName, null);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void setup() {
        _hasBeenSetup = true;
    }
  friend class DefaultFemaleStringExpressionSocketTest;
};

class MyFemaleSocketListener03 : public QObject, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  MyFemaleSocketListener03() : QObject() {}
  //@Override
  /*public*/  void connected(FemaleSocket* socket) {
  }

  //@Override
  /*public*/  void disconnected(FemaleSocket* socket) {
  }
};

class MyFemaleSocketListener04 : public QObject, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
  DefaultFemaleStringExpressionSocketTest* test;
 public:
  MyFemaleSocketListener04(DefaultFemaleStringExpressionSocketTest* test) : FemaleSocketListener() {this->test = test;}
  //@Override
  /*public*/  void connected(FemaleSocket* socket) {
   test->flag->set(true);
  }

  //@Override
  /*public*/  void disconnected(FemaleSocket* socket) {
   test->flag->set(true);
  }
};



#endif // DEFAULTFEMALESTRINGEXPRESSIONSOCKETTEST_H
