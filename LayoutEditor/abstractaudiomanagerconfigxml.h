#ifndef ABSTRACTAUDIOMANAGERCONFIGXML_H
#define ABSTRACTAUDIOMANAGERCONFIGXML_H
#include "abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT AbstractAudioManagerConfigXML : public AbstractNamedBeanManagerConfigXML
{
 Q_OBJECT
public:
 explicit AbstractAudioManagerConfigXML(QObject *parent = 0);
 /*public*/ QDomElement store(QObject* o) override;
 virtual /*abstract*/ /*public*/ void setStoreElementClass(QDomElement audio);
 /*public*/ void load(QDomElement element, QObject* o)  throw (Exception);
 /*abstract*/ /*public*/ bool load(QDomElement audio) throw (Exception) override;
 /*public*/ void loadAudio(QDomElement audio);
 /*public*/ int loadOrder()const override;

signals:

public slots:
private:
 Logger* log;
};

#endif // ABSTRACTAUDIOMANAGERCONFIGXML_H
