#ifndef MULTIINDEXPROGRAMMERFACADETESTACTION_H
#define MULTIINDEXPROGRAMMERFACADETESTACTION_H
#include "abstractaction.h"

class Logger;
class MultiIndexProgrammerFacadeTestAction : public AbstractAction
{
 Q_OBJECT
public:
 MultiIndexProgrammerFacadeTestAction(QObject *parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // MULTIINDEXPROGRAMMERFACADETESTACTION_H
