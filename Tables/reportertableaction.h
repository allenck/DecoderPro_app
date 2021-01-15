#ifndef REPORTERTABLEACTION_H
#define REPORTERTABLEACTION_H
#include "abstracttableaction.h"
#include "beantabledatamodel.h"
#include "actionlistener.h"
#include "colorutil.h"
#include "inputverifier.h"
#include "connectionnamefromsystemname.h"
#include "jtextfield.h"
#include "instancemanager.h"
#include "reportermanager.h"
#include "jbutton.h"
#include <QLineEdit>
#include <QValidator>
#include "managercombobox.h"
#include "jcheckbox.h"
#include "spinnernumbermodel.h"
#include "jspinner.h"
#include "jlabel.h"
#include "systemnamevalidator.h"

class QVBoxLayout;
class ReporterManager;
class JComboBox;
class QCheckBox;
class UserPreferencesManager;
class ReporterTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    Q_INVOKABLE ReporterTableAction(QObject* parent = 0);
    Q_INVOKABLE /*public*/ ReporterTableAction(QString actionName, QObject* parent);
    ~ReporterTableAction() {}
    ReporterTableAction(const ReporterTableAction& that) : AbstractTableAction(that.text(), that.parent()) {}
    /*public*/ void setManager(ReporterManager* man);
    Q_INVOKABLE /*public*/ QString getClassDescription();

private:
    void common();
    JmriJFrame* addFrame = NULL;
    QVBoxLayout* addFrameLayout;
    JTextField* hardwareAddressTextField = new JTextField(20);
    JTextField* userNameTextField = new JTextField(20);
    ManagerComboBox* prefixBox = new ManagerComboBox/*<Manager*>*/();
    /*private*/ /*final*/ SpinnerNumberModel* rangeSpinner = new SpinnerNumberModel(1, 1, 100, 1); // maximum 100 items
    /*private*/ /*final*/ JSpinner* numberToAddSpinner = new JSpinner(rangeSpinner);
    JCheckBox* rangeCheckBox = new JCheckBox(tr("Add a range"));
    JLabel* sysNameLabel;// = new JLabel("Hardware Address");
    JLabel* userNameLabel;// = new JLabel(tr("LabelUserName"));
    QString systemSelectionCombo;// = this.getClass().getName() + ".SystemSelected";
    /*private*/ JButton* addButton;
    QString userNameError;// = this.getClass().getName() + ".DuplicateUserName";
    QString connectionChoice;// = "";
    JLabel* statusBarLabel;// = new JLabel(Bundle.getMessage("HardwareAddStatusEnter"), JLabel.LEADING);
    /*private*/ QString addEntryToolTip;
    UserPreferencesManager* pref;
    /*private*/ SystemNameValidator* hardwareAddressValidator;
    Logger* log;

private slots:
    void cancelPressed(ActionEvent* e = 0);
    void createPressed(ActionEvent* e = 0);
    /*private*/ void canAddRange(ActionEvent* e = 0);


protected:
    /*protected*/ ReporterManager* reporterManager;// = InstanceManager::reporterManagerInstance();
    /*protected*/ void createModel();
    /*protected*/ void setTitle();
    /*protected*/ QString helpTarget();
    /*protected*/ QString getClassName();
    void handleCreateException(QString sysName);

protected slots:
    /*protected*/ void addPressed(ActionEvent* e = 0);

 friend class RtBeanTableDataModel;
 friend class RTACreateListener;
 friend class RTACancelActionListener;
 friend class ReporterRangeListener;
 friend class RTAValidator;
};
Q_DECLARE_METATYPE(ReporterTableAction)

class RtBeanTableDataModel : public BeanTableDataModel
{
    Q_OBJECT
    ReporterTableAction* act;
public:
    RtBeanTableDataModel(ReporterTableAction* act);
    /*public*/ static /*final*/ int LASTREPORTCOL;// = NUMCOLUMN;
    /*public*/ QString getValue(QString name) const;
    /*public*/ Manager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name) const;
    /*public*/ NamedBean* getByUserName(QString name);
    /*public*/ void clickOn(NamedBean* t);
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ void configValueColumn(JTable* table);
    /*public*/ QPushButton* configureButton();

private:
    Logger* log;
protected:
    /*protected*/ QString getMasterClassName();
    /*protected*/ QString getBeanType();
    /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);
};

class RTACreateListener : public ActionListener
{
 Q_OBJECT
    ReporterTableAction* act;
public:
    RTACreateListener(ReporterTableAction* act);
    /*public*/ void actionPerformed(JActionEvent* e = 0) ;
};

class RTACancelActionListener : public ActionListener
{
    Q_OBJECT
    ReporterTableAction* act;
   public:
    RTACancelActionListener(ReporterTableAction* act);
    /*public*/ void actionPerformed(JActionEvent* e = 0);
};

class ReporterRangeListener : public ActionListener
{
    Q_OBJECT
    ReporterTableAction* act;
   public:
     ReporterRangeListener(ReporterTableAction* act);
    /*public*/ void actionPerformed(JActionEvent* e = 0);
};
#if 0
/**
 * Private class used in conjunction with CheckedTextField to provide
 * the mechanisms required to validate the text field data upon loss of
 * focus, and colorize the text field in case of validation failure.
 */
/*private*/ class MyVerifier : public InputVerifier //implements java.awt.event.ActionListener
{
Q_OBJECT

    // set default background color for invalid field data
    QColor mark;// = ColorUtil::stringToColor("orange");
public:
    /** {@inheritDoc} */
    //@Override
    /*public*/ bool shouldYieldFocus(QWidget* input);
    /*public*/ bool verify(QWidget* input);
    //@Override
    /*public*/ void actionPerformed(ActionEvent* e);
};

/**
 * Extends JTextField to provide a data validation function.
 *
 * @author Egbert Broerse 2017, based on
 * jmri.jmrit.util.swing.ValidatedTextField by B. Milhaupt
 */
/*public*/ class CheckedTextField : public JTextField
{
Q_OBJECT
    CheckedTextField* fld;
    bool allow0Length = false; // for Add new bean item, a value that is zero-length is considered invalid.
    /*private*/ MyVerifier* verifier; // internal mechanism used for verifying field data before focus is lost
    ReporterTableAction* rta;
public:
    /**
     * Text entry field with an active key event checker.
     *
     * @param len field length
     */
    /*public*/ CheckedTextField(int len, ReporterTableAction* rta);
    /*public*/ bool isValid() ;
};
#endif
class RTAValidator : public QValidator
{
 Q_OBJECT
 ReporterTableAction* act;
 JTextField* fld;
 bool allow0Length = false; // for Add new bean item, a value that is zero-length is considered invalid.
 QString prefix;// = ConnectionNameFromSystemName::getPrefixFromName(rta->connectionChoice);
 QColor mark;// = ColorUtil::stringToColor("orange");
public:
 RTAValidator(JTextField* fld, ReporterTableAction* act);
 QValidator::State validate(QString &, int &) const;
 //void fixup(QString &input) const;

public slots:
 void prefixBoxChanged(QString txt);

};
#endif // REPORTERTABLEACTION_H
