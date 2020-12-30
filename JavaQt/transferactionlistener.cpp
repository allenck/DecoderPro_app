#include "transferactionlistener.h"
#include "vptr.h"
#include "QAction"
/**
 * A class that tracks the focused component. This is necessary to delegate the
 * menu cut/copy/paste commands to the right component. An instance of this
 * class is listening and when the user fires one of these commands, it calls
 * the appropriate action on the currently focused component.
 */
///*public*/ class TransferActionListener implements ActionListener,
//        PropertyChangeListener {


    /*public*/ TransferActionListener::TransferActionListener(QObject *parent) {
#if 0
        KeyboardFocusManager manager = KeyboardFocusManager.
                getCurrentKeyboardFocusManager();
        manager.addPropertyChangeListener("permanentFocusOwner", this);
#endif
    }

    //@Override
    /*public*/ void TransferActionListener::propertyChange(PropertyChangeEvent* e) {
        QVariant o = e->getNewValue();
#if 0
        if (o instanceof JComponent) {
            focusOwner = (JComponent) o;
        } else {
            focusOwner = nullptr;
        }
#endif
    }

    //@Override
    /*public*/ void TransferActionListener::actionPerformed(JActionEvent* e) {
        if (focusOwner == nullptr) {
            return;
        }
        QString action = ((QAction*)QObject::sender())->text();//e.getActionCommand();
#if 0
        Action a = focusOwner.getActionMap().get(action);
        if (a != null) {
            a.actionPerformed(new ActionEvent(focusOwner,
                    ActionEvent.ACTION_PERFORMED,
                    null));
        }
#endif
    }
