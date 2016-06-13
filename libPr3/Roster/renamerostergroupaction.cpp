#include "renamerostergroupaction.h"
#include "roster.h"
#include <QMessageBox>
#include "inputdialog.h"

RenameRosterGroupAction::RenameRosterGroupAction(QObject *parent) :
  JmriAbstractAction(parent)
{
 common();
}
/**
 * Rename a roster group.
 * <p>
 * This action prevents a user from renaming a roster group to same name as an
 * existing roster group.
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
 * @author Randall Wood Copyright (C) 2011
 * @version	$Revision: 28771 $
 * @see Roster
 */
///*public*/ class RenameRosterGroupAction extends JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -1370317330367764168L;

/*public*/ RenameRosterGroupAction::RenameRosterGroupAction(QString s, WindowInterface* wi) :
  JmriAbstractAction(s, wi){
    //super(s, wi);
 common();
}

/*public*/ RenameRosterGroupAction::RenameRosterGroupAction(QString s, QIcon i, WindowInterface* wi):
  JmriAbstractAction(s, i, wi) {
    //super(s, i, wi);
 common();
}

/**
 * @param s   Name of this action, e.g. in menus
 * @param who Component that action is associated with, used to ensure
 *            proper position in of dialog boxes
 */
/*public*/ RenameRosterGroupAction::RenameRosterGroupAction(QString s, QWidget* who) :
  JmriAbstractAction(s, (WindowInterface*)who)
{
 //super(s);
 _who = who;
 common();
}
void RenameRosterGroupAction::common()
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
/*public*/ void RenameRosterGroupAction::actionPerformed(ActionEvent* event)
{
    QString group = NULL;
//    if (Beans.hasProperty(wi, "selectedRosterGroup")) {
//        group = (String) Beans.getProperty(wi, "selectedRosterGroup");
//    }
    // NULL might be valid output from getting the selectedRosterGroup,
    // so we have to check for NULL again.
    if (group == NULL)
    {
//        group = (String) JOptionPane.showInputDialog(_who,
//                "<html><b>Rename roster group</b><br>Select the roster group to rename.</html>",
//                "Rename Roster Group",
//                JOptionPane.INFORMATION_MESSAGE,
//                NULL,
//                Roster::instance().getRosterGroupList().toArray(),
//                NULL);
     InputDialog dlg(tr("<html><b>Rename roster group</b><br>Select the roster group to rename.</html>"), group, NULL, _who);
     dlg.setWindowTitle(tr("Rename Roster Group"));
     if(dlg.exec() == QDialog::Accepted)
      group = dlg.value();
    }
    // can't rename the groups that represent the entire roster
    if (group == NULL || group==(Roster::ALLENTRIES)) {
        return;
    }

    QString entry;
    //    entry = (String) JOptionPane.showInputDialog(_who,
    //            "<html><b>Rename roster group</b><br>Enter the new name for roster group \"" + group + "\".</html>",
    //            "Rename Roster Group " + group,
    //            JOptionPane.INFORMATION_MESSAGE,
    //            NULL,
    //            NULL,
    //            NULL);
    InputDialog dlg(tr("<html><b>Rename roster group</b><br>Enter the new name for roster group \"") + group + tr("\".</html>"), entry, NULL, _who);
    dlg.setWindowTitle(tr("Rename Roster Group ") + group);
    if(dlg.exec() == QDialog::Accepted)
     entry = dlg.value();
    if (entry == NULL || entry==(Roster::ALLENTRIES))
    {
        return;
    }
    else if (Roster::instance()->getRosterGroupList().contains(entry))
    {
//        JOptionPane.showMessageDialog(_who,
//                "<html><b>Unable to rename roster group</b><br>The roster group named \"" + entry + "\" already exists.",
//                ,
//                JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(_who, tr("Rename Roster Group ") + group, tr("<html><b>Unable to rename roster group</b><br>The roster group named \"") + entry + tr("\" already exists."));
    }

    // rename the roster grouping
    Roster::instance()->renameRosterGroupList(group, entry);
    Roster::writeRosterFile();
}

// never invoked, because we overrode actionPerformed above
//@Override
/*public*/ JmriPanel* RenameRosterGroupAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
