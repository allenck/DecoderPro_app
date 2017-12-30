#ifndef TOOLSMENU_H
#define TOOLSMENU_H

#include <QMenu>
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT ToolsMenu : public QMenu
{
 Q_OBJECT
public:
 explicit ToolsMenu(QWidget *parent = 0);
 /*public*/ ToolsMenu(QString name, QWidget *parent =0) ;

signals:

public slots:

private:
 QAction* prefsAction;
 /*protected*/ void doPreferences();
 void common();

};

#endif // TOOLSMENU_H
