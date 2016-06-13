#include "warrantpreferences.h"
#include "signalspeedmap.h"
#include "file.h"
#include <QStringList>
#include <QVector>
#include "nxframe.h"
#include <QDir>

WarrantPreferences::WarrantPreferences(QObject *parent) :
  QObject(parent)
{
 _scale = 87.1f;
 _searchDepth = 20;
  _throttleScale = 0.5f;
  log = new Logger("WarrantPreferences");

 _interpretation = SignalSpeedMap::PERCENT_NORMAL;    // Interpretation of values in speed name table

 _msIncrTime = 1000;         // time in milliseconds between speed changes ramping up or down
  _throttleIncr = 0.04f;    // throttle increment for each ramp speed change
}

///*public*/ class WarrantPreferences  {

    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::layoutParams = "layoutParams";   // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::LayoutScale = "layoutScale";     // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::SearchDepth = "searchDepth";     // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::SpeedMapParams = "speedMapParams"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::RampPrefs = "rampPrefs";         // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::TimeIncrement = "timeIncrement"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::ThrottleScale = "throttleScale"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::RampIncrement = "rampIncrement"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::StepIncrements = "stepIncrements"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::SpeedNamePrefs = "speedNames";   // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::Interpretation = "interpretation"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::AppearancePrefs = "appearancePrefs"; // NOI18N


WarrantPreferences::WarrantPreferences(QString fileName, QObject *parent) :
  QObject(parent) {
 _scale = 87.1f;
 _searchDepth = 20;
  _throttleScale = 0.5f;
  log = new Logger("WarrantPreferences");

 _interpretation = SignalSpeedMap::PERCENT_NORMAL;    // Interpretation of values in speed name table

 _msIncrTime = 1000;         // time in milliseconds between speed changes ramping up or down
  _throttleIncr = 0.04f;    // throttle increment for each ramp speed change

 openFile(fileName);
}

/*public*/ void WarrantPreferences::openFile(QString name)
{
 _fileName = name;
 WarrantPreferencesXml* prefsXml = new WarrantPreferencesXml();
 File* file = new File(_fileName);
 QDomElement root = QDomElement();
 if(file->exists() && file->length() > 0)
 {
  //try {
  root = prefsXml->rootFromFile(file);
  if(root.toElement().isNull())
  {
   log->debug("Could not find Warrant preferences file.  Normal if preferences have not been saved before.");
   root = QDomElement();
  }
//         catch (Exception eb) {
//         Logger::error("Exception while loading warrant preferences: " + eb.getMessage());
//         root = QDomElement();
//     }
 }
 if (!root.isNull())
 {
  log->info(tr("Found Warrant preferences file: %1").arg(_fileName));
  loadLayoutParams(root.firstChildElement(layoutParams));
  if (!loadSpeedMap(root.firstChildElement(SpeedMapParams)))
  {
   loadSpeedMapFromOldXml();
   Logger::error("Unable to read ramp parameters. Setting to default values.");
  }
 }
 else
 {
  loadSpeedMapFromOldXml();
 }
}

/*public*/ void WarrantPreferences::loadLayoutParams(QDomElement child)
{
 if (child.isNull())
 {
  return;
 }
 QString a;
 if ((a = child.attribute(LayoutScale)) != NULL)
 {
  bool bok;
  setScale(a.toFloat(&bok));
  if(!bok) {
  setScale(87.1f);
  Logger::error("Unable to read layout scale. Setting to default value.");
  }
 }
 if ((a = child.attribute(SearchDepth)) != NULL)
 {
  bool bok;
  setSearchDepth(a.toInt(&bok));
  if(!bok)
  {
   setSearchDepth(20);
   Logger::error("Unable to read route search depth. Setting to default value (20).");
  }
 }
}

