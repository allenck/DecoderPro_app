#ifndef APPS_H
#define APPS_H
#include "jmrijframe.h"
#include "abstractshutdowntask.h"
#include "runnable.h"
#include "logger.h"
#include "appslib_global.h"
#include "filedrop.h"
#include "propertychangelistener.h"
#include "jlabel.h"


class QMenuBar;
class JFrame;
class PropertyChangeEvent;
class ConnectionConfig;
class WindowInterface;
class QFile;
class File;
class AWTEventListener;
class SplashWindow;
class AppConfigBase;
class APPSLIBSHARED_EXPORT Apps : public QWidget, public PropertyChangeListener
{
    Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)
public:
    //explicit Apps(QWidget *parent = 0);
    /*public*/ Apps(JFrame* frame, QWidget *parent = nullptr);
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
//void init();  // call init after constructor is complete
#ifdef SCRIPTING_ENABLED
/*public*/ static void ynstrument(QString path);
#endif
QObject* pself() override {return (QObject*)this;}


signals:

public slots:
/*public*/ void propertyChange(PropertyChangeEvent* ev) override;
void On_handleQuit();

private:
    static Logger* log;
    JFrame* _frame;
    qint64 start;
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
    void keyPressEvent(QKeyEvent *)override;
    // GUI members
    /*private*/ QMenuBar* menuBar;
    static QString nameString;// = "JMRI program";
    // line 4
    JLabel* cs4 = new JLabel();
    // line 5 optional
    QLabel* cs5 = new QLabel();
    // line 6 optional
    QLabel* cs6 = new QLabel();
    // line 7 optional
    QLabel* cs7 = new QLabel();
    //int[] connection = {-1,-1,-1,-1};
    QVector<ConnectionConfig*> connection = {NULL, NULL, NULL, NULL};
    QAction* prefsAction;
    /*public*/ void doPreferences();
#ifdef SCRIPTING_ENABLED
static Component* _jynstrumentSpace;// = NULL;
#endif

protected:
    QT_DEPRECATED /*protected*/ /*final*/ void addToActionModel();
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
    /*protected*/ virtual JPanel *statusPanel();
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
    /*static*/ /*protected*/ void createFrame(Apps* containedPane, JmriJFrame *frame);
    static /*protected*/ void loadFile(QString name);
    /*protected*/ /*static*/ void setApplication(QString name);
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
#ifdef SCRIPTING_ENABLED
    /*protected*/ void setJynstrumentSpace();
#endif
    static /*protected*/ void setJmriSystemProperty(QString key, QString value);

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

class AppsFileDrop : public FileDrop
{
 Q_OBJECT
 Component* _jynstrumentSpace;
 FileDrop::Listener* listener;
 Apps* apps;
public:
 AppsFileDrop(Component* _jynstrumentSpace, FileDrop::Listener* listener, Apps* apps);
 /*public*/ void filesDropped(QList<File*> files);
};

class LoadDecoders1 : public QObject
{
 Q_OBJECT
public:
  LoadDecoders1(QObject* parent = 0) {}
 ~LoadDecoders1() {}
public slots:
 void process();
 //void run();
signals:
 void finished();
 void error(QString err);

};

#endif // APPS_H
