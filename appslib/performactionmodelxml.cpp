#include "performactionmodelxml.h"
#include "performactionmodel.h"
#include "instancemanager.h"
#include "startupactionsmanager.h"
#include "loggerfactory.h"
#include "class.h"

/**
 * Handle XML persistence of PerformActionModel objects.
 *
 * @author Bob Jacobsen Copyright (c) 2003
 * @see apps.startup.PerformActionModelFactory
 */
///*public*/ class PerformActionModelXml extends jmri.configurexml.AbstractXmlAdapter {

/*public*/ PerformActionModelXml::PerformActionModelXml(QObject* parent)  : AbstractXmlAdapter(parent){
}

/**
 * Default implementation for storing the model contents
 *
 * @param o Object to store, of type PerformActonModel
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/ QDomElement PerformActionModelXml::store(QObject* o) {
    QDomElement element = doc.createElement("perform");
    PerformActionModel* g = (PerformActionModel*) o;

    element.setAttribute("name", g->getClassName());
    element.setAttribute("type", "Action");
    element.setAttribute("class", "apps.configurexml.PerformActionModelXml");
    element.setAttribute("title", g->getTitle());
    QDomElement property = doc.createElement("property"); // NOI18N
    property.setAttribute("name", "systemPrefix"); // NOI18N
    property.setAttribute("value", g->getSystemPrefix());
    element.appendChild(property);
    return element;
}

/**
 * Object should be loaded after basic GUI constructed
 *
 * @return true to defer loading
 * @see jmri.configurexml.AbstractXmlAdapter#loadDeferred()
 * @see jmri.configurexml.XmlAdapter#loadDeferred()
 */
//@Override
/*public*/ bool PerformActionModelXml::loadDeferred() {
    return true;
}

//@Override
/*public*/ bool PerformActionModelXml::load(QDomElement shared, QDomElement /*perNode*/) throw (Exception)
{
 bool result = true;
 QString className = shared.attribute("name");
 QString title = shared.attribute("title");
 PerformActionModel* model = new PerformActionModel();
 Exception* exception = NULL;
 model->setClassName(className);
 model->setTitle(title);
 //for (QDomElement child : shared.getChildren("property"))
 QDomNodeList children = shared.elementsByTagName("property");
 for(int i = 0; i < children.count(); i++)
 { // NOI18N
  QDomElement child = children.at(i).toElement();
  QString value = child.attribute("value"); // NOI18N
  if (child.attribute("name")==("systemPrefix") // NOI18N
          && value != "")
  { // NOI18N
   // handle the situation where the model expects a system prefix
   // but was not saved with one in a pre-4.19.7 JMRI instance
   // TODO: at some point (June 2022 release?) change entire
   // try/catch block to just "model.setSystemPrefix(value);"
   try
   {
    Class* ac = Class::forName(className);
    if (value.isEmpty() && ac->isAssignableFrom("SystemConnectionAction")) {
//        SystemConnectionAction<?> a = (SystemConnectionAction<?>) ac.getConstructor().newInstance();
//        InstanceManager::getList("SystemConnectionMemo")
//                .forEach(memo -> a.getSystemConnectionMemoClasses().stream()
//                .filter(mc -> memo.getClass().isAssignableFrom(mc))
//                .forEach(mc -> model.setSystemPrefix(memo.getSystemPrefix())));
    } else {
        model->setSystemPrefix(value);
    }
   }
   catch (ClassNotFoundException *ex){
//           | InstantiationException
//           | IllegalAccessException
//           | IllegalArgumentException
//           | InvocationTargetException
//           | NoSuchMethodException
//           | SecurityException ex) {
       // ignore to allow manager to handle later
       log->warn(tr("While trying to do %1, encountered exception").arg(className), ex);
   }
  }
 }
 ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->addAction(model);
 if (exception != NULL) {
     throw *exception;
 }
 return result;
}

/**
 * Update static data from XML file
 *
 * @param element Top level QDomElement to unpack.
 * @param o       ignored
 */
//@Override
/*public*/ void PerformActionModelXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    log->error("Unexpected call of load(Element, Object)");
}
// initialize logging
/*private*/ /*final*/ /*static*/ Logger* PerformActionModelXml::log = LoggerFactory::getLogger("PerformActionModelXml");
