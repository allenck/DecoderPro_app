#ifndef SIGNALLINGACTION_H
#define SIGNALLINGACTION_H

#include <QAction>
#include "logger.h"
#include "actionevent.h"

class SignalMast;
class SignallingAction : public QAction
{
    Q_OBJECT
public:
    explicit SignallingAction(QObject *parent = 0);
    /*public*/ SignallingAction(QString s, QObject *parent = 0);
    /*public*/ void setMast(SignalMast* source, SignalMast* dest);

signals:

public slots:
    /*public*/ void actionPerformed(/*JActionEvent* e = 0*/);

private:
 Logger* log;
 void init();
 SignalMast* source;// = null;
 SignalMast* dest;// = null;

};

#endif // SIGNALLINGACTION_H
