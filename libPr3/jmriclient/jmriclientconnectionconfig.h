#ifndef CONNECTIONCONFIG_H
#define CONNECTIONCONFIG_H
#include "abstractnetworkconnectionconfig.h"

class JmriClientConnectionConfig : public AbstractNetworkConnectionConfig
{
 Q_OBJECT
public:
 JmriClientConnectionConfig();
 /*public*/ JmriClientConnectionConfig(NetworkPortAdapter* p);
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

#endif // CONNECTIONCONFIG_H
