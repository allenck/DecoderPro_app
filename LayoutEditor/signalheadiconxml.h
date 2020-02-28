#ifndef SIGNALHEADICONXML_H
#define SIGNALHEADICONXML_H
#include "../LayoutEditor/positionablelabelxml.h"
#include "liblayouteditor_global.h"

class SignalHeadIcon;
class LIBLAYOUTEDITORSHARED_EXPORT SignalHeadIconXml : public PositionableLabelXml
{
    Q_OBJECT
public:
    //explicit SignalHeadIconXml(QObject *parent = 0);
    static /*final*/ QMap<QString,QString> _nameMap;// = new QMap<QString,QString>();
    Q_INVOKABLE /*public*/ SignalHeadIconXml(QObject *parent = 0);
    ~SignalHeadIconXml() override{}
    SignalHeadIconXml(const SignalHeadIconXml&) : PositionableLabelXml() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement element) throw (Exception) override;
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;
    SignalHeadIcon* getIcon();
signals:

public slots:
private:
    /*private*/ NamedIcon* loadSignalIcon(QString aspect, int rotation, SignalHeadIcon* l, QDomElement element, QString name, Editor* ed);
    Logger* log;
 SignalHeadIcon* l;
};
Q_DECLARE_METATYPE(SignalHeadIconXml)
#endif // SIGNALHEADICONXML_H
