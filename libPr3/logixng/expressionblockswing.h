#ifndef EXPRESSIONBLOCKSWING_H
#define EXPRESSIONBLOCKSWING_H

#include "abstractdigitalexpressionswing.h"

class JTabbedPane;
class BeanSelectPanel;
class JComboBox;
class ExpressionBlockSwing : public AbstractDigitalExpressionSwing
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit ExpressionBlockSwing(QObject *parent = nullptr);
    ~ExpressionBlockSwing() {}
    ExpressionBlockSwing(const ExpressionBlockSwing&) : AbstractDigitalExpressionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ QString getAutoSystemName()override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object) override;
    /*public*/ QString toString()override;
    /*public*/ void dispose()override;

    QObject* sself() override {return this;}
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

    /*private*/ JComboBox/*<Is_IsNot_Enum>*/* _is_IsNot_ComboBox;

    /*private*/ JTabbedPane* _tabbedPaneBlockState;
    /*private*/ JComboBox/*<BlockState>*/* _stateComboBox;
    /*private*/ JPanel* _panelBlockStateDirect;
    /*private*/ JPanel* _panelBlockStateReference;
    /*private*/ JPanel* _panelBlockStateLocalVariable;
    /*private*/ JPanel* _panelBlockStateFormula;
    /*private*/ JTextField* _blockStateReferenceTextField;
    /*private*/ JTextField* _blockStateLocalVariableTextField;
    /*private*/ JTextField* _blockStateFormulaTextField;

    /*private*/ JTabbedPane* _tabbedPaneBlockData;
    /*private*/ JPanel* _panelBlockDataDirect;
    /*private*/ JPanel* _panelBlockDataReference;
    /*private*/ JPanel* _panelBlockDataLocalVariable;
    /*private*/ JPanel* _panelBlockDataFormula;
    /*private*/ JTextField* _blockDataDirectTextField;
    /*private*/ JTextField* _blockDataReferenceTextField;
    /*private*/ JTextField* _blockDataLocalVariableTextField;
    /*private*/ JTextField* _blockDataFormulaTextField;
    /*private*/ void validateBlockSection(QList<QString>* errorMessages);
    /*private*/ void validateStateSection(QList<QString>* errorMessages);
    /*private*/ void setDataPanelState();
    /*private*/ void validateDataSection(QList<QString>* errorMessages) ;

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;


};
Q_DECLARE_METATYPE(ExpressionBlockSwing)
#endif // EXPRESSIONBLOCKSWING_H
