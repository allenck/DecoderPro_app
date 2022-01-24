#ifndef SOCKETALREADYCONNECTEDEXCEPTION_H
#define SOCKETALREADYCONNECTEDEXCEPTION_H
#include "exceptions.h"

class SocketAlreadyConnectedException : public JmriException
{
 public:
  SocketAlreadyConnectedException();
/*public*/ SocketAlreadyConnectedException(QString msg);
};

#endif // SOCKETALREADYCONNECTEDEXCEPTION_H
