#include "copyrostergroupaction.h"
#include "roster.h"
#include "inputdialog.h"
#include <QMessageBox>

CopyRosterGroupAction::CopyRosterGroupAction(QObject *parent) :
  JmriAbstractAction(parent)
{
 common();
}
/**
 * Duplicate roster group.
 * <p>
 * This action prevents a user from creating a new roster group with the same
 * name as an existing roster group.
 * <p>
 * If performAction(event) is being called in a context where the name of the
 * group to be duplicated is already known, call setContext(groupName) prior to
 * calling performAction(event) to bypass the group selection dialog.
 *
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
 * @author	Kevin Dickerson Copyright (C) 2009
 * @version	$Revision: 28771 $
 */
///*public*/ class CopyRosterGroupAction extends JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -3490415977207449861L;

/*public*/ CopyRosterGroupAction::CopyRosterGroupAction(QString s, WindowInterface* wi):
  JmriAbstractAction(s, wi){
    //super(s, wi);
 common();
}

/*public*/ CopyRosterGroupAction::CopyRosterGroupAction(QString s, QIcon i, WindowInterface* wi) :
  JmriAbstractAction(s, i, wi){
    //super(s, i, wi);
 common();
}

/**
 * @param s   Name of this action, e.g. in menus
 * @param who Component that action is associated with, used to ensure
 *            proper position in of dialog boxes
 */
/*public*/ CopyRosterGroupAction::CopyRosterGroupAction(QString s, QWidget* who):
  JmriAbstractAction(s, who) {
    //super(s);
 common();
    _who = who;
}
void CopyRosterGroupAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/**
 * Call setParameter("group", oldName) prior to calling
 * actionPerformed(event) to bypass the roster group selection dialog if the
 * name of the group to be copied is already known and is not the
 * selectedRosterGroup property of the WindowInterface.
 *
 * @param event
 */
//@Override
/*public*/ void CopyRosterGroupAction::actionPerformed(ActionEvent* event) {
    QString group = NULL;
    // only query wi for group if group was not set using setParameter
    // prior to call
//    if (Beans.hasProperty(wi, "selectedRosterGroup")) {
//        group = (String) Beans.getProperty(wi, "selectedRosterGroup");
//    }
    // NULL might be valid output from getting the selectedRosterGroup,
    // so we have to check for NULL again.
    if (group == NULL)
    {
//        group = (String) JOptionPane.showInputDialog(_who,
//                "<html><b>Duplicate roster group</b><br>Select the roster group to duplicate.</html>",
//                "Duplicate Roster Group",
//                JOptionPane.INFORMATION_MESSAGE,
//                NULL,
//                Roster.instance().getRosterGroupList().toArray(),
//                NULL);
     InputDialog dlg(tr("<html><b>Duplicate roster group</b><br>Select the roster group to duplicate.</html>"),group,NULL, _who);
     dlg.setWindowTitle(tr("Duplicate Roster Group"));
     if(dlg.exec() == QDialog::Accepted)
      group = dlg.value();
    }
    // don't duplicate the NULL and ALLENTRIES groups (they are the entire roster)
    if (group == NULL || group==(Roster::ALLENTRIES)) {
        return;
    }

//    QString entry = (String) JOptionPane.showInputDialog(_who,
//            "<html><b>Duplicate roster group</b><br>Enter the name for the new roster group.</html>",
//            "Duplicate Roster Group " + group,
//            JOptionPane.INFORMATION_MESSAGE,
//            NULL,
//            NULL,
//            NULL);
    QString entry;
    InputDialog dlg(tr("<html><b>Duplicate roster group</b><br>Enter the name for the new roster group.</html>"),"",NULL);
    dlg.setWindowTitle("Duplicate Roster Group " + group);
    if(dlg.exec() == QDialog::Accepted)
     entry = dlg.value();
    if (entry == NULL || entry==(Roster::ALLENTRIES))
    {
     return;
    }
    else if (Roster::instance()->getRosterGroupList().contains(entry))
    {
//        JOptionPane.showMessageDialog(_who,
//                "<html><b>Unable to duplicate roster group</b><br>The roster group named \"" + entry + "\" already exists.",
//                "Duplicate Roster Group " + group,
//                JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(_who, tr("Duplicate Roster Group ")+group, tr("<html><b>Unable to duplicate roster group</b><br>The roster group named \"") + entry + tr("\" already exists."));
    }

    // rename the roster grouping
    Roster::instance()->copyRosterGroupList(group, entry);
    Roster::writeRosterFile();
}

// never invoked, because we overrode actionPerformed above
//@Override
/*public*/ JmriPanel* CopyRosterGroupAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
