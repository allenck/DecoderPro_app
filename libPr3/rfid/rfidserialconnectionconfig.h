#ifndef RFIDSERIALCONNECTIONCONFIG_H
#define RFIDSERIALCONNECTIONCONFIG_H
#include "abstractserialconnectionconfig.h"

class JPanel;
class RfidSerialConnectionConfig : public AbstractSerialConnectionConfig
{
public:
 Q_INVOKABLE RfidSerialConnectionConfig(QObject* parent = nullptr);
 ~RfidSerialConnectionConfig() {}
 RfidSerialConnectionConfig(const RfidSerialConnectionConfig&) : AbstractSerialConnectionConfig() {}
 /*public*/ RfidSerialConnectionConfig(SerialPortAdapter* p, QObject *parent = nullptr);
 /*public*/ void loadDetails(QWidget *details);
 /*public*/ QString name();
 /*protected*/ void setInstance();

public slots:
 void optionBox1(QString);
 void optionBox3(QString);

private:
 /*private*/ void enableOpt2(QVariant o);
 /*private*/ void enableOpt3(QVariant o);
 /*private*/ void enableOpt4(QVariant o);

};
Q_DECLARE_METATYPE(RfidSerialConnectionConfig)
#endif // RFIDSERIALCONNECTIONCONFIG_H
