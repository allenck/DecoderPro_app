#ifndef ACTIONSENSORSWINGTESTACTION_H
#define ACTIONSENSORSWINGTESTACTION_H

#include <abstractaction.h>

class ActionSensorSwingTestAction : public AbstractAction
{
    Q_OBJECT
public:
    explicit ActionSensorSwingTestAction(QObject *parent = nullptr);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // ACTIONSENSORSWINGTESTACTION_H
