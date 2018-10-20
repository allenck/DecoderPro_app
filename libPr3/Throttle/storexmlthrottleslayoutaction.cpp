#include "storexmlthrottleslayoutaction.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "throttlemanager.h"
#include "jfilechooser.h"
#include "storexmlconfigaction.h"
#include "throttlewindow.h"
#include "throttleframemanager.h"
#include "throttleslistpanel.h"
#include "file.h"

/**
 * Save throttles to XML
 *
 * @author Glen Oberhauser
 * @author Daniel Boudreau (C) Copyright 2008
 */
///*public*/ class StoreXmlThrottlesLayoutAction extends AbstractAction {

/**
 * Constructor
 *
 * @param s Name for the action.
 */
/*public*/ StoreXmlThrottlesLayoutAction::StoreXmlThrottlesLayoutAction(QString s, QObject* parent) : AbstractAction(s, parent){
    //super(s);
    // disable this ourselves if there is no throttle Manager
    if (InstanceManager::getNullableDefault("ThrottleManager") == NULL) {
        setEnabled(false);
    }
    connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

/*public*/ StoreXmlThrottlesLayoutAction::StoreXmlThrottlesLayoutAction(QObject* parent) : AbstractAction(tr("Save default throttle layout..."), parent) {
    //this("Save default throttle layout...");
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

/**
 * The action is performed. Let the user choose the file to save to. Write
 * XML for each ThrottleFrame.
 *
 * @param e The event causing the action.
 */
//@Override
/*public*/ void StoreXmlThrottlesLayoutAction::actionPerformed(/*ActionEvent e*/) {
    JFileChooser* fileChooser = XmlFile::userFileChooser(tr("XML files"), "xml");
    fileChooser->setDialogType(JFileChooser::SAVE_DIALOG);
    fileChooser->setCurrentDirectory(new File(ThrottleWindow::getDefaultThrottleFolder()));
    File* file = StoreXmlConfigAction::getFileName(fileChooser);
    if (file == NULL) {
        return;
    }
    saveThrottlesLayout(file);
}

/*public*/ void StoreXmlThrottlesLayoutAction::saveThrottlesLayout(File* f) {

    try {
  QDomDocument doc = QDomDocument();
        QDomElement root = doc.createElement("throttle-layout-config");
//  TODO:      doc = XmlFile::newDocument(root, XmlFile::getDefaultDtdLocation() + "throttle-layout-config.dtd");

        // add XSLT processing instruction
        // <?xml-stylesheet type="text/xsl" href="XSLT/throttle-layout-config.xsl"?>
/*TODO   java.util.Map<String,String> m = new java.util.HashMap<String,String>();
         m.put("type", "text/xsl");
         m.put("href", jmri.jmrit.XmlFile.xsltLocation + "throttle-layout-config.xsl");
         ProcessingInstruction p = new ProcessingInstruction("xml-stylesheet", m);
         doc.addContent(0, p); */
        doc.appendChild(root);

        //QDomNodeList children = QDomNodeList();

        // throttle list window
        //children.add(InstanceManager::getDefault("ThrottleFrameManager").getThrottlesListPanel().getXml());
        root.appendChild(((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesListPanel()->getXml());
#if 1
        // throttle windows
        QListIterator<ThrottleWindow*> i =((ThrottleFrameManager*) InstanceManager::getDefault("ThrottleFrameManager"))->getThrottleWindows();
        while(i.hasNext())
        {
            ThrottleWindow* tw = i.next();
            QDomElement throttleElement = tw->getXml();
            root.appendChild(throttleElement);
        }
        //root.setContent(children);

        //FileOutputStream o = new java.io.FileOutputStream(f);
        QFile fout(f->getPath());

        try {
//            XMLOutputter fmt = new XMLOutputter();
//            fmt.setFormat(Format.getPrettyFormat()
//                    .setLineSeparator(System.getProperty("line.separator"))
//                    .setTextMode(Format.TextMode.PRESERVE));
//            fmt.output(doc, o);
         if(!fout.open(QIODevice::WriteOnly)) throw IOException();
              QTextStream stream(&fout);
              doc.toString();
              stream.setCodec("UTF-8");
              doc.save(stream,2);
              fout.close();
        } catch (IOException ex) {
            log->warn("Exception in storing throttle xml: " + ex.getMessage());
        }
//              finally {
//            o.close();
//        }
#endif
    } catch (FileNotFoundException ex) {
        log->warn("Exception in storing throttle xml: " + ex.getMessage());
    } catch (IOException ex) {
        log->warn("Exception in storing throttle xml: " + ex.getMessage());
    }
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* StoreXmlThrottlesLayoutAction::log = LoggerFactory::getLogger("StoreXmlThrottlesLayoutAction");
