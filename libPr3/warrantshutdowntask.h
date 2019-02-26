#ifndef WARRANTSHUTDOWNTASK_H
#define WARRANTSHUTDOWNTASK_H
#include "abstractshutdowntask.h"
#include <QMap>
class Logger;
class RosterSpeedProfile;
class WarrantShutdownTask : public AbstractShutDownTask
{
 Q_OBJECT

public:
 /*public*/ WarrantShutdownTask(QString name);
 /*public*/ bool execute();


private:
 static Logger* log;
 QMap<QString, bool>* _mergeCandidates;
 QMap<QString, RosterSpeedProfile*>* _mergeProfiles;
 QMap<QString, QMap<int, bool>* >* _anomalies;
 /*private*/ bool makeMergeCandidates();
 /*private*/ void makeMergeWindow();
 /*private*/ void merge();

};

#endif // WARRANTSHUTDOWNTASK_H