/*private*/ void WarrantPreferences::loadSpeedMapFromOldXml()
{
 SignalSpeedMap* map = SignalSpeedMap::getMap();
 if (map==NULL)
 {
  Logger::error("Cannot find signalSpeeds.xml file.");
  return;
 }
 QVectorIterator<QString> it(map->getValidSpeedNames());
 _speedNames =  QMap<QString, float>();
 while (it.hasNext())
 {
  QString name = it.next();
  _speedNames.insert(name, map->getSpeed(name));
 }

  QStringListIterator en = map->getAppearanceIterator();
 _headAppearances =  QMap<QString, QString>();
 while (en.hasNext())
 {
  QString name = en.next();
  _headAppearances.insert(name, map->getAppearanceSpeed(name));
 }
 setTimeIncre(map->getStepDelay());
 setThrottleIncre(map->getStepIncrement());
}

/*public*/ bool WarrantPreferences::loadSpeedMap(QDomElement child)
{
 if (child.isNull()) {
     return false;
 }
 QDomElement rampParms = child.firstChildElement(StepIncrements);
 if (rampParms.isNull()) {
     return false;
 }
 QString a;
 if ((a = rampParms.attribute(TimeIncrement)) != NULL) {
     bool bok;
         setTimeIncre(a.toInt(&bok));
         if(!bok) {
         setTimeIncre(750);
         Logger::error("Unable to read ramp time increment. Setting to default value (750ms).");
     }
 }
 if ((a = rampParms.attribute(RampIncrement)) != NULL) {
     bool bok;
         setThrottleIncre(a.toFloat(&bok));
         if(!bok) {
         setThrottleIncre(0.05f);
         Logger::error("Unable to read ramp throttle increment. Setting to default value (0.05).");
     }
 }
 if ((a = rampParms.attribute(ThrottleScale)) != NULL) {
     bool bok;
         setThrottleScale(a.toFloat(&bok));
         if(!bok) {
         setThrottleScale(0.70f);
         Logger::error("Unable to read throttle scale. Setting to default value (0.70f).");
     }
 }

 rampParms = child.firstChildElement(SpeedNamePrefs);
 if (rampParms.isNull()) {
     return false;
 }
 if ((a = rampParms.attribute("percentNormal")) != NULL) {
     if (a==("yes")) {
         setInterpretation(1);
     } else {
         setInterpretation(2);
     }
 }
 if ((a = rampParms.attribute(Interpretation)) != NULL) {
     bool bok;
         setInterpretation(a.toInt(&bok));
         if(!bok) {
         setInterpretation(1);
         Logger::error("Unable to read interpetation of Speed Map. Setting to default value % normal.");
     }
 }
 _speedNames =  QMap<QString, float>();
 QDomNodeList list = rampParms.childNodes();
 for (int i = 0; i < list.size(); i++) {
     QString name = list.at(i).toElement().tagName();
     float speed = 0;
     bool bok;
         speed =  list.at(i).toElement().text().toFloat(&bok);
         if(!bok) {
         Logger::error(SpeedNamePrefs+" has invalid content for "+name+" = "+list.at(i).toElement().text());
     }
     if (log->isDebugEnabled()) log->debug("Add "+name+", "+QString::number(speed)+" to AspectSpeed Table");
     _speedNames.insert(name, speed);
 }

 rampParms = child.firstChildElement(AppearancePrefs);
 if (rampParms.isNull()) {
     return false;
 }
 _headAppearances = QMap<QString, QString>();
 list = rampParms.childNodes();
 for (int i = 0; i < list.size(); i++) {
     QString name = (list.at(i).toElement().tagName());
     QString speed = list.at(i).toElement().text();
     _headAppearances.insert(name, speed);
 }

 setSpeedMap();
 return true;
}

/*public*/ void WarrantPreferences::save()
{
 if (_fileName == NULL)
 {
  Logger::error("_fileName NULL. Could not create warrant preferences file.");
  return;
 }

 xmlFile = new XmlFile();
 xmlFile->makeBackupFile(_fileName);
 File* file=new File(_fileName);
 try
 {
  File* parentDir=file->getParentFile();
  if(!QDir(file->getParent()).exists())
  {
   if (!parentDir->mkdir())
   {
    log->warn("Could not create parent directory for prefs file :"+_fileName);
    return;
   }
  }
  if (file->createNewFile()) log->debug("Creating new warrant prefs file: "+_fileName);
 }
 catch (Exception ea)
 {
  Logger::error("Could not create warrant preferences file at "+_fileName+". "/*+ea*/);
 }

 try
 {
  QDomElement root = xmlFile->doc.createElement("warrantPreferences");
  //Document doc = XmlFile.newDocument(root);
  if (store(root))
  {
   xmlFile->writeXML(file, xmlFile->doc);
  }
 }
 catch (Exception eb)
 {
  log->warn("Exception in storing warrant xml: "/*+eb*/);
 }
}

