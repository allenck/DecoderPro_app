#include "javatoqt.h"

JavaToQt::JavaToQt()
{

}QString JavaToQt::getQtName(QString jClass)
{
 QString clazz = map.value(jClass);
 if(!clazz.isEmpty())
  return clazz;
 if(jClass.lastIndexOf('.')>0)
  return jClass.mid(jClass.lastIndexOf('.')+1);
 return jClass;
}

/*static*/ QMap<QString, QString> JavaToQt::map = {
 {"jmri.jmrit.logixng.actions.LogData", "Actions::LogData"},
 {"jmri.jmrit.logixng.actions.LogDataSwing", "Actions::LogDataSwing"},
 {"jmri.jmrit.logixng.actions.LogDataXml", "Actions::LogDataXml"},
 {"jmri.jmrit.logixng.expressions.LogData", "Expressions::LogData"},
 {"jmri.jmrit.logixng.expressions.LogDataSwing", "Expressions::LogDataSwing"},
 {"jmri.jmrit.logixng.expressions.LogDataXml", "Expressions::LogDataXml"},
 {"jmri.jmrit.logixng.actions.DigitalCallModule", "Actions::DigitalCallModule"},
 {"jmri.jmrit.logixng.actions.DigitalCallModuleSwing", "Actions::DigitalCallModuleSwing"},
 {"jmri.jmrit.logixng.expressions.DigitalCallModule", "Expressions::DigitalCallModule"},
 {"jmri.jmrit.logixng.expressions.DigitalCallModuleSwing", "Expressions::DigitalCallModuleSwing"},
 {"jmri.jmrit.logixng.actions.StringFactory", "Actions::StringFactory"},
 {"jmri.jmrit.logixng.expressions.StringFactory", "Expressions::StringFactory"},

  };
