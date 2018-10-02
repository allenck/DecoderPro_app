#include "jmenuutil.h"
#include "windowinterface.h"
#include "logger.h"
#include <QMenu>
#include <QButtonGroup>
#include "action.h"
#include <QActionGroup>
#include "fileutil.h"
#include "file.h"
#include <QSignalMapper>

//JMenuUtil::JMenuUtil(QObject *parent) :
//  GuiUtilBase(parent)
//{
//}
/**
 * Common utility methods for working with JMenus.
 * <P>
 * Chief among these is the loadMenu method, for creating a set of menus from an
 * XML definition
 *
 * @author Bob Jacobsen Copyright 2003, 2010
 * @version $Revision: 28746 $
 * @since 2.9.4
 */
// /*public*/  class JMenuUtil extends GuiUtilBase {

/*static*/ /*public*/  QList<QMenu*> JMenuUtil::loadMenu(QString path, WindowInterface* wi, QObject* context)
{
 File file(path);
 if(!file.isAbsolute())
  path = FileUtil::getUserFilesPath() + path;
 XmlFile* xmlFile = new XmlFile();
 QDomElement root = xmlFile->rootFromName(path);

 //QDomNodeList nodes = root.elementsByTagName("node");
 QDomNodeList nodes = root.childNodes();

 int n = nodes.size();
 QVector<QMenu*> retval =  QVector<QMenu*>(n);

 QList<int> mnemonicList =  QList<int>();
 for (int i = 0; i <  nodes.size(); i++)
 {
  QDomElement child = nodes.at(i).toElement();
  if(child == QDomElement()) continue;
  QMenu* menuItem = jMenuFromElement( child, wi, context);
  retval.replace(i, menuItem);
  if (( !child.firstChildElement("mnemonic").isNull()) && menuItem != NULL)
  {
   int mnemonic = convertStringToKeyEvent( child.firstChildElement("mnemonic").text());
   if (mnemonicList.contains(mnemonic))
   {
    Logger::error("Menu item '" + menuItem->title() + "' Mnemonic '" + child.firstChildElement("mnemonic").text() + "' has already been assigned");
   }
   else
   {
    //menuItem->setMnemonic(mnemonic);
//    menuItem->setUserData(mnemonic);
    mnemonicList.append(mnemonic);
   }
  }
 }
 return retval.toList();
}

/*static*/ QMenu* JMenuUtil::jMenuFromElement(QDomElement main, WindowInterface* wi, QObject* context)
{
 bool addSep = false;
 QString name = "<none>";
 Logger log("JMenuUtil");
 if (main.isNull())
 {
  log.warn("Menu from element called without an element");
  return new QMenu(name);
 }

 //name = LocaleSelector.getAttribute(main, "name");
 name = GuiUtilBase::getLocaleAttribute(main, "name");
 QMenu* menu = new QMenu(name);
 QList<int> mnemonicList = QList<int>();
 //QDomNodeList nodes = main.elementsByTagName("node");
 QDomNodeList nodes = main.childNodes();
 for(int i = 0; i < nodes.size(); i++)
 {
  QObject* menuItem = NULL;
  QDomElement child = nodes.at(i).toElement();
  if(child.tagName()!= "node")
   continue;
  if (child.elementsByTagName("node").size() == 0)
  {  // leaf
   //QAction* menuItem = NULL;
   if ((child.text().trimmed())==("separator"))
   {
    addSep = true;
   }
   else
   {
    if ((/*!SystemType.isMacOSX()*/
//                        && UIManager.getLookAndFeel().isNativeLookAndFeel() &&
         (!(child.firstChildElement("adapter").isNull()
        && child.firstChildElement("adapter").text()==("apps.gui3.TabbedPreferencesAction"))
        || !(child.firstChildElement("current").isNull()
        && child.firstChildElement("current").text()==("quit")))))
    {
     if (addSep)
     {
      menu->addSeparator();
      addSep = false;
     }
     QString leafName = child.attribute("name");
     Action* act = actionFromNode(child, wi, context);
     if(act !=NULL)
     {
      log.debug(tr("create action item '%1' in '%2' menu").arg(act->text()).arg(name));
      menu->addAction((QAction*)(menuItem = (QObject*)act));
      if(!child.firstChildElement("type").isNull())
      {
       if(child.firstChildElement("type").text() == "checkbox")
        act->setCheckable(true);
      }
      if (!child.firstChildElement("current").isNull())
      {
       //setMenuItemInterAction(context, child.firstChildElement("current").text(), menuItem);
       QString current = act->data().toString();
      ((RosterFrame*)wi)->currentMapper->setMapping(act,act);
      connect(act, SIGNAL(triggered(bool)), ((RosterFrame*)wi)->currentMapper, SLOT(map()));
      }
     }
    }
   }
  }
  else
  {
   //QMenu* menuItem;
   if (addSep)
   {
    menu->addSeparator();
    addSep = false;
   }
   if (!child.firstChildElement("group").isNull() && child.firstChildElement("group").text()==("yes"))
   {
    //A separate method is required for creating radio button groups
    menu->addMenu(createMenuGroupFromElement(child, wi, context));
   }
   else
   {
    menu->addMenu((QMenu*)(menuItem = (QObject*)jMenuFromElement(child, wi, context))); // not leaf
   }
  }

  if (menuItem != NULL && !child.firstChildElement("current").isNull() )
  {
   setMenuItemInterAction(context, child.firstChildElement("current").text(), (QAction*)menuItem);
  }
  if (menuItem != NULL && !child.firstChildElement("mnemonic").isNull())
  {
   int mnemonic = convertStringToKeyEvent(child.firstChildElement("mnemonic").text());
   if (mnemonicList.contains(mnemonic))
   {
    log.error("Menu Item '" + ((QAction*)menuItem)->text() + "' Mnemonic '" + child.firstChildElement("mnemonic").text() + "' has already been assigned");
   }
   else
   {
    if(qobject_cast<QAction*>(menuItem)!= NULL)
     ((QAction*)menuItem)->setData(mnemonic);
    mnemonicList.append(mnemonic);
   }
  }
 }
 Q_ASSERT(menu != NULL);
 return menu;
}

