#include "locofile.h"
#include "cvtablemodel.h"
#include "fileutil.h"
#include "roster.h"
#include "file.h"
#include "variablevalue.h"
#include "loggerfactory.h"

LocoFile::LocoFile(QObject *parent) :
    XmlFile(parent)
{
 log = new Logger("LocoFile");
 log->setDebugEnabled(true);
}
/**
 * Represents and manipulates a locomotive definition, both as a file and
 * in memory.  The interal storage is a JDOM tree. See locomotive-config.xsd
 * <P>
 * This class is intended for use by RosterEntry only; you should not use it
 * directly. That's why this is not a public class.
 *
 * @author    Bob Jacobsen     Copyright (C) 2001, 2002, 2008
 * @author    Dennis Miller    Copyright (C) 2004
 * @author    Howard G. Penny  Copyright (C) 2005
 * @version   $Revision: 22547 $
 * @see       jmri.jmrit.roster.RosterEntry
 * @see       jmri.jmrit.roster.Roster
 */
//class LocoFile extends XmlFile {

/**
 * Convert to a cannonical text form for ComboBoxes, etc
 */
/*public*/ QString LocoFile::titleString() {
    return "no title form yet";
}

/**
 * Load a CvTableModel from the locomotive element in the File
 * @param loco A JDOM Element containing the locomotive definition
 * @param cvModel  An existing CvTableModel object which will have
 *                 the CVs from the loco Element appended.  It is
 *                 intended, but not required, that this be empty.
 */
//@SuppressWarnings("unchecked")
/*public*/ /*static*/ void LocoFile::loadCvModel(QDomElement loco, CvTableModel* cvModel, QString /*family*/){
    CvValue* cvObject;
    // get the CVs and load
    QString rosterName = loco.attribute("id");
    QDomElement values = loco.firstChildElement("values");

    // Ugly hack because of bug 1898971 in JMRI 2.1.2 - contents may be directly inside the
    // locomotive element, instead of in a nested values element
    if (values.isNull()) {
        // check for non-nested content, in which case use loco element
        QDomNodeList elementList = loco.elementsByTagName("CVvalue");
        if (!elementList.isEmpty()) values = loco;
    }
  if(values.isNull())
  {
    //for (Element element : values.getChildren("CVvalue"))
    QDomNodeList nl = values.elementsByTagName("CVvalue");
    for(int i=0; i < nl.size(); i++)
    {
     QDomElement element = nl.at(i).toElement();
     // locate the row
     if (element.attribute("name") == "") {
         if (log->isDebugEnabled()) {
             log->debug("unexpected null in name " + element.tagName()); // + " " + element.getAttributes());
         }
         break;
     }
     if (element.attribute("value") == "") {
         if (log->isDebugEnabled()) {
             log->debug("unexpected null in value " + element.tagName()); // + " " + element.getAttributes());
         }
         break;
     }

     QString name = element.attribute("name");
     QString value = element.attribute("value");
     log->debug(tr("CV named %1 has value: %2").arg(name).arg(value));

     cvObject = cvModel->allCvMap()->value(name);
     if (cvObject == nullptr) {
         // need to disable this warning as ESU files do not generate CV entries until panel load time
         // log.warn("CV "+name+" was in loco file, but not defined by the decoder definition");
         cvModel->addCV(name, false, false, false);
         cvObject = cvModel->allCvMap()->value(name);
     }
     cvObject->setValue((value).toInt());
     cvObject->setState(CvValue::FROMFILE);
    }
} else {
 log->error(tr("no values element found in config file; CVs not configured for ID=\"%1\"").arg( rosterName));
}

    // ugly hack - set CV17 back to fromFile if present
    // this is here because setting CV17, then CV18 seems to set
    // CV17 to Edited.  This needs to be understood & fixed.
    cvObject = cvModel->allCvMap()->value("17");
    if (cvObject!=NULL) cvObject->setState(CvValue::FROMFILE);
}

