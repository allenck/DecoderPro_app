#include "actionclearslotsswing.h"
#include "instancemanager.h"
#include "jcombobox.h"
#include "jlabel.h"
#include "logixng/actionclearslots.h"
#include "borderfactory.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "vptr.h"

ActionClearSlotsSwing::ActionClearSlotsSwing(QObject *parent)
    : AbstractDigitalActionSwing{parent}
{

}
/**
 * Configures an ExpressionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
// /*public*/ class ActionClearSlotsSwing extends AbstractDigitalActionSwing {


    //@Override
    /*protected*/ void ActionClearSlotsSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        if ((object != nullptr) && !(qobject_cast<ActionClearSlots*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an ActionClearSlots but is a: ")+object->bself()->metaObject()->className());
        }

        ActionClearSlots* action = nullptr;
        if(object) action = (ActionClearSlots*)object->bself();

        panel = new JPanel();
        panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));

        panel->layout()->addWidget(new JLabel(tr("ActionClearSlotsInfo1")));
        panel->layout()->addWidget(new JLabel(tr("ActionClearSlotsInfo2")));
        panel->layout()->addWidget(new JLabel(tr("ActionClearSlotsInfo3")));
        panel->layout()->addWidget(new JLabel(tr("ActionClearSlotsInfo4")));
        panel->layout()->addWidget(new JLabel(tr("ActionClearSlotsInfo5")));

        JPanel* queryPanel = new JPanel(new FlowLayout);
        queryPanel->setBorder(BorderFactory::createLineBorder(Qt::black));

        JPanel* locoNetPanel = new JPanel(new FlowLayout);
        locoNetPanel->layout()->addWidget(new JLabel(tr("LocoNetConnection")));

        _locoNetConnection = new JComboBox();
        QList<QObject*>* systemConnections =
                InstanceManager::getList("LocoNetSystemConnectionMemo");
        for (QObject* obj : *systemConnections) {
            LocoNetSystemConnectionMemo* connection = (LocoNetSystemConnectionMemo*)obj;
            LocoNetConnection* c = new LocoNetConnection(connection);
            _locoNetConnection->addItem(c->toString(),VPtr<LocoNetConnection>::asQVariant(c));
            if ((action != nullptr) && (action->getMemo() == connection)) {
                _locoNetConnection->setSelectedItem(VPtr<LocoNetConnection>::asQVariant(c));
            }
        }
        locoNetPanel->layout()->addWidget(_locoNetConnection);

        panel->layout()->addWidget(locoNetPanel);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ActionClearSlotsSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* ActionClearSlotsSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        LocoNetSystemConnectionMemo* memo =
                VPtr<LocoNetConnection>::asPtr(_locoNetConnection->getItemAt(_locoNetConnection->getSelectedIndex()))->_memo;

        ActionClearSlots* action = new ActionClearSlots(systemName, userName, memo);
        updateObject(action);

        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionClearSlotsSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionClearSlots*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an ExpressionTurnout but is a: ")+object->bself()->metaObject()->className());
        }

        ActionClearSlots* action = (ActionClearSlots*)object->bself();

        action->setMemo(VPtr<LocoNetConnection>::asPtr(_locoNetConnection->getItemAt(_locoNetConnection->getSelectedIndex()))->_memo);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ActionClearSlotsSwing::toString() {
        return tr("ActionClearSlots");
    }

    //@Override
    /*public*/ void ActionClearSlotsSwing::dispose() {
    }



//    /*private*/ static class LocoNetConnection {

//        /*private*/ LocoNetSystemConnectionMemo _memo;

//        /*public*/ LocoNetConnection(LocoNetSystemConnectionMemo memo) {
//            _memo = memo;
//        }

//        //@Override
//        /*public*/ String toString() {
//            return _memo.getUserName();
//        }
//    }
