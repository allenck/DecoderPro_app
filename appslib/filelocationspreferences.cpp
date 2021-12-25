#include "filelocationspreferences.h"
#include "preferences.h"
#include "profileutils.h"
#include "fileutil.h"
#include "file.h"

FileLocationsPreferences::FileLocationsPreferences()
{

}
/**
 *
 * @author Randall Wood (C) 2015
 */
// /*public*/ class FileLocationsPreferences extends AbstractPreferencesManager {

/*public*/ /*static*/ /*final*/ QString FileLocationsPreferences::USER_FILES = "user-files"; // NOI18N
/*public*/ /*static*/ /*final*/ QString FileLocationsPreferences::SCRIPTS = "scripts"; // NOI18N
/*public*/ /*static*/ /*final*/ QString FileLocationsPreferences::JMRIPROGRAM = "jmriprogram"; // NOI18N added ACK

//@Override
/*public*/ void FileLocationsPreferences::initialize(Profile* profile) /*throw (InitializationException)*/
{
 if (!this->isInitialized(profile))
 {
  Preferences* shared = ProfileUtils::getPreferences(profile, "jmri/implementation/FileLocations/FileLocationsPreferences", true);
  Preferences* perNode = ProfileUtils::getPreferences(profile, "jmri/implementation/FileLocations/FileLocationsPreferences", false);
  QString userFiles = shared->get(USER_FILES, FileUtil::PROFILE);
  if (!userFiles.startsWith(FileUtil::PROFILE)) // "profile:"
  {
   userFiles = perNode->get(USER_FILES, userFiles);
  }
  FileUtil::setUserFilesPath(profile, FileUtil::getAbsoluteFilename(userFiles));
  QString scripts = shared->get(SCRIPTS, FileUtil::PROFILE);
  if (!scripts.startsWith(FileUtil::PROFILE) && !scripts.startsWith(FileUtil::PROGRAM)) {
      scripts = perNode->get(SCRIPTS, scripts);
  }
  FileUtil::setScriptsPath(profile, FileUtil::getAbsoluteFilename(scripts));
  this->setInitialized(profile, true);
  try {
      if (!FileUtil::getFile(userFiles)->isDirectory())
      {
          //QString message = "UserFilesIsNotDir"; // NOI18N
          userFiles = FileUtil::getAbsoluteFilename(userFiles);
          throw new InitializationException(tr( "User files location \"%1\" is not a directory.").arg( userFiles),QString( "User files location \"%1\" is not a directory.").arg( userFiles),NULL);
      }
  } catch (FileNotFoundException* ex) {
     // QString message = "UserFilesDoesNotExist"; // NOI18N
      userFiles = FileUtil::getAbsoluteFilename(userFiles);
      throw new  InitializationException(tr("User files location \"%1\" does not exist.").arg(userFiles), QString("User files location \"%1\" does not exist.").arg(userFiles),NULL);
  }
  try {
      if (!FileUtil::getFile(scripts)->isDirectory()) {
          //QString message = "ScriptsIsNotDir"; // NOI18N
          scripts = FileUtil::getAbsoluteFilename(scripts);
          if(!QDir(scripts).exists())
           throw new FileNotFoundException(scripts);
          throw new  InitializationException(tr("Scripts location \"%1\" is not a directory.").arg(scripts), QString("Scripts location \"%1\" is not a directory.").arg(scripts),NULL);
      }
  } catch (FileNotFoundException* ex) {
      QString message = "Scripts Does Not Exist"; // NOI18N
      scripts = FileUtil::getAbsoluteFilename(scripts);
      throw new  InitializationException(tr("Scripts location \"%1\" does not exist.").arg(scripts), QString("Scripts location \"%1\" does not exist.").arg(scripts), NULL);
  }

  QString jmriprogram = shared->get(JMRIPROGRAM, FileUtil::PROFILE);
  if (!jmriprogram.startsWith(FileUtil::PROFILE) && !jmriprogram.startsWith(FileUtil::PROGRAM))
  {
   jmriprogram = perNode->get(JMRIPROGRAM, jmriprogram);
  }
  FileUtil::setProgramPath(FileUtil::getAbsoluteFilename(jmriprogram));
  try
  {
   if (!FileUtil::getFile(jmriprogram)->isDirectory())
   {
       //QString message = "ScriptsIsNotDir"; // NOI18N
       jmriprogram = FileUtil::getAbsoluteFilename(jmriprogram);
       if(!QDir(jmriprogram).exists())
        throw new FileNotFoundException(jmriprogram);
       throw new InitializationException(tr("JmriProgram location \"%1\" is not a directory.").arg(jmriprogram), QString("JmriProgram location \"%1\" is not a directory.").arg(jmriprogram),NULL);
   }
  }
  catch (FileNotFoundException* ex)
  {
      //QString message = "ScriptsDoesNotExist"; // NOI18N
      jmriprogram = FileUtil::getAbsoluteFilename(jmriprogram);
      throw new InitializationException(tr("JmriProgram location \"%1\" does not exist.").arg(jmriprogram), QString("JmriProgram location \"%1\" does not exist.").arg(jmriprogram), NULL);
  }
  FileUtil::setProgramPath(FileUtil::getAbsoluteFilename(jmriprogram));
 }
}

//@Override
/*public*/ QSet<QString/* extends PreferencesManager*/>* FileLocationsPreferences::getRequires() {
    return new QSet<QString>();
}

//@Override
/*public*/ void FileLocationsPreferences::savePreferences(Profile* profile) {
    Preferences* shared = ProfileUtils::getPreferences(profile, "jmri/implementation/FileLocations/FileLocationsPreferences", true);
    Preferences* perNode = ProfileUtils::getPreferences(profile, "jmri/implementation/FileLocations/FileLocationsPreferences", false);
    shared->put(USER_FILES, FileUtil::getPortableFilename(FileUtil::getUserFilesPath(), true, false));
    shared->put(SCRIPTS, FileUtil::getPortableFilename(FileUtil::getScriptsPath()));
    shared->put(JMRIPROGRAM, FileUtil::getPortableFilename(FileUtil::getProgramPath()));
    perNode->put(USER_FILES, FileUtil::getPortableFilename(FileUtil::getUserFilesPath(), true, false));
    perNode->put(SCRIPTS, FileUtil::getPortableFilename(FileUtil::getScriptsPath()));
    perNode->put(JMRIPROGRAM, FileUtil::getPortableFilename(FileUtil::getProgramPath()));
}
