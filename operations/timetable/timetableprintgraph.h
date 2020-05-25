#ifndef TIMETABLEPRINTGRAPH_H
#define TIMETABLEPRINTGRAPH_H

#include <QObject>
//#include "printable.h"

class Logger;
namespace TimeTable
{

class TimeTablePrintGraph : public QObject//, public Printable
{
 Q_OBJECT
public:
 /*public*/ TimeTablePrintGraph(int segmentId, int scheduleId, bool showTrainTimes, bool twoPage);
 void printGraph();

private:
 static Logger* log;
 /*final*/ int _segmentId;
 /*final*/ int _scheduleId;
 /*final*/ bool _showTrainTimes;
 /*final*/ bool _twoPage;

};
}
#endif // TIMETABLEPRINTGRAPH_H
