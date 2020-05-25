#include "timetabledisplaygraph.h"
#include "timetablegraphcommon.h"

namespace TimeTable
{
 TimeTableDisplayGraph::TimeTableDisplayGraph()
 {

 }
 /**
  * Display a timetable graph.
  * @author Dave Sand Copyright (c) 2019
  */
 // /*public*/ class TimeTableDisplayGraph extends JPanel {

     /**
      * Initialize the data used by paint() and supporting methods when the
      * panel is displayed.
      * @param segmentId The segment to be displayed.  For multiple segment
      * layouts separate graphs are required.
      * @param scheduleId The schedule to be used for this graph.
      * @param showTrainTimes When true, include the minutes portion of the
      * train times at each station.
      */
     /*public*/ TimeTableDisplayGraph::TimeTableDisplayGraph(int segmentId, int scheduleId, bool showTrainTimes, QWidget *parent) {
         _segmentId = segmentId;
         _scheduleId = scheduleId;
         _showTrainTimes = showTrainTimes;
     }


     //@Override
     /*public*/ void TimeTableDisplayGraph::paint(QPainter *g) {
//         if (qobject_cast< EditScene*>(g))
//         {
//             _g2 = (EditScene*) g;
//         } else {
//             throw  IllegalArgumentException();
//         }
         QSize dim = size();
         double dimHeight = dim.height();
         double dimWidth = dim.width();

         TimeTableGraphCommon* graph = new TimeTableGraphCommon();
         graph->init(_segmentId, _scheduleId, _showTrainTimes, dimHeight, dimWidth, true);
         graph->doPaint(g);

    }

 /*private*/ void TimeTableDisplayGraph::paintEvent(QPaintEvent *)
 {
  _g2 =  new QPainter(this);
  paint(_g2);
 }

}

