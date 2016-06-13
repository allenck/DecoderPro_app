#include "storexmlvsdecoderaction.h"
#include "jfilechooser.h"
#include "xmlfile.h"
#include "vsdecoderpane.h"
#include "storexmlconfigaction.h"
#include "file.h"
#include "vsdecodermanager.h"
#include "vsdecoder.h"


//StoreXmlVSDecoderAction::StoreXmlVSDecoderAction(QObject *parent) :
//  AbstractAction(parent)
//{
//}
/**
 * Save throttles to XML
 *
 * @author	Glen Oberhauser
 * @author Daniel Boudreau (C) Copyright 2008
 * @version $Revision: 28746 $
 */
//@SuppressWarnings("serial")
///*public*/ class StoreXmlVSDecoderAction extends AbstractAction {

    //static final ResourceBundle rb = VSDecoderBundle.bundle();

    /**
     * Constructor
     *
     * @param s Name for the action.
     */
    /*public*/ StoreXmlVSDecoderAction::StoreXmlVSDecoderAction(QString s,QObject *parent) :
  AbstractAction(s, parent)
{
        //super(s);
        // disable this ourselves if there is no throttle Manager
 /*
         if (jmri.InstanceManager.throttleManagerInstance() == null) {
         setEnabled(false);
         }
         */
 common();
    }

    /*public*/ StoreXmlVSDecoderAction::StoreXmlVSDecoderAction(QObject *parent) :
  AbstractAction(tr("Save Virtual Sound Decoder profile..."), parent) {
        //this("Save Virtual Sound Decoder profile...");
 common();
    }
void StoreXmlVSDecoderAction::common()
 {
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }
    /**
     * The action is performed. Let the user choose the file to save to. Write
     * XML for each ThrottleFrame.
     *
     * @param e The event causing the action.
     */
    /*public*/ void StoreXmlVSDecoderAction::actionPerformed(ActionEvent* e) {
        JFileChooser* fileChooser = XmlFile::userFileChooser(tr("XML Files"), "xml");
        fileChooser->setDialogType(JFileChooser::SAVE_DIALOG);
        fileChooser->setCurrentDirectory(new File(VSDecoderPane::getDefaultVSDecoderFolder()));
        File* file = StoreXmlConfigAction::getFileName(fileChooser);
        if (file == NULL) {
            return;
        }

        saveVSDecoderProfile(file);
    }

    /*public*/ void StoreXmlVSDecoderAction::saveVSDecoderProfile(File* f) {

        //try {
 QDomElement root = QDomElement();
 root.setTagName("VSDecoderConfig");

            QDomDocument doc = XmlFile::newDocument(root, XmlFile::dtdLocation + "vsdecoder-config.dtd");

            // add XSLT processing instruction
            // <?xml-stylesheet type="text/xsl" href="XSLT/throttle-layout-config.xsl"?>
     /*TODO			java.util.Map<String,String> m = new java.util.HashMap<String,String>();
             m.put("type", "text/xsl");
             m.put("href", jmri.jmrit.XmlFile.xsltLocation + "throttle-layout-config.xsl");
             ProcessingInstruction p = new ProcessingInstruction("xml-stylesheet", m);
             doc.addContent(0, p); */
            //QList<QDomElement> children = QList<QDomElement>();
            QListIterator<VSDecoder*> i(VSDecoderManager::instance()->getVSDecoderList());
            //for (java.util.Iterator<VSDecoder> i = VSDecoderManager::instance()->getVSDecoderList().iterator(); i.hasNext();) {
            while(i.hasNext())
            {
                VSDecoder* vsd = i.next();
                //children.append(vsd->getXml());
                root.appendChild(vsd->getXml());
            }

     // Throttle-specific stuff below.  Kept for reference
     /*
             // throttle list window
             children.add(ThrottleFrameManager.instance().getThrottlesListPanel().getXml() );

             // throttle windows
             for (Iterator<ThrottleWindow> i = ThrottleFrameManager.instance().getThrottleWindows(); i.hasNext();) {
             ThrottleWindow tw = i.next();
             Element throttleElement = tw.getXml();
             children.add(throttleElement);
             }
             */
            // End Throttle-specific stuff.
//            root.appendChild(children);

//            FileOutputStream o = new FileOutputStream(f);
            //try {
//                XMLOutputter fmt = new XMLOutputter();
//                fmt.setFormat(Format.getPrettyFormat()
//                        .setLineSeparator(System.getProperty("line.separator"))
//                        .setTextMode(Format.TextMode.PRESERVE));
//                fmt.output(doc, o);
            XmlFile* xmlFile = new XmlFile();
            xmlFile->writeXML(f,doc);
//            } catch (IOException ex) {
//                log.warn("Exception in storing VSDecoder xml: " + ex);
//            } finally {
//                o.close();
//            }
//        } catch (FileNotFoundException ex) {
//            log.warn("Exception in storing VSDecoder xml: " + ex);
//        } catch (IOException ex) {
//            log.warn("Exception in storing VSDecoder xml: " + ex);
//        }
    }
