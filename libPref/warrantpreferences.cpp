#include "warrantpreferences.h"
#include "signalspeedmap.h"
#include "file.h"
#include <QStringList>
#include <QVector>
#include "nxframe.h"
#include <QDir>
#include "instancemanager.h"
#include "profilemanager.h"
#include "fileutil.h"


WarrantPreferences::WarrantPreferences(QObject *parent) :
  AbstractPreferencesManager(parent)
{
 _scale = 87.1f;
 _searchDepth = 20;
  _throttleScale = 0.90f;
  log = new Logger("WarrantPreferences");

 _interpretation = SignalSpeedMap::PERCENT_NORMAL;    // Interpretation of values in speed name table

 _msIncrTime = 1000;         // time in milliseconds between speed changes ramping up or down
  _throttleIncr = 0.04f;    // throttle increment for each ramp speed change
}

///*public*/ class WarrantPreferences  {

    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::LAYOUT_PARAMS = "layoutParams";   // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::LAYOUT_SCALE = "layoutScale";    // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::SEARCH_DEPTH = "searchDepth";     // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::SPEED_MAP_PARAMS = "speedMapParams"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::RAMP_PREFS = "rampPrefs";         // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::TIME_INCREMENT = "timeIncrement"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::THROTTLE_SCALE = "throttleScale"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::RAMP_INCREMENT = "rampIncrement"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::STEP_INCREMENTS = "stepIncrements"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::SPEED_NAME_PREFS = "speedNames";   // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::SPEED_NAMES = WarrantPreferences::SPEED_NAME_PREFS;
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::INTERPRETATION = "interpretation"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::APPEARANCE_PREFS = "appearancePrefs"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString WarrantPreferences::APPEARANCES = "appearances"; // NOI18N

/**
 * Get the default instance.
 *
 * @return the default instance, creating it if necessary
 */
/*public*/ /*static*/ WarrantPreferences* WarrantPreferences::getDefault()
{
 WarrantPreferences* preferences = (WarrantPreferences*)InstanceManager::getOptionalDefault("WarrantPreferences"); //.orElseGet(() -> {
 if(preferences == NULL)
 {
   preferences = (WarrantPreferences*)InstanceManager::setDefault("WarrantPreferences", new WarrantPreferences());
  try {
      preferences->initialize(ProfileManager::getDefault()->getActiveProfile());
  }
  catch (InitializationException ex) {
      Logger::error("Error initializing default WarrantPreferences", ex);
  }
 }//);
 return preferences;
}

