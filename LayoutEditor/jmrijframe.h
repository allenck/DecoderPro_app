#ifndef JMRIJFRAME_H
#define JMRIJFRAME_H

#include "jframe.h"
#include <QList>
#include "logger.h"
#include "abstractshutdowntask.h"
#include <QMutex>
#include "exceptions.h"
#include "liblayouteditor_global.h"
#include "windowlistener.h"

class WindowInterface;
class UserPreferencesManager;
class AbstractAction;
class AbstractShutDownTask;
class LIBLAYOUTEDITORSHARED_EXPORT JmriJFrame : public JFrame
{
    Q_OBJECT
public:
    //explicit JmriJFrame(QWidget *parent = 0);
    /*public*/ JmriJFrame(bool saveSize, bool savePosition, QWidget *parent = 0);
    /*public*/ JmriJFrame(QWidget *parent = 0);
    /*public*/ JmriJFrame(QString name, QWidget *parent = 0);
    /*public*/ JmriJFrame(QString name, bool saveSize, bool savePosition, QWidget *parent = 0);
//    /*public*/ void pack();
//    /*public*/ QSize getPreferredSize();
//    /*public*/ QSize getMaximumSize();
    /*public*/ void moveEvent(QMoveEvent* e);
    /*public*/ void resizeEvent(QResizeEvent* e);
    /*public*/ void generateWindowRef();
    /*public*/ QString getWindowFrameRef();
    /*public*/ void setModifiedFlag(bool flag);
    /*public*/ bool getModifiedFlag();
    /*final*/ static QString WINDOW_MODIFIED;// = "windowModified";
    /*public*/ void markWindowModified(bool yes);
    /*public*/ void dispose();
    /*public*/ virtual void addHelpMenu(QString ref, bool direct);
    /*public*/ static QList<JmriJFrame*>* getFrameList();
    void init(bool saveSize, bool savePosition);
    void setLocation(int x, int y);
    /*public*/ QString getName();
    /*public*/ void setName(QString name);
    void setWindowTitle(const QString &title);
    void setTitle(QString _title);
    /*public*/ virtual void initComponents() /*throw (Exception)*/;
    QString getTitle();
    QWidget* getContentPane();
    void setAlwaysOnTop(bool checked);
    void setContentPane(QWidget*);
    /*public*/ void setEscapeKeyAction(AbstractAction* action);
    /*public*/ AbstractAction* getEscapeKeyAction();
    /*public*/ void setEscapeKeyClosesWindow(bool closesWindow);
    /*public*/ bool getEscapeKeyClosesWindow();
    bool eventFilter(QObject *target, QEvent *event);
    /*public*/ void componentMoved(QMoveEvent* e);
    /*public*/ void componentResized(QResizeEvent* e);
    /*public*/ void setSavePosition(bool save);
    /*public*/ void setSaveSize(bool save);
    /*public*/ bool getSavePosition();
    /*public*/ bool getSaveSize();
    /*public*/ void setAllowInFrameServlet(bool allow) ;
    /*public*/ bool getAllowInFrameServlet();
    /*public*/ static JmriJFrame* getFrame(QString name);


signals:

public slots:
//    void on_menuWindow_aboutToShow();
private:
    static /*volatile*/ QList<JmriJFrame*>* frameList;// = new QList<JmriJFrame*>();
    void reSizeToFitOnScreen();
    QString windowFrameRef;
    void setFrameLocation();
    void offSetFrameOnScreen(JmriJFrame* f);
    /*private*/ AbstractShutDownTask* task;// = NULL;
 Logger* log;
 /*private*/ bool modifiedFlag;// = false;
 QString name;
 //QMutex mutex;
 QMenu* windowMenu;
 /*private*/ static QString escapeKeyAction;// = "escapeKeyAction";
 /*private*/ bool escapeKeyActionClosesWindow;// = false;
 //void closeEvent(QCloseEvent *);
 /*private*/ void saveWindowSize(UserPreferencesManager* p);
 /*private*/ bool mShown;// = false;

protected:
    /*protected*/ bool allowInFrameServlet;// = true;
    /*protected*/ bool reuseFrameSavedPosition;// = true;
    /*protected*/ bool reuseFrameSavedSized;// = true;
 /*protected*/ WindowInterface* windowInterface;
    /*
     * This field contains a list of properties that do not correspond to the
     * JavaBeans properties coding pattern, or known properties that do correspond
     * to that pattern. The default JmriJFrame implementation of
     * BeanInstance.hasProperty checks this hashmap before using introspection
     * to find properties corresponding to the JavaBean properties
     * coding pattern.
     */
    /*protected*/ QMap<QString, QObject>* properties;// = new QMap<QString, QObject>();
//    /*protected*/ /*transient*/ WindowInterface windowInterface = NULL;
    /*protected*/ void setShutDownTask();
    /*protected*/ void handleModified();
    /*protected*/ virtual void storeValues();

    friend class LayoutEditorTools;
    friend class MyAbstractShutDownTask;
    friend class AddPanelIconDialog;
    friend class LogixTableAction;
    friend class LRouteTableAction;
    friend class RouteTableAction;
    friend class EditCircuitFrame;
    friend class SlipTurnoutTextEdit;
    friend class RosterFrame;
    friend class JmriJFrameWindowListener;
};
class MyAbstractShutDownTask : public AbstractShutDownTask
{
 Q_OBJECT
public:
    MyAbstractShutDownTask(QString windowTitle, JmriJFrame* frame, QObject* parent = 0);
    /*public*/ bool execute();

 private:
    JmriJFrame* frame;
    QString windowTitle;
};

class JmriJFrameWindowListener : public WindowListener
{
 Q_OBJECT
 JmriJFrame* frame;
public:
 JmriJFrameWindowListener(JmriJFrame* frame);
 void windowClosing(QCloseEvent*);
};

#endif // JMRIJFRAME_H
