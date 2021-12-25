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
    Q_INVOKABLE /*public*/ QString getClassDescription() override;
    Q_INVOKABLE /*public*/ void setMessagePreferencesDetails() override;

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
    JLabel* statusBarLabel = new JLabel(tr("Enter a System Name and (optional) User Name."), JLabel::LEADING);
    UserPreferencesManager* p = nullptr;
    QString systemNameAuto;// = this.getClass().getName() + ".AutoSystemName";
    Logger* log;
    void handleCreateException(QString sysNameField);

protected:
    /*protected*/ void createModel() override;
    /*protected*/ void setTitle() override;
    /*protected*/ QString helpTarget() override;
    /*protected*/ QString getClassName() override;

protected slots:
    /*protected*/ void addPressed(JActionEvent* e=0) override;
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
    /*public*/ AbstractManager* getManager();
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

class MtOkListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
 MemoryTableAction* act;
public:
 MtOkListener(MemoryTableAction* act);
QObject* self() override{return (QObject*)this;}public slots:
 void actionPerformed(JActionEvent */*e*/ = 0) override;
};

class MtCancelListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
 MemoryTableAction* act;
public:
 MtCancelListener(MemoryTableAction* act);
 QObject* self() override{return (QObject*)this;}
public slots:
 void actionPerformed(JActionEvent */*e*/ = 0)override;
};

#endif // MEMORYTABLEACTION_H
