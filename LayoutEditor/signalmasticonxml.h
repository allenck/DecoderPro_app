#ifndef SIGNALMASTICONXML_H
#define SIGNALMASTICONXML_H
#include "positionablelabelxml.h"
#include "liblayouteditor_global.h"

class SignalMastIcon;
class LIBLAYOUTEDITORSHARED_EXPORT SignalMastIconXml : public PositionableLabelXml
{
    Q_OBJECT
public:
    explicit SignalMastIconXml(QObject *parent = 0);
 ~SignalMastIconXml() {}
 SignalMastIconXml(const SignalMastIconXml&) : PositionableLabelXml() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    SignalMastIcon* getIcon();
signals:

public slots:
private:
    Logger* log;
    SignalMastIcon * l;
};
Q_DECLARE_METATYPE(SignalMastIconXml)
#endif // SIGNALMASTICONXML_H
