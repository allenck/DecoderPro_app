#ifndef LOCONETSLOTTESTACTION_H
#define LOCONETSLOTTESTACTION_H
#include "abstractaction.h"

class Logger;
class LocoNetSlotTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LocoNetSlotTestAction(QObject* parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;
};

#endif // LOCONETSLOTTESTACTION_H
