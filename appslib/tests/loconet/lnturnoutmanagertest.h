#ifndef LNTURNOUTMANAGERTEST_H
#define LNTURNOUTMANAGERTEST_H
#include "abstractturnoutmgrtestbase.h"

class LocoNetInterfaceScaffold;
class LocoNetSystemConnectionMemo;

class LnTurnoutManagerTest : public AbstractTurnoutMgrTestBase
{
 Q_OBJECT
public:
 LnTurnoutManagerTest(QObject* parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();
 /*public*/ QString getSystemName(int i);

public slots:
 /*public*/ void testMisses();
 /*public*/ void testLocoNetMessages();
 /*public*/ void testCreateFromMessage1 ();
 /*public*/ void testCreateFromMessage2 ();
 /*public*/ void testCreateFromMessage3 ();
 /*public*/ void testCreateFromMessage4 ();
 /*public*/ void testAsAbstractFactory();
 /*public*/ void testOpcLongAck();

  private:
  /*private*/ LocoNetInterfaceScaffold* lnis;
  /*private*/ LocoNetSystemConnectionMemo* memo;
 static Logger* log;

};

#endif // LNTURNOUTMANAGERTEST_H
