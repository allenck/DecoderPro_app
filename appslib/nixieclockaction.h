#ifndef NIXIECLOCKACTION_H
#define NIXIECLOCKACTION_H

#include <QAction>
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT NixieClockAction : public QAction
{
 Q_OBJECT
public:
 explicit NixieClockAction(QObject *parent = 0);
 /*public*/ NixieClockAction(QString s, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
 void common();

};

#endif // NIXIECLOCKACTION_H
