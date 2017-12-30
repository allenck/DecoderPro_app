#ifndef ADDSIGNALMASTPANEL_H
#define ADDSIGNALMASTPANEL_H

#include <QWidget>
#include <QComboBox>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QFileInfo>
#include "logger.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include "libPr3_global.h"


class JTextField;
class NamedBean;
class SignalMast;
class JmriBeanComboBox;
//class TurnoutAspectPanel;
class Turnout;
class BeanSelectCreatePanel;
class DecimalFormat;
class ActionEvent;
class UserPreferencesManager;
class LIBPR3SHARED_EXPORT TurnoutAspectPanel : public QObject
{
    Q_OBJECT

public:
    TurnoutAspectPanel(QString aspect);
    TurnoutAspectPanel(QString turnoutName, int state);
    void setReference(QString reference);
    int getTurnoutState();
    void setSelectedTurnout(QString name);
    void setTurnoutState(int state);
    bool isAspectDisabled();
    QString getTurnoutName();
    NamedBean* getTurnout();
    QWidget* getPanel();
public slots:
    void setAspectDisabled(bool boo);

private:
    void init();
    BeanSelectCreatePanel* beanBox;// = new BeanSelectCreatePanel(InstanceManager.turnoutManagerInstance(), NULL);
    QCheckBox* disabledCheck;// = new JCheckBox("Disable Aspect");

    QString stateThrown;// = InstanceManager::turnoutManagerInstance().getThrownText();
    QString stateClosed;// = InstanceManager::turnoutManagerInstance().getClosedText();
    QStringList turnoutStates;// = QStringList() << stateClosed << stateThrown;
    QList<int> turnoutStateValues;// =  QList<int>() << Turnout::CLOSED<< Turnout::THROWN;

    QComboBox* turnoutState;// = new JComboBox(turnoutStates);
    QLabel* turnoutStateLabel;// = new JLabel("Set State");
    QString aspect;// = "";
    QWidget* panel;
    Logger* log;
};
/*static*/ class DCCAspectPanel : public QObject
{
 Q_OBJECT
    QString aspect;// = "";
    QCheckBox* disabledCheck;// = new QCheckBox("Disable Aspect");
    QLabel* aspectLabel;// = new QLabel("Set Aspect Id");
    JTextField* aspectId;// = new JTextField(5);
    QWidget* panel;
    Logger* log;
public:
    DCCAspectPanel(QString aspect);
    //void setAspectDisabled(bool boo);
    bool isAspectDisabled();
    void setAspectId(int i);
    QWidget* getPanel();
    int getAspectId();

public slots:
    void setAspectDisabled(bool);

};

class LIBPR3SHARED_EXPORT AddSignalMastPanel : public QWidget
{
    Q_OBJECT
public:
    explicit AddSignalMastPanel(QWidget* parent = 0);
    /*public*/ AddSignalMastPanel(SignalMast* mast, QWidget *parent = 0);
    static bool validateAspectId(QString strAspect);

signals:

public slots:
private:
    UserPreferencesManager* prefs;// = ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
    QString systemSelectionCombo;// = this.getClass().getName()+".SignallingSystemSelected";
    QString mastSelectionCombo;// = this.getClass().getName()+".SignallingMastSelected";
    QString driverSelectionCombo;// = this.getClass().getName()+".SignallingDriverSelected";
    QList<NamedBean*>* alreadyUsed;// = new ArrayList<NamedBean>();

    QComboBox* signalMastDriver;

    QGroupBox* signalHeadPanel;// = new QWidget();
    QWidget* turnoutMastPanel;// = new QWidget();
    QScrollArea* turnoutMastScroll;
    QScrollArea* dccMastScroll;
    QWidget* dcTurnoutAspectPanelcMastPanel;// = new QWidget();
    QLabel* systemPrefixBoxLabel;// = new JLabel(tr("System") + ":");
    QComboBox* systemPrefixBox;// = new JComboBox();
    QLabel* dccAspectAddressLabel;// = new QLabel(tr("DCC Accessory Address"));
    JTextField* dccAspectAddressField;// = new JTextField(5);

    QPushButton* cancel;// = new QPushButton(tr("Cancel"));

    SignalMast* mast;// = null;

    JTextField* userName;// = new JTextField(20);
    QComboBox* sigSysBox;// = new QComboBox();
    QComboBox* mastBox;// = new QComboBox(new QString[]{tr("MastEmpty")});
    QCheckBox* includeUsed;// = new QCheckBox(tr("IncludeUsedHeads"));
    QCheckBox* resetPreviousState;// = new QCheckBox(tr("ResetPrevious"));

    QString sigsysname;
    QList<QFileInfo>* mastNames;// = new QList<QFile*>();

    QMap<QString, QCheckBox*>* disabledAspects;// = new QMap<QString, QCheckBox>(10);
    QGroupBox* disabledAspectsPanel;// = new QWidget();
    QGridLayout* disabledAspectsPanelLayout;
    bool inEditMode;// = false;TurnoutAspectPanel::
    QMap<QString, int>* map;// = new QMap<QString, int>();
    void loadMastDefinitions();
    Logger* log;
    void updateHeads();
    QList<JmriBeanComboBox*>* headList;// = new QList<JmriBeanComboBox>(5);

    QMap<QString, TurnoutAspectPanel*>* turnoutAspect;// = new MapMap<QString, TurnoutAspectPanel*>(10);
    class BeanSelectCreatePanel;
    void handleCreateException(QString sysName);
    void updateTurnoutAspectPanel();
    QMap<QString, DCCAspectPanel*>* dccAspect;// = new QMap<QString, DCCAspectPanel*>(10);
    void init();
    void updateDisabledOption();
//        FocusListener dccAddressListener = NULL;
    QWidget* dccMastPanel;
    QString extractMastTypeFromMast(QString name);
    void updateDCCMastPanel();
    bool validateDCCAddress();
    QComboBox* copyFromMastSelection();
    void copyFromAnotherDCCMastAspect(QString strMast);
    QComboBox* mastSelect;
    DecimalFormat* paddedNumber;// = new DecimalFormat("0000");
    bool checkUserName(QString nam);
    bool checkSystemName(QString nam);
    bool checkSignalHeadUse();
    bool duplicateHeadAssigned(QString head);
    bool headAssignedElseWhere(QString head, QString mast);
protected slots:
    /*protected*/ void updateSelectedDriver();
    void on_mastSelect_CurrentIndexChanged(int);
    void refreshHeadComboBox();
    void okPressed(ActionEvent* e = 0);
    void sigSysBox_currentIndexChanged(int);

    friend class AddSignalMastJFrame;
};
#endif // ADDSIGNALMASTPANEL_H
