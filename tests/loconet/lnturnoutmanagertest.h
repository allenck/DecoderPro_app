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
 Q_INVOKABLE /*public*/ void setUp()override;
 Q_INVOKABLE /*public*/ void tearDown();
 /*public*/ QString getSystemName(int i)override;

public slots:
 /*public*/ void testMisses()override;
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
