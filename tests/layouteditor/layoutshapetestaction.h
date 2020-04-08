#ifndef LAYOUTSHAPETESTACTION_H
#define LAYOUTSHAPETESTACTION_H
#include "abstractaction.h"

class Logger;
class LayoutShapeTestAction : public AbstractAction
{
 Q_OBJECT
public:
 LayoutShapeTestAction(QObject* parent);
 void actionPerformed();
private:
 static Logger* log;
};

#endif // LAYOUTSHAPETESTACTION_H
