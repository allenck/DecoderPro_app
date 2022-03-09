#ifndef DEFAULTFEMALEDIGITALEXPRESSIONSOCKETTEST_H
#define DEFAULTFEMALEDIGITALEXPRESSIONSOCKETTEST_H

#include "femalesockettestbase.h"
#include <QObject>
#include "femalesocketlistener.h"
#include "expressionturnout.h"


class DefaultFemaleDigitalExpressionSocketTest : public FemaleSocketTestBase
{
  Q_OBJECT
  /*private*/ class MyExpressionTurnout : public ExpressionTurnout {

      /*private*/ bool _hasBeenSetup = false;
  public:
      /*public*/  MyExpressionTurnout(QString systemName) : ExpressionTurnout(systemName, ""){
          //super(systemName, null);
      }

      /** {@inheritDoc} */
      //@Override
      /*public*/  void setup() {
          _hasBeenSetup = true;
      }
    friend class DefaultFemaleDigitalExpressionSocketTest;
  };

 public:
  explicit DefaultFemaleDigitalExpressionSocketTest(QObject *parent = nullptr) : FemaleSocketTestBase(parent) {}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();

 public slots:
  /*public*/  void testGetName();
  /*public*/  void testGetDescription();
  /*public*/  void testSetValue() /*throws Exception */;
  /*public*/  void testGetConnectableClasses();

 private:
  /*private*/ ConditionalNG* _conditionalNG;
  /*private*/ MyExpressionTurnout* _expression;

 protected:
  /*protected*/ Manager/*<? extends NamedBean>*/* getManager()override;
  /*protected*/ FemaleSocket* getFemaleSocket(QString name)override;
  /*protected*/ bool hasSocketBeenSetup()override;
  friend class MyFemaleSocketListener06;
};

class MyFemaleSocketListener05 : public QObject, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  MyFemaleSocketListener05() : QObject() {}
  //@Override
  /*public*/  void connected(FemaleSocket* socket) {
  }

  //@Override
  /*public*/  void disconnected(FemaleSocket* socket) {
  }
};
class MyFemaleSocketListener06 : public QObject, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
  DefaultFemaleDigitalExpressionSocketTest* test;
 public:
  MyFemaleSocketListener06(DefaultFemaleDigitalExpressionSocketTest* test) : QObject() {this->test = test;}
  //@Override
  /*public*/  void connected(FemaleSocket* socket) {
   test->flag->set(true);
  }

  //@Override
  /*public*/  void disconnected(FemaleSocket* socket) {
   test->flag->set(true);

  }
};

#endif // DEFAULTFEMALEDIGITALEXPRESSIONSOCKETTEST_H
