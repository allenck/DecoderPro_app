#ifndef SENSORTURNOUTOPERATIONCONFIG_H
#define SENSORTURNOUTOPERATIONCONFIG_H
#include "commonturnoutoperationconfig.h"

class TurnoutOperation;
class SensorTurnoutOperationConfig : public CommonTurnoutOperationConfig
{
    Q_OBJECT
public:
    explicit SensorTurnoutOperationConfig(TurnoutOperation* op, QWidget *parent = 0);

signals:

public slots:

};

#endif // SENSORTURNOUTOPERATIONCONFIG_H
