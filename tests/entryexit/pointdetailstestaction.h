#ifndef POINTDETAILSTESTACTION_H
#define POINTDETAILSTESTACTION_H

#include "abstractaction.h"

class Logger;
class PointDetailsTestAction : public AbstractAction
{
 Q_OBJECT
public:
 PointDetailsTestAction(QObject* parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // POINTDETAILSTESTACTION_H
