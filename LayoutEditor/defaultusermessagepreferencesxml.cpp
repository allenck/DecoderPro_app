#include "defaultusermessagepreferencesxml.h"
#include "userpreferencesmanager.h"
//#include "defaultusermessagepreferences.h"
#include "instancemanager.h"

DefaultUserMessagePreferencesXml::DefaultUserMessagePreferencesXml(QObject *parent) :
    AbstractXmlAdapter(parent)
{
 log = new Logger("DefaultUserMessagePreferencesXml");
}
// /*public*/ class DefaultUserMessagePreferencesXml extends jmri.configurexml.AbstractXmlAdapter{

//    /*public*/ DefaultUserMessagePreferencesXml() {
//        super();
//    }
#if 1
 /**
 * Default implementation for storing the contents of a
 * User Messages Preferences
 * @param o Object to store, but not really used, because
 *              info to be stored comes from the DefaultUserMessagePreferences
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement DefaultUserMessagePreferencesXml::store(QObject* o)
{
 // nothing to do, since this class exists only to load older preferences if they exist
         return QDomElement();
}

/*public*/ void DefaultUserMessagePreferencesXml::setStoreElementClass(QDomElement messages) {
    messages.setAttribute("class","jmri.managers.configurexml.DefaultUserMessagePreferencesXml");
}

/*public*/ void DefaultUserMessagePreferencesXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception){
    log->error("Invalid method called");
}

/**
 * Create a MemoryManager object of the correct class, then
 * register and fill it.
 * @param messages Top level QDomElement to unpack.
 * @return true if successful
 */
