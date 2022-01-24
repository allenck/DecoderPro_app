#include "ctceditoraction.h"
#include "instancemanager.h"
#include "frmmainform.h"

/**
 * Swing action to create and register a CtcEditor.
 *
 * @author Dave Sand Copyright (C) 2019
 */
///*public*/ class CtcEditorAction extends JmriAbstractAction {

    /*public*/ CtcEditorAction::CtcEditorAction(QString s, QObject* parent) : JmriAbstractAction(s, parent){
        //super(s);
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed(/*ActionEvent**/)));
    }

    /*public*/ CtcEditorAction::CtcEditorAction(QObject *parent) : JmriAbstractAction(tr("CTC Editor..."), parent) {
        //this(Bundle.getMessage("CtcEditorActionButton"));  // NOI18N
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed(/*ActionEvent**/)));
    }

    //@Override
    /*public*/ void CtcEditorAction::actionPerformed(/*ActionEvent e*/) {
     FrmMainForm* f = (FrmMainForm*)
        InstanceManager::getOptionalDefault("FrmMainForm");//.orElseGet(() -> new FrmMainForm())
     if(f == nullptr)
      f = new FrmMainForm();
      f->setVisible(true);
    }

    // never invoked, because we overrode actionPerformed above
    //@Override
    /*public*/ JmriPanel* CtcEditorAction::makePanel() {
        throw  IllegalArgumentException("Should not be invoked");  // NOI18N
    }
