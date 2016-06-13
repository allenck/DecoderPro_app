#include "installdecoderurlaction.h"
#include <QUrl>
#include "file.h"
#include "fileutil.h"
#include <QTextStream>
#include "xmlfile.h"
#include "inputdialog.h"
#include <QMessageBox>
#include "decoderindexfile.h"

InstallDecoderURLAction::InstallDecoderURLAction(QObject *parent) :
  JmriAbstractAction((WindowInterface*)parent)
{
 common();
}
/**
 * Install decoder definition from URL
 *
 * @author	Bob Jacobsen Copyright (C) 2008
 * @version	$Revision: 28746 $
 * @see jmri.jmrit.XmlFile
 */
///*public*/ class InstallDecoderURLAction extends JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 2460646302372383168L;

/*public*/ InstallDecoderURLAction::InstallDecoderURLAction(QString s, WindowInterface* wi)
 :  JmriAbstractAction(s, wi)
{
 //super(s, wi);
 common();
}

/*public*/ InstallDecoderURLAction::InstallDecoderURLAction(QString s, QIcon i, WindowInterface* wi)
 :   JmriAbstractAction(s, i, wi)
{
 //super(s, i, wi);
 common();
}

///*public*/ InstallDecoderURLAction(String s) {
//    super(s);
//}

/*public*/InstallDecoderURLAction:: InstallDecoderURLAction(QString s, QWidget* who)
 :   JmriAbstractAction(who)
{
 //super(s);
 common();
 this->_who = who;
}

//static ResourceBundle rb = null;


QUrl* InstallDecoderURLAction::pickURL(QWidget* who)
{
 // show input dialog
 QString urlname;
//    = JOptionPane.showInputDialog(who, tr("Input URL"));
 InputDialog dlg(tr("Input URL"), urlname, NULL, who);
 if(dlg.exec() == QDialog::Accepted)
  urlname = dlg.value();
// try
// {
  QUrl* url = new QUrl(urlname);
  //return url;
// }
 //catch (MalformedURLException e)
 if(!url->isValid())
 {
  //OptionPane.showMessageDialog(who, tr("MalformedURL"));
  QMessageBox::critical(who, tr("Error"), tr("That URL isn't in a valid format"));
 }

 return url;
}

void InstallDecoderURLAction::common()
{
 log = new Logger("InstallDecoderURLAction");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void InstallDecoderURLAction::actionPerformed(ActionEvent* e)
{
//    if (rb == null) {
//        rb = ResourceBundle.getBundle("jmri.jmrit.decoderdefn.DecoderFile");
//    }

 // get the input URL
 QUrl* url = pickURL(_who);
 if (url == NULL) {
     return;
 }

 if (checkFile(url, _who)) {
     // OK, do the actual copy
     copyAndInstall(url, _who);
 }
//    rb = null;
}

void InstallDecoderURLAction::copyAndInstall(QUrl* from, QWidget* who)
{
 log->debug("[" + from->path() + "]");

 // get output name
 File* temp = new File(from->path());

 log->debug("[" + temp->toString() + "]");

 // ensure directories exist
 FileUtil::createDirectory(FileUtil::getUserFilesPath() + "decoders");

 // output file
 File* toFile = new File(FileUtil::getUserFilesPath() + "decoders" + File::separator + temp->getName());
 log->debug("[" + toFile->toString() + "]");

 // first do the copy, but not if source and output files are the same
 if (temp->toString()!=(toFile->toString()))
 {
  if (!copyfile(from, toFile, _who))
  {
   return;
  }
 }
 else
 {
  // write a log entry
  log->info("Source and destination files identical - file not copied");
  log->info("  source file: " + temp->toString());
  log->info("  destination: " + toFile->toString());
 }

 // and rebuild index
 DecoderIndexFile::forceCreationOfNewIndex();

 // Done OK
 //OptionPane.showMessageDialog(who, tr("CompleteOK"));
 QMessageBox::information(who, tr("OK"), tr("Completed OK"));
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "OBL_UNSATISFIED_OBLIGATION", justification = "Looks like false positive")
bool InstallDecoderURLAction::copyfile(QUrl* from, File* toFile, QWidget* who)
{
 QTextStream* in = NULL;
 QTextStream* out = NULL;
// try
// {
//  in = from->openConnection().getInputStream();
  if(from->isLocalFile())
  {
   QFile inFile(from->path());
   if(inFile.open(QIODevice::ReadOnly))
   {
    in = new QTextStream(&inFile);
   }
  }

  // open for overwrite
  QString path = toFile->getAbsolutePath();
  out = new QTextStream(&path,QIODevice::WriteOnly);

//  QByteArray buf =  QByteArray(1024,0);
//  int len;
//  while ((len = in->read(buf)) > 0) {
//      out->write(buf, 0, len);
//  }
  if(in != NULL && out != NULL)
  {
   QString buf = in->readAll();
   *out << buf;
  }
  // done - finally cleans up
// }
 //catch (FileNotFoundException ex)
 if(in == NULL)
 {
  //log->debug("" + ex.getMessage());
  //JOptionPane.showMessageDialog(who, tr("CopyError1"));
  QMessageBox::critical(who, tr("Error"), tr("File couldn't be copied"));
  return false;
 }
 //catch (IOException e)
 if(out == NULL)
 {
  //log->debug("" + e.getMessage());
  //JOptionPane.showMessageDialog(who, tr("CopyError2"));
  QMessageBox::critical(who, tr("Error"), tr("Error while copying file"));
  return false;
 }
 //finally {
//  try {
//      if (in != NULL) {
//          in->close();
//      }
//  } catch (IOException e1) {
//      log->error("exception closing in stream", e1.getMessage());
//  }
//  try {
//      if (out != NULL) {
//          out->close();
//      }
//  } catch (IOException e2) {
//      log->error("exception closing out stream", e2.getMessage());
//  }
// }

 return true;
}

bool InstallDecoderURLAction::checkFile(QUrl* url, QWidget* who)
{
 // read the definition to check it (later should be outside this thread?)
 try
 {
  QDomElement root;// = readFile(url);
  if(url->isLocalFile())
  {
   XmlFile* xf = new XmlFile();
   root = xf->rootFromFile(new QFile(url->path()));
  }
  else
   readFile(url);

  if (log->isDebugEnabled())
  {
   log->debug("parsing complete");
  }

  // check to see if there's a decoder element
  if (root.firstChildElement("decoder") == QDomElement())
  {
      //JOptionPane.showMessageDialog(who, tr("WrongContent"));
   QMessageBox::critical(who, tr("Error"), tr("The file doesn't contain a decoder definition."));
      return false;
  }
  return true;

 }
 catch (Exception ex)
 {
  log->debug( ex.getMessage());
  //JOptionPane.showMessageDialog(who, tr("ParseError"));
  QMessageBox::critical(who, tr("Error"), tr("The file doesn't contain valid XML."));
  return false;
 }
}

/**
 * Ask SAX to read and verify a file
 */
QDomElement InstallDecoderURLAction::readFile(QUrl* url) /*throw (JDOMException, IOException)*/
{
 XmlFile* xf = new XmlFile();
//    {
//    };   // odd syntax is due to XmlFile being abstract

 return xf->rootFromURL(url);
}

// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* InstallDecoderURLAction::makePanel()
{
 throw new IllegalArgumentException("Should not be invoked");
}
