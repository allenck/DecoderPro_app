#ifndef ACTIVESYSTEMSMENU_H
#define ACTIVESYSTEMSMENU_H

#include <QMenu>
#include "appslib_global.h"

class Logger;
class QMenuBar;
class APPSLIBSHARED_EXPORT ActiveSystemsMenu : public QMenu
{
 Q_OBJECT
public:
 explicit ActiveSystemsMenu(QWidget *parent = 0);
 /*public*/ ActiveSystemsMenu(QString name, QWidget *parent);
 static /*public*/ void addItems(QMenuBar* m, QWidget* frame);
 static /*public*/ void addItems(QMenu* m, QWidget* frame);


signals:

public slots:
private:
 void common();
 static QMenu* getMenu(QString className);
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ActiveSystemsMenu");

};

#endif // ACTIVESYSTEMSMENU_H
