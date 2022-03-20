#ifndef LOGIXNGTEST_H
#define LOGIXNGTEST_H

#include <QObject>
#include "defaultconditionalng.h"

class MyConditionalNG;
class LogixNGTest : public QObject
{
  Q_OBJECT
 public:
  explicit LogixNGTest(QObject *parent = nullptr) : QObject(parent) {}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();


 public slots:
  /*public*/  void testSetParent();
  /*public*/  void testGetParent();
  /*public*/  void testState() /*throws JmriException*/;
  /*public*/  void testShortDescription();
  /*public*/  void testLongDescription();
  /*public*/  void testGetChild();
  /*public*/  void testGetChildCount();
  /*public*/  void testGetCategory();
  /*public*/  void testSwapConditionalNG();
  /*public*/  void testGetConditionalNG();
  //     /*public*/  void testAddConditionalNG() {
  /*public*/  void testGetConditionalNGByUserName();
  /*public*/  void testDeleteConditionalNG();
  /*public*/  void testActivateLogixNG();
  /*public*/  void testGetConditionalNG_WithoutParameters();
  /*public*/  void testGetLogixNG();
  /*public*/  void testGetRoot();

 signals:

};
/*private*/ class MyConditionalNG :public DefaultConditionalNG {
Q_OBJECT
    /*private*/ bool listenersAreRegistered =false;
public:
    /*public*/  MyConditionalNG(QString sys, QString user) /*throws NamedBean.BadUserNameException, NamedBean.BadSystemNameException*/
      : DefaultConditionalNG(sys, user)
    {
        //super(sys, user);
   listenersAreRegistered = false;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void registerListenersForThisClass() {
        listenersAreRegistered = true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void unregisterListenersForThisClass() {
        listenersAreRegistered = false;
    }
  friend class LogixNGTest;
};

#endif // LOGIXNGTEST_H
