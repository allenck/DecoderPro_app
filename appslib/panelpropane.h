#ifndef PANELPROPANE_H
#define PANELPROPANE_H
#include "appslaunchpane.h"
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT PanelProPane : public AppsLaunchPane
{
 Q_OBJECT
public:
 explicit PanelProPane(QWidget *parent = 0);

signals:

public slots:
 void On_quit();
protected:
 /*protected*/ QString windowHelpID();
 /*protected*/ QString logo();
 /*protected*/ QString line1();
 /*protected*/ QString line2();
 /*protected*/ QWidget* statusPanel();

};

#endif // PANELPROPANE_H
