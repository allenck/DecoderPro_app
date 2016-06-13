#ifndef SWINGSHUTDOWNTASK_H
#define SWINGSHUTDOWNTASK_H
#include "abstractshutdowntask.h"
#include "logger.h"
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT SwingShutDownTask : public AbstractShutDownTask
{
    Q_OBJECT
public:
    //explicit SwingShutDownTask(QObject *parent = 0);
    /*public*/ SwingShutDownTask(QString name, QString warning, QString action, QWidget* component, QObject *parent = 0);
    /*public*/ bool execute();
    QWidget* component;

signals:

public slots:
private:
    QString warning;
    QString action;
    Logger* log;
protected:
    /*protected*/ virtual bool checkPromptNeeded() ;
    /*protected*/ virtual bool doPrompt();
    /*protected*/ virtual bool doClose();
};

#endif // SWINGSHUTDOWNTASK_H
