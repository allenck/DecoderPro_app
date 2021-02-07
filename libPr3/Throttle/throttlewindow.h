#ifndef THROTTLEWINDOW_H
#define THROTTLEWINDOW_H

#include "../LayoutEditor/jmrijframe.h"
#include "loconetthrottle.h"
#include <QPushButton>
#include "abstractthrottlemanager.h"
#include "libPr3_global.h"
#include "speedpanel.h"
#include "addresslistener.h"

namespace Ui {
class ThrottleWindow;
}
class FunctionPanel;
class ControlPanel;
class AddressPanel;
class PowerManager;
class ThrottleManager;
class ListThrottles;
class RosterEntry;
class LIBPR3SHARED_EXPORT ThrottleWindow : public JmriJFrame, public AddressListener
{
    Q_OBJECT
    Q_INTERFACES(AddressListener)
public:
    explicit ThrottleWindow(/*LocoNetSystemConnectionMemo* memo = 0,*/ QWidget *parent = 0);
    ~ThrottleWindow();
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
    /*public*/ void dispose() override;
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
    /*public*/ QDomElement getXml();
    /*public*/ QDomElement getXml(ThrottleWindow*);
    /*public*/ QDomElement getXmlFile();
    /*public*/ void setXml(QDomElement e);
    /*public*/ static QString getDefaultThrottleFolder();
    /*public*/ static QString getDefaultThrottleFilename();
    /*public*/ void setLastUsedSaveFile(QString lusf);
    /*public*/ static void setTransparentBackground(QObject* jcomp);
    /*public*/ static void setTransparentBackground(QObjectList comps);
    /*public*/ static void setTransparent(QWidget* jcomp);
    /*public*/ static void setTransparent(QObject* jcomp, bool transparency);
    QObject* self() {return (QObject*)this;}
    QString getClassName() override;
    /*public*/ void saveRosterChanges();
    /*public*/ void setEditMode(bool mode);
    /*public*/ bool getEditMode();

public slots:
    /*public*/ void saveThrottle();
    /*public*/ void saveThrottleAs();
    void notifyAddressThrottleFound(DccThrottle*t) override;
    /*public*/ virtual void notifyAddressReleased(LocoAddress* la) override;
    void notifyThrottleFound(DccThrottle* t);
    /*public*/ virtual void notifyAddressChosen(LocoAddress* l) override;


signals:
    void throttleWindowupdate(PropertyChangeEvent*);
    void propertyChange(QString, QObject*, QObject*);

private slots:

//    void on_newThrottle_clicked();
//    void on_removeThrottle_clicked();

    void on_emergencyStop_clicked();
    //void on_togglePower_clicked();
    void on_actionNew_Throttle_triggered();
    void on_actionPower_On_triggered();
    void on_actionPower_Off_triggered();
    void on_listView_clicked();
    //void on_menuWindow_aboutToShow();
    void on_actionAddress_Panel_toggled(bool bChecked);
    void on_actionControl_Panel_toggled(bool bChecked);
    void on_actionFunction_Panel_toggled(bool bChecked);
    void notifyChangedSlot(LocoNetSlot*);
    void removeThrottleFrame();
    void OnFileMenuLoad();
    void on_address_released(LocoAddress*);
    void on_actionSpeed_Panel_toggled(bool);

    private:
    Ui::ThrottleWindow *ui;
    AddressPanel* addressPanel;
    ControlPanel* controlPanel;
    FunctionPanel* functionPanel;
    SpeedPanel* speedPanel;
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
    QAction* viewSpeedPanel;
    QAction* viewAllButtons;
    QAction* editMenuExportRoster;

    ThrottleManager* mgr;
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
    PowerManager* powerMgr;
    QString titleTextType;
    QString titleText;
    /*private*/ void saveThrottle(QString sfile);
    /*private*/ QMap<QString, ThrottleWindow*>* throttleFrames;// = new QMap<QString, ThrottleWindow*>(/*5*/);
    /*private*/ int cardCounterID;// = 0; // to generate unique names for each card
    /*private*/ int cardCounterNB;// = 1; // real counter
//    /*private*/ CardLayout throttlesLayout;
    /*private*/ bool isEditMode;// = true;
    /*private*/ bool willSwitch;// = false;
    ThrottleWindow* currentThrottleFrame;
    QString lastUsedSaveFile;
    void windowClosing(QCloseEvent *e);
    /*private*/ static QString DefaultThrottleFileName;// = "JMRI_ThrottlePreference.xml";
    QDomDocument doc;
    /*private*/ static void setTransparent(QObjectList comps, bool transparency);
    //BackgroundPanel* backgroundPanel;
    /*private*/ /*final*/ int BACKPANEL_LAYER;// = Integer.MIN_VALUE;
    enum frames
    {
     ADDRESS_PANEL_INDEX = 0,
     CONTROL_PANEL_INDEX = 1,
     FUNCTION_PANEL_INDEX = 2,
     SPEED_DISPLAY_INDEX = 3,
     NUM_FRAMES = 4
    };
    /*private*/ QToolBar* throttleToolBar;

private slots:
    void propertyChange(PropertyChangeEvent* e);
    /*private*/ void editPreferences();
    QT_DEPRECATED/*private*/ void switchMode();

friend class PropertyChangeSupport;
friend class LocoNetSlot;
friend class AbstractThrottle;
friend class SlotManager;
friend class ThrottleCreationAction;
friend class ThrottleOperator;
};

#endif // THROTTLEWINDOW_H
