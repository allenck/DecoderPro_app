#ifndef ACTIONENTRYEXITSWING_H
#define ACTIONENTRYEXITSWING_H

#include "abstractdigitalactionswing.h"

class JComboBox;
class JTabbedPane;
class BeanSelectPanel;
class ActionEntryExitSwing : public AbstractDigitalActionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionEntryExitSwing(QObject *parent = nullptr);
    ~ActionEntryExitSwing() {}
    ActionEntryExitSwing(const ActionEntryExitSwing&) : AbstractDigitalActionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object)override;
    /*public*/ QString toString()override;
    /*public*/ void dispose()override;


private:
    /*private*/ JTabbedPane* _tabbedPaneEntryExit;
    /*private*/ BeanSelectPanel/*<DestinationPoints>*/* entryExitBeanPanel;
    /*private*/ JPanel* _panelEntryExitDirect;
    /*private*/ JPanel* _panelEntryExitReference;
    /*private*/ JPanel* _panelEntryExitLocalVariable;
    /*private*/ JPanel* _panelEntryExitFormula;
    /*private*/ JTextField* _entryExitReferenceTextField;
    /*private*/ JTextField* _entryExitLocalVariableTextField;
    /*private*/ JTextField* _entryExitFormulaTextField;

    /*private*/ JTabbedPane* _tabbedPaneOperation;
    /*private*/ JComboBox/*<Operation>*/* _stateComboBox;
    /*private*/ JPanel* _panelOperationDirect;
    /*private*/ JPanel* _panelOperationReference;
    /*private*/ JPanel* _panelOperationLocalVariable;
    /*private*/ JPanel* _panelOperationFormula;
    /*private*/ JTextField* _entryExitLockReferenceTextField;
    /*private*/ JTextField* _entryExitLockLocalVariableTextField;
    /*private*/ JTextField* _entryExitLockFormulaTextField;

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

};
Q_DECLARE_METATYPE(ActionEntryExitSwing)
#endif // ACTIONENTRYEXITSWING_H
