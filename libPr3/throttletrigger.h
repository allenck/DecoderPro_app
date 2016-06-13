#ifndef THROTTLETRIGGER_H
#define THROTTLETRIGGER_H
#include "trigger.h"

class Logger;
class ThrottleTrigger : public Trigger
{
 Q_OBJECT
public:
 //explicit ThrottleTrigger(QObject *parent = 0);
 /*public*/ ThrottleTrigger(QString name, QObject *parent = 0);
 /*public*/ void propertyChange(PropertyChangeEvent* event = 0) ;
 /*public*/ QDomElement getXml();
 /*public*/ void setXml(QDomElement e);

signals:

public slots:

private:
 int current_notch, prev_notch;
 Logger* log;
};

#endif // THROTTLETRIGGER_H
