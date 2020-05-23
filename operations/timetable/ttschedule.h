#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QObject>
#include "timetabledatamanager.h"

namespace TimeTable
{
class TTSchedule : public QObject
{
 Q_OBJECT
public:
 /*public*/ TTSchedule(int layoutId, QObject *parent = nullptr);
 /*public*/ TTSchedule(int scheduleId, int layoutId, QString scheduleName, QString effDate, int startHour, int duration, QObject *parent= nullptr);
 /*public*/ int getScheduleId();
 /*public*/ int getLayoutId();
 /*public*/ QString getScheduleName();
 /*public*/ void setScheduleName(QString newName);
 /*public*/ QString getEffDate();
 /*public*/ void setEffDate(QString newDate);
 /*public*/ int getStartHour();
 /*public*/ void setStartHour(int newStartHour);
 /*public*/ int getDuration();
 /*public*/ void setDuration(int newDuration);
 /*public*/ QString toString();

signals:

public slots:
private:
 TimeTableDataManager* _dm = TimeTableDataManager::getDataManager();

 /*private*/ int _scheduleId = 0;
 /*private*/ int _layoutId = 0;
 /*private*/ QString _scheduleName = "New Schedule";  // NOI18N
 /*private*/ QString _effDate = "Today";  // NOI18N
 /*private*/ int _startHour = 0;
 /*private*/ int _duration = 24;

};
}
#endif // SCHEDULE_H
