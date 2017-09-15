#ifndef REPORTERICONXML_H
#define REPORTERICONXML_H
#include "positionablelabelxml.h"

class ReporterIcon;
class ReporterIconXml : public PositionableLabelXml
{
    Q_OBJECT
public:
    explicit ReporterIconXml(QObject *parent = 0);
 ~ReporterIconXml() {}
 ReporterIconXml(const ReporterIconXml&) : PositionableLabelXml() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    ReporterIcon* getIcon();
signals:

public slots:
private:
 Logger* log;
 ReporterIcon* l;
};
Q_DECLARE_METATYPE(ReporterIconXml)
#endif // REPORTERICONXML_H
