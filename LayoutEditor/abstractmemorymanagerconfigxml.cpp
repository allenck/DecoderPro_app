#include "abstractmemorymanagerconfigxml.h"
#include "memorymanager.h"
#include "abstractmemorymanager.h"
#include "rosterentry.h"
#include "instancemanager.h"
#include "roster.h"
#include "abstractmemory.h"

AbstractMemoryManagerConfigXML::AbstractMemoryManagerConfigXML(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("AbstractMemoryManagerConfigXML");
}
AbstractMemoryManagerConfigXML::~AbstractMemoryManagerConfigXML()
{
 delete log;
}

/**
 * Provides the abstract base and store functionality for
 * configuring MemoryManagers, working with
 * AbstractMemoryManagers.
 * <P>
 * Typically, a subclass will just implement the load(QDomElement memories)
 * class, relying on implementation here to load the individual Memory objects.
 * Note that these are stored explicitly, so the
 * resolution mechanism doesn't need to see *Xml classes for each
 * specific Memory or AbstractMemory subclass at store time.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002, 2008
 * @version $Revision: 20492 $
 */
///*public*/ abstract class AbstractMemoryManagerConfigXML extends AbstractNamedBeanManagerConfigXML {

///*public*/ AbstractMemoryManagerConfigXML() {
//}

/**
 * Default implementation for storing the contents of a
 * MemoryManager
 * @param o Object to store, of type MemoryManager
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement AbstractMemoryManagerConfigXML::store(QObject* o)
{
 QDomElement memories = doc.createElement("memories");
 setStoreElementClass(memories);
 MemoryManager* tm = (MemoryManager*) o;
 if (tm!=NULL)
 {
  QStringListIterator iter(((AbstractMemoryManager*) tm)->getSystemNameList());

  // don't return an element if there are not memories to include
  if (!iter.hasNext()) return QDomElement();

  // store the memories
  while (iter.hasNext())
  {
   QString sname = iter.next();
   if (sname==NULL) log->error("System name NULL during store");
   log->debug("system name is "+sname);
   Memory* m = ((AbstractMemoryManager*)tm)->getBySystemName(sname);
   QDomElement elem = doc.createElement("memory");
   //elem.setAttribute("systemName", sname);
   QDomElement e1;
   elem.appendChild(e1=doc.createElement("systemName"));
   e1.appendChild(doc.createTextNode(sname));

   // store common part
   storeCommon(m, elem);
   // store value if non-NULL; NULL values omitted
   QVariant obj = ((AbstractMemory*)m)->getValue();
   if (obj != QVariant())
   {
    //if(obj instanceof jmri.jmrit.roster.RosterEntry){
    if(qobject_cast<RosterEntry*>(VPtr<RosterEntry>::asPtr(obj))!= NULL)
    {
     QString valueClass = VPtr<RosterEntry>::asPtr(obj)->metaObject()->className();
     QString value = ((RosterEntry*)VPtr<RosterEntry>::asPtr(obj))->getId();
     elem.setAttribute("value", value);
     elem.setAttribute("valueClass", valueClass);
    }
    else
    {
     QString value = obj.toString();
     elem.setAttribute("value", value);
    }
   }

   log->debug("store Memory "+sname);
   memories.appendChild(elem);

  }
 }
 return memories;
}

/**
 * Create a MemoryManager object of the correct class, then
 * register and fill it.
 * @param memories Top level QDomElement to unpack.
 * @return true if successful
 */
//@Override
// /*abstract*/ /*public*/ bool load(QDomElement sharedMemories, QDomElement perNodeMemories) /*throws JmriConfigureXmlException*/;

/**
 * Utility method to load the individual Memory objects.
 * If there's no additional info needed for a specific Memory type,
 * invoke this with the parent of the set of Memory elements.
 * @param memories QDomElement containing the Memory elements to load.
 */
//@SuppressWarnings("unchecked")
/*public*/ void AbstractMemoryManagerConfigXML::loadMemories(QDomElement memories)
{
 QDomNodeList memoryList = memories.elementsByTagName("memory");
 if (log->isDebugEnabled()) log->debug("Found "+QString::number(memoryList.size())+" Memory objects");
  MemoryManager* tm = InstanceManager::memoryManagerInstance();

 for (int i=0; i<memoryList.size(); i++)
 {
  QString sysName = getSystemName(memoryList.at(i).toElement());
  if (sysName == NULL)
  {
   log->warn("unexpected NULL in systemName "+(memoryList.at(i).toElement().tagName()));
   break;
  }

  QString userName = getUserName(memoryList.at(i).toElement());

  if (log->isDebugEnabled()) log->debug("create Memory: ("+sysName+")("+(userName==NULL?"<NULL>":userName)+")");
  Memory* m = ((AbstractMemoryManager*)tm)->newMemory(sysName, userName);
  if (memoryList.at(i).toElement().attribute("value") != "")
  {
   loadValue(memoryList.at(i).toElement(), m);
  }
  // load common parts
  loadCommon(m, memoryList.at(i).toElement());
 }
}

/*public*/ int AbstractMemoryManagerConfigXML::loadOrder() const{
    return ((AbstractMemoryManager*)InstanceManager::memoryManagerInstance())->getXMLOrder();
}

void AbstractMemoryManagerConfigXML::loadValue(QDomElement memory, Memory* m)
{
 QString value = memory.attribute("value");
 if(memory.attribute("valueClass")!="")
 {
  QString adapter = memory.attribute("valueClass");
  if (adapter==("jmri.jmrit.roster.RosterEntry"))
  {
   RosterEntry* re = Roster::getDefault()->getEntryForId(value);
   ((AbstractMemory*)m)->setValue(VPtr<RosterEntry>::asQVariant(re));
   return;
  }
 }
 ((AbstractMemory*)m)->setValue(QVariant(value));
}
