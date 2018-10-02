#ifndef SERVERLISTNER_H
#define SERVERLISTNER_H
#include "lntcpserver.h"
/**
 * Implementation of the LocoNetOverTcp LbServer Server Protocol
 *
 * @author Alex Shepherd Copyright (C) 2006
 * @version	$Revision: 28746 $
 */
/*public*/ /*interface*/ class ServerListner : public QObject
{
public:
 ServerListner(QObject* parent) : QObject(parent) {}

 /*public*/ virtual void notifyServerStateChanged(LnTcpServer* s) {}

 /*public*/ virtual void notifyClientStateChanged(LnTcpServer* s) {}
};
#endif // SERVERLISTNER_H
