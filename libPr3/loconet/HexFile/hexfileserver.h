#ifndef HEXFILESERVER_H
#define HEXFILESERVER_H

#include <QObject>
#include "logger.h"
#include "libPr3_global.h"

class LnHexFilePort;
class LnPacketizer;
class LIBPR3SHARED_EXPORT HexFileServer : public QObject
{
    Q_OBJECT
public:
    //explicit HexFileServer(QObject *parent = 0);
    /*public*/ HexFileServer(QObject *parent) ;
    /*public*/ void dispose();
    /*public*/ void configure();
    /*public*/ void setAdapter(LnHexFilePort* adapter);
    /*public*/ LnHexFilePort* getAdapter();

signals:

public slots:
private:
bool connected;//= false;
LnPacketizer* packets;// = null;
Logger* log;
/*private*/ QThread* sourceThread;
/*private*/ LnHexFilePort* port;// = NULL;

};

#endif // HEXFILESERVER_H
