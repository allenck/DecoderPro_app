#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include "loconetmessage.h"
#include "dialog.h"
#include "masterthread.h"
#include "instancemanager.h"
#include "locoiodialog.h"
#include "pr3adapter.h"
#include "locobufferusbadapter.h"
#include <QSignalMapper>
#include <QMutex>
#include "sql.h"
#include <QLocale>
#ifdef HAVE_FTDI
#include "../ftdilib/ftdilib.h"
#else
#include "rfidusb.h"
#endif
#include "rfidsensormanager.h"
#include "rfidreportermanager.h"
#include "slotmanager.h"
#include "llnmon.h"
#include "lnsensormanager.h"
#include "../LayoutEditor/layouteditor.h"
#include "defaultidtagmanager.h"
#include "libtables.h"
#include "paneleditor.h"
#include "slotmonitor.h"
#include "configxmlmanager.h"
#include "Roster/combinedlocoseltreepane.h"
#include "paneprogframe.h"
#include "paneprogpane.h"
#include "apps.h"


namespace Ui {
class MainWindow;
}

class ConnectionConfigFrame;
class DccAddressPanel;
class ThisProgPane;
class ProgModeSelector;
class JmriJFrameInterface;
class LocoMonPane;
class ControlPanelEditor;
class PR3Adapter;
class MainWindow : public /*JmriJFrame*/ Apps
{
 Q_OBJECT
    
public:
 explicit MainWindow(QWidget *parent = 0);
 ~MainWindow();
    
private:
 Ui::MainWindow *ui;
 Dialog* dialog;
 MasterThread* thread;
 QString portName;
 void closeEvent(QCloseEvent *event);
 InstanceManager* instanceManager;
 //LocoIODialog* dlg;
 QVector<LocoIODialog*> moduleDlg;
 PR3Adapter* pr3;
 LocoBufferUsbAdapter* locobuffer;
 LocoBufferAdapter * locoBufferAdapter;
 //QMutex mutex;
 LocoIOData* data;
 QList<LocoIOAddress* > list;
 QSignalMapper* signalMapper;
 bool bHexValues;
 void getSettings();
 void saveSettings();
 bool checkDirty();
 Sql* sql;
 QString commandStationType;
 QTranslator     m_translator;   /**< contains the translations for this application */
 QTranslator     m_translatorQt; /**< contains the translations for qt */
 QString         m_currLang;     /**< contains the currently loaded language */
 QString         m_langPath;     /**< Path of language files. This is always fixed to /languages. */
 void recalculateLanguageMenu(QString default_Locale);
 QString default_Locale;
#ifdef HAVE_FTDI
 Ftdilib* ftdilib;
 RfidSensorManager* rfidSensorManager;
 RfidReporterManager* rfidReporterManager;
 DefaultIdTagManager* rfidTagManager;
#else
 RfidUsb* rfidPort;
#endif
 void openRfid();
 void onNewPortName(QString portName);
 QSerialPortInfo info;
 SlotManager* slotManager;
 LocoNetSystemConnectionMemo* connectionMemo;
 LlnMon* lnMon;
 LnTurnoutManager* loconetTurnoutManager;
 LnSensorManager* loconetSensorManager;
 LayoutEditor* editor;
 PanelEditor* panelEditor;
 LibTables* libTables;
 LnLightManager* loconetLightManager;
 SlotMonitor* slotMonitor;
 ControlPanelEditor* frame;
 bool bAutoScrollToBottom;
 ConfigXmlManager* configXmlManager;
 LocoMonPane* locoMonPane;
 JmriJFrameInterface* ifc;
 JmriJFrame* f;
 CombinedLocoSelTreePane* combinedLocoSelTree;
 QWidget* bottomPanel;
 Logger* log;
 QLabel* statusLabel;
 ProgModeSelector* modePane;// = new ProgServiceModeComboBox();
 ConnectionConfigFrame* configFrame;
 JTextField* owner;// = new JTextField(20);
 bool checkActive();

private slots:
// void showResponse(const QByteArray &ba);
 void timeout(const QString &s);
 void error(const QString &s);
 //void on_actionConfig_triggered();
 void on_actionClear_display_triggered();
 void on_actionExit_triggered();
 //void on_actionRoster_triggered();
// void MessageReceived(LocoNetMessage* m, bool bOutput);
 //void on_actionLocoIO_triggered(bool bNewAddress);
 //void onProbeCompleted(QList<LocoIOAddress*> list);
 //void onLocoIO_selected(int index);
 void onMessageReceived(LocoNetMessage *m, bool);
 void on_actionValues_in_Hex_toggled(bool bChecked);
 //void on_actionProbe_triggered();
 void on_actionQuery_Cv_triggered();
 void onPortOpenError(QString s);
 void on_actionAbout_triggered();
 void onCommandStationTypeSelected(QAction*);
 void create_Language_Menu(void);
 void switch_Translator(QTranslator& this_translator,const QString& s_filename,QString s_icon_Name="");
 void load_Language(const QString& s_Language);
 void retranslate_Menus();
 void onNewPortInfo(QSerialPortInfo info);
#ifdef HAVE_FTDI
 void OnRfidRcvd(ftdiMsg * msg);
#endif
 void on_actionLocoNet_Message_triggered();
 void on_actionObject_View_triggered();
 void on_actionLayout_Editor_triggered();
 void on_actionTables_triggered();
 void on_actionPanel_Editor_triggered();
 void on_actionNew_Throttle_triggered();
 void on_actionThrottle_Windows_triggered();
// void on_menuWindow_aboutToShow();
 void on_actionSlot_monitor_triggered();
 void on_actionControl_Panel_Editor_triggered();
 void on_actionAuto_scroll_to_bottom_triggered(bool);
 void on_actionSetup_Fast_Clock_triggered();
 void on_actionNixie_Clock_triggered();
 void on_actionLCD_Clock_triggered();
 void on_actionAnalog_Clock_triggered();
 void on_actionPower_Control_triggered();
 void on_actionTurnouts_triggered();
 void on_actionMonitor_triggered();
 void OnConsoleMessageReceived(QString s);
 void on_actionService_Mode_Programmer_Programmer_track_triggered();
 void on_actionTest_glass_pane_triggered();
 //void on_actionConfigure_Command_Station_triggered();
 void on_actionPreferences_triggered();
 //void on_actionConnection_Config_triggered();
 //void on_actionConnect_triggered();
 void On_newConnection(PropertyChangeEvent* = 0);

protected:
 /** this event is called,when a new translator is loaded or the system language is changed
  */
 void changeEvent(QEvent*);

protected slots:
 /** this slot is called by the language menu actions
   */
 void slot_Language_Changed(QAction* action);
signals:
 void retranslateControls();
 friend class MyCombinedLocoSelTreePane;
 friend class Connect;
};

//The connection process is placed into its own thread so that it doens't hog the swingthread while waiting for the connections to open.
/*protected*/ class Connect : public Runnable
{
    Q_OBJECT
    MainWindow* parent;
public:
    Connect(MainWindow* parent);
    /*public*/ void run();
};
#endif // MAINWINDOW_H
