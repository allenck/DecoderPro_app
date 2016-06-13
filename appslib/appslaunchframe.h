#ifndef APPSLAUNCHFRAME_H
#define APPSLAUNCHFRAME_H
#include"jmrijframe.h"
#include "appslib_global.h"


class Action;
class WindowInterface;
class AppsLaunchPane;
class QMenuBar;
class APPSLIBSHARED_EXPORT AppsLaunchFrame : public JmriJFrame
{
 Q_OBJECT
public:
 //explicit AppsLaunchFrame(QWidget *parent = 0);
 /*public*/ AppsLaunchFrame(AppsLaunchPane* containedPane, QString name,QWidget *parent = 0);
 static /*public*/ QWidget* buttonSpace();

signals:

public slots:
private:
 // GUI members
 /*private*/ QMenuBar* menuBar;
 static QWidget* _buttonSpace;// = NULL;
 static QString profileFilename;// = "";
 Logger* log;
 Action* prefsAction;

protected:
 /*protected*/ void createMenus(QMenuBar* menuBar, WindowInterface* wi, AppsLaunchPane* pane);
 /*protected*/ void fileMenu(QMenuBar* menuBar, WindowInterface* wi = NULL);
 /*protected*/ void setPrefsFrameHelp(JmriJFrame* f, QString l);
 /*protected*/ void editMenu(QMenuBar* menuBar, WindowInterface* wi);
 /*protected*/ void toolsMenu(QMenuBar* menuBar, WindowInterface* wi);
 /*protected*/ void operationsMenu(QMenuBar* menuBar, WindowInterface* wi);
 /*protected*/ void rosterMenu(QMenuBar* menuBar, WindowInterface* wi);
 /*protected*/ void panelMenu(QMenuBar* menuBar, WindowInterface* wi);
 /*protected*/ void systemsMenu(QMenuBar* menuBar, WindowInterface* wi);
 /*protected*/ void debugMenu(QMenuBar* menuBar, WindowInterface* wi, AppsLaunchPane* pane);
 /*protected*/ void scriptMenu(QMenuBar* menuBar, WindowInterface* wi);
 /*protected*/ void developmentMenu(QMenuBar* menuBar, WindowInterface* wi);
 /*protected*/ void helpMenu(QMenuBar* menuBar, WindowInterface* wi, AppsLaunchPane* containedPane);

};

#endif // APPSLAUNCHFRAME_H
