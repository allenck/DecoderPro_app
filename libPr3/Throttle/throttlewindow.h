#ifndef THROTTLEWINDOW_H
#define THROTTLEWINDOW_H

#include "../LayoutEditor/jmrijframe.h"
#include "loconetthrottle.h"
#include <QPushButton>
#include "abstractthrottlemanager.h"
#include "libPr3_global.h"

namespace Ui {
class ThrottleWindow;
}
class FunctionPanel;
class ControlPanel;
class AddressPanel;
class LnPowerManager;
class LnThrottleManager;
class ListThrottles;
class RosterEntry;
class LIBPR3SHARED_EXPORT ThrottleWindow : public JmriJFrame
{
    Q_OBJECT

public:
    explicit ThrottleWindow(/*LocoNetSystemConnectionMemo* memo = 0,*/ QWidget *parent = 0);
    ~ThrottleWindow();
    void notifyThrottleFound(DccThrottle* t);
    void enableControlPanel(bool bState);
    QString getTitle();
    Throttle* getThrottle();
    QString id();
//    void setId(QString id);
    RosterEntry* getRosterEntry();
    /*public*/ void loadThrottle(QString sfile);
    /*public*/ QString getTitleTextType();
    /*public*/ QString getTitleText() ;
    /*public*/ void setTitleText(QString titleText) ;
    /*public*/ void setTitleTextType(QString titleTextType);
    /*public*/ void nextRunningThrottleFrame();
    /*public*/ void nextThrottleFrame();
    /*public*/ void previousRunningThrottleFrame();
    /*public*/ void previousThrottleFrame();
    /*public*/ void dispose();
    /*public*/ void removeThrottleFrame(ThrottleWindow* tf);
    /*public*/ void addThrottleFrame(ThrottleWindow* tp);
    /*public*/ ThrottleWindow* addThrottleFrame();
    /*public*/ void setCurrentThrottleFrame(ThrottleWindow* tf);
    /*public*/ ThrottleWindow* getCurrentThrottleFrame();
    /*public*/ void updateGUI();
    AddressPanel* getAddressPanel();
    ControlPanel* getControlPanel();
    FunctionPanel* getFunctionPanel();
    /*public*/ QString getLastUsedSaveFile();
    /*public*/ void setFrameTitle();


public slots:
    /*public*/ void saveThrottle();
    /*public*/ void saveThrottleAs();
    void notifyAddressThrottleFound(DccThrottle*t);


signals:
    void throttleWindowupdate(PropertyChangeEvent*);
    void propertyChange(QString, QObject*, QObject*);

private slots:

//    void on_newThrottle_clicked();
//    void on_removeThrottle_clicked();

    void on_emergencyStop_clicked();
    void on_togglePower_clicked();
    void on_actionNew_Throttle_triggered();
    void on_actionPower_On_triggered();
    void on_actionPower_Off_triggered();
    void on_listView_clicked();
    void on_menuWindow_aboutToShow();
    void on_actionAddress_Panel_toggled(bool bChecked);
    void on_actionControl_Panel_toggled(bool bChecked);
    void on_actionFunction_Panel_toggled(bool bChecked);
    void notifyChangedSlot(LocoNetSlot*);
    void removeThrottleFrame();
    void OnFileMenuLoad();
    void on_address_released(LocoAddress*);

    private:
    Ui::ThrottleWindow *ui;
    AddressPanel* addressPanel;
    ControlPanel* controlPanel;
    FunctionPanel* functionPanel;
    LocoNetThrottle* throttle;
//    LocoNetSystemConnectionMemo* memo;
    QAction* addThrottle;
    QAction* removeThrottle;
    QAction* previousRunning;
    QAction* previous;
    QAction* nextRunning;
    QAction* next;
    QAction* emergencyStop;
    QAction* togglePower;
    QAction* editView;
    QAction* listViewAct;
    QAction* fileMenuSave;
    QAction* viewAddressPanel;
    QAction* viewControlPanel;
    QAction* viewFunctionPanel;
    QAction* viewAllButtons;
    QAction* editMenuExportRoster;

    LnThrottleManager* mgr;
    /*private*/ void initializeMenu();
    void fillCbRoster();
    void getSettings();
    void saveSettings();
    void closeEvent(QCloseEvent *);
    Logger* log;
    ListThrottles* listViewDlg;
    bool bAltFunc;
    void setAltFunc(bool bAltFunc);

    QWidget* parent;
    RosterEntry* rosterEntry;
    LnPowerManager* powerMgr;
    QString titleTextType;
    QString titleText;
    /*private*/ void saveThrottle(QString sfile);
    /*private*/ QMap<QString, ThrottleWindow*>* throttleFrames;// = new QMap<QString, ThrottleWindow*>(/*5*/);
    /*private*/ int cardCounterID;// = 0; // to generate unique names for each card
    /*private*/ int cardCounterNB;// = 1; // real counter
//    /*private*/ CardLayout throttlesLayout;
    /*private*/ bool isEditMode;// = true;
    ThrottleWindow* currentThrottleFrame;
    QString lastUsedSaveFile;
    void windowClosing(QCloseEvent *e);

private slots:
    void propertyChange(PropertyChangeEvent* e);
    /*private*/ void editPreferences();
    /*private*/ void switchMode();
    void OnEditMenuExportRoster();
friend class PropertyChangeSupport;
friend class LocoNetSlot;
friend class AbstractThrottle;
friend class SlotManager;
friend class ThrottleCreationAction;
};

#endif // THROTTLEWINDOW_H
