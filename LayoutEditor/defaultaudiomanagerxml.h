#ifndef DEFAULTAUDIOMANAGERXML_H
#define DEFAULTAUDIOMANAGERXML_H
#include "abstractaudiomanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT DefaultAudioManagerXml : public AbstractAudioManagerConfigXML
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit DefaultAudioManagerXml(QObject *parent = 0);
 ~DefaultAudioManagerXml() {}
 DefaultAudioManagerXml(const DefaultAudioManagerXml&) : AbstractAudioManagerConfigXML() {}
 /*public*/ void setStoreElementClass(QDomElement audio);
 /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException);

signals:

public slots:
private:
 Logger* log;
};

Q_DECLARE_METATYPE(DefaultAudioManagerXml)
#endif // DEFAULTAUDIOMANAGERXML_H
