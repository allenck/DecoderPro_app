#include "decoderindexfile.h"
#include "decoderfile.h"
#include "comboboxmodel.h"
#include "defaultcomboboxmodel.h"
#include "decoderfile.h"
#include "fileutil.h"
#include "file.h"
#include "fileutil.h"

DecoderIndexFile* DecoderIndexFile::_instance = NULL;
//QString DecoderIndexFile::decoderIndexFileName = "decoderIndex.xml";
/*static*/ /*final*/ /*protected*/ QString DecoderIndexFile::DECODER_INDEX_FILE_NAME = "decoderIndex.xml";
QString DecoderIndexFile::decoderIndexFileName = "/home/allen/NetBeansProjects/JMRI/xml/decoderIndex.xml";

DecoderIndexFile::DecoderIndexFile(QObject *parent) :
    XmlFile(parent)
{
 log = new Logger("DecoderIndexFile");
 fileVersion = -1;
 decoderList = new QList<DecoderFile*>();
 _mfgIdFromNameHash = new QHash<QString,QString>();
 _mfgNameFromIdHash = new QHash<QString,QString>();

  mMfgNameList = new QStringList();
}
/**
 * DecoderIndex represents a decoderIndex.xml file in memory.
 * <P>
 * This allows a program
 * to navigate to various decoder descriptions without having to
 * manipulate files.
 *<P>
 * This class doesn't provide tools for defining the index; that's done manually, or
 * at least not done here.
 *<P>
 * Multiple DecoderIndexFile objects don't make sense, so we use an "instance" member
 * to navigate to a single one.
 *
 * @author			Bob Jacobsen   Copyright (C) 2001
 * @version			$Revision: 22547 $
 *
 */
// /*public*/ class DecoderIndexFile extends XmlFile {

// fill in abstract members

/*public*/ int DecoderIndexFile::numDecoders() { return decoderList->size(); }



/*public*/ QStringList* DecoderIndexFile::getMfgNameList() { return mMfgNameList; }

/*public*/ QString DecoderIndexFile::mfgIdFromName(QString name) {
    return _mfgIdFromNameHash->value(name);
}

/*public*/ QString DecoderIndexFile::mfgNameFromId(QString name) {
    return _mfgNameFromIdHash->value(name);
}

/**
 *	Get a List of decoders matching some information
 */
/*public*/ QList<DecoderFile*>* DecoderIndexFile::matchingDecoderList(QString mfg, QString family, QString decoderMfgID, QString decoderVersionID, QString decoderProductID, QString model )
{
 QList<DecoderFile*>* l = new QList<DecoderFile*>();
 for (int i = 0; i < numDecoders(); i++)
 {
  if ( checkEntry(i, mfg, family, decoderMfgID, decoderVersionID, decoderProductID, model ))
  {
   l->append(decoderList->at(i));
  }
 }
 return l;
}

/**
 * Get a JComboBox representing the choices that match
 * some information
 */
/*public*/ QComboBox* DecoderIndexFile::matchingComboBox(QString mfg, QString family, QString decoderMfgID, QString decoderVersionID, QString decoderProductID, QString model )
{
 QList<DecoderFile*>* l = matchingDecoderList(mfg, family, decoderMfgID, decoderVersionID, decoderProductID, model );
 return jComboBoxFromList(l);
}

/**
 * Return a JComboBox made with the titles from a list of
 * DecoderFile entries
 */
/*static*/ /*public*/ QComboBox* DecoderIndexFile::jComboBoxFromList(QList<DecoderFile*>* l)
{
 QComboBox* comboBox = new QComboBox();
// for(int i=0; i < l->size(); l++)
//  comboBox->addItem(l->at(i)->titleString());
 foreach (DecoderFile* f, *l)
 {
  comboBox->addItem(f->titleString());
 }
 //return new QComboBox(jComboBoxModelFromList(l));
 return comboBox;
}

/**
 * Return a new ComboBoxModel made with the titles from a list of
 * DecoderFile entries
 */
/*static*/ /*public*/ ComboBoxModel* DecoderIndexFile::jComboBoxModelFromList(QList<DecoderFile*>* l)
{
//    DefaultComboBoxModel<QString>* b = new DefaultComboBoxModel<QString>();
//    for (int i = 0; i < l->size(); i++) {
//        DecoderFile* r = l->at(i);
////        b->addElement(r->titleString());
//    }
//    return (ComboBoxModel*)b;
    return NULL;
}

/**
 * Return DecoderFile from a "title" string, ala selection in matchingComboBox.
 */
