#include "operationsxml.h"
#include "operationssetupxml.h"
#include "logger.h"
#include "file.h"
#include "fileutil.h"
#include "trainmanagerxml.h"
#include "locationmanagerxml.h"
#include "routemanagerxml.h"
#include "carmanagerxml.h"
#include "enginemanagerxml.h"

/*private*/ /*static*/ QString OperationsXml::operationsDirectoryName = "operations"; // NOI18N

OperationsXml::OperationsXml(QObject *parent) :
  XmlFile(parent)
{
 log = new Logger("OperationsXml");
 dirty = false;
 operationsFileName = "DefaultOperations.xml"; // should be overridden // NOI18N
}
/**
 * Loads and stores the operation setup using xml files.
 *
 * @author Daniel Boudreau Copyright (C) 2008
 * @version $Revision: 29427 $
 */
///*public*/ abstract class OperationsXml extends XmlFile {

/**
 * Store the all of the operation train objects in the default place,
 * including making a backup if needed
 */
/*public*/ void OperationsXml::writeOperationsFile()
{
 createFile(getDefaultOperationsFilename(), true); // make backup
 try
 {
     writeFile(getDefaultOperationsFilename());
 }
 catch (Exception e) {
     Logger::error("Exception while writing operation file, may not be complete: " + e.getMessage());
 }
}

/*protected*/ void OperationsXml::load() throw (Exception)
{
    try {
        readFile(getDefaultOperationsFilename());
    } catch (Exception e) {
        Logger::error("Exception during operations file reading", e);
    }
}

/*protected*/ File* OperationsXml::createFile(QString fullPathName, bool backupFile)
{
 if (backupFile)
 {
  makeBackupFile(fullPathName);
 }
 File* file = NULL;
 try
 {
  if (!checkFile(fullPathName))
  {
   log->debug("File "+fullPathName+ " does not exist, creating it");
   // The file does not exist, create it before writing
   file = new File(fullPathName);
   File* parentDir = file->getParentFile();
   if (!parentDir->exists())
   {
    if (!parentDir->mkdir())
    {
     Logger::error("Directory wasn't created");
    }
   }
   if (file->createNewFile())
   {
    log->debug("File created " + fullPathName);
   }
  }
  else
  {
   file = new File(fullPathName);
  }
 }
 catch (Exception e)
 {
  Logger::error("Exception while creating operations file, may not be complete: " + e.getMessage());
 }
 return file;
}

/**
 * @throws FileNotFoundException
 * @throws IOException
 */
/*protected*/ void OperationsXml::writeFile(QString filename) // throw (FileNotFoundException, IOException)
{
 Logger::error("writeFile not overridden");
}

/**
 * @throws org.jdom2.JDOMException
 * @throws java.io.IOException
 */
/*abstract*/ /*public*/ void OperationsXml::readFile(QString filename) /*throw (JDOMException, IOException)*/ {}


/*public*/ void OperationsXml::setDirty(bool b)
{
 dirty = b;
}

/*public*/ bool OperationsXml::isDirty()
{
 return dirty;
}

/*public*/ void OperationsXml::writeFileIfDirty()
{
 if (isDirty()) {
     writeOperationsFile();
 }
}

/*public*/ QString OperationsXml::getDefaultOperationsFilename() {
    return getFileLocation() + getOperationsDirectoryName() + /*File::separator*/ "/" + getOperationsFileName();
}

/*public*/ /*static*/ void OperationsXml::setOperationsDirectoryName(QString name) {
    operationsDirectoryName = name;
}

/*public*/ /*static*/ QString OperationsXml::getOperationsDirectoryName()
{
 return operationsDirectoryName;
}


/*public*/ void OperationsXml::setOperationsFileName(QString name)
{
 operationsFileName = name;
}

/*public*/ QString OperationsXml::getOperationsFileName()
{
 return operationsFileName;
}

/*private*/ /*static*/ QString OperationsXml::fileLocation = nullptr;//FileUtil::getUserFilesPath();

