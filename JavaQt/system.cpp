#include "system.h"
#include <qsettings.h>
#include <QStringList>
#include "properties.h"
#include <QSysInfo>
#include <QDir>

System::System(QObject *parent) :
  QObject(parent)
{
}
void System::setProperty(QString key, QVariant value)
{
 QSettings settings;
 settings.beginGroup("Properties");
 settings.setValue(key,value);
 settings.endGroup();
}
QString System::getProperty(QString key, QString dft)
{
 QString val;
 if((val = getProperty(key)) == "")
  return dft;
 return val;
}

QString System::getProperty(QString key)
{
 QSettings settings;
 settings.beginGroup("Properties");
 QString value = settings.value(key).toString();
 settings.endGroup();
 if(value == "")
  value = checkDefault(key);
 return value;
}

Properties* System::getProperties()
{
 QSettings settings;
 settings.beginGroup("Properties");
 QStringList properties = settings.allKeys();
 props = new Properties;
 foreach (QString key, properties) {
 props->setProperty(key, settings.value(key).toString());
 }
 settings.endGroup();
 return props;
}
Properties* System::props = NULL;

QString System::checkDefault(QString key)
{
 if(key == "os.name")
 {
#ifdef Q_OS_WIN
  setProperty("os.name", QSysInfo::prettyProductName());
  setProperty("file.separator", "\\");
  setProperty("line.separator", "\r\n");
  setProperty("user.name",qgetenv("USERNAME"));
#endif
#ifdef Q_OS_UNIX
//  setProperty("os.name", QSysInfo::prettyProductName());
//  setProperty("os.arch", QSysInfo::currentCpuArchitecture());
//  setProperty("os.version", QSysInfo::kernelVersion());
  setProperty("file.separator", "/");
  setProperty("line.separator", "\n");
  setProperty("user.name",qgetenv("USER"));
  setProperty("user.home", QDir::homePath());
#endif
  //return QSysInfo::prettyProductName();
 }
 return "";
}
