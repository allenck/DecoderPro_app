#ifndef ADDEDITLIGHTDIALOG_H
#define ADDEDITLIGHTDIALOG_H

#include "../LayoutEditor/jmrijframe.h"
#include "proxylightmanager.h"
#include "abstracttablemodel.h"

namespace Ui {
class AddEditLightDialog1;
}

class QPushButton;
class ActionEvent;
class JTextField;
class QLabel;
class QComboBox;
class JmriJFrame;
class LightControlTableModel;
class LightControl;
class AbstractLight;
class AddEditLightDialog : public JmriJFrame
{
    Q_OBJECT

public:
    explicit AddEditLightDialog(AbstractLight* light, QWidget *parent);
    ~AddEditLightDialog();
    int addr();
    QString system();
    QString userName();
    bool isAddRange();
    int numToAdd();
    QString sensorControl;// = tr("Sensor Control");
    QString fastClockControl;// = tr("LightFastClockControl");
    QString turnoutStatusControl;// = tr("LightTurnoutStatusControl");
    QString timedOnControl;// = tr("LightTimedOnControl");
    QString twoSensorControl;// = tr("LightTwoSensorControl");
    QString noControl;// = tr("LightNoControl");
    /*public*/ QString getControlTypeText(int type);
    bool isUpdate();
private:
    Ui::AddEditLightDialog1 *ui;
    AbstractLight* curLight;
    ProxyLightManager* mgr;
    QList<LightControl*>* controlList;
    void setLight(AbstractLight*);
    /*public*/ QString getDescriptionText(LightControl* lc, int type);
    /*private*/ QString getControlSensorSenseText (LightControl* lc) ;
    /*private*/ QString getControlTurnoutStateText (LightControl* lc);
    LightControlTableModel* lightControlTableModel;
    QString formatTime (int hour,int minute);
    bool lightControlChanged;
    bool inEditMode;
    /*private*/ void addEditControlWindow();
    // items for add/edit Light Control window
    /*private*/ JmriJFrame* addControlFrame;// = null;
    /*private*/ QComboBox* typeBox;
    /*private*/ QLabel* typeBoxLabel;// = new JLabel( rb.getString("LightControlType") );
    /*private*/ int sensorControlIndex;
    /*private*/ int fastClockControlIndex;
    /*private*/ int turnoutStatusControlIndex;
    /*private*/ int timedOnControlIndex;
    /*private*/ int twoSensorControlIndex;
    /*private*/ int noControlIndex;
    /*private*/ int defaultControlIndex;// = 0;
    /*private*/ bool inEditControlMode;// = false;
    /*private*/ LightControl* lc;// = null;
    /*private*/ JTextField* field1a;// = new JTextField(10);  // Sensor
    /*private*/ JTextField* field1a2;// = new JTextField(10);  // Sensor 2
    /*private*/ JTextField* field1b;// = new JTextField(8);  // Fast Clock
    /*private*/ JTextField* field1c;// = new JTextField(10);  // Turnout
    /*private*/ JTextField* field1d;// = new JTextField(10);  // Timed ON
    /*private*/ QLabel* f1Label;// = new JLabel( rb.getString("LightSensor") );
    /*private*/ JTextField* field2a;// = new JTextField(8);  // Fast Clock
    /*private*/ JTextField* field2b;// = new JTextField(8); // Timed ON
    /*private*/ QLabel* f2Label;// = new JLabel( rb.getString("LightSensorSense") );
    /*private*/ QComboBox* stateBox;
    /*private*/ int sensorActiveIndex;
    /*private*/ int sensorInactiveIndex;
    /*private*/ int turnoutClosedIndex;
    /*private*/ int turnoutThrownIndex;
    /*private*/ QPushButton* createControl;
    /*private*/ QPushButton* updateControl;
    /*private*/ QPushButton* cancelControl;
    /*private*/ bool setControlInformation(LightControl* g);
    Logger* log;
    void setUpControlType(QString ctype);
    /*private*/ void clearLightControls();
    bool noWarn;
    void handleCreateException(QString sysName);
    /*private*/ void setLightControlInformation(AbstractLight* g);
   bool lightCreatedOrUpdated;

private slots:
    void on_btnCreate_clicked();
    void on_btnUpdate_clicked();
    void on_btnCancel_clicked();
    void on_addControl_clicked();
    void controlTypeChanged();

protected:

protected slots:
    /*protected*/ void createControlPressed(ActionEvent* e = 0);
    /*protected*/ void updateControlPressed(ActionEvent* e = 0);
    /*protected*/ void cancelControlPressed(ActionEvent* e = 0);
    /*protected*/ void editControlAction(int row);
    /*protected*/ void deleteControlAction(int row);

    friend class LightControlTableModel;

};
/**
 * Table model for Light Controls in the Add/Edit Light window
 */
/*public*/ class LightControlTableModel : public AbstractTableModel //implements
//java.beans.PropertyChangeListener
{
 Q_OBJECT

public:
    enum COLUMNS
    {
     TYPE_COLUMN = 0,
     DESCRIPTION_COLUMN = 1,
     EDIT_COLUMN = 2,
     REMOVE_COLUMN = 3
    };


    /*public*/ LightControlTableModel(AddEditLightDialog* dlg);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) ;
private:
    QList<LightControl*>* controlList;
    AddEditLightDialog* dlg;
};
#endif // ADDEDITLIGHTDIALOG_H
