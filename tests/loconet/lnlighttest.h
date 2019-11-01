#ifndef LNLIGHTTEST_H
#define LNLIGHTTEST_H

#include <QObject>

class LnLightTest : public QObject
{
 Q_OBJECT
public:
 explicit LnLightTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testCTor();

};

#endif // LNLIGHTTEST_H
