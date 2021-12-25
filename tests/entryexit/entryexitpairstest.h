#ifndef ENTRYEXITPAIRSTEST_H
#define ENTRYEXITPAIRSTEST_H

#include <QObject>
#include "exceptions.h"
#include "junitutil.h"
#include "layoutblockmanager.h"
#include <QColor>

class EntryExitPairs;
class LayoutBlockManager;
class SensorManager;
class TurnoutManager;
class EntryExitTestTools;
class LayoutEditor;
class EntryExitPairsTest : public QObject
{
 Q_OBJECT
public:
 explicit EntryExitPairsTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();
signals:

public slots:
 /*public*/ void testCTor();
 /*public*/ void testAddNxSourcePoint();
 /*public*/ void testGetSourceList();
 /*public*/ void testSetSingleSegmentRoute();
 /*public*/ void testDiscoverPairs() throw (Exception) ;
 /*public*/ void testNxPairDelete();

private:
 static EntryExitTestTools* tools;
 static QMap<QString, LayoutEditor*>* panels;// = new HashMap<>();

 static EntryExitPairs* eep;
 static LayoutBlockManager* lbm;
 static SensorManager* sm;
 static TurnoutManager* tm;
 void createModalDialogOperatorThread(QString dialogTitle, QString buttonText);

 friend class ReleaseUntil_EEPT1;
 friend class ReleaseUntil_EEPT2;
};

class ReleaseUntil_EEPT1 : public ReleaseUntil
{
 Q_OBJECT
 EntryExitPairsTest* test;
public:
 ReleaseUntil_EEPT1(EntryExitPairsTest* test) {this->test = test;}

 bool ready() /*throw (Exception)*/
 { return test->lbm->getLayoutBlock("B-Alpha-Main")->getUseExtraColor(); }
};

class ReleaseUntil_EEPT2 : public ReleaseUntil
{
 Q_OBJECT
 EntryExitPairsTest* test;
public:
 ReleaseUntil_EEPT2(EntryExitPairsTest* test) {this->test = test;}

 bool ready()  throw (Exception) { return test->tm->getTurnout("T-AE")->getKnownState() == Turnout::CLOSED; }
};

#endif // ENTRYEXITPAIRSTEST_H
