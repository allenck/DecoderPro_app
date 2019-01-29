#ifndef INET4ADDRESS_H
#define INET4ADDRESS_H
#include "inetaddress.h"

class Inet4Address : public InetAddress
{
 Q_OBJECT
public:
 Inet4Address();
 Inet4Address(QString hostName, QByteArray addr);
 Inet4Address(QString hostName, int address);
 /*public*/ bool isMulticastAddress();
 /*public*/ bool isAnyLocalAddress();
 /*public*/ bool isLoopbackAddress();
 /*public*/ bool isLinkLocalAddress();
 /*public*/ bool isSiteLocalAddress();
 /*public*/ bool isMCGlobal();
 /*public*/ bool isMCNodeLocal();
 /*public*/ bool isMCLinkLocal();
 /*public*/ bool isMCSiteLocal();
 /*public*/ bool isMCOrgLocal();
 /*public*/ QByteArray getAddress();
 /*public*/ QString getHostAddress();
 /*public*/ int hashCode();
 /*public*/ bool equals(QObject* obj);
 static QString numericToTextFormat(QByteArray src);

private:
 /*final*/ static int INADDRSZ;// = 4;
 // /*private*/ static native void init();

};

#endif // INET4ADDRESS_H
