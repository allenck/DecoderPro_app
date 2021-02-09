#ifndef ROSTERFRAME_H
#define ROSTERFRAME_H

#include "jmrijframe.h"
#include "loconetsystemconnectionmemo.h"
#include <QComboBox>
#include <QAction>
#include "identifyloco.h"
#include <QToolButton>
#include "powermanager.h"
#include "instancemanager.h"
#include <QLabel>
#include "roster.h"
#include "exportrosteritemaction.h"
#include "copyrosteritemaction.h"
//#include "twopanetbwindow.h"
#include "paneprogframe.h"

namespace Ui {
class RosterFrame;
}
typedef void (*NoParm)();

class ProgrammerConfigManager;
class RosterTableModel;
class RosterGroupSelector;
class RosterGroupsPanel;
class DecoderFile;
class UserPreferencesManager;
class PropertyChangeEvent;
class ConnectionConfig;
class ProgModeSelector;
class QLabel;
//class ConnectionConfig;
class RosterEntry;
class Roster;
class PaneProgFrame;
class RosterEntryUpdateListener;
class LIBPR3SHARED_EXPORT RosterFrame : public JmriJFrame
{
    Q_OBJECT

public:
    explicit RosterFrame(QWidget *parent = 0);
    RosterFrame(QString name, QWidget *parent = 0);
    RosterFrame(QString name, QString menubarFile, QString toolbarFile, QWidget *parent = 0);
    ~RosterFrame();
    RosterFrame(const RosterFrame&) : JmriJFrame() {}
    QString getTitle();
//    void propertyChange(PropertyChangeEvent*);
    //static int openWindowInstances;// = 0;
    PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
    static QList<RosterFrame*> frameInstances;// = new ArrayList<RosterFrame>();
    /*public*/ QMenuBar* getMenu();
    /*public*/ void setAllowQuit(bool allowQuit);
    void additionsToToolBar();
    /*public*/ void hideBottomPane(bool hide);
    QSignalMapper* currentMapper;
    /*public*/ void hideGroupsPane(bool hide);
    /*public*/ QString getSelectedRosterGroup();
    /*public*/ QList<RosterEntry*>* getSelectedRosterEntries();
    /*public*/ void setTitle(QString title)  override;
    /*public*/ QVariant getProperty(QString key) override;
    /*public*/ void setProgrammerLaunch(int buttonId, QString programmer, QString buttonText);
    /*public*/ void setSelectedRosterGroup(QString rosterGroup);


public slots:
    void On_ConnectionStatusPropertyChange(PropertyChangeEvent*);
    void On_InstanceManagerPropertyChange(PropertyChangeEvent*);
    void On_newLoco_clicked();
    /*public*/ Q_INVOKABLE virtual void remoteCalls(QStringList args);

private:
    Ui::RosterFrame *ui;
    void common();
    Roster* roster;
    RosterEntry* re;
    QToolButton* newLoco;
    QToolButton* identifyLoco;
    QToolButton* togglePower;
    QList<RosterEntry*> list;
    JFrame* progFrame;
    QComboBox* cbProgrammers;
    ProgModeSelector* modePanel;
    //QComboBox* cbProgMode;
    UserPreferencesManager* prefsMgr;
//    ConnectionConfig* serModeProCon;// = NULL;
//    ConnectionConfig* opsModeProCon;// = NULL;
    QLabel* programmerStatusLabel;
    QLabel* statusField;
    QLabel* serviceModeProgrammerLabel;
    QLabel* operationsModeProgrammerLabel;
    QString programmer1 =  "Comprehensive";
    QString programmer2 = "Basic";
    QVector<RosterEntry*> rows;
    QPushButton* prog2Button;

