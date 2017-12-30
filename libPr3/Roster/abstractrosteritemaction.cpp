#include "abstractrosteritemaction.h"
#include "roster.h"
#include "windowinterface.h"
#include <QComboBox>
#include "rosterentrycombobox.h"
#include <QMessageBox>
#include "../../LayoutEditor/inputdialog.h"
#include "jfilechooser.h"
#include <QFileInfo>
#include "file.h"


AbstractRosterItemAction::AbstractRosterItemAction(QObject *parent) :
    JmriAbstractAction("<none>", parent)
{
 mParent = (QWidget*)parent;
}
/**
 * Base class for Actions to copy, export and import RosterEntrys.
 * <P>
 * Note that {@link DeleteRosterItemAction} is sufficiently
 * different that it doesn't use this base class.
 *
 * @author	Bob Jacobsen   Copyright (C) 2001, 2002, 2007, 2008
 * @version	$Revision: 20599 $
 * @see         jmri.jmrit.XmlFile
 */
// abstract /*public*/ class AbstractRosterItemAction extends jmri.util.swing.JmriAbstractAction {

/*public*/ AbstractRosterItemAction::AbstractRosterItemAction(QString pName, QWidget* pWho) : JmriAbstractAction(pName, pWho)
{
 //super(pName);
 common();
 mParent = pWho;
}

/*public*/ AbstractRosterItemAction::AbstractRosterItemAction(QString s, WindowInterface* wi) : JmriAbstractAction(s,wi)
{
 //super(s, wi);
 common();
 mParent = (QWidget*)wi;
}
void AbstractRosterItemAction::common()
{
 log = new Logger("AbstractRosterItemAction");
 mFromID = "";
 mFromEntry = NULL;
 mFromFile = NULL;
 mFromFilename = "";
 mFullFromFilename = "";  // includes path to preferences

 mToID = "";
 mToEntry = NULL;
 mToFile = NULL;
 mToFilename = "";
 mFullToFilename = "";  // includes path to preferences
 fileChooser = NULL;
 mParent = NULL;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ AbstractRosterItemAction::AbstractRosterItemAction(QString s, QIcon i, WindowInterface* wi): JmriAbstractAction(s,i,wi)
{
 //super(s, i, wi);
 common();
 mParent = (QWidget*)wi;
}


/*public*/ void AbstractRosterItemAction::actionPerformed(ActionEvent* event)
{
  // select the "from" entry/file
  if (!selectFrom()) return;
  // select the "to" entry/file
  if (!selectTo()) return;
  // transfer "from" to "to" as needed
  if (!doTransfer()) return;
  // update roster
  updateRoster();

  return;
}


/**
 * Common, but not unique implementation to add the "To" entry
 * to the Roster and rewrite the roster file.
 */
void AbstractRosterItemAction::updateRoster() {
    addToEntryToRoster();
}

bool AbstractRosterItemAction::selectExistingFromEntry()
{
 // create a dialog to select the roster entry to copy
 QString group = NULL;
//    if (Beans::hasProperty(wi, "selectedRosterGroup")) {
//        group = (QString) Beans::getProperty(wi, "selectedRosterGroup");
//    }
 QComboBox* selections = new RosterEntryComboBox(group);
//    int retval = JOptionPane.showOptionDialog(mParent,
//                                              "Select one roster entry", "Select roster entry",
//                                              0, JOptionPane.INFORMATION_MESSAGE, NULL,
//                                              new Object[]{"Cancel", "OK", selections}, NULL );
 InputDialog* dlg = new InputDialog(tr("Select one  roster entry"),selections, tr("Select roster entry"));
 int retval = dlg->exec();
 log->debug("Dialog value "+QString::number(retval)+" selected "+QString::number(selections->currentIndex())+":\""
           +selections->currentText()+"\"");
 if (retval!= QDialog::Accepted) return false;  // user didn't select

 // find the file for the selected entry to copy
 setExistingEntry((RosterEntry*) Roster::instance()->getEntryForId(selections->currentText()));

 return true;
}

/**
 * method added for DP3 where the existing roster entry is selected from a table
 */

/*public*/ void AbstractRosterItemAction::setExistingEntry(RosterEntry* mFromEntry){
    this->mFromEntry = mFromEntry;
    mFromFilename = mFromEntry->getFileName();
    mFullFromFilename = LocoFile::getFileLocation()+mFromFilename;
    log->debug(" from resolves to \""+mFromFilename+"\", \""+mFullFromFilename+"\"");
}

bool AbstractRosterItemAction::selectNewToEntryID()
{
 do
 {
  // prompt for the new ID
  //mToID = JOptionPane.showInputDialog(mParent, "Enter id for new roster entry:");
  InputDialog* dlg = new InputDialog("Enter id for new roster entry:", mToID, NULL);
  if(dlg->exec() == QDialog::Accepted)
  {
   //if (mToID==NULL) return false;
   mToID = dlg->value();

   // check for empty
   if (mToID==(""))
   {
     //JOptionPane.showMessageDialog(mParent,"The ID cannot be blank");
     QMessageBox::critical(mParent, tr("Error"),tr("The ID cannot be blank"));
     // ask again
     continue;
   }

   // check for duplicate
   if (0 == Roster::instance()->matchingList(NULL, NULL, NULL, NULL, NULL, NULL, mToID).size()) break;

   // here it is a duplicate, reprompt
    //JOptionPane.showMessageDialog(mParent,
//                                      "That entry already exists, please choose another");
   QMessageBox::critical(mParent, tr("Error"),tr("That entry already exists, please choose another"));
  }
  else
   return false;
 } while (true);
 return true;
}


bool AbstractRosterItemAction::selectNewFromFile()
{
 if (fileChooser==NULL) {
     fileChooser = XmlFile::userFileChooser();
 }
 // refresh fileChooser view of directory, in case it changed
//    fileChooser->rescanCurrentDirectory();
 int retVal = fileChooser->showOpenDialog(mParent);

 // handle selection or cancel
 if (retVal != JFileChooser::APPROVE_OPTION)
 {
  return false;  // give up if no file selected
 }
 // call load to process the file
 mFromFile = fileChooser->getSelectedFile();
 mFromFilename = mFromFile->getName();
 mFullFromFilename = mFromFile->getAbsolutePath();
 log->debug("New from file: " + mFromFilename + " at " + mFullFromFilename);
 return true;
}

bool AbstractRosterItemAction::selectNewToFile()
{
 if (fileChooser==NULL)
 {
  fileChooser = XmlFile::userFileChooser();
 }
 fileChooser->setSelectedFile(new File(mFromFilename));
 int retVal = fileChooser->showSaveDialog(mParent);

 // handle selection or cancel
 if (retVal != JFileChooser::APPROVE_OPTION) {
     return false;  // give up if no file selected
 }
 // call load to process the file
 mToFile = fileChooser->getSelectedFile();
 mToFilename = mToFile->getName();
 mFullToFilename = mToFile->getAbsolutePath();
 log->debug("New to file: " + mToFilename + " at " + mFullToFilename);
 return true;
}

void AbstractRosterItemAction::addToEntryToRoster()
{
 // add the new entry to the roster & write it out
 Roster::instance()->addEntry(mToEntry);
 Roster::writeRosterFile();
}

// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* AbstractRosterItemAction::makePanel() {
    throw IllegalArgumentException("Should not be invoked");
}
