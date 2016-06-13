#ifndef TRACKER_H
#define TRACKER_H

#include <QObject>
#include <QLinkedList>
#include <QFont>
#include <QColor>

class Logger;
class Portal;
class OBlock;
class Tracker : public QObject
{
 Q_OBJECT
public:
 //explicit Tracker(QObject *parent = 0);
 Tracker(OBlock* block, QString name, QObject *parent = 0);
 /*public*/ void setupCheck();
 /*public*/ QString toString();

signals:
private:
 /*private*/ QString _trainName;
 /*private*/ QList<OBlock*> _headRange;	// blocks reachable from head block
 /*private*/ QList<OBlock*> _tailRange;	// blocks reachable from tail block
 /*private*/ QList<OBlock*> _lostRange;	// reachable block occupied by someone else
 /*private*/ QLinkedList<OBlock*> _occupies;	// blocks occupied by train
 /*private*/ Portal* _headPortal;
 /*private*/ Portal* _tailPortal;
 /*private*/ qint64 _time;
 enum TRACKERS
 {
  NO_BLOCK = 0,
  ENTER_BLOCK = 1,
  LEAVE_BLOCK = 2,
  ERROR_BLOCK = 3
 };
 /*private*/ QColor _markerForeground;
 /*private*/ QColor _markerBackground;
 /*private*/ QFont _markerFont;
 /*private*/ void showBlockValue(OBlock* block);
 Logger* log;
 /*private*/ void removeName(OBlock* block);
 /*private*/ bool recovery(OBlock* block);
 /*private*/ QList<OBlock*> makeRange();
 /*private*/ void addtoHeadRange(OBlock* b) ;
 /*private*/ void addtoTailRange(OBlock* b);
 static /*private*/ Portal* getPortalBetween(OBlock* blkA, OBlock* blkB);

public slots:
protected:
 /*protected*/ QString getTrainName();
 /*final*/ /*protected*/ OBlock* getHeadBlock() ;
 /*final*/ /*protected*/ OBlock* getTailBlock() ;
 /*protected*/ QString getStatus();
 /*protected*/ QLinkedList<OBlock*> getBlocksOccupied();
 /*protected*/ QList<OBlock*> getRange();
 /*protected*/ int move(OBlock* block, int state);
 /*protected*/ void removeBlock(OBlock* block);

friend class TrackerTableAction;
friend class TableFrame;
friend class TrackerTableModel;
};

#endif // TRACKER_H
