#include "whereusedaction.h"
#include "whereusedframe.h"
#include "jmripanel.h"

/**
 * Swing action to create and register a WhereUsedFrame
 *
 * @author Dave Sand Copyright (C) 2020
 */
///*public*/ class WhereUsedAction extends JmriAbstractAction {

    /*public*/ WhereUsedAction::WhereUsedAction(QString s, QObject* parent) : AbstractAction(s, parent) {
        //super(s);
        connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed(/*ActionEvent*/)));
    }

    /*public*/ WhereUsedAction::WhereUsedAction(QObject* parent) : AbstractAction("Where Used", parent) {
        //this("WhereUsed");  // NOI18N
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed(/*ActionEvent*/)));

    }

    //@Override
    /*public*/ void WhereUsedAction::actionPerformed(/*ActionEvent e*/) {
        WhereUsedFrame* f = new WhereUsedFrame();
        f->setVisible(true);
    }

    // never invoked, because we overrode actionPerformed above
    //@Override
    /*public*/ JmriPanel* makePanel() {
        throw IllegalArgumentException("Should not be invoked");  // NOI18N
    }
