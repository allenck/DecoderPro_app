#include "defaultsignalappearancemap.h"
#include "xmlfile.h"
#include "fileutil.h"
#include "signalhead.h"
#include "instancemanager.h"

//DefaultSignalAppearanceMap::DefaultSignalAppearanceMap(QObject *parent) :
//    SignalAppearanceMap(parent)
//{
//}
/**
 * Default implementation of a basic signal head table.
 * <p>
 * The default contents are taken from the NamedBeanBundle properties file.
 * This makes creation a little more heavy-weight, but speeds operation.
 *
 * @author	Bob Jacobsen Copyright (C) 2009
 * @version     $Revision: 22547 $
 */
///*public*/ class DefaultSignalAppearanceMap extends AbstractNamedBean implements jmri.SignalAppearanceMap {
/*static*/ QMap<QString, DefaultSignalAppearanceMap*>* DefaultSignalAppearanceMap::maps
        = new QMap<QString, DefaultSignalAppearanceMap*>();

/*public*/ DefaultSignalAppearanceMap::DefaultSignalAppearanceMap(QString systemName, QString userName) : SignalAppearanceMap(systemName, userName)
{
 //super(systemName, userName);
 log = new Logger("DefaultSignalAppearanceMap");
 aspectAttributeMap = new QHash<QString, QHash<QString, QString> >();
 aspectImageMap = new QHash<QString, QHash<QString, QString> >();
 specificMaps = new QHash<int, QString>();
 aspectRelationshipMap = new QHash<QString, QVector<QString> >();
 table = new QMap<QString, QVector<int>* >();
}

/*public*/ DefaultSignalAppearanceMap::DefaultSignalAppearanceMap(QString systemName) : SignalAppearanceMap(systemName)
{
 //super(systemName);
 log = new Logger("DefaultSignalAppearanceMap");
 aspectAttributeMap = new QHash<QString, QHash<QString, QString> >();
 aspectImageMap = new QHash<QString, QHash<QString, QString> >();
 specificMaps = new QHash<int, QString>();
 aspectRelationshipMap = new QHash<QString, QVector<QString> >();
 table = new QMap<QString, QVector<int>* >();
}

/*static*/ /*public*/ DefaultSignalAppearanceMap* DefaultSignalAppearanceMap::getMap(QString signalSystemName, QString aspectMapName)
{
 Logger* log = new Logger("DefaultSignalAppearanceMap");

 if (log->isDebugEnabled()) log->debug("getMap signalSystem= \""+signalSystemName+"\", aspectMap= \""+aspectMapName+"\"");
 DefaultSignalAppearanceMap* map = maps->value("map:"+signalSystemName+":"+aspectMapName);
 if (map == NULL)
 {
   map = loadMap(signalSystemName, aspectMapName);
 }
 return map;
}

