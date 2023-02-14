#ifndef TIMERUNIT_H
#define TIMERUNIT_H
#include "exceptions.h"

/**
 * Units for timer classes.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
/*public*/ /*enum*/class TimerUnit : public QObject{
Q_OBJECT
//    MilliSeconds(1, Bundle.getMessage("TimerUnit_UnitMilliSeconds"), Bundle.getMessage("TimerUnit_TimeMilliSeconds")),
//    Seconds(1000, Bundle.getMessage("TimerUnit_UnitSeconds"), Bundle.getMessage("TimerUnit_TimeSeconds")),
//    Minutes(1000 * 60, Bundle.getMessage("TimerUnit_UnitMinutes"), Bundle.getMessage("TimerUnit_TimeMinutes")),
//    Hours(1000 * 60 * 60, Bundle.getMessage("TimerUnit_UnitHours"), Bundle.getMessage("TimerUnit_TimeHours"));
    public:
  TimerUnit() {}
  enum VAL {MilliSeconds, Seconds, Minutes, Hours};
#if 0
 private:
    private final long _multiply;
    private final String _text;
    private final String _timeText;

    /*private*/ TimerUnit(long multiply, String text, String timeText) {
        this._multiply = multiply;
        this._text = text;
        this._timeText = timeText;
    }
#endif
    /*public*/static long getMultiply(VAL v) {
     switch (v) {
      case MilliSeconds: return 1;
      case Seconds: return 1000;
      case Minutes: return 1000 * 60;
      case Hours: return 1000 * 60 * 60;
     }
     throw new IllegalArgumentException();
    }

    //@Override
    /*public*/static  QString toString(VAL v) {
     switch (v) {
      case MilliSeconds: return tr("Milliseconds");
      case Seconds: return tr("Seconds");
      case Minutes: return tr("Minutes");
      case Hours: return tr("Hours");
     }
    }

    /*public*/static VAL valueOf(QString s)
    {
     if(s== tr("Milliseconds")) return MilliSeconds;
     if(s== tr("Seconds")) return Seconds;
     if(s== tr("Minutes")) return Minutes;
     if(s== tr("Hours")) return Hours;
     throw  new IllegalArgumentException(s + " is invalid!");
    }

    /*public*/static  QString getTimeWithUnit(VAL v, int delay) {

      switch (v) {
       case MilliSeconds: return tr("%1 Milliseconds").arg(delay);
       case Seconds: return tr("%1 Seconds").arg(delay);
       case Minutes: return tr("%1 Minutes").arg(delay);
       case Hours: return tr("%1 Hours").arg(delay);
      }
      //return MessageFormat.format(_timeText, time);
    }
    static QList<VAL> values()
    {
     return {MilliSeconds, Seconds, Minutes, Hours};
    }
};
#endif // TIMERUNIT_H
