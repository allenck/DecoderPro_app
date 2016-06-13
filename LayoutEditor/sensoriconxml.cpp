#include "sensoriconxml.h"
#include "sensoricon.h"
#include "editor.h"

QHash<QString,QString>* SensorIconXml::_nameMap = new QHash<QString,QString>();
//SensorIconXml::SensorIconXml(QObject *parent) :
//    PositionableLabelXml(parent)
//{
//}
/**
 * Handle configuration for display.SensorIcon objects
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002
 * @version $Revision: 21078 $
 */
//public class SensorIconXml extends PositionableLabelXml {


/*public*/ SensorIconXml::SensorIconXml(QObject *parent) : PositionableLabelXml(parent)
{
 log = new Logger("SensorIconXml");
 setObjectName("SensorIconXml");
 //_nameMap = new QHash<QString,QString>();

 // map previous store names to actual localized names
 _nameMap->insert("active", "SensorStateActive");
 _nameMap->insert("inactive", "SensorStateInactive");
 _nameMap->insert("unknown", "BeanStateUnknown");
 _nameMap->insert("inconsistent", "BeanStateInconsistent");
}

/**
 * Default implementation for storing the contents of a
 * SensorIcon
 * @param o Object to store, of type SensorIcon
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement SensorIconXml::store(QObject* o)
{
 SensorIcon* p = (SensorIcon*)o;
 if (!p->isActive()) return QDomElement();  // if flagged as inactive, don't store
 QDomElement element = doc.createElement("sensoricon");
 element.setAttribute("sensor", p->getNamedSensor()->getName());
 storeCommonAttributes((Positionable*)p, element);
 element.setAttribute("momentary", (p->getMomentary()?"true":"false"));
 element.setAttribute("icon", (p->isIcon()?"yes":"no"));

 storeIconInfo(p, element);
 storeTextInfo(p, element);
 element.setAttribute("class", "jmri.jmrit.display.configurexml.SensorIconXml");
 return element;
}

/*protected*/ void SensorIconXml::storeTextInfo(SensorIcon* p, QDomElement element)
{
 if (p->getText()=="")
 {
  QString s = p->getOriginalText();
  if (s!="" && s.length()>0)
  {
   element.setAttribute("text", s);
  }
  else if (p->isText())
  {
   element.setAttribute("text", "");
  }
  else
  {
   return;
  }
 }
 else
 {
  element.setAttribute("text", p->getText());
 }
 // get iconic overlay text info
 PositionableLabelXml::storeTextInfo((Positionable*)p, element);
 // get state textual info
 QDomElement textElement = doc.createElement("activeText");
 if(p->getActiveText()!="")
   textElement.setAttribute("text", p->getActiveText());
 if (p->getTextActive()!=(QColor(Qt::black)))
 {
  textElement.setAttribute("red", p->getTextActive().red());
  textElement.setAttribute("green", p->getTextActive().green());
  textElement.setAttribute("blue", p->getTextActive().blue());
 }
 if (p->getBackgroundActive()!="")
 {
  textElement.setAttribute("redBack", p->getBackgroundActive().red());
  textElement.setAttribute("greenBack", p->getBackgroundActive().green());
  textElement.setAttribute("blueBack", p->getBackgroundActive().blue());
 }
 element.appendChild(textElement);
 textElement = doc.createElement("inactiveText");
 if(p->getInactiveText()!="")
  textElement.setAttribute("text", p->getInactiveText());
 if(p->getTextInActive()!=(QColor(Qt::black)))
 {
  textElement.setAttribute("red", p->getTextInActive().red());
        textElement.setAttribute("green", p->getTextInActive().green());
        textElement.setAttribute("blue", p->getTextInActive().blue());
 }
 if(p->getBackgroundInActive()!="")
 {
  textElement.setAttribute("redBack", p->getBackgroundInActive().red());
  textElement.setAttribute("greenBack", p->getBackgroundInActive().green());
  textElement.setAttribute("blueBack", p->getBackgroundInActive().blue());
 }
 element.appendChild(textElement);

 textElement = doc.createElement("unknownText");

 if(p->getUnknownText()!="")
   textElement.setAttribute("text", p->getUnknownText());
 if(p->getTextUnknown()!=(QColor(Qt::black)))
 {
  textElement.setAttribute("red", p->getTextUnknown().red());
  textElement.setAttribute("green", p->getTextUnknown().green());
  textElement.setAttribute("blue", p->getTextUnknown().blue());
 }
 if(p->getBackgroundUnknown()!="")
 {
  textElement.setAttribute("redBack", p->getBackgroundUnknown().red());
  textElement.setAttribute("greenBack", p->getBackgroundUnknown().green());
  textElement.setAttribute("blueBack", p->getBackgroundUnknown().blue());
 }
 element.appendChild(textElement);

 textElement =doc.createElement("inconsistentText");
 if(p->getInconsistentText()!="")
  textElement.setAttribute("text", p->getInconsistentText());
 if(p->getTextInconsistent()!=(QColor(Qt::black)))
 {
  textElement.setAttribute("red", p->getTextInconsistent().red());
  textElement.setAttribute("green", p->getTextInconsistent().green());
  textElement.setAttribute("blue", p->getTextInconsistent().blue());
 }
 if(p->getBackgroundInconsistent()!="")
 {
  textElement.setAttribute("redBack", p->getBackgroundInconsistent().red());
  textElement.setAttribute("greenBack", p->getBackgroundInconsistent().green());
  textElement.setAttribute("blueBack", p->getBackgroundInconsistent().blue());
 }
 element.appendChild(textElement);
}

