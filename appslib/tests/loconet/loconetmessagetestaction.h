#ifndef LOCONETMESSAGETESTACTION_H
#define LOCONETMESSAGETESTACTION_H
#include "abstractaction.h"

class LocoNetMessageTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LocoNetMessageTestAction(QObject *parent);

public slots:
    void actionPerformed();
};

#endif // LOCONETMESSAGETESTACTION_H
