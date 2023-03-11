#ifndef ACTIONSIGNALMASTSWING_H
#define ACTIONSIGNALMASTSWING_H

#include "abstractdigitalactionswing.h"
#include "threadingutil.h"

class ActionSignalMast;
class JComboBox;
class JTabbedPane;
class BeanSelectPanel;
class ActionSignalMastSwing : public AbstractDigitalActionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionSignalMastSwing(QObject *parent = nullptr);
    ~ActionSignalMastSwing() {}
    ActionSignalMastSwing(const ActionSignalMastSwing&) : AbstractDigitalActionSwing() {}
    /*public*/ static /*final*/ int NUM_COLUMNS_TEXT_FIELDS;// = 20;
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object)override;
    /*public*/ QString toString()override;
    /*public*/ void dispose()override;


private:
    /*private*/ JTabbedPane* _tabbedPaneSignalMast;
    /*private*/ BeanSelectPanel/*<SignalMast>*/* _signalMastBeanPanel;
    /*private*/ JPanel* _panelSignalMastDirect;
    /*private*/ JPanel* _panelSignalMastReference;
    /*private*/ JPanel* _panelSignalMastLocalVariable;
    /*private*/ JPanel* _panelSignalMastFormula;
    /*private*/ JTextField* _signalMastReferenceTextField;
    /*private*/ JTextField* _signalMastLocalVariableTextField;
    /*private*/ JTextField* _signalMastFormulaTextField;

    /*private*/ JTabbedPane* _tabbedPaneOperationType;
    /*private*/ JPanel* _panelOperationTypeDirect;
    /*private*/ JPanel* _panelOperationTypeReference;
    /*private*/ JPanel* _panelOperationTypeLocalVariable;
    /*private*/ JPanel* _panelOperationTypeFormula;

    /*private*/ JComboBox/*<ActionSignalMast.OperationType>*/* _operationComboBox;
    /*private*/ JTextField* _signalMastOperationReferenceTextField;
    /*private*/ JTextField* _signalMastOperationLocalVariableTextField;
    /*private*/ JTextField* _signalMastOperationFormulaTextField;

    /*private*/ JTabbedPane* _tabbedPaneAspectType;
    /*private*/ JPanel* _panelAspectTypeDirect;
    /*private*/ JPanel* _panelAspectTypeReference;
    /*private*/ JPanel* _panelAspectTypeLocalVariable;
    /*private*/ JPanel* _panelAspectTypeFormula;

    /*private*/ JComboBox/*<String>*/* _signalMastAspectComboBox;
    /*private*/ JTextField* _signalMastAspectReferenceTextField;
    /*private*/ JTextField* _signalMastAspectLocalVariableTextField;
    /*private*/ JTextField* _signalMastAspectFormulaTextField;

    /*private*/ BeanSelectPanel/*<SignalMast>*/* _exampleSignalMastBeanPanel;
    /*private*/ void setGuiEnabledStates();
    /*private*/ void setAspectComboBox(ActionSignalMast* action);

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

 friend class ASMS_ThreaingUtil;
};
Q_DECLARE_METATYPE(ActionSignalMastSwing)

class ASMS_ThreaingUtil : public ThreadAction
{
  Q_OBJECT
  ActionSignalMastSwing* asms;
  ActionSignalMast* action;
 public:
  ASMS_ThreaingUtil(ActionSignalMast* action, ActionSignalMastSwing* asms){
   this->action = action;
   this->asms = asms;
  }
  void run()
  {
   asms->setAspectComboBox(action);
  }
};
#endif // ACTIONSIGNALMASTSWING_H
