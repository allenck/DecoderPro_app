#ifndef SPEEDPROFILEACTION_H
#define SPEEDPROFILEACTION_H

#include <QAction>

class WindowInterface;
class SpeedProfileAction : public QAction
{
 Q_OBJECT
public:
 //explicit SpeedProfileAction(QObject *parent = 0);
 /*public*/ SpeedProfileAction(QString s, WindowInterface* wi);
 /*public*/ SpeedProfileAction(QString s, QIcon i, WindowInterface* wi) ;
 /*public*/ SpeedProfileAction(QString s, QObject *parent) ;

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* = 0);
private:
 void common();

};

#endif // SPEEDPROFILEACTION_H
