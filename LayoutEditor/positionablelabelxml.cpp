#include "positionablelabelxml.h"
#include "layouteditor.h"
#include "positionablepopuputil.h"

PositionableLabelXml::PositionableLabelXml(QObject *parent) :
    AbstractXmlAdapter(parent)
{
    log = new Logger("PositionableLabelXml");
}
/**
 * Handle configuration for display.PositionableLabel objects
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002
 * @version $Revision: 21072 $
 */
//public class PositionableLabelXml extends AbstractXmlAdapter {

//    public PositionableLabelXml() {
//    }

/**
 * Default implementation for storing the contents of a
 * PositionableLabel
 * @param o Object to store, of type PositionableLabel
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement PositionableLabelXml::store(QObject* o)
{
 PositionableLabel* p = (PositionableLabel*)o;

 if (!p->isActive()) return QDomElement();  // if flagged as inactive, don't store

 QDomElement element =doc.createElement("positionablelabel");
 storeCommonAttributes((Positionable*)p, element);

 if (p->isText())
 {
  if (p->getUnRotatedText()!=NULL) element.setAttribute("text", p->getUnRotatedText());
   storeTextInfo((Positionable*)p, element);
 }

 if (p->isIcon() && p->getIcon()!=NULL)
 {
  element.setAttribute("icon", "yes");
  element.appendChild(storeIcon("icon", (NamedIcon*)p->getIcon()));
 }

 element.setAttribute("class", "jmri.jmrit.display.configurexml.PositionableLabelXml");
 return element;
}

/**
 * Store the text formatting information.
 * <p>
 * This is always stored, even if the icon isn't in text mode,
 * because some uses (subclasses) of PositionableLabel flip
 * back and forth between icon and text, and want to remember their
 * formatting.
 */
/*protected*/ void PositionableLabelXml::storeTextInfo(Positionable* p, QDomElement element)
{
 //if (p.getText()!=NULL) element.setAttribute("text", p.getText());
 PositionablePopupUtil* util = p->getPopupUtility();
 element.setAttribute("size", util->getFontSize());
 element.setAttribute("style", util->getFontStyle());
 if (util->getForeground()!=QColor(Qt::black))
 {
  element.setAttribute("red", util->getForeground().red());
  element.setAttribute("green", util->getForeground().green());
  element.setAttribute("blue", util->getForeground().blue());
 }
 if(/*(p->isOpaque() || p->getSaveOpaque())&& */util->getBackground() != QColor(Qt::transparent))
 {
  element.setAttribute("redBack", util->getBackground().red());
  element.setAttribute("greenBack", util->getBackground().green());
  element.setAttribute("blueBack", util->getBackground().blue());
 }
 if (util->getMargin()!=0)
   element.setAttribute("margin", util->getMargin());
 if (util->getBorderSize()!=0)
 {
  element.setAttribute("borderSize", util->getBorderSize());
  element.setAttribute("redBorder", util->getBorderColor().red());
  element.setAttribute("greenBorder", util->getBorderColor().green());
  element.setAttribute("blueBorder", util->getBorderColor().blue());
  }
  if (util->getFixedWidth()!=0)
   element.setAttribute("fixedWidth", util->getFixedWidth());
  if (util->getFixedHeight()!=0)
   element.setAttribute("fixedHeight", util->getFixedHeight());

  QString just;
  switch (util->getJustification())
  {
  case 0x02 : just="right";
   break;
  case 0x04 : just ="centre";
   break;
  default :   just="left";
   break;
  }
  element.setAttribute("justification", just);

  if(util->getOrientation()!=PositionablePopupUtil::HORIZONTAL){
  QString ori;
  switch (util->getOrientation())
  {
  case PositionablePopupUtil::VERTICAL_DOWN: ori="vertical_down";
   break;
  case PositionablePopupUtil::VERTICAL_UP:   ori = "vertical_up";
   break;
  default : ori = "horizontal";
   break;
  }
 element.setAttribute("orientation", ori);
 }
 //return element;
}
/**
 * Default implementation for storing the common contents of an Icon
 * @param element QDomElement in which contents are stored
 */
