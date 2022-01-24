#ifndef LNCVDEVICETEST_H
#define LNCVDEVICETEST_H

#include <QObject>

class LncvDevice;
class LncvDeviceTest : public QObject
{
  Q_OBJECT
 public:
  explicit LncvDeviceTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

 signals:

 public slots:
  /*public*/ void testCTor();
  void testGetProductID();
  void testGetDestAddr();
  void testSetDestAddr();
  void testGetCvNum();
  void testSetCvNum();
  void testGetCvValue();
  void testSetCvValue();

 private:
  LncvDevice* lncvd;

};

#endif // LNCVDEVICETEST_H
