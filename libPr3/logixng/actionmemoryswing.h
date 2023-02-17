#ifndef ACTIONMEMORYSWING_H
#define ACTIONMEMORYSWING_H

#include "abstractdigitalactionswing.h"

class JTabbedPane;
class BeanSelectPanel;
class ActionMemorySwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  ActionMemorySwing(QObject*parent = nullptr);
  ~ActionMemorySwing() {}
  ActionMemorySwing(const ActionMemorySwing&) : AbstractDigitalActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  void validateDataSection(/*@Nonnull*/ QList<QString>* errorMessages);
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString() override;
  /*public*/  void dispose() ;

  QObject* sself() override {return this;}

 private:
  /*private*/ JTabbedPane* _tabbedPaneMemory;
  /*private*/ BeanSelectPanel/*<Memory>*/* _memoryBeanPanel;
  /*private*/ JPanel* _panelMemoryDirect;
  /*private*/ JPanel* _panelMemoryReference;
  /*private*/ JPanel* _panelMemoryLocalVariable;
  /*private*/ JPanel* _panelMemoryFormula;
  /*private*/ JTextField* _memoryReferenceTextField;
  /*private*/ JTextField* _memoryLocalVariableTextField;
  /*private*/ JTextField* _memoryFormulaTextField;

  /*private*/ JTabbedPane* _tabbedPaneMemoryOperation;
  /*private*/ BeanSelectPanel/*<Memory>*/* _copyMemoryBeanPanel;
  /*private*/ JPanel* _setToNull;
  /*private*/ JPanel* _setToConstant;
  /*private*/ JPanel* _copyMemory;
  /*private*/ JPanel* _copyTableCell;
  /*private*/ JPanel* _copyVariable;
  /*private*/ JPanel* _calculateFormula;
  /*private*/ JTextField* _setToConstantTextField;
  /*private*/ JTextField* _copyTableCellTextField;
  /*private*/ JTextField* _copyLocalVariableTextField;
  /*private*/ JTextField* _calculateFormulaTextField;
  /*private*/ void validateMemorySection(/*@Nonnull*/ QList<QString>* errorMessages);


 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ActionMemorySwing)
#endif // ACTIONMEMORYSWING_H
