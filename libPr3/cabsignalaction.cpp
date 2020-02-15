#include "cabsignalaction.h"
#include "cabsignalpane.h"
/**
 * Swing action to create and register a CabSignalPanel object.
 *
 * @author Paul Bender Copyright (C) 2003
 */
// /*public*/ class CabSignalAction extends JmriAbstractAction {

    /*public*/ CabSignalAction::CabSignalAction(QString s, WindowInterface* wi) : JmriAbstractAction(s,wi) {
        //super(s, wi);
     connect(this, SIGNAL(triggered(bool)), this, SLOT(makePanel()));
    }

    /*public*/ CabSignalAction::CabSignalAction(QString s, QIcon i, WindowInterface* wi) : JmriAbstractAction(s, i, wi){
        //super(s, i, wi);
        connect(this, SIGNAL(triggered(bool)), this, SLOT(makePanel()));
    }

    /*public*/ CabSignalAction::CabSignalAction(QString s, QObject *parent) : JmriAbstractAction(s,parent){
        //super(s);
        connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
    }

    /*public*/ CabSignalAction::CabSignalAction(QObject *parent) : JmriAbstractAction(tr("Cab Signals"), parent){
        //this(Bundle.getMessage("MenuItemCabSignalPane"));
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
    }

    //@Override
    /*public*/ JmriPanel* CabSignalAction::makePanel() {
       CabSignalPane* retval = new CabSignalPane();
       retval->initComponents();
       return retval;
    }
