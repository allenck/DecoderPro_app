#ifndef ACTIONBLOCKSWING_H
#define ACTIONBLOCKSWING_H

#include "abstractdigitalactionswing.h"

class JComboBox;
class BeanSelectPanel;
class JTabbedPane;
class ActionBlockSwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ActionBlockSwing(QObject *parent = nullptr);
  ~ActionBlockSwing() {}
  ActionBlockSwing(const ActionBlockSwing&) : AbstractDigitalActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages) ;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}
 private:
  /*private*/ JTabbedPane* _tabbedPaneBlock;
  /*private*/ BeanSelectPanel/*<Block>*/* _blockBeanPanel;
  /*private*/ JPanel* _panelBlockDirect;
  /*private*/ JPanel* _panelBlockReference;
  /*private*/ JPanel* _panelBlockLocalVariable;
  /*private*/ JPanel* _panelBlockFormula;
  /*private*/ JTextField* _blockReferenceTextField;
  /*private*/ JTextField* _blockLocalVariableTextField;
  /*private*/ JTextField* _blockFormulaTextField;

  /*private*/ JTabbedPane* _tabbedPaneOperation;
  /*private*/ JComboBox/*<DirectOperation>*/* _stateComboBox;
  /*private*/ JPanel* _panelOperationDirect;
  /*private*/ JPanel* _panelOperationReference;
  /*private*/ JPanel* _panelOperationLocalVariable;
  /*private*/ JPanel* _panelOperationFormula;
  /*private*/ JTextField* _blockOperReferenceTextField;
  /*private*/ JTextField *_blockOperLocalVariableTextField;
  /*private*/ JTextField* _blockOperFormulaTextField;

  /*private*/ JTabbedPane* _tabbedPaneData;
  /*private*/ JPanel* _panelDataDirect;
  /*private*/ JPanel* _panelDataReference;
  /*private*/ JPanel* _panelDataLocalVariable;
  /*private*/ JPanel* _panelDataFormula;
  /*private*/ JTextField* _blockDataDirectTextField;
  /*private*/ JTextField* _blockDataReferenceTextField;
  /*private*/ JTextField* _blockDataLocalVariableTextField;
  /*private*/ JTextField* _blockDataFormulaTextField;
  /*private*/ void setDataPanelState();
  /*private*/ void validateBlockSection(QList<QString>* errorMessages);
  /*private*/ void validateOperationSection(QList<QString>* errorMessages);
  /*private*/ void validateDataSection(QList<QString>* errorMessages);

 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ActionBlockSwing)
#endif // ACTIONBLOCKSWING_H
