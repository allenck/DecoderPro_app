#ifndef ABSTRACTSERIALPORTCONTROLLERTESTBASE_H
#define ABSTRACTSERIALPORTCONTROLLERTESTBASE_H
#include "abstractportcontrollertestbase.h"

class AbstractSerialPortControllerTestBase : public AbstractPortControllerTestBase
{
    Q_OBJECT
public:
    AbstractSerialPortControllerTestBase(QObject* parent = 0);
};

#endif // ABSTRACTSERIALPORTCONTROLLERTESTBASE_H
