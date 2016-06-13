#ifndef PR3CONNECTIONCONFIG_H
#define PR3CONNECTIONCONFIG_H

#include "../../abstractserialconnectionconfig.h"
#include "libPr3_global.h"

class PR3Adapter;
class LIBPR3SHARED_EXPORT Pr3ConnectionConfig : public AbstractSerialConnectionConfig
{
    Q_OBJECT

public:
    explicit Pr3ConnectionConfig(QObject *parent = 0);
    ~Pr3ConnectionConfig() {}
    Pr3ConnectionConfig(const Pr3ConnectionConfig&)
        : AbstractSerialConnectionConfig(){}
    /*public*/ Pr3ConnectionConfig(PR3Adapter* p, QObject *parent = 0);
    /*public*/ QString name();
    /*public*/ bool isOptList2Advanced();

signals:

public slots:
protected:
    /*protected*/ QStringList getPortFriendlyNames();
    /*protected*/ void setInstance();

};
Q_DECLARE_METATYPE(Pr3ConnectionConfig)
#endif // PR3CONNECTIONCONFIG_H
