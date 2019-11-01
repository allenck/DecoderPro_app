#ifndef LNPOWERMANAGERTESTACTION_H
#define LNPOWERMANAGERTESTACTION_H
#include "abstractaction.h"

class Logger;
class LnPowerManagerTestAction : public AbstractAction
{
    Q_OBJECT
public:
    LnPowerManagerTestAction(QObject* parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;

};

#endif // LNPOWERMANAGERTESTACTION_H
