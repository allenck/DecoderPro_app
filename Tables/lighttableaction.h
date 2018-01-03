#ifndef LIGHTTABLEACTION_H
#define LIGHTTABLEACTION_H
#include "abstracttablemodel.h"
#include "abstracttableaction.h"
#include "beantabledatamodel.h"
#include "windowlistener.h"

class QGroupBox;
class LightControlTableModel;
class LightControl;
class QLabel;
class QComboBox;
class QCheckBox;
class JTextField;
class Light;
class DecimalFormat;
class LightManager;
class PropertyChangeEvent;
class LightTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    LightTableAction(QObject* parent =0);
    /*public*/ LightTableAction(QString s, QObject* parent);
    ~LightTableAction() {}
    LightTableAction(const LightTableAction&) : AbstractTableAction() {}
    /*public*/ void setManager(Manager* man);
    /*public*/ QString getClassDescription();
    /*public*/ QString getControlTypeText(int type);
    /*public*/ QString getDescriptionText(LightControl* lc, int type);

private:
    void common();
    QString     gbStyleSheet;
    DecimalFormat* oneDigit;// = new DecimalFormat("0");
    DecimalFormat* oneDotTwoDigit;// = new DecimalFormat("0.00");
    JmriJFrame* addFrame;// = NULL;
    Light* curLight;// = NULL;
    bool lightCreatedOrUpdated;// = false;
    bool noWarn;// = false;
    bool inEditMode;// = false;
    /*private*/ bool lightControlChanged;// = false;

    // items of add frame
    QLabel* systemLabel;// = new JLabel(tr("LightSystem"));
    QComboBox* prefixBox;// = new JComboBox<String>();
    QCheckBox* addRangeBox;// = new JCheckBox(tr("AddRangeBox"));
    JTextField* fieldHardwareAddress;// = new JTextField(10);
    JTextField* fieldNumToAdd;// = new JTextField(5);
    QLabel* labelNumToAdd;// = new JLabel("   " + tr("LabelNumberToAdd"));
    QString systemSelectionCombo;// = this.getClass().getName() + ".SystemSelected";
    QWidget* panel1a;// = NULL;
    QGroupBox* varPanel;// = NULL;
    QLabel* systemNameLabel;// = new JLabel(tr("LabelSystemName") + " ");
    QLabel* fixedSystemName;// = new JLabel("xxxxxxxxxxx");
    JTextField* userName;// = new JTextField(10);
    QLabel* userNameLabel;// = new JLabel(tr("LabelUserName") + " ");
    LightControlTableModel* lightControlTableModel;// = NULL;
    QPushButton* create;
    QPushButton* update;
    QPushButton* cancel;
    QPushButton* addControl;

    QList<LightControl*>* controlList;// = new ArrayList<LightControl>();
    QString sensorControl;// = tr("LightSensorControl");
    QString fastClockControl;// = tr("LightFastClockControl");
    QString turnoutStatusControl;// = tr("LightTurnoutStatusControl");
    QString timedOnControl;// = tr("LightTimedOnControl");
    QString twoSensorControl;// = tr("LightTwoSensorControl");
    QString noControl;// = tr("LightNoControl");

    QLabel* status1;// = new JLabel(tr("LightCreateInst"));
    QLabel* status2;// = new JLabel("");

    // parts for supporting variable intensity, transition
    QLabel* labelMinIntensity;// = new JLabel(tr("LightMinIntensity") + "  ");
    JTextField* fieldMinIntensity;// = new JTextField(3);
    QLabel* labelMinIntensityTail;// = new JLabel(" %   ");
    QLabel* labelMaxIntensity;// = new JLabel(tr("LightMaxIntensity") + "  ");
    JTextField* fieldMaxIntensity;// = new JTextField(3);
    QLabel* labelMaxIntensityTail;// = new JLabel(" %   ");
    QLabel* labelTransitionTime;// = new JLabel(tr("LightTransitionTime") + "  ");
    JTextField* fieldTransitionTime;// = new JTextField(5);
    /*private*/ void initializePrefixCombo();
    /*private*/ bool canAddRange();
    void setupVariableDisplay(bool showIntensity, bool showTransition);
    bool supportsVariableLights();
    Logger * log;
    /*private*/ void setLightControlInformation(Light* g);
    /*private*/ void clearLightControls();
    QString formatTime(int hour, int minute);
    /*private*/ QString getControlSensorSenseText(LightControl* lc);
    /*private*/ QString getControlTurnoutStateText(LightControl* lc);

    // items for add/edit Light Control window
    /*private*/ JmriJFrame* addControlFrame;// = NULL;
    /*private*/ QComboBox* typeBox;
    /*private*/ QLabel* typeBoxLabel;// = new JLabel(tr("LightControlType"));
    /*private*/ int sensorControlIndex;
    /*private*/ int fastClockControlIndex;
    /*private*/ int turnoutStatusControlIndex;
    /*private*/ int timedOnControlIndex;
    /*private*/ int twoSensorControlIndex;
    /*private*/ int noControlIndex;
    /*private*/ int defaultControlIndex;// = 0;
    /*private*/ bool inEditControlMode;// = false;
    /*private*/ LightControl* lc;// = NULL;
    /*private*/ JTextField* field1a;// = new JTextField(10);  // Sensor
    /*private*/ JTextField* field1a2;// = new JTextField(10);  // Sensor 2
    /*private*/ JTextField* field1b;// = new JTextField(8);  // Fast Clock
    /*private*/ JTextField* field1c;// = new JTextField(10);  // Turnout
    /*private*/ JTextField* field1d;// = new JTextField(10);  // Timed ON
    /*private*/ QLabel* f1Label;// = new JLabel(tr("LightSensor"));
    /*private*/ JTextField* field2a;// = new JTextField(8);  // Fast Clock
    /*private*/ JTextField* field2b;// = new JTextField(8); // Timed ON
    /*private*/ QLabel* f2Label;// = new JLabel(tr("LightSensorSense"));
    /*private*/ QComboBox* stateBox;
    /*private*/ int sensorActiveIndex;
    /*private*/ int sensorInactiveIndex;
    /*private*/ int turnoutClosedIndex;
    /*private*/ int turnoutThrownIndex;
    /*private*/ QPushButton* createControl;
    /*private*/ QPushButton* updateControl;
    /*private*/ QPushButton* cancelControl;
    /*private*/ void addEditControlWindow();
    void setUpControlType(QString ctype);
    /*private*/ bool setControlInformation(LightControl* g);

