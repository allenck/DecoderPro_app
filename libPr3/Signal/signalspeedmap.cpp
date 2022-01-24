#include "signalspeedmap.h"
#include <QDir>
#include "xmlfile.h"
#include "signalsystem.h"
#include "fileutil.h"
#include <QVector>
#include <QUrl>
#include "loggerfactory.h"
#include "warrantpreferences.h"
#include "propertychangeevent.h"
#include "instancemanager.h"

/*static*/ /*private*/ bool SignalSpeedMap::_percentNormal = false;
/*static*/ /*private*/ int SignalSpeedMap::_sStepDelay = 0;
/*static*/ /*private*/ int SignalSpeedMap::_numSteps =4;
/*static*/ /*private*/ int SignalSpeedMap::_interpretation = 0;
/*static*/ /*private*/ QMap<QString, float>* SignalSpeedMap::_table = new QMap<QString, float>();
/*static*/ /*private*/ QMap<QString, QString>* SignalSpeedMap::_headTable =  new QMap<QString, QString>();

SignalSpeedMap::SignalSpeedMap(QObject *parent) :
    Bean(parent)
{
 setProperty("InstanceManagerAutoDefault", "true");
 setProperty("InstanceManagerAutoInitialize", "true");

 loadMap();
// this.warrantPreferencesListener = (PropertyChangeEvent evt) -> {
//     WarrantPreferences preferences = WarrantPreferences.getDefault();
//     SignalSpeedMap map = SignalSpeedMap.this;
//     switch (evt.getPropertyName()) {
//         case WarrantPreferences.APPEARANCES:
//             map.setAppearances(preferences.getAppearances());
//             break;
//         case WarrantPreferences.LAYOUT_SCALE:
//             map.setLayoutScale(preferences.getLayoutScale());
//             break;
//         case WarrantPreferences.SPEED_NAMES:
//         case WarrantPreferences.INTERPRETATION:
//             map.setAspects(preferences.getSpeedNames(), preferences.getInterpretation());
//             break;
//         case WarrantPreferences.THROTTLE_SCALE:
//             map.setDefaultThrottleFactor(preferences.getThrottleScale());
//             break;
//         case WarrantPreferences.TIME_INCREMENT:
//         case WarrantPreferences.RAMP_INCREMENT:
//             map.setRampParams(preferences.getThrottleIncrement(), preferences.getTimeIncrement());
//             break;
//         default:
//         // ignore other properties
//     }
// };
 this->warrantPreferencesListener = new WarrantPreferencesListener(this);
}

//@Override
/*public*/ void SignalSpeedMap::initialize() {
 WarrantPreferences* wp = (WarrantPreferences*)
    InstanceManager::getOptionalDefault("WarrantPreferences");
 if(wp)
 {
  wp->addPropertyChangeListener(this->warrantPreferencesListener);
 }//);
//    InstanceManager.addPropertyChangeListener((PropertyChangeEvent evt) -> {
//        if (evt.getPropertyName().equals(InstanceManager.getDefaultsPropertyName(WarrantPreferences.class))) {
//            InstanceManager.getDefault(WarrantPreferences.class).addPropertyChangeListener(this.warrantPreferencesListener);
//        }
//    });
    InstanceManager::addPropertyChangeListener((PropertyChangeListener*)this);
}
void WarrantPreferencesListener::propertyChange(PropertyChangeEvent * evt)
{
     WarrantPreferences* preferences = WarrantPreferences::getDefault();
     //SignalSpeedMap map = SignalSpeedMap.this;
     QString propertyName = evt->getPropertyName();
     if(propertyName == WarrantPreferences::APPEARANCES)
       ssm->setAppearances(preferences->getAppearances());
     else if(propertyName ==  WarrantPreferences::LAYOUT_SCALE)
       ssm->setLayoutScale(preferences->getLayoutScale());
     else if(propertyName ==  WarrantPreferences::SPEED_NAMES || propertyName ==  WarrantPreferences::INTERPRETATION)
      ssm->setAspects(preferences->getSpeedNames(), preferences->getInterpretation());
     else if(propertyName ==   WarrantPreferences::THROTTLE_SCALE)
      ssm->setDefaultThrottleFactor(preferences->getThrottleScale());
      else if(propertyName ==  WarrantPreferences::TIME_INCREMENT ||
       propertyName ==  WarrantPreferences::RAMP_INCREMENT)
      ssm->setRampParams(preferences->getThrottleIncrement(), preferences->getTimeIncrement());
         // ignore other properties
}

/**
 * Default implementation to map Signal aspects or appearances to speed requirements.
 * <p>
 * A singleton class for use by all SignalHeads and SignalMasts
 *
 * @author	Pete Cressman Copyright (C) 2010
 * @version     $Revision: 22387 $
 */
///*public*/ class SignalSpeedMap {


