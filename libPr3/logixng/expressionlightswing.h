#ifndef EXPRESSIONLIGHTSWING_H
#define EXPRESSIONLIGHTSWING_H

#include "abstractdigitalexpressionswing.h"

class JTabbedPane;
class BeanSelectPanel;
class JComboBox;
class ExpressionLightSwing : public AbstractDigitalExpressionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ExpressionLightSwing(QObject *parent = nullptr);
    ~ExpressionLightSwing() {}
    ExpressionLightSwing(const ExpressionLightSwing&) : AbstractDigitalExpressionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages) override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object)override;
    /*public*/ QString toString()override;
    /*public*/ void dispose() override;

    QObject* sself() override{return this;}

private:
    /*private*/ JTabbedPane* _tabbedPaneLight;
    /*private*/ BeanSelectPanel/*<Light>*/* _lightBeanPanel;
    /*private*/ JPanel* _panelLightDirect;
    /*private*/ JPanel* _panelLightReference;
    /*private*/ JPanel* _panelLightLocalVariable;
    /*private*/ JPanel* _panelLightFormula;
    /*private*/ JTextField* _lightReferenceTextField;
    /*private*/ JTextField* _lightLocalVariableTextField;
    /*private*/ JTextField* _lightFormulaTextField;

    /*private*/ JComboBox/*<Is_IsNot_Enum>*/* _is_IsNot_ComboBox;

    /*private*/ JTabbedPane* _tabbedPaneLightState;
    /*private*/ JComboBox/*<LightState>*/* _stateComboBox;
    /*private*/ JPanel* _panelLightStateDirect;
    /*private*/ JPanel* _panelLightStateReference;
    /*private*/ JPanel* _panelLightStateLocalVariable;
    /*private*/ JPanel* _panelLightStateFormula;
    /*private*/ JTextField* _lightStateReferenceTextField;
    /*private*/ JTextField* _lightStateLocalVariableTextField;
    /*private*/ JTextField* _lightStateFormulaTextField;

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

};
Q_DECLARE_METATYPE(ExpressionLightSwing)
#endif // EXPRESSIONLIGHTSWING_H
