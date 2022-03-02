#ifndef CONDITIONALNGTEST_H
#define CONDITIONALNGTEST_H

#include <QObject>

class ConditionalNG;
class ConditionalNGTest : public QObject
{
  Q_OBJECT
 public:
  explicit ConditionalNGTest(QObject *parent = nullptr) : QObject(parent)  {}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();
  /*public*/  void setupInitialConditionalNGTree(ConditionalNG* conditionalNG);

 public slots:
  void testGetBeanType();
  void testGetParent();
  void testGetRoot();
  void testGetLogixNG();
  void testState();
  void testConnectDisconnect();

 signals:

};

#endif // CONDITIONALNGTEST_H
