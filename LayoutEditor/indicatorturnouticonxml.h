#ifndef INDICATORTURNOUTICONXML_H
#define INDICATORTURNOUTICONXML_H
#include "positionablelabelxml.h"
#include "namedbeanhandle.h"

class IndicatorTurnoutIcon;
class Turnout;
class OBlock;
class Sensor;
class IndicatorTurnoutIconXml : public PositionableLabelXml
{
    Q_OBJECT
public:
    explicit IndicatorTurnoutIconXml(QObject *parent = 0);
 ~IndicatorTurnoutIconXml() {}
 IndicatorTurnoutIconXml(const IndicatorTurnoutIconXml&) : PositionableLabelXml() {}
    /*public*/ QDomElement store(QObject* o);
    template< class T>
    QDomElement storeNamedBean(QString elemName, NamedBeanHandle<T>* nb);

    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    IndicatorTurnoutIcon* getIcon();
signals:

public slots:
private:
    Logger* log;
    IndicatorTurnoutIcon* l;
};
Q_DECLARE_METATYPE(IndicatorTurnoutIconXml)
#endif // INDICATORTURNOUTICONXML_H
