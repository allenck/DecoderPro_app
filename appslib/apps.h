#ifndef APPS_H
#define APPS_H
#include "jmrijframe.h"
#include "abstractshutdowntask.h"
#include "runnable.h"
#include "logger.h"
#include "appslib_global.h"

class QMenuBar;
class JFrame;
class PropertyChangeEvent;
class ConnectionConfig;
class QLabel;
class WindowInterface;
class QFile;
class File;
class AWTEventListener;
class SplashWindow;
class AppConfigBase;
class APPSLIBSHARED_EXPORT Apps : public JmriJFrame
{
    Q_OBJECT
public:
    //explicit Apps(QWidget *parent = 0);
    /*public*/ Apps(JFrame* frame, QWidget *parent = 0);
static QString profileFilename;
static QString configFilename;// = "jmriconfig2.xml";  // usually overridden, this is default
static /*public*/ QWidget* buttonSpace();
static QWidget* _buttonSpace;// = NULL;
static AppConfigBase* prefs;// = NULL;

static /*public*/ AppConfigBase* getPrefs();
static /*public*/ bool handleQuit();
static /*public*/ bool handleRestart();
static /*public*/ QString getConfigFileName();
/*public*/ void windowClosing(QCloseEvent* e);
void initGui();

signals:

public slots:
/*public*/ void propertyChange(PropertyChangeEvent* ev);
void On_handleQuit();

private:
    Logger* log;
    class MyShutdownTask : public AbstractShutDownTask
    {
     public:
        /*public*/ bool execute();

    };

    class Run1 : public Runnable
    {
     /*public*/ void run();
    };

    class Run2 : public Runnable
    {
     /*public*/ void run();
    };

    static SplashWindow* sp;// = NULL;
    //static AWTEventListener* debugListener;// = NULL;
    static bool debugListener;
    static bool debugFired;// = false;  // true if we've seen F8 during startup
    static bool debugmsg;// = false;    // true while we're handling the "No Logix?" prompt window on startup
    /*private*/ bool doDeferredLoad(File* file);
    void keyPressEvent(QKeyEvent *);
    // GUI members
    /*private*/ QMenuBar* menuBar;
    static QString nameString;// = "JMRI program";
    // line 4
    QLabel* cs4;// = new QLabel();
    // line 5 optional
    QLabel* cs5;// = new QLabel();
    // line 6 optional
    QLabel* cs6;// = new QLabel();
    // line 7 optional
    QLabel* cs7;// = new QLabel();
    //int[] connection = {-1,-1,-1,-1};
    QVector<ConnectionConfig*> connection;// = {NULL, NULL, NULL, NULL};
    QAction* prefsAction;
    /*public*/ void doPreferences();

protected:
    /*protected*/ /*final*/ void addToActionModel();
    /*protected*/ static bool configOK;
    static bool configDeferredLoadOK;
    /*protected*/ void setButtonSpace();
    static /*protected*/ void splash(bool show);
    static /*protected*/ void splash(bool show, bool debug);
    static /*protected*/ QWidget* splashDebugMsg();
    static /*protected*/ void startupDebug();
    static /*protected*/ void setConfigFilename(QString def, char *args[]);
//    static QString nameString = "JMRI program";
    /*protected*/ static void setStartupInfo(QString name);
    /*protected*/ virtual QWidget* statusPanel();
    /*protected*/ virtual QString line1();
    /*protected*/ virtual QString line2();
    /*protected*/ virtual QString line3();
    /*protected*/ void buildLine4(QWidget* pane);
    /*protected*/ void buildLine5(QWidget* pane);
    /*protected*/ void buildLine6(QWidget* pane);
    /*protected*/ void buildLine7(QWidget* pane);
    /*protected*/ void buildLine(ConnectionConfig* conn, QLabel* cs, QWidget* pane);
    /*protected*/ void updateLine(ConnectionConfig* conn, QLabel* cs);
    /*protected*/ QString line8() ;
    /*protected*/ QString line9() ;
    /*protected*/ virtual QString logo();
    static /*protected*/ void createFrame(Apps* containedPane, JFrame* frame);
    /*protected*/ void createMenus(QMenuBar* menuBar, WindowInterface* wi);
    /*protected*/ void fileMenu(QMenuBar* menuBar, WindowInterface* wi);
    /*protected*/ void setPrefsFrameHelp(JmriJFrame* frame, QString location);
    /*protected*/ void editMenu(QMenuBar* menuBar, WindowInterface* wi);
    /*protected*/ void toolsMenu(QMenuBar* menuBar, WindowInterface* wi);
    /*protected*/ void operationsMenu(QMenuBar* menuBar, WindowInterface* wi);
    /*protected*/ void rosterMenu(QMenuBar* menuBar, WindowInterface* wi);
    /*protected*/ void panelMenu(QMenuBar* menuBar, WindowInterface* wi);
    /*protected*/ void scriptMenu(QMenuBar* menuBar, WindowInterface* wi);
    /*protected*/ void helpMenu(QMenuBar* menuBar, WindowInterface* wi);
    /*protected*/ QString mainWindowHelpID();
    /*protected*/ void systemsMenu(QMenuBar* menuBar, WindowInterface* wi);
    /*protected*/ void closeEvent(QCloseEvent *);
    /*protected*/ void debugMenu(QMenuBar* menuBar, WindowInterface* wi);

};
class WriteBlocksShutdownTask : public AbstractShutDownTask
{
 Q_OBJECT

 public:
    WriteBlocksShutdownTask(QString name);
public slots:
    /*public*/ bool execute();
private:
    Logger* log;
};
#endif // APPS_H
