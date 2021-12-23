#include "backupbase.h"
#include "logger.h"
#include "file.h"
#include "exceptions.h"
#include "operationsxml.h"
#include "stringutil.h"
#include "backupset.h"
#include <QDir>
#include "runtimeexception.h"
#include "calendar.h"
#include "loggerfactory.h"

//BackupBase::BackupBase(QObject *parent) :
//  QObject(parent)
//{
//}
namespace Operations
{
/**
 * Base class for backing up and restoring Operations working files. Derived
 * classes implement specifics for working with different backup set stores,
 * such as Automatic and Default backups.
 *
 * @author Gregory Madsen Copyright (C) 2012
 */
///*public*/ abstract class BackupBase {

//    static Logger log = LoggerFactory
//            .getLogger(BackupBase.class.getName());




 /*public*/ File* BackupBase::getBackupRoot() {
     return _backupRoot;
 }



 /*public*/ QStringList BackupBase::getBackupSetFileNames()
{
     //eturn _backupSetFileNames.clone();
 return QStringList(_backupSetFileNames);
 }

 /**
  * Creates a BackupBase instance and initializes the Operations root
  * directory to its normal value.
  */
 /*protected*/ BackupBase::BackupBase(QString rootName, QObject *parent) :
QObject(parent)
 {
  _backupSetFileNames = QStringList() << "Operations.xml" << // NOI18N
  "OperationsCarRoster.xml" << "OperationsEngineRoster.xml" << // NOI18N
  "OperationsLocationRoster.xml" << "OperationsRouteRoster.xml" << // NOI18N
  "OperationsTrainRoster.xml"; // NOI18N
  _demoPanelFileName = "Operations Demo Panel.xml"; // NOI18N

  // A root directory name for the backups must be supplied, which will be
  // from the derived class constructors.
  if (rootName == NULL) {
      throw new IllegalArgumentException("Backup root name can't be NULL"); // NOI18N
  }
  _operationsRoot = new File(OperationsXml::getFileLocation(),
          OperationsXml::getOperationsDirectoryName());

  _backupRoot = new File(_operationsRoot, rootName);

  // Make sure it exists
  if (!_backupRoot->exists()) {
      bool ok = _backupRoot->mkdirs();
      if (!ok) {
       Logger::error("Unable to make directory:" + _backupRoot->getAbsolutePath());
       throw RuntimeException("Unable to make directory: " // NOI18N
                  + _backupRoot->getAbsolutePath());
      }
  }

  // We maybe want to check if it failed and throw an exception.
 }

 /**
  * Backs up Operations files to the named backup set under the backup root
  * directory.
  *
  * @param setName The name of the new backup set
  * @throws java.io.IOException
  */
 /*public*/ void BackupBase::backupFilesToSetName(QString setName) //throws IOException
{
     validateNotNullOrEmpty(setName);

     copyBackupSet(_operationsRoot, new File(_backupRoot, setName));
 }

 /*private*/ void BackupBase::validateNotNullOrEmpty(QString s) {
     if (s == NULL || s.trimmed().length() == 0) {
         throw new IllegalArgumentException(
                 "string cannot be NULL or empty."); // NOI18N
     }

 }

 /**
  * Creates backup files for the directory specified. Assumes that
  * backupDirectory is a fully qualified path where the individual files will
  * be created. This will backup files to any directory which does not have
  * to be part of the JMRI hierarchy.
  *
  * @param backupDirectory The directory to use for the backup.
  * @throws java.io.IOException
  */
 /*public*/ void BackupBase::backupFilesToDirectory(File* backupDirectory) //throws IOException
{
     copyBackupSet(_operationsRoot, backupDirectory);
 }

 /**
  * Returns a sorted list of the Backup Sets under the backup root.
  *
  */
 /*public*/ QStringList BackupBase::getBackupSetList() {
     QStringList setList = _backupRoot->list();
     // no guarantee of order, so we need to sort
     StringUtil::sort(setList);
     return setList;
 }

