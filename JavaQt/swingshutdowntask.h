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
//    /*public*/ bool execute();
    QWidget* component;
    /*public*/ /*final*/ bool call()final override;
    /*public*/ void run()override;

signals:

public slots:
private:
    QString warning;
    QString action;
    static Logger* log;
    /*private*/ bool _didPrompt = false;

protected:
    /*protected*/ bool checkPromptNeeded() ;
    /*protected*/ void didPrompt();
    /*protected*/ bool doPrompt();
    QT_DEPRECATED/*protected*/ bool doClose();
};
#endif // SWINGSHUTDOWNTASK_H
