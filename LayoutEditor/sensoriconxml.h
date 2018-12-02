#ifndef SENSORICONXML_H
#define SENSORICONXML_H
#include "positionablelabelxml.h"
#include "liblayouteditor_global.h"

class SensorIcon;
class LIBLAYOUTEDITORSHARED_EXPORT SensorIconXml : public PositionableLabelXml
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SensorIconXml(QObject *parent = 0);
 ~SensorIconXml() {}
 SensorIconXml(const SensorIconXml&) : PositionableLabelXml() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    SensorIcon* getIcon();
signals:

public slots:
private:
    static /*final*/ QHash<QString,QString>* _nameMap;// = new QHash<QString,QString>();
    bool _icon;
    /*private*/ NamedIcon* loadSensorIcon(QString state, int rotation, SensorIcon* l, QDomElement element, QString name, Editor* ed);
    void loadTextInfo(SensorIcon* l, QDomElement element);
    /*private*/ void loadSensorTextState(QString state, SensorIcon* l, QDomElement element);
Logger* log;
protected:
    /*protected*/ void storeIconInfo(SensorIcon* p, QDomElement element);
    /*protected*/ void storeTextInfo(SensorIcon* p, QDomElement element);
 SensorIcon* l;
};
Q_DECLARE_METATYPE(SensorIconXml)
#endif // SENSORICONXML_H
