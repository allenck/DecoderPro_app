#include "fullbackupimportaction.h"
//#include "../../../../../Projects/quazip-0.7/quazip/quazip.h"
#include "quazip.h"
//#include "../../../../../Projects/quazip-0.7/quazip/quazipfile.h"
#include "quazipfile.h"
#include "windowinterface.h"
#include "fileutil.h"
#include "locofile.h"
#include "roster.h"
#include "rosterentry.h"
#include <QFileDialog>
#include "logger.h"
#include <QMessageBox>
#include "importrosteritemaction.h"
#include "jfilechooser.h"
#include "joptionpane.h"
#include "file.h"


FullBackupImportAction::FullBackupImportAction(QObject *parent) :
  ImportRosterItemAction("Import Roster Backup", (WindowInterface*)parent)
{
}
/**
 * Reload the JMRI Roster ({@link jmri.jmrit.roster.Roster}) from a file
 * previously stored by {@link jmri.jmrit.roster.FullBackupExportAction}.
 *
 * Does not currently handle importing the group(s) that the entry belongs to.
 *
 * @author Bob Jacobsen Copyright 2014
 */
// /*public*/ class FullBackupImportAction extends ImportRosterItemAction {

/**
 * Load from a file exported by {@link FullBackupImportAction}
 *
 * @author Bob Jacobsen Copyright 2014
 */
//private static final long serialVersionUID = 1L;

//private Component _who;
/*public*/ FullBackupImportAction::FullBackupImportAction(QString s, WindowInterface* wi)
 : ImportRosterItemAction(s, wi)
{
 //super(s, wi);
 common();
}

/*public*/ FullBackupImportAction::FullBackupImportAction(QString s, QIcon i, WindowInterface* wi)
 : ImportRosterItemAction(s, i, wi)
{
 //super(s, i, wi);
 common();
}

/**
 * @param title  Name of this action, e.g. in menus
 * @param parent Component that action is associated with, used to ensure
 *               proper position in of dialog boxes
 */
/*public*/ FullBackupImportAction::FullBackupImportAction(QString title, QWidget* parent)
 : ImportRosterItemAction(title, parent)
{
 //super(title, parent);
 common();
 _parent = parent;
}

void FullBackupImportAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 log = new Logger("FullBackupImportAction");
}

