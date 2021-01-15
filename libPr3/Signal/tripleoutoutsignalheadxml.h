#ifndef TRIPLEOUTOUTSIGNALHEADXML_H
#define TRIPLEOUTOUTSIGNALHEADXML_H
#include "doubleturnoutsignalheadxml.h"

class TripleOutputSignalHeadXml : public DoubleTurnoutSignalHeadXml
{
public:
 Q_INVOKABLE TripleOutputSignalHeadXml(QObject* parent = nullptr);
 ~TripleOutputSignalHeadXml() {}
 TripleOutputSignalHeadXml(const TripleOutputSignalHeadXml&) : DoubleTurnoutSignalHeadXml() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement shared, QDomElement /*perNode*/) throw (JmriConfigureXmlException);
 /*public*/ void load(QDomElement /*element*/, QObject* /*o*/) throw (Exception);

private:
 static Logger* log;
};
Q_DECLARE_METATYPE(TripleOutputSignalHeadXml)
#endif // TRIPLEOUTOUTSIGNALHEADXML_H