/*public*/ void WarrantPreferences::openFile(QString name)
{
 _fileName = name;
 WarrantPreferencesXml* prefsXml = new WarrantPreferencesXml();
 File* file = new File(_fileName);
 QDomElement root;
 try
 {
  root = prefsXml->rootFromFile(file);
  if(root.toElement().isNull())
  {
   log->debug("Could not find Warrant preferences file.  Normal if preferences have not been saved before.");
   root = QDomElement();
  }
 }
 catch (FileNotFoundException ea) {
     log->debug("Could not find Warrant preferences file.  Normal if preferences have not been saved before.");
     root = QDomElement();
 }catch (Exception eb) {
     log->error("Exception while loading warrant preferences: " + eb.getMessage());
     root = QDomElement();
 }
 if (!root.isNull())
 {
  log->info(tr("Found Warrant preferences file: %1").arg(_fileName));
  loadLayoutParams(root.firstChildElement(LAYOUT_PARAMS));
  if (!loadSpeedMap(root.firstChildElement(SPEED_MAP_PARAMS)))
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
 if ((a = child.attribute(LAYOUT_SCALE)) != NULL)
 {
  bool bok;
  setScale(a.toFloat(&bok));
  if(!bok) {
  setScale(87.1f);
  Logger::error("Unable to read layout scale. Setting to default value.");
  }
 }
 if ((a = child.attribute(SEARCH_DEPTH)) != NULL)
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
 SignalSpeedMap* map = static_cast<SignalSpeedMap*>(InstanceManager::getNullableDefault("SignalSpeedMap"));
 if (map==nullptr)
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
 setTimeIncrement(map->getStepDelay());
 setThrottleIncrement(map->getStepIncrement());
}

/*public*/ bool WarrantPreferences::loadSpeedMap(QDomElement child)
{
 if (child.isNull()) {
     return false;
 }
 QDomElement rampParms = child.firstChildElement(STEP_INCREMENTS);
 if (rampParms.isNull()) {
     return false;
 }
 QString a;
 if ((a = rampParms.attribute(TIME_INCREMENT)) != NULL) {
     bool bok;
         setTimeIncrement(a.toInt(&bok));
         if(!bok) {
         setTimeIncrement(750);
         Logger::error("Unable to read ramp time increment. Setting to default value (750ms).");
     }
 }
 if ((a = rampParms.attribute(RAMP_INCREMENT)) != NULL) {
     bool bok;
         setThrottleIncrement(a.toFloat(&bok));
         if(!bok) {
         setThrottleIncrement(0.05f);
         Logger::error("Unable to read ramp throttle increment. Setting to default value (0.05).");
     }
 }
 if ((a = rampParms.attribute(THROTTLE_SCALE)) != NULL) {
     bool bok;
         setThrottleScale(a.toFloat(&bok));
         if(!bok) {
         setThrottleScale(0.70f);
         Logger::error("Unable to read throttle scale. Setting to default value (0.70f).");
     }
 }

 rampParms = child.firstChildElement(SPEED_NAME_PREFS);
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
 if ((a = rampParms.attribute(INTERPRETATION)) != NULL) {
     bool bok;
         setInterpretation(a.toInt(&bok));
         if(!bok) {
         setInterpretation(1);
         Logger::error("Unable to read interpetation of Speed Map. Setting to default value % normal.");
     }
 }
 QMap<QString, float> map =  QMap<QString, float>();
 QDomNodeList list = rampParms.childNodes();
 for (int i = 0; i < list.size(); i++)
 {
     QString name = list.at(i).toElement().tagName();
     float speed = 0;
     bool bok;
         speed =  list.at(i).toElement().text().toFloat(&bok);
         if(!bok) {
         Logger::error(SPEED_NAME_PREFS+" has invalid content for "+name+" = "+list.at(i).toElement().text());
     }
     if (log->isDebugEnabled()) log->debug("Add "+name+", "+QString::number(speed)+" to AspectSpeed Table");
     map.insert(name, speed);
 }
 this->setSpeedNames(map);

 rampParms = child.firstChildElement(APPEARANCE_PREFS);
 if (rampParms.isNull()) {
     return false;
 }
 QMap<QString, QString> heads = QMap<QString, QString>();
 list = rampParms.childNodes();
 for (int i = 0; i < list.size(); i++) {
     QString name = (list.at(i).toElement().tagName());
     QString speed = list.at(i).toElement().text();
     heads.insert(name, speed);
 }
 this->setAppearances(heads);

 // Now set SignalSpeedMap members.
 SignalSpeedMap* speedMap = static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"));
 speedMap->setRampParams(_throttleIncr, _msIncrTime);
 speedMap->setDefaultThrottleFactor(_throttleScale);
 speedMap->setLayoutScale(_scale);
 speedMap->setAspects( QMap<QString, float>(this->_speedNames), _interpretation);
 speedMap->setAppearances( QMap<QString, QString>(this->_headAppearances));
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
  //Document doc = XmlFile.newDocument(root);
  doc  = QDomDocument("warrantPreferences");
  QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
  doc.appendChild(xmlProcessingInstruction);
  QDomElement root = doc.createElement("warrantPreferences");
  doc.appendChild(root);

  if (store(root))
  {
   xmlFile->writeXML(file, doc);
  }
 }
 catch (Exception eb)
 {
  log->warn("Exception in storing warrant xml: "/*+eb*/);
 }
}

