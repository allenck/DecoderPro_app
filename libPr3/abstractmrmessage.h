#ifndef ABSTRACTMRMESSAGE_H
#define ABSTRACTMRMESSAGE_H
#include "abstractmessage.h"

class AbstractMRMessage : public AbstractMessage
{
 Q_OBJECT
public:
 AbstractMRMessage(QObject* parent = 0);
 /*public*/ AbstractMRMessage(int i, QObject* parent = 0 );
 /*public*/ AbstractMRMessage(/*@Nonnull*/ AbstractMRMessage* m, QObject* parent =0 );
 /*public*/ AbstractMRMessage(QString s, QObject* parent =0);
 /*public*/ void setOpCode(int i);
 /*public*/ int getOpCode();
 /*public*/ QString getOpCodeHex();
 /*public*/ void setNeededMode(int pMode);
 /*public*/ int getNeededMode();
 /*public*/ bool replyExpected();
 /*public*/ bool isBinary();
 /*public*/ void setBinary(bool b);
 /*public*/ void setTimeout(int t);
 /*public*/ int getTimeout() ;
 /*public*/ void setRetries(int i);
 /*public*/ int getRetries();
 /*public*/ void addIntAsThree(int val, int offset);
 /*public*/ void addIntAsTwoHex(int val, int offset);
 /*public*/ void addIntAsThreeHex(int val, int offset);
 /*public*/ void addIntAsFourHex(int val, int offset);
 /*public*/ QString toString();


private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("AbstractMRMessage");
 void common();
 void common(int);
 // state info
 int mNeededMode;
 bool _isBinary;
 int mTimeout;  // in milliseconds
 /* For some systems, we want to retry sending a message if the port
  isn't ready for them. */
 /*private*/ int mRetries;// = 0; // number of retries, default = 0;

protected:
 static /*protected*/ /*final*/ int SHORT_TIMEOUT;// = 2000;
 static /*protected*/ /*final*/ int LONG_TIMEOUT;// = 60000;  // e.g. for programming options

};

#endif // ABSTRACTMRMESSAGE_H
