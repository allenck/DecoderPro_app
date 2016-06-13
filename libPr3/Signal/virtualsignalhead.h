#ifndef VIRTUALSIGNALHEAD_H
#define VIRTUALSIGNALHEAD_H
#include "defaultsignalhead.h"

class Turnout;
class LIBPR3SHARED_EXPORT VirtualSignalHead : public DefaultSignalHead
{
    Q_OBJECT
public:
    //explicit VirtualSignalHead(QObject *parent = 0);
    /*public*/ VirtualSignalHead(QString sys, QString user="", QObject *parent = 0) ;
    /*public*/ void dispose();
    /*protected*/ void updateOutput();

signals:

public slots:
private:
//    int saveAppearance;
    bool isTurnoutUsed(Turnout* t);

};

#endif // VIRTUALSIGNALHEAD_H
