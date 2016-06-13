#ifndef ANALOGCLOCKACTION_H
#define ANALOGCLOCKACTION_H

#include <QAction>
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT AnalogClockAction : public QAction
{
 Q_OBJECT
public:
 explicit AnalogClockAction(QObject *parent = 0);
 /*public*/ AnalogClockAction(QString s, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 void common();
};

#endif // ANALOGCLOCKACTION_H
