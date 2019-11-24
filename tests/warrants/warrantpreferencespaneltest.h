#ifndef WARRANTPREFERENCESPANELTEST_H
#define WARRANTPREFERENCESPANELTEST_H

#include <QObject>

class WarrantPreferencesPanelTest : public QObject
{
 Q_OBJECT
public:
 explicit WarrantPreferencesPanelTest(QObject *parent = nullptr);
 Q_INVOKABLE/*public*/ void setUp();
 Q_INVOKABLE/*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testCTor();

};

#endif // WARRANTPREFERENCESPANELTEST_H