/*public*/ DecoderFile* DecoderIndexFile::fileFromTitle(QString title )
{
 for (int i = numDecoders()-1; i >= 0; i--)
 {
  DecoderFile* r = decoderList->at(i);
  if (r->titleString()==(title)) return r;
 }
 return NULL;
}

/**
 * Check if an entry consistent with specific properties. A NULL QString entry
 * always matches. QStrings are used for convenience in GUI building.
 * Don't bother asking about the model number...
 *
 */
/*public*/ bool DecoderIndexFile::checkEntry(int i, QString mfgName, QString family, QString mfgID, QString decoderVersionID, QString decoderProductID, QString model)
{
 DecoderFile* r = decoderList->at(i);
 if (mfgName != "" && mfgName!=(r->getMfg())) return false;
 if (family != "" && family!=(r->getFamily())) return false;
 if (mfgID != "" && mfgID!=(r->getMfgID())) return false;
 if (model != "" && model!=(r->getModel())) return false;
 // check version ID - no match if a range specified and out of range
 if (decoderVersionID != "")
 {
  int versionID = (decoderVersionID).toInt();
  if (!r->isVersion(versionID)) return false;
 }
 if (decoderProductID != "" && decoderProductID!=(r->getProductID())) return false;
 return true;
}

/*public*/ /*synchronized*/ /*static*/ void DecoderIndexFile::resetInstance()
{
 //QMutexLocker locker(*mutex);
 _instance = NULL;
}
/*public*/ /*synchronized*/ /*static*/ DecoderIndexFile* DecoderIndexFile::instance()
{
 //QMutexLocker locker(*mutex);
 Logger log = Logger("DecoderIndexFile");
 if (_instance == NULL)
 {
  if (log.isDebugEnabled()) log.debug("DecoderIndexFile creating instance");
  // create and load
  try
  {
   _instance = new DecoderIndexFile();
   _instance->readFile(FileUtil::getProgramPath() + "xml" + File::separator + defaultDecoderIndexFilename());
  }
  catch (Exception e)
  {
   log.error("Exception during decoder index reading: "+e.getMessage());
//            e.printStackTrace();
  }
  // see if needs to be updated
  try
  {
   if (updateIndexIfNeeded(defaultDecoderIndexFilename()))
   {
    try
    {
     _instance = new DecoderIndexFile();
     _instance->readFile(defaultDecoderIndexFilename());
    }
    catch (Exception e)
    {
     log.error("Exception during decoder index reload: "+e.getMessage());
//                    e.printStackTrace();
    }
   }
  }
  catch (Exception e)
  {
   log.error("Exception during decoder index update: "+e.getMessage());
//            e.printStackTrace();
  }
 }
 if (log.isDebugEnabled()) log.debug(tr("DecoderIndexFile returns instance ")+_instance->metaObject()->className());
  return _instance;
}

/**
 * Check whether the user's version of the decoder index file needs to be
 * updated; if it does, then force the update.
 * @return true is the index should be reloaded because it was updated
 * @param name
 * @throws JDOMException
 * @throws FileNotFoundException
 */
/*static*/ bool DecoderIndexFile::updateIndexIfNeeded(QString name) throw (JDOMException, IOException)
{
 Logger log = Logger("DecoderIndexFile");
 // get version from master index; if not found, give up
 QString masterVersion = NULL;
 DecoderIndexFile* masterXmlFile = new DecoderIndexFile();
 QFile* masterFile = new QFile("xml"+QString(QDir::separator())+defaultDecoderIndexFilename());
 if (! masterFile->exists()) return false;
 QDomElement masterRoot = masterXmlFile->rootFromFile(masterFile);
 if (!masterRoot.firstChildElement("decoderIndex").isNull() )
 {
  if (masterRoot.firstChildElement("decoderIndex").attribute("version")!="")
   masterVersion = masterRoot.firstChildElement("decoderIndex").attribute("version");
  log.debug("master version found, is "+masterVersion);
 }
 else
 {
  return false;
 }

 // get from user index.  Unless they are equal, force an update.
 // note we find this file via the search path; if not exists, so that
 // the master is found, we still do the right thing (nothing).
 QString userVersion = "";
 DecoderIndexFile* userXmlFile = new DecoderIndexFile();
 QDomElement userRoot = userXmlFile->rootFromName(defaultDecoderIndexFilename());
 if (!userRoot.firstChildElement("decoderIndex").isNull() )
 {
  if (userRoot.firstChildElement("decoderIndex").attribute("version")!=NULL)
   userVersion = userRoot.firstChildElement("decoderIndex").attribute("version");
  log.debug("user version found, is "+userVersion);
 }
 if (masterVersion!=NULL && masterVersion==(userVersion)) return false;

 // force the update, with the version number located earlier is available
 if (masterVersion != NULL)
  instance()->fileVersion = (masterVersion.toInt());

 forceCreationOfNewIndex();
 // and force it to be used
 return true;
}

