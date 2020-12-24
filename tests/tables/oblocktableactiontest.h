#ifndef OBLOCKTABLEACTIONTEST_H
#define OBLOCKTABLEACTIONTEST_H

#include <QObject>
#include "oblocktableaction.h"
#include "junitutil.h"

class OBlockTableActionTest : public QObject
{
  Q_OBJECT
 public:
  explicit OBlockTableActionTest(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/ void setUp() throw (Exception) ;
  Q_INVOKABLE/*public*/ void tearDown() throw (Exception);

 signals:

 public slots:
  /*public*/ void testCreate();
  /*public*/ void testGetClassDescription();
  /*public*/ void testIncludeAddButton();
  /*public*/ void testInvoke();
  /*public*/ void testInvokeTabbed();
  /*public*/ void testAddOBlock();
  /*public*/ void testRenameOBlock();
  /*public*/ void testAddPortal();
  /*public*/ void testAddSignal();

 protected:
  /*protected*/ OBlockTableAction* a = nullptr;
friend class OBTWaitFor;
};

class OBTWaitFor : public ReleaseUntil
{
  Q_OBJECT
  QThread* remove;
 public:
  OBTWaitFor( QThread* remove){ this->remove = remove;}
  bool ready() throw (Exception)
  {
   return !(remove->isRunning()/*isAlive()*/);
  }
};
#endif // OBLOCKTABLEACTIONTEST_H
