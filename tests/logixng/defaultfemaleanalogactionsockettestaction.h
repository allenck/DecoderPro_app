#ifndef DEFAULTFEMALEANALOGACTIONSOCKETTESTACTION_H
#define DEFAULTFEMALEANALOGACTIONSOCKETTESTACTION_H

#include <abstractaction.h>

class Logger;
class DefaultFemaleAnalogActionSocketTestAction : public AbstractAction
{
    Q_OBJECT
public:
    explicit DefaultFemaleAnalogActionSocketTestAction(QObject *parent = nullptr);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // DEFAULTFEMALEANALOGACTIONSOCKETTESTACTION_H
