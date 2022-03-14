#ifndef LOGIXNG_MANAGERTEST_H
#define LOGIXNG_MANAGERTEST_H

#include <QObject>

class LogixNG_ManagerTest : public QObject
{
  Q_OBJECT
 public:
  explicit LogixNG_ManagerTest(QObject *parent = nullptr) : QObject(parent){}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();

 public slots:
  /*public*/  void testValidSystemNameFormat();


 signals:

 private:
  /*private*/ void testSystemNameFormat(QString prefix);
  /*private*/ void testValidSystemNameFormat(QString prefix);

 protected:

};

#endif // LOGIXNG_MANAGERTEST_H
