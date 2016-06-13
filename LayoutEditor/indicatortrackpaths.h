#ifndef INDICATORTRACKPATHS_H
#define INDICATORTRACKPATHS_H
#include "logger.h"

#include <QObject>
#include <QStringList>

class Editor;
class OBlock;
class LocoLable;
class IndicatorTrackPaths : public QObject
{
    Q_OBJECT
public:
    //explicit IndicatorTrackPaths(QObject *parent = 0);

signals:

public slots:
private:
    /*private*/ LocoLable* _loco;// = NULL;
    Logger* log;
    /*private*/ void removeLocoIcon();

protected:
    /*protected*/ QStringList _paths;      // list of paths that this icon displays
    /*protected*/ bool _showTrain; 		// this track icon should display _loco when occupied
    /*protected*/ IndicatorTrackPaths(QObject *parent = 0);
    /*protected*/ IndicatorTrackPaths* deepClone();
    /*protected*/ QStringList getPaths();
    /*protected*/ void setPaths(QStringList paths);
    /*protected*/ void addPath(QString path);
    /*protected*/ void removePath(QString path);
    /*protected*/ void setShowTrain(bool set);
    /*protected*/ bool showTrain() ;
    /*protected*/ QString setStatus(OBlock* block, int state);
    /*protected*/ void setLocoIcon(QString trainName, QPoint pt, QSize size, Editor* ed);
    /*protected*/ QString setStatus(int state) ;
friend class IndicatorTrackIcon;
friend class IndicatorTurnoutIcon;
};
class LocoLable
{

};

#endif // INDICATORTRACKPATHS_H
