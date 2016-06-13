#include "fullbackupexportaction.h"
#include "exceptions.h"
#include "jmripanel.h"
#include "roster.h"
#include "file.h"
//#include "../../../../../Projects/quazip-0.7/quazip/quazip.h"
#include "quazip.h"
//#include "../../../../../Projects/quazip-0.7/quazip/quazipfile.h"
#include "quazipfile.h"

//#include <QFileDialog>
#include "fileutil.h"
#include "version.h"
#include "rosterentry.h"
#include "jfilechooser.h"

FullBackupExportAction::FullBackupExportAction(QObject *parent)
 :  JmriAbstractAction("Export Roster Backup", parent)
{
}
/**
 * Offer an easy mechanism to save the entire roster contents from one instance
 * of DecoderPro. The result is a zip format file, containing all of the roster
 * entries plus the overall roster.xml index file.
 *
 * @author david d zuhn
 *
 */
// /*public*/ class FullBackupExportAction
//        extends JmriAbstractAction {

//private static final long serialVersionUID = 1L;
// parent component for GUI

/*public*/ FullBackupExportAction::FullBackupExportAction(QString s, WindowInterface* wi) : JmriAbstractAction(s, wi)
{
 //super(s, wi);
 common();
}

/*public*/ FullBackupExportAction::FullBackupExportAction(QString s, QIcon i, WindowInterface* wi) : JmriAbstractAction(s, i, wi)
{
 //super(s, i, wi);
 common();
}

/**
 * @param s      Name of this action, e.g. in menus
 * @param parent Component that action is associated with, used to ensure
 *               proper position in of dialog boxes
 */
/*public*/ FullBackupExportAction::FullBackupExportAction(QString s, QWidget* parent)
 : JmriAbstractAction(s, parent)
{
 //super(s);
 _parent = parent;
 common();
}

void FullBackupExportAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 log = new Logger("FullBackupExportAction");
}

/*public*/ void FullBackupExportAction::actionPerformed(ActionEvent* /*e*/)
{
 Roster* roster = Roster::instance();
#if 1
 //ZipOutputStream* zipper = NULL;
 zipper = NULL;

 try
 {
  QString roster_filename_extension = ".roster";

  JFileChooser* chooser = new JFileChooser();
//  FileNameExtensionFilter filter = new FileNameExtensionFilter(
//          "JMRI full roster files", roster_filename_extension);
  QString filter = "JMRI full roster files (*.roster)";
  chooser->setFileFilter(filter);

  int returnVal = chooser->showSaveDialog(_parent);
  if (returnVal != JFileChooser::APPROVE_OPTION) {
      return;
  }

  QString filename = chooser->getSelectedFile()->getAbsolutePath();
//  QString filename = QFileDialog::getSaveFileName(_parent, tr("Select roster save file"), FileUtil::getUserFilesPath(), QString("JMRI full roster files (*.roster)") );

  if (!filename.endsWith(roster_filename_extension))
  {
   filename = filename.append(roster_filename_extension);
  }

  //zipper = new ZipOutputStream(new FileOutputStream(filename));
  zipper = new QuaZip(filename);
  if(!zipper->open(QuaZip::mdCreate))
  {
   log->error(tr("Can't create complete roster export file ") + filename);
   return;
  }
  QuaZipFile* outFile = new QuaZipFile(zipper);

  // create a zip file roster entry for each entry in the main roster
  for (int index = 0; index < roster->numEntries(); index++)
  {
   RosterEntry* entry = roster->getEntry(index);
   copyFileToStream(entry->getPathName(), "roster", outFile, entry->getId());
  }

    // Now the full roster entry
  copyFileToStream(Roster::defaultRosterFilename(), "", outFile, "");

  zipper->setComment("Roster file saved from DecoderPro " + Version::name());

  zipper->close();

 }
 catch (FileNotFoundException ex)
 {
//        ex.printStackTrace();
 } catch (IOException ex)
 {
//        ex.printStackTrace();
 }
//    finally
//    {
//     if (zipper != NULL)
//     {

//         try {
//             zipper.close();
//         } catch (IOException ex) {
//             ex.printStackTrace();
//         }
//     }
//    }
#endif
}

/**
 * Copy a file to an entry in a zip file.
 *
 * The basename of the source file will be used in the zip file, placed in
 * the directory of the zip file specified by dirname. If dirname is NULL,
 * the file will be placed in the root level of the zip file.
 *
 * @param filename the file to copy
 * @param dirname  the zip file "directory" to place this file in
 * @param zipper   the ZipOutputStream
 * @throws IOException
 */
/*private*/ bool FullBackupExportAction::copyFileToStream(QString filename, QString dirname, QuaZipFile* outFile, QString comment)
        /*throws IOException*/
{
 QFile* inFile = new QFile(filename);
 QFileInfo* fileInfo = new QFileInfo(filename);
 QString entryName;
 char c;

 if (dirname != "")
 {
  entryName = dirname + "/" + fileInfo->fileName();
 }
 else
 {
  entryName = fileInfo->fileName();
 }
#if 1
 //ZipEntry zipEntry = new ZipEntry(entryName);
 if(!inFile->open(QIODevice::ReadOnly))
  return false;

 if(!outFile->open(QIODevice::WriteOnly, QuaZipNewInfo(fileInfo->fileName(), fileInfo->filePath())))
  return false;

 //zipper->setCurrentFile(entryName);


// zipEntry->setTime(file.lastModified());
// zipEntry.setSize(file.length());
// if (comment != NULL) {
//     zipEntry.setComment(comment);
// }

//    zipper.putNextEntry(zipEntry);

//    FileInputStream fis = new FileInputStream(file);
//    try {
//        int c;
//        while ((c = fis.read()) != -1) {
//            zipper.write(c);
//        }
//    } finally {
//        fis.close();
//    }

//    zipper.closeEntry();
 while (inFile->getChar(&c) )
     outFile->putChar(c);

 if (outFile->getZipError() != ZIP_OK)
 {
     return false;
 }

 outFile->close();

 if (outFile->getZipError() != ZIP_OK)
 {
     return false;
 }

 inFile->close();
 return true;
#endif
}

// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* FullBackupExportAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
