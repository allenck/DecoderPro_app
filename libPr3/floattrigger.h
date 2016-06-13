#ifndef FLOATTRIGGER_H
#define FLOATTRIGGER_H
#include "trigger.h"

class Logger;
class FloatTrigger : public Trigger
{
 Q_OBJECT
public:
 //explicit FloatTrigger(QObject *parent = 0);
 /*public*/ FloatTrigger(QString name, float next, Trigger::CompareType ct, QObject *parent = 0) ;
 /*public*/ void setMatchValue(float next);
 /*public*/ float getMatchValue() ;
 /*public*/ void setCompareType(CompareType ct) ;
 /*public*/ CompareType getCompareType();
 /*public*/ void propertyChange(PropertyChangeEvent* event);
 /*public*/ QDomElement getXml();
 /*public*/ void setXml(QDomElement e);

signals:

public slots:
private:
 Logger* log;
 float match_value;
 CompareType compare_type;

};

#endif // FLOATTRIGGER_H
