#ifndef ACTIONLOCALVARIABLESWING_H
#define ACTIONLOCALVARIABLESWING_H

#include "abstractdigitalactionswing.h"

class BeanSelectPanel;
class JTabbedPane;
class ActionLocalVariableSwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ActionLocalVariableSwing(QObject *parent = nullptr);
  ~ActionLocalVariableSwing() {}
  ActionLocalVariableSwing(const ActionLocalVariableSwing&) : AbstractDigitalActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;


  QObject* sself() override {return (QObject*)this;}

 private:
  /*private*/ JTextField* _localVariableTextField;

  /*private*/ JTabbedPane* _tabbedPaneVariableOperation;
  /*private*/ BeanSelectPanel/*<Memory>*/* _copyMemoryBeanPanel;
  /*private*/ JPanel* _setToNull;
  /*private*/ JPanel* _setToConstant;
  /*private*/ JPanel* _copyMemory;
  /*private*/ JPanel* _copyVariable;
  /*private*/ JPanel* _calculateFormula;
  /*private*/ JPanel* _copyTableCell;
  /*private*/ JTextField* _setToConstantTextField;
  /*private*/ JTextField* _copyLocalVariableTextField;
  /*private*/ JTextField* _calculateFormulaTextField;
  /*private*/ JTextField* _copyTableCellTextField;

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel);

};
Q_DECLARE_METATYPE(ActionLocalVariableSwing)
#endif // ACTIONLOCALVARIABLESWING_H
