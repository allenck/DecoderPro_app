#ifndef DEFAULTFEMALEGENERICEXPRESSIONSOCKET_H
#define DEFAULTFEMALEGENERICEXPRESSIONSOCKET_H

#include "abstractfemalesocket.h"
#include "femalegenericexpressionsocket.h"
#include "defaultfemaleanalogexpressionsocket.h"
class FemaleStringExpressionSocket;
class FemaleDigitalExpressionSocket;
class FemaleAnalogExpressionSocket;
class DefaultFemaleGenericExpressionSocket : public AbstractFemaleSocket, public FemaleGenericExpressionSocket, public FemaleSocketListener
{
 public:
  DefaultFemaleGenericExpressionSocket();

 private:
  /*private*/ SocketType* _socketType;             // The type of the socket the user has selected
  /*private*/ SocketType* _currentSocketType;      // The current type of the socket.
  /*private*/ FemaleSocket* _currentActiveSocket;  // The socket that is currently in use, if any. Null otherwise.
  /*private*/ /*final*/ FemaleAnalogExpressionSocket* _analogSocket = new DefaultFemaleAnalogExpressionSocket(this, this, "A");
  /*private*/ /*final*/ FemaleDigitalExpressionSocket* _digitalSocket = new DefaultFemaleDigitalExpressionSocket(this, this, "D");
  /*private*/ /*final*/ FemaleStringExpressionSocket* _stringSocket = new DefaultFemaleStringExpressionSocket(this, this, "S");
  /*private*/ bool _do_i18n;

};

#endif // DEFAULTFEMALEGENERICEXPRESSIONSOCKET_H
