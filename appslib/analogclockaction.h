#ifndef ANALOGCLOCKACTION_H
#define ANALOGCLOCKACTION_H

#include "abstractaction.h"
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT AnalogClockAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit AnalogClockAction(QObject *parent = 0);
 /*public*/ AnalogClockAction(QString s, QObject *parent);
 ~AnalogClockAction() {}
 AnalogClockAction(const AnalogClockAction&) : AbstractAction() {}
signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 void common();
};
Q_DECLARE_METATYPE(AnalogClockAction)
#endif // ANALOGCLOCKACTION_H
