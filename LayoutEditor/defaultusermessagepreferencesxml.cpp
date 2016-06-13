#include "defaultusermessagepreferencesxml.h"
#include "userpreferencesmanager.h"
#include "defaultusermessagepreferences.h"
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
 UserPreferencesManager* p = (UserPreferencesManager*) o;

 QDomElement messages = doc.createElement("UserMessagePreferences");
 setStoreElementClass(messages);

 QStringList preferenceList = ((DefaultUserMessagePreferences*)p)->getSimplePreferenceStateList();
 for (int i = 0; i < preferenceList.size(); i++)
 {
  QDomElement pref = doc.createElement("setting");
  pref.appendChild(doc.createTextNode( preferenceList.at(i)));
  messages.appendChild(pref);
 }

 int comboBoxSize = p->getComboBoxSelectionSize();
 if (comboBoxSize >0)
 {
  QDomElement comboList = doc.createElement("comboBoxLastValue");
  for(int i = 0; i<comboBoxSize; i++)
  {
   //No point in storing the last entered/selected value if it is blank
   if ((p->getComboBoxLastSelection(i)!=NULL)&&(p->getComboBoxLastSelection(i)!=("")))
   {
    QDomElement combo = doc.createElement("comboBox");
    combo.setAttribute("name", p->getComboBoxName(i));
    combo.setAttribute("lastSelected", p->getComboBoxLastSelection(i));
    comboList.appendChild(combo);
   }
  }
  messages.appendChild(comboList);
 }
 QStringList preferenceClassList = p->getPreferencesClasses();
 for (int k = 0; k<preferenceClassList.size(); k++)
 {
  QString strClass = preferenceClassList.at(k);
  QStringList multipleList = p->getMultipleChoiceList(strClass);
  QDomElement classElement = doc.createElement("classPreferences");
  classElement.setAttribute("class", strClass);
  //This bit deals with the multiple choice
  bool store = false;
  QDomElement multiOption = doc.createElement("multipleChoice");
  for (int i=0; i<multipleList.size(); i++)
  {
   QString itemName = p->getChoiceName(strClass, i);
   if (p->getMultipleChoiceDefaultOption(strClass, itemName)!=p->getMultipleChoiceOption(strClass, itemName))
   {
    //Only save if we are not at the default value.
    QDomElement multiOptionItem = doc.createElement("option");
    store = true;
    multiOptionItem.setAttribute("item", itemName);
    multiOptionItem.setAttribute("value", p->getMultipleChoiceOption(strClass, itemName));
    multiOption.appendChild(multiOptionItem);
   }
  }
  if (store)
  {
   classElement.appendChild(multiOption);
  }

  bool listStore=false;
  QStringList singleList = p->getPreferenceList(strClass);
  if (singleList.size()!=0)
  {
   QDomElement singleOption = doc.createElement("reminderPrompts");
   for (int i = 0; i<singleList.size(); i++)
   {
    QString itemName = p->getPreferenceItemName(strClass, i);
    if(p->getPreferenceState(strClass, itemName))
    {
     QDomElement pref = doc.createElement("reminder");
     pref.appendChild(doc.createTextNode(singleList.at(i)));
     singleOption.appendChild(pref);
     listStore = true;
    }
   }
   if (listStore)
     classElement.appendChild(singleOption);
  }

  //This bit deals with simple hiding of messages
  if ((store) || (listStore))
   messages.appendChild(classElement);
 }

 QStringList windowList = p->getWindowList();
 if (/*windowList != NULL &&*/ windowList.size() != 0)
 {
  foreach(QString strClass, windowList)
  {
   QDomElement windowElement = doc.createElement("windowDetails");
   windowElement.setAttribute("class", strClass);
   bool set = false;
   if(p->getSaveWindowLocation(strClass))
   {
    try {
    double x = p->getWindowLocation(strClass).x();
    double y = p->getWindowLocation(strClass).y();
    QDomElement loc = doc.createElement("locX");
    loc.appendChild(doc.createTextNode(QString::number(x)));
    windowElement.appendChild(loc);
    loc = doc.createElement("locY");
    windowElement.appendChild(loc);
    loc.appendChild(doc.createTextNode(QString::number(y)));
    set=true;
    } catch (NullPointerException ex){
        //Considered normal if the window hasn't been closed or all of the information hasn't been set
    }
   }
   if(p->getSaveWindowSize(strClass))
   {
    try
    {
     double width=p->getWindowSize(strClass).width();
     double height=p->getWindowSize(strClass).height();
     //We do not want to save the width or height if it is set to zero!
     if (!(width==0.0 && height==0.0))
     {
      QDomElement size = doc.createElement("width");
      size.appendChild(doc.createTextNode(QString::number(width)));
      windowElement.appendChild(size);
      size = doc.createElement("height");
      size.appendChild(doc.createTextNode(QString::number(height)));
      windowElement.appendChild(size);
      set=true;
     }
    } catch (NullPointerException ex){
     //Considered normal if the window hasn't been closed
    }
   }
   QSet<QString> s = p->getPropertyKeys(strClass);
   if (/*s != NULL &&*/ s.size() != 0)
   {
    QDomElement ret = doc.createElement("properties");
    windowElement.appendChild(ret);
    foreach (QVariant key, s)
    {
     QVariant value = p->getProperty(strClass, key);
     QDomElement prop = doc.createElement("property");
     ret.appendChild(prop);
     QDomElement e;
     prop.appendChild(e = doc.createElement("key"));
     QString s_class;
     //e.setAttribute("class", key.getClass().getName());
     if(key.toString() == "QString")
      s_class = "java.lang.String";
     e.setAttribute("class", s_class);
     e.appendChild(doc.createTextNode(key.toString()));
     if (value != QVariant())
     {
      prop.appendChild(e = doc.createElement("value"));
      //e.setAttribute("class", value.getClass().getName())
      e.setAttribute("value", s_class);
      e.appendChild(doc.createTextNode(value.toString()));
     }
    }
    set=true;
   }
   if (set)
    messages.appendChild(windowElement);
  }
 }

 if(p->getTablesList().size()!=0)
 {
  QDomElement tablesElement = doc.createElement("tableDetails");
  foreach(QString table, p->getTablesList())
  {
   QDomElement tableElement = doc.createElement("table");
   tableElement.setAttribute("name", table);
   foreach(QString column, p->getTablesColumnList(table))
   {
    QDomElement columnElement = doc.createElement("column");
    columnElement.setAttribute("name", column);
    if(p->getTableColumnOrder(table, column)!=-1)
    {
     columnElement.appendChild(doc.createElement("order").appendChild(doc.createTextNode(QString::number(p->getTableColumnOrder(table, column)))));
    }
    if(p->getTableColumnWidth(table, column)!=-1)
    {
     columnElement.appendChild(doc.createElement("width").appendChild(doc.createTextNode(QString::number(p->getTableColumnWidth(table, column)))));
    }
    if(p->getTableColumnSort(table, column)!=0)
    {
     columnElement.appendChild(doc.createElement("sort").appendChild(doc.createTextNode(QString::number(p->getTableColumnSort(table, column)))));
    }
    if(p->getTableColumnHidden(table, column))
    {
     columnElement.appendChild(doc.createElement("hidden").appendChild(doc.createTextNode("yes")));
    }
    tableElement.appendChild(columnElement);
   }
   tablesElement.appendChild(tableElement);
  }
  messages.appendChild(tablesElement);
 }
 return messages;
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
/*public*/ bool DefaultUserMessagePreferencesXml::load(QDomElement messages) throw (Exception)
{
 // ensure the master object exists
 UserPreferencesManager* p = (UserPreferencesManager*) InstanceManager::getDefault("UserPreferencesManager");

 if(p == NULL)
  p = new DefaultUserMessagePreferences();

 p->setLoading();

 QDomNodeList settingList = messages.elementsByTagName("setting");

 for (int i = 0; i < settingList.size(); i++)
 {
  QString name = settingList.at(i).toElement().text();
  p->setSimplePreferenceState(name, true);
 }

 QDomNodeList comboList = messages.elementsByTagName("comboBoxLastValue");

 for (int i = 0; i < comboList.size(); i++)
 {
  QDomNodeList comboItem = comboList.at(i).toElement().elementsByTagName("comboBox");
  for (int x = 0; x<comboItem.size(); x++)
  {
   QString combo = comboItem.at(x).toElement().attribute("name");
   QString setting = comboItem.at(x).toElement().attribute("lastSelected");
   p->addComboBoxLastSelection(combo, setting);
  }
 }

 QDomNodeList classList = messages.elementsByTagName("classPreferences");
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

 QDomNodeList windowList = messages.elementsByTagName("windowDetails");
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

 QDomNodeList tablesList = messages.elementsByTagName("tableDetails");
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

    p->setTableColumnPreferences(strTableName, strColumnName, order, width, sort, hidden);
   }
  }

 }
 p->finishLoading();
 return true;
}
#endif
