#ifndef INDICATORTRACKICONXML_H
#define INDICATORTRACKICONXML_H
#include "positionablelabelxml.h"
#include "namedbeanhandle.h"

class IndicatorTrackIcon;
class IndicatorTrackIconXml : public PositionableLabelXml
{
    Q_OBJECT
public:
    explicit IndicatorTrackIconXml(QObject *parent = 0);
    /*public*/ QDomElement store(QObject* o) ;
    template <class T>
    QDomElement storeNamedBean(QString elemName, NamedBeanHandle<T>* nb);
    /*public*/ bool load(QDomElement element) throw (Exception) ;
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    IndicatorTrackIcon* getIcon();
signals:

public slots:
private:
    Logger* log;
    IndicatorTrackIcon* l;
};

#endif // INDICATORTRACKICONXML_H
