#ifndef CONTROLPANELTESTACTION_H
#define CONTROLPANELTESTACTION_H
#include "abstractaction.h"

class Logger;
class ControlPanelTestAction : public AbstractAction
{
    Q_OBJECT
public:
    ControlPanelTestAction(QObject* parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;
};

#endif // CONTROLPANELTESTACTION_H
