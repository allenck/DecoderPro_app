#ifndef DCCLOCOADDRESSTESTACTION_H
#define DCCLOCOADDRESSTESTACTION_H

#include <QObject>
#include "abstractaction.h"

class Logger;
class DccLocoAddressTestAction : public AbstractAction
{
 Q_OBJECT
public:
 DccLocoAddressTestAction(QObject *parent);


public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // DCCLOCOADDRESSTESTACTION_H
