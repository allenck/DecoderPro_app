#ifndef RAWTURNOUTOPERATIONXML_H
#define RAWTURNOUTOPERATIONXML_H
#include "commonturnoutoperationxml.h"

class RawTurnoutOperationXml : public CommonTurnoutOperationXml
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit RawTurnoutOperationXml(QObject *parent = 0);
    ~RawTurnoutOperationXml() {}
    RawTurnoutOperationXml(const RawTurnoutOperationXml&) : CommonTurnoutOperationXml() {}
    /*public*/ TurnoutOperation* loadOne(QDomElement e);

signals:

public slots:

 private:
    static Logger* log;

};
Q_DECLARE_METATYPE(RawTurnoutOperationXml)
#endif // RAWTURNOUTOPERATIONXML_H
