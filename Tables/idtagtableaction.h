#ifndef IDTAGTABLEACTION_H
#define IDTAGTABLEACTION_H
#include "abstracttableaction.h"
#include "beantabledatamodel.h"
#include "actionlistener.h"
#include "instancemanager.h"
#include "rfid/proxyidtagmanager.h"
#include <QCheckBox>
#include "jtextfield.h"

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
    Q_INVOKABLE /*public*/ QString getClassDescription()override;
    /*public*/ void addToFrame(BeanTableFrame* f)override;
    /*public*/ void addToPanel(AbstractTableTabAction* f)override;
    /*public*/ void setManager(/*@Nonnull*/ Manager/*<IdTag>*/* t)override;

    QObject* self() override {return (QObject*)this;}

private:
    JmriJFrame* addFrame = nullptr;
    JTextField* sysName = new JTextField(12);
    JTextField* userName = new JTextField(15);
    QCheckBox* isStateStored = new QCheckBox(tr("Store State"));
    QCheckBox* isFastClockUsed = new QCheckBox(tr("Use Fast Clock"));
    void handleCreateException(QString sysName, IllegalArgumentException* ex);
    static Logger* log;
    /*final*/ void init();

private slots:
    void cancelPressed(ActionEvent* /*e*/= 0);
    void okPressed(ActionEvent* /*e*/ = 0);


protected:
    /*protected*/ void createModel() override;
    /*protected*/ QString getClassName() override;
    /*protected*/ void setTitle() override;
    /*protected*/ QString helpTarget() override;
    /*protected*/ IdTagManager* tagManager = (ProxyIdTagManager*)InstanceManager::getDefault("IdTagManager");

protected slots:
    /*protected*/ void addPressed(JActionEvent* =0) override;

 friend class IdTagBeanTableDataModel;
 friend class StateStoredActionListener;
 friend class FastClockUsedActionListener;
 friend class CancelListener;
 friend class IdTagOkListener;
};
Q_DECLARE_METATYPE(IdTagTableAction)

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
