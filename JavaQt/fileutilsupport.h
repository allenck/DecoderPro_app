#ifndef FILEUTILSUPPORT_H
#define FILEUTILSUPPORT_H

#include "bean.h"

class Logger;
class File;
class FileUtilSupport : public Bean
{
public:
 FileUtilSupport();
 /*public*/ QString getHomePath();
 /*public*/ void backup(File* file); //throws IOException
 /*public*/ void rotate(/*@NonNULL*/ File* file, int max, QString extension);// //throws IOException
 /*public*/ static FileUtilSupport* getDefault();

private:
 /*private*/ static /*final*/ QString homePath;// = System.getProperty("user.home") + File.separator; // NOI18N
 /*
  * Settable directories
  */
 /* JMRI program path, defaults to directory JMRI is executed from */
 /*private*/ QString programPath;// = null;
 /* path to jmri.jar */
 /*private*/ QString jarPath;// = null;
 /* path to the jython scripts directory */
 /*private*/ QString scriptsPath;// = null;
 /* path to the user's files directory */
 /*private*/ QString userFilesPath;// = null;
 /* path to the current profile */
 /*private*/ QString profilePath;// = null;
 // initialize logging
 ///*private*/ static /*final*/ Logger log = LoggerFactory.getLogger(FileUtilSupport.class);
 Logger* log;
 // default instance
 /*volatile*/ /*private*/ static FileUtilSupport* defaultInstance;// = null;


};

#endif // FILEUTILSUPPORT_H