 Logger* log;
 bool inStartProgrammer;// = false;
 RosterEntryUpdateListener* rosterEntryUpdateListener = nullptr;
// void updateRow(int row, RosterEntry* re);
// void updateDetails();
 bool bUpdating;
 void updateDetails();
 ConnectionConfig* serModeProCon;// = null;
 ConnectionConfig* opsModeProCon;// = null;
// JRadioButtonMenuItem contextEdit = new JRadioButtonMenuItem(Bundle.getMessage("Edit"));
// JRadioButtonMenuItem contextOps = new JRadioButtonMenuItem(Bundle.getMessage("ProgrammingOnMain"));
// JRadioButtonMenuItem contextService = new JRadioButtonMenuItem(Bundle.getMessage("ProgrammingTrack"));
 QSignalMapper* signalMapper;
 int groupSplitPaneLocation = 0;
 RosterGroupsPanel* groups;
 QMenuBar* menuBar;// = new JMenuBar();
 void closeEvent(QCloseEvent *);
 void handleQuit(QCloseEvent* e);
 void saveWindowDetails();
 bool _hideGroups;// = false;
 bool _hideRosterImage;// = false;
 //QHash<QString, NoParm>* slotTable;
 bool checkIfEntrySelected();
 QAction* newLocoAct;
 RosterGroupSelector* rosterGroupSource;
 RosterTableModel* model;
 QSortFilterProxyModel* sorter;
 QAction* contextService;
 QAction* contextOps;
 QAction* contextEdit;
 QList<RosterEntry*>* selectedRosterEntries;
 void editMediaButton();
 QString getClassName() override;

private slots:
//    void on_tableWidget_cellClicked(int row, int col);
    void on_btnRosterMedia_clicked();
    void on_throttleLaunch_clicked();
//    void on_menuWindow_aboutToShow();
    void on_prog1Button_clicked();
    void on_actionHide_Show_Summary_Panel_triggered();
    void on_actionHide_Show_Roster_Image_triggered();
    void On_actionPreferences_triggered();
    void on_actionProgramming_Track_triggered();
    void on_actionProgramming_On_Main_triggered();
    void on_actionEdit_Only_triggered();
    void on_actionLabels_and_Media_triggered();
    void on_actionNew_Throttle_triggered();
    void on_togglePower_clicked();
    void on_actionDelete_Loco_triggered();
//    void on_tableWidget_cellChanged(int, int);
    void propertyChange(PropertyChangeEvent* e);
//    void On_cbProgrammers_currentIndexChanged(QString);
    void updateProgMode();
    void On_splitterMoved(int, int);
    void On_splitter2Moved(int, int);
    void On_Quit();
    void on_currentMapped(QAction*);
    void on_currentMapped(QObject*);
    void on_groupChange(PropertyChangeEvent*);
    void on_RosterChange(PropertyChangeEvent*);
    void on_tableClicked(QModelIndex);
    void actionPerformed(QObject*); // handles actions in popup menu;


protected:
    /*protected*/ bool _allowQuit;// = true;
    /*protected*/ void firePropertyChange(QString prefsMgr, QVariant old, QVariant n);
    /*protected*/ QVector<RosterEntry*> selectRosterEntry(QString rosterGroup);
    /*protected*/ void buildGUI(QString menubarFile, QString toolbarFile);
    /*protected*/ void addMainMenuBar(QString menuFile);
    /*protected*/ void addMainToolBar(QString toolBarFile);
    /*protected*/ void allowQuit(bool quitAllowed);
    /*protected*/ void addMainStatusBar(); // from TwoPaneTbWindow
    /*protected*/ JmriAbstractAction* getNewWindowAction();
    /*protected*/ JmriAbstractAction* newWindowAction;
    /*protected*/ bool _hideBottomPane;// = false;
    /*protected*/ void enableRosterGroupMenuItems(bool enable);
    /*protected*/ void helpMenu(QMenuBar* menuBar, /*final*/ JFrame* frame);
    /*protected*/ void deleteLoco();
    /*protected*/ QString baseTitle;// = "Roster";

protected slots:
    /*protected*/ void startIdentifyLoco();
    /*protected*/ void selectLoco(int dccAddress, bool isLong, int mfgId, int modelId);
    /*protected*/ void updateProgrammerStatus(/*@Nullable*/ PropertyChangeEvent* evt);
    /*protected*/ void setNewWindowAction(JmriAbstractAction* newWindowAction);
    /*protected*/ void systemsMenu();
    /*protected*/ void printLoco(bool boo);
    /*protected*/ void exportLoco();
    /*protected*/ void copyLoco();
    /*protected*/ void startProgrammer(DecoderFile* decoderFile, RosterEntry* re, QString filename);
    /*protected*/ void newWindow();
    /*protected*/ void newWindow(JmriAbstractAction* action);
    /*protected*/ void hideSummary();
    /*protected*/ void hideGroups();
    /*protected*/ void hideRosterImage();
    virtual /*protected*/ /*final*/ void buildWindow();
    /*protected*/ void showPopup(QPoint pos);
    /*protected*/ ProgrammerConfigManager* getProgrammerConfigManager();


 friend class PwrListener;
 friend class MyIdentifyLoco;
 friend class RosterEntryUpdateListener;
 friend class PropertyChangeSupport;
 friend class DefaultFilePropertyChangeListener;
};

