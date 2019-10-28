#ifndef DEFAULTMEMORYMANAGERTESTACTION_H
#define DEFAULTMEMORYMANAGERTESTACTION_H
#include "abstractaction.h"

class Logger;
class DefaultMemoryManagerTestAction : public AbstractAction
{
 Q_OBJECT
public:
 DefaultMemoryManagerTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // DEFAULTMEMORYMANAGERTESTACTION_H
