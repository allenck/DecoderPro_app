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
#include "jrootpane.h"

class WindowInterface;
class UserPreferencesManager;
class AbstractAction;
class AbstractShutDownTask;
class LIBLAYOUTEDITORSHARED_EXPORT JmriJFrame : public JFrame
{
    Q_OBJECT
public:
    //explicit JmriJFrame(QWidget *parent = 0);
    /*public*/ JmriJFrame(bool saveSize, bool savePosition, QWidget *parent = nullptr);
    /*public*/ JmriJFrame(QWidget *parent = nullptr);
    /*public*/ JmriJFrame(QString name, QWidget *parent = nullptr);
    /*public*/ JmriJFrame(QString name, bool saveSize, bool savePosition, QWidget *parent = nullptr);
    /*public*/ ~JmriJFrame();
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
    /*public*/ void dispose() override;
    /*public*/ virtual void addHelpMenu(QString ref, bool direct);
    /*public*/ static QList<JmriJFrame*>* getFrameList();
    void init(bool saveSize, bool savePosition);
    void setLocation(int x, int y);
    /*public*/ QString getName();
    /*public*/ void setName(QString name);
    void setWindowTitle(const QString &title);
    void setTitle(QString _title) override;
    /*public*/ virtual void initComponents() /*throw (Exception)*/;
    QString getTitle() override;
    JPanel *getContentPane();
    JPanel *getContentPane(bool addLayout)override;
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
    /*public*/ void setFrameRef(QString windowFrameRef);
    virtual /*public*/ QVariant getProperty(QString key);
    /*public*/ void makePrivateWindow();
    virtual /*public*/ void windowClosing(QCloseEvent* e);
    /*public*/ virtual QString getClassName() = 0;
    /*public*/ void addNotify();
    /*public*/ void setFrameLocation();
    QMenu* windowMenu;
    /*public*/ QWidget* getGlassPane();
    /*public*/ void setGlassPane(QWidget* glassPane);
    /*public*/ void setBorder(Border* border) override {this->_border = border;}
    /*public*/ Border* getBorder() {return _border;}
    /*public*/ JRootPane* getRootPane() {return (JRootPane*)centralWidget();}


signals:

public slots:
//    void on_menuWindow_aboutToShow();
    void setupWindowRef();

private:
    static /*volatile*/ QList<JmriJFrame*>* frameList;// = new QList<JmriJFrame*>();
    QString windowFrameRef = QString();
    void offSetFrameOnScreen(JmriJFrame* f);
    /*private*/ AbstractShutDownTask* task = nullptr;
    Logger* log;
    /*private*/ bool modifiedFlag = false;
    QString name;
    //QMutex mutex;
    /*private*/ static QString escapeKeyAction;// = "escapeKeyAction";
    /*private*/ bool escapeKeyActionClosesWindow = false;
    //void closeEvent(QCloseEvent *);
    /*private*/ void saveWindowSize(UserPreferencesManager* p);
    /*private*/ bool mShown = false;
    QWidget* glassPane = nullptr;
    Border* _border = nullptr;

protected:
    /*protected*/ bool allowInFrameServlet = true;
    /*protected*/ bool reuseFrameSavedPosition = true;
    /*protected*/ bool reuseFrameSavedSized = true;
 /*protected*/ WindowInterface* windowInterface;
    /*
     * This field contains a list of properties that do not correspond to the
     * JavaBeans properties coding pattern, or known properties that do correspond
     * to that pattern. The default JmriJFrame implementation of
     * BeanInstance.hasProperty checks this hashmap before using introspection
     * to find properties corresponding to the JavaBean properties
     * coding pattern.
     */
    /*protected*/ QMap<QString, QVariant>* properties;// = new QMap<QString, QObject>();
//    /*protected*/ /*transient*/ WindowInterface windowInterface = NULL;
    /*protected*/ void setShutDownTask();
    /*protected*/ virtual void handleModified();
    /*protected*/ virtual void storeValues();
    void reSizeToFitOnScreen();

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
    friend class ListedTableFrame;
    friend class UserInterface;
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

// overload that won't provide class name
class JmriJFrameX : public  JmriJFrame
{
 Q_OBJECT
public:
 /*public*/ JmriJFrameX(QString name) : JmriJFrame(name) {}
 /*public*/ JmriJFrameX(QString name, bool b1, bool b2) : JmriJFrame(name, b1,b2) {}

 /*public*/ QString getClassName() {return JmriJFrame::getClassName();}
};

#endif // JMRIJFRAME_H
