#ifndef DEFAULTSIGNALGROUPMANAGERXML_H
#define DEFAULTSIGNALGROUPMANAGERXML_H

#include "abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class SignalGroup;
class LIBLAYOUTEDITORSHARED_EXPORT DefaultSignalGroupManagerXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DefaultSignalGroupManagerXml(QObject *parent = 0);
 ~DefaultSignalGroupManagerXml() {}
 DefaultSignalGroupManagerXml(const DefaultSignalGroupManagerXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ void setStoreElementClass(QDomElement signalGroup);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    /*public*/ int loadOrder();

signals:

public slots:
private:
    /*private*/ void storeSignalHead(QDomElement element, SignalGroup* _group, int x);
    /*private*/ void storeTurnout(QDomElement element, SignalGroup* _group, int x, int turn);
    /*private*/ void storeSensor(QDomElement element, SignalGroup* _group, int x, int sensor);
    /*private*/ QString getSignalColour(int mAppearance);
    Logger* log;
    /*private*/ int getIntFromColour(QString colour);
};
Q_DECLARE_METATYPE(DefaultSignalGroupManagerXml)
#endif // DEFAULTSIGNALGROUPMANAGERXML_H
