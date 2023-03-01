#include "actionupdateslotsswing.h"
#include "borderfactory.h"
#include "jcombobox.h"
#include "logixng/actionupdateslots.h"
#include "instancemanager.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "vptr.h"

ActionUpdateSlotsSwing::ActionUpdateSlotsSwing(QObject *parent)
    : AbstractDigitalActionSwing(parent)
{

}

/**
 * Configures an ExpressionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
// /*public*/ class ActionUpdateSlotsSwing extends AbstractDigitalActionSwing {


    //@Override
    /*protected*/ void ActionUpdateSlotsSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        if ((object != nullptr) && !(qobject_cast<ActionUpdateSlots*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ActionUpdateSlots but is a: ")+object->bself()->metaObject()->className());
        }

        ActionUpdateSlots* action = nullptr;
        if(object) action = (ActionUpdateSlots*)object->bself();

        panel = new JPanel();
        panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));

        JPanel* queryPanel = new JPanel(new FlowLayout);
        queryPanel->setBorder(BorderFactory::createLineBorder(Qt::black));

        JPanel* locoNetPanel = new JPanel(new FlowLayout);
        locoNetPanel->layout()->addWidget(new JLabel(tr("LocoNet connection")));

        _locoNetConnection = new JComboBox();
        QList<QObject*>* systemConnections =
                InstanceManager::getList("LocoNetSystemConnectionMemo");
        for (QObject* obj : *systemConnections) {
            LocoNetSystemConnectionMemo* connection = (LocoNetSystemConnectionMemo*)obj;
            LocoNetConnection* c = new LocoNetConnection(connection);
            _locoNetConnection->addItem(c->toString(), VPtr<LocoNetConnection>::asQVariant(c));
            if ((action != nullptr) && (action->getMemo() == connection)) {
                _locoNetConnection->setSelectedItem(VPtr<LocoNetConnection>::asQVariant(c));
            }
        }
        locoNetPanel->layout()->addWidget(_locoNetConnection);

        panel->layout()->addWidget(locoNetPanel);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ActionUpdateSlotsSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* ActionUpdateSlotsSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        LocoNetSystemConnectionMemo* memo =
                VPtr<LocoNetSystemConnectionMemo>::asPtr(_locoNetConnection->getItemAt(_locoNetConnection->getSelectedIndex()));

        ActionUpdateSlots* action = new ActionUpdateSlots(systemName, userName, memo);
        updateObject(action);

        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionUpdateSlotsSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionUpdateSlots*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ExpressionTurnout but is a: ")+object->bself()->metaObject()->className());
        }

        ActionUpdateSlots* action = (ActionUpdateSlots*)object->bself();

        action->setMemo(VPtr<LocoNetSystemConnectionMemo>::asPtr(_locoNetConnection->getItemAt(_locoNetConnection->getSelectedIndex())));
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ActionUpdateSlotsSwing::toString() {
        return tr("ActionUpdateSlots");
    }

    //@Override
    /*public*/ void ActionUpdateSlotsSwing::dispose() {
    }




