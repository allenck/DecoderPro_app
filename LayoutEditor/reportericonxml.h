#ifndef REPORTERICONXML_H
#define REPORTERICONXML_H
#include "positionablelabelxml.h"

class ReporterIcon;
class ReporterIconXml : public PositionableLabelXml
{
    Q_OBJECT
public:
    explicit ReporterIconXml(QObject *parent = 0);
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

#endif // REPORTERICONXML_H
