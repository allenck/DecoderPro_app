#ifndef PRAGOTRONCLOCKACTION_H
#define PRAGOTRONCLOCKACTION_H
#include "abstractaction.h"

class PragotronClockAction : public AbstractAction
{
 Q_OBJECT
public:
 PragotronClockAction(QObject *parent);
 /*public*/ PragotronClockAction(QString s, QObject* parent);
public slots:
 void actionPerformed();
};

#endif // PRAGOTRONCLOCKACTION_H
