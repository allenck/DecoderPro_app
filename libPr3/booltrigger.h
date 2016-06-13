#ifndef BOOLTRIGGER_H
#define BOOLTRIGGER_H
#include "trigger.h"
#include "libPr3_global.h"

class Logger;
class LIBPR3SHARED_EXPORT BoolTrigger : public Trigger
{
 Q_OBJECT
public:
 //explicit BoolTrigger(QObject *parent = 0);
 /*public*/ BoolTrigger(QString name,QObject *parent=0);
 /*public*/ BoolTrigger(QString name, bool bv,QObject *parent=0) ;
 /*public*/ void setMatchValue(bool bv) ;
 /*public*/ bool getMatchValue() ;
 /*public*/ void propertyChange(PropertyChangeEvent* event);
 /*public*/ QDomElement getXml();
 /*public*/ void setXml(QDomElement e);

signals:

public slots:
private:
 Logger* log;
 bool match_value;

};

#endif // BOOLTRIGGER_H