/*public*/ void FullBackupImportAction::actionPerformed(ActionEvent* /*e*/)
{

 // ensure preferences will be found for read
 FileUtil::createDirectory(LocoFile::getFileLocation());

 // make sure instance loaded
 Roster::getDefault();

 // set up to read import file
 //ZipInputStream zipper = NULL;
 QuaZip* zipper = NULL;
 //FileInputStream inputfile = NULL;
 QuaZipFile* inputFile = NULL;

 try
 {
  JFileChooser* chooser = new JFileChooser();

  QString roster_filename_extension = "roster";
//  FileNameExtensionFilter filter = new FileNameExtensionFilter(
//          "JMRI full roster files", roster_filename_extension);
  chooser->setFileFilter("JMRI full roster files *.roster" );
  //chooser->addChoosableFileFilter(filter);
  //chooser->setCurrentDirectory(new File(FileUtil::getPreferencesPath()));

  int returnVal = chooser->showOpenDialog(mParent);
  if (returnVal != JFileChooser::APPROVE_OPTION)
  {
      return;
  }

  QString filename = chooser->getSelectedFile()->getAbsolutePath();

//  inputfile = new FileInputStream(filename);
//  zipper = new ZipInputStream(inputfile) {
//      /*public*/ void close() {
//      } // SaxReader calls close when reading XML stream, ignore
//      // and close directly later
//  };
  zipper = new QuaZip(filename);
  zipper->open(QuaZip::mdUnzip);
  inputFile = new QuaZipFile(zipper);

  // now iterate through each item in the stream. The get next
  // entry call will return a ZipEntry for each file in the
  // stream
  //ZipEntry entry;
  //while ((entry = zipper.getNextEntry()) != NULL)
  //for(bool f = zipper->goToFirstFile(); f; f = zipper->goToNextFile());
  bool f = zipper->goToFirstFile();
  while(f)
  {
//      log->debug(QString.format("Entry: %s len %d added %TD",
//              entry.getName(), entry.getSize(),
//              new Date(entry.getTime())));
      // Once we get the entry from the stream, the stream is
      // positioned read to read the raw data, and we keep
      // reading until read returns 0 or less.
   try
   {
   LocoFile* xfile = new LocoFile();   // need a dummy object to do this operation in next line
   inputFile->open(QIODevice::ReadOnly);

   QByteArray ba = inputFile->readAll();
   QString fn = zipper->getCurrentFileName();
   if(fn.endsWith(".jpg", Qt::CaseInsensitive) || fn.endsWith(".png", Qt::CaseInsensitive) || fn.endsWith(".gif", Qt::CaseInsensitive) || fn.endsWith(".svn", Qt::CaseInsensitive) || fn.endsWith(".ico", Qt::CaseInsensitive))
   {
    File* location = new File(LocoFile::getFileLocation());
    if(!location->exists())
    {
      location->mkdirs();
    }
    QFile fOut(LocoFile::getFileLocation()+ fn);
    if(fOut.open(QIODevice::WriteOnly))
    {
     fOut.write(ba);
     fOut.close();
    }
    else
      throw new IOException(tr("error writing file %1").arg(fOut.fileName()));
    inputFile->close();
    f = zipper->goToNextFile();
    continue;
   }


   QDomElement lroot = xfile->rootFromInputStream(new QDataStream(ba)).cloneNode().toElement();
   if (lroot.firstChildElement("locomotive") == QDomElement())
   {
    f = zipper->goToNextFile();  // that's the roster file
    continue;
   }
   mToID = lroot.firstChildElement("locomotive").attribute("id");

    // see if user wants to do it
   QList<QVariant> vl = QList<QVariant>();
   vl << tr("Cancel Imports") <<
     tr("Skip") <<
     tr("OK");
    int retval = JOptionPane::showOptionDialog(mParent,
            tr("Import locomotive ID: \"%1\"").arg(mToID),
            tr("Confirm Import"),
            0,
            JOptionPane::INFORMATION_MESSAGE,
            QIcon(),
            vl,
            QVariant());
   if (retval == 0)  // cancel
   {
    f = false;
    break;
   }
   if (retval == 1) // skip
   {
    inputFile->close();
    f = zipper->goToNextFile();  // that's the roster file
    continue;
   }
//    int retval = QMessageBox::question(_parent, tr("Confirm Import"), tr("Import locomotive ID: \"%1\"").arg(mToID), QMessageBox::Yes  | QMessageBox::No);
//    if (retval == QMessageBox::No)
//    {
//     inputFile->close();
//     f = zipper->goToNextFile();  // that's the roster file
//     continue;
//    }

    // see if duplicate
    RosterEntry* currentEntry = Roster::getDefault()->getEntryForId(mToID);

    if (currentEntry != NULL)
    {
     QVariantList vl;
     vl << tr("Cancel Imports") << tr("Skip") << tr("OK");
     retval = JOptionPane::showOptionDialog(mParent,
             tr("This will replace an existing roster entry\nby the same name:\"%1\"").arg(mToID),
             tr("Confirm Import"),
             0,
             JOptionPane::INFORMATION_MESSAGE,
             QIcon(),
             vl,
             QVariant());
     if (retval == 0)
     {
         break;
     }
     if (retval == 1) {
         continue;
     }

     // turn file into backup
     LocoFile* df = new LocoFile();   // need a dummy object to do this operation in next line
     df->makeBackupFile(LocoFile::getFileLocation() + currentEntry->getFileName());

     // delete entry
     Roster::getDefault()->removeEntry(currentEntry);

    }

    loadEntryFromElement(lroot);
    addToEntryToRoster();

    // use the new roster
    Roster::getDefault()->reloadRosterFile();
   }
   catch (JDOMException* ex) {
       //ex.printStackTrace();
   }
    inputFile->close();
    f = zipper->goToNextFile();
  }

 } catch (FileNotFoundException* ex) {
     //ex.printStackTrace();
 } catch (IOException* ex) {
     //ex.printStackTrace();
 }
// finally {
//     if (inputfile != NULL) {
//         try {
//             inputfile.close(); // zipper.close() is meaningless, see above, but this will do
//         } catch (IOException* ex) {
//             ex.printStackTrace();
//         }
//     }
// }

}

bool FullBackupImportAction::selectFrom()
{
 return false;
}