/*public*/ void PositionableLabelXml::storeCommonAttributes(Positionable* p, QDomElement element)
{
 element.setAttribute("x", p->getX());
 element.setAttribute("y", p->getY());
 element.setAttribute("level", p->getDisplayLevel());
 element.setAttribute("forcecontroloff", (!p->isControlling()?"true":"false"));
 element.setAttribute("hidden", p->isHidden()?"yes":"no");
 element.setAttribute("positionable", (p->isPositionable()?"true":"false"));
 element.setAttribute("showtooltip", (p->showToolTip()?"true":"false"));
 element.setAttribute("editable", (p->isEditable()?"true":"false"));
// ToolTip tip = p.getTooltip();
// QString txt = tip.getText();
 QString txt = p->getToolTip();
 if (txt!=NULL)
 {
  QDomElement elem = doc.createElement("tooltip");
  elem.appendChild(doc.createTextNode(txt));
  element.appendChild(elem);
 }
 if (p->getDegrees()!=0)
 {
  element.setAttribute("degrees", p->getDegrees());
 }
}

/*public*/ QDomElement PositionableLabelXml::storeIcon(QString elemName, NamedIcon* icon)
{
 if (icon==NULL)
 {
     return QDomElement();
 }
 QDomElement element = doc.createElement(elemName);
 element.setAttribute("url", icon->getURL().replace(":/", "program:"));
 element.setAttribute("degrees", icon->getDegrees());
 element.setAttribute("scale", icon->getScale());

 // the "rotate" attribute was deprecated in 2.9.4, replaced by the "rotation" element
 //element.addContent(new QDomElement("rotation").addContent(String.valueOf(icon.getRotation())));
 QDomElement e = doc.createElement("rotation");
 e.appendChild(doc.createTextNode(QString("%1").arg(icon->getRotation())));
 element.appendChild(e);
 return element;
}

/*public*/ bool PositionableLabelXml::load(QDomElement /*element*/)  throw (Exception)
{
    log->error("Invalid method called");
    return false;
}

/**
 * Create a PositionableLabel, then add to a target JLayeredPane
 * @param element Top level QDomElement to unpack.
 * @param o  Editor as an Object
 */
