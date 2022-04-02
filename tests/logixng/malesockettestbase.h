#ifndef MALESOCKETTESTBASE_H
#define MALESOCKETTESTBASE_H

#include <QObject>

class MaleSocket;
class BaseManager;
class MaleSocketTestBase : public QObject
{
  Q_OBJECT
 public:
  explicit MaleSocketTestBase(QObject *parent = nullptr) : QObject(parent) {}

  Q_INVOKABLE /*abstract*/ /*public*/ virtual void setUp()=0;
  Q_INVOKABLE /*abstract*/ /*public*/ virtual void tearDown()=0;

 public slots:
  /*public*/  void testExists() /*throws JmriException*/;
  /*public*/  void testLock();
  /*public*/  void testCategory() /*throws JmriException*/;
  /*public*/  void testShortDescription() /*throws JmriException*/;
  /*public*/  void testLongDescription() /*throws JmriException*/;
  /*public*/  void testGetSystemName() /*throws JmriException*/;
  /*public*/  void testUserName() /*throws JmriException*/;
  /*public*/  void testDisplayName() /*throws JmriException*/;
  /*public*/  void testState() /*throws JmriException*/;
  /*public*/  void testComment() /*throws JmriException*/;
  /*public*/  void testProperty();
  /*public*/  void testDebugConfig();

 signals:

 protected:
  /*protected*/ BaseManager/*<? extends NamedBean>*/* manager;
  /*protected*/ MaleSocket* maleSocketA;
  /*protected*/ MaleSocket* maleSocketB;

  /*protected*/ /*abstract*/ virtual QString getNewSystemName()=0;

};

#endif // MALESOCKETTESTBASE_H
