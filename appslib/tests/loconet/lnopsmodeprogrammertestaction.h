#ifndef LNOPSMODEPROGRAMMERACTION_H
#define LNOPSMODEPROGRAMMERACTION_H
#include "abstractaction.h"

class LnOpsModeProgrammerTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LnOpsModeProgrammerTestAction(QObject *parent);

public slots:
    void actionPerformed();
};

#endif // LNOPSMODEPROGRAMMERACTION_H
