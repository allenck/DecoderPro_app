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
#include <QStackedWidget>

class RuntimeException;
class File;
class QFormLayout;
class SignalMastAddPane;
class JTextField;
class NamedBean;
class SignalMast;
class JmriBeanComboBox;
//class TurnoutAspectPanel;
class Turnout;
class BeanSelectCreatePanel;
class DecimalFormat;
class JActionEvent;
class UserPreferencesManager;
class LIBPR3SHARED_EXPORT AddSignalMastPanel : public QWidget
{
    Q_OBJECT
public:
    explicit AddSignalMastPanel(QWidget* parent = 0);
    /*public*/ AddSignalMastPanel(SignalMast* mast, QWidget *parent = 0);
 /*public*/ void refresh();

signals:

public slots:
    void selection(QString);
    void cancelPressed();

private:
    UserPreferencesManager* prefs;// = ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
    QString systemSelectionCombo;// = this.getClass().getName()+".SignallingSystemSelected";
    QString mastSelectionCombo;// = this.getClass().getName()+".SignallingMastSelected";
    QString driverSelectionCombo;// = this.getClass().getName()+".SignallingDriverSelected";
    QList<NamedBean*>* alreadyUsed;// = new ArrayList<NamedBean>();

    QComboBox* signalMastDriver;
    QList<SignalMastAddPane*> panes;// = new ArrayList<>();

    // center pane, which holds the specific display
    QStackedWidget* centerPanel;// = new JPanel();
    //QFormLayout* cl;// = new CardLayout();
    SignalMastAddPane* currentPane;

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
    QPushButton* apply;// = new JButton(Bundle.getMessage("ButtonApply")); // NOI18N
    QPushButton* create;// = new JButton(Bundle.getMessage("ButtonCreate")); // NOI18N

    SignalMast* mast;// = null;

    JTextField* userName;// = new JTextField(20);
    QComboBox* sigSysBox;// = new QComboBox();
    QComboBox* mastBox;// = new QComboBox(new QString[]{tr("MastEmpty")});
    bool mastBoxPassive = false; // if true, mastBox doesn't process updates

    QCheckBox* includeUsed;// = new QCheckBox(tr("IncludeUsedHeads"));
    QCheckBox* resetPreviousState;// = new QCheckBox(tr("ResetPrevious"));

    // signal system definition variables
    QString sigsysname;
    QList<File*> mastFiles;// = new ArrayList<>(); // signal system definition files
    QMap<QString, int> mapNameToShowSize;// = new LinkedHashMap<>();
    QMap<QString, QString> mapTypeToName;// = new LinkedHashMap<>();
//    QList<QFileInfo>* mastNames;// = new QList<QFile*>();

    QMap<QString, QCheckBox*>* disabledAspects;// = new QMap<QString, QCheckBox>(10);
    QGroupBox* disabledAspectsPanel;// = new QWidget();
    QGridLayout* disabledAspectsPanelLayout;
    bool inEditMode;// = false;TurnoutAspectPanel::
    QMap<QString, int> map;// = new QMap<QString, int>();
    QLabel* centerPanelLabel;

    void loadMastDefinitions();
    static Logger* log;
    void init();

    QWidget* dccMastPanel;
    QComboBox* mastSelect;
    DecimalFormat* paddedNumber;// = new DecimalFormat("0000");
    bool checkUserName(QString nam);
    void issueWarningUserName(QString nam);
    void issueWarningUserNameAsSystem(QString nam);
    int issueNoUserNameGiven();
    void issueDialogFailMessage(RuntimeException ex);
    void clearPanel();

protected:


protected slots:
    /*protected*/ void updateSelectedDriver();
//    void on_mastSAcelect_CurrentIndexChanged(int);
    void okPressed();
    void sigSysBox_currentIndexChanged(int);
    void onSignalMastDriverSelected();
friend class AddSignalMastJFrame;
};
#endif // ADDSIGNALMASTPANEL_H
