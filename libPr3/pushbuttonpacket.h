#ifndef PUSHBUTTONPACKET_H
#define PUSHBUTTONPACKET_H

#include <QObject>
#include "logger.h"

class PushbuttonPacket : public QObject
{
    Q_OBJECT
public:
    explicit PushbuttonPacket(QObject *parent = 0);
    /**
     * Valid stationary decoder names
     */
    /*public*/ /*final*/ static QString unknown;// = "None";
    /*public*/ /*final*/ static QString NCEname;// = "NCE_Rev_C";
    /*public*/ /*final*/ static QString CVP_1Bname;// = "CVP_AD4_1B";
    /*public*/ /*final*/ static QString CVP_2Bname;// = "CVP_AD4_2B";
    /*public*/ static QByteArray pushbuttonPkt(QString prefix, int turnoutNum, bool locked);
    /*public*/ static QStringList getValidDecoderNames();


signals:

public slots:

   private:
    /*private*/ /*final*/ static QStringList VALIDDECODERNAMES;// = { unknown, NCEname, CVP_1Bname,
//		CVP_2Bname };
    Logger* log;
    /*private*/ static int CVPturnoutLockout(QString prefix, int turnoutNum);

};

#endif // PUSHBUTTONPACKET_H
