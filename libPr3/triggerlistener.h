#ifndef TRIGGERLISTENER_H
#define TRIGGERLISTENER_H

#include <QObject>

class TriggerListener : public QObject
{
 Q_OBJECT
public:
 explicit TriggerListener(QObject *parent = 0);
 virtual /*public*/ void takeAction();

 virtual /*public*/ void takeAction(int i);

 virtual /*public*/ void takeAction(float f);

signals:

public slots:

};

#endif // TRIGGERLISTENER_H
