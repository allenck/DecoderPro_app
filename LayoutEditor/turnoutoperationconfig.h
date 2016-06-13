#ifndef TURNOUTOPERATIONCONFIG_H
#define TURNOUTOPERATIONCONFIG_H

#include <QWidget>
#include "logger.h"
#include "liblayouteditor_global.h"

class TurnoutOperation;
class LIBLAYOUTEDITORSHARED_EXPORT TurnoutOperationConfig : public QWidget
{
    Q_OBJECT
public:
    explicit TurnoutOperationConfig(TurnoutOperation* op, QWidget *parent = 0);
    TurnoutOperation* getOperation();
    /*public*/ void endConfigure();
    static /*public*/ TurnoutOperationConfig* getConfigPanel(TurnoutOperation* op);

signals:

public slots:
 private:
  Logger* log;
  TurnoutOperation* myOperation;
  //boolean valid = true;

};

#endif // TURNOUTOPERATIONCONFIG_H
