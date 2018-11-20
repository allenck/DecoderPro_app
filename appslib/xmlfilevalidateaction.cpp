#include "xmlfilevalidateaction.h"
#include "jfilechooser.h"
#include "file.h"
#include "xmlfile.h"
#include "logger.h"
#include "joptionpane.h"
#include <QTextStream>

//XmlFileValidateAction::XmlFileValidateAction(QObject* parent) : JmriAbstractAction(parent)
//{

//}
/**
 * Make sure an XML file is readable, and validates OK.
 *<p>
 * Can also be run from the command line with e.g.
 *    ./runtest.csh jmri/jmrit/XmlFileValidateAction foo.xml
 * in which case if there's a filename argument, it checks that directly, otherwise
 * it pops a file selection dialog-> (The dialog form has to be manually canceled when done)
 *
 * @author	Bob Jacobsen Copyright (C) 2005, 2007
 * @see jmri.jmrit.XmlFile
 * @see jmri.jmrit.XmlFileCheckAction
 */
// /*public*/ class XmlFileValidateAction extends jmri.util.swing.JmriAbstractAction {

/*public*/ XmlFileValidateAction::XmlFileValidateAction(QString s, QWidget* who) : JmriAbstractAction(s, who){
   // super(s);
 common();
    _who = who;
    xmlfile = new XmlFile();
}

/*public*/ XmlFileValidateAction::XmlFileValidateAction(QString  s, WindowInterface* wi)
 : JmriAbstractAction(s, (QObject*)(wi != NULL?wi->getFrame(): NULL))
{
    //this(s, wi!=NULL ? wi.getFrame() : NULL);
 common();
}

/*public*/ XmlFileValidateAction::XmlFileValidateAction(QObject *parent) : JmriAbstractAction(tr("Xml File Validate Action"), parent){
    //super(Bundle.getMessage("XmlFileValidateAction")); // NOI18N
 common();
}

void XmlFileValidateAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void XmlFileValidateAction::actionPerformed()
{
    if (fci == NULL) {
        fci = XmlFile::userFileChooser("XML files", "xml");
    }
    // request the filename from an open dialog
//    fci->rescanCurrentDirectory();
    int retVal = fci->showOpenDialog(_who);
    // handle selection or cancel
    if (retVal == JFileChooser::APPROVE_OPTION) {
        processFile(fci->getSelectedFile());
    } else {
        log->debug("XmlFileValidateAction cancelled in open dialog");
    }
}

/*protected*/ void XmlFileValidateAction::processFile(File* file) {
    if (log->isDebugEnabled()) {
        log->debug("located file " + file->getPath() + " for XML processing");
    }
    // handle the file (later should be outside this thread?)
    try {
        xmlfile->setValidate(XmlFile::Validate::CheckDtdThenSchema);
        readFile(file);
    } catch (Exception ex) {
        showFailResults(_who, ex.getMessage());
        return;
    }
#if 0
    try {
        XmlFile::verify = true;
        readFile(file);
    } catch (Exception ex) {
        // because of XInclude, we're doing this
        // again to validate the entire file
        // without losing the error message
        XmlFile::verify = false;
        QDomDocument doc;

        try {
            //InputStream stream = new BufferedInputStream(new FileInputStream(file));
         QTextStream* stream;
         QFile* f = new QFile(file->getPath());
         if(f->open(QIODevice::ReadOnly))
         {
          stream = new QTextStream(f);
         }
         else {
          throw FileNotFoundException(tr("%1 not found").arg(f->fileName()));
         }

            SAXBuilder builder = new SAXBuilder("org.apache.xerces.parsers.SAXParser", false);
            builder.setEntityResolver(new JmriLocalEntityResolver());
            builder.setFeature("http://apache.org/xml/features/xinclude", true);
            builder.setFeature("http://apache.org/xml/features/xinclude/fixup-base-uris", false);
            builder.setFeature("http://apache.org/xml/features/validation/schema", false);
            builder.setFeature("http://apache.org/xml/features/validation/schema-full-checking", false);
            builder.setFeature("http://xml.org/sax/features/namespaces", true);
            doc = builder.build(new BufferedInputStream(stream));
        } catch (/*JDOMException | IOException ex2*/ Exception ex2) {
            showFailResults(_who, "Err(1): " + ex2);
            return;
        }
        XMLOutputter outputter = new XMLOutputter();
        outputter.setFormat(Format.getPrettyFormat()
                .setLineSeparator(System.getProperty("line.separator"))
                .setTextMode(Format.TextMode.PRESERVE));
        QString out;// = new StringWriter();
        try {
            outputter.output(doc, out);
        } catch (IOException ex2) {
            showFailResults(_who, "Err(4): " + ex2);
            return;
        }
        QString input = new QString(out/*.getBuffer()*/);
        SAXBuilder builder = new SAXBuilder("org.apache.xerces.parsers.SAXParser", true);
        builder.setEntityResolver(new JmriLocalEntityResolver());
        builder.setFeature("http://apache.org/xml/features/xinclude", true);
        builder.setFeature("http://apache.org/xml/features/xinclude/fixup-base-uris", false);
        builder.setFeature("http://apache.org/xml/features/validation/schema", true);
        builder.setFeature("http://apache.org/xml/features/validation/schema-full-checking", true);
        builder.setFeature("http://xml.org/sax/features/namespaces", true);
        try {
            XmlFile.verify = true;
            builder.build(input).getRootElement();
        } catch (/*JDOMException | IOException ex2*/Exception ex2) {
            showFailResults(_who, "Err(2): " + ex2);
            return;
        }

        showFailResults(_who, "Err(3): " + ex);
        return;
    } finally {
        XmlFile::verify = original;

    }
#endif
    showOkResults(_who, "OK");
    if (log->isDebugEnabled())
    {
        log->debug("parsing complete");
    }
}

/*protected*/ void XmlFileValidateAction::showOkResults(QWidget* who, QString  text) {
    JOptionPane::showMessageDialog(who, text);
}

/*protected*/ void XmlFileValidateAction::showFailResults(QWidget* who, QString  text) {
    JOptionPane::showMessageDialog(who, text);
}

/**
 * Ask SAX to read and verify a file
 */
void XmlFileValidateAction::readFile(File* file) //throw (JDOMException, IOException)
{

//    {
//    };   // odd syntax is due to XmlFile being abstract

 xmlfile->rootFromFile(file);

}

// never invoked, because we overrode actionPerformed above
//@Override
/*public*/ JmriPanel* XmlFileValidateAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
#if 0 // TODO: for command line
// Main entry point fires the action
static /*public*/ void XmlFileValidateAction::main(QStringList args) {
    // if a 1st argument provided, act
    if (args.length() == 0 ) {
        new XmlFileValidateAction("", /*(Component)*/ NULL)->actionPerformed(NULL);
    } else {
//        jmri.util.Log4JUtil.initLogging("default.lcf");
        new XmlFileValidateAction("", (Component) NULL){
            //@Override
            protected void showFailResults(Component who, QMenuBar*  text) {
                System.out.println(text);
            }
            //@Override
            protected void showOkResults(Component who, QMenuBar*  text) {
                // silent if OK
            }
        }.processFile(new File(args[0]));
    }
}
#endif
