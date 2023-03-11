#ifndef EXPRESSIONWARRANTSWING_H
#define EXPRESSIONWARRANTSWING_H

#include "abstractdigitalexpressionswing.h"

class JComboBox;
class JTabbedPane;
class JTextField;
class BeanSelectPanel;
class ExpressionWarrantSwing : public AbstractDigitalExpressionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ExpressionWarrantSwing(QObject *parent = nullptr);
    ~ExpressionWarrantSwing() {}
    ExpressionWarrantSwing(const ExpressionWarrantSwing&) : AbstractDigitalExpressionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ QString getAutoSystemName()override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object)override;
    /*public*/ QString toString()override;
    /*public*/ void dispose() override;

    QObject* sself() override {return this;}

private:
    /*private*/ JTabbedPane* _tabbedPaneWarrant;
    /*private*/ BeanSelectPanel/*<Warrant>*/* warrantBeanPanel;
    /*private*/ JPanel* _panelWarrantDirect;
    /*private*/ JPanel* _panelWarrantReference;
    /*private*/ JPanel* _panelWarrantLocalVariable;
    /*private*/ JPanel* _panelWarrantFormula;
    /*private*/ JTextField* _warrantReferenceTextField;
    /*private*/ JTextField* _warrantLocalVariableTextField;
    /*private*/ JTextField* _warrantFormulaTextField;

    /*private*/ JComboBox/*<Is_IsNot_Enum>*/* _is_IsNot_ComboBox;

    /*private*/ JTabbedPane* _tabbedPaneWarrantState;
    /*private*/ JComboBox/*<WarrantState>*/* _stateComboBox;
    /*private*/ JPanel* _panelWarrantStateDirect;
    /*private*/ JPanel* _panelWarrantStateReference;
    /*private*/ JPanel* _panelWarrantStateLocalVariable;
    /*private*/ JPanel* _panelWarrantStateFormula;
    /*private*/ JTextField* _warrantStateReferenceTextField;
    /*private*/ JTextField* _warrantStateLocalVariableTextField;
    /*private*/ JTextField* _warrantStateFormulaTextField;

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

};
Q_DECLARE_METATYPE(ExpressionWarrantSwing)
#endif // EXPRESSIONWARRANTSWING_H
