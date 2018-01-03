#ifndef LCDCLOCKACTION_H
#define LCDCLOCKACTION_H

#include "abstractaction.h"
#include "appslib_global.h"


class APPSLIBSHARED_EXPORT LcdClockAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit LcdClockAction(QObject *parent = 0);
 /*public*/ LcdClockAction(QString s, QObject *parent);
 ~LcdClockAction() {}
 LcdClockAction(const LcdClockAction&) : AbstractAction() {}
signals:
public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
 void common();

};
Q_DECLARE_METATYPE(LcdClockAction)
#endif // LCDCLOCKACTION_H
