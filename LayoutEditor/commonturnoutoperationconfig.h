#ifndef COMMONTURNOUTOPERATIONCONFIG_H
#define COMMONTURNOUTOPERATIONCONFIG_H
#include "turnoutoperationconfig.h"

class QSpinBox;
class CommonTurnoutOperation;
class CommonTurnoutOperationConfig : public TurnoutOperationConfig
{
    Q_OBJECT
public:
    explicit CommonTurnoutOperationConfig(TurnoutOperation* op, QWidget *parent = 0);
    /*public*/ void endConfigure();

signals:

public slots:
private:
    QSpinBox* intervalSpinner;   // actually a JSpinner
    QSpinBox* maxTriesSpinner;   // actually a JSpinner
    CommonTurnoutOperation* myOp;

};

#endif // COMMONTURNOUTOPERATIONCONFIG_H
