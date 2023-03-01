#ifndef ACTIONTURNOUTLOCKSWING_H
#define ACTIONTURNOUTLOCKSWING_H

#include "abstractdigitalactionswing.h"

class JComboBox;
class JTabbedPane;
class BeanSelectPanel;
class ActionTurnoutLockSwing : public AbstractDigitalActionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionTurnoutLockSwing(QObject *parent = nullptr);
    ~ActionTurnoutLockSwing() {}
    ActionTurnoutLockSwing(const ActionTurnoutLockSwing&) : AbstractDigitalActionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object)override;
    /*public*/ QString toString() override;
    /*public*/ void dispose()override;

    QObject* sself() override {return this;}

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

    /*private*/ JTabbedPane* _tabbedPaneTurnoutLock;
    /*private*/ JComboBox/*<TurnoutLock>*/* _stateComboBox;
    /*private*/ JPanel* _panelTurnoutLockDirect;
    /*private*/ JPanel* _panelTurnoutLockReference;
    /*private*/ JPanel* _panelTurnoutLockLocalVariable;
    /*private*/ JPanel* _panelTurnoutLockFormula;
    /*private*/ JTextField* _turnoutLockReferenceTextField;
    /*private*/ JTextField* _turnoutLockLocalVariableTextField;
    /*private*/ JTextField* _turnoutLockFormulaTextField;

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ActionTurnoutLockSwing)
#endif // ACTIONTURNOUTLOCKSWING_H
