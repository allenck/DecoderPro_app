#ifndef DCCSIGNALHEADTESTACTION_H
#define DCCSIGNALHEADTESTACTION_H
#include "abstractaction.h"

class Logger;
class DccSignalHeadTestAction : public AbstractAction
{
public:
 DccSignalHeadTestAction(QObject *parent);
public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // DCCSIGNALHEADTESTACTION_H
