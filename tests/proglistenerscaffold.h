#ifndef PROGLISTENERSCAFFOLD_H
#define PROGLISTENERSCAFFOLD_H
#include "proglistener.h"


class ProgListenerScaffold : public ProgListener
{
    Q_OBJECT
public:
    ProgListenerScaffold();
    /*public*/ int getRcvdValue();
    /*public*/ int getRcvdStatus();
    /*public*/ int getRcvdInvoked();
    /*public*/ bool wasRightThread();
    /*public*/ bool reset();

public slots:
    /*public*/ void programmingOpReply(int value, int status);

private:
    /*private*/ int rcvdValue;
    /*private*/ int rcvdStatus;
    /*private*/ int rcvdInvoked;
    /*private*/ bool wasOnRightThread;


};

#endif // PROGLISTENERSCAFFOLD_H