 /*public*/ QList<File*> BackupBase::getBackupSetDirs() {
     // Returns a list of File objects for the backup sets in the
     // backup store.
     // Not used at the moment, and can probably be removed in favor of
     // getBackupSets()
     QList<File*> dirs = _backupRoot->listFiles();

     return dirs;
 }

 /*public*/ QList<BackupSet*> BackupBase::getBackupSets() {
     // This is a bit of a kludge for now, until I learn more about dynamic
     // sets
     QList<File*> dirs = _backupRoot->listFiles();
     QVector<BackupSet*> sets = QVector<BackupSet*>(dirs.length());

     for (int i = 0; i < dirs.length(); i++) {
         sets.replace(i, new BackupSet(dirs[i]));
     }

     return sets.toList();
 }

 /**
  * Check to see if the given backup set already exists in the backup store.
  *
  * @param setName
  * @return true if it exists
  */
 /*public*/ bool BackupBase::checkIfBackupSetExists(QString setName) {
     // This probably needs to be simplified, but leave for now.
     validateNotNullOrEmpty(setName);

     try {
         File* file = new File(_backupRoot, setName);

         if (file->exists()) {
             return true;
         }
     } catch (Exception e) {
         log->error("Exception during backup set directory exists check");
     }
     return false;
 }

 /**
  * Restores a Backup Set with the given name from the backup store.
  *
  * @param setName
  * @throws java.io.IOException
  */
 /*public*/ void BackupBase::restoreFilesFromSetName(QString setName) //throws IOException
{
     copyBackupSet(new File(_backupRoot, setName), _operationsRoot);
 }

 /**
  * Restores a Backup Set from the given directory.
  *
  * @param directory
  * @throws java.io.IOException
  */
 /*public*/ void BackupBase::restoreFilesFromDirectory(File* directory) //throws IOException
{
     log->debug(tr("restoring files from directory %1").arg(directory->getAbsolutePath()));

     copyBackupSet(directory, _operationsRoot);
 }

 /**
  * Copies a complete set of Operations files from one directory to another
  * directory. Usually used to copy to or from a backup location. Creates the
  * destination directory if it does not exist.
  *
  * Only copies files that are included in the list of Operations files.
  *
  * @param sourceDir
  * @param destDir
  * @throws java.io.IOException
  */
 /*public*/ void BackupBase::copyBackupSet(File* sourceDir, File* destDir) //throws IOException
{
     log->debug(tr("copying backup set from: %1 to: %2").arg(sourceDir->getPath()).arg(destDir->getPath()));
     log->info(tr("Saving copy of operations files to: %1").arg(destDir->getPath()));

     if (!sourceDir->exists()) // This throws an exception, as the dir should
     // exist.
     {
         throw new IOException("Backup Set source directory: " // NOI18N
                 + sourceDir->getAbsolutePath() + " does not exist"); // NOI18N
     }
     // See how many Operations files we have. If they are all there, carry
     // on, if there are none, just return, any other number MAY be an error,
     // so just log it.
     // We can't throw an exception, as this CAN be a valid state.
     // There is no way to tell if a missing file is an error or not the way
     // the files are created.

     int sourceCount = getSourceFileCount(sourceDir);

     if (sourceCount == 0) {
         log->debug(tr("No source files found in %1 so skipping copy.").arg(sourceDir->getAbsolutePath())); // NOI18N
         return;
     }

     if (sourceCount != _backupSetFileNames.length()) {
         log->warn(tr("Only %1 file(s) found in directory %2").arg(sourceCount).arg(sourceDir->getAbsolutePath()));
         // throw new IOException("Only " + sourceCount
         // + " file(s) found in directory "
         // + sourceDir.getAbsolutePath());
     }

     // Ensure destination directory exists
     if (!destDir->exists()) {
         // Note that mkdirs does NOT throw an exception on error.
         // It will return false if the directory already exists.
         bool result = destDir->mkdirs();

         if (!result) {
             // This needs to use a better Exception class.....
             throw new IOException(
                     destDir->getAbsolutePath()
                     + " (Could not create all or part of the Backup Set path)"); // NOI18N
         }
     }

     // Just copy the specific Operations files, now that we know they are
     // all there.
     foreach (QString name, _backupSetFileNames) {
         log->debug(tr("copying file: %1").arg(name));

         File* src = new File(sourceDir, name);

         if (src->exists()) {
             File* dst = new File(destDir, name);

            // FileHelper.copy(src.getAbsolutePath(), dst.getAbsolutePath(), true);
             QFile::copy(src->getAbsolutePath(), dst->getAbsolutePath());
         } else {
             log->debug(tr("Source file: %1 does not exist, and is not copied.").arg(src->getAbsolutePath()));
         }

     }
#if 1
     // Throw a test exception, if we have one.
     if (testException != NULL) {
         //testException->fillInStackTrace();
         throw testException;
     }
#endif
 }

