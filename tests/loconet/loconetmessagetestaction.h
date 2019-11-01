#ifndef LOCONETMESSAGETESTACTION_H
#define LOCONETMESSAGETESTACTION_H
#include "abstractaction.h"

class Logger;
class LocoNetMessageTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LocoNetMessageTestAction(QObject *parent);

public slots:
    void actionPerformed();
private:
    static Logger* log;
};

#endif // LOCONETMESSAGETESTACTION_H