/**
 * Load a VariableTableModel from the locomotive element in the File
 *
 * @param loco    A JDOM Element containing the locomotive definition
 * @param varModel An existing VariableTableModel object
 */
/*public*/ /*static*/ void LocoFile::loadVariableModel(QDomElement loco, VariableTableModel* varModel) {

    QDomElement values = loco.firstChildElement("values");

    if (values.isNull()) {
        log->error(tr("no values element found in config file; Variable values not loaded for \"%1\"").arg(loco.attribute("id")));
        return;
    }

    QDomElement decoderDef = values.firstChildElement("decoderDef");

    if (decoderDef.isNull()) {
        log->error(tr("no decoderDef element found in config file; Variable values not loaded for \"%1\"").arg(loco.attribute("id")));
        return;
    }


    // get the Variable values and load
    if (log->isDebugEnabled()) {
        log->debug("Found " + QString::number(decoderDef.elementsByTagName("varValue").size()) + " varValue elements");
    }

    // preload an index
    QMap<QString, VariableValue*> map = QMap<QString, VariableValue*>();
    for (int i = 0; i < varModel->getRowCount(); i++) {
        log->debug(tr("  map put %1 to %2").arg(varModel->getItem(i)).arg(varModel->getVariable(i)->getCvDescription()));
        map.insert(varModel->getItem(i), varModel->getVariable(i));
        map.insert(varModel->getLabel(i), varModel->getVariable(i));
    }

    //for (Element element : decoderDef.getChildren("varValue"))
    QDomNodeList nl = decoderDef.elementsByTagName("varValue");
    for(int i=0; i < nl.size(); i++)
    {
     QDomElement element = nl.at(i).toElement();
        // locate the row
        if (element.attribute("item") == "") {
            if (log->isDebugEnabled()) {
                log->debug(tr("unexpected null in item %1 %2").arg(element.tagName()).arg( element.tagName()));
            }
            break;
        }
        if (element.attribute("value") == "") {
            if (log->isDebugEnabled()) {
                log->debug(tr("unexpected null in value %1 %2").arg(element.tagName()).arg(element.tagName()));
            }
            break;
        }

        QString item = element.attribute("item");
        QString value = element.attribute("value");
        log->debug(tr("Variable \"%1\" has value: %2").arg(item).arg(value));

        VariableValue* var = map.value(item);
        if (var != nullptr) {
            var->setValue(value);
        } else {
            if (selectMissingVarResponse(item) == MessageResponse::REPORT) {
                log->warn(tr("Did not find locofile variable \"%1\" in decoder definition, not loading").arg(item));
            }
        }
    }
}

/**
 * Determine if a missing variable in decoder definition should be logged
 * @param var Name of missing variable
 * @return Decision on how to handle
 */
/*protected*/ /*static*/ LocoFile::MessageResponse LocoFile::selectMissingVarResponse(QString var) {
    if (var.startsWith("ESU Function Row")) return LocoFile::MessageResponse::IGNORE; // from jmri.jmrit.symbolicprog.FnMapPanelESU
    return LocoFile::MessageResponse::REPORT;
}

/**
 * Write an XML version of this object, including also the RosterEntry
 * information, and memory-resident decoder contents.
 *
 * Does not do an automatic backup of the file, so that
 * should be done elsewhere.
 *
 * @param file Destination file. This file is overwritten if it exists.
 * @param cvModel provides the CV numbers and contents
 * @param iCvModel provides the Indexed CV numbers and contents
 * @param variableModel provides the variable names and contents
 * @param r  RosterEntry providing name, etc, information
 */
