#ifndef RAWTURNOUTOPERATIONXML_H
#define RAWTURNOUTOPERATIONXML_H
#include "commonturnoutoperationxml.h"

class RawTurnoutOperationXml : public CommonTurnoutOperationXml
{
    Q_OBJECT
public:
    explicit RawTurnoutOperationXml(QObject *parent = 0);
    /*public*/ TurnoutOperation* loadOne(QDomElement e);

signals:

public slots:

};

#endif // RAWTURNOUTOPERATIONXML_H
