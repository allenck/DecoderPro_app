#ifndef LOCONETCONSISTTESTACTION_H
#define LOCONETCONSISTTESTACTION_H
#include "abstractaction.h"
class LocoNetConsistTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LocoNetConsistTestAction(QObject* parent);
public slots:
    void actionPerformed();
};

#endif // LOCONETCONSISTTESTACTION_H
