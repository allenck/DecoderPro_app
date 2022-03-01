#include "system.h"
#include <qsettings.h>
#include <QStringList>
#include "properties.h"
#include <QSysInfo>
#include <QDir>
#include <QTime>
#include "loggerfactory.h"

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

/**
 * Returns the current time in milliseconds.  Note that
 * while the unit of time of the return value is a millisecond,
 * the granularity of the value depends on the underlying
 * operating system and may be larger.  For example, many
 * operating systems measure time in units of tens of
 * milliseconds.
 *
 * <p> See the description of the class <code>Date</code> for
 * a discussion of slight discrepancies that may arise between
 * "computer time" and coordinated universal time (UTC).
 *
 * @return  the difference, measured in milliseconds, between
 *          the current time and midnight, January 1, 1970 UTC.
 * @see     java.util.Date
 */
/*public*/ /*static*/ /*native*/ long System::currentTimeMillis()
{
 return QTime::currentTime().msecsSinceStartOfDay();
}

/*public*/ /*static*/ void System::out(QString s)
{
 log->info(s);
}
/*public*/ /*static*/ void System::err(QString s)
{
 log->error(s);
}

/*static*/ Logger* System::log = LoggerFactory::getLogger("System");
