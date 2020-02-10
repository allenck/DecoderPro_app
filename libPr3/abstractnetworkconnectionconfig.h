#ifndef ABSTRACTNETWORKCONNECTIONCONFIG_H
#define ABSTRACTNETWORKCONNECTIONCONFIG_H
#include "abstractconnectionconfig.h"
#include "logger.h"
#include "libPr3_global.h"

class JLabel;
class QCheckBox;
class JTextField;
class UserPreferencesManager;
class NetworkPortAdapter;
class LIBPR3SHARED_EXPORT AbstractNetworkConnectionConfig : public AbstractConnectionConfig
{
 Q_OBJECT
public:
 explicit AbstractNetworkConnectionConfig(QObject *parent = 0);
 /*public*/ AbstractNetworkConnectionConfig(NetworkPortAdapter* p,QObject *parent);
 /*public*/ void updateAdapter();
 /*public*/ PortAdapter* getAdapter();
 /*public*/ QString getInfo();
 /*public*/ void loadDetails(/*final*/ JPanel *details);
 /*public*/ bool isHostNameAdvanced();
 /*public*/ bool isPortAdvanced();
 /*public*/ bool isAutoConfigPossible() ;
 /*public*/ QString getManufacturer();
 /*public*/ void setManufacturer(QString manufacturer);
 /*public*/ bool getDisabled();
 /*public*/ void setDisabled(bool disabled);
 /*public*/ QString getConnectionName();
 /*public*/ void dispose();

signals:

public slots:
 void on_hostNameField_leave();
 void on_portField_leave();
 void on_adNameField_leave();
 void on_serviceTypeField_leave();
 void on_systemPrefixField_editingFinished();
 void on_systemPrefixField_leave();
 void on_connectionNameField_leave();
 /*public*/ void setAutoNetworkConfig();
 void showAdvancedItems();
 void autoConfig();

private:
 void common();
 Logger* log;
 UserPreferencesManager* p;// = InstanceManager.getDefault("UserPreferencesManager");

private slots:
 void on_optionCb_currentIndexChanged(QWidget*);
 void updated();

protected:
 /*protected*/ bool init = false;
  /*protected*/ void checkInitDone();
 /*protected*/ JTextField* hostNameField;// = new JTextField(15);
 /*protected*/ QLabel* hostNameFieldLabel;
 /*protected*/ JTextField* portField;// = new JTextField(10);
 /*protected*/ QLabel* portFieldLabel;

 /*protected*/ QCheckBox* showAutoConfig;// = new JCheckBox(rb.getString("AutoConfigLabel"));
 /*protected*/ JTextField* adNameField;// = new JTextField(15);
 /*protected*/ QLabel* adNameFieldLabel;
 /*protected*/ JTextField* serviceTypeField;// = new JTextField(15);
 /*protected*/ QLabel* serviceTypeFieldLabel;

 /*protected*/ NetworkPortAdapter* adapter = nullptr;
 /*abstract*/ /*protected*/ virtual void setInstance();
 /*protected*/ int addStandardDetails(bool incAdvanced, int i);

};

#endif // ABSTRACTNETWORKCONNECTIONCONFIG_H
