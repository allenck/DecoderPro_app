#ifndef JMRIJPANEL_H
#define JMRIJPANEL_H

#include <QWidget>
#include "exceptions.h"
#include <QMenu>
#include <QFrame>
#include "javaqt_global.h"
#include "jpanel.h"

class UserPreferencesManager;
class Logger;
class WindowInterface;
class JAVAQTSHARED_EXPORT JmriPanel : public JPanel
{
    Q_OBJECT
public:
    explicit JmriPanel(QWidget *parent = nullptr);
    virtual ~JmriPanel() {}
    /*public*/ virtual QString getHelpTarget();
    /*public*/ virtual QString getTitle() ;
    /*public*/ virtual bool isMultipleInstances();
    /*public*/ virtual QList<QMenu*> getMenus();
    /*public*/ WindowInterface* getWindowInterface();
    /*public*/ void setWindowInterface(WindowInterface* w) ;
    /*public*/ void virtual initComponents() /*throw (Exception)*/;
    /*public*/ void virtual initContext(QObject* context) /*throw (Exception)*/ ;
    virtual /*public*/ void dispose();
    /*public*/ void pack();
    /*public*/ QSize getPreferredSize();
    /*public*/ QSize getMaximumSize();

    /*public*/ void setSavePosition(bool save);
    /*public*/ void setFrameLocation();
    /*public*/ void setFrameRef(QString initref);

signals:

public slots:
private:
    /*private*/ WindowInterface* wi;// = NULL;
    void reSizeToFitOnScreen();
    Logger* log;
    bool reuseFrameSavedPosition;
    bool reuseFrameSavedSized;
    QString windowFrameRef;
    void moveEvent(QMoveEvent*);
    void resizeEvent(QResizeEvent*);
    /*private*/ void saveWindowSize(UserPreferencesManager* p);

};

#endif // JMRIJPANEL_H
