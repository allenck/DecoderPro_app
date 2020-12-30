#ifndef DEFAULTCONDITIONAL_H
#define DEFAULTCONDITIONAL_H

#include "conditional.h"
#include "bitset.h"
#include "exceptions.h"
#include "actionlistener.h"
#include "libPr3_global.h"
#include "jdialog.h"
#include <QCheckBox>

class BitSet;
class Memory;
class DataPair;
class ConditionalAction;
class ConditionalVariable;
class LIBPR3SHARED_EXPORT DefaultConditional : public Conditional
{
    Q_OBJECT
public:
 explicit DefaultConditional(QObject *parent = 0) : Conditional(parent) {}
    /*public*/ static /*final*/ bool PARKS_DEBUG;// = false;
    /*public*/ DefaultConditional(QString systemName, QString userName="", QObject *parent = 0);
    /*public*/ static int getIndexInTable(QList<int> table, int entry);
    /*public*/ QString getAntecedentExpression();
    /*public*/ int getLogicType() ;
    /*public*/ void setLogicType(int type, QString antecedent);
    /*public*/  bool getTriggerOnChange();
    /*public*/  void setTriggerOnChange(bool trigger);
    /*public*/ void setStateVariables(QList <ConditionalVariable*>* arrayList);
    /*public*/ QList <ConditionalVariable*>* getCopyOfStateVariables() ;
    /*public*/ QList <ConditionalAction*>* getCopyOfActions ();
    /*public*/ void setAction (QList <ConditionalAction*>* arrayList);
    void setState(int s);
    int getState();
    /*public*/ void cancelSensorTimer (QString sname);
    /*public*/ void cancelTurnoutTimer (QString sname);

    /*public*/ int calculate (bool enabled, PropertyChangeEvent* evt);
    bool wantsToTrigger(PropertyChangeEvent* evt);
    /*public*/ QString validateAntecedent(QString ant, QList <ConditionalVariable*>* variableList);
    /*public*/ QList<ConditionalAction*> getActionList();
    /*public*/ QList<ConditionalVariable *> *getStateVariableList();


signals:

public slots:
private:
    // boolean expression of state variables
    /*private*/ QString _antecedent;// = "";
    /*private*/ int _logicType;// = Conditional::ALL_AND;
    // variables (antecedent) parameters
    /*private*/ QList <ConditionalVariable*>* _variableList;// = new ArrayList<ConditionalVariable>();
    // actions (consequent) parameters

    /*private*/ int _currentState;// = Conditional.UNKNOWN;
    /*private*/ bool _triggerActionsOnChange;// = true;
    /*private*/ void takeActionIfNeeded();
    static /*private*/ bool _skipErrorDialog;// = false;
    /*private*/ QString getDeviceName(ConditionalAction* action);
    /*private*/ QString getActionString(ConditionalAction* action);
    static /*private*/ Memory* getMemory(QString name);
    int getIntegerValue(ConditionalAction* action);

    Logger* log;
    protected:
    /*protected*/ QList <ConditionalAction*>* _actionList;// = new ArrayList<ConditionalAction>();
    DataPair* parseCalculate(QString s, QList <ConditionalVariable*>* variableList)
    throw (JmriException);
    friend class TimeTurnout;
    friend class TimeSensor;
    friend class ErrorDialog;
};
/*static*/ class DataPair
{

 public:
    bool result;// = false;
    int indexCount;// = 0;         // index reached when parsing completed
    BitSet* argsUsed;// = NULL;     // error detection for missing arguments
    DataPair();
};
class TimeSensor : public ActionListener
{
    Q_OBJECT

    /*private*/ int mIndex;// = 0;
     DefaultConditional* self;
public:
     TimeSensor(int index, DefaultConditional* self);
public slots:
     /*public*/ void actionPerformed(JActionEvent* event = 0);

};

class TimeTurnout : public ActionListener
{
    Q_OBJECT

    /*private*/ int mIndex;// = 0;
     DefaultConditional* self;
public:
    TimeTurnout(int index, DefaultConditional* self);
public slots:
    /*public*/ void actionPerformed(JActionEvent* event = 0);

};

class ErrorDialog : public  JDialog
{
 Q_OBJECT
    QCheckBox* rememberSession;
    DefaultConditional* cond;
public:
    ErrorDialog(QStringList list, DefaultConditional* cond);
public slots:
    void onCloseButton();
};

#endif // DEFAULTCONDITIONAL_H
