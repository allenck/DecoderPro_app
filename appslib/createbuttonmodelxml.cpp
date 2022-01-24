#include "createbuttonmodelxml.h"
#include "createbuttonmodel.h"
#include "QMetaType"
#include "instancemanager.h"
#include "createbuttonpanel.h"
#include "apps.h"
#include <QPushButton>
#include "flowlayout.h"
#include "actionlistener.h"

CreateButtonModelXml::CreateButtonModelXml(QObject* parent) :
    AbstractXmlAdapter(parent)
{
 log = new Logger("CreateButtonModelXml");
}
/**
 * Handle XML persistance of CreateButtonModel objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @version $Revision: 27930 $
 * @see apps.CreateButtonPanel
 */
///*public*/ class CreateButtonModelXml extends jmri.configurexml.AbstractXmlAdapter {

///*public*/ CreateButtonModelXml() {
//}

/**
 * Default implementation for storing the model contents
 * @param o QObject*  to store, of type CreateButtonModel
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement CreateButtonModelXml::store(QObject*  o) {
    QDomElement e = doc.createElement("perform");
    CreateButtonModel* g = (CreateButtonModel*) o;

    e.setAttribute("name", g->getClassName());
    e.setAttribute("type", "Button");
    e.setAttribute("class", /*this.getClass().getName()*/ "apps.configurexml.CreateButtonModelXml.java");
    return e;
}

/**
 * QObject*  should be loaded after basic GUI constructed
 * @return true to defer loading
 * @see jmri.configurexml.AbstractXmlAdapter#loadDeferred()
 * @see jmri.configurexml.XmlAdapter#loadDeferred()
 */
//@Override
/*public*/ bool CreateButtonModelXml::loadDeferred() {
    return true;
}

/**
 * Create object from XML file
 * @param e Top level QDomElement to unpack.
 * @return true if successful
  */
/*public*/ bool CreateButtonModelXml::load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException)
{
 bool result = true;
 QString className = shared.attribute("name");
 log->debug("Invoke Action from"+className);
// try
// {
  int type = QMetaType::type(className.toLocal8Bit());
  //Action action = (Action)Class.forName(className).newInstance();
  if(type > 0)
  {
   void* action;
#if QT_VERSION < 0x050000
   action = QMetaType::construct(type);
#else
   action = QMetaType::create(type);
#endif
   if (Apps::buttonSpace()!=NULL)
   {
    QPushButton* b = new QPushButton();
    ActionListener* l = (ActionListener*)action;
    connect(b, SIGNAL(clicked()), l, SLOT(actionPerformed(ActionEvent*)));
    ((FlowLayout*)Apps::buttonSpace()->layout())->addWidget(b);
   }
#if 0
   else if (Apps3.buttonSpace()!=NULL)
   {
    JButton b = new JButton(action);
    Apps3.buttonSpace().add(b);
   }
#endif
        //} else if (DecoderPro3.get)
  } /*catch (ClassNotFoundException ex1) */
  else
  {
   log->error("Could not find specified class: "+className);
   result = false;
  }
//  catch (IllegalAccessException ex2) {
//        log.error("Unexpected access exception for class: "+className, ex2);
//        result = false;
//    } catch (InstantiationException ex3) {
//        log.error("Could not instantiate specified class: "+className, ex3);
//        result = false;
//    } catch (Exception ex4) {
//        log.error("Exception while performing startup action for class: "+className, ex4);
//        result = false;
//    }
  CreateButtonModel* m = new CreateButtonModel();
  m->setClassName(className);
  CreateButtonModel::rememberObject(m);
  InstanceManager::configureManagerInstance()->registerPref(new CreateButtonPanel());
    return result;
}

/**
 * Update static data from XML file
 * @param element Top level QDomElement to unpack.
 * @param o  ignored
 */
/*public*/ void CreateButtonModelXml::load(QDomElement /*element*/, QObject*  /*o*/) throw (Exception){
    log->error("Unexpected call of load(Element, QObject* )");
}