/*protected*/ void SensorIconXml::storeIconInfo(SensorIcon* p, QDomElement element)
{
    element.appendChild(storeIcon("active", p->getIcon("SensorStateActive")));
    element.appendChild(storeIcon("inactive", p->getIcon("SensorStateInactive")));
    element.appendChild(storeIcon("unknown", p->getIcon("BeanStateUnknown")));
    element.appendChild(storeIcon("inconsistent", p->getIcon("BeanStateInconsistent")));
    QDomElement elem = doc.createElement("iconmaps");
    QString family = p->getFamily();
    if (family!="") {
        elem.setAttribute("family", family);
    }
    element.appendChild(elem);
}

/*public*/ bool SensorIconXml::load(QDomElement /*element*/) throw (Exception)
{
    log->error("Invalid method called");
    return false;
}

/**
 * Create a PositionableLabel, then add to a target JLayeredPane
 * @param element Top level QDomElement to unpack.
 * @param o  an Editor as an Object
 */
/*public*/ void SensorIconXml::load(QDomElement element, QObject* o) throw (Exception)
{
 Editor* ed = (Editor*)o;
 QString name;
 QString attr = element.attribute("sensor");
 if (attr == NULL)
 {
  log->error("incorrect information for sensor; must use sensor name");
  ed->loadFailed();
  return;
 }
 else
 {
  name = attr;
 }
 _icon=true;
 if (element.attribute("icon") != NULL)
 {
  QString yesno = element.attribute("icon");
  if ( yesno!="")
  {
   if (yesno==("yes")) _icon=true;
   else if (yesno==("no")) _icon=false;
  }
 }

 if (_icon)
 {
  l = new SensorIcon(new NamedIcon(":/resources/icons/smallschematics/tracksegments/circuit-error.gif", "resources/icons/smallschematics/tracksegments/circuit-error.gif"), ed);
 }
 else
 {
  l = new SensorIcon("  ", ed);
 }
 int rotation = 0;
// try {
 bool bOk;
 rotation = element.attribute("rotate", "0").toInt(&bOk);
//    } catch (org.jdom.DataConversionException e) {
//    } catch ( NullPointerException e) {  // considered normal if the attributes are not present
//    }

 if (loadSensorIcon("active", rotation, l, element, name, ed)==NULL)
 {
  return;
 }
 if (loadSensorIcon("inactive", rotation, l, element, name, ed)==NULL)
 {
  return;
 }
 if (loadSensorIcon("unknown", rotation, l,element, name, ed)==NULL)
 {
  return;
 }
 if (loadSensorIcon("inconsistent", rotation, l,element, name, ed)==NULL)
 {
  return;
 }
 QDomElement elem = element.firstChildElement("iconmaps");
 if (!elem.isNull())
 {
  attr = elem.attribute("family");
  if (attr!=NULL)
  {
   l->setFamily(attr);
  }
 }

 QString a = element.attribute("momentary");
 if ( (a!="") && a==("true"))
  l->setMomentary(true);
 else
  l->setMomentary(false);

 l->setSensor(name);

 loadTextInfo(l, element);
    // load individual item's option settings after editor has set its global settings
 loadCommonAttributes((Positionable*)l, Editor::SENSORS, element);
 ed->putItem((Positionable*)l);
}

/*private*/ NamedIcon* SensorIconXml::loadSensorIcon(QString state, int rotation, SensorIcon* l,
                                 QDomElement element, QString name, Editor* ed)
{
 QString msg = "SensorIcon \""+name+"\": icon \""+state+"\" ";
 // loadIcon gets icon as an element
 NamedIcon* icon = loadIcon(l,state, element, msg, ed);
 if (icon==NULL && _icon)
 {
  // old config files may define icons as attributes
  QString iconName;
  if (element.attribute(state) != ""
        && (iconName = element.attribute(state))!=(""))
  {

   icon = NamedIcon::getIconByName(iconName);
   if (icon==NULL)
   {
    icon = ed->loadFailed(msg, iconName);
    if (icon==NULL)
    {
     log->info(msg+" removed for url= "+iconName);
    }
   }
   else
   {
    icon->setRotation(rotation, (QObject*)l);
   }
  }
  else log->warn("did not locate " + state + " icon file for "+name);
 }
 if (icon==NULL)
 {
  log->info(msg+" removed");
 }
 else
 {
  l->setIcon(_nameMap->value(state), icon);
 }
 return icon;
}

