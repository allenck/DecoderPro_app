#include "guiutilbase.h"
#include "xmlfile.h"
#include "action.h"
#include "logger.h"
#include "fileutil.h"
#include "imageicon.h"
#include <QIcon>
#include "jmrinamedpaneaction.h"
#include "helputil.h"

GuiUtilBase::GuiUtilBase(QObject *parent) :
  QObject(parent)
{
}
/**
 * Common utility methods for working with GUI items
 *
 * @author Bob Jacobsen Copyright 2010
 * @version $Revision: 28746 $
 */
///*public*/  class GuiUtilBase {

/*static*/ Action* GuiUtilBase::actionFromNode(QDomElement child, WindowInterface* wi, QObject* context)
{
 Logger log("Action");
 QString name = NULL;
 QIcon* icon = NULL;

 QHash<QString, QString> parameters =  QHash<QString, QString>();
 if (child.isNull())
 {
  log.warn("Action from node called without child");
  return createEmptyMenuItem(NULL, "<none>");
 }
 name = child.attribute("name");
 name = /*LocaleSelector::getAttribute(child, "name")*/ GuiUtilBase::getLocaleAttribute(child, "name");

 if (!child.firstChildElement("icon").isNull())
 {
  //icon = new ImageIcon(FileUtil::findURL(child.firstChildElement("icon").text()));
  icon = new QIcon(FileUtil::findURL(child.firstChildElement("icon").text()).toString());
 }
 //This bit does not size very well, but it works for now.
 if (!child.firstChildElement("option").isNull())
 {
  QDomNodeList options = child.elementsByTagName("option");
  for(int i= 0; i < options.size(); i++)
  {
   QDomElement item = options.at(i).toElement();
   QString setting = (item).attribute("setting");
   QString setMethod = ( item).text();
   parameters.insert(setMethod, setting);
  }
 }

 if (!child.firstChildElement("adapter").isNull())
 {
  QString classname = child.firstChildElement("adapter").text();
  QString cname = classname.mid(classname.lastIndexOf(".")+1);
  int typeId = QMetaType::type(cname.toLocal8Bit());
  JmriAbstractAction* a = NULL;
  QStringList methods;
  int constructorCount = 0;
  int propertyCount = 0;
  QByteArray ba;
  QStringList properties;
  QStringList constructors;
  QString signature;
  int constructorIndex;
  if(typeId > 0)
  {
#if 0
         //Class<?> c = Class.forName(classname);
         for (java.lang.reflect.Constructor<?> ct : c.getConstructors()) {
             // look for one with right arguments
             if (icon == NULL) {
                 Class<?>[] parms = ct.getParameterTypes();
                 if (parms.length != 2) {
                     continue;
                 }
                 if (parms[0] != String.class) {
                     continue;
                 }
                 if (parms[1] != WindowInterface.class) {
                     continue;
                 }
                 // found it!
                 a = (JmriAbstractAction) ct.newInstance(new Object[]{name, wi});
                 a.setName(name);
                 a.setContext(context);
                 setParameters(a, parameters);
                 return a;
             } else {
                 Class<?>[] parms = ct.getParameterTypes();
                 if (parms.length != 3) {
                     continue;
                 }
                 if (parms[0] != String.class) {
                     continue;
                 }
                 if (parms[1] != Icon.class) {
                     continue;
                 }
                 if (parms[2] != WindowInterface.class) {
                     continue;
                 }
                 // found it!
                 a = (JmriAbstractAction) ct.newInstance(new Object[]{name, icon, wi});
                 a.setName(name);
                 a.setContext(context);
                 setParameters(a, parameters);
                 return a;
             }
#else

#if QT_VERSION < 0x050000
   a = (JmriAbstractAction*)QMetaType::construct(typeId);
#else
   a = (JmriAbstractAction*)QMetaType::create(typeId);
#endif
   a->setName(name);
   a->setContext(context);
   a->setParent((QObject*)wi);

   const QMetaObject* metaObject = a->metaObject();
   constructorCount = metaObject->constructorCount();
   for(int i = metaObject->methodOffset(); i < metaObject->constructorCount(); ++i)
   {
#if QT_VERSION < 0x050000
    constructors << QString::fromLatin1(metaObject->method(i).signature());
#else
    constructors << QString::fromLatin1(metaObject->method(i).methodSignature());
#endif
   }
   if(icon == NULL)
    signature = cname+"(QString,WindowInterface*)";
   else
    signature = cname+"(QString,QIcon,WindowInterface*)";
   constructorIndex = metaObject->indexOfConstructor(signature.toLatin1());

   for(int i = metaObject->methodOffset(); i < metaObject->methodCount(); ++i)
   {
#if QT_VERSION < 0x050200
    methods << QString::fromLatin1(metaObject->method(i).signature());
#else
    methods << QString::fromLatin1(metaObject->method(i).methodSignature());
#endif
   }
   if(methods.count() == 0)
    log.debug(tr("class '%1' has no methods").arg(cname));
   if(constructorIndex < 0)
   {
    if(methods.contains("setParameter(QString,QString)"))
     setParameters(a, parameters);
   }
   else
   {
    if(icon== NULL)
      a = (JmriAbstractAction*)metaObject->newInstance(Q_ARG(QString, name), Q_ARG(WindowInterface*, wi));
    else
     a = (JmriAbstractAction*)metaObject->newInstance(Q_ARG(QString, name), Q_ARG(QIcon*, icon),Q_ARG(WindowInterface*, wi));
    setParameters(a, parameters);
   }

   propertyCount = metaObject->propertyCount();
   for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
    properties << QString::fromLatin1(metaObject->property(i).name());

//   if(methods.contains("actionPerformed()"))
//   {
//    connect(a,SIGNAL(triggered()), a, SLOT(actionPerformed()));
//   }
#endif
  }
  else
  {
   log.warn("Did not find suitable ctor for " + classname + (icon != NULL ? " with" : " without") + " icon");
   return createEmptyMenuItem(icon, name);
  }
  if(a == NULL)
  {
   log.warn("failed to load GUI adapter class: " + classname /*+ " due to: " + e*/);
   return createEmptyMenuItem(icon, name);
  }
  else
  {
   return a;
  }
 }
 else if (!child.firstChildElement("panel").isNull())
 {
  try
  {
   JmriNamedPaneAction* act;
   if (icon == NULL)
   {
    act = new JmriNamedPaneAction(name, wi, child.firstChildElement("panel").text());
   }
   else
   {
    act = new JmriNamedPaneAction(name, *icon, wi, child.firstChildElement("panel").text());
   }
   act->setContext(context);
   setParameters(act, parameters);
   return (Action*)act;
  }
  catch (Exception ex)
  {
   log.warn("could not load toolbar adapter class: " + child.firstChildElement("panel").text()
              + " due to " + ex.getMessage());
   return createEmptyMenuItem(icon, name);
  }
 }
 else if (!child.firstChildElement("help").isNull())
 {
  QString reference = child.firstChildElement("help").text();
  return (Action*)HelpUtil::getHelpAction(name, *icon, reference);
 }
 else if (!child.firstChildElement("current").isNull())
 {
  QStringList method;
  method << child.firstChildElement("current").text();
  return createActionInCallingWindow(context, method, name, icon);
  //Relates to the instance that has called it
 }
 else
 { // make from icon or text without associated function
  return createEmptyMenuItem(icon, name);
 }
}

QString GuiUtilBase::getLocaleAttribute(QDomElement element, QString attrName, QString locale)
{
 QDomNodeList attr = element.elementsByTagName(attrName);
 if(attr.size() > 0)
 {
  for(int i=0; i < attr.size(); i++)\
  {
   QString a;
   if((a =attr.at(i).toElement().attribute("xml:lang")) == locale)
    return attr.at(i).toElement().text();
  }
 }
 return element.attribute(attrName);
}

/**
 * Create an action against the object that invoked the creation of the
 * GUIBase, a string array is used so that in the future further options can
 * be specified to be passed.
 */
/*static*/ Action* GuiUtilBase::createActionInCallingWindow(QObject* obj, /*final*/ QStringList args, QString name, QIcon* icon)
{
 QMetaMethod method;
#if 0
 try {
     method = obj.getClass().getDeclaredMethod("remoteCalls", String[].class);
 } catch (java.lang.NullPointerException e) {
     log.error("Null object passed");
     return createEmptyMenuItem(icon, name);
 } catch (SecurityException e) {
     log.error("security exception unable to find remoteCalls for " + obj.getClass().getName());
     createEmptyMenuItem(icon, name);
 } catch (NoSuchMethodException e) {
     log.error("No such method remoteCalls for " + obj.getClass().getName());
     return createEmptyMenuItem(icon, name);
 }
#else
 if(obj == NULL)
 {
  Logger::error("Null object passed");
  return createEmptyMenuItem(icon, name);
 }
 int iRemoteCalls = obj->metaObject()->indexOfMethod(QMetaObject::normalizedSignature("remoteCalls(QStringList)"));
#endif
 if(iRemoteCalls < 0)
 {
  Logger::error("No such method remoteCalls for " + QString(obj->metaObject()->className()));
  return createEmptyMenuItem(icon, name);
 }
 method = obj->metaObject()->method(iRemoteCalls);
 CallingAbstractAction* act = new CallingAbstractAction(name, icon, obj);

 act->setMethod(method);
 act->setArgs(args);
 act->setObject(obj);
//    act->setEnabled(true);
 return (Action*)act;
}
//static class CallingAbstractAction extends javax.swing.AbstractAction
//{

/**
 *
 */
//private static final long serialVersionUID = -6063626025483350164L;

/*public*/  CallingAbstractAction::CallingAbstractAction(QString name, QIcon* icon, QObject* parent)
: AbstractAction(name, parent)
{
    //super(name, icon);
if(icon != NULL)
 setIcon(*icon);
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/  void CallingAbstractAction::setArgs(QStringList args)
{
 //args = stringArgs.getClass();
 this->args = args;
}

/*public*/  void CallingAbstractAction::setMethod(QMetaMethod method)
{
 this->method = method;
}

/*public*/  void CallingAbstractAction::setObject(QObject* obj)
{
 this->obj = obj;
}

/*public*/  void CallingAbstractAction::actionPerformed(ActionEvent* /*e*/)
{
//        try {
#if 0 // TODO:
 method.invoke(obj, args);
#else
 if(!method.invoke(obj, Qt::DirectConnection, Q_ARG(QStringList, args)))
  Logger::error("Invoke error");
#endif
//        } catch (IllegalArgumentException ex) {
//            System.out.println("IllegalArgument " + ex);
//        } catch (IllegalAccessException ex) {
//            System.out.println("IllegalAccess " + ex);
//        } catch (InvocationTargetException ex) {
//            System.out.println("InvocationTarget " + ex.toString());
//        }
}
//};

/*static*/ Action* GuiUtilBase::createEmptyMenuItem(QIcon* icon, QString name)
{
 if (icon != NULL)
 {
  GUAbstractAction* act = new GUAbstractAction(name, icon);
//  {
//            /**
//             *
//             */
//            private static final long serialVersionUID = 3780162682022372836L;

//            /*public*/  void actionPerformed(java.awt.event.ActionEvent e) {
//            }

//            /*public*/  String toString() {
//                return (String) getValue(javax.swing.Action.NAME);
//            }
//        };
   act->setEnabled(false);
   return (Action*)act;
  }
  else
  { // then name must be present
   GUAbstractAction* act = new GUAbstractAction(name);
//        {
//            /**
//             *
//             */
//            private static final long serialVersionUID = -1746638499145752231L;

//            /*public*/  void actionPerformed(java.awt.event.ActionEvent e) {
//            }

//            /*public*/  String toString() {
//                return (String) getValue(javax.swing.Action.NAME);
//            }
//        };
        act->setEnabled(false);
        return (Action*)act;
  }
 }
GUAbstractAction::GUAbstractAction(QString name, QIcon* icon)
 : AbstractAction( name, NULL)
{
 if(icon != NULL)
 {
  setIcon(*icon);
 }
}
/*public*/  void GUAbstractAction::actionPerformed(ActionEvent* e) {
}

/*public*/  QString GUAbstractAction::toString() {
    //return  getValue(Action::NAME);
 return Action::NAME;
}

/*static*/ void GuiUtilBase::setParameters(JmriAbstractAction* act, QHash<QString, QString> parameters)
{
//    for (Map.Entry<String, String> map : parameters.entrySet()) {
//        act.setParameter(map.getKey(), map);
//    }
 QHashIterator<QString, QString> iter(parameters);
 while(iter.hasNext())
 {
  iter.next();
  act->setParameter(iter.key(), iter.value());
 }
}

/**
 * Get root element from XML file, handling errors locally.
 *
 */
/*static*/ /*protected*/  QDomElement GuiUtilBase::rootFromName(QString name) {
//    try {
//        return new XmlFile() {
//        }.rootFromName(name);
//    } catch (Exception e) {
//        log.error("Could not parse file \"" + name + "\" due to: " + e);
//        return NULL;
//    }
 XmlFile* xmlFile = new XmlFile();
 return xmlFile->rootFromName(name);
}
