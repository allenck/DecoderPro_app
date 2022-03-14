#ifndef DEFAULTFEMALEDIGITALBOOLEANACTIONSOCKETTEST_H
#define DEFAULTFEMALEDIGITALBOOLEANACTIONSOCKETTEST_H

#include "femalesockettestbase.h"
#include "digitalbooleanonchange.h"

class MyOnChangeAction;
class DefaultFemaleDigitalBooleanActionSocketTest : public FemaleSocketTestBase
{
  Q_OBJECT
 public:
  explicit DefaultFemaleDigitalBooleanActionSocketTest(QObject *parent = nullptr) : FemaleSocketTestBase(parent) {}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();

 public slots:
  /*public*/  void testGetName();
  /*public*/  void testGetDescription();
  /*public*/  void testSetValue() /*throws Exception*/;
  /*public*/  void testGetConnectableClasses();

 private:
  /*private*/ class MyOnChangeAction : public DigitalBooleanOnChange {

      /*private*/ bool _hasBeenSetup = false;

      /*public*/  MyOnChangeAction(QString systemName) : DigitalBooleanOnChange(systemName, "", DigitalBooleanOnChange::Trigger::CHANGE){
//          super(systemName, null, DigitalBooleanOnChange.Trigger.CHANGE);
      }

      /** {@inheritDoc} */
      //@Override
      /*public*/  void setup() {
          _hasBeenSetup = true;
      }
    friend class DefaultFemaleDigitalBooleanActionSocketTest;

  };
  /*private*/ MyOnChangeAction* _action;

 protected:
  /*protected*/ Manager/*<? extends NamedBean>*/* getManager()override;
  /*protected*/ FemaleSocket* getFemaleSocket(QString name)override;
  /*protected*/ bool hasSocketBeenSetup()override;

 friend class MyFemaleSocketListener08;
};

class MyFemaleSocketListener07 : public QObject, public FemaleSocketListener
{
  Q_OBJECT
  DefaultFemaleDigitalBooleanActionSocketTest* test;
 public:
  MyFemaleSocketListener07(DefaultFemaleDigitalBooleanActionSocketTest* test) {this->test = test;}
  //@Override
  /*public*/   void connected(FemaleSocket* socket) override{
  }

  //@Override
  /*public*/   void disconnected(FemaleSocket* socket) override{
  }
};
class MyFemaleSocketListener08 : public QObject, public FemaleSocketListener
{
  Q_OBJECT
  DefaultFemaleDigitalBooleanActionSocketTest* test;
 public:
  MyFemaleSocketListener08(DefaultFemaleDigitalBooleanActionSocketTest* test) {this->test = test;}
  //@Override
  /*public*/   void connected(FemaleSocket* socket) override{
   test->flag->set(true);
  }

  //@Override
  /*public*/   void disconnected(FemaleSocket* socket) override{
   test->flag->set(true);
  }
};

#endif // DEFAULTFEMALEDIGITALBOOLEANACTIONSOCKETTEST_H
