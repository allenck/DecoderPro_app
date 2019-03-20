#include "signalmasticonxml.h"
#include "signalmasticon.h"
#include "signalmast.h"
#include "instancemanager.h"
#include "defaultsignalmastmanager.h"
#include "editor.h"

SignalMastIconXml::SignalMastIconXml(QObject *parent) :
    PositionableLabelXml(parent)
{
 log = new Logger("SignalMastIconXml");
}
/**
 * Handle configuration for display.SignalMastIcon objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2010
 * @version $Revision: 18808 $
 */
// /*public*/ class SignalMastIconXml extends PositionableLabelXml {

///*public*/ SignalMastIconXml() {
//}

/**
 * Default implementation for storing the contents of a
 * SignalMastIcon
 * @param o Object to store, of type SignalMastIcon
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement SignalMastIconXml::store(QObject* o) {

    SignalMastIcon* p = (SignalMastIcon*)o;
    if (!p->isActive()) return QDomElement();  // if flagged as inactive, don't store

    QDomElement element = doc.createElement("signalmasticon");

    element.setAttribute("signalmast", p->getNamedSignalMast()->getName());
    storeCommonAttributes((Positionable*)p, element);
    element.setAttribute("clickmode", p->getClickMode());
    element.setAttribute("litmode", p->getLitMode());
    element.setAttribute("degrees", p->getDegrees());
    element.setAttribute("scale", p->getScale());
    element.setAttribute("imageset", p->useIconSet());
    element.setAttribute("class", "jmri.jmrit.display.configurexml.SignalMastIconXml");
    //storeIconInfo(p, element);
    return element;
}


/*public*/ bool SignalMastIconXml::load(QDomElement /*element*/) throw (Exception){
    log->error("Invalid method called");
    return false;
}

/**
 * Create a SignalMastIcon, then add
 * @param element Top level QDomElement to unpack.
 * @param o  an Editor as an Object
 */
/*public*/ void SignalMastIconXml::load(QDomElement element, QObject* o) throw (Exception)
{
 // create the objects
 Editor* ed = (Editor*)o;
 l = new SignalMastIcon(ed);
 QString name;

 QString attr;
 /*
  * We need to set the rotation and scaling first, prior to setting the
  * signalmast, otherwise we end up in a situation where by the icons do
  * not get rotated or scaled correctly.
  **/
 bool bOk = true;
 bool bok;
// try
// {
  int rotation = 0;
  double scale = 1.0;
  attr = element.attribute("rotation");    // former attribute name.
  if (attr!="")
  {
   rotation = attr.toInt(&bok);
   if(!bok) bOk = false;
  }
  attr = element.attribute("degrees");
  if (attr!="")
  {
   rotation = attr.toInt(&bok);
   if(!bok) bOk = false;
  }
  l->rotate(rotation);
  attr = element.attribute("scale");
  QString text = "Error attr NULL";
  if (attr!="")
  {
   scale = attr.toDouble(&bok);
   text = attr;
   if(!bok) bOk = false;
  }
  l->setScale(scale);
  if (log->isDebugEnabled()) log->debug("Load SignalMast rotation= "+QString::number(rotation)+
                                         " scale= "+QString::number(scale)+" attr text= "+text);
// }
 //catch ( DataConversionException e)
 if(!bOk)
 {
  log->error("failed to convert rotation or scale attribute");
 }
 attr = element.attribute("signalmast");
 if (attr == NULL)
 {
  log->error("incorrect information for signal mast; must use signalmast name");
  ed->loadFailed();
  return;
 }
 else
 {
  name = attr;
  if (log->isDebugEnabled()) log->debug("Load SignalMast "+name);
 }

 SignalMast* sh = static_cast<SignalMastManager*>( InstanceManager::getDefault("SignalMastManager"))->getSignalMast(name);
 if (sh != NULL)
 {
  l->setSignalMast(new NamedBeanHandle<SignalMast*>(name, sh));
 }
 else
 {
  log->error("SignalMast named '"+attr+"' not found.");
  ed->loadFailed();
  return;
 }

 attr=element.attribute("imageset");
 if(attr!="")
  l->useIconSet(attr);

 attr=element.attribute("imageset");
 if(attr!="")
  l->useIconSet(attr);

// try {
  attr = element.attribute("clickmode");
  if (attr!="")
  {
   l->setClickMode(attr.toInt(&bok));
  }
// }
//catch (DataConversionException e) {
  if(!bok)
  {
  log->error("Failed on clickmode attribute: "/*+e.getMessage()*/);
  }

// try {
  attr = element.attribute("litmode");
  if (attr!="")
  {
      l->setLitMode(attr=="true"?true:false);
  }
// } catch (DataConversionException e) {
//     log->error("Failed on litmode attribute: "+e.getMessage());
// }

 // load individual item's option settings after editor has set its global settings
 loadCommonAttributes((Positionable*)l, Editor::SIGNALS, element);

 ed->putItem((Positionable*)l);
}

SignalMastIcon* SignalMastIconXml::getIcon() { return l;}
