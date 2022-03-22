#ifndef DEFAULTCONDITIONALMANAGERTEST_H
#define DEFAULTCONDITIONALMANAGERTEST_H

#include <abstractmanagertestbase.h>

class DefaultConditionalManagerTest : public AbstractManagerTestBase
{
 public:
  explicit DefaultConditionalManagerTest(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();
 public slots:
  /*public*/  void testCtor();
  /*public*/  void testCreate();
  /*public*/  void testUserNameOverlap();

};

#endif // DEFAULTCONDITIONALMANAGERTEST_H
