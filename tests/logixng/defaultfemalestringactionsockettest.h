#ifndef DEFAULTFEMALESTRINGACTIONSOCKETTEST_H
#define DEFAULTFEMALESTRINGACTIONSOCKETTEST_H

#include "femalesockettestbase.h"
#include "femalesocketlistener.h"
#include "stringactionmemory.h"

class Memory;
class MyStringActionMemory;
class DefaultFemaleStringActionSocketTest : public FemaleSocketTestBase
{
  Q_OBJECT
 public:
  explicit DefaultFemaleStringActionSocketTest(QObject *parent = nullptr) : FemaleSocketTestBase(parent) {}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();


 public slots:
  ///*public*/  void testBundleClass();
  /*public*/  void testGetName();
  /*public*/  void testGetDescription();
  /*public*/  void testSetValue() /*throws Exception*/ ;
  /*public*/  void testGetConnectableClasses();

  private:
  /*private*/ QString _memorySystemName;
  /*private*/ Memory* _memory;
  /*private*/ MyStringActionMemory* _action;

 protected:
  /*protected*/ Manager/*<? extends NamedBean>*/* getManager() override;
  /*protected*/ FemaleSocket* getFemaleSocket(QString name);
  /*protected*/ bool hasSocketBeenSetup();

  friend class MyFemaleSocketListener10;
};

class MyFemaleSocketListener09 : public QObject, public FemaleSocketListener
{
  Q_OBJECT
  DefaultFemaleStringActionSocketTest* test;
 public:
  MyFemaleSocketListener09(DefaultFemaleStringActionSocketTest* test) {this->test = test;}
  //@Override
  /*public*/   void connected(FemaleSocket* socket) override{
  }

  //@Override
  /*public*/   void disconnected(FemaleSocket* socket) override{
  }
};
class MyFemaleSocketListener10 : public QObject, public FemaleSocketListener
{
  Q_OBJECT
  DefaultFemaleStringActionSocketTest* test;
 public:
  MyFemaleSocketListener10(DefaultFemaleStringActionSocketTest* test) {this->test = test;}
  //@Override
  /*public*/   void connected(FemaleSocket* socket) override{
   test->flag->set(true);
  }

  //@Override
  /*public*/   void disconnected(FemaleSocket* socket) override{
   test->flag->set(true);
  }
};

/*private*/ class MyStringActionMemory : public StringActionMemory {
Q_OBJECT
    /*private*/ bool _hasBeenSetup = false;
public:
    /*public*/  MyStringActionMemory(QString systemName) : StringActionMemory(systemName, ""){
        //super(systemName, null);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void setup() {
        _hasBeenSetup = true;
    }
  friend class DefaultFemaleStringActionSocketTest;
};

#endif // DEFAULTFEMALESTRINGACTIONSOCKETTEST_H
