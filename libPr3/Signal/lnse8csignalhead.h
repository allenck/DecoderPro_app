#ifndef SE8CSIGNALHEAD_H
#define SE8CSIGNALHEAD_H
#include "defaultsignalhead.h"

class LnTrafficController;
class LocoNetMessage;
class LIBPR3SHARED_EXPORT LnSE8cSignalHead : public DefaultSignalHead
{
    Q_OBJECT
public:
   //explicit Se8cSignalHead(QObject *parent = 0);
    /*public*/ LnSE8cSignalHead(int pNumber, QString userName = "", QObject *parent = 0);
//    /*public*/ SE8cSignalHead(int pNumber, QObject *parent = 0);
    /*public*/ int getNumber();
    /*public*/ QString getSystemName();
    /*public*/ void message(LocoNetMessage* l);
    /*public*/ void dispose();

signals:

public slots:
private:
    LnTrafficController* tc;
    void init(int pNumber);
    /*private*/ bool myAddress(int a1, int a2) ;
    /*private*/ bool myAddressPlusOne(int a1, int a2);
    int mNumber;
    Logger* log;
protected:
    /*protected*/ void updateOutput();


};

#endif // SE8CSIGNALHEAD_H