 /**
  * Checks to see how many of the Operations files are present in the source
  * directory.
  *
  * @return number of files
  */
 /*public*/ int BackupBase::getSourceFileCount(File* sourceDir) {
     int count = 0;
     bool exists;

     foreach (QString name, _backupSetFileNames)
     {
         //exists = new File(sourceDir+name)->exists();
      File f = File(sourceDir->getPath()+ QDir::separator()+name);
      exists = f.exists();
         if (exists) {
             count++;
         }
     }

     return count;
 }

 /**
  * Reloads the demo Operations files that are distributed with JMRI.
  *
  * @throws java.io.IOException
  */
 /*public*/ void BackupBase::loadDemoFiles() //throws IOException
 {
  File* fromDir = new File(XmlFile::xmlDir(), "demoOperations"); // NOI18N
  copyBackupSet(fromDir, _operationsRoot);

  // and the demo panel file
  log->debug(tr("copying file: %1").arg(_demoPanelFileName));

  File* src = new File(fromDir, _demoPanelFileName);
  File* dst = new File(_operationsRoot, _demoPanelFileName);

  //FileHelper.copy(src.getAbsolutePath(), dst.getAbsolutePath(), true);
  QFile::copy(src->getAbsolutePath(), dst->getAbsolutePath());
 }

 /**
  * Searches for an unused directory name, based on the default base name,
  * under the given directory. A name suffix as appended to the base name and
  * can range from 00 to 99.
  *
  * @return A backup set name that is not already in use.
  */
 /*public*/ QString BackupBase::suggestBackupSetName() {
     // Start with a base name that is derived from today's date
     // This checks to see if the default name already exists under the given
     // backup root directory.
     // If it exists, the name is incremented by 1 up to 99 and checked
     // again.
     QString baseName = getDate();
     QString fullName = NULL;
     QStringList dirNames = _backupRoot->list();

     // Check for up to 100 backup file names to see if they already exist
     for (int i = 0; i < 99; i++) {
         // Create the trial name, then see if it already exists.
         //fullName = QString.format("%s_%02d", baseName, i); // NOI18N
      fullName = baseName + "_" + QString::number(i);

         bool foundFileNameMatch = false;
         foreach (QString name, dirNames) {
             if (name==(fullName)) {
                 foundFileNameMatch = true;
                 break;
             }
         }
         if (!foundFileNameMatch) {
             return fullName;
         }

//			This should also work, commented out by D. Boudreau
//			The Linux problem turned out to be related to the order
//			files names are returned by list().
//			File testPath = new File(_backupRoot, fullName);
//
//			if (!testPath.exists()) {
//				return fullName; // Found an unused name
         // Otherwise complain and keep trying...
         log->debug(tr("Operations backup directory: %1 already exists").arg(fullName)); // NOI18N
     }

     // If we get here, we have tried all 100 variants without success. This
     // should probably throw an exception, but for now it just returns the
     // last file name tried.
     return fullName;
 }

