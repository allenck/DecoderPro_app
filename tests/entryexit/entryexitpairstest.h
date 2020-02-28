#ifndef ENTRYEXITPAIRSTEST_H
#define ENTRYEXITPAIRSTEST_H

#include <QObject>
#include "exceptions.h"

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

};

#endif // ENTRYEXITPAIRSTEST_H