/*public*/ bool WarrantPreferences::store(QDomElement root)
{
 QDomElement prefs = xmlFile->doc.createElement(layoutParams);
 try
 {
  prefs.setAttribute(LayoutScale, QString::number(getScale()));
  prefs.setAttribute(SearchDepth, QString::number(getSearchDepth()));
  root.appendChild(prefs);

  prefs = xmlFile->doc.createElement(SpeedMapParams);
  QDomElement rampPrefs = xmlFile->doc.createElement(StepIncrements);
  rampPrefs.setAttribute(TimeIncrement, QString::number(getTimeIncre()));
  rampPrefs.setAttribute(RampIncrement, QString::number(getThrottleIncre()));
  rampPrefs.setAttribute(ThrottleScale, QString::number(getThrottleScale()));
  prefs.appendChild(rampPrefs);

  rampPrefs = xmlFile->doc.createElement(SpeedNamePrefs);
  rampPrefs.setAttribute(Interpretation, QString::number(getInterpretation()));

  QMapIterator<QString, float>  it = getSpeedNameEntryIterator();
  while (it.hasNext())
  {
     // Entry<QString, float> ent = it.next();
   it.next();
      QDomElement step =  xmlFile->doc.createElement(it.key());
      step.appendChild(xmlFile->doc.createTextNode(QString::number(it.value())));
      rampPrefs.appendChild(step);
  }
  prefs.appendChild(rampPrefs);

  rampPrefs = xmlFile->doc.createElement(AppearancePrefs);
  QDomElement step =  xmlFile->doc.createElement("SignalHeadStateRed");
  step.appendChild(xmlFile->doc.createTextNode(_headAppearances.value(tr("Red"))));
  rampPrefs.appendChild(step);
  step =  xmlFile->doc.createElement("SignalHeadStateFlashingRed");
  step.appendChild(xmlFile->doc.createTextNode(_headAppearances.value(tr("Flashing Red"))));
  rampPrefs.appendChild(step);
  step =  xmlFile->doc.createElement("SignalHeadStateGreen");
  step.appendChild(xmlFile->doc.createTextNode(_headAppearances.value(tr("Green"))));
  rampPrefs.appendChild(step);
  step =  xmlFile->doc.createElement("SignalHeadStateFlashingGreen");
  step.appendChild(xmlFile->doc.createTextNode(_headAppearances.value(tr("Flashing Green"))));
  rampPrefs.appendChild(step);
  step =  xmlFile->doc.createElement("SignalHeadStateYellow");
  step.appendChild(xmlFile->doc.createTextNode(_headAppearances.value(tr("Yellow"))));
  rampPrefs.appendChild(step);
  step =  xmlFile->doc.createElement("SignalHeadStateFlashingYellow");
  step.appendChild(xmlFile->doc.createTextNode(_headAppearances.value(tr("Flashing Yellow"))));
  rampPrefs.appendChild(step);
  step =  xmlFile->doc.createElement("SignalHeadStateLunar");
  step.appendChild(xmlFile->doc.createTextNode(_headAppearances.value(tr("Lunar"))));
  rampPrefs.appendChild(step);
  step =  xmlFile->doc.createElement("SignalHeadStateFlashingLunar");
  step.appendChild(xmlFile->doc.createTextNode(_headAppearances.value(tr("Flashing Lunar"))));
  rampPrefs.appendChild(step);
  prefs.appendChild(rampPrefs);
 }
 catch (Exception ex)
 {
  log->warn("Exception in storing warrant xml: ");
  //ex.printStackTrace();
  return false;
 }
 root.appendChild(prefs);
 return true;
}

