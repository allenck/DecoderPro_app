#include "defaultmemorymanagerxml.h"
#include "instancemanager.h"

DefaultMemoryManagerXml::DefaultMemoryManagerXml(QObject *parent) :
  AbstractMemoryManagerConfigXML(parent)
{
 setObjectName("DefaultMemoryManagerXml");
}
/**
 * Persistency implementation for the default MemoryManager persistance.
 * <P>
 * The state of memory objects is not persisted, just their existance.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002
 * @version $Revision: 28746 $
 */
///*public*/ class DefaultMemoryManagerXml extends AbstractMemoryManagerConfigXML {

///*public*/ DefaultMemoryManagerXml() {
//}

/**
 * Subclass provides implementation to create the correct top element,
 * including the type information. Default implementation is to use the
 * local class here.
 *
 * @param memories The top-level element being created
 */
/*public*/ void DefaultMemoryManagerXml::setStoreElementClass(QDomElement memories) {
 memories.setAttribute("class", "jmri.managers.configurexml.DefaultMemoryManagerXml");
}

/**
 * Create a MemoryManager object of the correct class, then register and
 * fill it.
 *
 * @param memories Top level Element to unpack.
 * @return true if successful
 */
/*public*/ bool DefaultMemoryManagerXml::load(QDomElement memories) throw (JmriConfigureXmlException)
{
 // ensure the master object exists
 InstanceManager::memoryManagerInstance();
 // load individual routes
 loadMemories(memories);
 return true;
}
