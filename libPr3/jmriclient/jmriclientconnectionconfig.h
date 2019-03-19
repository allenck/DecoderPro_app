#ifndef JMRICLIENTCONNECTIONCONFIG_H
#define JMRICLIENTCONNECTIONCONFIG_H
#include "abstractnetworkconnectionconfig.h"

class JMRIClientConnectionConfig : public AbstractNetworkConnectionConfig
{
 Q_OBJECT
public:
 Q_INVOKABLE JMRIClientConnectionConfig();
 ~JMRIClientConnectionConfig() {}
 JMRIClientConnectionConfig(const JMRIClientConnectionConfig&) : AbstractNetworkConnectionConfig() {}
 /*public*/ JMRIClientConnectionConfig(NetworkPortAdapter* p);
 /*public*/ QString name();
 /*public*/ bool isPortAdvanced();
 /*public*/ void updateAdapter();
 /*public*/ bool isHostNameAdvanced();
 /*public*/ bool isAutoConfigPossible();

private:
 void common();
private slots:
 void onTransmitPrefixField_editingFinished();
 void onTransmitPrefixField_left();

protected:
 /*protected*/ QLabel* transmitPrefixLabel;// = new JLabel("Server Connection Prefix");
 /*protected*/ JTextField* transmitPrefixField;// = new JTextField(10);
 /*protected*/ void setInstance();
 /*protected*/ void checkInitDone();
 /*protected*/ void showAdvancedItems();


};
Q_DECLARE_METATYPE(JMRIClientConnectionConfig)
#endif // JMRICLIENTCONNECTIONCONFIG_H
