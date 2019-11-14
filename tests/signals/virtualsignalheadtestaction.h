#ifndef VIRTUALSIGNALHEADTESTACTION_H
#define VIRTUALSIGNALHEADTESTACTION_H
#include "abstractaction.h"

class Logger;
class VirtualSignalHeadTestAction : public AbstractAction
{
 Q_OBJECT
public:
 VirtualSignalHeadTestAction(QObject* parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // VIRTUALSIGNALHEADTESTACTION_H
