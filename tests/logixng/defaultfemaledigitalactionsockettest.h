#ifndef DEFAULTFEMALEDIGITALACTIONSOCKETTEST_H
#define DEFAULTFEMALEDIGITALACTIONSOCKETTEST_H

#include "femalesockettestbase.h"
#include "actionturnout.h"
#include "femalesocketlistener.h"

class MyActionTurnout;
class DefaultFemaleDigitalActionSocketTest : public FemaleSocketTestBase
{
  Q_OBJECT
 public:
  explicit DefaultFemaleDigitalActionSocketTest(QObject *parent = nullptr) : FemaleSocketTestBase(parent){}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();

 public slots:
//  /*public*/  void testBundleClass();
  /*public*/  void testGetName();
  /*public*/  void testGetDescription();
  /*public*/  void testSetValue() /*throws Exception*/;
  /*public*/  void testGetConnectableClasses();


 private:
  /*private*/ MyActionTurnout* _action;

 protected:
  /*protected*/  Manager/*<? extends NamedBean>*/* getManager() override;
  /*protected*/  FemaleSocket* getFemaleSocket(QString name)override;
  /*protected*/  bool hasSocketBeenSetup()override;
};

/*private*/ class MyActionTurnout : ActionTurnout {
 Q_OBJECT

    /*private*/ bool _hasBeenSetup = false;
public:

    /*public*/ MyActionTurnout(QString systemName) : ActionTurnout(systemName, "") {
        //super(systemName, null);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void setup() {
        _hasBeenSetup = true;
    }
  friend class DefaultFemaleDigitalActionSocketTest;
};
class MyFemaleSocketListener01 : public QObject, public FemaleSocketListener
{
  Q_OBJECT
 public:
  MyFemaleSocketListener01()
   : FemaleSocketListener() {}
  //@Override
  /*public*/  void connected(FemaleSocket* socket) {
  }

  //@Override
  /*public*/  void disconnected(FemaleSocket* socket) {
  }
  friend class DefaultFemaleDigitalActionSocketTest;
};

class MyFemaleSocketListener02 : public QObject, public FemaleSocketListener
{
  Q_OBJECT
  DefaultFemaleDigitalActionSocketTest* test;
 public:
  MyFemaleSocketListener02(DefaultFemaleDigitalActionSocketTest* test)
   : FemaleSocketListener() {this->test = test;}
  //@Override
  /*public*/  void connected(FemaleSocket* socket) {
   test->flag->set(true);
  }

  //@Override
  /*public*/  void disconnected(FemaleSocket* socket) {
   test->flag->set(true);
  }
  friend class DefaultFemaleDigitalActionSocketTest;
};

#endif // DEFAULTFEMALEDIGITALACTIONSOCKETTEST_H
