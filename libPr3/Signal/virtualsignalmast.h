#ifndef VIRTUALSIGNALMAST_H
#define VIRTUALSIGNALMAST_H
#include "abstractsignalmast.h"

class LIBPR3SHARED_EXPORT VirtualSignalMast : public AbstractSignalMast
{
    Q_OBJECT
public:
    //explicit VirtualSignalMast(QObject *parent = 0);
    /*public*/ VirtualSignalMast(QString systemName, QString userName = "", QObject *parent = 0) ;
//    /*public*/ VirtualSignalMast(QString systemName) ;
    void configureFromName(QString systemName) ;
    /*public*/ void setAspect(QString aspect) override;
    /*public*/ static int getLastRef();
    /*public*/ QString className()override;

signals:

public slots:
private:
    static  int lastRef;// = 0;

    Logger* log;
protected:
    /*protected*/ static void setLastRef(int newVal);

};

#endif // VIRTUALSIGNALMAST_H
