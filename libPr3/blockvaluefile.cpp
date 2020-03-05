#include "blockvaluefile.h"
#include "fileutil.h"
#include "Roster/rosterentry.h"
#include "Roster/roster.h"
#include "path.h"
#include "instancemanager.h"
#include "blockmanager.h"


/*private*/ /*static*/ QString BlockValueFile::defaultFileName = FileUtil::getUserFilesPath()+"blockvalues.xml";

BlockValueFile::BlockValueFile(QObject *parent) :
    XmlFile(parent)
{
 blockManager = static_cast<BlockManager*>(InstanceManager::getDefault("BlockManager"));
 log = new Logger("BlockValueFile");
 QDomDocument doc = QDomDocument("block_values");
 root = doc.createElement("block_values");
}
/**
 * Handle saving/restoring block value information to XML files.
 * This class manipulates files conforming to the block_value DTD.
 *
 * @author      Dave Duchamp Copyright (C) 2008
 * @version     $Revision: 22539 $
 */

//public class BlockValueFile extends XmlFile {

//	public BlockValueFile () {
//		super();
//		blockManager = jmri.InstanceManager.blockManagerInstance();
//	}


/*
 *  Reads Block values from a file in the user's preferences directory
 *  If the file containing block values does not exist this routine returns quietly.
 *  If a Block named in the file does not exist currently, that entry is quietly ignored.
 */
//@SuppressWarnings("unchecked")
/*public*/ void BlockValueFile::readBlockValues() throw (JDOMException, IOException)
{
 log->debug("entered readBlockValues");
 QStringList blocks = blockManager->getSystemNameList();
 // check if file exists
 if (checkFile(defaultFileName))
 {
  // file is present,
  root = rootFromName(defaultFileName);
  if ( (!root.isNull()) && (!blocks.isEmpty()) && (blocks.size()>0) )
  {
   // there is a file and there are Blocks defined
   QDomElement blockvalues = root.firstChildElement("blockvalues");
   if (!blockvalues.isNull())
   {
    // there are values defined, read and set block values if Block exists.
    QDomNodeList blockList = blockvalues.elementsByTagName("block");
    for (int i=0; i<blockList.size(); i++)
    {
     if ((blockList.at(i)).toElement().attribute("systemname").isEmpty())
     {
      log->warn("unexpected NULL in systemName "+
                                blockList.at(i).toElement().tagName()+" "/*+
                                    blockList.get(i).getAttributes()*/);
      break;
     }
     QString sysName = blockList.at(i).toElement().attribute("systemname");
     // get Block - ignore entry if block not found
     Block* b = (Block*)blockManager->getBySystemName(sysName);
     if (b!=NULL)
     {
      // Block was found, set its value
      QVariant v;
      QString v1 = blockList.at(i).toElement().attribute("value");
      //v = &v1;
      if(blockList.at(i).toElement().attribute("valueClass")!=NULL)
      {
       if(blockList.at(i).toElement().attribute("valueClass")==("jmri.jmrit.roster.RosterEntry"))
       {
        RosterEntry* re = Roster::getDefault()->getEntryForId((v1));
        if(re!=NULL)
         //v.setValue(re);
         v= VPtr<RosterEntry>::asQVariant(re);
       }
      }
      b->setValue(v);
      // set direction if there is one
      int dd = Path::NONE;
      QString a = blockList.at(i).toElement().attribute("dir");
      if (a!=NULL)
      {
       try
       {
        bool bOk;
        dd = a.toInt(&bOk);
        if(!bOk) throw new DataConversionException();
       }
       catch (DataConversionException e)
       {
        log->error("failed to convert direction attribute");
       }
      }
      b->setDirection(dd);
     }
    }
   }
  }
 }
}

/*
 *  Writes out block values to a file in the user's preferences directory
 *  If there are no defined Blocks, no file is written.
 *  If none of the defined Blocks have values, no file is written.
 */
/*public*/ void BlockValueFile::writeBlockValues() throw (IOException)
{
 log->debug("entered writeBlockValues");
 QStringList blocks = blockManager->getSystemNameList();
 if (blocks.size()>0)
 {
  // there are blocks defined, create root element
  doc = newDocument(root, dtdLocation+"block-values.dtd");
  root = doc.createElement("block_values");

  bool valuesFound = false;

  // add XSLT processing instruction
  // <?xml-stylesheet type="text/xsl" href="XSLT/block-values.xsl"?>
  QMap<QString,QString> m = QMap<QString,QString>();
  m.insert("type", "text/xsl");
  m.insert("href", xsltLocation+"blockValues.xsl");
//  ProcessingInstruction* p = new ProcessingInstruction("xml-stylesheet", m);
//  doc.addContent(0,p);

  // save block values in xml format
  QDomElement values = doc.createElement("blockvalues");
  for (int i = 0; i<blocks.size(); i++)
  {
   QString sname = blocks.at(i);
   Block* b = (Block*)blockManager->getBySystemName(sname);
   if (b!=NULL)
   {
    QVariant o = b->getValue();
    if (!o.isNull())
    {
     // block has value, save it
     QDomElement val = doc.createElement("block");
     val.setAttribute("systemname", sname);
     //if(o instanceof jmri.jmrit.roster.RosterEntry){
     //if(dynamic_cast<RosterEntry*>(o)!=NULL)
     RosterEntry* re = VPtr<RosterEntry>::asPtr(o);
     if(re != NULL)
     {
      //val.setAttribute("value", ((RosterEntry*)o)->getId());
      val.setAttribute("value", re->getId());
      val.setAttribute("valueClass", "jmri.jmrit.roster.RosterEntry");
     }
     else
     {
      val.setAttribute("value",o.toString());
     }
     int v = b->getDirection();
     if (v!=Path::NONE) val.setAttribute("dir",v);
     values.appendChild(val);
     valuesFound = true;
    }
   }
   else log->error("Block "+sname+" was not found.");
  }
  root.appendChild(values);

  // write out the file if values were found
  if (valuesFound)
  {
   try
   {
    if (!checkFile(defaultFileName))
    {
     // file does not exist, create it
     QFile file(defaultFileName);
     if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) // create and check result
      log->error("createNewFile failed");
    }
    // write content to file
    writeXML(findFile(defaultFileName),doc);
   }
   catch (IOException ioe)
   {
    log->error("IO Exception "+ioe.getMessage());
    throw (ioe);
   }
 }
 }
}

