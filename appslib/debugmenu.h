#ifndef DEBUGMENU_H
#define DEBUGMENU_H

#include <QMenu>
#include "appslib_global.h"


class APPSLIBSHARED_EXPORT DebugMenu : public QMenu
{
 Q_OBJECT
public:
 //explicit DebugMenu(QWidget *parent = 0);
 /*public*/ DebugMenu(QString name, QWidget* panel);
 /*public*/ DebugMenu(QWidget* panel);

signals:

public slots:
private:
 void common(QWidget* panel);

};

#endif // DEBUGMENU_H
