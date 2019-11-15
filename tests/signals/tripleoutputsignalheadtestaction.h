#ifndef TRIPLEOUTPUTSIGNALHEADTESTACTION_H
#define TRIPLEOUTPUTSIGNALHEADTESTACTION_H
#include "abstractaction.h"

class Logger;
class TripleOutputSignalHeadTestAction : public AbstractAction
{
 Q_OBJECT
public:
 TripleOutputSignalHeadTestAction(QObject* parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // TRIPLEOUTPUTSIGNALHEADTESTACTION_H
