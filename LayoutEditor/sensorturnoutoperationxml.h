#ifndef SENSORTURNOUTOPERATIONXML_H
#define SENSORTURNOUTOPERATIONXML_H
#include "commonturnoutoperationxml.h"

class TurnoutOperation;
class SensorTurnoutOperationXml : public CommonTurnoutOperationXml
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SensorTurnoutOperationXml(QObject *parent = 0);
    ~SensorTurnoutOperationXml() {}
    SensorTurnoutOperationXml(const SensorTurnoutOperationXml&) : CommonTurnoutOperationXml() {}
    /*public*/ TurnoutOperation* loadOne(QDomElement e);

signals:

public slots:
private:
    Logger* log;
};
Q_DECLARE_METATYPE(SensorTurnoutOperationXml)
#endif // SENSORTURNOUTOPERATIONXML_H
