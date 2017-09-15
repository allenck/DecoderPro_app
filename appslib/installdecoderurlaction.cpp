#include "installdecoderurlaction.h"
#include "logger.h"
#include <file.h>
#include <QUrl>
#include "fileutil.h"
#include "decoderindexfile.h"
#include <QMessageBox>


InstallDecoderURLAction::InstallDecoderURLAction(QObject *parent) :
  JmriAbstractAction(parent)
{
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
    }

    /*public*/ InstallDecoderURLAction::InstallDecoderURLAction(QString s, QIcon i, WindowInterface* wi) : JmriAbstractAction(s, i,wi)
{
        //super(s, i, wi);
 common();
    }

    /*public*/ InstallDecoderURLAction::InstallDecoderURLAction(QString s, QObject* parent) : JmriAbstractAction(s, parent)
{
        //super(s);
 common();
    }

/*public*/ InstallDecoderURLAction::InstallDecoderURLAction(QString s, QWidget* who): JmriAbstractAction(s, (QObject*)who)
{
        //super(s);
 common();
    }

    //static ResourceBundle rb = NULL;
void InstallDecoderURLAction::common()
{
 log = new Logger("InstallDecoderURLAction");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

    QUrl* pickURL(QWidget* who) {
#if 0
        // show input dialog
        QString urlname = JOptionPane.showInputDialog(who, rb.getString("InputURL"));
        try {
            URL url = new URL(urlname);
            return url;
        } catch (java.net.MalformedURLException e) {
            JOptionPane.showMessageDialog(who, rb.getString("MalformedURL"));
        }
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
#if 0
        log->debug("[" + from->getFile() + "]");

        // get output name
        File* temp = new File(from->getFile());

        log->debug("[" + temp->toString() + "]");

        // ensure directories exist
        FileUtil::createDirectory(FileUtil::getUserFilesPath() + "decoders");

        // output file
        File* toFile = new File(FileUtil::getUserFilesPath() + "decoders" + File::separator + temp->getName());
        log->debug("[" + toFile->toString() + "]");

        // first do the copy, but not if source and output files are the same
        if (!temp->toString()==(toFile->toString())) {
            if (!copyfile(from, toFile, _who)) {
                return;
            }
        } else {
            // write a log entry
            log->info("Source and destination files identical - file not copied");
            log->info("  source file: " + temp->toString());
            log->info("  destination: " + toFile->toString());
        }

        // and rebuild index
        DecoderIndexFile::forceCreationOfNewIndex();

        // Done OK
        //JOptionPane.showMessageDialog(who, rb.getString("CompleteOK"));
        QMessageBox::information(who, tr("Information"), tr("Completed OK"));
#endif
    }

   // @edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "OBL_UNSATISFIED_OBLIGATION", justification = "Looks like false positive")
    bool InstallDecoderURLAction::copyfile(QUrl* from, File* toFile, QWidget* who) {
        QDataStream* in = NULL;
        QDataStream* out = NULL;
#if 0
        try {
            in = from->openConnection().getInputStream();

            // open for overwrite
            out = new FileOutputStream(toFile);

            byte[] buf = new byte[1024];
            int len;
            while ((len = in.read(buf)) > 0) {
                out.write(buf, 0, len);
            }
            // done - finally cleans up
        } catch (FileNotFoundException ex) {
            log->debug("" + ex);
            JOptionPane.showMessageDialog(who, rb.getString("CopyError1"));
            return false;
        } catch (IOException e) {
            log->debug("" + e);
            JOptionPane.showMessageDialog(who, rb.getString("CopyError2"));
            return false;
        } finally {
            try {
                if (in != NULL) {
                    in.close();
                }
            } catch (IOException e1) {
                log->error("exception closing in stream", e1);
            }
            try {
                if (out != NULL) {
                    out.close();
                }
            } catch (IOException e2) {
                log->error("exception closing out stream", e2);
            }
        }
#endif
        return true;
    }

    bool InstallDecoderURLAction::checkFile(QUrl* url, QWidget* who)
    {
        // read the definition to check it (later should be outside this thread?)
#if 0
        try {
            QDomElement root = readFile(url);
            if (log->isDebugEnabled()) {
                log->debug("parsing complete");
            }

            // check to see if there's a decoder element
            if (root.getChild("decoder") == NULL) {
                JOptionPane.showMessageDialog(who, rb.getString("WrongContent"));
                return false;
            }
            return true;

        } catch (Exception ex) {
            log->debug("" + ex);
            JOptionPane.showMessageDialog(who, rb.getString("ParseError"));
            return false;
        }
    }

    /**
     * Ask SAX to read and verify a file
     */
    Element readFile(URL url) throws org.jdom2.JDOMException, java.io.IOException {
        XmlFile xf = new XmlFile() {
        };   // odd syntax is due to XmlFile being abstract

        return xf.rootFromURL(url);
#endif
    }

    // never invoked, because we overrode actionPerformed above
    /*public*/ JmriPanel* makePanel() {
        throw new IllegalArgumentException("Should not be invoked");
    }
