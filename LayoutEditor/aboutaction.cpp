#include "aboutaction.h"
#include "aboutdialog.h"
/**
 *
 * @author Randall Wood Copyright 2020
 */
///*public*/ class AboutAction extends JmriAbstractAction {

    /*public*/ AboutAction::AboutAction(QString s, WindowInterface* wi) : JmriAbstractAction(s, wi) {
        //super(s, wi);
    }

    /*public*/ AboutAction::AboutAction(QString s, QIcon i, WindowInterface* wi) : JmriAbstractAction(s, i, wi){
        //super(s, i, wi);
    }

    /*public*/ AboutAction::AboutAction(QObject* parent) : JmriAbstractAction("About", parent){
        //super("About");
    }

    //@Override
    /*public*/ void AboutAction::actionPerformed(JActionEvent* e) {
        (new AboutDialog(nullptr, true))->setVisible(true);
    }

    // never invoked, because we overrode actionPerformed above
    //@Override
    /*public*/ JmriPanel* AboutAction::makePanel() {
        throw  IllegalArgumentException("Should not be invoked");
    }
