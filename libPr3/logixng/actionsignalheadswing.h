#ifndef ACTIONSIGNALHEADSWING_H
#define ACTIONSIGNALHEADSWING_H

#include "swingconfiguratorinterface.h"
#include "jtextfield.h"
#include "jtabbedpane.h"
#include "beanselectpanel.h"
#include "jcombobox.h"
#include "abstractdigitalactionswing.h"
#include "threadingutil.h"

class ActionSignalHead;
class ActionSignalHeadSwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE ActionSignalHeadSwing(QObject* parent = nullptr) : AbstractDigitalActionSwing(){ setObjectName("ActionSignalHeadSwing");}
  ~ActionSignalHeadSwing() {}
  ActionSignalHeadSwing(const ActionSignalHeadSwing&) : AbstractDigitalActionSwing() {}
  /*public*/  static /*final*/ int NUM_COLUMNS_TEXT_FIELDS;// = 20;
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages);
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object);
  /*public*/  QString toString()override;
  /*public*/  void dispose();

  QObject* sself() override{return (QObject*)this;
                           }
 private:
  /*private*/ JTabbedPane* _tabbedPaneSignalHead;
  /*private*/ BeanSelectPanel/*<SignalHead>*/* _signalHeadBeanPanel;
  /*private*/ JPanel* _panelSignalHeadDirect;
  /*private*/ JPanel* _panelSignalHeadReference;
  /*private*/ JPanel* _panelSignalHeadLocalVariable;
  /*private*/ JPanel* _panelSignalHeadFormula;
  /*private*/ JTextField* _signalHeadReferenceTextField;
  /*private*/ JTextField* _signalHeadLocalVariableTextField;
  /*private*/ JTextField* _signalHeadFormulaTextField;

  /*private*/ JTabbedPane* _tabbedPaneOperationType;
  /*private*/ JPanel* _panelOperationTypeDirect;
  /*private*/ JPanel* _panelOperationTypeReference;
  /*private*/ JPanel* _panelOperationTypeLocalVariable;
  /*private*/ JPanel* _panelOperationTypeFormula;

  /*private*/ JComboBox/*<ActionSignalHead.OperationType>*/* _operationComboBox;
  /*private*/ JTextField* _signalHeadOperationReferenceTextField;
  /*private*/ JTextField* _signalHeadOperationLocalVariableTextField;
  /*private*/ JTextField* _signalHeadOperationFormulaTextField;

  /*private*/ JTabbedPane* _tabbedPaneAppearanceType;
  /*private*/ JPanel* _panelAppearanceTypeDirect;
  /*private*/ JPanel* _panelAppearanceTypeReference;
  /*private*/ JPanel* _panelAppearanceTypeLocalVariable;
  /*private*/ JPanel* _panelAppearanceTypeFormula;

  /*private*/ JComboBox/*<SignalHeadAppearance>*/* _signalHeadAppearanceComboBox;
  /*private*/ JTextField* _signalHeadAppearanceReferenceTextField;
  /*private*/ JTextField* _signalHeadAppearanceLocalVariableTextField;
  /*private*/ JTextField* _signalHeadAppearanceFormulaTextField;

  /*private*/ BeanSelectPanel/*<SignalHead>*/* _exampleSignalHeadBeanPanel;
  /*private*/ void setGuiEnabledStates();
  /*private*/ void setAppearanceComboBox(ActionSignalHead* action);
  /*private*/ /*static*/ class SignalHeadAppearance {

      /*private*/ int _state;
      /*private*/ QString _name;
 public:
      //@Override
      /*public*/  QString toString() {
          return _name;
      }
   friend class ActionSignalHeadSwing;
  };
 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;
 friend class ActionSignalHeadSwing_run;
};
Q_DECLARE_METATYPE(ActionSignalHeadSwing)

class ActionSignalHeadSwing_run : public ThreadAction
{
  Q_OBJECT
  ActionSignalHeadSwing* act;
  ActionSignalHead* action;
 public:
  ActionSignalHeadSwing_run(ActionSignalHead* action, ActionSignalHeadSwing* act ) {this->action =action, this->act = act;}
  void run()
  {
   act->setAppearanceComboBox(action);
  }
};

#endif // ACTIONSIGNALHEADSWING_H
