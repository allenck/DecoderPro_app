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
    /*public*/ void setMenuBar(BeanTableFrame* f);
    Q_INVOKABLE /*public*/ QString getClassDescription();

public slots:
    /*public*/ void actionPerformed(JActionEvent* e = 0)override;


private:
    AddSignalMastJFrame* addFrame;// = null;

 protected:
    /*protected*/ void createModel();
    /*protected*/ void setTitle();
    /*protected*/ QString helpTarget();
    /*protected*/ QString getClassName();

protected slots:
    /*protected*/ void addPressed(JActionEvent* e = 0);
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
