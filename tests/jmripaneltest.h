#ifndef JMRIPANELTEST_H
#define JMRIPANELTEST_H

#include <QObject>
#include "jmripanel.h"

class JmriPanelTest : public QObject
{
  Q_OBJECT
 public:
  explicit JmriPanelTest(QObject *parent = nullptr);
  /*public*/ virtual void setUp() = 0;
  /*public*/ virtual void tearDown() = 0;

 signals:

 public slots:
  /*public*/ void testCTor();
  /*public*/ virtual void testInitComponents();// throw (Exception);
  /*public*/ virtual void testGetHelpTarget();
  /*public*/ virtual void testGetTitle();

 protected:
  /*protected*/ JmriPanel* panel = nullptr;
  /*protected*/ QString helpTarget = "";
  /*protected*/ QString title = "";

};

#endif // JMRIPANELTEST_H
