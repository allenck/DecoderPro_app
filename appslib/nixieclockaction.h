#ifndef NIXIECLOCKACTION_H
#define NIXIECLOCKACTION_H

#include "abstractaction.h"
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT NixieClockAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit NixieClockAction(QObject *parent = 0);
 /*public*/ NixieClockAction(QString s, QObject *parent);
 ~NixieClockAction() {}
 NixieClockAction(const NixieClockAction&) : AbstractAction() {}
signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
 void common();

};
Q_DECLARE_METATYPE(NixieClockAction)
#endif // NIXIECLOCKACTION_H
