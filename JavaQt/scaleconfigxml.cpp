#include "scaleconfigxml.h"
#include "scale.h"
#include "loggerfactory.h"
#include "fileutil.h"
#include "scalemanager.h"

ScaleConfigXML::ScaleConfigXML(QObject *parent) : QObject(parent)
{

}
/**
 * Load and store scale xml data files.
 * <p>
 * Custom changes to scale information result in the scale data being stored
 * at the user files location.  Subsequent scale data loading uses the custom
 * data file.  The default scale data file is part of the JMRI distribution.
 * @author Dave Sand Copyright (C) 2018
 * @since 4.13.6
 */
// /*public*/ class ScaleConfigXML {

    /*public*/ /*static*/ bool ScaleConfigXML::doStore() {
        ScaleXmlFile* x = new ScaleXmlFile();
        File* file = x->getStoreFile();
        if (file == nullptr) {
            log->warn("Unable to create local scale file");
            return false;
        }

        // Create root element
        QDomDocument doc = QDomDocument();
        QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
        doc.appendChild(xmlProcessingInstruction);
        QDomElement root = doc.createElement("scale-data");  // NOI18N

        root.setAttribute("xsi:noNamespaceSchemaLocation",  // NOI18N
                "http://jmri.org/xml/schema/scale.xsd");  // NOI18N
        root.setAttribute( "xmlns:xsi",
                        "http://www.w3.org/2001/XMLSchema-instance");  // NOI18N
        doc.appendChild(root);
        QDomElement values;

        root.appendChild(values = doc.createElement("scales"));  // NOI18N
        for (Scale* scale : ScaleManager::getScales()) {
            QDomElement e = doc.createElement("scale");  // NOI18N
            e.appendChild(doc.createElement("scale_name").appendChild(doc.createTextNode(scale->getScaleName())));  // NOI18N
            e.appendChild(doc.createElement("user_name").appendChild(doc.createTextNode(scale->getUserName())));  // NOI18N
            e.appendChild(doc.createElement("scale_ratio").appendChild(doc.createTextNode(QString::number(scale->getScaleRatio()))));  // NOI18N
            values.appendChild(e);
        }

        try {
            x->writeXML(file, doc);
        } catch (FileNotFoundException ex) {
            log->error("File not found when writing: " + ex.getMessage());  // NOI18N
            return false;
        } catch (IOException ex) {
            log->error("IO Exception when writing: " + ex.getMessage());  // NOI18N
            return false;
        }

        return true;
    }

    /*public*/ /*static*/ bool ScaleConfigXML::doLoad() {
        ScaleXmlFile* x = new ScaleXmlFile();
        File* file = x->getLoadFile();

        // Find root
        QDomElement root;
        try {
            root = x->rootFromFile(file);
            if (root.isNull()) {
                log->debug("File could not be read");  // NOI18N
                return false;
            }

            QDomElement scales = root.firstChildElement("scales");  // NOI18N
            if (scales.isNull()) {
                log->error("Unable to find a scale entry");  // NOI18N
                return false;
            }
            //for (Element scale : scales.getChildren("scale"))
            QDomNodeList nl = scales.elementsByTagName("scale");
            for(int i=0; i < nl.count(); i++)
            {  // NOI18N
             QDomElement scale = nl.at(i).toElement();
                QDomElement scale_name = scale.firstChildElement("scale_name");  // NOI18N
                QString scaleName = scale_name.text();//(scale_name.isNull()) ? "" : scale_name.getValue();
                QDomElement user_name = scale.firstChildElement("user_name");  // NOI18N
                QString userName = user_name.text();//(user_name == null) ? "" : user_name.getValue();
                QDomElement scale_ratio = scale.firstChildElement("scale_ratio");  // NOI18N
                double scaleRatio = scale_ratio.text().toDouble();//(scale_ratio == null) ? 1.0 : Double.parseDouble(scale_ratio.getValue());

                ScaleManager::addScale(scaleName, userName, scaleRatio);
            }

        } catch (JDOMException ex) {
            log->error("File invalid: " + ex.getMessage());  // NOI18N
            return false;
        } catch (IOException ex) {
            log->error("Error reading file: " + ex.getMessage());  // NOI18N
            return false;
        }

        return true;
    }

//    /*private*/ /*static*/ class ScaleXmlFile : public XmlFile {
        /*private*/ /*static*/ QString ScaleXmlFile::prodPath = "";//FileUtil::getProgramPath() + "resources/scales/";  // NOI18N
        /*private*/ /*static*/ QString ScaleXmlFile::userPath = "";//FileUtil::getUserFilesPath() + "resources/scales/";  // NOI18N
        /*private*/ /*static*/ QString ScaleXmlFile::fileName = "ScaleData.xml";  // NOI18N

        /*public*/ /*static*/ QString ScaleXmlFile::getStoreFileName() {
            return userPath + fileName;
        }

        /*public*/ File* ScaleXmlFile::getStoreFile() {
            File* chkdir = new File(userPath);
            if (!chkdir->exists()) {
                if (!chkdir->mkdirs()) {
                    return nullptr;
                }
            }
            File* file = new File(findFile(getStoreFileName())->fileName());
            if (file == nullptr) {
                 ScaleConfigXML::log->info("Create new scale file");  // NOI18N
                file = new File(getStoreFileName());
            } else {
                try {
                    FileUtil::rotate(file, 4, "bup");  // NOI18N
                } catch (IOException ex) {
                     ScaleConfigXML::log->warn("Rotate failed, reverting to xml backup");  // NOI18N
                    makeBackupFile(getStoreFileName());
                }
            }
            return file;
        }

        /*public*/ File* ScaleXmlFile::getLoadFile() {
            QFile* file = findFile(userPath + fileName)->toQfile();
            if (file == nullptr) {
                file = findFile(prodPath + fileName)->toQfile();
            }
            return new File(file->fileName());
        }


    /*private*/ /*final*/ /*static*/ Logger* ScaleConfigXML::log =LoggerFactory::getLogger("ScaleConfigXML");
