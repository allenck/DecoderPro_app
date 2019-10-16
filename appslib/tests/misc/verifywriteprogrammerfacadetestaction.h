#ifndef VERIFYWRITEPROGRAMMERFACADETESTACTION_H
#define VERIFYWRITEPROGRAMMERFACADETESTACTION_H
#include "abstractaction.h"

class Logger;
class VerifyWriteProgrammerFacadeTestAction : public AbstractAction
{
public:
 VerifyWriteProgrammerFacadeTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;

};

#endif // VERIFYWRITEPROGRAMMERFACADETESTACTION_H
