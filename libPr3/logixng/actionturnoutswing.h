#ifndef ACTIONTURNOUTSWING_H
#define ACTIONTURNOUTSWING_H

#include "abstractdigitalactionswing.h"

class JComboBox;
class JTabbedPane;
class BeanSelectPanel;
class ActionTurnoutSwing : public AbstractDigitalActionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionTurnoutSwing(QObject *parent = nullptr);
    ~ActionTurnoutSwing() {}
    ActionTurnoutSwing(const ActionTurnoutSwing&) : AbstractDigitalActionSwing() {}

    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object)override;
    /*public*/ QString toString()override;
    /*public*/ void dispose()override;

    QObject* sself() override{return this;}

private:
    /*private*/ JTabbedPane* _tabbedPaneTurnout;
    /*private*/ BeanSelectPanel/*<Turnout>*/* turnoutBeanPanel;
    /*private*/ JPanel* _panelTurnoutDirect;
    /*private*/ JPanel* _panelTurnoutReference;
    /*private*/ JPanel* _panelTurnoutLocalVariable;
    /*private*/ JPanel* _panelTurnoutFormula;
    /*private*/ JTextField* _turnoutReferenceTextField;
    /*private*/ JTextField* _turnoutLocalVariableTextField;
    /*private*/ JTextField* _turnoutFormulaTextField;

    /*private*/ JTabbedPane* _tabbedPaneTurnoutState;
    /*private*/ JComboBox/*<TurnoutState>*/* _stateComboBox;
    /*private*/ JPanel* _panelTurnoutStateDirect;
    /*private*/ JPanel* _panelTurnoutStateReference;
    /*private*/ JPanel* _panelTurnoutStateLocalVariable;
    /*private*/ JPanel* _panelTurnoutStateFormula;
    /*private*/ JTextField* _turnoutStateReferenceTextField;
    /*private*/ JTextField* _turnoutStateLocalVariableTextField;
    /*private*/ JTextField* _turnoutStateFormulaTextField;

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

};
Q_DECLARE_METATYPE(ActionTurnoutSwing)
#endif // ACTIONTURNOUTSWING_H