private slots:
    void createPressed(ActionEvent* e = 0);
    void editPressed();
    void updatePressed(ActionEvent* e = 0);
    void cancelPressed(ActionEvent* e = 0);
    void controlTypeChanged();

protected:
    /*protected*/ LightManager* lightManager;// = InstanceManager.lightManagerInstance();
    /*protected*/ void createModel();
    /*protected*/ void setTitle();
    /*protected*/ QString helpTarget();
    ///*protected*/ BeanTableDataModel* m;
    /*protected*/ QString getClassName();

protected slots:
    /*protected*/ void addPressed(ActionEvent* e = 0);
    /*protected*/ void editControlAction(int row);
    /*protected*/ void deleteControlAction(int row);
    /*protected*/ void createControlPressed(ActionEvent* e = 0);
    /*protected*/ void updateControlPressed(ActionEvent* e = 0);
    /*protected*/ void cancelControlPressed(ActionEvent* e = 0);
    /*protected*/ void addRangeChanged();
    /*protected*/ void prefixChanged();
    /*protected*/ void addControlPressed(ActionEvent* e = 0);


 friend class LTBeanTableDataModel;
 friend class LightControlTableModel;
 friend class LTAWindowListener;
 friend class ACFWindowListener;
};
Q_DECLARE_METATYPE(LightTableAction)

class LTBeanTableDataModel : public BeanTableDataModel
{
    Q_OBJECT
    LightTableAction* lta;
public:
    enum COLUMNS
    {
     ENABLECOL = NUMCOLUMN,
     INTENSITYCOL = ENABLECOL + 1,
     EDITCOL = INTENSITYCOL + 1
    };
    LTBeanTableDataModel(LightTableAction* lta);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QString getValue(QString name) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    void doDelete(NamedBean* bean);
    /*public*/ Manager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name) const;
    /*public*/ NamedBean* getByUserName(QString name) ;
    /*public*/ void clickOn(NamedBean* t);
    /*public*/ QPushButton* configureButton();
    /*public*/ void configureTable(JTable *table);


protected:
  /*protected*/ QString enabledString;// = tr("Enabled");
  /*protected*/ QString intensityString;// = tr("Intensity");

    /*protected*/ QString getBeanType() ;
    /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);
    /*protected*/ QString getMasterClassName();

};

/*public*/ class LightControlTableModel : public AbstractTableModel //implements
//        java.beans.PropertyChangeListener {
{
 Q_OBJECT
    LightTableAction* lta;
 public:
    enum COLUMNS
    {
     TYPE_COLUMN = 0,
     DESCRIPTION_COLUMN = 1,
     EDIT_COLUMN = 2,
     REMOVE_COLUMN = 3
    };

    /*public*/ LightControlTableModel(LightTableAction* lta, QObject* parent = 0);
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);

};

class LTAWindowListener : public WindowListener
{
 Q_OBJECT
 LightTableAction* lta;
public:
 LTAWindowListener(LightTableAction* lta);
 void windowClosing(QCloseEvent *e);

};
class ACFWindowListener : public WindowListener
{
 Q_OBJECT
 LightTableAction* lta;
public:
 ACFWindowListener(LightTableAction* lta);
 void windowClosing(QCloseEvent *e);

};

#endif // LIGHTTABLEACTION_H
