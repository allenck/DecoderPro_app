#ifndef CIRCUITBUILDERTEST_H
#define CIRCUITBUILDERTEST_H

#include <QObject>
#include "exceptions.h"

class Logger;
class ControlPanelEditor;
class CircuitBuilder;
class CircuitBuilderTest : public QObject
{
 Q_OBJECT
public:
 explicit CircuitBuilderTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testCtor();
 /*public*/ void testEditCircuitFrame();
 /*public*/ void testEditCircuitError();
 /*public*/ void testEditPortals();
 /*public*/ void testEditCircuitPaths();
 /*public*/ void testEditPortalDirection();
 /*public*/ void testEditSignalFrame();
 /*public*/ void testEditPortalError();
 /*public*/ void testEditPortalErrorIcon() throw (Exception);
 /*public*/ void testNoBlock();

private:
 static Logger* log;
 ControlPanelEditor* cpe;
 CircuitBuilder* cb;
 void getCPEandCB();

};

#endif // CIRCUITBUILDERTEST_H
