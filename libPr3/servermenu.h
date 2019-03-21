#ifndef SERVERMENU_H
#define SERVERMENU_H
#include <QMenu>

class ServerMenu : public QMenu
{
public:
 ServerMenu(QWidget *parent=nullptr);
 /*public*/ ServerMenu(QString name, QWidget *parent);
};

#endif // SERVERMENU_H