/*public*/ bool WarrantPreferences::store(QDomElement root)
{
 QDomElement prefs = doc.createElement(LAYOUT_PARAMS);
 try
 {
  prefs.setAttribute(LAYOUT_SCALE, QString::number(getScale()));
  prefs.setAttribute(SEARCH_DEPTH, QString::number(getSearchDepth()));
  root.appendChild(prefs);

  prefs = doc.createElement(SPEED_MAP_PARAMS);
  QDomElement rampPrefs = doc.createElement(STEP_INCREMENTS);
  rampPrefs.setAttribute(TIME_INCREMENT, QString::number(getTimeIncrement()));
  rampPrefs.setAttribute(RAMP_INCREMENT, QString::number(getThrottleIncrement()));
  rampPrefs.setAttribute(THROTTLE_SCALE, QString::number(getThrottleScale()));
  prefs.appendChild(rampPrefs);

  rampPrefs = doc.createElement(SPEED_NAME_PREFS);
  rampPrefs.setAttribute(INTERPRETATION, QString::number(getInterpretation()));

  QMapIterator<QString, float>  it = getSpeedNameEntryIterator();
  while (it.hasNext())
  {
     // Entry<QString, float> ent = it.next();
   it.next();
      QDomElement step =  doc.createElement(it.key());
      step.appendChild(doc.createTextNode(QString::number(it.value())));
      rampPrefs.appendChild(step);
  }
  prefs.appendChild(rampPrefs);

  rampPrefs = doc.createElement(APPEARANCE_PREFS);
  QDomElement step =  doc.createElement("SignalHeadStateRed");
  step.appendChild(doc.createTextNode(_headAppearances.value(tr("SignalHeadStateRed"))));
  rampPrefs.appendChild(step);
  step =  doc.createElement("SignalHeadStateFlashingRed");
  step.appendChild(doc.createTextNode(_headAppearances.value(tr("SignalHeadStateFlashingRed"))));
  rampPrefs.appendChild(step);
  step =  doc.createElement("SignalHeadStateGreen");
  step.appendChild(doc.createTextNode(_headAppearances.value(tr("SignalHeadStateGreen"))));
  rampPrefs.appendChild(step);
  step =  doc.createElement("SignalHeadStateFlashingGreen");
  step.appendChild(doc.createTextNode(_headAppearances.value(tr("SignalHeadStateFlashingGreen"))));
  rampPrefs.appendChild(step);
  step =  doc.createElement("SignalHeadStateYellow");
  step.appendChild(doc.createTextNode(_headAppearances.value(tr("SignalHeadStateYellow"))));
  rampPrefs.appendChild(step);
  step =  doc.createElement("SignalHeadStateFlashingYellow");
  step.appendChild(doc.createTextNode(_headAppearances.value(tr("SignalHeadStateFlashingYellow"))));
  rampPrefs.appendChild(step);
  step =  doc.createElement("SignalHeadStateLunar");
  step.appendChild(doc.createTextNode(_headAppearances.value(tr("SignalHeadStateLunar"))));
  rampPrefs.appendChild(step);
  step =  doc.createElement("SignalHeadStateFlashingLunar");
  step.appendChild(doc.createTextNode(_headAppearances.value(tr("SignalHeadStateFlashingLunar"))));
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
 * @deprecated since 4.7.2 without replacement. Classes interested in
 * changes to the warrant preferences listen for those changes.
 */
//@Deprecated
/*public*/ void WarrantPreferences::apply() {
//    setSpeedMap();
//    setNXFrame();
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
///*private*/ void WarrantPreferences::setSpeedMap() {
//    SignalSpeedMap* map = new SignalSpeedMap();
//    map->setAspectTable(getSpeedNameEntryIterator(), _interpretation);
//    map->setAppearanceTable(getAppearanceEntryIterator());
//    map->setRampParams(_throttleIncr, _msIncrTime);
//    map->setDefaultThrottleFactor(_throttleScale);
//    map->setLayoutScale(_scale);
//    map->setMap(map);
//}

/**
 * @return the scale
 * @deprecated since 4.7.1; use {@link #getLayoutScale()} instead
 */
//@Deprecated
float WarrantPreferences::getScale() {
    return this->getLayoutScale();
}
/**
 * @param s the scale
 * @deprecated since 4.7.1; use {@link #setLayoutScale(float)} instead
 */
//@Deprecated
void WarrantPreferences::setScale(float s) {
    _scale = s;
}
/**
 * Get the layout scale.
 *
 * @return the scale
 */
/*public*/ float WarrantPreferences::getLayoutScale() {
    return _scale;
}

/**
 * Set the layout scale.
 *
 * @param scale the scale
 */
/*public*/ void WarrantPreferences::setLayoutScale(float scale) {
    float oldScale = this->_scale;
    _scale = scale;
    this->firePropertyChange(LAYOUT_SCALE, QVariant(oldScale), QVariant(scale));
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

int WarrantPreferences::getTimeIncrement() {
    return _msIncrTime;
}
void WarrantPreferences::setTimeIncrement(int t) {
    _msIncrTime = t;
}

float WarrantPreferences::getThrottleIncrement() {
    return _throttleIncr;
}
void WarrantPreferences::setThrottleIncrement(float ti) {
    _throttleIncr = ti;
}
//@Override
/*public*/ void WarrantPreferences::initialize(Profile* profile) throw (InitializationException)
{
    if (!this->isInitialized(profile) && !this->isInitializing(profile)) {
        this->setInitializing(profile, true);
        this->openFile(FileUtil::getUserFilesPath() + "signal" + File::separator + "WarrantPreferences.xml");
        this->setInitialized(profile, true);
    }
}
/*protected*/ void WarrantPreferences::setShutdown(Shutdown set) {
    _shutdown = set;
}
/*public*/ WarrantPreferences::Shutdown WarrantPreferences::getShutdown() {
    return _shutdown;
}

//@Override
/*public*/ void WarrantPreferences::savePreferences(Profile* profile) {
    this->save();
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

//@Nonnull
//@CheckReturnValue
/*public*/ QMap<QString, float> WarrantPreferences::getSpeedNames() {
    return QMap<QString, float>(this->_speedNames);
}

// Called when preferences is updated from panel
void WarrantPreferences::setSpeedNames(QMap<QString, float> map)
{
 _speedNames.clear();
 QMapIterator<QString, float>iter (map);
 while(iter.hasNext())
 {
  iter.next();
  _speedNames.insert(iter.key(),iter.value());
 }
}

// Called when preferences is updated from panel
/*protected*/ void WarrantPreferences::setSpeedNames(QList<QPair<QString, float>> speedNameMap) {
    QMap<QString, float> map = QMap<QString, float>();
    for (int i = 0; i < speedNameMap.size(); i++) {
        QPair<QString, float> dp = speedNameMap.at(i);
        map.insert(dp.first, dp.second);
    }
    QMap<QString, float> old = QMap<QString, float>(_speedNames);
    QVariantMap qvOld = QVariantMap();
    QMapIterator<QString, float> iter(_speedNames);
    while(iter.hasNext())
    {
     iter.next();
     qvOld.insert(iter.key(),iter.value());
    }
    this->setSpeedNames(map);
    QVariantMap qvMap = QVariantMap();
    QMapIterator<QString, float> iter1(_speedNames);
    while(iter1.hasNext())
    {
     iter1.next();
     qvMap.insert(iter1.key(),iter1.value());
    this->firePropertyChange(SPEED_NAMES, qvOld, qvMap);
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

/**
 * Get a map of signal head appearances.
 *
 * @return a map of appearances or an empty map if none are defined
 */
//@Nonnull
//@CheckReturnValue
/*public*/ QMap<QString, QString> WarrantPreferences::getAppearances() {
    return QMap<QString, QString>(this->_headAppearances);
}

// Only called directly at load time
/*private*/ void WarrantPreferences::setAppearances(QMap<QString, QString> map) {
    this->_headAppearances.clear();
    //this->_headAppearances.putAll(map);
  QMapIterator<QString, QString> iter(map);
  while(iter.hasNext())
  {
   iter.next();
   this->_headAppearances.insert(iter.key(), iter.value());
  }
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

