#ifndef TURNOUTTABLEACTION_H
#define TURNOUTTABLEACTION_H
#include "abstracttableaction.h"
#include "../LayoutEditor/beantabledatamodel.h"
#include "actionlistener.h"
#include "jdialog.h"
#include "libtables_global.h"
#include <QHash>
#include "namedbeancombobox.h"
#include <functional>
#include "managercombobox.h"
#include "spinnernumbermodel.h"
#include "jspinner.h"
#include "jlabel.h"
#include "jcheckbox.h"
#include "instancemanager.h"
#include "turnoutmanager.h"
#include "tristatejcheckbox.h"

class SystemNameValidator;
class Sensor;
class BufferedImage;
class TTAValidator;
class QSpinBox;
class JTable;
class TurnoutOperationConfig;
class TurnoutOperation;
class ItemListener;
class TTComboBoxDelegate;
class TTEditDelegate;
class Turnout;
class JActionEvent;
class JmriJFrame;
class QLabel;
class JTextField;
class JComboBox;
class UserPreferencesManager;
//class TurnoutManager;
//class QTableView;
class LIBTABLESSHARED_EXPORT TurnoutTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TurnoutTableAction(QObject *parent = 0);
    /*public*/ Q_INVOKABLE TurnoutTableAction(QString actionName, QObject *parent);
    ~TurnoutTableAction() {}
    Q_INVOKABLE TurnoutTableAction(const TurnoutTableAction& that) : AbstractTableAction(that.text(), that.parent()) {}
    /*public*/ void setManager(Manager* man) override;
    Q_INVOKABLE /*public*/ QString getClassDescription() override;
    static QString getName();
    /*public*/ static void updateAutomationBox(Turnout* t, JComboBox *cb);
    /*public*/ void addToFrame(BeanTableFrame* f) override;
    /*public*/ void setMenuBar(BeanTableFrame* f) override;
    /*public*/ void addToPanel(AbstractTableTabAction* f) override;
    QObject* self() override {return (QObject*)this;}

signals:

public slots:
    void createPressed(ActionEvent* e = 0);
    void cancelPressed(ActionEvent* e = 0);
//    void showFeedbackChanged();
//    void showLockChanged();
//    /*public*/ void showTurnoutSpeedChanged();
//    void On_doAutomationBox_toggled(bool);
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;

private:
    void common();
    /*private*/ bool noWarn;// = false;
    Q_INVOKABLE /*public*/ void setMessagePreferencesDetails() override;
//    /*private*/ void updateClosedList();
//    /*private*/ void updateThrownList();
    JmriJFrame* addFrame;// = NULL;
    JTextField* userNameTextField;// = new JTextField(40);
    JTextField* hardwareAddressTextField;// = new CheckedTextField(20);
    JLabel* statusBarLabel;

    ManagerComboBox/*<Turnout>*/* prefixBox = new ManagerComboBox();
    SpinnerNumberModel* rangeSpinner = new SpinnerNumberModel(1, 1, 100, 1); // maximum 100 items
    JSpinner* numberToAddSpinner = new JSpinner(rangeSpinner);
    JCheckBox* rangeBox = new JCheckBox("Add a range");
    QLabel* sysNameLabel;// = new JLabel("Hardware Address");
    QLabel* userNameLabel;// = new JLabel(tr("LabelUserName"));
    QString systemSelectionCombo;// = this.getClass().getName()+".SystemSelected";
    JButton* addButton;
    QString userNameError;// = this.getName()+".DuplicateUserName";
    UserPreferencesManager* pref;
    SystemNameValidator* hardwareAddressValidator;
    static Logger* log;
//    void editButton(Turnout* t, QModelIndex index);
    TriStateJCheckBox* showFeedbackBox = new TriStateJCheckBox("Show feedback information");
    TriStateJCheckBox* showLockBox = new TriStateJCheckBox("Show lock information");
    TriStateJCheckBox* showTurnoutSpeedBox = new TriStateJCheckBox("Show Turnout Speed Details");
    /*private*/ /*final*/ TriStateJCheckBox* showStateForgetAndQueryBox = new TriStateJCheckBox(tr("Show State Query actions"));
    JCheckBox* doAutomationBox = new JCheckBox("Automatic retry");
    void handleCreateException(QString sysName);
    TTAValidator* validator;
    QString connectionChoice;
    QString addEntryToolTip;
    /*private*/ void initCheckBoxes();

protected:
    /*protected*/ QString getClassName() override;
    /*protected*/ void createModel() override;
    /*protected*/ void setTitle() override;
    /*protected*/ QString helpTarget() override;
