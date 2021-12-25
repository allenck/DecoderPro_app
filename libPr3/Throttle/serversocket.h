#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include "exceptions.h"

class ServerSocket : public QObject
{
 Q_OBJECT
public:
 explicit ServerSocket(QTcpSocket* impl, QObject *parent = 0);
 /*public*/ int getLocalPort();
 /*public*/ ServerSocket(QObject *parent = 0) /*throw (IOException)*/;
 /*public*/ ServerSocket(int port, QObject *parent = 0) /*throw (IOException)*/;
 /*public*/ bool isBound();
 /*public*/ void close() /*throw (IOException)*/;
 /*public*/ bool isClosed();

signals:

public slots:

private:
 /**
  * Various states of this socket.
  */
 /*private*/ bool created;// = false;
 /*private*/ bool bound;// = false;
 /*private*/ bool closed;// = false;
 /*private*/ QObject* closeLock;// = new Object();

 /**
  * The implementation of this Socket.
  */
 /*private*/ /*SocketImpl*/QTcpSocket* impl;

 /**
  * Are we using an older SocketImpl?
  */
 /*private*/ bool oldImpl;// = false;

};

#endif // SERVERSOCKET_H
