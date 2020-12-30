#ifndef SIGNALLINGSOURCEACTION_H
#define SIGNALLINGSOURCEACTION_H

#include <QAction>
#include "logger.h"
#include "libtables_global.h"
#include "actionevent.h"

class SignalMast;
class LIBTABLESSHARED_EXPORT SignallingSourceAction : public QAction
{
    Q_OBJECT
public:
    explicit SignallingSourceAction(QObject *parent = 0);
    /*public*/ SignallingSourceAction(QString s, QObject *parent = 0);
    /*public*/ SignallingSourceAction(QString s, SignalMast* source, QObject *parent = 0);
    /*public*/ void setMast(SignalMast* source);

signals:

public slots:
    /*public*/ void actionPerformed(JActionEvent* e = 0); // SLOT

private:
 SignalMast* source = nullptr;
 void init();
 Logger* log;
};

#endif // SIGNALLINGSOURCEACTION_H