//@SuppressWarnings("unchecked")
/*public*/ void PositionableLabelXml::load(QDomElement element, QObject* o) throw (Exception)
{
 // create the objects
 l = NULL;

 // get object class and determine editor being used
 Editor* editor = (Editor*)o;
 if (element.attribute("icon")!="")
 {
  NamedIcon* icon = NULL;
  QString name = element.attribute("icon");
//            if (log.isDebugEnabled()) log.debug("icon attribute= "+name);
  if (name==("yes"))
  {
   icon = getNamedIcon("icon", element, "PositionableLabel ", editor);
  }
  else
  {
   icon = NamedIcon::getIconByName(name);
   if (icon==NULL)
   {
    icon = editor->loadFailed("PositionableLabel", name);
    if (icon==NULL)
    {
     log->info("PositionableLabel icon removed for url= "+name);
     return;
    }
   }
  }
  // allow NULL icons for now
  l = new PositionableLabel(icon, editor);
  l->setPopupUtility(NULL);        // no text
//  try
//  {
   QString a = element.attribute("rotate");
   if (!a.isEmpty() && icon!=NULL)
   {
    bool bOk;
    int rotation = element.attribute("rotate", "0").toInt(&bOk);
    //if(!bOk) throw new DataConversionException();
    icon->setRotation(rotation, l);
   }
//  }
//  catch (DataConversionException e) {}

  if (name==("yes"))
  {
   NamedIcon* nIcon = loadIcon(l,"icon", element, "PositionableLabel ", editor);
   if (nIcon!=NULL)
   {
    l->updateIcon(nIcon);
   }
   else
   {
    log->info("PositionableLabel icon removed for url= "+name);
    return;
   }
  }
  else
  {
   if (icon==NULL)
   {
    log->info("PositionableLabel icon removed for url= "+name);
    return;
   }
   else
   {
    l->updateIcon(icon);
   }
  }

  //l.setSize(l.getPreferredSize().width, l.getPreferredSize().height);
 }
 else if (!element.attribute("text").isEmpty())
 {
  l = new PositionableLabel(element.attribute("text"), editor);
  loadTextInfo((Positionable*)l, element);
 }
 else
 {
  log->error("PositionableLabel is NULL!");
  if (log->isDebugEnabled())
  {
   //java.util.List <Attribute> attrs = element.getAttributes();
   QDomNamedNodeMap attrs = element.attributes();
   log->debug("\tQDomElement Has "+QString("%1").arg(attrs.size())+" Attributes:");
   for (int i=0; i<attrs.size(); i++)
   {
    QDomNode n = attrs.item(i);
    log->debug("\t\t"+n.toAttr().name()+" = "+n.toAttr().value());
   }
   //java.util.List <QDomElement> kids = element.getChildren();
   QDomNodeList kids = element.childNodes();
   log->debug("\tQDomElement Has "+QString("%1").arg(kids.size())+" children:");
   for (int i=0; i<kids.size(); i++)
   {
    QDomElement e = kids.at(i).toElement();
    log->debug("\t\t"+e.toElement().tagName()+" = \""+e.text()+"\"");
   }
  }
  editor->loadFailed();
  return;
 }
 // load individual item's option settings after editor has set its global settings
 loadCommonAttributes((Positionable*)l, LayoutEditor::LABELS, element);

 editor->putItem((Positionable*)l);
}

