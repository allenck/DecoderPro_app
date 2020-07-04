#ifndef ZEROCONFPREFERENCES_H
#define ZEROCONFPREFERENCES_H
#include "preferencesbean.h"

class Logger;
class ZeroConfPreferences : public PreferencesBean
{
 Q_OBJECT
public:
 ZeroConfPreferences(Profile* profile);
 /*public*/ static /*final*/ QString USE_IP_V4;// = "useIPv4";
 /*public*/ static /*final*/ QString USE_IP_V6;// = "useIPv6";
 /*public*/ static /*final*/ QString USE_LOOPBACK;// = "useLoopback";
 /*public*/ static /*final*/ QString USE_LINK_LOCAL;// = "useLinkLocal";
 /*public*/ bool isUseIPv4();
 /*public*/ void setUseIPv4(bool useIPv4);
 /*public*/ bool isUseIPv6();
 /*public*/ void setUseIPv6(bool useIPv6);
 /*public*/ bool isUseLoopback();
 /*public*/ void setUseLoopback(bool useLoopback);
 /*public*/ bool isUseLinkLocal();
 /*public*/ void setUseLinkLocal(bool useLinkLocal);
 /*public*/ void savePreferences(Profile* profile);

private:
 /*private*/ bool useIPv4 = true;
 /*private*/ bool useIPv6 = true;
 /*private*/ bool useLoopback = false;
 /*private*/ bool useLinkLocal = true;
 QT_DEPRECATED     /*private*/ static /*final*/ QString IPv4;// = "IPv4";
 QT_DEPRECATED     /*private*/ static /*final*/ QString IPv6;// = "IPv6";
 static Logger* log;
 QString getClass();
};

#endif // ZEROCONFPREFERENCES_H
