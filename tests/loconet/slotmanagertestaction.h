#ifndef SLOTMANAGERTESTACTION_H
#define SLOTMANAGERTESTACTION_H
#include "abstractaction.h"

class Logger;
class SlotManagerTestAction : public AbstractAction
{
    Q_OBJECT
public:
    SlotManagerTestAction(QObject* parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;
};

#endif // SLOTMANAGERTESTACTION_H
