#include "ctcrunaction.h"
#include "instancemanager.h"
#include "ctcmain.h"

/**
 * Swing action to create and register the CTC Run Time.
 * Replaces the original custom file opener.
 *
 * @author Dave Sand Copyright (C) 2019
 */
///*public*/ class CtcRunAction extends JmriAbstractAction {

    /*public*/ CtcRunAction::CtcRunAction(QString s, QWidget *parent) : JmriAbstractAction(s, parent){
        //super(s);
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed(/*ActionEvent**/)));
    }

    /*public*/ CtcRunAction::CtcRunAction(QWidget *parent) : JmriAbstractAction(tr("Run CTC"), parent){
        //this(Bundle.getMessage("CtcRunActionButton"));  // NOI18N
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed(/*ActionEvent**/)));
    }

    //@Override
    /*public*/ void CtcRunAction::actionPerformed(/*ActionEvent e*/) {
        if (InstanceManager::getNullableDefault("CTCMain") != nullptr) {
            // Prevent duplicate copies
            return;
        }
        CTCMain* _mCTCMain = new CTCMain();
        InstanceManager::setDefault("CTCMain", _mCTCMain);
        _mCTCMain->startup();
    }

    // never invoked, because we overrode actionPerformed above
    //@Override
    /*public*/ JmriPanel* CtcRunAction::makePanel() {
        throw  IllegalArgumentException("Should not be invoked");  // NOI18N
    }