/**
     * Force creation of a new user index without incrementing version
     */
/*static*/ /*public*/ void DecoderIndexFile::forceCreationOfNewIndex()
{
 forceCreationOfNewIndex(false);
}

/**
 * Force creation of a new user index
 */
/*static*/ /*public*/ void DecoderIndexFile::forceCreationOfNewIndex(bool increment) {
 Logger* log = new Logger("DecoderIndexFile");
 log->info("update decoder index");
 // make sure we're using only the default manufacturer info
 // to keep from propagating wrong, old stuff
 File* oldfile = new File(FileUtil::getUserFilesPath() + "decoderIndex.xml");
 if (oldfile->exists())
 {
  log->debug("remove existing user decoderIndex.xml file");
  if (!oldfile->_delete()) // delete file, check for success
  {
   Logger::error("Failed to delete old index file");
  }
  // force read from distributed file
  resetInstance();
  instance();
 }

 // create an array of file names from decoders dir in preferences, count entries
 QStringList al;
 QStringList sp = QStringList();
 int i=0;
 FileUtil::createDirectory(FileUtil::getUserFilesPath() + DecoderFile::fileLocation);
 QDir* fp = new QDir(FileUtil::getUserFilesPath() + DecoderFile::fileLocation);
 if (fp->exists())
 {
  sp = fp->entryList();
  for (i=0; i<sp.length(); i++)
  {
   if (sp.at(i).endsWith(".xml") || sp.at(i).endsWith(".XML"))
    al.append(sp.at(i));
  }
 }
 else
 {
  log->warn(FileUtil::getUserFilesPath()+"decoders was missing, though tried to create it");
 }
 // create an array of file names from xml/decoders, count entries
 QStringList sx = ( new QDir(XmlFile::xmlDir()+DecoderFile::fileLocation))->entryList();
 for (i=0; i<sx.length(); i++)
 {
  if (sx[i].endsWith(".xml") || sx[i].endsWith(".XML"))
  {
   // Valid name.  Does it exist in preferences xml/decoders?
   if (!al.contains(sx[i]))
   {
    // no, include it!
    al.append(sx.at(i));
   }
  }
 }
 // copy the decoder entries to the final array (toArray needs cast of +elements+)
 //QList<QObject*> aa = al.toArray();
 QList<QObject*> aa;
 foreach (QString s, al)
 {
  aa.append((QObject*)&s);
 }
 QStringList* sbox =  new QStringList();
 for (i =0; i<sbox->length(); i++)
  sbox->append(*(QString*) aa.at(i));

 //the resulting array is now sorted on file-name to make it easier
 // for humans to read
// TODO:    jmri.util.QStringUtil.sort(sbox);

 // create a new decoderIndex
 // the existing version is used, so that a new master file
 // with a larger one will force an update
 DecoderIndexFile* index = new DecoderIndexFile();

 // For user operations the existing version is used, so that a new master file
 // with a larger one will force an update
 if (increment) {
     index->fileVersion = instance()->fileVersion + 2;
 } else {
     index->fileVersion = instance()->fileVersion;
 }

 // write it out
 try
 {
  index->writeFile("decoderIndex.xml", _instance, sbox);
 }
 catch (IOException ex)
 {
  log->error("Error writing new decoder index file: "+ex.getMessage());
 }
}

/**
 * Read the contents of a decoderIndex XML file into this object. Note that this does not
 * clear any existing entries; reset the instance to do that.
 */
void DecoderIndexFile::readFile(QString name) throw (JDOMException, IOException)
{
 if (log->isDebugEnabled()) log->debug("readFile "+name);

 // read file, find root
 QDomElement root = rootFromName(name);

 // decode type, invoke proper processing routine if a decoder file
 if (!root.firstChildElement("decoderIndex").isNull())
 {
  if (root.firstChildElement("decoderIndex").attribute("version")!="")
   fileVersion = (root.firstChildElement("decoderIndex").attribute("version").toInt());
  log->debug("found fileVersion of "+QString::number(fileVersion));
  readMfgSection(root.firstChildElement("decoderIndex"));
  readFamilySection(root.firstChildElement("decoderIndex"));
 }
 else
 {
  log->error("Unrecognized decoderIndex file contents in file: "+name);
 }
}

