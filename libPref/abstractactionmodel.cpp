#include "abstractactionmodel.h"
#include <QStringList>
#include "stringutil.h"
#include "swingpropertychangesupport.h"
#include "fileutil.h"
#include <QMap>
#include <QTextStream>
#include "resourcebundle.h"
#include "libpref_global.h"
#include "loggerfactory.h"
#include "startupactionmodelutil.h"
#include "class.h"
#include "connectionnamefromsystemname.h"
#include "systemconnectionaction.h"
#include "loconetmenustartupaction.h"
#include <QTimer>
#include "jmriexception.h"
#include "systemconnectionmemomanager.h"

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
/*private*/ /*final*/ /*static*/ Logger* AbstractActionModel::log = LoggerFactory::getLogger("AbstractActionModel");


/*public*/ LIBPREFSHARED_EXPORT AbstractActionModel::AbstractActionModel(QObject *parent) :
    StartupModel(parent)
{
 className="";
 systemPrefix = "";
 exceptions = QList<Exception*>();
}

/*public*/ QString AbstractActionModel::getClassName() {
    return className;
}

/*public*/ QString AbstractActionModel::getName()
{
 if (className != "")
 {
  return StartupActionModelUtil::getDefault()->getActionName(className);
 }
 return "";
}

/*public*/ void AbstractActionModel::setName(QString n)
{
 log->debug(tr("setName(\"%1\")").arg(n));// can set className to NULL if no class found for n
 this->className = StartupActionModelUtil::getDefault()->getClassName(n);
}

/*public*/ void AbstractActionModel::setClassName(QString n) {
 log->debug(tr("setClassName(\"%1\")").arg(n));
 //Objects.requireNonNull(n, "Class name cannot be NULL");
 className = n;
}

//@NonNULL
/*public*/ QString AbstractActionModel::getSystemPrefix() {
    return this->systemPrefix;
}

/*public*/ void AbstractActionModel::setSystemPrefix(/*@Nullable*/ QString prefix) {
    if (prefix == "") {
        this->systemPrefix = ""; // NOI18N
    } else {
        this->systemPrefix = prefix;
    }
}

/*public*/ bool AbstractActionModel::isSystemConnectionAction() {
    QString name = this->getName();
    if (name != "") {
        return StartupActionModelUtil::getDefault()->isSystemConnectionAction(name);
    }
    return false;
}

//@Override
/*public*/ bool AbstractActionModel::isValid()
{
 if (this->className != "" && !this->className.isEmpty())
 {
  try
  {
   // don't need return value, just want to know if exception is triggered
   Class::forName(className);
   if (isSystemConnectionAction()) {
     return SystemConnectionMemoManager::getDefault()->getSystemConnectionMemoForSystemPrefix(systemPrefix) != nullptr;
   }
   return true;return true;
  }
  catch (ClassNotFoundException* ex)
  {
   return false;
  }
 }
 return false;
}

//@Override
/*public*/ QString AbstractActionModel::toString()
{
 QString name = this->getName();
 if (name != "")
 {
  if (!this->systemPrefix.isEmpty())
  {
    return tr("<html>%1<br>on connection %2</html>").arg(name).arg( ConnectionNameFromSystemName::getConnectionName(this->systemPrefix)); // NOI18N
  }
  return name;
 }
 if (this->className != "" && this->isValid())
 {
  return tr("Create instance of class %1").arg(this->className);
 }
 else if (this->className != "" && !this->className.isEmpty())
 {
  return tr("Unable to find class %1").arg(this->className);
 }
 return tr("Action %1 is invalid").arg(toString());
}

//@Override
/*public*/ void AbstractActionModel::performAction() /*throw (JmriException)*/
{
 log->debug(tr("Invoke Action from %1").arg(className));
 try
 {
  Action* action = (Action*) Class::forName(className)/*->newInstance()*/;
  action->setTitle(title);
   //if (SystemConnectionAction.class.isAssignableFrom(action->getClass()))
  if(((Class*)action)->isAssignableFrom("SystemConnectionAction"))
  {
   SystemConnectionMemo* memo = ConnectionNameFromSystemName::getSystemConnectionMemoFromSystemPrefix(this->getSystemPrefix());
   if (memo != NULL) {
       ((SystemConnectionAction/*<SystemConnectionMemo*>*/*) action)->setSystemConnectionMemo(memo);
   } else {
       log->warn(tr("Connection \"%1\" does not exist and cannot be assigned to action %2\nThis warning can be silenced by configuring the connection associated with the startup action.").arg(this->getSystemPrefix()).arg(className));
   }
  }
//  jmri.util.ThreadingUtil.runOnLayout(() -> {
//   try {
//       this.performAction(action);
//   } catch (JmriException ex) {
//       log.error("Error while performing startup action for class: {}", className, ex);
//   }
// });
  QTimer::singleShot(1000, [=]() {this->performAction(action);});
 } catch (ClassNotFoundException* ex) {
     log->error(tr("Could not find specified class: %1").arg(className));
 } catch (IllegalAccessException* ex) {
     log->error(tr("Unexpected access exception for class: %1").arg(className), ex);
     throw new JmriException(ex->getMessage());
 } catch (InstantiationException* ex) {
     log->error(tr("Could not instantiate specified class: %1").arg(className), ex);
     throw new JmriException(ex->getMessage());
 } catch (Exception* ex) {
     log->error(tr("Error while performing startup action for class: %1").arg(className), ex);
     throw new JmriException(ex->getMessage());
 }
}

//@Override
/*public*/ QList<Exception*> AbstractActionModel::getExceptions() {
    return QList<Exception*>(this->exceptions);
}

//@Override
/*public*/ void AbstractActionModel::addException(Exception* exception) {
    this->exceptions.append(exception);
}

/*protected*/ /*abstract*/ void AbstractActionModel::performAction(Action* action) /*throw (JmriException)*/ {}
