#ifndef COLORCHOOSERPANELTEST_H
#define COLORCHOOSERPANELTEST_H

#include <QObject>

class ColorChooserPanelTest : public QObject
{
 Q_OBJECT
public:
 explicit ColorChooserPanelTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testCtor();

};

#endif // COLORCHOOSERPANELTEST_H
