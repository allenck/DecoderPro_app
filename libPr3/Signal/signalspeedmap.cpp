#include "signalspeedmap.h"
#include <QDir>
#include "xmlfile.h"
#include "signalsystem.h"
#include "fileutil.h"
#include <QVector>

/*static*/ /*private*/ SignalSpeedMap* SignalSpeedMap::_map = NULL;
/*static*/ /*private*/ bool SignalSpeedMap::_percentNormal = false;
/*static*/ /*private*/ int SignalSpeedMap::_sStepDelay = 0;
/*static*/ /*private*/ int SignalSpeedMap::_numSteps =4;
/*static*/ /*private*/ int SignalSpeedMap::_interpretation = 0;
/*static*/ /*private*/ QMap<QString, float>* SignalSpeedMap::_table = NULL; //  QMap<QString, float>();
/*static*/ /*private*/ QMap<QString, QString>* SignalSpeedMap::_headTable = NULL; //QMap<QString, QString>();

SignalSpeedMap::SignalSpeedMap(QObject *parent) :
    QObject(parent)
{
 log = new Logger("SignalSpeedMap");
 _stepIncrement = 0.04f;       // ramp step throttle increment
 _throttleFactor = 0.75f;

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


/*static*/ /*public*/ SignalSpeedMap* SignalSpeedMap::getMap()
{
    if(_table == NULL)
     _table = new QMap<QString, float>();
    if(_headTable == NULL)
     _headTable = new QMap<QString, QString>();
    if (_map == NULL) {

        loadMap();
    }
    return _map;
}

/*static*/ void SignalSpeedMap::loadMap() {
 Logger* log = new Logger("SignalSpeedMap");
 _map = new SignalSpeedMap();

 QString path = FileUtil::getProgramPath()+QString("xml") + QDir::separator()
   + "signals" + QDir::separator()
   + "signalSpeeds.xml";
 XmlFile* xf = new XmlFile();
 QDomElement root;
 try {
  root = xf->rootFromName(path);
  log->debug("root = "+ root.tagName()+ " name = "+root.attribute("name"));
  QDomElement e = root.firstChildElement("interpretation");
  QString sval = e.text().toUpper();
  if (sval==("PERCENTNORMAL")) {
   _percentNormal = true;
  }
  else if (sval==("PERCENTTHROTTLE")) {
   _percentNormal = false;
  }
  else {
   throw new JDOMException("invalid content for interpretation: "+sval);
  }
  if (log->isDebugEnabled()) log->debug("_percentNormal "+_percentNormal);

  e = root.firstChildElement("msPerIncrement");
  _sStepDelay = 250;
  try {
   _sStepDelay = e.text().toInt();
  } catch (NumberFormatException nfe) {
   throw new JDOMException("invalid content for msPerIncrement: "+e.text());
  }
  if (_sStepDelay < 200) {
   _sStepDelay = 200;
   log->warn("\"msPerIncrement\" must be at lewast 200 milliseconds.");
  }
  if (log->isDebugEnabled()) log->debug("_sStepDelay = "+_sStepDelay);

  e = root.firstChildElement("stepsPerIncrement");
  _numSteps = 1;
  try {
   _numSteps = e.text().toInt();
  } catch (NumberFormatException nfe) {
   throw new JDOMException("invalid content for msPerIncrement: "+e.text());
  }
  if (_numSteps < 1) {
   _numSteps = 1;
  }
  if (log->isDebugEnabled()) log->debug("_numSteps = "+_numSteps);

  //@SuppressWarnings("unchecked")
  QDomNodeList list = root.firstChildElement("aspectSpeeds").childNodes();
  for (int i = 0; i < list.size(); i++) {
   QString name = list.at(i).toElement().tagName();
   float speed = 0.0;
   try {
    speed = list.at(i).toElement().text().toFloat();
   } catch (NumberFormatException nfe) {
    log->error("invalid content for "+name+" = "+list.at(i).toElement().text());
    throw new JDOMException("invalid content for "+name+" = "+list.at(i).toElement().text());
   }
   if (log->isDebugEnabled()) log->debug("Add "+name+", "+speed+" to AspectSpeed Table");
   _table->insert(name, speed);
  }

  //@SuppressWarnings("unchecked")
  QDomNodeList l = root.firstChildElement("appearanceSpeeds").childNodes();
  for (int i = 0; i < l.size(); i++) {
   QString name = l.at(i).toElement().tagName();
   QString speed = l.at(i).toElement().text();
   _headTable->insert((name), speed);
   if (log->isDebugEnabled()) log->debug("Add "+name+"="+(name)+", "+speed+" to AppearanceSpeed Table");
  }
 } catch (JDOMException e) {
  log->error("error reading file \"" + path + "\" due to: " + e.getMessage());
 } catch (FileNotFoundException e) {
  log->error("signalSpeeds file (" + path + ") doesn't exist in XmlFile search path.");
  throw new IllegalArgumentException("signalSpeeds file (" + path + ") doesn't exist in XmlFile search path.");
 } catch (IOException ioe) {
  log->error("error reading file \"" + path + "\" due to: " + ioe.getMessage());
 }
}

/*public*/ bool SignalSpeedMap::checkSpeed(QString name) {
    return _table->value(name) != 0;
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
/*public*/ QString SignalSpeedMap::getAppearanceSpeed(QString name) throw (NumberFormatException) {
    if (log->isDebugEnabled()) log->debug("getAppearanceSpeed Appearance= "+name+
                                        ", speed="+_headTable->value(name));
    return _headTable->value(name);
}
/*public*/ QStringListIterator SignalSpeedMap::getAppearanceIterator() {
 return _headTable->keys();
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
  //throw new IllegalArgumentException("attempting to get speed from invalid name: "+name);
 }
 float speed = _table->value(name);
 if (speed==NULL)
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
/*public*/ int SignalSpeedMap::getNumSteps() {
    return _numSteps;
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

/*public*/ void SignalSpeedMap::setMap(SignalSpeedMap* map) {
    _map = map;
}
