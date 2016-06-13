#ifndef QUIETSHUTDOWNTASK_H
#define QUIETSHUTDOWNTASK_H
#include "abstractshutdowntask.h"
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT QuietShutDownTask : public AbstractShutDownTask
{
    Q_OBJECT
public:
    explicit QuietShutDownTask(QString name, QObject *parent = 0);
    /*public*/ bool execute();

signals:

public slots:
 protected:
    /*protected*/ virtual bool doAction();

};

#endif // QUIETSHUTDOWNTASK_H
