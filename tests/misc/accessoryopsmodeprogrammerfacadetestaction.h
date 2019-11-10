#ifndef ACCESSORYOPSMODEPROGRAMMERFACADETESTACTION_H
#define ACCESSORYOPSMODEPROGRAMMERFACADETESTACTION_H
#include "abstractaction.h"

class Logger;
class AccessoryOpsModeProgrammerFacadeTestAction : public AbstractAction
{
 Q_OBJECT
public:
 AccessoryOpsModeProgrammerFacadeTestAction(QObject* parent);
public slots:
 void actionPerformed();
};

#endif // ACCESSORYOPSMODEPROGRAMMERFACADETESTACTION_H
