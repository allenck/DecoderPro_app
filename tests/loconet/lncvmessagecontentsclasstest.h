#ifndef LNCVMESSAGECONTENTSCLASSTEST_H
#define LNCVMESSAGECONTENTSCLASSTEST_H

#include <QObject>

class LncvMessageContentsClassTest : public QObject
{
  Q_OBJECT
 public:
  explicit LncvMessageContentsClassTest(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/ void setUp();
  Q_INVOKABLE /*public*/ void tearDown();

 signals:

 public slots:
      /*public*/ void testCTorIllegalArgument();
      /*public*/ void testIsLnMessageASpecificLncvCommand();
      /*public*/ void testGetModuleNum();
      /*public*/ void testGetProdId();
      /*public*/ void testExtractMessageType();
};
#endif // LNCVMESSAGECONTENTSCLASSTEST_H
