#ifndef APPS3_H
#define APPS3_H
#include "appsbase.h"
#include "appslib_global.h"

class Logger;
class AWTEventListener;
class SplashWindow;
class QSize;
class QToolBar;
class JmriJFrame;
class APPSLIBSHARED_EXPORT Apps3 : public AppsBase
{
 Q_OBJECT
public:
 //explicit Apps3(QObject *parent = 0);
 static /*public*/  void preInit(QString applicationName);
 /*public*/  Apps3(QString applicationName, QString configFileDef, QStringList args, QObject *parent =0);
 static /*public*/  QWidget* buttonSpace();

signals:

public slots:
 /*public*/  void createAndDisplayFrame();

private:
 static QWidget* _buttonSpace;// = null;
 static SplashWindow* sp;// = NULL;
 static AWTEventListener* debugListener;// = NULL;
 static bool debugFired;// = false;
 static bool debugmsg;// = false;
 /*private*/ void prepareFontLists();
 Logger* log;
protected:
 /*protected*/ static void setButtonSpace();
 /*protected*/ JmriJFrame* mainFrame;

 /*protected*/ void initializeHelpSystem();
  /*abstract*/ /*protected*/ virtual void createMainFrame();
 /*protected*/ void addToActionModel();
 /*protected*/ void setFloating(QToolBar* toolBar);
 /*protected*/ void displayMainFrame(QSize d);
 /*protected*/ void start();
 static /*protected*/ void splash(bool show);
 static /*protected*/ void splash(bool show, bool debug);
 static /*protected*/ QWidget* splashDebugMsg();
 static /*protected*/ void startupDebug();
 /*protected*/ void configureProfile();

};

#endif // APPS3_H
