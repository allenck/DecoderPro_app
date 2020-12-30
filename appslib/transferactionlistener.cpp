#include "transferactionlistener.h"
#include "propertychangeevent.h"
#include "vptr.h"
#include "jcomponent.h"

/**
 * A class that tracks the focused component. This is necessary to delegate the
 * menu cut/copy/paste commands to the right component. An instance of this
 * class is listening and when the user fires one of these commands, it calls
 * the appropriate action on the currently focused component.
 */
///*public*/ class TransferActionListener implements ActionListener,
//        PropertyChangeListener {


    /*public*/ TransferActionListener::TransferActionListener() {
//        KeyboardFocusManager manager = KeyboardFocusManager.
//                getCurrentKeyboardFocusManager();
//        manager.addPropertyChangeListener("permanentFocusOwner", this);
    }

    //@Override
    /*public*/ void TransferActionListener::propertyChange(PropertyChangeEvent* e) {
        QVariant v = e->getNewValue();
        JComponent*  o = VPtr<JComponent>::asPtr(v);
        if (qobject_cast<JComponent*>(o->jself())) {
            focusOwner = (JComponent*) o;
        } else {
            focusOwner = nullptr;
        }
    }

    //@Override
    /*public*/ void TransferActionListener::actionPerformed(JActionEvent* e) {
        if (focusOwner == nullptr) {
            return;
        }
        QObject* o = QObject::sender();
#if 0
        QString action = e->getActionCommand();
        QAction* a = focusOwner->getActionMap().get(action);
        if (a != nullptr) {
            a.actionPerformed(new ActionEvent(focusOwner,
                    ActionEvent.ACTION_PERFORMED,
                    null));
        }
#endif
    }
