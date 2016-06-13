#ifndef BACKUPBASE_H
#define BACKUPBASE_H

#include <QObject>
#include <QStringList>
#include "appslib_global.h"

class File;
class RuntimeException;
class Logger;
namespace Operations
{
 class BackupSet;
 class APPSLIBSHARED_EXPORT BackupBase : public QObject
 {
  Q_OBJECT
 public:
  explicit BackupBase(QObject *parent = 0);
  // Just for testing......
  // If this is not null, it will be thrown to simulate various IO exceptions
  // that are hard to reproduce when running tests..
  /*public*/ RuntimeException* testException;// = null;
  /*public*/ File* getBackupRoot();
  /*public*/ void backupFilesToSetName(QString setName);// //throws IOException
  /*public*/ void backupFilesToDirectory(File* backupDirectory); //throws IOException
  /*public*/ QStringList getBackupSetList();
  /*public*/ QList<File*> getBackupSetDirs();
  /*public*/ void copyBackupSet(File* sourceDir, File* destDir); //throws IOException
  /*public*/ QString suggestBackupSetName();
  /*public*/ int getSourceFileCount(File* sourceDir);
  /*public*/ QStringList getBackupSetFileNames();
  /*public*/ bool checkIfBackupSetExists(QString setName);
  /*public*/ QList<BackupSet*> getBackupSets();
  /*public*/ void deleteOperationsFiles();
  /*public*/ void restoreFilesFromSetName(QString setName); //throws IOException
  /*public*/ void loadDemoFiles();// //throws IOException
  /*public*/ void restoreFilesFromDirectory(File* directory);// //throws IOException

 signals:

 public slots:

 private:
  Logger* log;
  // These constitute the set of files for a complete backup set.
  /*private*/ QStringList _backupSetFileNames;// = new QStringList{"Operations.xml", // NOI18N
//      "OperationsCarRoster.xml", "OperationsEngineRoster.xml", // NOI18N
//      "OperationsLocationRoster.xml", "OperationsRouteRoster.xml", // NOI18N
//      "OperationsTrainRoster.xml"}; // NOI18N
  /*private*/ void validateNotNullOrEmpty(QString s);
  /*private*/ QString _demoPanelFileName;// = "Operations Demo Panel.xml"; // NOI18N
  /*private*/ QString getDate();

 protected:
  /*protected*/ BackupBase(QString rootName, QObject *parent= 0);
  // The root directory for all Operations files, usually
  // "user / name / JMRI / operations"
  /*protected*/ File*_operationsRoot;// = null;
  // This will be set to the appropriate backup root directory from the
  // derived
  // classes, as their constructor will fill in the correct directory.
  /*protected*/ File* _backupRoot;

 };
}
#endif // BACKUPBASE_H