//    /*protected*/ void setTurnoutOperation(Turnout* t, JComboBox *cb);
//    /*protected*/ void editTurnoutOperation(Turnout* t, QString val);
    /*protected*/ void setDefaultSpeeds(JFrame* _who);
    // for icon state col
    /*protected*/ bool _graphicState = false; // updated from prefs
    /*protected*/ TurnoutManager* turnoutManager = (TurnoutManager*)InstanceManager::getDefault("TurnoutManager");
    /*protected*/ void configureTable(JTable* table) override;
    /*protected*/ void columnsVisibleUpdated(QVector<bool> colsVisible) override;

protected slots:
    /*protected*/ void addPressed(JActionEvent* e = 0) override;
    /*private*/ void canAddRange(JActionEvent* e = 0);
 friend class CBActionListener;
 friend class RangeListener;
 friend class OkListener;
 friend class TurnoutTableDataModel;
 friend class ItemListener2;
 friend class TTAValidator;
 friend class TTComboBoxDelegate;
};
Q_DECLARE_METATYPE(TurnoutTableAction)

class OkListener : public QObject, public ActionListener
{
    Q_OBJECT
    Q_INTERFACES(ActionListener)
    TurnoutTableAction* tta;
public:
    OkListener(TurnoutTableAction* tta);
    QObject* self() override{return (QObject*)this;}
public slots:
    void actionPerformed(JActionEvent *e = 0)override;
};

class ToCancelActionListener : public QObject, public ActionListener
{
    Q_OBJECT
    Q_INTERFACES(ActionListener)
    TurnoutTableAction* tta;
public:
    ToCancelActionListener(TurnoutTableAction* tta);
    QObject* self() override{return (QObject*)this;}
public slots:
    void actionPerformed(JActionEvent *e = 0) override;
};

class RangeListener : public QObject, public ActionListener
{
    Q_OBJECT
    Q_INTERFACES(ActionListener)
    TurnoutTableAction* tta;
public:
    RangeListener(TurnoutTableAction* tta);
    QObject* self() override{return (QObject*)this;}
public slots:
    void actionPerformed(JActionEvent *e = 0) override;
};

class ItemListener1 : public QObject, public ActionListener
{
 Q_OBJECT
  Q_INTERFACES(ActionListener)
 JmriJFrame* F;
public:
 ItemListener1(JmriJFrame* F);
 QObject* self() override{return (QObject*)this;}
public slots:
 void actionPerformed(JActionEvent *e = 0)override;
};

class ItemListener2 : public QObject, public ActionListener
{
 Q_OBJECT
  Q_INTERFACES(ActionListener)
 JmriJFrame* F;
 TurnoutTableAction* tta;
public:
 ItemListener2(JmriJFrame* F, TurnoutTableAction* tta);
 QObject* self() override{return (QObject*)this;}
public slots:
 void actionPerformed(JActionEvent *e = 0) override;
};

#if 0
/*protected*/ /*static*/ class TurnoutOperationEditor : public JDialog, public PropertyChangeListener
{
 Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)
    /**
     *
     */
//    /*private*/ static /*final*/ long serialVersionUID = 3523604197678096714L;
    TurnoutOperationConfig* config;
    TurnoutOperation* myOp;
    Turnout* myTurnout;
 public:
    TurnoutOperationEditor(TurnoutTableAction* tta, JFrame* parent, TurnoutOperation* op, Turnout* t, /*JComboBox* box*/ QString val);
    QObject* self() override {return (QObject*)this;}
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt) override;
private:
    /*private*/ void setTitle();
};
#endif
class TTAValidator : public QValidator
{
 Q_OBJECT
 TurnoutTableAction* act;
 JTextField* fld;
 bool allow0Length = false; // for Add new bean item, a value that is zero-length is considered invalid.
 QString prefix;// = ConnectionNameFromSystemName::getPrefixFromName(rta->connectionChoice);
 QColor mark;// = ColorUtil::stringToColor("orange");

public:
 TTAValidator(JTextField* fld, TurnoutTableAction* act);
 QValidator::State validate(QString &, int &) const;
 void setPrefix(QString);
 //void fixup(QString &input) const;

public slots:
 void prefixBoxChanged(QString);
};
#if 0
class BeanBoxRenderer : public JComboBoxEditor
{
  Q_OBJECT
 public:
  BeanBoxRenderer(NamedBeanComboBox* beanBox)
  {
   setValues(beanBox->itemList());
  }
};

class BeanComboBoxEditor : public JComboBoxEditor
{
  Q_OBJECT
 public:
  BeanComboBoxEditor(NamedBeanComboBox* beanBox)
  {
   setValues(beanBox->itemList());
  }
};
#endif
#endif // TURNOUTTABLEACTION_H
