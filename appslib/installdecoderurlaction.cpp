#include "installdecoderurlaction.h"
#include "logger.h"
#include <file.h>
#include <QUrl>
#include "fileutil.h"
#include "decoderindexfile.h"
#include <QMessageBox>
#include "inputdialog.h"
#include "joptionpane.h"
#include <QTextStream>
#include "xmlfile.h"
#include "xinclude/xinclude.h"

InstallDecoderURLAction::InstallDecoderURLAction(QObject *parent) :
  JmriAbstractAction(parent)
{
 common();
 _who = (QWidget*)parent;
}
/**
 * Install decoder definition from URL
 *
 * @author	Bob Jacobsen Copyright (C) 2008
 * @version	$Revision: 28746 $
 * @see jmri.jmrit.XmlFile
 */
// /*public*/ class InstallDecoderURLAction extends JmriAbstractAction {

    /**
     *
     */
    //private static final long serialVersionUID = 2460646302372383168L;

    /*public*/ InstallDecoderURLAction::InstallDecoderURLAction(QString s, WindowInterface* wi)
 : JmriAbstractAction(s,(QObject*)wi)
{
        //super(s, wi);
 common();
 _who = wi->getFrame();
    }

    /*public*/ InstallDecoderURLAction::InstallDecoderURLAction(QString s, QIcon i, WindowInterface* wi) : JmriAbstractAction(s, i,wi)
{
        //super(s, i, wi);
 common();
 _who = wi->getFrame();

    }

    /*public*/ InstallDecoderURLAction::InstallDecoderURLAction(QString s, QObject* parent) : JmriAbstractAction(s, parent)
{
        //super(s);
 common();
 if(qobject_cast<QWidget*>(parent) != NULL)
   _who = (QWidget*)parent;
}

/*public*/ InstallDecoderURLAction::InstallDecoderURLAction(QString s, QWidget* who): JmriAbstractAction(s, (QObject*)who)
{
 //super(s);
 common();
 _who = who;
}

//static ResourceBundle rb = NULL;
void InstallDecoderURLAction::common()
{
 log = new Logger("InstallDecoderURLAction");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

QUrl* InstallDecoderURLAction::pickURL(QWidget* who)
{
#if 1
 // show input dialog
 QString urlname = JOptionPane::showInputDialog(who, tr("URL to import:"));
// InputDialog* dlg = new InputDialog(tr("URL to import:"), "");
// if(dlg->exec() == QDialog::Accepted)
// {
//  QString urlname = dlg->value();


// try {
     QUrl* url = new QUrl(urlname);
     if(url->isValid())
      return url;
// } catch (java.net.MalformedURLException e) {
     JOptionPane::showMessageDialog(who, /*rb.getString("MalformedURL")*/tr("That URL isn't in a valid format"));
     //QMessageBox::critical(who, tr("Error"), tr("That URL isn't in a valid format"));
// }
#endif
    return NULL;
}

/*public*/ void InstallDecoderURLAction::actionPerformed(ActionEvent* /*e*/) {
//        if (rb == NULL) {
//            rb = ResourceBundle.getBundle("jmri.jmrit.decoderdefn.DecoderFile");
//        }

    // get the input URL
    QUrl* url = pickURL(_who);
    if (url == NULL) {
        return;
    }

    if (checkFile(url, _who)) {
        // OK, do the actual copy
        copyAndInstall(url, _who);
    }
//        rb = NULL;
}

void InstallDecoderURLAction::copyAndInstall(QUrl* from, QWidget* who) {
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
//  XInclude* xi = new XInclude();
//  xi->copyXml(from, new QUrl(toFile->getPath()));
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
#if 0
// @edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "OBL_UNSATISFIED_OBLIGATION", justification = "Looks like false positive")
bool InstallDecoderURLAction::copyfile(QUrl* from, File* toFile, QWidget* who) {
 QTextStream* in = NULL;
 QTextStream* out = NULL;
 try
 {
//  in = from->openConnection().getInputStream();
 QFile* inFile;
  if(from->isLocalFile())
  {
   inFile = new QFile(from->path());
   if(inFile->open(QIODevice::ReadOnly))
   {
    in = new QTextStream(inFile);
   }
   else
    throw new FileNotFoundException(tr("File not found: ") + from->path());
  }

  // open for overwrite
  QString path = toFile->getAbsolutePath();
  QFile* oFile = new QFile(path);
  if(oFile->open(QIODevice::WriteOnly))
   out = new QTextStream(oFile);
  if(out == NULL)
   throw new IOException(tr("output file = \"%1\"").arg(path));

//  QByteArray buf =  QByteArray(1024,0);
//  int len;
//  while ((len = in->read(buf)) > 0) {
//      out->write(buf, 0, len);
//  }
  if(in != NULL && out != NULL)
  {
   QString buf = in->readAll();
   *out << buf;
   out->flush();
   if(out->status() != QTextStream::Ok) throw Exception(tr("write error"));
  }
  // done - finally cleans up
 }
 catch (FileNotFoundException ex)
 {
  //log->debug("" + ex.getMessage());
  //JOptionPane.showMessageDialog(who, tr("CopyError1"));
  QMessageBox::critical(who, tr("Error"), tr("File couldn't be copied"));
  return false;
 }
 catch (IOException e)
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
#else
bool InstallDecoderURLAction::copyfile(QUrl* from, File* toFile, QWidget* who) {
 XInclude* xInclude = new XInclude();
 xInclude->copyXml(from, toFile, who);
}
#endif
bool InstallDecoderURLAction::checkFile(QUrl* url, QWidget* who)
{
 // read the definition to check it (later should be outside this thread?)
 QFile* f;
 try
 {
  QDomElement root;// = readFile(url);
  if(url->isLocalFile())
  {
   XmlFile* xf = new XmlFile();
   f = new QFile(url->path());
   if(!f->exists())
    throw  new FileNotFoundException(tr("File not found: ") + f->fileName());
   root = xf->rootFromFile(f);
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
//   QMessageBox::critical(who, tr("Error"), tr("The file doesn't contain a decoder definition."));
//      return false;
   throw Exception(tr("File \"%1\" does not contain a decoder definition").arg(f->fileName()));
  }
  return true;

 }
 catch (Exception ex)
 {
  log->debug( ex.getMessage());
  //JOptionPane.showMessageDialog(who, tr("ParseError"));
  QMessageBox::critical(who, tr("Error"), tr("The file doesn't contain valid XML.") + " " + ex.getMessage());
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
/*public*/ JmriPanel* InstallDecoderURLAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