//@SuppressWarnings("unchecked")
void DecoderIndexFile::readMfgSection(QDomElement decoderIndex)
{
 QDomElement mfgList = decoderIndex.firstChildElement("mfgList");
 if (!mfgList.isNull())
 {

  QString a;
  a = mfgList.attribute("nmraListDate");
  if (a!=NULL) nmraListDate = a;
  a = mfgList.attribute("updated");
  if (a!=NULL) updated = a;
  a = mfgList.attribute("lastadd");
  if (a!=NULL) lastAdd = a;

  QDomNodeList l = mfgList.elementsByTagName("manufacturer");
  if (log->isDebugEnabled()) log->debug("readMfgSection sees "+QString::number(l.size())+" children");
  for (int i=0; i<l.size(); i++)
  {
   // handle each entry
   QDomElement el = l.at(i).toElement();
   QString mfg = el.attribute("mfg");
   mMfgNameList->append(mfg);
   QString attr = el.attribute("mfgID");
   if (attr != NULL)
   {
    _mfgIdFromNameHash->insert(mfg, attr);
    _mfgNameFromIdHash->insert(attr, mfg);
   }
  }
 }
 else log->warn("no mfgList found in decoderIndexFile");
}

//@SuppressWarnings("unchecked")
void DecoderIndexFile::readFamilySection(QDomElement decoderIndex)
{
 QDomElement familyList = decoderIndex.firstChildElement("familyList");
 if (!familyList.isNull())
 {

  QDomNodeList l = familyList.elementsByTagName("family");
  if (log->isDebugEnabled()) log->debug("readFamilySection sees "+QString::number(l.size())+" children");
  for (int i=0; i<l.size(); i++)
  {
   // handle each entry
   QDomElement el = l.at(i).toElement();
   readFamily(el);
  }
 }
 else log->warn("no familyList found in decoderIndexFile");
}

//@SuppressWarnings("unchecked")
void DecoderIndexFile::readFamily(QDomElement family)
{
 QString attr;
 QString filename = family.attribute("file");
 QString parentLowVersID = ((attr = family.attribute("lowVersionID"))     != "" ? attr : "" );
 QString parentHighVersID = ((attr = family.attribute("highVersionID"))     != "" ? attr : "" );
 QString familyName   = ((attr = family.attribute("name"))     != "" ? attr : "" );
 QString mfg   = ((attr = family.attribute("mfg"))     != "" ? attr : "" );
 QString mfgID = "";
 if (mfg != "")
 {
  mfgID  = mfgIdFromName(mfg);
 }
 else
 {
  log->error("Did not find required mfg attribute, may not find proper manufacturer");
 }

 QDomNodeList l = family.elementsByTagName("model");
 if (log->isDebugEnabled()) log->debug("readFamily sees "+QString::number(l.size())+" children");
 QDomElement modelElement;
 if (l.size()<=0)
 {
  log->error("Did not find at least one model in the "+familyName+" family");
  modelElement = QDomElement();
 }
 else
 {
  modelElement = l.at(0).toElement();
 }

 // Record the family as a specific model, which allows you to select the
 // family as a possible thing to program
 DecoderFile* vFamilyDecoderFile
        = new DecoderFile( mfg, mfgID, familyName,
                           parentLowVersID, parentHighVersID,
                           familyName,
                           filename,
                           -1, -1, modelElement); // numFns, numOuts, XML element equal
                                        // to the first decoder
 decoderList->append(vFamilyDecoderFile);

 // record each of the decoders
 for (int i=0; i<l.size(); i++)
 {
  // handle each entry by creating a DecoderFile object containing all it knows
  QDomElement decoder = l.at(i).toElement();
  QString loVersID = ( (attr = decoder.attribute("lowVersionID"))     != "" ? attr : parentLowVersID);
  QString hiVersID = ( (attr = decoder.attribute("highVersionID"))     != "" ? attr : parentHighVersID);
  int numFns   = ((attr = decoder.attribute("numFns"))     != "" ? (attr).toInt() : -1 );
  int numOuts   = ((attr = decoder.attribute("numOuts"))     != "" ? (attr).toInt() : -1 );
  DecoderFile* df = new DecoderFile( mfg, mfgID,
                                  ( (attr = decoder.attribute("model"))     != NULL ? attr : NULL ),
                                  loVersID, hiVersID, familyName, filename, numFns, numOuts, decoder);
  // and store it
  decoderList->append(df);
  // if there are additional version numbers defined, handle them too
  QDomNodeList vcodes = decoder.elementsByTagName("versionCV");
  for (int j=0; j<vcodes.size(); j++)
  {
   // for each versionCV element
   QDomElement vcv = vcodes.at(j).toElement();
   QString vLoVersID = ( (attr = vcv.attribute("lowVersionID")) != "" ? attr : loVersID);
   QString vHiVersID = ( (attr = vcv.attribute("highVersionID"))!= "" ? attr : hiVersID);
   df->setVersionRange(vLoVersID, vHiVersID);
  }
 }
}

