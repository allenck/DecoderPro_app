#ifndef DECODERFILETEST_H
#define DECODERFILETEST_H

#include <QObject>
#include <QtXml>

class ProgDebugger;
class DecoderFileTest : public QObject
{
 Q_OBJECT
public:
 explicit DecoderFileTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();
 /*public*/ QDomElement decoder;// = null;
 /*public*/ void setupDecoder();

signals:

public slots:
 /*public*/ void testSingleVersionNumber();
 /*public*/ void testRangeVersionNumber();
 /*public*/ void testCtorRange();
 /*public*/ void testCtorLow();
 /*public*/ void testCtorHigh();
 /*public*/ void testSeveralSingleVersionNumber();
 /*public*/ void testMfgName();
 /*public*/ void testLoadTable();
 /*public*/ void testIncludeCheck();
 /*public*/ void testIncludeCheckRippleDown();
 /*public*/ void testIncludeCheckModel();
 /*public*/ void testExcludeCheck();
 /*public*/ void testExcludeCheckRippleDown();
 /*public*/ void testExcludeCheckModel();
 /*public*/ void testMinOut();
 /*public*/ void testMinFn();


private:
 ProgDebugger* p;// = new ProgDebugger();
 // static variables for the test XML structures
 QDomElement root;// = null;
 QDomDocument doc;// = null;

};

#endif // DECODERFILETEST_H