class  PwrListener : public PropertyChangeListener
{
 Q_OBJECT
public:
 PwrListener(RosterFrame* parent)
 {
  this->parent = parent;

 }
 void propertyChange(PropertyChangeEvent *e)
 {
  if(e->getPropertyName() == "Power")
  {
   PowerManager* pmgr = (PowerManager*)InstanceManager::getDefault("PowerManager");
   if(pmgr->getPower()== PowerManager::ON)
   {
    //parent->togglePower = new QToolButton();
    parent->togglePower->setIcon(QIcon(":/resources/icons/throttles/power_green.png") );
    parent->togglePower->setText(tr("Power on"));
   }
   else if (pmgr->getPower()== PowerManager::OFF)
   {
    //parent->togglePower = new QToolButton( );
    parent->togglePower->setIcon(QIcon(":/resources/icons/throttles/power_red.png"));
    parent->togglePower->setText(tr("Power off"));
   }
   else
   {
    //parent->togglePower = new QToolButton( );
    parent->togglePower->setIcon(QIcon(":/resources/icons/throttles/power_yellow.png"));
    parent->togglePower->setText(tr("Power unknown"));
   }
  }
 }
 private:
  RosterFrame* parent;
  friend class RosterFrame;
};
Q_DECLARE_METATYPE(RosterFrame)

class MyIdentifyLoco : public IdentifyLoco
{
    Q_OBJECT
 Programmer* programmer;
 public:
    MyIdentifyLoco(Programmer* programmer, RosterFrame* me) : IdentifyLoco(programmer)
    {
     who = me;
     this->programmer = programmer;
    }
    QObject* self() {return (QObject*)this;}
 signals:
  void doneSignal(int dccAddress, bool bLongAddr, int cv8Val, int cv7Val);

private:
 RosterFrame* who;// = me;

    //@Override
protected:
 void done(int dccAddress) override
 {
  // if Done, updated the selected decoder
   //who->selectLoco(dccAddress, !shortAddr, cv8val, cv7val);
  emit doneSignal(dccAddress, !shortAddr, cv8val, cv7val);
 }

 //@Override
 protected: void message(QString m) override
 {
  who->statusField->setText(m);
 }

    //@Override
    protected: void error() {
        // raise the button again
        //idloco.setSelected(false);
    }
};
#if 1
class RosterEntryUpdateListener : public PropertyChangeListener
{
 Q_OBJECT
 public:
    RosterEntryUpdateListener(RosterFrame* f);
public slots:
    void propertyChange(PropertyChangeEvent *);

private:
    RosterFrame* f;
protected:
};
#endif
/*static*/ class ExportRosterItem : public ExportRosterItemAction
{
    /**
     *
     */
    //private static final long serialVersionUID = 5920288372458701120L;
public:
    ExportRosterItem(QString pName, QWidget* pWho, RosterEntry* re)
     : ExportRosterItemAction(pName, pWho)
    {
        //super(pName, pWho);
        setExistingEntry(re);
    }
protected:
    //@Override
    /*protected*/ bool selectFrom() {
        return true;
    }
};

/*static*/ class CopyRosterItem : public  CopyRosterItemAction {

    /**
     *
     */
    //private static final long serialVersionUID = -4822095767152284104L;
public:
    CopyRosterItem(QString pName, QWidget* pWho, RosterEntry* re)
     : CopyRosterItemAction(pName, pWho)
    {
        //super(pName, pWho);
        setExistingEntry(re);
    }

    //@Override
    /*protected*/ bool selectFrom() {
        return true;
    }
};

class DefaultFilePropertyChangeListener : public PropertyChangeListener
{
 Q_OBJECT
 RosterFrame* frame;
public:
 DefaultFilePropertyChangeListener(RosterFrame* frame) {this->frame = frame;}
public slots:
 void propertyChange(PropertyChangeEvent* evt);
};

class PaneProgFrameO1 : public PaneProgFrame
{
 Q_OBJECT
public:
 PaneProgFrameO1(DecoderFile* pDecoderFile, RosterEntry* pRosterEntry, QString frameTitle, QString programmerFile, Programmer* pProg, bool opsMode, QWidget* parent=nullptr)
  : PaneProgFrame(pDecoderFile, pRosterEntry, frameTitle, programmerFile, pProg, opsMode, parent){}
 /*public*/ QString getClassName() {return "PaneProgFrameO1";}

protected:
 JPanel* getModePane()
 {
  return nullptr;
 }
};
#endif // ROSTERFRAME_H
