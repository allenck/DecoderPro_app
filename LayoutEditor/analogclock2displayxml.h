#ifndef ANALOGCLOCK2DISPLAYXML_H
#define ANALOGCLOCK2DISPLAYXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT AnalogClock2DisplayXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    explicit AnalogClock2DisplayXml(QObject *parent = 0);
    ~AnalogClock2DisplayXml();
 AnalogClock2DisplayXml(const AnalogClock2DisplayXml&) : AbstractXmlAdapter() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:
private:
 Logger* log;
};

#endif // ANALOGCLOCK2DISPLAYXML_H