/*public*/ void LocoFile::writeFile(QFile* file, CvTableModel* cvModel, /*IndexedCvTableModel* iCvModel, */VariableTableModel* variableModel, RosterEntry* r)
{
 QFileInfo* info = new QFileInfo(*file);
 if (log->isDebugEnabled()) log->debug("writeFile to "+info->absoluteFilePath()+" "+info->fileName());
 try
 {
  // This is taken in large part from "Java and XML" page 368
  QDomDocument doc;
  QDomProcessingInstruction p = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
  doc.appendChild(p);
  p = doc.createProcessingInstruction("xml-stylesheet", QString("type=\"text/xsl\",href=\"%1locomotive.xsl\"").arg(xsltLocation));
  doc.appendChild(p);

  // create root element
  QDomElement root = doc.createElement("locomotive-config");
  root.setTagName("locomotive-config");
//        root.setAttribute("noNamespaceSchemaLocation",
//            "http://jmri.org/xml/schema/locomotive-config"+Roster::schemaVersion+".xsd",
//            org.jdom.Namespace.getNamespace("xsi",
//                "http://www.w3.org/2001/XMLSchema-instance"));
  root.setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
  root.setAttribute("xsi:noNamespaceSchemaLocation", "http://jmri.org/xml/schema/locomotive-config.xsd");

        //QDomDocument doc = newDocument(root);

        // add XSLT processing instruction
        // <?xml-stylesheet type="text/xsl" href="XSLT/locomotive.xsl"?>
//        java.util.Map<String,String> m = new java.util.HashMap<String,String>();
//        m.put("type", "text/xsl");
//        m.put("href", xsltLocation+"locomotive.xsl");
//        ProcessingInstruction p = new ProcessingInstruction("xml-stylesheet", m);
//        doc.addContent(0,p);
  addDefaultInfo(root);
  // add top-level elements
  QDomElement locomotive = r->store(doc);   // the locomotive element from the RosterEntry

  root.appendChild(locomotive);
  QDomElement values = doc.createElement("values");
        locomotive.appendChild(values);

        // Append a decoderDef element to values
        QDomElement decoderDef;
        values.appendChild(decoderDef = doc.createElement("decoderDef"));
        // add the variable values to the decoderDef Element
        if (variableModel!=NULL)
        {
            for (int i = 0; i < variableModel->rowCount(QModelIndex()); i++)
         {
          QDomElement elem;
          decoderDef.appendChild(elem =doc.createElement("varValue"));
                                      elem.setAttribute("item", variableModel->getLabel(i));
                                      elem.setAttribute("value", variableModel->getValString(i));
          }
            // mark file as OK
          variableModel->setFileDirty(false);
        }

        // add the CV values to the values Element
        if (cvModel!=NULL)
        {
            for (int i = 0; i < cvModel->rowCount(QModelIndex()); i++)
         {
          QDomElement elem;
                values.appendChild(elem=doc.createElement("CVvalue"));
                                  elem.setAttribute("name", cvModel->getName(i));
                                  elem.setAttribute("value", cvModel->getValString(i));
         }
        }

//        // add the Indexed CV values to the
//        if (iCvModel!=NULL)
//        {
//            for (int i = 0; i < iCvModel->rowCount(QModelIndex()); i++)
//         {
//          QDomElement elem;
//                values.appendChild(elem =doc.createElement("indexedCVvalue"));
//                                  elem.setAttribute("name", iCvModel->getName(i));
//                                  elem.setAttribute("piCv", ((iCvModel->getCvByRow(i))->piCv()));
//                                  elem.setAttribute("piVal", QString::number((iCvModel->getCvByRow(i))->piVal()));
//                                  elem.setAttribute("siCv", ((iCvModel->getCvByRow(i))->siCv()));
//                                  elem.setAttribute("siVal", QString::number((iCvModel->getCvByRow(i))->siVal()));
//                                  elem.setAttribute("iCv", ((iCvModel->getCvByRow(i))->iCv()));
//                                  elem.setAttribute("value", iCvModel->getValString(i));
//            }
//        }
        doc.appendChild(root);
        writeXML(file, doc);

    }
    catch (IOException ex) {
        log->error("IOException"/*, ex*/);
    }
}

/**
 * Write an XML version of this object from an existing XML tree,
 * updating only the ID string.
 *
 * Does not do an automatic backup of the file, so that
 * should be done elsewhere. This is intended for copy and import
 * operations, where the tree has been read from an existing file.
 * Hence, only the "ID" information in the roster entry is updated.
 * Note that any multi-line comments are not changed here.
 *
 * @param pFile Destination file. This file is overwritten if it exists.
 * @param pRootElement Root element of the JDOM tree to write.
 *                      This should be of type "locomotive-config", and
 *                      should not be in use elsewhere (clone it first!)
 * @param pEntry RosterEntry providing name, etc, information
 */
