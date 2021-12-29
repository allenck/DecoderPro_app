#ifndef IDTAGTABLEACTION_H
#define IDTAGTABLEACTION_H
#include "abstracttableaction.h"
#include "beantabledatamodel.h"
#include "actionlistener.h"
#include "instancemanager.h"

class AddNewDevicePanel;
class JTextField;
class QCheckBox;
class IdTagTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    IdTagTableAction(QObject* parent = 0);
    Q_INVOKABLE /*public*/ IdTagTableAction(QString actionName, QObject* parent);
    ~IdTagTableAction() {}
    IdTagTableAction(const IdTagTableAction& that) : AbstractTableAction(that.text(), that.parent()) {}
    Q_INVOKABLE /*public*/ QString getClassDescription();
    /*public*/ void addToFrame(BeanTableFrame* f);
    /*public*/ void addToPanel(AbstractTableTabAction* f);

private:
    JmriJFrame* addFrame;// = NULL;
    JTextField* sysName;// = new JTextField(12);
    JTextField* userName;// = new JTextField(15);
    QCheckBox* isStateStored;// = new JCheckBox(tr("IdStoreState"));
    QCheckBox* isFastClockUsed;// = new JCheckBox(tr("IdUseFastClock"));
    void handleCreateException(QString sysName);
    Logger* log;

private slots:
    void cancelPressed(ActionEvent* /*e*/= 0);
    void okPressed(ActionEvent* /*e*/ = 0);


protected:
    /*protected*/ void createModel() override;
    /*protected*/ QString getClassName() override;
    /*protected*/ void setTitle() override;
    /*protected*/ QString helpTarget() override;
    /*protected*/ IdTagManager* tagManager = (IdTagManager*)InstanceManager::getDefault("IdTagManager");

protected slots:
    /*protected*/ void addPressed(JActionEvent* =0) override;

 friend class IdTagBeanTableDataModel;
 friend class StateStoredActionListener;
 friend class FastClockUsedActionListener;
 friend class CancelListener;
 friend class IdTagOkListener;
};
Q_DECLARE_METATYPE(IdTagTableAction)

class IdTagBeanTableDataModel : public BeanTableDataModel
{
 Q_OBJECT
    IdTagTableAction* act;
public:
    IdTagBeanTableDataModel(IdTagTableAction* act);
    enum COLUMNS
    {
     WHERECOL = NUMCOLUMN,
     WHENCOL = WHERECOL + 1,
     CLEARCOL = WHENCOL + 1
    };
    /*public*/ QString getValue(QString name) const;
    /*public*/ AbstractManager *getManager();
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
    void configureTable(JTable *table);

private:
    Logger* log;
protected:
    /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);
    /*protected*/ QString getMasterClassName();
    /*protected*/ QString getBeanType();
};

class StateStoredActionListener : public QObject, public ActionListener
{
 Q_OBJECT
 Q_INTERFACES(ActionListener)
 IdTagTableAction* act;
 StateStoredActionListener(IdTagTableAction* act);
 QObject* self() override{return (QObject*)this;}
public slots:
 void actionPerformed(JActionEvent */*e*/ = 0)override;

 friend class IdTagTableAction;
};

class FastClockUsedActionListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
 IdTagTableAction* act;
 FastClockUsedActionListener(IdTagTableAction* act);
 QObject* self() override{return (QObject*)this;}
public slots:
 void actionPerformed(JActionEvent */*e*/ = 0)override;

 friend class IdTagTableAction;
};

class IdTagOkListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
 IdTagTableAction* act;
 IdTagOkListener(IdTagTableAction* act);
 QObject* self() override{return (QObject*)this;}
public slots:
 void actionPerformed(JActionEvent */*e*/ = 0)override;

 friend class IdTagTableAction;
};

class CancelListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
 IdTagTableAction* act;
 CancelListener(IdTagTableAction* act);
 QObject* self() override{return (QObject*)this;}
public slots:
 void actionPerformed(JActionEvent */*e*/ = 0)override;

 friend class IdTagTableAction;
};

#endif // IDTAGTABLEACTION_H
