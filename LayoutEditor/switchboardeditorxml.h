#ifndef SWITCHBOARDEDITORXML_H
#define SWITCHBOARDEDITORXML_H
#include "abstractxmladapter.h"

class Logger;
class SwitchboardEditorXml : public AbstractXmlAdapter
{
public:
 SwitchboardEditorXml(QObject *parent = nullptr);
 ~SwitchboardEditorXml() {}
 SwitchboardEditorXml(const SwitchboardEditorXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
 /*public*/ bool load(QDomElement shared, QDomElement perNode);


private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(SwitchboardEditorXml.class);

};
Q_DECLARE_METATYPE(SwitchboardEditorXml)
#endif // SWITCHBOARDEDITORXML_H
