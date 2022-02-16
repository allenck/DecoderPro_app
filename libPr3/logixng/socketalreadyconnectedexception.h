#ifndef SOCKETALREADYCONNECTEDEXCEPTION_H
#define SOCKETALREADYCONNECTEDEXCEPTION_H
#include "jmriexception.h"
#
class SocketAlreadyConnectedException : public JmriException
{
 public:
  SocketAlreadyConnectedException();
/*public*/ SocketAlreadyConnectedException(QString msg);
};

#endif // SOCKETALREADYCONNECTEDEXCEPTION_H
