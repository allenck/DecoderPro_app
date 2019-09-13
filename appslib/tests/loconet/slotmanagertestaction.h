#ifndef SLOTMANAGERTESTACTION_H
#define SLOTMANAGERTESTACTION_H
#include "abstractaction.h"

class SlotManagerTestAction : public AbstractAction
{
    Q_OBJECT
public:
    SlotManagerTestAction(QObject* parent);
public slots:
    void actionPerformed();
};

#endif // SLOTMANAGERTESTACTION_H
