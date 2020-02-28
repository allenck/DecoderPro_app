#ifndef DESTINATIONPOINTSTESTACTION_H
#define DESTINATIONPOINTSTESTACTION_H
#include "abstractaction.h"

class Logger;
class DestinationPointsTestAction : public AbstractAction
{
 Q_OBJECT
public:
 DestinationPointsTestAction(QObject *parent);
public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // DESTINATIONPOINTSTESTACTION_H
