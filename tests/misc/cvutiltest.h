#ifndef CVUTILTEST_H
#define CVUTILTEST_H

#include <QObject>

class CvUtilTest : public QObject
{
  Q_OBJECT
 public:
  explicit CvUtilTest(QObject *parent = nullptr);
  /*public*/ static void setUpClass();
  /*public*/ static void tearDownClass();
  Q_INVOKABLE /*public*/ void setUp();
  Q_INVOKABLE /*public*/ void tearDown();

 signals:

 public slots:
  /*public*/ void testExpandCvList();
  /*public*/ void testAddCvDescription();
  /*public*/ void testGetMaskDescription();

};

#endif // CVUTILTEST_H
