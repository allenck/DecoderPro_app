#ifndef SIGNALGROUPSUBTABLEACTION_H
#define SIGNALGROUPSUBTABLEACTION_H

#include <QObject>
#include "logger.h"
#include "abstracttablemodel.h"
#include "abstracttableaction.h"

class PropertyChangeEvent;
class JActionEvent;
class QTableView;
class Turnout;
class Sensor;
class SignalHead;
class QPushButton;
class QRadioButton;
class QButtonGroup;
class SignalGroupSensorModel;
class SignalGroupTurnoutModel;
class JmriJFrame;
class QLabel;
class QComboBox;
class SignalGroup;
class SignalGroupSubTableAction : public QObject
{
    Q_OBJECT
public:
    //explicit SignalGroupSubTableAction(QObject *parent = 0);
/*public*/ SignalGroupSubTableAction(QString s = tr("SignalGroup Head Edit Table"), QObject* parent = 0);
    ~SignalGroupSubTableAction() {}
    SignalGroupSubTableAction(const SignalGroupSubTableAction& that) : QObject(that.parent()) {}
    QString helpTarget();

    void editSignal(SignalGroup* g, QString signal);
    void setColumnToHoldButton(QTableView* table, int column, QPushButton* sample);
    void initializeIncludedList();
    int setTurnoutInformation(SignalGroup* g);
    int setSensorInformation(SignalGroup* g);
    void updateSubPressed(JActionEvent* e, bool newSignalGroup );
signals:

public slots:

private:
    /*private*/ static QVector<QString> oper;// = new String[]{"AND", "OR"};
    /*private*/ static QVector<int> operValues;// = new int[]{0x00, 0x01};
    void setoperBox(bool mode, QComboBox* box);
    bool operFromBox(QComboBox* box);
    Logger* log;
    int sensorModeFromBox(QComboBox* box) ;
    void setSensorModeBox(int mode, QComboBox* box);
    int signalStateFromBox(QComboBox* box) ;
    void setSignalStateBox(int mode, QComboBox* box);
    int turnoutModeFromBox(QComboBox* box);
    void setTurnoutModeBox(int mode, QComboBox* box);
    void finishUpdate();
    void cancelEdit();
    void cancelIncludedOnly();

    /*private*/ bool showAll;// = true;   // false indicates show only included Turnouts

    /*private*/ static int ROW_HEIGHT;

    /*private*/ static QStringList COLUMN_NAMES;// = {rbx.getString("ColumnLabelSystemName"),
//                                            rbx.getString("ColumnLabelUserName"),
//                                            rbx.getString("ColumnLabelInclude"),
//                                            rbx.getString("ColumnLabelSetState")};
    /*private*/ static QString SET_TO_ACTIVE;// = rbx.getString("SensorActive");
    /*private*/ static QString SET_TO_INACTIVE;// = rbx.getString("SensorInactive");
    /*private*/ static QString SET_TO_CLOSED;// = InstanceManager.turnoutManagerInstance().getClosedText();
    /*private*/ static QString SET_TO_THROWN;// = InstanceManager.turnoutManagerInstance().getThrownText();

    /*private*/ static QVector<QString> sensorInputModes;// = new String[]{"Active", "Inactive"};
    /*private*/ static QVector<int> sensorInputModeValues;// = new int[]{SignalGroup.ONACTIVE, SignalGroup.ONINACTIVE};

    /*private*/ static QVector<QString> signalStates;// = new String[]{rbx.getString("StateSignalHeadDark"), rbx.getString("StateSignalHeadRed"), rbx.getString("StateSignalHeadYellow"), rbx.getString("StateSignalHeadGreen"), rbx.getString("StateSignalHeadLunar")};
    /*private*/ static QVector<int> signalStatesValues;// = new int[]{SignalHead.DARK, SignalHead.RED, SignalHead.YELLOW, SignalHead.GREEN, SignalHead.LUNAR};

    QLabel* _systemName;
    QComboBox* _OnAppearance;
    QComboBox* _OffAppearance;
    QComboBox* _SensorTurnoutOper;// = new QComboBox(oper);

    JmriJFrame* addFrame;// = NULL;
    SignalGroupTurnoutModel* _signalGroupTurnoutModel;
    //JScrollPane _SignalGroupTurnoutScrollPane;
    SignalGroupSensorModel* _signalGroupSensorModel;
    //JScrollPane _SignalGroupSensorScrollPane;

