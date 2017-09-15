#ifndef MEMORYTABLEACTION_H
#define MEMORYTABLEACTION_H
#include "abstracttableaction.h"
#include "beantabledatamodel.h"
#include "actionlistener.h"

class UserPreferencesManager;
class JTextField;
class QLabel;
class MemoryTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    MemoryTableAction(QObject* parent = 0);
    Q_INVOKABLE/*public*/ MemoryTableAction(QString actionName, QObject* parent);
    ~MemoryTableAction() {}
    MemoryTableAction(const MemoryTableAction& that) : AbstractTableAction(that.text(), that.parent()) {}
    /*public*/ QString getClassDescription();

private:
    void common();
    JmriJFrame* addFrame;// = NULL;
    JTextField* sysName;// = new JTextField(5);
    JTextField* userName;// = new JTextField(5);
    QLabel* sysNameLabel;// = new JLabel(tr("LabelSystemName"));
    QLabel* userNameLabel;// = new JLabel(tr("LabelUserName"));

    JTextField* numberToAdd;// = new JTextField(10);
    QCheckBox* range;// = new JCheckBox(tr("AddRangeBox"));
    QCheckBox* autoSystemName;// = new JCheckBox(tr("LabelAutoSysName"));
    UserPreferencesManager* p;
    QString systemNameAuto;// = this.getClass().getName() + ".AutoSystemName";
    Logger* log;
    void handleCreateException(QString sysName);

protected:
    /*protected*/ void createModel();
    /*protected*/ void setTitle();
    /*protected*/ QString helpTarget();
    /*protected*/ QString getClassName();

protected slots:
    /*protected*/ void addPressed(ActionEvent* /*e*/);
    void cancelPressed(ActionEvent* e = 0);
    void okPressed(ActionEvent* e = 0);


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
