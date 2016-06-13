#include "system.h"
#include <qsettings.h>
#include <QStringList>

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
QString System::getProperty(QString key)
{
 QSettings settings;
 settings.beginGroup("Properties");
 QString value = settings.value(key).toString();
 settings.endGroup();
 return value;
}
QStringList System::getProperties()
{
 QSettings settings;
 settings.beginGroup("Properties");
 QStringList properties = settings.allKeys();
 settings.endGroup();
 return properties;
}