/*protected*/ void PositionableLabelXml::loadTextInfo(Positionable* l, QDomElement element)
{
 if (log->isDebugEnabled()) log->debug("loadTextInfo");
 PositionablePopupUtil* util = l->getPopupUtility();
 if (util==NULL)
 {
  log->warn("PositionablePopupUtil is NULL! "+element.tagName());
  return;
 }
 QString a = element.attribute("size", "10");
 bool bOk;
 bool bOk1;
 if (!a.isEmpty()) util->setFontSize(a.toFloat(&bOk));
 if(!bOk) /*throw new DataConversionException();*/
 {
  log->warn("invalid size attribute value");
 }
 a = element.attribute("style", "0");
 bOk=true;
 if (a!="")
 {
  int style = a.toInt(&bOk);
  //if(!bOk) throw new DataConversionException();

  int drop = 0;
  switch (style)
  {
  case 0: drop = 1; //0 Normal
   break;
  case 2: drop = 1; //italic
   break;
  }
  util->setFontStyle(style, drop);
 }
 if(!bOk)
 {
  log->warn("invalid style attribute value");
 }

 // set color if needed
// try
// {
 QColor c = l->getForeground();
 bOk=true;
 int red = element.attribute("red", QString::number(c.red())).toInt(&bOk1);
 if(!bOk1) bOk=false;
 int blue = element.attribute("blue", QString::number(c.blue())).toInt(&bOk1);
 if(!bOk1) bOk=false;
 int green = element.attribute("green", QString::number(c.green())).toInt(&bOk1);
 if(!bOk1) bOk=false;
  util->setForeground(QColor(red, green, blue));
 if(!bOk)
 {
  log->warn("Could not parse color attributes!");
 }
// catch ( NullPointerException e)
// {  // considered normal if the attributes are not present
// }

 bOk = true;
 c = l->getBackground();
 red = element.attribute("redBack", "?").toInt(&bOk1);
 if(!bOk1) bOk=false;
 blue = element.attribute("blueBack", "?").toInt(&bOk1);
 if(!bOk1) bOk=false;
 green = element.attribute("greenBack", "?").toInt(&bOk1);
 if(!bOk1) bOk=false;
 if(bOk)
 {
  util->setBackgroundColor(QColor(red, green, blue));
 }
 else
 {
  util->setBackgroundColor(QColor(Qt::transparent));
  log->warn("Could not parse background color attributes!");
 }
// catch ( NullPointerException e)
// {
//  util->setBackgroundColor(QColor());// if the attributes are not listed, we consider the background as clear.
// }

 int fixedWidth=0;
 int fixedHeight=0;
 bOk = true;
 fixedHeight=element.attribute("fixedHeight", "0").toInt(&bOk);
 if(!bOk)
 {
  log->warn("Could not parse fixed Height attributes!");
 }
// catch ( NullPointerException e)
// {  // considered normal if the attributes are not present
// }

// try
// {

 fixedWidth=element.attribute("fixedWidth", "0").toInt(&bOk);

 if(!bOk)
 {
  log->warn("Could not parse fixed Width attribute!");
 }
// catch ( NullPointerException e)
// {  // considered normal if the attributes are not present
// }
 if (!(fixedWidth==0 && fixedHeight==0))
  util->setFixedSize(fixedWidth, fixedHeight);
 int margin=0;
 if ((util->getFixedWidth()==0) || (util->getFixedHeight()==0))
 {
  bool bOk;
  margin=element.attribute("margin", "0").toInt(&bOk);
  //if(!bOk) throw new DataConversionException();
  util->setMargin(margin);
//  }
//  catch (DataConversionException e)
  if(!bOk)
  {
   log->warn("Could not parse margin attribute!");
  }
//  catch ( NullPointerException e)
//  {  // considered normal if the attributes are not present
//  }
 }
 bOk= true;
 util->setBorderSize(element.attribute("borderSize", "0").toInt(&bOk1));
 if(!bOk1) bOk=false;
 red = element.attribute("redBorder", "0").toInt(&bOk1);
 if(!bOk1) bOk=false;
 blue = element.attribute("blueBorder", "0").toInt(&bOk1);
 if(!bOk1) bOk=false;
 green = element.attribute("greenBorder", "0").toInt(&bOk1);
  //if(!bOk) throw new DataConversionException();
 util->setBorderColor(QColor(red, green, blue));
 if(!bOk)
 {
  log->warn("Could not parse border attributes!");
 }
// catch ( NullPointerException e)
// {  // considered normal if the attribute not present
// }

 a = element.attribute("justification");
 if(a!="")
  util->setJustification(a);
 else
  util->setJustification("left");
 a = element.attribute("orientation");
 if(a!="")
  util->setOrientation(a);
 else
  util->setOrientation("horizontal");

 a = element.attribute("degrees", "0");
 if(a!="")
 {
  bool bOk;
  l->rotate(a.toInt(&bOk));
  if(!bOk) /*throw new DataConversionException();*/
  {
   log->warn("invalid 'degrees' value (non integer)");
  }
 }
}