/**
 * Apply to classes that use this data
 */
/*public*/ void WarrantPreferences::apply() {
    setSpeedMap();
    setNXFrame();
}
/*private*/ void WarrantPreferences::setNXFrame() {

    NXFrame* frame = NXFrame::getInstance();
    frame->setScale(_scale);
    frame->setDepth(_searchDepth);
    frame->setTimeInterval(_msIncrTime);
    frame->setRampIncrement(_throttleIncr);
    frame->updatePanel(_interpretation);
    frame->closeFrame();
}
/*private*/ void WarrantPreferences::setSpeedMap() {
    SignalSpeedMap* map = new SignalSpeedMap();
    map->setAspectTable(getSpeedNameEntryIterator(), _interpretation);
    map->setAppearanceTable(getAppearanceEntryIterator());
    map->setRampParams(_throttleIncr, _msIncrTime);
    map->setDefaultThrottleFactor(_throttleScale);
    map->setLayoutScale(_scale);
    map->setMap(map);
}

float WarrantPreferences::getScale() {
    return _scale;
}
void WarrantPreferences::setScale(float s) {
    _scale = s;
}

/*public*/ float WarrantPreferences::getThrottleScale() {
    return _throttleScale;
}
void WarrantPreferences::setThrottleScale(float f) {
    _throttleScale = f;
}

int WarrantPreferences::getSearchDepth() {
    return _searchDepth;
}
void WarrantPreferences::setSearchDepth(int d) {
    _searchDepth = d;
}

int WarrantPreferences::getTimeIncre() {
    return _msIncrTime;
}
void WarrantPreferences::setTimeIncre(int t) {
    _msIncrTime = t;
}

float WarrantPreferences::getThrottleIncre() {
    return _throttleIncr;
}
void WarrantPreferences::setThrottleIncre(float ti) {
    _throttleIncr = ti;
}

QMapIterator<QString, float> WarrantPreferences::getSpeedNameEntryIterator()
{
    QStringListIterator keys = _speedNames.keys();
    QMap<QString, float> vec =  QMap<QString, float> ();
    while (keys.hasNext())
    {
        QString key = keys.next();
        vec.insert(key, _speedNames.value(key));
    }
    return QMapIterator<QString, float> (vec)/*.iterator()*/;
}
int WarrantPreferences::getSpeedNamesSize() {
    return _speedNames.size();
}
float WarrantPreferences::getSpeedNameValue(QString key) {
    return _speedNames.value(key);
}
void WarrantPreferences::setSpeedNames(QList<QPair<QString, float>* > speedNameMap)
{
 _speedNames =  QMap<QString, float>();
 for (int i=0; i<speedNameMap.size(); i++) {
     QPair<QString, float>* dp = speedNameMap.at(i);
     _speedNames.insert(dp->first, dp->second);
 }
}

QMapIterator<QString, QString> WarrantPreferences::getAppearanceEntryIterator()
{
 QStringListIterator keys(_headAppearances.keys());
 QMap<QString, QString>  vec =  QMap<QString, QString> ();
 while (keys.hasNext())
 {
  QString key = keys.next();
  vec.insert(key, _headAppearances.value(key));
 }
 return QMapIterator<QString, QString> (vec);
}
int WarrantPreferences::getAppearancesSize()
{
 return _headAppearances.size();
}

QString WarrantPreferences::getAppearanceValue(QString key)
{
 return _headAppearances.value(key);
}
void WarrantPreferences::setAppearances(QList<QPair<QString, QString>* > appearanceMap)
{
 _headAppearances =  QMap<QString, QString>();
 for (int i=0; i<appearanceMap.size(); i++)
 {
  QPair<QString, QString>* dp = appearanceMap.at(i);
  _headAppearances.insert(dp->first, dp->second);
 }
}

int WarrantPreferences::getInterpretation()
{
 return _interpretation;
}
void WarrantPreferences::setInterpretation(int interp)
{
 _interpretation = interp;
}

