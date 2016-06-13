#ifndef NOTCHTRIGGER_H
#define NOTCHTRIGGER_H
#include "trigger.h"

class Logger;
class NotchTrigger : public Trigger
{
 Q_OBJECT
public:
 //explicit NotchTrigger(QObject *parent = 0);
 /*public*/ NotchTrigger(QString name, QObject *parent = 0) ;
 /*public*/ NotchTrigger(QString name, int prev, int cur,QObject *parent = 0);
 /*public*/ void setNotch(int next);
 /*public*/ int getNotch();
 /*public*/ void propertyChange(PropertyChangeEvent* event) ;
 /*public*/ QDomElement getXml() ;
 /*public*/ void setXml(QDomElement e);

signals:

public slots:
private:
 int current_notch, prev_notch;
 Logger* log;
};

#endif // NOTCHTRIGGER_H
