#ifndef LOGIXNG_INITIALIZATIONMANAGERTESTACTION_H
#define LOGIXNG_INITIALIZATIONMANAGERTESTACTION_H

#include <abstractaction.h>

class Logger;
class LogixNG_InitializationManagerTestAction : public AbstractAction
{
public:
    explicit LogixNG_InitializationManagerTestAction(QObject *parent = nullptr);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // LOGIXNG_INITIALIZATIONMANAGERTESTACTION_H
