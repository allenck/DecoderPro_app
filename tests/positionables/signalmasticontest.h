#ifndef SIGNALMASTICONTEST_H
#define SIGNALMASTICONTEST_H
#include "positionableicontest.h"
#include "defaultsignalhead.h"

class SignalMastIconTest : public PositionableIconTest
{
 Q_OBJECT
public:
 SignalMastIconTest();
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

public slots:
 /*public*/ void testShowText();
 /*public*/ void testShowIcon();

private:
 SignalMast* s = nullptr;
 SignalMastIcon* to = nullptr;

};
class IH1SignalHead : public DefaultSignalHead
{
 Q_OBJECT
public:
 IH1SignalHead() : DefaultSignalHead("IH1") {}
protected:
 //@Override
 /*protected*/ void updateOutput() {
 }
};
class IH2SignalHead : public DefaultSignalHead
{
 Q_OBJECT
public:
 IH2SignalHead() : DefaultSignalHead("IH2") {}
protected:
 //@Override
 /*protected*/ void updateOutput() {
 }
};
class IH3SignalHead : public DefaultSignalHead
{
 Q_OBJECT
public:
 IH3SignalHead() : DefaultSignalHead("IH3") {}
protected:
 //@Override
 /*protected*/ void updateOutput() {
 }
};

#endif // SIGNALMASTICONTEST_H