void SignalSpeedMap::propertyChange(PropertyChangeEvent *evt)
{
 if (evt->getPropertyName()==(InstanceManager::getDefaultsPropertyName("WarrantPreferences")))
 {
  WarrantPreferences* wp = static_cast<WarrantPreferences*>(InstanceManager::getDefault("WarrantPreferences"));
wp->addPropertyChangeListener(warrantPreferencesListener);
 }
}
void SignalSpeedMap::loadMap()
{
 QStringList list = QStringList() << FileUtil::getProgramPath() + "" <<FileUtil::getProgramPath() + "xml/signals";
    QUrl path = FileUtil::findURL("signalSpeeds.xml", list);
    XmlFile* xf = new XmlFile();
    try {
        loadRoot(xf->rootFromURL(&path));
    }
    catch (FileNotFoundException* e)
    {
     log->warn(tr("signalSpeeds file (%1) doesn't exist in XmlFile search path.").arg(path.toString()));
        throw  IllegalArgumentException("signalSpeeds file (" + path.toDisplayString() + ") doesn't exist in XmlFile search path.");
    }
    catch (JDOMException*  e) {
     log->error(tr("error reading file \"%1\" due to: %2").arg(path.toDisplayString().arg(e->getMessage())));
    }
    catch (IOException* e) {
     log->error(tr("error reading file \"%1\" due to: %2").arg(path.toDisplayString().arg(e->getMessage())));
    }

}

/*public*/ void SignalSpeedMap::loadRoot(/*@Nonnull*/ QDomElement root) {
 try
 {
  QDomElement e = root.firstChildElement("interpretation");
  QString sval = e.text().toUpper();
  if(sval== "PERCENTNORMAL")
          _interpretation = PERCENT_NORMAL;
   else if(sval== "PERCENTTHROTTLE")
          _interpretation = PERCENT_THROTTLE;
   else
     throw new JDOMException("invalid content for interpretation: " + sval);

  log->debug(tr("_interpretation= %1").arg(_interpretation));

  e = root.firstChildElement("msPerIncrement");
  _sStepDelay = 1000;
  bool bok;
      _sStepDelay = e.text().toInt(&bok);
  if(!bok)
  {
      throw new JDOMException("invalid content for msPerIncrement: " + e.text());
  }
  if (_sStepDelay < 200)
  {
      _sStepDelay = 200;
      log->warn("\"msPerIncrement\" must be at least 200 milliseconds.");
  }
  log->debug(tr("_sStepDelay = %1").arg(_sStepDelay));

  e = root.firstChildElement("stepsPerIncrement");

  _numSteps = e.text().toInt(&bok);
  if(!bok)
  {
      throw  JDOMException("invalid content for stepsPerIncrement: " + e.text());
  }
  if (_numSteps < 1)
  {
      _numSteps = 1;
  }

  QDomNodeList list = root.firstChildElement("aspectSpeeds").childNodes();
  _table->clear();
  for (int i = 0; i < list.size(); i++)
  {
      QString name = list.at(i).toElement().tagName();
      float speed;
      bool bok;
          speed = list.at(i).toElement().text().toFloat(&bok);
      if(!bok)
      {
       log->error(tr("invalid content for %1 = %2").arg(name).arg(list.at(i).toElement().text()));
       throw  JDOMException("invalid content for " + name + " = " + list.at(i).toElement().text());
      }
      log->debug(tr("Add %1, %2 to AspectSpeed Table").arg(name).arg(speed));
      _table->insert(name, speed);
  }

  /*synchronized (this._headTable)*/ {
      _headTable->clear();
      QDomNodeList l = root.firstChildElement("appearanceSpeeds").childNodes();
      for (int i = 0; i < l.size(); i++)
      {
          QString name = l.at(i).toElement().tagName();
          QString speed = l.at(i).toElement().text();
          _headTable->insert((name), speed);
          log->debug(tr("Add %1=%2, %3 to AppearanceSpeed Table").arg(name).arg( (name)).arg(speed)); // TODO: expand 2nd name (appearanceSpeeds) parameter string
      }
  }
 }
 catch (JDOMException* e)
 {
  log->error(tr("error reading speed map elements due to: %1").arg(e->getMessage()));
 }
}

/*public*/ bool SignalSpeedMap::checkSpeed(QString name) {
    //return _table->value(name) != 0;
 return _table->contains(name);
}

/**
* @return speed from SignalMast Aspect name
*/
/*public*/ QString SignalSpeedMap::getAspectSpeed(QString aspect, SignalSystem* system) {
    if (log->isDebugEnabled()) log->debug("getAspectSpeed: aspect="+aspect+", speed="+
                                        system->getProperty(aspect, "speed").toString());
    return system->getProperty(aspect, "speed").toString();
}
/**
* @return speed from SignalMast Aspect name
*/
/*public*/ QString SignalSpeedMap::getAspectExitSpeed(QString aspect, SignalSystem* system) {
    if (log->isDebugEnabled()) log->debug("getAspectExitSpeed: aspect="+aspect+", speed2="+
                                        system->getProperty(aspect, "speed2").toString());
    return (QString)system->getProperty(aspect, "speed2").toString();
}
/**
* @return speed from SignalHead Appearance name
*/
/*public*/ QString SignalSpeedMap::getAppearanceSpeed(QString name) /*throw (NumberFormatException)*/ {
    if (log->isDebugEnabled()) log->debug("getAppearanceSpeed Appearance= "+name+
                                        ", speed="+_headTable->value(name));
    return _headTable->value(name);
}
/*public*/ QStringListIterator SignalSpeedMap::getAppearanceIterator() {
 return QStringListIterator(_headTable->keys());
}
/*public*/ QStringListIterator SignalSpeedMap::getSpeedIterator() {
 return _table->keys();
}

