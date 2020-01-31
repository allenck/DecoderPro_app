#ifndef CONSISTTOOLFRAMETESTACTION_H
#define CONSISTTOOLFRAMETESTACTION_H
#include "abstractaction.h"

class Logger;
class ConsistToolFrameTestAction : public AbstractAction
{
 Q_OBJECT
public:
 ConsistToolFrameTestAction(QObject* parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // CONSISTTOOLFRAMETESTACTION_H
