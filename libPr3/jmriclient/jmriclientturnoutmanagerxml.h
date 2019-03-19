#ifndef JMRICLIENTTURNOUTMANAGERXML_H
#define JMRICLIENTTURNOUTMANAGERML_H
#include "abstractturnoutmanagerconfigxml.h"

class JMRIClientTurnoutManagerXml : public AbstractTurnoutManagerConfigXML
{
public:
 Q_INVOKABLE JMRIClientTurnoutManagerXml(QObject* parent = nullptr);
 ~JMRIClientTurnoutManagerXml() {}
 JMRIClientTurnoutManagerXml(const JMRIClientTurnoutManagerXml&) : AbstractTurnoutManagerConfigXML() {}
 /*public*/ void setStoreElementClass(QDomElement turnouts);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
 /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (Exception);

private:
 static Logger* log;
};
Q_DECLARE_METATYPE(JMRIClientTurnoutManagerXml)
#endif // JMRICLIENTTURNOUTMANAGERXML_H