/*public*/ void LocoFile::writeFile(File* pFile, QDomElement pRootElement, RosterEntry* pEntry)
{
 writeFile(new QFile(pFile->getAbsoluteFile()),pRootElement, pEntry);
}

/*public*/ void LocoFile::writeFile(QFile* pFile, QDomElement pRootElement, RosterEntry* pEntry)
{
 QFileInfo* info = new QFileInfo(*pFile);
 if (log->isDebugEnabled()) log->debug("writeFile to "+info->absoluteFilePath()+" "+info->fileName());
 try
 {
  // This is taken in large part from "Java and XML" page 368

  // create root element
  QDomDocument doc = newDocument(pRootElement, dtdLocation+"locomotive-config.dtd");

  // Update the locomotive.id element
  if (log->isDebugEnabled()) log->debug("pEntry: "+pEntry->getId());
  //pRootElement.firstChildElement("locomotive").attribute("id").setValue(pEntry.getId());
  pRootElement.firstChildElement("locomotive").setAttribute("id",pEntry->getId());

  addDefaultInfo(pRootElement);
  writeXML(pFile, doc);
 }
    catch (Exception ex) {
        // need to trace this one back
//        ex.printStackTrace();
    }
}

/**
 * Write an XML version of this object, updating the RosterEntry
 * information, from an existing XML tree.
 *
 * Does not do an automatic backup of the file, so that
 * should be done elsewhere. This is intended for
 * writing out changes to the RosterEntry information only.
 *
 * @param pFile Destination file. This file is overwritten if it exists.
 * @param existingElement Root element of the existing JDOM tree containing
 *                           the CV and variable contents
 * @param newLocomotive Element from RosterEntry providing name, etc, information
 */
/*public*/ void LocoFile::writeFile(QFile* pFile, QDomElement existingElement, QDomElement newLocomotive)
{
    QFileInfo* info = new QFileInfo(*pFile);
    if (log->isDebugEnabled()) log->debug("writeFile to "+info->absolutePath()+" "+info->fileName());
    try {
        // This is taken in large part from "Java and XML" page 368

        // create root element
        //QDomElement root = doc.createElement("locomotive-config");
        QDomElement root;
        root.setTagName("locomotive-config");
        QDomDocument doc = newDocument(root, dtdLocation+"locomotive-config.dtd");
        root.appendChild(newLocomotive);

        // add XSLT processing instruction
        // <?xml-stylesheet type="text/xsl" href="XSLT/locomotive.xsl"?>
//        QMap<QString,QString>* m = new QMap<QString,QString>();
//        m->insert("type", "text/xsl");
//        m->insert("href", xsltLocation+"locomotive.xsl");
//        ProcessingInstruction* p = new ProcessingInstruction("xml-stylesheet", m);
        QDomProcessingInstruction p = doc.createProcessingInstruction("xml-stylesheet", QString("type=\"text/xsl\",href=\"%1locomotive.xsl").arg(xsltLocation));
        doc.appendChild(p);

        // Add the variable info
        QDomElement values = existingElement.firstChildElement("locomotive").firstChildElement("values");
        //newLocomotive.appendChild((QDomElement)values.clone());
        newLocomotive.appendChild(values);

        writeXML(pFile, doc);
    }
    catch (Exception ex) {
        // need to trace this one back
//        ex.printStackTrace();
    }
}

/**
 * Defines the preferences subdirectory in which LocoFiles are kept
 * by default.
 */

/*static*/ /*public*/ QString LocoFile::getFileLocation()
{
 return Roster::getDefault()->getRosterLocation() + "roster" + File::separator;
}


//    // initialize logging
/*static*/ Logger* LocoFile::log = LoggerFactory::getLogger("LocoFile");

//}