/*static*/ DefaultSignalAppearanceMap* DefaultSignalAppearanceMap::loadMap(QString signalSystemName, QString aspectMapName)
{
 Logger* log = new Logger("DefaultSignalAppearanceMap");
 DefaultSignalAppearanceMap* map =
        new DefaultSignalAppearanceMap("map:"+signalSystemName+":"+aspectMapName);
 maps->insert("map:"+signalSystemName+":"+aspectMapName, map);

 QFile* file = new QFile(FileUtil::getUserFilesPath()
                            +"resources"+QDir::separator()
                            +"signals"+QDir::separator()
                            +signalSystemName+QDir::separator()
                            +"appearance-"+aspectMapName+".xml");
 if(!file->exists())
 {
  file = new QFile(FileUtil::getProgramPath()+QString("xml")+QDir::separator()
                                +"signals"+QDir::separator()
                                +signalSystemName+QDir::separator()
                                +"appearance-"+aspectMapName+".xml");
  if (!file->exists())
  {
    log->error("appearance file doesn't exist: "+file->fileName());
            //throw new IllegalArgumentException("appearance file doesn't exist: "+file->fileName());
  }
 }
 XmlFile* xf = new XmlFile();
 QDomElement root;
 try
 {
  root = xf->rootFromFile(file);
  // get appearances
  //@SuppressWarnings("unchecked")
  QDomNodeList l = root.firstChildElement("appearances").elementsByTagName("appearance");

  // find all appearances, include them by aspect name,
  for (int i = 0; i < l.size(); i++)
  {
   QString name = l.at(i).toElement().firstChildElement("aspectname").text();
   if (log->isDebugEnabled()) log->debug("aspect name "+name);

   // add 'show' sub-elements as ints
   //@SuppressWarnings("unchecked")
   QDomNodeList c = l.at(i).toElement().elementsByTagName("show");

   QVector<int>* appearances =  new QVector<int>(c.size());
   for (int j = 0; j < c.size(); j++)
   {
    // note: includes setting name; redundant, but needed
    int ival;
    QString sval = c.at(j).toElement().text().toUpper();
    if (sval==("LUNAR")) ival = SignalHead::LUNAR;
    else if (sval==("GREEN")) ival = SignalHead::GREEN;
    else if (sval==("YELLOW")) ival = SignalHead::YELLOW;
    else if (sval==("RED")) ival = SignalHead::RED;
    else if (sval==("FLASHLUNAR")) ival = SignalHead::FLASHLUNAR;
    else if (sval==("FLASHGREEN")) ival = SignalHead::FLASHGREEN;
    else if (sval==("FLASHYELLOW")) ival = SignalHead::FLASHYELLOW;
    else if (sval==("FLASHRED")) ival = SignalHead::FLASHRED;
    else if (sval==("DARK")) ival = SignalHead::DARK;
    else throw new JDOMException("invalid content: "+sval);

    appearances->replace(j, ival);
   }
   map->addAspect(name, appearances);

   //QHash<String, String> images = new QHash<String, String>();

   //@SuppressWarnings("unchecked")
   QDomNodeList img = l.at(i).toElement().elementsByTagName("imagelink");
   loadImageMaps(img, name, map);

   // now add the rest of the attributes
   QHash<QString, QString> hm =  QHash<QString, QString>();

   //@SuppressWarnings("unchecked")
   QDomNodeList a = l.at(i).toElement().childNodes();

   for (int j = 0; j < a.size(); j++)
   {
    QString key = a.at(j).toElement().tagName();
    QString value = a.at(j).toElement().text();
    hm.insert(key, value);
   }

   map->aspectAttributeMap->insert(name, hm);
  }
  loadSpecificMap(signalSystemName, aspectMapName, map, root);
  loadAspectRelationMap(signalSystemName, aspectMapName, map, root);
 }
 catch (IOException e)
 {
  log->error("error reading file \""+file->fileName(), e);
  return NULL;
 }
 catch (JDOMException e)
 {
  log->error("error parsing file \""+file->fileName(), e);
  return NULL;
 }
 return map;
}

/*static*/ void DefaultSignalAppearanceMap::loadImageMaps(QDomNodeList img, QString name, DefaultSignalAppearanceMap* map)
{
 //Logger* log = new Logger("DefaultSignalAppearanceMap");
 QHash<QString, QString> images =  QHash<QString, QString>();
 for (int j = 0; j < img.size(); j++)
 {
  QString key = "default";
  if((img.at(j).toElement().attribute("type"))!="")
    key = img.at(j).toElement().attribute("type");
  QString value = img.at(j).toElement().text();
  images.insert(key, value);
 }
 map->aspectImageMap->insert(name, images);
}


