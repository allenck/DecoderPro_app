#ifndef JMRICLIENTMENU_H
#define JMRICLIENTMENU_H
#include <QMenu>

class JMRIClientSystemConnectionMemo;
class JMRIClientMenu : public QMenu
{
public:
 /*public*/ JMRIClientMenu(QString name, JMRIClientSystemConnectionMemo* memo, QWidget *parent = nullptr);
 /*public*/ JMRIClientMenu(JMRIClientSystemConnectionMemo* memo, QWidget *parent = nullptr);


private:
 void common(JMRIClientSystemConnectionMemo* memo);

};

#endif // JMRICLIENTMENU_H
