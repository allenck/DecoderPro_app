#ifndef CONTROLLERFILTERFRAMETESTACTION_H
#define CONTROLLERFILTERFRAMETESTACTION_H
#include "abstractaction.h"

class Logger;
class ControllerFilterFrameTestAction : public AbstractAction
{
 Q_OBJECT
public:
 ControllerFilterFrameTestAction(QObject *parent);
public slots:

 void actionPerformed();
private:
 static Logger* log;
};

#endif // CONTROLLERFILTERFRAMETESTACTION_H
