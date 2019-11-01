#ifndef LNOPSMODEPROGRAMMERACTION_H
#define LNOPSMODEPROGRAMMERACTION_H
#include "abstractaction.h"

class Logger;
class LnOpsModeProgrammerTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LnOpsModeProgrammerTestAction(QObject *parent);

public slots:
    void actionPerformed();
private:
    static Logger* log;

};

#endif // LNOPSMODEPROGRAMMERACTION_H
