#ifndef LNMESSAGEMANAGER_H
#define LNMESSAGEMANAGER_H

#include <QObject>
#include "loconetmessage.h"
#include "lntrafficcontroller.h"

/**
 * Provide access to throttle-messaging on a LocoNet.
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project.  That permission
 * does not extend to uses in other software products.  If you wish to
 * use this code, algorithm or these message formats outside of JMRI, please
 * contact Digitrax Inc for separate permission.
 * <P>
 * @author	Bob Jacobsen Copyright (C) 2001
 * @version     $Revision: 17977 $
 */

class LnMessageManager : public QObject
{
    Q_OBJECT
public:
    explicit LnMessageManager(LnTrafficController* tc, QObject *parent = 0);
    void sendMessage(QString text);
    void sendMessage(int id, QString text);
    /**
     * Free resources when no longer used
     */
    void dispose();

    
signals:
    
public slots:
    void message(LocoNetMessage* m);

private:
    LnTrafficController* tc;

    
};

#endif // LNMESSAGEMANAGER_H
