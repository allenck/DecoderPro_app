#ifndef TIMETABLEGRAPHCOMMON_H
#define TIMETABLEGRAPHCOMMON_H

#include <QObject>
#include "timetabledatamanager.h"
#include "editscene.h"

class Logger;
namespace TimeTable
{
 class TimeTableGraphCommon : public QObject
 {
  Q_OBJECT
 public:
  explicit TimeTableGraphCommon(QObject *parent = nullptr);
  void init(int segmentId, int scheduleId, bool showTrainTimes, double height, double width, bool displayType);
  /*public*/ void doPaint(QPainter *g);

 signals:

 public slots:

 private:
  static Logger* log;
  /*final*/ QFont _stdFont;// = new Font(Font.SANS_SERIF, Font.PLAIN, 10);
  /*final*/ QFont _smallFont;// = new Font(Font.SANS_SERIF, Font.PLAIN, 8);
  TimeTableDataManager* _dataMgr;
  int _segmentId;
  int _scheduleId;

  Layout* _layout;
  int _throttles;

  Segment* _segment;

  TTSchedule* _schedule;
  int _startHour;
  int _duration;

  QList<Station*> _stations;
  QList<TTTrain*> _trains;
  QList<Stop*> _stops;

  // ------------ global variables ------------
  QMap<int, double> _stationGrid = QMap<int, double>();
  QMap<int, double> _hourMap = QMap<int, double>();
  QList<double> _hourGrid = QList<double>();
  int _infoColWidth = 0;
  double _hourOffset = 0;
  double _graphHeight = 0;
  double _graphWidth = 0;
  double _graphTop = 0;
  double _graphBottom = 0;
  double _graphLeft = 0;
  double _graphRight = 0;
  QPainter* _g2;
  bool _showTrainTimes;
  //PageFormat _pf;
  double _dimHeight = 0;
  double _dimWidth = 0;

  // ------------ train variables ------------
  QList<QRectF> _textLocation = QList<QRectF>();

  // Train
  QString _trainName;
  int _trainThrottle;
  QColor _trainColor;
  QPainterPath* _trainLine;

  // Stop
  int _stopCnt;
  int _stopIdx;
  int _arriveTime;
  int _departTime;

  // Stop processing
  double _maxDistance;
  QString _direction;
 //     int _baseTime;
  bool _firstStop;
  bool _lastStop;

  double _firstX;
  double _lastX;

  double _sizeMinute;
  double _throttleX;

  /*final*/ static QPen gridstroke;// = new BasicStroke(0.5f);
  /*final*/ static QPen stroke;// = new BasicStroke(2.0f);

  void drawInfoSection();
  void drawStationSection();
  void drawHours();
  void drawThrottleNumbers();
  void drawGraphGrid();
  void drawTrains();
  void drawTrainName(double x, double y, QString justify, bool invert, bool throttle);
  void drawTrainTime(int time, QString mode, double x, double y);
  QRectF adjustText(QRectF textRect);
  void setDirection();
  void setBegin(Stop *stop);
  void drawLine(Stop* stop);
  void setEnd(Stop* stop, bool endSegment);
  double calculateX(int time);

 };
}
#endif // TIMETABLEGRAPHCOMMON_H