//@SuppressWarnings("unchecked")
/*public*/ bool DefaultUserMessagePreferencesXml::load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException)
{
 // ensure the master object exists
 UserPreferencesManager* p = (UserPreferencesManager*) InstanceManager::getDefault("UserPreferencesManager");

 if(p == NULL)
  p = static_cast<UserPreferencesManager*>(InstanceManager::getDefault("UserPreferencesManager"));

 p->setLoading();

 QDomNodeList settingList = shared.elementsByTagName("setting");

 for (int i = 0; i < settingList.size(); i++)
 {
  QString name = settingList.at(i).toElement().text();
  p->setSimplePreferenceState(name, true);
 }

 QDomNodeList comboList = shared.elementsByTagName("comboBoxLastValue");

 for (int i = 0; i < comboList.size(); i++)
 {
  QDomNodeList comboItem = comboList.at(i).toElement().elementsByTagName("comboBox");
  for (int x = 0; x<comboItem.size(); x++)
  {
   QString combo = comboItem.at(x).toElement().attribute("name");
   QString setting = comboItem.at(x).toElement().attribute("lastSelected");
   p->setComboBoxLastSelection(combo, setting);
  }
 }

 QDomNodeList classList = shared.elementsByTagName("classPreferences");
 for (int k = 0; k < classList.size(); k++)
 {
  QDomNodeList multipleList = classList.at(k).toElement().elementsByTagName("multipleChoice");
  QString strClass = classList.at(k).toElement().attribute("class");
  for (int i = 0; i < multipleList.size(); i++)
  {
   QDomNodeList multiItem = multipleList.at(i).toElement().elementsByTagName("option");
   for (int x = 0; x<multiItem.size(); x++)
   {
    QString item = multiItem.at(x).toElement().attribute("item");
    int value = 0x00;
    try {
     value = multiItem.at(x).toElement().attribute("value").toInt();
    } catch (DataConversionException e)
    {
     log->error("failed to convert positional attribute");
    }
    p->setMultipleChoiceOption(strClass, item, value);
   }
  }

  QDomNodeList preferenceList = classList.at(k).toElement().elementsByTagName("reminderPrompts");
  for (int i = 0; i<preferenceList.size(); i++)
  {
   QDomNodeList reminderBoxes = preferenceList.at(i).toElement().elementsByTagName("reminder");
   for (int j = 0; j < reminderBoxes.size(); j++)
   {
    QString name = reminderBoxes.at(j).toElement().text();
    p->setPreferenceState(strClass, name, true);
   }
  }
 }

 QDomNodeList windowList = shared.elementsByTagName("windowDetails");
 for (int k = 0; k < windowList.size(); k++)
 {
  QString strClass = windowList.at(k).toElement().attribute("class");
  QDomNodeList locListX = windowList.at(k).toElement().elementsByTagName("locX");
  double x=0.0;
  for (int i = 0; i < locListX.size(); i++)
  {
   try {
    x = locListX.at(i).toElement().text().toDouble();
   } catch ( NumberFormatException e)
   {
    log->error("failed to convert positional attribute");
   }
  }
  QDomNodeList locListY = windowList.at(k).toElement().elementsByTagName("locY");
  double y=0.0;
  for (int i = 0; i < locListY.size(); i++)
  {
   try {
    y = locListY.at(i).toElement().text().toDouble();
   } catch ( NumberFormatException e)
   {
    log->error("failed to convert positional attribute");
   }
  }
  p->setWindowLocation(strClass,  QPoint((int)x, (int)y));


  QDomNodeList sizeWidth = windowList.at(k).toElement().elementsByTagName("width");
  double width=0.0;
  for (int i = 0; i < sizeWidth.size(); i++)
  {
   try {
    width = sizeWidth.at(i).toElement().text().toDouble();
   } catch ( NumberFormatException e) {
    log->error("failed to convert positional attribute");
   }
  }
  QDomNodeList heightList = windowList.at(k).toElement().elementsByTagName("height");
  double height=0.0;
  for (int i = 0; i < heightList.size(); i++)
  {
   try {
    height = heightList.at(i).toElement().text().toDouble();
   } catch ( NumberFormatException e)
   {
    log->error("failed to convert positional attribute");
   }
  }
  p->setWindowSize(strClass,  QSize((int)width, (int)height));

  QDomElement prop = windowList.at(k).toElement().firstChildElement("properties");
  if (!prop .isNull())
  {
   //foreach (QDomNode next, prop.childNodes("property"))
   QDomNodeList propertyList = prop.elementsByTagName("property");
   for(int i = 0; i <propertyList.count(); i++)
   {
    QDomElement e = propertyList.at(i).toElement();
#if 0
                try {
                    Class<?> cl;
                    Constructor<?> ctor;
                    // create key object
                    cl = Class.forName(e.getChild("key").attributeValue("class"));
                    ctor = cl.getConstructor(new Class<?>[] {String.class});
                    Object key = ctor.newInstance(new Object[] {e.getChild("key").text()});
                    Object value = NULL;
                    if (e.getChild("value") != NULL) {
                        cl = Class.forName(e.getChild("value").attributeValue("class"));
                        ctor = cl.getConstructor(new Class<?>[] {String.class});
                        value = ctor.newInstance(new Object[] {e.getChild("value").text()});
                    }

                    // store
                    p.setProperty(strClass, key, value);
                } catch (Exception ex) {
                    log.error("Error loading properties", ex);
                }
#else
   QString fullClassName = e.firstChildElement("key").attribute("class");
   QString keyText = e.firstChildElement("key").text();
   QString valueText;
   QString className;
   QString valueName;
   if(fullClassName == "java.lang.String")
       className = "QString";
   else
       className = fullClassName.mid(fullClassName.lastIndexOf(".")+1);
   int typeId = QMetaType::type(className.toLocal8Bit());
   if(typeId > 0)
   {
    void* ptr;
#if QT_VERSION < 0x050000
    ptr = QMetaType::construct(typeId);
#else
    ptr = QMetaType::create(typeId);
#endif
    if(ptr!= NULL)
    {
     QString fullValueName = e.firstChildElement("value").attribute("class");
     valueText = e.firstChildElement("value").text();
     if(fullValueName == "java.lang.String" || fullValueName == "")
         valueName = "QString";
     else
         valueName = fullValueName.mid(fullClassName.lastIndexOf(".")+1);
     int typeId = QMetaType::type(valueName.toLocal8Bit());
     if(typeId > 0)
     {
      void* ptr;
  #if QT_VERSION < 0x050000
      ptr = QMetaType::construct(typeId);
  #else
      ptr = QMetaType::create(typeId);
  #endif
      if(ptr != NULL)
      {
       p->setProperty(strClass, keyText, valueText);
      }
     }
    }
    else
    {
     log->error("DefaultUserMessagePreferencesXml: Unable to create class " + className);
    }
   }
   else
   {
    log->error("DefaultUserMessagePreferencesXml: Error loading properties for class " + fullClassName);
   }
#endif
  }
 }
}

 QDomNodeList tablesList = shared.elementsByTagName("tableDetails");
 //foreach(QDomNode tables, tablesList)
 for(int i = 0; i < tablesList.count(); i++)
 {
  QDomNode tables = tablesList.at(i);
  QDomNodeList tableList = tables.toElement().elementsByTagName("table");
  //foreach(QDomNode table, tableList)
  for( int k =0; k < tableList.count(); k++)
  {
   QDomNode table = tableList.at(k);
   QDomNodeList columnList = table.toElement().elementsByTagName("column");
   QString strTableName = table.toElement().attribute("name");
   //foreach(QDomNode column, columnList)
   for(int l = 0; l < columnList.count(); l++)
   {
    QDomNode column = columnList.at(l);
    QString strColumnName = column.toElement().attribute("name");
    int order = -1;
    int width = -1;
    int sort = 0;
    bool hidden = false;
    if(!column.toElement().firstChildElement("order").isNull())
    {
     order = column.toElement().firstChildElement("order").text().toInt();
    }
    if(!column.toElement().firstChildElement("width").isNull())
    {
     width = column.toElement().firstChildElement("width").text().toInt();
    }
    if(!column.toElement().firstChildElement("sort").isNull())
    {
     sort = column.toElement().firstChildElement("sort").text().toInt();
    }
    if(!column.toElement().firstChildElement("hidden").isNull() && column.toElement().firstChildElement("hidden").text()== ("yes"))
    {
     hidden=true;
    }

//    p->setTableColumnPreferences(strTableName, strColumnName, order, width, sort, hidden);
   }
  }

 }
 p->finishLoading();
 return true;
}
#endif
