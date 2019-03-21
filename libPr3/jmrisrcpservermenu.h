#ifndef JMRISRCPSERVERMENU_H
#define JMRISRCPSERVERMENU_H
#include <QMenu>

class JmriSRCPServerMenu : public QMenu
{
public:
 JmriSRCPServerMenu(QWidget* parent = nullptr);
 /*public*/ JmriSRCPServerMenu(QString name, QWidget *parent =nullptr);

private:
 void common();
};

#endif // JMRISRCPSERVERMENU_H
