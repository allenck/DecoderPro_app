#ifndef JMRIJPANEL_H
#define JMRIJPANEL_H

#include <QWidget>
#include "exceptions.h"
#include <QMenu>
#include <QFrame>
#include "javaqt_global.h"

class Logger;
class WindowInterface;
class JAVAQTSHARED_EXPORT JmriPanel : public QFrame
{
    Q_OBJECT
public:
    explicit JmriPanel(QWidget *parent = 0);
    /*public*/ virtual QString getHelpTarget();
    /*public*/ virtual QString getTitle() ;
    /*public*/ virtual bool isMultipleInstances();
    /*public*/ virtual QList<QMenu*> getMenus();
    /*public*/ WindowInterface* getWindowInterface();
    /*public*/ void setWindowInterface(WindowInterface* w) ;
    /*public*/ void virtual initComponents() /*throw (Exception)*/;
    /*public*/ void virtual initContext(QObject* context) /*throw (Exception)*/ ;
    /*public*/ void dispose();
    /*public*/ void pack();
    /*public*/ QSize getPreferredSize();
    /*public*/ QSize getMaximumSize();

signals:

public slots:
private:
    /*private*/ WindowInterface* wi;// = NULL;
    void reSizeToFitOnScreen();
    Logger* log;
};

#endif // JMRIJPANEL_H