    QButtonGroup* selGroup;// = NULL;
    QRadioButton* allButton;// = NULL;
    QRadioButton* includedButton;// = NULL;

    QLabel* nameLabel;// = new QLabel("Signal Head:");
    QLabel* signalOnStateLabel;// = new QLabel("State when conditions are met");
    QLabel* signalOffStateLabel;// = new QLabel("State when conditions are not met");
    QLabel* userLabel;// = new QLabel("Select the conditions that must be met to set this Signal Head on");

    QPushButton* updateSubButton;// = new QPushButton("Done");

    static QString updateInst;// = "To change this SignalGroup, make changes above, then click 'Done'.";

    QLabel* status1;// = new QLabel(updateInst);

    QWidget* p2xt;// = NULL;   // Turnout list table
    QWidget* p2xs;// = NULL;   // Sensor list table

    SignalGroup* curSignalGroup;// = NULL;
    QString curSignal;
    SignalHead* curSignalHead;
    /*private*/ static QVector<QString>  turnoutInputModes;// = QStringList() << ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText() << ((ProxyTurnoutManager*) InstanceManager::turnoutManagerInstance())->getThrownText() ;
    /*private*/ static QVector<int> turnoutInputModeValues;// = QList<int>() << SignalGroup::ONCLOSED << SignalGroup::ONTHROWN ;

    /*private*/ /*abstract*/ class SignalGroupElement : public QObject
    {
        QString _sysName;
        QString _userName;
        bool _included;
        int _setToState;
       public:
        SignalGroupElement(QString sysName, QString userName);
        QString getSysName();
        QString getUserName();
        bool isIncluded();
        void setIncluded(bool include);
        /*abstract*/ QString getSetToState();
        /*abstract*/ void setSetToState(QString state);

        int getState();
        void setState(int state);
        friend class SignalGroupSensor;
        friend class SignalGroupSubTableAction;
    };

    /*private*/ class SignalGroupSensor : public SignalGroupElement {
        SignalGroupSensor (QString sysName, QString userName);
        QString getSetToState();
        void setSetToState(QString state);
        Sensor* getSensor();
        friend class SignalGroupSubTableAction;
        friend class SignalGroupSensorModel;
    };

    /*private*/ class SignalGroupTurnout : public SignalGroupElement
    {
        SignalGroupTurnout(QString sysName, QString userName);
        QString getSetToState();
        void setSetToState(QString state);
        Turnout* getTurnout();
        friend class SignalGroupSubTableAction;
        friend class SignalGroupTurnoutModel;
    };
    /*private*/ QList <SignalGroupTurnout*> _turnoutList;      // array of all Turnouts
    /*private*/ QList <SignalGroupTurnout*> _includedTurnoutList;

    /*private*/ QList <SignalGroupSensor*> _sensorList;        // array of all Sensorsy
    /*private*/ QList <SignalGroupSensor*> _includedSensorList;
private slots:
    void On_AllButton_clicked();
    void On_includedButton_clicked();
    void On_updateSubButton_clicked();

    friend class SignalGroupSensorModel;
    friend class SignalGroupTurnoutModel;
    friend class SGSTASignalGroupOutputModel;
};
/*public*/ /*abstract*/ class SGSTASignalGroupOutputModel : public AbstractTableModel //implements PropertyChangeListener
{
    Q_OBJECT
    SignalGroupSubTableAction* act;
public:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ void dispose();
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ int columnCount(const QModelIndex &parent) const;

    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    enum COLUMNS
    {
     SNAME_COLUMN = 0,
     UNAME_COLUMN = 1,
     INCLUDE_COLUMN = 2,
     STATE_COLUMN = 3
    };

    /*public*/ QVariant data(const QModelIndex &index, int role) const;

};
/**
 * Table model for selecting Turnouts and Turnout State
 */
class SignalGroupTurnoutModel : public SGSTASignalGroupOutputModel
{
    Q_OBJECT
    SignalGroupSubTableAction* act;
public:
    SignalGroupTurnoutModel(SignalGroupSubTableAction* act) ;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
};

/**
 * Set up table for selecting Sensors and Sensor State
 */
class SignalGroupSensorModel : public SGSTASignalGroupOutputModel
{
    Q_OBJECT
    SignalGroupSubTableAction* act;
public:
    SignalGroupSensorModel(SignalGroupSubTableAction* act);
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
};

#endif // SIGNALGROUPSUBTABLEACTION_H
