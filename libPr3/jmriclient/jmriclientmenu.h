#ifndef JMRICLIENTMENU_H
#define JMRICLIENTMENU_H
#include <QMenu>

class JMRIClientSystemConnectionMemo;
class JMRIClientMenu : public QMenu
{
public:
 /*public*/ JMRIClientMenu(QString name, JMRIClientSystemConnectionMemo* memo);
 /*public*/ JMRIClientMenu(JMRIClientSystemConnectionMemo* memo, QObject *parent);


private:
 void common(JMRIClientSystemConnectionMemo* memo);

};

#endif // JMRICLIENTMENU_H
