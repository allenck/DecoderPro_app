#ifndef SIMPLECLOCKACTION_H
#define SIMPLECLOCKACTION_H

#include <QAction>
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT SimpleClockAction : public QAction
{
 Q_OBJECT
public:
 //explicit SimpleClockAction(QObject *parent = 0);
 /*public*/ SimpleClockAction(QString s,QObject *parent);
 /*public*/ SimpleClockAction(QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 void common();
};

#endif // SIMPLECLOCKACTION_H
