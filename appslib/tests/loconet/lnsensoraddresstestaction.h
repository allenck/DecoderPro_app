#ifndef LNSENSORADDRESSTESTACTION_H
#define LNSENSORADDRESSTESTACTION_H

#include "abstractaction.h"

class Logger;
class LnSensorAddressTestAction : public AbstractAction
{
 Q_OBJECT
public:
 LnSensorAddressTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // LNSENSORADDRESSTESTACTION_H
