#include "createrostergroupaction.h"
#include <QMessageBox>
#include "roster.h"
#include "jmripanel.h"
#include "../../LayoutEditor/inputdialog.h"

CreateRosterGroupAction::CreateRosterGroupAction(QObject *parent) :
    JmriAbstractAction(tr("CreateRoster Group"),parent)
{
 rosterEntries = new QList<RosterEntry*>();
 log = new Logger("CreateRosterGroupAction");
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}
#if 1
/**
 * Create a roster group.
 *
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General public License
 * for more details.
 * <P>
 * @author	Kevin Dickerson   Copyright (C) 2009
 * @version	$Revision: 22006 $
 */
// /*public*/ class CreateRosterGroupAction extends JmriAbstractAction {

/*public*/ CreateRosterGroupAction::CreateRosterGroupAction(QString s, /*WindowInterface* wi,*/ QWidget *parent) :JmriAbstractAction(s,parent){
    //super(s, wi);
    log = new Logger("CreateRosterGroupAction");
    connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

/*public*/ CreateRosterGroupAction::CreateRosterGroupAction(QString s, QIcon i, /*WindowInterface wi,*/ QWidget *parent) : JmriAbstractAction(s, parent) {
    //super(s, i, wi);
    log = new Logger("CreateRosterGroupAction");
    connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}
/**
 * @param s Name of this action, e.g. in menus
 * @param who Component that action is associated with, used
 *              to ensure proper position in of dialog boxes
 */
///*public*/ CreateRosterGroupAction::CreateRosterGroupAction(QString s, QWidget* who) : QAction(s,who)
//{
//    //super(s);
//    _who = who;
//    log = new Logger("CreateRosterGroupAction");
//}


//@Override
/*public*/ void CreateRosterGroupAction::actionPerformed(ActionEvent* event) {

//    QString entry = (String)JOptionPane.showInputDialog(_who,
//                                 "<html><b>"+ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getString("MenuGroupCreate")+"</b></html>",
//                                 ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getString("MenuGroupCreate"),
//                                 JOptionPane.INFORMATION_MESSAGE,
//                                 NULL, // icon
//                                 NULL, // initial values
//                                 NULL);// preselected initial value
    InputDialog* dlg = new InputDialog("<html><b>" + tr("Create Roster Group")+"</b></html>","Create Roster Group");
    dlg->exec();
    QString entry = dlg->value();
    if(entry == "" || entry==(Roster::ALLENTRIES)){
        return;
    }
    if (rosterEntries != NULL)
    {
     foreach (RosterEntry* re, *rosterEntries)
     {
      log->debug("Adding RosterEntry " + re->getId() + " to new group " + entry);
      re->putAttribute(Roster::ROSTER_GROUP_PREFIX + entry, "yes");
      re->updateFile();
     }
    }
    Roster::getDefault()->addRosterGroup(entry);
    Roster::getDefault()->writeRoster();
}

// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* CreateRosterGroupAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}

/**
 * Set a parameter
 * <p>
 * This method accepts the following key, with the following value:
 * <dl>
 * <dt>RosterEntries</dt>
 * <dd>An ArrayList&lt;RosterEntry&gt; of roster entries.
 * </dl>
 * @param key
 * @param value
 */
//    @Override
//    @SuppressWarnings("unchecked")
/*public*/ void CreateRosterGroupAction::setParameter(QString key, QObject* value) {
    if (key==("RosterEntries") && QString(value->metaObject()->className())==("QList")) {
        rosterEntries = (QList<RosterEntry*>*)value;
    }
}
#endif
