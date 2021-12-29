#ifndef SIGNALMASTTABLEACTION_H
#define SIGNALMASTTABLEACTION_H
#include "abstracttableaction.h"
#include "beantabledatamodel.h"

class AddSignalMastJFrame;
class SignalMastTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    Q_INVOKABLE SignalMastTableAction(QObject* parent = 0);
    Q_INVOKABLE /*public*/ SignalMastTableAction(QString actionName, QObject* parent);
    ~SignalMastTableAction() {}
    SignalMastTableAction(const SignalMastTableAction& that) : AbstractTableAction(that.text(), that.parent()) {}
    enum COLUMNS
    {
    // has to agree with number in SignalMastDataModel
     VALUECOL = BeanTableDataModel::VALUECOL,
     SYSNAMECOL = BeanTableDataModel::SYSNAMECOL
    };
    /*public*/ void setMenuBar(BeanTableFrame* f)override;
    Q_INVOKABLE /*public*/ QString getClassDescription() override;

public slots:

private:
    AddSignalMastJFrame* addFrame;// = null;

 protected:
    /*protected*/ void createModel() override;
    /*protected*/ void setTitle() override;
    /*protected*/ QString helpTarget() override;
    /*protected*/ QString getClassName() override;

protected slots:
    /*protected*/ void addPressed(JActionEvent* =0) override;
    void On_repeatersTriggered();

};
Q_DECLARE_METATYPE(SignalMastTableAction)

class SMTBeanTableFrame : public BeanTableFrame
{
    Q_OBJECT
    SignalMastTableAction* act;
public:
    SMTBeanTableFrame(BeanTableDataModel* m, QString helpTarget, JTable* dataTable, SignalMastTableAction* act);
 /**
  * Include an "add" button
  */
 void extras();
};

#endif // SIGNALMASTTABLEACTION_H
