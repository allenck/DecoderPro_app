#ifndef SENSORTABLEACTION_H
#define SENSORTABLEACTION_H

#include <QObject>
#include "actionlistener.h"
#include "abstracttableaction.h"
#include "libtables_global.h"
#include "propertychangeevent.h"
#include <QVariant>
#include<QPushButton>
#include "propertychangelistener.h"
#include <QSpinBox>

class STAValidator;
class QPushButton;
class ProxySensorManager;
class QTableView;
class PropertyChangeEvent;
class BeanTableFrame;
class BeanTableDataModel;
class JFrame;
//class ActionEvent;
class Manager;
class SensorManager;
class QLabel;
class QCheckBox;
class UserPreferencesManager;
class QComboBox;
class JmriJFrame;
class JTextField;
class LIBTABLESSHARED_EXPORT SensorTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SensorTableAction(QObject *parent = 0);
    /*public*/ SensorTableAction(QString actionName, QObject *parent);
    ~SensorTableAction() {}
    SensorTableAction(const SensorTableAction& that) : AbstractTableAction(that.text(), that.parent()) {}
    /*public*/ void setManager(Manager* man);
    /*public*/ void setMenuBar(JmriJFrame* f);
//    /*public*/ void setEnabled(bool newValue);
    /*public*/ void addToFrame(BeanTableFrame* f);
    Q_INVOKABLE /*public*/ void setMessagePreferencesDetails();
    Q_INVOKABLE /*public*/ QString getClassDescription();
    static QString getName();
    /*public*/ void addToPanel(AbstractTableTabAction* f);

signals:
//    void propertyChange(PropertyChangeEvent*);
public slots:
//    void onDebounce();
    /*public*/ void propertyChange(PropertyChangeEvent* propertyChangeEvent);

private:
    JmriJFrame* addFrame;// = NULL;

    JTextField* hardwareAddressTextField;// = new JTextField(40);
    JTextField* userNameField;// = new JTextField(40);
    QComboBox* prefixBox;// = new JComboBox();
    JTextField* numberToAdd;// = new JTextField(5);
    QSpinBox* numberToAddSpinner;// = new JSpinner(rangeSpinner);
    QCheckBox* rangeBox;// = new JCheckBox("Add a range");
    QLabel* sysNameLabel;// = new JLabel("Hardware Address");
    QLabel* userNameLabel;// = new JLabel(tr("LabelUserName"));
    QString systemSelectionCombo;// = this.getClass().getName()+".SystemSelected";
    QString userNameError;// = this.getClass().getName()+".DuplicateUserName";
    QLabel* statusBarLabel;// = new JLabel(Bundle.getMessage("HardwareAddStatusEnter"), JLabel.LEADING);

    UserPreferencesManager* p;
    void handleCreateException(QString hardwareAddressTextField);
    BeanTableFrame* f;
    //BeanTableDataModel* m;
    QCheckBox* showDebounceBox;// = new JCheckBox(tr("SensorDebounceCheckBox"));
    bool enabled;
    QString connectionChoice;// = "";
    QPushButton* addButton;
    QString  addEntryToolTip;
    QLabel* statusBar;// = new JLabel(Bundle.getMessage("HardwareAddStatusEnter"), JLabel.LEADING);
    STAValidator* validator;

private slots:
    /*private*/ void canAddRange();
    void showDebounceChanged(bool);
    void createPressed();

protected:
    /*protected*/ SensorManager* senManager;// = jmri.InstanceManager.sensorManagerInstance();
    /*protected*/ void createModel();
    /*protected*/ void setTitle();
    /*protected*/ QString helpTarget();
    /*protected*/ void setDefaultDebounce(JFrame* _who);
    /*protected*/ QString getClassName();
    /*protected*/ void setDefaultState(JFrame* _who);

protected slots:
    /*protected*/ void addPressed();
    void cancelPressed(ActionEvent* e = 0);


friend class STOkButtonActionListener;
friend class STCancelActionListener;
friend class STRangeActionListener;
friend class DebounceActionListener;
friend class SensorWidget;
friend class SensorTableWidget;
friend class DefaultStateActionListener;
friend class STAValidator;
};
Q_DECLARE_METATYPE(SensorTableAction)

class STOkButtonActionListener : public ActionListener
{
 Q_OBJECT
 SensorTableAction* act;
public:
 STOkButtonActionListener(SensorTableAction* act);
public slots:
 void actionPerformed();

};

class STCancelActionListener : public ActionListener
{
 Q_OBJECT
 SensorTableAction* act;
public:
 STCancelActionListener(SensorTableAction* act);
public slots:
 void actionPerformed();
};

class STRangeActionListener : public ActionListener
{
 Q_OBJECT
 SensorTableAction* act;
public:
 STRangeActionListener(SensorTableAction* act);
public slots:
 void actionPerformed();
};

class DebounceActionListener : public ActionListener
{
 Q_OBJECT
 JmriJFrame* finalF;
 SensorTableAction* act;
public:
 DebounceActionListener(JmriJFrame* finalF, SensorTableAction* act);
public slots:
 void actionPerformed(ActionEvent *e = 0);
};

class DefaultStateActionListener : public ActionListener
{
 Q_OBJECT
 JmriJFrame* finalF;
 SensorTableAction* act;
public:
 DefaultStateActionListener(JmriJFrame* finalF, SensorTableAction* act);
public slots:
 void actionPerformed(ActionEvent *e = 0);
};

class STAValidator : public QValidator
{
 Q_OBJECT
 SensorTableAction* act;
 JTextField* fld;
 bool allow0Length = false; // for Add new bean item, a value that is zero-length is considered invalid.
 QString prefix;// = ConnectionNameFromSystemName::getPrefixFromName(rta->connectionChoice);
 QColor mark;// = ColorUtil::stringToColor("orange");

public:
 STAValidator(JTextField* fld, SensorTableAction* act);
 QValidator::State validate(QString &, int &) const;
 void setPrefix(QString);
 //void fixup(QString &input) const;

public slots:
 void prefixBoxChanged(QString);
};
#endif // SENSORTABLEACTION_H
