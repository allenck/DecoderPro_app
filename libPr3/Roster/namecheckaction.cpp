#include "namecheckaction.h"
#include "xmlfile.h"
#include "file.h"
#include "jfilechooser.h"
#include "namefile.h"
#include "joptionpane.h"

//NameCheckAction::NameCheckAction()
//{

//}
/**
 * Check the names in an XML decoder file against the names.xml definitions
 *
 * @author	Bob Jacobsen Copyright (C) 2001, 2007
 * @see jmri.jmrit.XmlFile
 */
///*public*/ class NameCheckAction extends AbstractAction {

/*public*/ NameCheckAction::NameCheckAction(QString s, QWidget* who) :AbstractAction(s, who) {
    //super(s);
 log = new Logger("NameCheckAction");
    _who = who;
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}


//@SuppressWarnings("unchecked")
//@Override
/*public*/ void NameCheckAction::actionPerformed() {
    if (fci == NULL) {
        fci = XmlFile::userFileChooser("XML files", "xml");
    }
    // request the filename from an open dialog
//    fci.rescanCurrentDirectory();
    int retVal = fci->showOpenDialog(_who);
    // handle selection or cancel
    if (retVal == JFileChooser::APPROVE_OPTION)
    {
     File* file = fci->getSelectedFile();
     if (log->isDebugEnabled()) {
         log->debug("located file " + file->getPath() + " for XML processing");
     }
     // handle the file (later should be outside this thread?)
     try {
         QDomElement root = readFile(file);
         if (log->isDebugEnabled()) {
             log->debug("parsing complete");
         }

         // check to see if there's a decoder element
         if (root.firstChildElement("decoder").isNull()) {
             log->warn("Does not appear to be a decoder file");
             return;
         }

//            Iterator<Element> iter = root.getChild("decoder").getChild("variables")
//                    .getDescendants(new ElementFilter("variable"));
         QList<QDomElement> list = QList<QDomElement>();
         QDomNodeList nl = root.firstChildElement("variable").elementsByTagName("variables");
         for(int i=0; i < nl.size(); i++)
         {
          QDomNodeList variableList = nl.at(i).toElement().elementsByTagName("variable");
          for(int j=0; j < variableList.size(); j++)
           list.append(variableList.at(j).toElement());
         }
         QListIterator<QDomElement> iter(list);

         NameFile* nfile = NameFile::instance();

         QString warnings = "";

         while (iter.hasNext()) {
             QDomElement varElement = iter.next();

             // for each variable, see if can find in names file
             QString labelAttr = varElement.attribute("label");
             QString label = NULL;
             if (labelAttr != NULL) {
                 label = labelAttr;
             }
             QString itemAttr = varElement.attribute("item");
             QString item = NULL;
             if (itemAttr != NULL) {
                 item = itemAttr;
             }
             if (log->isDebugEnabled()) {
                 log->debug("Variable called \""
                         + ((label != NULL) ? label : "<none>") + "\" \""
                         + ((item != NULL) ? item : "<none>"));
             }
             if (!(label == NULL ? false : nfile->checkName(label))
                     && !(item == NULL ? false : nfile->checkName(item))) {
                 log->warn("Variable not found: label=\""
                         + ((label != NULL) ? label : "<none>") + "\" item=\""
                         + ((item != NULL) ? label : "<none>") + "\"");
                 warnings += "Variable not found: label=\""
                         + ((label != NULL) ? label : "<none>") + "\" item=\""
                         + ((item != NULL) ? item : "<none>") + "\"\n";
             }
         }

         if (warnings != ("")) {
             JOptionPane::showMessageDialog(_who, warnings);
         } else {
             JOptionPane::showMessageDialog(_who, "No mismatched items found");
         }

     } catch (/*HeadlessException | IOException | JDOMException ex*/Exception ex) {
         JOptionPane::showMessageDialog(_who, "Error parsing decoder file: " + ex.getMessage());
     }

    } else {
        log->debug("XmlFileCheckAction cancelled in open dialog");
    }
}

/**
 * Ask SAX to read and verify a file
 */
QDomElement NameCheckAction::readFile(File* file) throw (JDOMException, IOException) {
    XmlFile* xf = new XmlFile();
//    {
//    };   // odd syntax is due to XmlFile being abstract

    return xf->rootFromFile(file);

}
