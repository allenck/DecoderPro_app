#ifndef LNTCPDRIVERADAPTER_H
#define LNTCPDRIVERADAPTER_H
#include "lnnetworkportcontroller.h"

class LnTcpDriverAdapter : public LnNetworkPortController
{
 Q_OBJECT
public:
 explicit LnTcpDriverAdapter(QObject *parent = 0);
 /*public*/ void configure();
 /*public*/ bool status();
 /*public*/ void configureOption1(QString value);

signals:

public slots:
 void on_rcvHandlerTerminated();

private:
 // /*private*/ control members
 /*private*/ bool opened;// = false;
 Logger* log;
};

#endif // LNTCPDRIVERADAPTER_H
