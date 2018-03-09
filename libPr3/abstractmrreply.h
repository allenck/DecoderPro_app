#ifndef ABSTRACTMRREPLY_H
#define ABSTRACTMRREPLY_H
#include "abstractmessage.h"

class AbstractMRReply : public AbstractMessage
{
 Q_OBJECT
public:
 explicit AbstractMRReply(QObject *parent = 0);
 static /*public*/ /*final*/const int DEFAULTMAXSIZE = 120;
 // copy one
 /*public*/  AbstractMRReply(AbstractMRReply* m, QObject *parent = 0);
 // from String
 /*public*/ AbstractMRReply(QString s, QObject *parent = 0);
 /*public*/ void setElement(int n, int v);
 /*public*/ void setOpCode(int i);
 /*public*/ int getOpCode();
 /*public*/ void flush();
 /*public*/ bool isBinary();
 /*public*/ void setBinary(bool b);
 /*public*/ /*final*/ void setUnsolicited();
 /*public*/ bool isUnsolicited();
 /*public*/ bool isRetransmittableErrorMsg() ;
 /*public*/ QString toString();
 /*public*/ int value();
 /*public*/ int pollValue();
 /*public*/ int match(QString s);
 /*public*/ int skipWhiteSpace(int index);
 /*public*/ int maxSize();

signals:
    
public slots:
private:
 // contents (/*private*/)
 /*private*/ bool unsolicited;
 void init();
    protected:
 /*abstract*/ /*protected*/ virtual int skipPrefix(int index) =0;
 Logger* log;
 /*private*/ bool _isBinary;

};

#endif // ABSTRACTMRREPLY_H