/*public*/ QVector<QString> SignalSpeedMap::getValidSpeedNames() {
   QListIterator<QString> e (_table->keys());
    QVector<QString> v =  QVector<QString>();
    while (e.hasNext()) {
        v.append(e.next());
    }
    return v;
}

/*public*/ float SignalSpeedMap::getSpeed(QString name)
{
 if ( !checkSpeed(name))
 {
  // not a valid aspect
  log->warn("attempting to set invalid speed: "+name);
  //java.util.Enumeration<String> e = _table->keys();
  throw new IllegalArgumentException("attempting to get speed from invalid name: \""+name + "\"");
 }
 float speed = _table->value(name);
 if (speed==0)
 {
  return 0.0f;
 }
 return speed;
}

/*public*/ QString SignalSpeedMap::getNamedSpeed(float speed){
    QListIterator<QString> e = _table->keys();
    while (e.hasNext()) {
        QString key = e.next();
        if(_table->value(key)==(speed)) {
            return key;
        }
    }
    return NULL;
}

/*public*/ bool SignalSpeedMap::isRatioOfNormalSpeed() {
    return _percentNormal;
}

/*public*/ int SignalSpeedMap::getInterpretation() {
    return _interpretation;
}

/*public*/ int SignalSpeedMap::getStepDelay() {
    return _sStepDelay;
}

/*public*/ float SignalSpeedMap::getStepIncrement() {
    return _stepIncrement;

}

/*public*/ void SignalSpeedMap::setAspects(/*@Nonnull*/ QMap<QString, float> map, int interpretation) {
        QMap<QString, float> oldMap = QMap<QString, float>(*this->_table);
        int oldInterpretation = this->_interpretation;
        this->_table->clear();
        //this->_table.putAll(map);
        QMapIterator<QString, float> iter(map);
        while(iter.hasNext())
        {
         iter.next();
         this->_table->insert(iter.key(),iter.value());
        }
        this->_interpretation = interpretation;
        if (interpretation != oldInterpretation) {
            this->firePropertyChange("interpretation", oldInterpretation, interpretation);
        }
        if (map != (oldMap))
        {
//         QMap<QString,QVariant> newMap = QMap<QString,float>(map);
//            this->firePropertyChange("aspects", oldMap,  newMap);
        }
    }

/*public*/ void SignalSpeedMap::setAspectTable(QMapIterator<QString, float> iter, int interpretation)
{
    _table = new  QMap<QString, float>();
    while (iter.hasNext() )
    {
        //Entry<String, Float> ent = iter.next();
     iter.next();
        _table->insert(iter.key(), iter.value());
    }
    _interpretation = interpretation;
}
/*public*/ void SignalSpeedMap::setAppearances(/*@Nonnull*/ QMap<QString, QString> map) {
 /*synchronized (this._headTable)*/ {
  QMap<QString, QString> old = QMap<QString, QString>(*_headTable);
  _headTable->clear();
  //_headTable.putAll(map);
  QMapIterator<QString, QString> iter(map);
  while(iter.hasNext())
  {
   iter.next();
   _headTable->insert(iter.key(), iter.value());
  }
  if (map != (old)) {
//                this->firePropertyChange("Appearances", old,  QMap<QString, QVariant>(*_headTable));
  }
 }
}
/*public*/ void SignalSpeedMap::setAppearanceTable(QMapIterator<QString, QString> iter) {
    _headTable =  new QMap<QString, QString>();
    while (iter.hasNext() )
    {
     iter.next();
     //Entry<String, String> ent = iter.next();
     _headTable->insert(iter.key(), iter.value());
    }
}
/*public*/ void SignalSpeedMap::setRampParams(float throttleIncr, int msIncrTime) {
    _sStepDelay = msIncrTime;
    _stepIncrement = throttleIncr;
}

/*public*/ void SignalSpeedMap::setDefaultThrottleFactor(float f) {
    _throttleFactor = f;
}
/*public*/ float SignalSpeedMap::getDefaultThrottleFactor() {
    return _throttleFactor;
}

/*public*/ void SignalSpeedMap::setLayoutScale(float s) {
    _scale = s;
}
/*public*/ float SignalSpeedMap::getLayoutScale() {
    return _scale;
}


/*static*/ /*private*/ /*final*/ Logger* SignalSpeedMap::log = LoggerFactory::getLogger("SignalSpeedMap");
