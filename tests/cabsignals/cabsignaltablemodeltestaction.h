#ifndef CABSIGNALTABLEMODELTESTACTION_H
#define CABSIGNALTABLEMODELTESTACTION_H
#include "abstractaction.h"

class Logger;
class CabSignalTableModelTestAction : public AbstractAction
{
public:
 CabSignalTableModelTestAction(QObject* parent);

public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // CABSIGNALTABLEMODELTESTACTION_H
