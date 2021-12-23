#ifndef STARTUPPAUSEMODELXML_H
#define STARTUPPAUSEMODELXML_H
#include "abstractxmladapter.h"

class Logger;
class StartupPauseModelXml : public AbstractXmlAdapter
{
public:
 StartupPauseModelXml(QObject* parent = 0);
 ~StartupPauseModelXml() {}
 StartupPauseModelXml(const StartupPauseModelXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool loadDeferred() ;
 /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throw (JmriException)*/;
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("StartupPauseModelXml");

};
Q_DECLARE_METATYPE(StartupPauseModelXml)
#endif // STARTUPPAUSEMODELXML_H
