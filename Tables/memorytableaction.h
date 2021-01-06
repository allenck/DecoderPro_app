#ifndef MEMORYTABLEACTION_H
#define MEMORYTABLEACTION_H
#include "abstracttableaction.h"
#include "beantabledatamodel.h"
#include "actionlistener.h"
#include "spinnernumbermodel.h"
#include "jspinner.h"
#include "jcheckbox.h"
#include "jlabel.h"

class UserPreferencesManager;
class JTextField;
class QLabel;
class MemoryTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    Q_INVOKABLE MemoryTableAction(QObject* parent = 0);
    Q_INVOKABLE/*public*/ MemoryTableAction(QString actionName, QObject* parent);
    ~MemoryTableAction() {}
    MemoryTableAction(const MemoryTableAction& that) : AbstractTableAction(that.text(), that.parent()) {}
    Q_INVOKABLE /*public*/ QString getClassDescription();
    Q_INVOKABLE /*public*/ void setMessagePreferencesDetails();

private:
    void common();
    JmriJFrame* addFrame;// = NULL;
    JTextField* sysNameField;// = new JTextField(5);
    JTextField* userNameField;// = new JTextField(5);
    QLabel* sysNameLabel;// = new JLabel(tr("LabelSystemName"));
    QLabel* userNameLabel;// = new JLabel(tr("LabelUserName"));
    SpinnerNumberModel* rangeSpinner = new SpinnerNumberModel(1, 1, 100, 1); // maximum 100 items
    JSpinner* numberToAddSpinner = new JSpinner(rangeSpinner);
    JCheckBox* rangeBox = new JCheckBox(tr("Add Range Box"));
    JCheckBox* autoSystemNameBox = new JCheckBox(tr("Auto Sys Name"));
    JLabel* statusBarLabel = new JLabel(tr("Enter a System Name and (optional) User Name."), JLabel::LEADING);UserPreferencesManager* p;
    QString systemNameAuto;// = this.getClass().getName() + ".AutoSystemName";
    Logger* log;
    void handleCreateException(QString sysNameField);

protected:
    /*protected*/ void createModel();
    /*protected*/ void setTitle();
    /*protected*/ QString helpTarget();
    /*protected*/ QString getClassName();

protected slots:
    /*protected*/ void addPressed(JActionEvent* /*e*/);
    void cancelPressed(JActionEvent* e = 0);
    void okPressed(JActionEvent* e = 0);


    friend class MtBeanTableDataModel;
    friend class MtOkListener;
    friend class MtCancelListener;
};
Q_DECLARE_METATYPE(MemoryTableAction)

class MtBeanTableDataModel : public BeanTableDataModel
{
 Q_OBJECT
    MemoryTableAction* act;
public:
    MtBeanTableDataModel(MemoryTableAction* mt);
    /*public*/ QString getValue(QString name) const;
    /*public*/ Manager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name) const;
    /*public*/ NamedBean* getByUserName(QString name) ;
    /*public*/ void clickOn(NamedBean* t);
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ void configValueColumn(JTable* table);
    /*public*/ QPushButton* configureButton();
private:
    Logger* log;

protected:
    /*protected*/ QString getMasterClassName();
    /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);
    /*protected*/ QString getBeanType() ;
};

class MtOkListener : public ActionListener
{
 Q_OBJECT
 MemoryTableAction* act;
public:
 MtOkListener(MemoryTableAction* act);
public slots:
 void actionPerformed();
};

class MtCancelListener : public ActionListener
{
 Q_OBJECT
 MemoryTableAction* act;
public:
 MtCancelListener(MemoryTableAction* act);
public slots:
 void actionPerformed();
};

#endif // MEMORYTABLEACTION_H
