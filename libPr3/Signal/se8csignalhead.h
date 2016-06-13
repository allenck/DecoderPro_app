#ifndef SE8CSIGNALHEAD_H
#define SE8CSIGNALHEAD_H
#include "defaultsignalhead.h"
#include "namedbeanhandle.h"

class  Turnout;
class LIBPR3SHARED_EXPORT SE8cSignalHead : public DefaultSignalHead
{
    Q_OBJECT
public:
    //explicit SE8cSignalHead(QObject *parent = 0);
    /*public*/ SE8cSignalHead(NamedBeanHandle<Turnout*>* lowTO,
                            NamedBeanHandle<Turnout*>* highTO,
                              QString userName = "", QObject *parent= 0);
    /*public*/ SE8cSignalHead(QString sname, NamedBeanHandle<Turnout*>* lowTO,
                            NamedBeanHandle<Turnout*>* highTO,
                              QString userName="", QObject *parent= 0);
    /*public*/ SE8cSignalHead(int pNumber, QString username= "", QObject *parent = 0);
    static QString makeSystemName(NamedBeanHandle<Turnout*>* lowTO,
                            NamedBeanHandle<Turnout*>* highTO);
    static NamedBeanHandle<Turnout*>* makeHandle(int i);
    /*public*/ QString getSystemName();
    /*public*/ SE8cSignalHead(int pNumber);
    /*public*/ NamedBeanHandle<Turnout*>* getLow();
    /*public*/ NamedBeanHandle<Turnout*>* getHigh();
    /*public*/ void dispose();

signals:

public slots:
private:
    NamedBeanHandle<Turnout*>* lowTurnout;
    NamedBeanHandle<Turnout*>* highTurnout;
    void init();
    QString systemName;
protected:
    /*protected*/ void updateOutput();
 Logger* log;
};

#endif // SE8CSIGNALHEAD_H
