#ifndef ABSTRACTNETWORKCONNECTIONCONFIG_H
#define ABSTRACTNETWORKCONNECTIONCONFIG_H
#include "abstractconnectionconfig.h"
#include "logger.h"
#include "libPr3_global.h"
#include <qhostinfo.h>
#include "spinnernumbermodel.h"
#include "jspinner.h"
#include <QPushButton>

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
 /*public*/ void updateAdapter() override;
 /*public*/ PortAdapter* getAdapter() override;
 /*public*/ QString getInfo() override;
 /*public*/ void loadDetails(/*final*/ JPanel *details) override;
 /*public*/ virtual bool isHostNameAdvanced();
 /*public*/ virtual bool isPortAdvanced();
 /*public*/ virtual bool isAutoConfigPossible() ;
 /*public*/ QString getManufacturer();
 /*public*/ void setManufacturer(QString manufacturer) override;
 /*public*/ bool getDisabled() override;
 /*public*/ void setDisabled(bool disabled) override;
 /*public*/ QString getConnectionName() override;
 /*public*/ void dispose() override;

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
 void showAdvancedItems() override;
 //void autoConfig();

private:
 void common();
 Logger* log;
 UserPreferencesManager* p;// = InstanceManager.getDefault("UserPreferencesManager");

private slots:
 void on_optionCb_currentIndexChanged(QWidget*);
 //void updated();
 void on_lookupHost(QHostInfo);

protected:
 /*protected*/ bool init = false;
  /*protected*/ void checkInitDone() override;
 /*protected*/ JTextField* hostNameField;// = new JTextField(15);
 /*protected*/ QLabel* hostNameFieldLabel;
 /*protected*/ JTextField* portField;// = new JTextField(10);
 /*protected*/ QLabel* portFieldLabel;

 /*protected*/ QCheckBox* showAutoConfig;// = new JCheckBox(rb.getString("AutoConfigLabel"));
 /*protected*/ JTextField* adNameField;// = new JTextField(15);
 /*protected*/ QLabel* adNameFieldLabel;
 /*protected*/ JTextField* serviceTypeField;// = new JTextField(15);
 /*protected*/ QLabel* serviceTypeFieldLabel;

 /*protected*/ SpinnerNumberModel* intervalSpinner = new SpinnerNumberModel(250, 0, 10000, 1); // 10 sec max seems long enough
 /*protected*/ JSpinner* outputIntervalSpinner = new JSpinner(intervalSpinner);
 /*protected*/ JLabel* outputIntervalLabel;
 /*protected*/ QPushButton* outputIntervalReset = new QPushButton(tr("Reset"));

 /*protected*/ NetworkPortAdapter* adapter = nullptr;
 /*abstract*/ /*protected*/ virtual void setInstance() override;
 /*protected*/ int addStandardDetails(bool incAdvanced, int i);

};

#endif // ABSTRACTNETWORKCONNECTIONCONFIG_H