/*public*/ void DecoderIndexFile::writeFile(QString name, DecoderIndexFile* oldIndex, QStringList* files) throw (IOException)
{
#if 1 //TODO:
 //QDomDocument doc(/*QString("../xml/)"+"decoderIndex-config.dtd")*/);
 QDomDocument doc;
 if (log->isDebugEnabled()) log->debug("writeFile "+name);
 // This is taken in large part from "Java and XML" page 368
 QFile* file = new QFile(FileUtil::getUserFilesPath() + name);

 // create root element and document
 QDomElement root = doc.createElement("decoderIndex-config");
 // Replacement DTD location, temporary until this is changed to schema
 //    QDomDocument doc = newDocument(root, tr("../xml/"+"decoderIndex-config.dtd"));
 doc.appendChild(root);

 // add XSLT processing instruction
 // <?xml-stylesheet type="text/xsl" href="XSLT/DecoderID.xsl"?>
 //    QMap<QString,QString>* m = new QMap<QString,QString>();
 //    m->insert("type", "text/xsl");
 //    m->insert("href", xsltLocation+"DecoderID.xsl");
 QDomProcessingInstruction p = doc.createProcessingInstruction("xml-stylesheet", "type= \"text/xsl\", href=\""+xsltLocation+"DecoderID.xsl\"");
 doc.appendChild(p);

 // add top-level elements
 QDomElement index;
 root.appendChild(index = doc.createElement("decoderIndex"));
 index.setAttribute("version", QString::number(fileVersion));
 log->debug("version written to file as "+QString::number(fileVersion));

 // add mfg list from existing DecoderIndexFile item
 QDomElement mfgList = doc.createElement("mfgList");
 // copy dates from original mfgList element
 if (oldIndex->nmraListDate!="")
  mfgList.setAttribute("nmraListDate", oldIndex->nmraListDate);
 if (oldIndex->updated!="")
  mfgList.setAttribute("updated", oldIndex->updated);
 if (oldIndex->lastAdd!="")
  mfgList.setAttribute("lastadd", oldIndex->lastAdd);

 // We treat "NMRA" spencial...
 QDomElement mfg = doc.createElement("manufacturer");
 mfg.setAttribute("mfg","NMRA");
 mfg.setAttribute("mfgID","999");
 mfgList.appendChild(mfg);
 // start working on the rest of the entries
 QStringListIterator keys(oldIndex->_mfgIdFromNameHash->keys());
 QStringList* l = new QStringList();
 while (keys.hasNext())
 {
  l->append(keys.next());
 }

 QVector<QString> s = l->toVector();
 // all of the above mess was to get something we can sort into alpha order
 //    jmri.util.QStringUtil.sort(s);
 for (int i=0; i<s.size(); i++)
 {
  QString mfgName = (QString)s.at(i);
  if (mfgName!=("NMRA"))
  {
   mfg = doc.createElement("manufacturer");
   mfg.setAttribute("mfg",mfgName);
   mfg.setAttribute("mfgID", oldIndex->_mfgIdFromNameHash->value(mfgName));
   mfgList.appendChild(mfg);
  }
 }

 // add family list by scanning files
 QDomElement familyList = doc.createElement("familyList");
 for (int i=0; i<files->length(); i++)
 {
  DecoderFile* d = new DecoderFile();
  try
  {
   QDomElement droot = d->rootFromName(DecoderFile::fileLocation+files->at(i));
   QDomElement family = (QDomElement)droot.firstChildElement("decoder").firstChildElement("family")/*.clone()*/;
   family.setAttribute("file",files->at(i));
   familyList.appendChild(family);
  }
  catch (JDOMException exj) {log->error(tr("could not parse ")+files->at(i)+": "+exj.getMessage());}
  catch (FileNotFoundException exj) {log->error("could not read "+files->at(i)+": "+exj.getMessage());}
  catch (Exception exj) {log->error(tr("other exception while dealing with ")+files->at(i)+": "+exj.getMessage());}
 }

 index.appendChild(mfgList);
//    index.appendChild(familyList);

 writeXML(file, doc);

 // force a read of the new file next time
 resetInstance();
#endif
}


/**
 * Return the filename QString for the default decoder index file, including location.
 * This is here to allow easy override in tests.
 */
/*protected*/ /*static*/ QString DecoderIndexFile::defaultDecoderIndexFilename()
{ return DECODER_INDEX_FILE_NAME;}

