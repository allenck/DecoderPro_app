#ifndef DIGITALEXPRESSIONSTEST_H
#define DIGITALEXPRESSIONSTEST_H

#include <QObject>

class DigitalExpressionsTest : public QObject
{
  Q_OBJECT
 public:
  explicit DigitalExpressionsTest(QObject *parent = nullptr) : QObject(parent) {}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();

 public slots:
  void testLoad();
 signals:

};

#endif // DIGITALEXPRESSIONSTEST_H
