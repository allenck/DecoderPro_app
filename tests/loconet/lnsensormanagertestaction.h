#ifndef LNSENSORMANAGERTESTACTION_H
#define LNSENSORMANAGERTESTACTION_H
#include "abstractaction.h"

class Logger;
class LnSensorManagerTestAction : public AbstractAction
{
 Q_OBJECT
public:
 LnSensorManagerTestAction(QObject* parent);
public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // LNSENSORMANAGERTESTACTION_H