 /**
  * Reset Operations by deleting XML files, leaves directories and backup
  * files in place.
  */
 /*public*/ void BackupBase::deleteOperationsFiles() {
     // TODO Maybe this should also only delete specific files used by Operations,
     // and not just all XML files.
     File* files = _operationsRoot;

     if (!files->exists()) {
         return;
     }

     QStringList operationFileNames = files->list();
     foreach (QString fileName, operationFileNames) {
         // skip non-xml files
         if (!fileName.toUpper().endsWith(".XML")) // NOI18N
         {
             continue;
         }
         //
         log->debug(tr("deleting file: %1").arg(fileName));
         File* file = new File(_operationsRoot->getPath() + File::separator + fileName);
         if (!file->_delete()) {
             log->debug("file not deleted");
         }
         // TODO This should probably throw an exception if a delete fails.
     }
 }

 /**
  * Returns the current date formatted for use as part of a Backup Set name.
  */
 /*private*/ QString BackupBase::getDate() {
     // This could use some clean-up.... but works OK for now
#if 0
     Calendar* now = Calendar::getInstance();
     int month = now->get(Calendar::MONTH) + 1;
     QString m = QString::number(month);
     if (month < 10) {
         m = "0" + QString::number(month);
     }
     int day = now->get(Calendar::DATE);
     QString d = QString::number(day);
     if (day < 10) {
         d = "0" + QString::number(day);
     }
     QString date = QString() + now->get(Calendar::YEAR) + "_" + m + "_" + d;
     return date;
#else
 return QDate::currentDate().toString("yyyy_MM_dd");
#endif
 }
#if 0
 /**
  * Helper class for working with Files and Paths. Should probably be moved
  * into its own public class.
  *
  * Probably won't be needed now that I discovered the File class and it can
  * glue together paths. Need to explore it a bit more.
  *
  * @author Gregory Madsen Copyright (C) 2012
  *
  */
 /*private*/ static class FileHelper {

     /**
      * Copies an existing file to a new file. Overwriting a file of the same
      * name is allowed. The destination directory must exist.
      *
      * @param sourceFileName
      * @param destFileName
      * @param overwrite
      * @throws IOException
      */
     @edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "OBL_UNSATISFIED_OBLIGATION")
     /*public*/ static void copy(QString sourceFileName, QQString destFileName,
             bool overwrite) throws IOException {

         // If we can't overwrite the destination, check if the destination
         // already exists
         if (!overwrite) {
             if (new File(destFileName).exists()) {
                 throw new IOException(
                         "Destination file exists and overwrite is false."); // NOI18N
             }
         }

         InputStream source = NULL;
         OutputStream dest = NULL;

         try {
             source = new FileInputStream(sourceFileName);
             dest = new FileOutputStream(destFileName);

             byte[] buffer = new byte[1024];

             int len;

             while ((len = source.read(buffer)) > 0) {
                 dest.write(buffer, 0, len);
             }
         } catch (Exception ex) {
             if (source != NULL) {
                 source.close();
             }
             if (dest != NULL) {
                 dest.close();
             }
             QString msg = String.format("Error copying file: %s to: %s", // NOI18N
                     sourceFileName, destFileName);
             throw new IOException(msg, ex);
         }

         source.close();
         dest.close();

         // Now update the last modified time to equal the source file.
         File src = new File(sourceFileName);
         File dst = new File(destFileName);

         bool ok = dst.setLastModified(src.lastModified());
         if (!ok) {
             throw new RuntimeException(
                     "Failed to set modified time on file: " // NOI18N
                     + dst.getAbsolutePath());
         }
     }
 }
#endif
 /*private*/ /*final*/ /*static*/ Logger* BackupBase::log = LoggerFactory::getLogger("BackupBase");

}
