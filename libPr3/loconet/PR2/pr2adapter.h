#ifndef PR2ADAPTER_H
#define PR2ADAPTER_H
#include "locobufferadapter.h"

class PR2Adapter : public LocoBufferAdapter
{
public:
 PR2Adapter(QObject* parent = nullptr);
 /*public*/ void configure();
 /*public*/ QStringList validBaudRates();
 /*public*/ QVector<int> validBaudNumber();
 /*public*/ QStringList commandStationOptions();

private:
static Logger* log;

protected:
/*protected*/ void setSerialPort(SerialPort* activeSerialPort) throw (UnsupportedCommOperationException);

};

#endif // PR2ADAPTER_H
