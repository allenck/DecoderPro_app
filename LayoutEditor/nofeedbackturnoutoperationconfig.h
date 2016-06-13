#ifndef NOFEEDBACKTURNOUTOPERATIONCONFIG_H
#define NOFEEDBACKTURNOUTOPERATIONCONFIG_H
#include "commonturnoutoperationconfig.h"

class TurnoutOperation;
class NoFeedbackTurnoutOperationConfig : public CommonTurnoutOperationConfig
{
    Q_OBJECT
public:
    explicit NoFeedbackTurnoutOperationConfig(TurnoutOperation* op, QWidget *parent = 0);

signals:

public slots:

};

#endif // NOFEEDBACKTURNOUTOPERATIONCONFIG_H
