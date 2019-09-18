#ifndef ABSTRACTMESSAGE_H
#define ABSTRACTMESSAGE_H
#include "message.h"
#include "logger.h"
#include <QVector>

class AbstractMessage : public Message
{
 Q_OBJECT
public:
    //explicit AbstractMessage(QObject *parent = 0);
    /*public*/ AbstractMessage(QObject *parent = 0);
    /*public*/ AbstractMessage(int n) ;
    /*public*/ AbstractMessage(QString s);
    /*public*/ AbstractMessage(AbstractMessage* m);
    /*public*/ int getElement(int n);
    // accessors to the bulk data
    /*public*/ int getNumDataElements();
    /*public*/ void setElement(int n, int v);

signals:
    
public slots:
    
private:
 Logger* log;
 QObject *parent;
 // display format

protected:
 /*protected*/ QVector<int> _dataChars;// = NULL;
 // display format
 // contents (/*private*/)
 /*protected*/ int _nDataChars;// = 0;
 friend class AbstractMRMessage;
 friend class AbstractMRReply;

 friend class SprogMessage;
 friend class AMRTXmtHandler;
};

#endif // ABSTRACTMESSAGE_H
