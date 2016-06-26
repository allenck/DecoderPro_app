#include "system.h"
#include <qsettings.h>
#include <QStringList>
#include "properties.h"

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
 if((val =getProperty(key)) == "")
  return dft;
 return val;
}

QString System::getProperty(QString key)
{
 QSettings settings;
 settings.beginGroup("Properties");
 QString value = settings.value(key).toString();
 settings.endGroup();
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
