#ifndef CONDITIONALVARIABLE_H
#define CONDITIONALVARIABLE_H

#include <QObject>
#include "namedbeanhandle.h"
#include "logger.h"
#include "libPr3_global.h"

class NamedBeanHandleManager;
class Conditional;
class LIBPR3SHARED_EXPORT ConditionalVariable : public QObject
{
    Q_OBJECT
public:
    explicit ConditionalVariable(QObject *parent = 0);
    enum OPERATORS
    {
     NUM_COMPARE_OPERATIONS  = 5,
     LESS_THAN          = 1,
     LESS_THAN_OR_EQUAL = 2,
     EQUAL              = 3,
     GREATER_THAN_OR_EQUAL = 4,
     GREATER_THAN       = 5
    };
    /*public*/ ConditionalVariable(bool _not, int opern, int type, QString name, bool trigger, QObject *parent = 0);
    /*public*/ bool isNegated() ;
    /*public*/ void setNegation(bool _not) ;
    /*public*/ int getOpern();
    /*public*/ void setOpern(int opern);
    /*public*/ int getType();
    /*public*/ void setType(int type);
    /*public*/ QString getName();
    /*public*/ void setName(QString name);
    /*public*/ NamedBeanHandle<NamedBean*>* getNamedBean();
    /*public*/ NamedBean* getBean();
    /*public*/ QString getDataString();
    /*public*/ void setDataString(QString data);
    /*public*/ int getNum1();
    /*public*/ int getNum2();
    /*public*/ void setNum1(int num);
    /*public*/ void setNum2(int num);
    /*public*/ bool doTriggerActions();
    /*public*/ void setTriggerActions(bool trigger);
    /*public*/ int getState();
    /*public*/ void setState(int state);
    /*public*/ void setState(bool state);
    /*public*/ QString getTestTypeString();
    /*public*/ QString getOpernString();
    /*public*/ bool evaluate();
    bool compare(QString value1, QString value2, bool caseInsensitive);
    /*public*/ static QString getItemTypeString(int t);
    /*public*/ static QString getStateString(int t);
    /*public*/ static QString getTestTypeString(int t);
    /*public*/ static QString getCompareOperationString(int index);
    /*public*/ static QString getCompareSymbols(int index);
    /*public*/ static int stringToVariableTest(QString str);
    /*public*/ QString toString();
    /*public*/ static QString describeState(int t);
    /*public*/ QString getGuiName();
    /*public*/ void setGuiName(QString guiName);

signals:

public slots:
 private:
    /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ConditionalVariable");
    /*private*/ bool _not;// = false;
    // Not a variable attribute, but retained as an artifact of previous releases.  This will be used
    // as the default operator immediately to the left of this variable in the antecedent statement. 
    // It may be over written by the antecedent statement in the Conditional to which this variable 
    // belongs.
    /*private*/ int _opern;// = Conditional.OPERATOR_NONE;
    /*private*/ int _type;//   = Conditional.TYPE_NONE;
    /*private*/ QString _name;// = "";
    /*private*/ QString _dataString;// = "";
    /*private*/ int _num1;// = 0;
    /*private*/ int _num2;// = 0;
    /*private*/ QString _guiName;// = "";       // Contains the user name of the referenced conditional
    /*private*/ NamedBeanHandle<NamedBean*>* _namedBean;// = NULL;
    //private NamedBeanHandle<Sensor> _namedSensorBean = null;
    // Name clarification: Formerly was named '_triggersCalculation' because it controlled whether
    // a listener was installed for this device and thus trigger calcuation of the Conditional.
    // Now named '_triggersActions' because listeners are always installed for activated Logix
    // Conditionals and this parameter nows controls whether, if its change of state changes the
    // state of the conditional, should that also  trigger the actions.
    /*private*/ bool _triggersActions;// = true;
    /*private*/ int _state;// = Conditional.UNKNOWN;        // tri-state
    /*private*/ int fixMidnight(int time);
    void common();
protected:
    /*protected*/ NamedBeanHandleManager* nbhm;// = InstanceManager.getDefault(jmri.NamedBeanHandleManager.class);

};

#endif // CONDITIONALVARIABLE_H