void SensorIconXml::loadTextInfo(SensorIcon* l, QDomElement element)
{
 PositionableLabelXml::loadTextInfo((Positionable*)l, element);

 loadSensorTextState("Active", l, element);
 loadSensorTextState("InActive", l, element);
 loadSensorTextState("Unknown", l, element);
 loadSensorTextState("Inconsistent", l, element);
 if (element.attribute("text")!="")
 {
  l->setText(element.attribute("text"));
 }
}

//@SuppressWarnings("unchecked")
/*private*/ void SensorIconXml::loadSensorTextState(QString state, SensorIcon* l, QDomElement element)
{
 QString name = "";
 bool bOk=true;
 bool bOk1;

 QColor clrText=QColor();
 QColor clrBackground=QColor();
 QDomNodeList textList = element.elementsByTagName(state.toLower()+"Text");
 if (log->isDebugEnabled()) log->debug("Found "+QString("%1").arg(textList.size())+" "+state+"Text objects");
 if (textList.size()>0)
 {
  QDomElement elem = textList.at(0).toElement();
//  try {
  name = elem.attribute("text");
//  } catch ( NullPointerException e) {  // considered normal if the attributes are not present
//  }
  //try {
  int red = elem.attribute("red","0").toInt(&bOk1);
  if(!bOk1) bOk = false;
  int blue = elem.attribute("blue","0").toInt(&bOk1);
  if(!bOk1) bOk = false;
  int green = elem.attribute("green","0").toInt(&bOk1);
  if(!bOk1) bOk = false;
  clrText = QColor(red, green, blue);
  //} catch ( org.jdom.DataConversionException e) {
  if(bOk)
   log->warn("Could not parse color attributes!");
//    } catch ( NullPointerException e) {  // considered normal if the attributes are not present
//    }
//    try {
  bOk = true;
  red = elem.attribute("redBack","0").toInt(&bOk1);
  if(!bOk1) bOk = false;
  blue = elem.attribute("blueBack","0").toInt(&bOk1);
  if(!bOk1) bOk = false;
  green = elem.attribute("greenBack","0").toInt(&bOk1);
  if(!bOk1) bOk = false;
  clrBackground = QColor(red, green, blue);
  //} catch ( org.jdom.DataConversionException e) {
  if(bOk)
   log->warn("Could not parse color attributes!");
//    } catch ( NullPointerException e) {  // considered normal if the attributes are not present
//    }

 }
 else
 {
  if (element.attribute(state.toLower())!="")
  {
    name = element.attribute(state.toLower());
  }
  //try {
  bOk=true;
  int red = element.attribute("red"+state,"0").toInt(&bOk1);
  if(!bOk1) bOk = false;
  int blue = element.attribute("blue"+state,"0").toInt(&bOk1);
  if(!bOk1) bOk = false;
  int green = element.attribute("green"+state,"0").toInt(&bOk1);
  if(!bOk1) bOk = false;
  clrText =  QColor(red, green, blue);
  //} catch ( org.jdom.DataConversionException e) {
  if(!bOk)
   log->warn("Could not parse color attributes!");
  //} catch ( NullPointerException e) {  // considered normal if the attributes are not present
  //}
  //try {
   bOk = true;
  red = element.attribute("red"+state+"Back","0").toInt(&bOk1);
  if(!bOk1) bOk = false;
  blue = element.attribute("blue"+state+"Back","0").toInt(&bOk1);
  if(!bOk1) bOk = false;
  green = element.attribute("green"+state+"Back","0").toInt(&bOk1);
  if(!bOk1) bOk = false;
  clrBackground =  QColor(red, green, blue);
  //} catch ( org.jdom.DataConversionException e) {
  if(!bOk)
   log->warn("Could not parse color attributes!");
  //} catch ( NullPointerException e) {  // considered normal if the attributes are not present
  //}
 }
 if (state==("Active"))
 {
  if (name!="") l->setActiveText(name);
  if (clrText.isValid()) l->setTextActive(clrText);
  if (clrBackground.isValid()) l->setBackgroundActive(clrBackground);
 }
 else if (state==("InActive"))
 {
  if (name!="") l->setInactiveText(name);
  if (clrText.isValid()) l->setTextInActive(clrText);
  if (clrBackground.isValid()) l->setBackgroundInActive(clrBackground);
 }
 else if (state==("Unknown"))
 {
  if (name!="") l->setUnknownText(name);
  if (clrText.isValid()) l->setTextUnknown(clrText);
  if (clrBackground.isValid()) l->setBackgroundUnknown(clrBackground);
 }
 else if (state==("Inconsistent"))
 {
  if (name!="") l->setInconsistentText(name);
  if (clrText.isValid()) l->setTextInconsistent(clrText);
  if (clrBackground.isValid()) l->setBackgroundInconsistent(clrBackground);
 }
}
SensorIcon* SensorIconXml::getIcon() { return l;}
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SensorIconXml.class.getName());

//}
