#ifndef OPSMODEDELAYEDPROGRAMMERFACADETESTACTION_H
#define OPSMODEDELAYEDPROGRAMMERFACADETESTACTION_H
#include "abstractaction.h"

class Logger;
class OpsModeDelayedProgrammerFacadeTestAction : public AbstractAction
{
 Q_OBJECT
public:
 OpsModeDelayedProgrammerFacadeTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger * log;
};

#endif // OPSMODEDELAYEDPROGRAMMERFACADETESTACTION_H
