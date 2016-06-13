#ifndef ACTIVESYSTEMSMENU_H
#define ACTIVESYSTEMSMENU_H

#include <QMenu>
#include "appslib_global.h"

class QMenuBar;
class APPSLIBSHARED_EXPORT ActiveSystemsMenu : public QMenu
{
 Q_OBJECT
public:
 explicit ActiveSystemsMenu(QWidget *parent = 0);
 /*public*/ ActiveSystemsMenu(QString name, QWidget *parent);
 static /*public*/ void addItems(QMenuBar* m);
 static /*public*/ void addItems(QMenu* m);


signals:

public slots:
private:
 void common();
 static QMenu* getMenu(QString className);

};

#endif // ACTIVESYSTEMSMENU_H
