#ifndef EXPRESSIONCONDITIONALSWING_H
#define EXPRESSIONCONDITIONALSWING_H

#include "abstractdigitalexpressionswing.h"

class JComboBox;
class JTabbedPane;
class BeanSelectPanel;
class ExpressionConditionalSwing : public AbstractDigitalExpressionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ExpressionConditionalSwing(QObject *parent = nullptr);
    ~ExpressionConditionalSwing() {}
    ExpressionConditionalSwing(const ExpressionConditionalSwing&) :AbstractDigitalExpressionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object)override;
    /*public*/ QString toString()override;
    /*public*/ void dispose()override;

    QObject* sself() override {return this;}

private:
    /*private*/ JTabbedPane* _tabbedPaneConditional;
    /*private*/ BeanSelectPanel/*<Conditional>*/* _conditionalBeanPanel;
    /*private*/ JPanel* _panelConditionalDirect;
    /*private*/ JPanel* _panelConditionalReference;
    /*private*/ JPanel* _panelConditionalLocalVariable;
    /*private*/ JPanel* _panelConditionalFormula;
    /*private*/ JTextField* _conditionalReferenceTextField;
    /*private*/ JTextField* _conditionalLocalVariableTextField;
    /*private*/ JTextField* _conditionalFormulaTextField;

    /*private*/ JComboBox/*<Is_IsNot_Enum>*/* _is_IsNot_ComboBox;

    /*private*/ JTabbedPane* _tabbedPaneConditionalState;
    /*private*/ JComboBox/*<ExpressionConditional.ConditionalState>*/* _stateComboBox;
    /*private*/ JPanel* _panelConditionalStateDirect;
    /*private*/ JPanel* _panelConditionalStateReference;
    /*private*/ JPanel* _panelConditionalStateLocalVariable;
    /*private*/ JPanel* _panelConditionalStateFormula;
    /*private*/ JTextField* _conditionalStateReferenceTextField;
    /*private*/ JTextField* _conditionalStateLocalVariableTextField;
    /*private*/ JTextField* _conditionalStateFormulaTextField;
    JPanel* panel;

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

};
Q_DECLARE_METATYPE(ExpressionConditionalSwing)
#endif // EXPRESSIONCONDITIONALSWING_H
