#ifndef VIRTUALSIGNALHEAD_H
#define VIRTUALSIGNALHEAD_H
#include "defaultsignalhead.h"

class Turnout;
class LIBPR3SHARED_EXPORT VirtualSignalHead : public DefaultSignalHead
{
    Q_OBJECT
public:
    //explicit VirtualSignalHead(QObject *parent = 0);
    /*public*/ VirtualSignalHead(QString sys, QString user, QObject *parent = 0) ;
    /*public*/ VirtualSignalHead(QString sys, QObject *parent = 0);

    /*public*/ void dispose() override;
    /*protected*/ void updateOutput() override;

signals:

public slots:
private:
//    int saveAppearance;
    bool isTurnoutUsed(Turnout* t) override;

};

#endif // VIRTUALSIGNALHEAD_H
