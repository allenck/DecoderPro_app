#ifndef LAYOUT_H
#define LAYOUT_H

#include <QObject>

#include "scalemanager.h"
#include "exceptions.h"
#include "propertychangeevent.h"

class Scale;
class Logger;

namespace TimeTable
{

class TimeTableDataManager;
class Layout : public QObject
{
 Q_OBJECT
public:
 explicit Layout(QObject *parent = nullptr);
 /*public*/ static /*final*/ QString SCALE_RATIO;// = "ScaleRatio";
 /*public*/ Layout(int layoutId, QString layoutName, Scale* scale, int fastClock, int throttles, bool metric,QObject *parent=nullptr);
 /*public*/ void setScaleMK();
 /*public*/ double getScaleMK();
 /*public*/ int getLayoutId();
 /*public*/ QString getLayoutName();
 /*public*/ void setLayoutName(QString newName);
 /*public*/ double getRatio();
 /*public*/ Scale *getScale();
 /*public*/ void setScale(Scale *newScale);
 /*public*/ int getFastClock();
 /*public*/ void setFastClock(int newClock);
 /*public*/ int getThrottles();
 /*public*/ void setThrottles(int newThrottles);
 /*public*/ bool getMetric();
 /*public*/ void setMetric(bool newMetric);
 /*public*/ QString toString();
signals:

public slots:
 /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throw (PropertyVetoException)*/;

private:
 static Logger* log;
 TimeTableDataManager* _dm;// = TimeTableDataManager::getDataManager();

 /*private*/ /*final*/ int _layoutId;
 /*private*/ QString _layoutName = "New Layout";  // NOI18N
 /*private*/ Scale* _scale = ScaleManager::getScale("HO");  // NOI18N
 /*private*/ int _fastClock = 4;
 /*private*/ int _throttles = 0;
 /*private*/ bool _metric = false;

 /*private*/ double _ratio = 87.1;
 /*private*/ double _scaleMK;          // Scale mile (real feet) or km (real meter)


};
}
#endif // LAYOUT_H
