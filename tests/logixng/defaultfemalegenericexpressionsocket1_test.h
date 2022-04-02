#ifndef DEFAULTFEMALEGENERICEXPRESSIONSOCKET1_TEST_H
#define DEFAULTFEMALEGENERICEXPRESSIONSOCKET1_TEST_H

#include "femalesockettestbase.h"
#include "femalesocketlistener.h"
#include "expressionturnout.h"


class DefaultFemaleGenericExpressionSocket;
class DefaultFemaleGenericExpressionSocket1_Test : public FemaleSocketTestBase
{
  Q_OBJECT
 public:
  explicit DefaultFemaleGenericExpressionSocket1_Test(QObject *parent = nullptr) : FemaleSocketTestBase(parent) {}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();

 public slots:
  /*public*/  void testSWISystemName();
  /*public*/  void testSetParentForAllChildren() /*throws SocketAlreadyConnectedException */;
  /*public*/  void testSocketType();
  /*public*/  void testGetName();
  /*public*/  void testGetDescription();
  /*public*/  void testConnect();
  /*public*/  void testDisconnect() /*throws SocketAlreadyConnectedException */;
  /*public*/  void testConnectableClasses() /*throws SocketAlreadyConnectedException*/;
  /*public*/  void testIsCompatibleSocket();
  /*public*/  void testGetAndSetSocketType() /*throws SocketAlreadyConnectedException*/;
  /*public*/  void testIsCompatible();
  /*public*/  void testDoI18N();

 private:
  /*private*/ ConditionalNG* _conditionalNG;
  /*private*/ FemaleSocketListener* _listener;
  /*private*/ DefaultFemaleGenericExpressionSocket* _femaleGenericSocket;
  class MyFemaleSocketListener : public FemaleSocketListener
  {
   //@Override
   /*public*/  void connected(FemaleSocket* socket) override{
   }

   //@Override
   /*public*/  void disconnected(FemaleSocket* socket)override {
   }
  };
  class MyFemaleSocketListener02 : public FemaleSocketListener
  {
   DefaultFemaleGenericExpressionSocket1_Test* test;
   public:
   MyFemaleSocketListener02(DefaultFemaleGenericExpressionSocket1_Test* test)  {this->test = test;}
   //@Override
   /*public*/  void connected(FemaleSocket* socket) override{
       test->flag->set(true);
   }

   //@Override
   /*public*/  void disconnected(FemaleSocket* socket) override{
       test->flag->set(true);
   }
  };
  /*private*/ class MyExpressionTurnout : public ExpressionTurnout {

      /*private*/ bool _hasBeenSetup = false;
   public:
      /*public*/  MyExpressionTurnout(QString systemName) :ExpressionTurnout(systemName, "") {
          //super(systemName, null);
      }

      /** {@inheritDoc} */
      //@Override
      /*public*/  void setup() {
          _hasBeenSetup = true;
      }
   friend class DefaultFemaleGenericExpressionSocket1_Test;
  };
  /*private*/ MyExpressionTurnout* _expression;
  /*private*/ void checkConnectableClasses(FemaleSocket* femaleSocket);

 protected:
  /*protected*/ Manager/*<? extends NamedBean>*/* getManager()override;
  /*protected*/ FemaleSocket* getFemaleSocket(QString name)override;
  /*protected*/ bool hasSocketBeenSetup()override;
  friend class DefaultFemaleGenericExpressionSocket1_Test;
};

class MyExpressionTurnout : public ExpressionTurnout
{

};

#endif // DEFAULTFEMALEGENERICEXPRESSIONSOCKET1_TEST_H
