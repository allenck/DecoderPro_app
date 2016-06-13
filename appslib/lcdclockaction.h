#ifndef LCDCLOCKACTION_H
#define LCDCLOCKACTION_H

#include <QAction>
#include "appslib_global.h"


class APPSLIBSHARED_EXPORT LcdClockAction : public QAction
{
 Q_OBJECT
public:
 explicit LcdClockAction(QObject *parent = 0);
 /*public*/ LcdClockAction(QString s, QObject *parent);

signals:
public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
 void common();

};

#endif // LCDCLOCKACTION_H
