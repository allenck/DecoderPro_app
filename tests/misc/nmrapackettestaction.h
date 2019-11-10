#ifndef NMRAPACKETTESTACTION_H
#define NMRAPACKETTESTACTION_H
#include "abstractaction.h"

class Logger;
class NmraPacketTestAction : public AbstractAction
{
 Q_OBJECT
public:
 NmraPacketTestAction(QObject *parent);

public slots:
 void actionPerformed();
private:
 static Logger * log;
};

#endif // NMRAPACKETTESTACTION_H
