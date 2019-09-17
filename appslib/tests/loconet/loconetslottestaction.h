#ifndef LOCONETSLOTTESTACTION_H
#define LOCONETSLOTTESTACTION_H
#include "abstractaction.h"

class LocoNetSlotTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LocoNetSlotTestAction(QObject* parent);
public slots:
    void actionPerformed();
};

#endif // LOCONETSLOTTESTACTION_H
