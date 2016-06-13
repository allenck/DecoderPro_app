#ifndef NOFEEDBACKTURNOUTOPERATIONXML_H
#define NOFEEDBACKTURNOUTOPERATIONXML_H

#include <QObject>
#include <QDomElement>
#include "commonturnoutoperationxml.h"

class NoFeedbackTurnoutOperationXml : public CommonTurnoutOperationXml
{
    Q_OBJECT
public:
    explicit NoFeedbackTurnoutOperationXml(QObject *parent = 0);
    /*public*/ TurnoutOperation* loadOne(QDomElement e);

signals:
    
public slots:
    
};

#endif // NOFEEDBACKTURNOUTOPERATIONXML_H
