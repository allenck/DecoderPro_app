#ifndef SENSORTURNOUTOPERATIONXML_H
#define SENSORTURNOUTOPERATIONXML_H
#include "commonturnoutoperationxml.h"

class TurnoutOperation;
class SensorTurnoutOperationXml : public CommonTurnoutOperationXml
{
    Q_OBJECT
public:
    explicit SensorTurnoutOperationXml(QObject *parent = 0);
    /*public*/ TurnoutOperation* loadOne(QDomElement e);

signals:

public slots:
private:
    Logger* log;
};

#endif // SENSORTURNOUTOPERATIONXML_H
