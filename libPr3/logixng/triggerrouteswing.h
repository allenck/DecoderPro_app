#ifndef TRIGGERROUTESWING_H
#define TRIGGERROUTESWING_H

#include "abstractdigitalactionswing.h"

class JTabbedPane;
class BeanSelectPanel;
class JComboBox;
class TriggerRouteSwing : public AbstractDigitalActionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TriggerRouteSwing(QObject *parent = nullptr);
    ~TriggerRouteSwing() {}
    TriggerRouteSwing(const TriggerRouteSwing&) : AbstractDigitalActionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object) override;
    /*public*/ QString toString() override;
    /*public*/ void dispose() override;

    QObject* sself() override{return this;}
private:
    /*private*/ JTabbedPane* _tabbedPaneRoute;
    /*private*/ BeanSelectPanel/*<Route>*/* routeBeanPanel;
    /*private*/ JPanel* _panelRouteDirect;
    /*private*/ JPanel* _panelRouteReference;
    /*private*/ JPanel* _panelRouteLocalVariable;
    /*private*/ JPanel* _panelRouteFormula;
    /*private*/ JTextField* _routeReferenceTextField;
    /*private*/ JTextField* _routeLocalVariableTextField;
    /*private*/ JTextField* _routeFormulaTextField;

    /*private*/ JTabbedPane* _tabbedPaneOperation;
    /*private*/ JComboBox/*<Operation>*/* _stateComboBox;
    /*private*/ JPanel* _panelOperationDirect;
    /*private*/ JPanel* _panelOperationReference;
    /*private*/ JPanel* _panelOperationLocalVariable;
    /*private*/ JPanel* _panelOperationFormula;
    /*private*/ JTextField* _routeLockReferenceTextField;
    /*private*/ JTextField* _routeLockLocalVariableTextField;
    /*private*/ JTextField* _routeLockFormulaTextField;

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;


};
Q_DECLARE_METATYPE(TriggerRouteSwing)
#endif // TRIGGERROUTESWING_H
