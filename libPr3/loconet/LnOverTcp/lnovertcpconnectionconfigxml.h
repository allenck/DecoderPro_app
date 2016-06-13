#ifndef LNOVERTCPCONNECTIONCONFIGXML_H
#define LNOVERTCPCONNECTIONCONFIGXML_H
#include "abstractnetworkconnectionconfigxml.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT LnOverTcpConnectionConfigXml : public AbstractNetworkConnectionConfigXml
{
 Q_OBJECT
public:
 explicit LnOverTcpConnectionConfigXml(QObject *parent = 0);
 ~LnOverTcpConnectionConfigXml() {}
 LnOverTcpConnectionConfigXml(const LnOverTcpConnectionConfigXml&) : AbstractNetworkConnectionConfigXml() {}
signals:

public slots:
protected:
 /*protected*/ void getInstance();
 /*protected*/ virtual void getInstance(QObject* object);
 /*protected*/ void _register();

};
Q_DECLARE_METATYPE (LnOverTcpConnectionConfigXml)
#endif // LNOVERTCPCONNECTIONCONFIGXML_H