/*public*/ void PositionableLabelXml::loadCommonAttributes(Positionable* l, int defaultLevel, QDomElement element)
{
 QString a = element.attribute("forcecontroloff");
 if ( (a!="") && a==("true"))
  l->setControlling(false);
 else
  l->setControlling(true);

 // find coordinates
 int x = 0;
 int y = 0;
// try
// {
  bool bOk = true;
  bool bOk1;
  x = element.attribute("x", "0").toInt(&bOk1);
  if(!bOk1) bOk = false;
  y = element.attribute("y", "0").toInt(&bOk);
  if(!bOk1) bOk=false;
 if(!bOk)
 {
  log->error("failed to convert positional attribute");
 }
 l->setLocation(x,y);

 // find display level
 int level = defaultLevel;
 level = element.attribute("level", QString::number(defaultLevel)).toInt(&bOk);
 if(!bOk)
 {
  log->warn("Could not parse level attribute!");
 }
// catch ( NullPointerException e)
// {  // considered normal if the attribute not present
// }
 l->setDisplayLevel(level);

 a = element.attribute("hidden");
 if ( (a!="") && a==("yes"))
 {
  l->setHidden(true);
  l->setVisible(false);
 }
 a = element.attribute("positionable");
 if ( (a!="") && a==("true"))
  l->setPositionable(true);
 else
  l->setPositionable(false);

 a = element.attribute("showtooltip");
 if ( (a!="") && a==("true"))
  l->setShowToolTip(true);
 else
  l->setShowToolTip(false);

 a = element.attribute("editable");
 if ( (a!="") && a==("true"))
  l->setEditable(true);
 else
  l->setEditable(false);

 QDomElement elem = element.firstChildElement("tooltip");
 if (!elem.isNull())
 {
//  ToolTip tip = l->getTooltip();
//  if (tip!=NULL)
//  {
//   tip.setText(elem.getText());
//  l->setToolTip(elem.text()); // (QWidget tooltip)
  l->setToolTip(elem.text()); // (PositionableLabel)
//  }
  if(l->_itemGroup != NULL)
   l->_itemGroup->setToolTip(elem.text());
 }
}
/*public*/ NamedIcon* PositionableLabelXml::loadIcon(PositionableLabel* l, QString attrName, QDomElement element, QString name, Editor* ed)
{
 NamedIcon* icon = getNamedIcon(attrName, element, name, ed);
 if (icon != NULL)
 {
//  try
//  {
   int deg = 0;
   double scale = 1.0;
   QDomElement elem = element.firstChildElement(attrName);
   if (!elem.isNull())
   {
    QString a = elem.attribute("degrees", "0");
    if (a!="")
    {
     bool bOk;
     deg = a.toInt(&bOk);
     //if(!bOk) throw new DataConversionException();
    }
    a =  elem.attribute("scale", "0");
    if (a!="")
    {
     bool bOk;
     scale = elem.attribute("scale", "0").toDouble(&bOk);
     //if(!bOk) throw new DataConversionException();
    }
    icon->setLoad(deg, scale, l);
    if ( deg==0)
    {
     // "rotate" attribute is JMRI 2.9.3 and before
     a = elem.attribute("rotate", "0");
     if (a!="")
     {
      bool bOk;
      int rotation = a.toInt(&bOk);
      // 2.9.3 and before, only unscaled icons rotate
      //if(!bOk) throw new DataConversionException();
      if (scale == 1.0) icon->setRotation(rotation, l);
     }
     // "rotation" element is JMRI 2.9.4 and after
     QDomElement e = elem.firstChildElement("rotation");
     if (!e.isNull())
     {
      // ver 2.9.4 allows orthogonal rotations of scaled icons
      bool bOk;
      int rotation = e.text().toInt(&bOk);
      //if(!bOk) throw new DataConversionException();
      icon->setRotation(rotation, l);
     }
    }
   }
  //}
  //catch (DataConversionException dce) {}
 }
 return icon;
}


/*protected*/ NamedIcon* PositionableLabelXml::getNamedIcon(QString childName, QDomElement element,
                                        QString name, Editor* ed)
{
 NamedIcon* icon = nullptr;
 QDomElement elem = element.firstChildElement(childName);
 if (!elem.isNull())
 {
  QString iconName = elem.attribute("url");
  //iconName.replace("program:", ":");
  icon = NamedIcon::getIconByName(iconName);
  if (icon==NULL)
  {
   icon = ed->loadFailed(name, iconName);
   if (icon==NULL)
   {
    log->info(name+" removed for url= "+iconName);
   }

  }
 }
 else
 {
  log->debug("getNamedIcon: child element \""+childName+"\" not found in element "+element.tagName());
 }
 return icon;
}

void PositionableLabelXml::setDoc(QDomDocument doc)
{
 this->doc = doc;
}
PositionableLabel* PositionableLabelXml::getIcon() {return l;}
