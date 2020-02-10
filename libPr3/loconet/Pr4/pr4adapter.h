#ifndef PR4ADAPTER_H
#define PR4ADAPTER_H
#include "locobufferadapter.h"

class PR4SystemConnectionMemo;
class PR4Adapter : public LocoBufferAdapter
{
 Q_OBJECT
public:
 PR4Adapter(QObject *parent = 0);
 /*public*/ void configure();
 /*public*/ QStringList validBaudRates();
 /*public*/ QVector<int> validBaudNumbers() override;
 /*public*/ int defaultBaudIndex() override;
 /*public*/ QStringList commandStationOptions();
 /*public*/ SystemConnectionMemo* getSystemConnectionMemo();
 /*public*/ QString className();

private:
 static Logger* log;

protected:
 /*protected*/ void setSerialPort(SerialPort* activeSerialPort) throw (UnsupportedCommOperationException);

};

#endif // PR4ADAPTER_H
