#ifndef RAWTURNOUTOPERATIONCONFIG_H
#define RAWTURNOUTOPERATIONCONFIG_H
#include "commonturnoutoperationconfig.h"
#include "liblayouteditor_global.h"

class TurnoutOperation;
class LIBLAYOUTEDITORSHARED_EXPORT RawTurnoutOperationConfig : public CommonTurnoutOperationConfig
{
    Q_OBJECT
public:
    explicit RawTurnoutOperationConfig(TurnoutOperation* op, QWidget *parent = 0);

signals:

public slots:

};

#endif // RAWTURNOUTOPERATIONCONFIG_H
