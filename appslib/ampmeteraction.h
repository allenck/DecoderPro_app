#ifndef AMPMETERACTION_H
#define AMPMETERACTION_H
#include "abstractaction.h"

class AmpMeterAction : public AbstractAction
{
 Q_OBJECT
public:
 AmpMeterAction(QObject* parent);
 /*public*/ AmpMeterAction(QString s, QObject* parent);
public slots:
 void actionPerformed();
};

#endif // AMPMETERACTION_H
