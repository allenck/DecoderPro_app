#ifndef LNDEFERPROGRAMMERTESTACTION_H
#define LNDEFERPROGRAMMERTESTACTION_H
#include "abstractaction.h"

class Logger;
class LnDeferProgrammerTestAction : public AbstractAction
{
 Q_OBJECT
public:
 LnDeferProgrammerTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // LNDEFERPROGRAMMERTESTACTION_H
