#include "abstractactionmodel.h"
#include <QStringList>
#include "stringutil.h"
#include "propertychangesupport.h"
#include "fileutil.h"
#include <QMap>
#include <QTextStream>
#include "resourcebundle.h"
#include "libpref_global.h"

//AbstractActionModel::AbstractActionModel(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Provide services for invoking actions during configuration
 * and startup.
 * <P>
 * The action classes and corresponding human-readable names are kept in the
 * apps.ActionListCoreBundle properties file (which can be translated).
 * They are displayed in lexical order by human-readable name.
 * <P>
 * @author	Bob Jacobsen   Copyright 2003, 2007, 2014
 * @version     $Revision: 25398 $
 * @see PerformActionPanel
 */
// /*public*/ abstract class AbstractActionModel{

/*public*/ LIBPREFSHARED_EXPORT AbstractActionModel::AbstractActionModel(QObject *parent) :
    QObject(parent)
{
 className="";
 pcs = new PropertyChangeSupport(this);
 log = new Logger("AbstractActionModel");
}

/*public*/ QString AbstractActionModel::getClassName() {
    return className;
}

/*public*/ QString AbstractActionModel::getName()
{
 //Iterator<Class<?>> iterator = classList.keySet().iterator();
 QStringListIterator iterator(_classList.keys());
 while (iterator.hasNext())
 {
  QString key = iterator.next();
  if(key==(className))
   return _classList.value(key);
 }
 return "";
}

/*public*/ void AbstractActionModel::setName(QString n)
{
 //Iterator<Class<?>> iterator = classList.keySet().iterator();
 QStringListIterator iterator(_classList.keys());
 while (iterator.hasNext())
 {
  QString key = iterator.next();
  if(_classList.value(key)==(n))
  {
   className = key;
   return;
  }
 }
}

/*public*/ void AbstractActionModel::setClassName(QString n) {
    className = n;
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings({"EI_EXPOSE_REP", "MS_EXPOSE_REP"}) // OK until Java 1.6 allows return of cheap array copy
/*static*/ /*public*/ QStringList AbstractActionModel::nameList()
{
 if (_classList.isEmpty()) loadArrays();
 QStringList names = _classList.values();//.toArray(new String[classList.size()]);
 //StringUtil::sort(names);
 return names;
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings({"EI_EXPOSE_REP", "MS_EXPOSE_REP"}) // OK until Java 1.6 allows return of cheap array copy
/*static*/ /*public*/ QStringList AbstractActionModel::classList()
{
 if (_classList.isEmpty()) loadArrays();
 return _classList.keys();//.toArray(new Class<?>[classList.size()]);
}

/*static*/ /*private*/ void AbstractActionModel::loadArrays()
{
 //ResourceBundle rb = ResourceBundle.getBundle("apps.ActionListCoreBundle");
    ResourceBundle* rb = new ResourceBundle();
 rb->getBundle("src/apps/ActionListCoreBundle.properties");
 // count entries (not entirely efficiently!)
 _classList = QMap<QString, QString>();
 //Enumeration<String> e = rb.getKeys();
 QStringListIterator e(rb->keys());
 while (e.hasNext())
 {
  QString classes;
  QString key = e.next();
  if (key!=(""))
  { // ignoring empty lines in file
   try
   {
    classes = key;//Class.forName(key);
    _classList.insert(classes, rb->getString(key));
   }
   catch (ClassNotFoundException ex)
   {
    Logger::error("Did not find class ["+key+"]");
   }
  }
 }
}

/*public*/ void AbstractActionModel::addAction(QString strClass, QString name) throw (ClassNotFoundException)
{
 if(_classList.isEmpty()) loadArrays();
 QString classes;
 try
 {
  classes= strClass /*Class.forName(strClass)*/;
 }
 catch (ClassNotFoundException ex)
 {
    log->error("Did not find class "+strClass);
        throw ex;
    }
    _classList.insert(classes, name);
    firePropertyChange("length","","");
}

/*public*/ void AbstractActionModel::removeAction(QString strClass) throw (ClassNotFoundException)
{
 if(_classList.isEmpty()) return;
 QString classes;
 try
 {
  classes= strClass /*Class.forName(strClass)*/;
 } catch (ClassNotFoundException ex)
 {
  log->error("Did not find class "+strClass);
  throw ex;
 }
 _classList.remove(classes);
 firePropertyChange("length","","");
}

/*static*/ /*private*/ QMap<QString, QString> AbstractActionModel::_classList = QMap<QString, QString>();

/*public*/ /*synchronized*/ void AbstractActionModel::addPropertyChangeListener(PropertyChangeListener* l) {
    pcs->addPropertyChangeListener(l);
}
/*public*/ /*synchronized*/ void AbstractActionModel::removePropertyChangeListener(PropertyChangeListener* l) {
    pcs->removePropertyChangeListener(l);
}
/*protected*/ void AbstractActionModel::firePropertyChange(QString p, QVariant old, QVariant n)
{ pcs->firePropertyChange(p,old,n);}

#if 0
/*static*/ QMap<QString, QString> ResourceBundle::bundleMap = QMap<QString, QString>();

void ResourceBundle::getBundle(QString filename)
{
 QString path = FileUtil::getProgramPath() + "java" + QDir::separator() + filename;
 QFileInfo info(path);
 if(!info.exists())
 {
  Logger::error(QString("Can't find %1").arg(path));
  return;
 }
 QFile file(path);
 if(file.open(QIODevice::ReadOnly| QIODevice::Text))
 {
  bundleMap.clear();
  while (!file.atEnd())
  {
   QTextStream in(&file);
   while (!in.atEnd())
   {
    QString line = in.readLine();
    if(line.startsWith("#"))
        continue;
    if(!line.contains("="))
        continue;
    QStringList sl = line.split("=");
    QString left = sl.at(0).trimmed();
    QString key;
    QString value;
    int i = left.lastIndexOf(".");
    if(i == -1)
     key = left;
    else
     key = left.mid(i+1);
    value = sl.at(1).trimmed();
    bundleMap.insert(key, value);
   }
  }
 }
}
QString ResourceBundle::getString(QString key)
{
 return bundleMap.value(key);
}
QStringList ResourceBundle::keys()
{
 return bundleMap.keys();
}
#endif
