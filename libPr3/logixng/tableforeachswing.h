#ifndef TABLEFOREACHSWING_H
#define TABLEFOREACHSWING_H

#include "abstractdigitalactionswing.h"
#include "beanselectpanel.h"
#include "jlabel.h"
#include "jtextfield.h"
#include "jcombobox.h"
#include "jtabbedpane.h"

class TableForEachSwing : public AbstractDigitalActionSwing
{
 public:
  Q_INVOKABLE explicit TableForEachSwing(QObject *parent = nullptr);
  ~TableForEachSwing() {}
  TableForEachSwing(const TableForEachSwing&) : AbstractDigitalActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString> errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull */QString systemName, QString userName);
  /*public*/  void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override {return (QObject*)this;}

 private:
  /*private*/ JTabbedPane* _tabbedTablePane;
  /*private*/ JPanel* _panelTable;
  /*private*/ JPanel* _panelReference;
  /*private*/ JPanel* _panelLocalVariable;
  /*private*/ JPanel* _panelFormula;
  /*private*/ BeanSelectPanel/*<NamedTable>*/* tableBeanPanel;
  /*private*/ JComboBox/*<TableRowOrColumn>*/* _tableRowOrColumnComboBox;
  /*private*/ JTextField* _referenceTextField;
  /*private*/ JTextField* _localVariableTextField;
  /*private*/ JTextField* _formulaTextField;

  /*private*/ JLabel* _panelRowOrColumnLabel;
  /*private*/ JTabbedPane* _tabbedRowOrColumnPane;
  /*private*/ JPanel* _panelRowOrColumnName;
  /*private*/ JPanel* _panelRowOrColumnReference;
  /*private*/ JPanel* _panelRowOrColumnLocalVariable;
  /*private*/ JPanel* _panelRowOrColumnFormula;
  /*private*/ JComboBox/*<String>*/* _rowOrColumnNameComboBox;
  /*private*/ JTextField* _rowOrColumnNameTextField;

  /*private*/ JTextField* _referenceRowOrColumnTextField;
  /*private*/ JTextField* _localRowOrColumnVariableTextField;
  /*private*/ JTextField* _formulaRowOrColumnTextField;

  /*private*/ JTextField* _localVariable;
  /*private*/ void setupRowOrColumnNameComboBox(QString rowOrColumnName);

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(TableForEachSwing)
#endif // TABLEFOREACHSWING_H
