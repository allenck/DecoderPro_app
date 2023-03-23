#ifndef EXPRESSIONOBLOCKSWING_H
#define EXPRESSIONOBLOCKSWING_H

#include "abstractdigitalexpressionswing.h"

class JTabbedPane;
class BeanSelectPanel;
class JComboBox;
class ExpressionOBlockSwing : public AbstractDigitalExpressionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ExpressionOBlockSwing(QObject *parent = nullptr);
    ~ExpressionOBlockSwing() {}
    ExpressionOBlockSwing(const ExpressionOBlockSwing&) : AbstractDigitalExpressionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ QString getAutoSystemName() override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object) override;
    /*public*/ QString toString()override;
    /*public*/ void dispose() override;

    QObject* sself() override {return this;}

  private:
    /*private*/ JTabbedPane* _tabbedPaneOBlock;
    /*private*/ BeanSelectPanel/*<OBlock>*/* oblockBeanPanel;
    /*private*/ JPanel*  _panelOBlockDirect;
    /*private*/ JPanel*  _panelOBlockReference;
    /*private*/ JPanel*  _panelOBlockLocalVariable;
    /*private*/ JPanel*  _panelOBlockFormula;
    /*private*/ JTextField* _oblockReferenceTextField;
    /*private*/ JTextField* _oblockLocalVariableTextField;
    /*private*/ JTextField* _oblockFormulaTextField;

    /*private*/ JComboBox/*<Is_IsNot_Enum>*/* _is_IsNot_ComboBox;

    /*private*/ JTabbedPane* _tabbedPaneOBlockState;
    /*private*/ JComboBox/*<OBlock.OBlockStatus>*/* _stateComboBox;
    /*private*/ JPanel*  _panelOBlockStateDirect;
    /*private*/ JPanel*  _panelOBlockStateReference;
    /*private*/ JPanel*  _panelOBlockStateLocalVariable;
    /*private*/ JPanel*  _panelOBlockStateFormula;
    /*private*/ JTextField* _oblockStateReferenceTextField;
    /*private*/ JTextField* _oblockStateLocalVariableTextField;
    /*private*/ JTextField* _oblockStateFormulaTextField;

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel*  buttonPanel) override;

};
Q_DECLARE_METATYPE(ExpressionOBlockSwing)
#endif // EXPRESSIONOBLOCKSWING_H
