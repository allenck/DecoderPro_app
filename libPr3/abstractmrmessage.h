#ifndef ABSTRACTMRMESSAGE_H
#define ABSTRACTMRMESSAGE_H
#include "abstractmessage.h"

class AbstractMessage;
class AbstractMRMessage : public AbstractMessage
{
    Q_OBJECT
public:
    //explicit AbstractMRMessage(QObject *parent = 0);
    /*public*/ AbstractMRMessage(QObject *parent = 0);
    /*public*/ AbstractMRMessage(int i, QObject *parent = 0);
    /*public*/ AbstractMRMessage(AbstractMRMessage* m, QObject *parent = 0);
    /*public*/ AbstractMRMessage(QString s, QObject *parent = 0);
    /*public*/ void setOpCode(int i);
    /*public*/ int getOpCode();
    /*public*/ QString getOpCodeHex();

    // accessors to the bulk data
    /*public*/ void setNeededMode(int pMode);
    /*public*/ int getNeededMode();

    /**
     * Is a reply expected to this message?
     * <P>
     * By default, a reply is expected to every message;
     * either a reply or a timeout is needed before the next
     * message can be sent.
     * <p>
     * If this returns false, the transmit queue will
     * immediately go on to transmitt the next message (if any).
     */
    /*public*/ bool replyExpected();
    // mode accessors
    bool _isBinary;
    /*public*/ bool isBinary();
    /*public*/ void setBinary(bool b);
    /*public*/ void setTimeout(int t);
    /*public*/ int getTimeout();
    /*public*/ void setRetries(int i);
    /*public*/ int getRetries();
    /*public*/ void addIntAsThree(int val, int offset);
    /*public*/ void addIntAsTwoHex(int val, int offset);
    /*public*/ void addIntAsThreeHex(int val, int offset);
    /*public*/ void addIntAsFourHex(int val, int offset);
    /*public*/ QString toString();

signals:
    
public slots:
private:
 Logger log;

 // state info
 int mNeededMode;
 int mTimeout;  // in milliseconds
 /*private*/ int mRetries;//=0; // number of retries, default = 0;

protected:
 static /*protected*/ /*final*/ const int SHORT_TIMEOUT=2000;
 static /*protected*/ /*final*/ const int LONG_TIMEOUT=60000;  // e.g. for programming options


};

#endif // ABSTRACTMRMESSAGE_H
