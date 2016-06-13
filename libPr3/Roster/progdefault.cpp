#include "progdefault.h"
#include "fileutil.h"
#include "xmlfilenamefilter.h"
#include "xmlfile.h"

ProgDefault::ProgDefault(QObject *parent) :
    QObject(parent)
{
}
/**
 * Functions for use with programmer files, including the default file name. <P>
 * This was refactored from LocoSelPane in JMRI 1.5.3, which was the the right
 * thing to do anyway. But the real reason was that on MacOS Classic the static
 * member holding the default programmer name was being overwritten when the
 * class was (erroneously) initialized for a second time. This refactoring did
 * not fix the problem. What did fix it was an ugly hack in the
 * {@link CombinedLocoSelPane} class; see comments there for more information.
 *
 * @author	Bob Jacobsen Copyright (C) 2001, 2002
 * @version	$Revision: 22547 $
 */
///*public*/ class ProgDefault {

/*static*/ /*public*/ QStringList ProgDefault::findListOfProgFiles()
{
 Logger* log = new Logger("ProgDefault");
 // create an array of file names from prefs/programmers, count entries
 int np = 0;
 QStringList sp = QStringList();
 FileUtil::createDirectory(FileUtil::getUserFilesPath() + "programmers");
 QDir* fp = new QDir(FileUtil::getUserFilesPath() + "programmers");
 //XmlFilenameFilter* filter = new XmlFilenameFilter();
 QStringList filter = QStringList() << "*.xml";
 if (fp->exists())
 {
  sp = fp->entryList(filter);
  np = sp.length();
 }
 else
 {
  log->warn(FileUtil::getUserFilesPath() + "programmers was missing, though tried to create it");
 }
 if (log->isDebugEnabled())
 {
  log->debug("Got " + QString::number(np) + " programmers from " + fp->absolutePath());
 }
 // create an array of file names from xml/programmers, count entries
 fp = new QDir(XmlFile::xmlDir() + "programmers");
 int nx;
 QStringList sx;
 if (fp->exists())
 {
  sx = fp->entryList(filter);
  nx = sx.length();
  if (log->isDebugEnabled())
  {
   log->debug("Got " + QString::number(nx) + " programmers from " + fp->absolutePath());
  }
 }
 else
 {
  // create an array of file names from jmri.jar!xml/programmers, count entries
  QStringList sr =  QStringList();
//        Enumeration je = FileUtil::jmriJarFile().entries();
//        while (je.hasMoreElements()) {
//            QString name = ((JarEntry) je.nextElement()).getName();
//            if (name.startsWith("xml" + QDir::separator() + "programmers") && name.endsWith(".xml")) {
//                sr.append(name.mid(name.lastIndexOf(QDir::separator())));
//            }
// }
        //sx = sr.toArray(new QStringList()); //String[sr.size()]);
  foreach (QString s, sr)
  {
   sx.append(s);
  }
  nx = sx.length();
  if (log->isDebugEnabled())
  {
   log->debug("Got " + QString::number(nx) + " programmers from jmri.jar");
  }
 }
 // copy the programmer entries to the final array
 // note: this results in duplicate entries if the same name is also local.
 // But for now I can live with that.
 QStringList sbox =  QStringList(); //[np + nx];
 int n = 0;
 foreach (QString s,  sp)
 {
    //sbox[n++] = s.mid(0, s.length() - 4);
  sbox.append(s.mid(0, s.length() - 4));
 }
 foreach (QString s, sx) {
    sbox.append( s.mid(0, s.length() - 4));
 }
 return sbox;
}
/*volatile*/ /*static*/ QString ProgDefault::defaultProgFile = "";

/*synchronized*/ /*static*/ /*public*/ QString ProgDefault::getDefaultProgFile()
{
    Logger* log = new Logger("ProgDefault");
    if (log->isDebugEnabled()) {
        log->debug(tr("get programmer: ") + defaultProgFile);
    }
 return defaultProgFile;
}

/*synchronized*/ /*static*/ /*public*/ void ProgDefault::setDefaultProgFile(QString s)
{
 Logger* log = new Logger("ProgDefault");
 if (log->isDebugEnabled())
 {
  log->debug("set programmer: " + s);
 }
 defaultProgFile = s;
}

