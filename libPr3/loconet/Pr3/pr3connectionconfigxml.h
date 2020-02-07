#ifndef PR3CONNECTIONCONFIGXML_H
#define PR3CONNECTIONCONFIGXML_H
#include "../../../LayoutEditor/abstractserialconnectionconfigxml.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT  Pr3ConnectionConfigXml : public AbstractSerialConnectionConfigXml
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit Pr3ConnectionConfigXml(QObject *parent = 0);
    ~Pr3ConnectionConfigXml() {}
    Pr3ConnectionConfigXml(const Pr3ConnectionConfigXml&) : AbstractSerialConnectionConfigXml() {}
signals:

public slots:
protected:
    /*protected*/ void getInstance();
    /*protected*/ void getInstance(QObject* object);
    /*protected*/ void _register();

};
Q_DECLARE_METATYPE(Pr3ConnectionConfigXml)
#endif // PR3CONNECTIONCONFIGXML_H
