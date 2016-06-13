#include "resourcebundle.h"
#include "logger.h"
#include <QFile>
#include "fileutil.h"
#include <QTextStream>


ResourceBundle::ResourceBundle(QObject *parent) :
    QObject(parent)
{
 initDefault();
}
ResourceBundle* ResourceBundle::getBundle(QString name)
{
 if(name == "DCS51")
 {
  initDCS51();
 }
 else if(name == "LocoBuffer")
 {
  initLocoBuffer();
 }
 else
 {
  QString path = FileUtil::getProgramPath() + "java" + QDir::separator() + name;
  QFileInfo info(path);
  if(!info.exists())
  {
   Logger::error(QString("Can't find %1").arg(path));
   return NULL;
  }
  bundleMap = new QMap<QString, QString>();

  QFile file(path);
  if(file.open(QIODevice::ReadOnly| QIODevice::Text))
  {
   bundleMap->clear();
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
     bundleMap->insert(key, value);
    }
   }
  }
 }
 return this;
}
QString ResourceBundle::getString(QString key)
{
 return bundleMap->value(key);
}
QStringList ResourceBundle::keys()
{
 return bundleMap->keys();
}
void ResourceBundle::initDCS51()
{
 bundleMap = new QMap<QString, QString>();
 bundleMap->insert("ButtonRead", tr("Read"));
 bundleMap->insert("ButtonWrite", tr("Write"));
 bundleMap->insert("CONFIG_SLOT", tr("127"));
 bundleMap->insert("CheckBoxReserved", tr("Show reserved option switches"));
 bundleMap->insert("HeadingText", tr("Items describe effect on system operation when set \"closed\""));
 bundleMap->insert("LabelC", tr("C"));
 bundleMap->insert("LabelT", tr("T"));
 bundleMap->insert("LabelTop", tr("DCS51 (Zephyr) Programmer"));
 bundleMap->insert("MAX_OPTION", tr("49"));
 bundleMap->insert("MIN_OPTION", tr("1"));
 bundleMap->insert("Option1", tr("1: One jump port (normally two)"));
 bundleMap->insert("Option10", tr("10: Recall Depth 4"));
 bundleMap->insert("Option11", tr("11: Recall Depth 8"));
 bundleMap->insert("Option13", tr("13: Raise loco address purge time to 600 seconds"));
 bundleMap->insert("Option14", tr("14: Disable loco address purging"));
 bundleMap->insert("Option15", tr("15: Purge will force a loco to zero speed"));
 bundleMap->insert("Option17", tr("17: Automatic advanced consists are disabled"));
 bundleMap->insert("Option18", tr("18: Extend booster short shutdown to 1/2 second"));
 bundleMap->insert("Option2", tr("2: Booster/Throttle, not command station"));
 bundleMap->insert("Option20", tr("20: Disable address 0 analog operation"));
 bundleMap->insert("Option21", tr("21: Global default for new loco: FX"));
 bundleMap->insert("Option22", tr("22: Global default for new loco: 28 step"));
 bundleMap->insert("Option23", tr("23: Global default for new loco: 14 step"));
 bundleMap->insert("Option27", tr("27: Disable normal switch commands (Bushby bit)"));
 bundleMap->insert("Option28", tr("28: Disable DS54 interrogate at power on"));
 bundleMap->insert("Option3", tr("3: Booster is autoreversing"));
 bundleMap->insert("Option33", tr("33: Restore track power to prior state at power on"));
 bundleMap->insert("Option34", tr("34: Allow track to power up to run state"));
 bundleMap->insert("Option39", tr("39: Clear all internal memory"));
 bundleMap->insert("Option43", tr("43: Disable LocoNet update of track status"));
 bundleMap->insert("Option45", tr("45: Disable reply for switch state request"));
 bundleMap->insert("Option5", tr("5: No change allowed for throttle ID, Vmax or brake rate"));
 bundleMap->insert("Option6", tr("6: Function 3 is non-latching"));
 bundleMap->insert("Option7", tr("7: Blast-mode programming for sound decoders"));
 bundleMap->insert("Reserved", tr("Reserved"));
}
void ResourceBundle::initDefault()
{
 bundleMap = new QMap<QString, QString>();
 bundleMap->insert("ButtonRead", tr("Read"));
 bundleMap->insert("ButtonWrite", tr("Write"));
 bundleMap->insert("CONFIG_SLOT", tr("127"));
 bundleMap->insert("CheckBoxReserved", tr("Show reserved option switches"));
 bundleMap->insert("HeadingText", tr("Items describe effect on system operation when set \"closed\""));
 bundleMap->insert("LabelC", tr("C"));
 bundleMap->insert("LabelT", tr("T"));
 bundleMap->insert("LabelTop", tr("Command Station Programmer"));
 bundleMap->insert("MAX_OPTION", tr("49"));
 bundleMap->insert("MIN_OPTION", tr("1"));
 bundleMap->insert("Option10", tr("10: Expand trinary switch echo"));
 bundleMap->insert("Option11", tr("11: Make certain trinary switches long duration"));
 bundleMap->insert("Option12", tr("12: Trinary addresses 1-80 allowed"));
 bundleMap->insert("Option13", tr("13: Raise loco address purge time to 600 seconds"));
 bundleMap->insert("Option14", tr("14: Disable loco address purging"));
 bundleMap->insert("Option15", tr("15: Purge will force a loco to zero speed"));
 bundleMap->insert("Option17", tr("17: Automatic advanced consists are disabled"));
 bundleMap->insert("Option18", tr("18: Extend booster short shutdown to 1/2 second"));
 bundleMap->insert("Option2", tr("2: Set unit to be booster only, not command station"));
 bundleMap->insert("Option20", tr("20: Disable address 0 analog operation"));
 bundleMap->insert("Option21", tr("21: Global default for new loco: FX"));
 bundleMap->insert("Option22", tr("22: Global default for new loco: 28 step"));
 bundleMap->insert("Option23", tr("23: Global default for new loco: 14 step"));
 bundleMap->insert("Option25", tr("25: Disable aliasing"));
 bundleMap->insert("Option26", tr("26: Enable routes"));
 bundleMap->insert("Option27", tr("27: Disable normal switch commands (Bushby bit)"));
 bundleMap->insert("Option28", tr("28: Disable DS54 interrogate at power on"));
 bundleMap->insert("Option3", tr("3: Booster is autoreversing"));
 bundleMap->insert("Option31", tr("31: Meter route/switch output when not in trinary"));
 bundleMap->insert("Option33", tr("33: Restore track power to prior state at power on"));
 bundleMap->insert("Option34", tr("34: Allow track to power up to run state"));
 bundleMap->insert("Option36", tr("36: Clear all mobile decoder info and consists"));
 bundleMap->insert("Option37", tr("37: Clear all routes"));
 bundleMap->insert("Option38", tr("38: Clear the loco roster"));
 bundleMap->insert("Option39", tr("39: Clear all internal memory"));
 bundleMap->insert("Option41", tr("41: Diagnostic click when LocoNet command received"));
 bundleMap->insert("Option42", tr("42: Disable 3 beeps when loco address purged"));
 bundleMap->insert("Option43", tr("43: Disable LocoNet update of track status"));
 bundleMap->insert("Option45", tr("45: Disable reply for switch state request"));
 bundleMap->insert("Option47", tr("47: Program track is brake generator"));
 bundleMap->insert("Option5", tr("5: No change allowed for throttle ID, Vmax or brake rate"));
 bundleMap->insert("Option9", tr("9: Allow Motorola trinary echo for 1-256"));
 bundleMap->insert("Reserved", tr("Reserved"));
}
void ResourceBundle::initLocoBuffer()
{
 bundleMap = new QMap<QString, QString>();
 bundleMap->insert("ButtonRead", tr("Read"));
 bundleMap->insert("ButtonWrite", tr("Write"));
 bundleMap->insert("CONFIG_SLOT", tr("127"));
 bundleMap->insert("CheckBoxReserved", tr("Show reserved option switches"));
 bundleMap->insert("HeadingText", tr("Items describe effect on system operation when set \"closed\""));
 bundleMap->insert("LabelC", tr("C"));
 bundleMap->insert("LabelT", tr("T"));
 bundleMap->insert("LabelTop", tr("LocoBuffer-PS (Programming Station) Programmer"));
 bundleMap->insert("MAX_OPTION", tr("41"));
 bundleMap->insert("MIN_OPTION", tr("1"));
 bundleMap->insert("Option13", tr("13: Raise loco address purge time to 600 seconds"));
 bundleMap->insert("Option14", tr("14: Disable loco address purging"));
 bundleMap->insert("Option22", tr("22: Global default for new loco: 28 step"));
 bundleMap->insert("Option23", tr("23: Global default for new loco: 14 step"));
 bundleMap->insert("Option33", tr("33: Restore track power to prior state at power on"));
 bundleMap->insert("Option34", tr("34: Allow track to power up to run state"));
 bundleMap->insert("Option4", tr("4: Programmer mode only"));
 bundleMap->insert("Option5", tr("5: No change allowed for throttle ID, Vmax or brake rate"));
 bundleMap->insert("Reserved", tr("Reserved"));
}
