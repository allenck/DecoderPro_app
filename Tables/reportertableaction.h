#ifndef REPORTERTABLEACTION_H
#define REPORTERTABLEACTION_H
#include "abstracttableaction.h"
#include "beantabledatamodel.h"
#include "actionlistener.h"

class QSpinBox;
class QVBoxLayout;
class ReporterManager;
class JTextField;
class QComboBox;
class QCheckBox;
class UserPreferencesManager;
class QLabel;
class ReporterTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    ReporterTableAction(QObject* parent = 0);
    Q_INVOKABLE /*public*/ ReporterTableAction(QString actionName, QObject* parent);
    ~ReporterTableAction() {}
    ReporterTableAction(const ReporterTableAction& that) : AbstractTableAction(that.text(), that.parent()) {}
    /*public*/ void setManager(ReporterManager* man);
    /*public*/ QString getClassDescription();

private:
    void common();
    JmriJFrame* addFrame = NULL;
    QVBoxLayout* addFrameLayout;
    JTextField* hardwareAddressTextField;// = new CheckedTextField(20);
    //JTextField* sysName;// = new JTextField(10);
    JTextField* userNameTextField;// = new JTextField(20);
    QComboBox* prefixBox;// = new JComboBox<String>();
    QSpinBox* numberToAdd;// = new JTextField(10);
    QCheckBox* range;// = new JCheckBox(tr("AddRangeBox"));
    QLabel* sysNameLabel;// = new JLabel("Hardware Address");
    QLabel* userNameLabel;// = new JLabel(tr("LabelUserName"));
    QString systemSelectionCombo;// = this.getClass().getName() + ".SystemSelected";
    QPushButton* addButton;
    QString userNameError;// = this.getClass().getName() + ".DuplicateUserName";
    QLabel* statusBar;// = new JLabel(Bundle.getMessage("HardwareAddStatusEnter"), JLabel.LEADING);

    UserPreferencesManager* pref;
    Logger* log;

private slots:
    void cancelPressed(ActionEvent* e = 0);
    void createPressed(ActionEvent* e = 0);
    /*private*/ void canAddRange(ActionEvent* e = 0);


protected:
    /*protected*/ ReporterManager* reportManager;// = InstanceManager::reporterManagerInstance();
    /*protected*/ void createModel();
    /*protected*/ void setTitle();
    /*protected*/ QString helpTarget();
    /*protected*/ QString getClassName();
    void handleCreateException(QString sysName);

protected slots:
    /*protected*/ void addPressed(ActionEvent* e = 0);

 friend class RtBeanTableDataModel;
 friend class OkActionListener;
 friend class CancelActionListener;
 friend class ReporterRangeListener;
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
class OkActionListener : public ActionListener
{
 Q_OBJECT
    ReporterTableAction* act;
public:
    OkActionListener(ReporterTableAction* act);
    /*public*/ void actionPerformed(ActionEvent* e = 0) ;
};
class CancelActionListener : public ActionListener
{
    Q_OBJECT
    ReporterTableAction* act;
   public:
    CancelActionListener(ReporterTableAction* act);
    /*public*/ void actionPerformed(ActionEvent* e = 0);
};
class ReporterRangeListener : public ActionListener
{
    Q_OBJECT
    ReporterTableAction* act;
   public:
     ReporterRangeListener(ReporterTableAction* act);
    /*public*/ void actionPerformed(ActionEvent* e = 0);
};

#endif // REPORTERTABLEACTION_H
