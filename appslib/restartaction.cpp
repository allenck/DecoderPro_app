#include "restartaction.h"
#include "loggerfactory.h"
#include "actionevent.h"
#include "apps.h"

/**
 * Simple AbstractAction class that can be invoked to restart JMRI
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author Matthew Harris Copyright (C) 2011
 */
///*public*/ class RestartAction extends JmriAbstractAction {

/*public*/ RestartAction::RestartAction(QString s, WindowInterface* wi) : JmriAbstractAction(s, wi)
{
    //super(s, wi);
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ RestartAction::RestartAction(QString s, QIcon i, WindowInterface* wi) : JmriAbstractAction(s,i,wi)
{
    //super(s, i, wi);
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ RestartAction::RestartAction(QObject* parent) : JmriAbstractAction(tr("Restart Action"), parent){
    //super(Bundle.getMessage("RestartAction")); // NOI18N
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void RestartAction::actionPerformed(ActionEvent* /*e*/) {

    //log->debug(tr("Source: %1; class: %2").arg(*e->getSource(), e->getSource()->metaObject()->className());

    // Don't actually do this if launched as a start-up action
    // as we'll be in an endless loop
#if 0
    if (qobject_cast<QString*>(e->getSource()) != NULL && (!e->getSource() == ("prefs"))) {
        Apps::handleRestart();
    } else {
        log->warn("RestartAction called in error - this should not be done...");
    }
#endif
}

// never invoked, because we overrode actionPerformed above
//@Override
/*public*/ JmriPanel* RestartAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}

/*private*/ /*static*/ /*final*/ Logger* RestartAction::log = LoggerFactory::getLogger("RestartAction");
