#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "jmrijframe.h"
#include "zeroconfeventlistener.h"
#include "abstractshutdowntask.h"

struct WiDevice;
class DeviceServer;
class ServerSocket;
class ZeroConfService;
class WiThrottlesListModel;
class QLabel;
class JTable;
class RosterGroupComboBox;
class Logger;
class UserInterface : public JmriJFrame//, public ZeroConfServiceListener
{
 Q_OBJECT
 //Q_INTERFACES(ZeroConfServiceListener)
public:
 UserInterface(QWidget* parent = 0);
 /*public*/ void createServerThread();
 /*public*/ void listen();
 /*public*/ QString getSelectedRosterGroup();

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(UserInterface.class.getName());
 QMenuBar* _menuBar;
 QAction* serverOnOff;
 QWidget* panel;
 QLabel* portLabel;// = new JLabel(rb.getString("LabelPending"));
 QLabel* manualPortLabel;// = new JLabel();
 QLabel* numConnected;
 //JScrollPane scrollTable;
 JTable* withrottlesList;
 WiThrottlesListModel* withrottlesListModel;
 UserPreferencesManager* userPreferences;// = InstanceManager.getDefault(UserPreferencesManager.class);
 QString rosterGroupSelectorPreferencesName;// = this.getClass().getName() + ".rosterGroupSelector";
 RosterGroupComboBox* rosterGroupSelector;// = new RosterGroupComboBox(userPreferences.getComboBoxLastSelection(rosterGroupSelectorPreferencesName));

 // Server iVars
 int port;
 ZeroConfService* service = nullptr;
 bool isListen;// = true;
 ServerSocket* socket;// = NULL;
 QVector<WiDevice*>* deviceList;
 /*private*/ void disableServer();
 /*private*/ void stopDevices();
 DeviceServer* device;
 /*private*/ void addIPAddressesToUI();


public slots:
 void on_rosterGroupSelector(QString);
 void on_serverOnOff();
 /*public*/ void notifyDeviceConnected(WiDevice* device);
 /*public*/ void notifyDeviceDisconnected(WiDevice* device);
 /*public*/ void notifyDeviceAddressChanged(WiDevice* device);
 /*public*/ void notifyDeviceInfoChanged(WiDevice* device);
 void on_serverStateChanged(DeviceServer*);
 /*public*/ void servicePublished(ZeroConfServiceEvent* se);


protected:
 /*protected*/ void createWindow();
 /*protected*/ void buildMenu();
 /*protected*/ void setShutDownTask();

 friend class ServerThread;
 friend class UIShutdownTask;
};

/*static*/ class ServerThread : public  QObject {
Q_OBJECT
    UserInterface* UI;
    QThread* currentThread;
    QString name;
public:
    ServerThread(UserInterface* _UI);
    void setName(QString);
signals:
    void finished();
    //@Override
public slots:
    /*public*/ void start();
};

class UIShutdownTask : public AbstractShutDownTask
{
 Q_OBJECT
 UserInterface* ui;
public:
 UIShutdownTask(QString title, UserInterface* ui);
 bool execute();
};
#endif // USERINTERFACE_H
