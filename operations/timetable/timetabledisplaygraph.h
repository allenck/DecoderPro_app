#ifndef TIMETABLEDISPLAYGRAPH_H
#define TIMETABLEDISPLAYGRAPH_H
#include "jpanel.h"
#include "exceptions.h"

class EditScene;
namespace TimeTable
{
 class TimeTableDisplayGraph : public JPanel
 {
  Q_OBJECT
 public:
  TimeTableDisplayGraph();
  /*public*/ TimeTableDisplayGraph(int segmentId, int scheduleId, bool showTrainTimes, QWidget* parent = nullptr);
  /*public*/ void paint(QPainter* g);

 private:
  /*final*/ int _segmentId;
  /*final*/ int _scheduleId;
  /*final*/ bool _showTrainTimes;
  QPainter* _g2;
  void paintEvent(QPaintEvent *);

 };
}
#endif // TIMETABLEDISPLAYGRAPH_H
