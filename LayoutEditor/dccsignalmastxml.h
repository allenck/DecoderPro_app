#ifndef DCCSIGNALMASTXML_H
#define DCCSIGNALMASTXML_H
#include "abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class DccSignalMast;
class LIBLAYOUTEDITORSHARED_EXPORT DccSignalMastXml : public AbstractNamedBeanManagerConfigXML
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit DccSignalMastXml(QObject *parent = 0);
 ~DccSignalMastXml() {}
 DccSignalMastXml(const DccSignalMastXml&) : AbstractNamedBeanManagerConfigXML() {}
 /*public*/  QDomElement store(QObject* o);
 /*public*/  bool load(QDomElement shared, QDomElement perNode)throw (JmriConfigureXmlException);
 /*public*/  void load(QDomElement element, QObject* o) throw (Exception);
signals:

public slots:
protected:
 /*protected*/ bool loadCommonDCCMast(DccSignalMast* m, QDomElement element);

};
Q_DECLARE_METATYPE(DccSignalMastXml)
#endif // DCCSIGNALMASTXML_H