/*static*/ QMenu* JMenuUtil::createMenuGroupFromElement(QDomElement main, WindowInterface* wi, QObject* context)
{
 Logger log("JMenuUtil");
 QString name = "<none>";
 if (main.isNull())
 {
  log.warn("Menu from element called without an element");
  return new QMenu(name);
 }
 name = /*LocaleSelector.getAttribute(main, "name");*/ GuiUtilBase::getLocaleAttribute(main,"name");
 //Next statement left in if the xml file hasn't been converted
 if ((name == NULL) || (name==("")))
 {
  if (!main.firstChildElement("name").isNull())
  {
   name = main.firstChildElement("name").text();
  }
 }
 QMenu* menu = new QMenu(name);
 QActionGroup* group = new QActionGroup(wi);
 QDomNodeList nodes = main.elementsByTagName("node");
 for( int i = 0; i < nodes.count(); i++)
 {
  QDomElement elem = nodes.at(i).toElement();
  Action* act = actionFromNode(elem, wi, context);
  QAction* menuItem = new QAction(act);
  menuItem->setCheckable(true);
  group->addAction(menuItem);
  menu->addAction(menuItem);
  if(!elem.firstChildElement("type").isNull())
  {
   if(elem.firstChildElement("type").text() == "checkbox")
    menuItem->setCheckable(true);
  }
  if (!elem.firstChildElement("current").isNull())
  {
   setMenuItemInterAction(context, elem.firstChildElement("current").text(), menuItem);
  ((RosterFrame*)wi)->currentMapper->setMapping(act,act);
  connect(act, SIGNAL(triggered(bool)), ((RosterFrame*)wi)->currentMapper, SLOT(map()));
  }
 }

 return menu;
}

/*static*/ void JMenuUtil::setMenuItemInterAction(QObject* /*context*/, /*final*/ QString /*ref*/, /*final*/ QAction* /*menuItem*/)
{
#if 0 // TODO:
    Method* methodListener = NULL;
    try {
     methodListener = context.getClass().getMethod("addPropertyChangeListener", "PropertyChangeListener");
    } catch (java.lang.NullPointerException e) {
        log.error("Null object passed");
        return;
    } catch (SecurityException e) {
        log.error("security exception unable to find remoteCalls for " + context.getClass().getName());
        return;
    } catch (NoSuchMethodException e) {
        log.error("No such method remoteCalls for " + context.getClass().getName());
        return;
    }
    if (methodListener != NULL) {
        try {
            methodListener.invoke(context, new PropertyChangeListener() {
                /*public*/  void propertyChange(java.beans.PropertyChangeEvent e) {
                    if (e.getPropertyName()==(ref)) {
                        String method = (String) e.getOldValue();
                        if (method==("setSelected")) {
                            menuItem.setSelected(true);
                        } else if (method==("setEnabled")) {
                            menuItem.setEnabled((Boolean) e.getNewValue());
                        }
                    }
                }
            });
        } catch (IllegalArgumentException ex) {
            System.out.println("IllegalArgument " + ex);
        } catch (IllegalAccessException ex) {
            System.out.println("IllegalAccess " + ex);
        } catch (java.lang.reflect.InvocationTargetException ex) {
            System.out.println("InvocationTarget " + ref + " " + ex.getCause());
        } catch (java.lang.NullPointerException ex) {
            System.out.println("NPE " + context.getClass().getName() + " " + ex.toString());
        }
    }
#endif
}

/*static*/ int JMenuUtil::convertStringToKeyEvent(QString st)
{
 char a = (st.toLower().toLocal8Bit()).at(0);
 int kcode = a - 32;
 return kcode;
}
