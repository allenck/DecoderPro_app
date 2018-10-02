#ifndef SYSTEMCONNECTIONMEMOMANAGER_H
#define SYSTEMCONNECTIONMEMOMANAGER_H
#include "bean.h"
#include "systemconnectionmemo.h"

class Logger;
class SystemConnectionMemoManager : public Bean
{
public:
 SystemConnectionMemoManager();
 /*public*/ /*final*/ static QString CONNECTION_ADDED;// = "ConnectionAdded";
 /*public*/ /*final*/ static QString CONNECTION_REMOVED;// = "ConnectionRemoved";
 /*public*/ void _register(SystemConnectionMemo* memo);
 /*public*/ void deregister(SystemConnectionMemo* memo);
 /*public*/ /*synchronized*/ SystemConnectionMemo* getSystemConnectionMemo(/*@Nonnull*/ QString systemPrefix,/* @Nonnull*/ QString userName);
 /*public*/ /*synchronized*/ SystemConnectionMemo* getSystemConnectionMemoForUserName(/*@Nonnull */QString userName);
 /*public*/ /*synchronized*/ SystemConnectionMemo* getSystemConnectionMemoForSystemPrefix(/*@Nonnull*/ QString systemPrefix);
 /*public*/ /*synchronized*/ bool isUserNameAvailable(/*@Nonnull*/ QString userName);
 /*public*/ /*synchronized*/ bool isSystemPrefixAvailable(/*@Nonnull*/ QString systemPrefix);
 /*public*/ static SystemConnectionMemoManager* getDefault();


private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SystemConnectionMemoManager");

};

#endif // SYSTEMCONNECTIONMEMOMANAGER_H
