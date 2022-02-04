#ifndef ACTIONSIGNALHEADSWING_H
#define ACTIONSIGNALHEADSWING_H

#include "swingconfiguratorinterface.h"
#include "jtextfield.h"
#include "jtabbedpane.h"
#include "beanselectpanel.h"
#include "jcombobox.h"
#include "abstractdigitalactionswing.h"

class ActionSignalHeadSwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  ActionSignalHeadSwing(QObject* parent = nullptr) : AbstractDigitalActionSwing(){}
  /*public*/  static /*final*/ int NUM_COLUMNS_TEXT_FIELDS;// = 20;
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

};

#endif // ACTIONSIGNALHEADSWING_H
