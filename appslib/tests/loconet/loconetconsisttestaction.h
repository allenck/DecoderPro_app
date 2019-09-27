#ifndef LOCONETCONSISTTESTACTION_H
#define LOCONETCONSISTTESTACTION_H
#include "abstractaction.h"

class Logger;
class LocoNetConsistTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LocoNetConsistTestAction(QObject* parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;
};

#endif // LOCONETCONSISTTESTACTION_H