/**
 * Absolute path to location of Operations files.
 * <P>
 * Default is in the user's files path, but can be set to anything.
 *
 * @see jmri.util.FileUtil#getUserFilesPath()
 */
/*public*/ /*static*/ QString OperationsXml::getFileLocation()
{
 if(fileLocation == nullptr)
  fileLocation = FileUtil::getUserFilesPath();
 return fileLocation;
}

/**
 * Set path to location of Operations files.
 * <P>
 * Default is in the user's files path, but can be set to anything.
 *
 * @param location path to file, including trailing file separator.
 */
/*public*/ /*static*/ void OperationsXml::setFileLocation(QString location) {
 fileLocation = location;
}


/**
 * Convert standard string to xml string one character at a time expect when
 * a \n is found. In that case, insert a "<?p?>".
 *
 * @param comment standard string
 * @return string converted to xml format.
 */
//@Deprecated
/*public*/ /*static*/ QString OperationsXml::convertToXmlComment(QString comment) {
//    QString buf;// = new StringBuffer();
//    for (int k = 0; k < comment.length(); k++) {
//        if (comment.mid(k).startsWith("\n"/*, k*/)) { // NOI18N
//            buf.append("<?p?>"); // NOI18N
//        } else {
//            buf.append(comment.mid(k, k + 1));
//        }
//    }
//    return buf/*.toString()*/;
 return comment;
}

/**
 * Convert xml string comment to standard string format one character at a
 * time, except when <?p?> is found. In that case, insert a \n and skip over
 * those characters.
 *
 * @param comment input xml comment string
 * @return output string converted to standard format
 */
//@Deprecated
/*public*/ /*static*/ QString OperationsXml::convertFromXmlComment(QString comment)
{
//    QString buf;// = new StringBuffer();
//    for (int k = 0; k < comment.length(); k++) {
//        if (comment.mid(k).startsWith("<?p?>"/*, k*/)) { // NOI18N
//            buf.append("\n"); // NOI18N
//            k = k + 4;
//        } else {
//            buf.append(comment.mid(k, k + 1));
//        }
//    }
//    return buf/*.toString()*/;
 return comment;
}

/**
 * Checks name for the file control characters:
 *
 * @param name The string to check for a valid file name.
 * @return true if name is okay, false if name contains a control character.
 */
/*public*/ /*static*/ bool OperationsXml::checkFileName(QString name) {
    if (name.contains(".") || name.contains("<") || name.contains(">") // NOI18N
            || name.contains(":") || name.contains("\"") || name.contains("\\") // NOI18N
            || name.contains("/") || name.contains("|") || name.contains("?") // NOI18N
            || name.contains("*")) { // NOI18N
        return false;
    }
    return true;
}

/**
 * Saves operation files that have been modified.
 */
/*public*/ /*static*/ void OperationsXml::save()
{
 Operations::OperationsSetupXml::instance()->writeFileIfDirty();

 Operations::LocationManagerXml::instance()->writeFileIfDirty(); // Need to save "moves" for track location
 Operations::RouteManagerXml::instance()->writeFileIfDirty(); // Only if user used setX&Y
 Operations::CarManagerXml::instance()->writeFileIfDirty(); // save train assignments
 Operations::EngineManagerXml::instance()->writeFileIfDirty(); // save train assignments
 Operations::TrainManagerXml::instance()->writeFileIfDirty(); // save train changes

}

/**
 * Checks to see if any operations files are dirty
 *
 * @return True if any operations parameters have been modified.
 */
/*public*/ /*static*/ bool OperationsXml::areFilesDirty()
{
 if (Operations::OperationsSetupXml::instance()->isDirty() || Operations::LocationManagerXml::instance()->isDirty()
         || Operations::RouteManagerXml::instance()->isDirty() || Operations::CarManagerXml::instance()->isDirty()
         || Operations::EngineManagerXml::instance()->isDirty() || Operations::TrainManagerXml::instance()->isDirty())
 {
     return true;
 }
 return false;
}
