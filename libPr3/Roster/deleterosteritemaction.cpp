#include "deleterosteritemaction.h"
#include "windowinterface.h"
#include "roster.h"
#include "locofile.h"
#include "rosterentry.h"
#include "fileutil.h"
#include "rosterentrycombobox.h"
#include "QMessageBox"
#include "roster.h"
#include "../../LayoutEditor/inputdialog.h"

//DeleteRosterItemAction::DeleteRosterItemAction(QObject *parent) :
//    QAction(parent)
//{
//}
/**
 * Remove a locomotive from the roster.
 *
 * <P>In case of error, this
 * moves the definition file to a backup.  This action posts
 * a dialog box to select the loco to be deleted, and then posts
 * an "are you sure" dialog box before acting.
 *
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 * @author	Bob Jacobsen   Copyright (C) 2001, 2002
 * @version	$Revision: 22547 $
 * @see         jmri.jmrit.XmlFile
 */
// /*public*/ class DeleteRosterItemAction extends JmriAbstractAction {

/*public*/ DeleteRosterItemAction::DeleteRosterItemAction(QString s, WindowInterface* wi)
    : QAction(s, wi)
{
    //super(s, wi);
    log = new Logger("DeleteRosterItemAction");
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ DeleteRosterItemAction::DeleteRosterItemAction(QString s, QIcon i, WindowInterface* wi)
    : QAction(i, s, wi)
{
    //super(s, i, wi);
    log = new Logger("DeleteRosterItemAction");
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}
/**
 * @param s Name of this action, e.g. in menus
 * @param who Component that action is associated with, used
 *              to ensure proper position in of dialog boxes
 */
/*public*/ DeleteRosterItemAction::DeleteRosterItemAction(QString s, QWidget* who)
    : QAction(s, who)
{
    //super(s);
    _who = who;
    log = new Logger("DeleteRosterItemAction");
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}


/*public*/ void DeleteRosterItemAction::actionPerformed(ActionEvent* event)
{

 Roster* roster = Roster::instance();
 QString rosterGroup = Roster::instance()->getDefaultRosterGroup();
 QList<RosterEntry*>* entries;
 // rosterGroup may legitimately be NULL
 // but getProperty returns NULL if the property cannot be found, so
 // we test that the property exists before attempting to get its value
//    if (Beans.hasProperty(wi, "selectedRosterGroup")) {
//        rosterGroup = (String) Beans.getProperty(wi, "selectedRosterGroup");
//    }
//    if (Beans.hasProperty(wi, "selectedRosterEntries")) {
//        entries = (RosterEntry[]) Beans.getProperty(wi, "selectedRosterEntries");
//    }
//    else
 {
  entries = selectRosterEntry(rosterGroup);
 }
 if (entries == NULL)
 {
  return;
 }
 // get parent object if there is one
 //Component parent = NULL;
 //if ( event.getSource() instanceof Component) parent = (Component)event.getSource();

 // find the file for the selected entry
 foreach (RosterEntry* re, *entries)
 {
  QString filename = roster->fileFromTitle(re->titleString());
  QString fullFilename = LocoFile::getFileLocation() + filename;
  if (log->isDebugEnabled())
  {
   log->debug("resolves to \"" + filename + "\", \"" + fullFilename + "\"");
  }

  // prompt for one last chance
  if (rosterGroup == NULL)
  {
   if (!userOK(re->titleString(), filename, fullFilename)) {
       return;
   }
   // delete it from roster
   roster->removeEntry(re);
  }
  else
  {
   QString group = Roster::getRosterGroupProperty(rosterGroup);
   re->deleteAttribute(group);
   re->updateFile();
  }
  Roster::writeRoster();

  // backup the file & delete it
  if (rosterGroup == NULL)
  {
   try
   {
    // ensure preferences will be found
    FileUtil::createDirectory(LocoFile::getFileLocation());

    // do backup
    LocoFile* df = new LocoFile();   // need a dummy object to do this operation in next line
    df->makeBackupFile(LocoFile::getFileLocation() + filename);

    // locate the file and delete
    QFile* f = new QFile(fullFilename);
    if (!f->remove())
    { // delete file and check success
     log->error("failed to delete file \"" + fullFilename + "\"");
    }
   } catch (Exception ex)
   {
    log->error("error during locomotive file output: " + ex.getMessage());
   }
  }
 }
}

/*protected*/ QList<RosterEntry*>* DeleteRosterItemAction::selectRosterEntry(QString rosterGroup){
    // create a dialog to select the roster entry
    QComboBox* selections = new RosterEntryComboBox(rosterGroup);
//    int retval = JOptionPane.showOptionDialog(_who,
//                                              "Select one roster entry", "Delete roster entry",
//                                              0, JOptionPane.INFORMATION_MESSAGE, NULL,
//                                              new Object[]{"Cancel", "OK", selections}, NULL );
//    int retval = QMessageBox::information(_who, tr("Delete roster entry"), tr("Select one  roster entry"), QMessageBox::Cancel | QMessageBox::Ok);
    InputDialog* dlg = new InputDialog(tr("Select one  roster entry"),selections, tr("Delete roster entry"));
    int retval = dlg->exec();
    log->debug("Dialog value "+QString::number(retval)+" selected "+QString::number(selections->currentIndex())+":"
              +selections->currentText());
    if (retval != QDialog::Accepted) return NULL;
    QList<RosterEntry*>* entries = new QList<RosterEntry*>;
    entries->append( (RosterEntry*) Roster::instance()->getEntryForId(selections->currentText()));
    return entries;
}

/**
 * Can provide some mechanism to prompt for user for one
 * last chance to change his/her mind
 * @return true if user says to continue
 */
bool DeleteRosterItemAction::userOK(QString entry, QString filename, QString fullFileName)
{
//    return ( JOptionPane.YES_OPTION ==
//             JOptionPane.showConfirmDialog(_who,
//                    java.text.MessageFormat.format(ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getString("DeletePrompt"),
//                                    entry,fullFileName),
//                    java.text.MessageFormat.format(ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getString("DeleteTitle"),
//                                    entry),
//                    JOptionPane.YES_NO_OPTION));
    return (QMessageBox::question(_who, tr("Delete entry (%1)?").arg(entry), tr("Delete entry (%1) and file (%2)?").arg(entry).arg(fullFileName), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes);
}

// initialize logging
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DeleteRosterItemAction.class.getName());
#if 0
/**
 * Main entry point to run as standalone tool. This doesn't work
 * so well yet:  It should take an optional command line argument,
 * and should terminate when done, or at least let you delete
 * another file.
 */
/*public*/ static void main(String s[]) {

    // initialize log4j - from logging control file (lcf) only
    // if can find it!
    String logFile = "default.lcf";
    try {
        if (new java.io.File(logFile).canRead()) {
            org.apache.log4j.PropertyConfigurator.configure("default.lcf");
        } else {
            org.apache.log4j.BasicConfigurator.configure();
        }
    }
    catch (java.lang.NoSuchMethodError e) { System.out.println("Exception starting logging: "+e); }

    // log->info("DeleteRosterItemAction starts");

    // fire the action
    Action a = new DeleteRosterItemAction("Delete Roster Item", new javax.swing.JFrame());
    a.actionPerformed(new ActionEvent(a, 0, "dummy"));
}
#endif
// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* DeleteRosterItemAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
