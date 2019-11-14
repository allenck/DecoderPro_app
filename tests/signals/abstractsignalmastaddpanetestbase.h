#ifndef ABSTRACTSIGNALMASTADDPANETESTBASE_H
#define ABSTRACTSIGNALMASTADDPANETESTBASE_H

#include <QObject>

class SignalMastAddPane;
class AbstractSignalMastAddPaneTestBase : public QObject
{
 Q_OBJECT
public:
 explicit AbstractSignalMastAddPaneTestBase(QObject *parent = nullptr);
 Q_INVOKABLE virtual /*public*/ void setUp();
 Q_INVOKABLE virtual /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testInfoMethods();

protected:
 /*abstract*/ virtual /*protected*/ SignalMastAddPane* getOTT() =0;

};

#endif // ABSTRACTSIGNALMASTADDPANETESTBASE_H
