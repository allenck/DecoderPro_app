#ifndef INTTRIGGER_H
#define INTTRIGGER_H
#include "trigger.h"

class Logger;
class IntTrigger : public Trigger
{
public:
 IntTrigger();
 /*public*/ IntTrigger(QString name, QObject *parent = 0) ;
 /*public*/ IntTrigger(QString name, int next, Trigger::CompareType ct, QObject *parent = 0) ;
 /*public*/ void setMatchValue(int next);
 /*public*/ int getMatchValue();
 /*public*/ void setCompareType(IntTrigger::CompareType ct) ;
 /*public*/ CompareType getCompareType() ;
 /*public*/ void propertyChange(PropertyChangeEvent* event);
 /*public*/ void setXml(QDomElement e);

private:
 int notch;
 CompareType compare_type;
 Logger* log;
};

#endif // INTTRIGGER_H