/*static*/ void DefaultSignalAppearanceMap::loadSpecificMap(QString signalSystemName, QString aspectMapName, DefaultSignalAppearanceMap* SMmap, QDomElement root)
{
 Logger* log = new Logger("DefaultSignalAppearanceMap");
 if (log->isDebugEnabled()) log->debug("load specific signalSystem= \""+signalSystemName+"\", aspectMap= \""+aspectMapName+"\"");
 for (int i = 0; i<NUMSPECIFIC; i++)
 {
  loadSpecificAspect(signalSystemName, aspectMapName, i, SMmap, root);
 }
}

/*static*/ void DefaultSignalAppearanceMap::loadSpecificAspect(QString /*signalSystemName*/, QString /*aspectMapName*/, int aspectType, DefaultSignalAppearanceMap* SMmap, QDomElement root)
{
 Logger* log = new Logger("DefaultSignalAppearanceMap");

 QString child;
 switch (aspectType)
 {
 case HELD:  child = "held";
  break;
 case DANGER: child = "danger";
  break;
 case PERMISSIVE: child = "permissive";
  break;
 case DARK: child = "dark";
  break;
 default: child = "danger";
 }

 QString appearance;
 try {
        appearance = root.firstChildElement("specificappearances").firstChildElement(child).firstChildElement("aspect").text();
        SMmap->specificMaps->insert(aspectType, appearance);
    } catch (NullPointerException e){
        log->debug("appearance not configured");
        return;
    }

    try {
        //@SuppressWarnings("unchecked")
        QDomNodeList img = root.firstChildElement("specificappearances").firstChildElement(child).elementsByTagName("imagelink");
        QString name = "$"+child;
        if (img.size()==0){
           //We do not have any specific images created, therefore we use the
           //those associated with the aspect.
           QVector<QString> app = SMmap->getImageTypes(appearance);
           QHash<QString, QString> images =  QHash<QString, QString>();
           QString type = "";
           for (int i = 0; i<app.size(); i++){
                type = SMmap->getImageLink(appearance, app.at(i));
                images.insert(app.at(i), type);
           }
           //We will register the last aspect as a default.
           images.insert("default", type);
           SMmap->aspectImageMap->insert(name, images);
        } else {
            loadImageMaps(img, name, SMmap);
        }
    } catch (NullPointerException e){
        //Considered Normal if held aspect uses default signal appearance
    }
}

/*static*/ void DefaultSignalAppearanceMap::loadAspectRelationMap(QString signalSystemName, QString aspectMapName, DefaultSignalAppearanceMap* SMmap, QDomElement root)
{
 Logger* log = new Logger("DefaultSignalAppearanceMap");
 if (log->isDebugEnabled()) log->debug("load aspect relation map signalSystem= \""+signalSystemName+"\", aspectMap= \""+aspectMapName+"\"");

 try
 {
  // @SuppressWarnings("unchecked")
  QDomNodeList l = root.firstChildElement("aspectMappings").elementsByTagName("aspectMapping");
  for (int i = 0; i < l.size(); i++)
  {
   QString advanced = l.at(i).firstChildElement("advancedAspect").text();
   //@SuppressWarnings("unchecked")
   QDomNodeList o = l.at(i).toElement().elementsByTagName("ourAspect");
   QVector<QString> appearances =  QVector<QString>(o.size());
   for (int j = 0; j < o.size(); j++)
   {
    appearances.replace(j, o.at(j).toElement().text());
   }
   SMmap->aspectRelationshipMap->insert(advanced, appearances);
  }

 }
 catch (NullPointerException e)
 {
  log->debug("appearance not configured");
  return;
 }
}

/**
 * Get a property associated with a specific aspect
 */
/*public*/ QString DefaultSignalAppearanceMap::getProperty(QString aspect, QString key) {
    return aspectAttributeMap->value(aspect).value(key);
}

/*public*/ QString DefaultSignalAppearanceMap::getImageLink(QString aspect, QString type){
    if(type==NULL|| type==(""))
        type = "default";
    QString value;
    try {
        value = aspectImageMap->value(aspect).value(type);
        //if we don't return a valid image set, then we will use which ever set is loaded in the getProperty
        if(value==NULL){
            value = getProperty(aspect, "imagelink");
        }
    } catch (NullPointerException e){
        /* Can be considered normal for situations where a specific aspect
        has been asked for but it hasn't yet been loaded or configured */
        value = "";
    }
    return value;
}

/*public*/ QVector<QString> DefaultSignalAppearanceMap::getImageTypes(QString aspect)
{
 if(!checkAspect(aspect))
  return  QVector<QString>();
 QStringListIterator e( aspectImageMap->value(aspect).keys());
 QVector<QString> v =  QVector<QString>();
 while (e.hasNext())
 {
  v.append(e.next());
 }
 return v;
}

/*public*/ void DefaultSignalAppearanceMap::loadDefaults() {

    log->debug("start loadDefaults");

    QString ra;
    ra = tr("Stop");
    if (ra!=NULL)
    {
     QVector<int>* v = new QVector<int>();
     *v << SignalHead::RED;
     addAspect(ra, v);
    }
    else log->error("no default red aspect");

    ra = tr("Approach");
    if (ra!=NULL)
    {
     QVector<int>* v = new QVector<int>();
     *v << SignalHead::YELLOW;
     addAspect(ra, v);
    }
    else log->error("no default yellow aspect");

    ra = ("Clear");
    if (ra!=NULL)
    {
     QVector<int>* v = new QVector<int>();
     *v << SignalHead::GREEN;
     addAspect(ra, v);
    }
    else log->error("no default green aspect");
}

/*public*/ bool DefaultSignalAppearanceMap::checkAspect(QString aspect)
{
    if (aspect==NULL) return false;
    return table->contains(aspect);// != NULL;
}

/*public*/ void DefaultSignalAppearanceMap::addAspect(QString aspect, QVector<int>* appearances)
{
    if (log->isDebugEnabled()) log->debug("add aspect \""+aspect+"\" for "+QString::number(appearances->count())+" heads "
                                         +QString::number(appearances->at(0)));
    table->insert(aspect, appearances);
}

/*public*/ QStringList DefaultSignalAppearanceMap::getAspects()
{
 return table->keys();
}

/*public*/ QString DefaultSignalAppearanceMap::getSpecificAppearance(int appearance)
{
 if (specificMaps->contains(appearance))
 {
  return specificMaps->value(appearance);
 }
 return "";
}

/**
* Returns a list of postential aspects that we could set the signalmast to
* given the state of the advanced signal mast.
*/
/*public*/ QVector<QString> DefaultSignalAppearanceMap::getValidAspectsForAdvancedAspect(QString advancedAspect){
    if (aspectRelationshipMap==NULL){
        log->error("aspect relationships have not been defined or loaded");
        throw new IllegalArgumentException("aspect relationships have not been defined or loaded");
    }
    if (advancedAspect==NULL){
        QVector<QString> danger =  QVector<QString>(1);
        danger.replace(0, getSpecificAppearance(DANGER));
        return danger;
    }
    if(aspectRelationshipMap->contains(advancedAspect)){
        //String[] validAspects = aspectRelationMap.get(advancedAspect);
        return aspectRelationshipMap->value(advancedAspect);
    }
    return QVector<QString>();
}


/*public*/ SignalSystem* DefaultSignalAppearanceMap::getSignalSystem()
{
    return systemDefn;
}

/*public*/ void DefaultSignalAppearanceMap::setSignalSystem(SignalSystem* t) { systemDefn = t; }

/*public*/ int DefaultSignalAppearanceMap::getState() {
    throw new /*NoSuchMethodError*/ Exception();
}

/*public*/ void DefaultSignalAppearanceMap::setState(int /*s*/) {
    throw new /*NoSuchMethodError*/Exception();
}

/*public*/ QVector<int>* DefaultSignalAppearanceMap::getAspectSettings(QString aspect){
    return table->value(aspect);
}
