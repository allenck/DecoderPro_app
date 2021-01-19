#include "abstractaudiomanagerconfigxml.h"
#include "instancemanager.h"
#include "fileutil.h"
#include "audiosource.h"
#include "audiomanager.h"

AbstractAudioManagerConfigXML::AbstractAudioManagerConfigXML(QObject *parent) :
  AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("AbstractAudioManagerConfigXML");
}
/**
 * Provides the abstract base and store functionality for configuring
 * AudioManagers, working with AbstractAudioManagers.
 * <P>
 * Typically, a subclass will just implement the load(QDomElement audio) class,
 * relying on implementation here to load the individual Audio objects. Note
 * that these are stored explicitly, so the resolution mechanism doesn't need to
 * see *Xml classes for each specific Audio or AbstractAudio subclass at store
 * time.
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002, 2008
 * @author Matthew Harris copyright (c) 2009, 2011
 * @version $Revision: 28746 $
 */
// /*public*/ abstract class AbstractAudioManagerConfigXML extends AbstractNamedBeanManagerConfigXML {

/**
 * Default constructor
 */
///*public*/ AbstractAudioManagerConfigXML() {
//}

/**
 * Default implementation for storing the contents of a AudioManager
 *
 * @param o Object to store, of type AudioManager
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/ QDomElement AbstractAudioManagerConfigXML::store(QObject* o)
{
 QDomElement audio = doc.createElement("audio");
 setStoreElementClass(audio);
 AudioManager* am = (AudioManager*) o;
 if (am != NULL)
 {
  QSet<NamedBean*> audioList = ((AbstractManager*)am)->getNamedBeanSet();
  // don't return an element if there are no audios to include
  if (audioList.isEmpty()) {
      return QDomElement();
  }
  // also, don't store if we don't have any Sources or Buffers
  // (no need to store the automatically created Listener object by itself)
  if (am->getNamedBeanSet(QChar(Audio::SOURCE)).isEmpty()
          && am->getNamedBeanSet(QChar(Audio::BUFFER)).isEmpty()) {
      return QDomElement();
  }
  // finally, don't store if the only Sources and Buffers are for the
  // virtual sound decoder (VSD)
  int vsdObjectCount = 0;

  // count all VSD objects
  for (NamedBean* nb : audioList)
  {
   Audio* a = (Audio*)nb;
   QString aName = a->getSystemName();
   log->debug(tr("Check if %1 is a VSD object").arg(aName));
   if (aName.length() >= 8 && aName.mid(3, 8).toUpper() == ("$VSD:")) {
       log->debug("...yes");
       vsdObjectCount++;
   }
  }

  if (log->isDebugEnabled())
  {
   log->debug("Found " + QString::number(vsdObjectCount) + " VSD objects of "
              + am->getSystemNameList(Audio::SOURCE).size()
              + am->getSystemNameList(Audio::BUFFER).size()
              + " objects");
  }

  // check if the total number of Sources and Buffers is equal to
  // the number of VSD objects - if so, exit.
  if (am->getSystemNameList(Audio::SOURCE).size()
      + am->getSystemNameList(Audio::BUFFER).size() == vsdObjectCount) {
   log->debug("Only VSD objects - nothing to store");
   return QDomElement();
  }

  // store global information
  audio.setAttribute("distanceattenuated",
                     am->getActiveAudioFactory()->isDistanceAttenuated() ? "yes" : "no");

  // store the audios
  for (NamedBean* nb : audioList)
  {
   Audio* a = (Audio*)nb;
   QString sname = a->getSystemName();
   if (sname.isNull())
   {
    log->error("System name NULL during store");
    continue;
   }
   if (log->isDebugEnabled())
   {
    log->debug("system name is " + sname);
   }

   if (sname.length() >= 8 && sname.mid(3, 8)==("$VSD:"))
   {
    if (log->isDebugEnabled()) {
     log->debug("Skipping storage of VSD object " + sname);
    }
    continue;
   }

   a = am->getBySystemName(sname);

   // Transient objects for current element and any children
   QDomElement e = QDomElement();
   QDomElement ce = QDomElement();

   QChar type = a->getSubType();
   if (type == Audio::BUFFER)
   {
    AudioBuffer* ab = (AudioBuffer*) a;
    e = doc.createElement("audiobuffer");
    //e.setAttribute("systemName", sname);
    QDomElement e1;
    e.appendChild(e1=doc.createElement("systemName"));
     e1.appendChild(doc.createTextNode(sname));

    // store common part
    storeCommon(ab, e);

    // store sub-type specific data
    ce = doc.createElement("url");
    ce.appendChild(doc.createTextNode(FileUtil::getPortableFilename(ab->getURL())));
    e.appendChild(ce);

    ce = doc.createElement("looppoint");
    ce.setAttribute("start", (int)ab->getStartLoopPoint());
    ce.setAttribute("end", (int)ab->getEndLoopPoint());
    e.appendChild(ce);

    ce = doc.createElement("streamed");
    ce.appendChild(doc.createTextNode(ab->isStreamed() ? "yes" : "no"));
    e.appendChild(ce);
   }
   else if (type == Audio::LISTENER)
   {
    AudioListener* al = (AudioListener*) a;
    e = doc.createElement("audiolistener");
    //e.setAttribute("systemName", sname);
    QDomElement e1;
    e.appendChild(e1=doc.createElement("systemName"));
     e1.appendChild(doc.createTextNode(sname));

    // store common part
    storeCommon(al, e);

    // store sub-type specific data
    ce = doc.createElement("position");
    ce.setAttribute("x", al->getPosition().x());
    ce.setAttribute("y", al->getPosition().y());
    ce.setAttribute("z", al->getPosition().z());
    e.appendChild(ce);

    ce = doc.createElement("velocity");
    ce.setAttribute("x", al->getVelocity().x());
    ce.setAttribute("y", al->getVelocity().y());
    ce.setAttribute("z", al->getVelocity().z());
    e.appendChild(ce);

    ce = doc.createElement("orientation");
    ce.setAttribute("atX", al->getOrientation(Audio::AT).x());
    ce.setAttribute("atY", al->getOrientation(Audio::AT).y());
    ce.setAttribute("atZ", al->getOrientation(Audio::AT).z());
    ce.setAttribute("upX", al->getOrientation(Audio::UP).x());
    ce.setAttribute("upY", al->getOrientation(Audio::UP).y());
    ce.setAttribute("upZ", al->getOrientation(Audio::UP).z());
    e.appendChild(ce);

    ce = doc.createElement("gain");
    ce.appendChild(doc.createTextNode(QString::number(al->getGain())));
    e.appendChild(ce);

    ce = doc.createElement("metersperunit");
    ce.appendChild(doc.createTextNode(QString::number(al->getMetersPerUnit())));
    e.appendChild(ce);
   }
   else if (type == Audio::SOURCE)
   {
    AudioSource* as = (AudioSource*) a;
    e = doc.createElement("audiosource");
    //e.setAttribute("systemName", sname);
    QDomElement e1;
    e.appendChild(e1=doc.createElement("systemName"));
     e1.appendChild(doc.createTextNode(sname));

    // store common part
    storeCommon((NamedBean*)as, e);

    // store sub-type specific data
    ce = doc.createElement("position");
    ce.setAttribute("x", QString::number(as->getPosition().x()));
    ce.setAttribute("y", as->getPosition().y());
    ce.setAttribute("z", as->getPosition().z());
    e.appendChild(ce);

    ce = doc.createElement("velocity");
    ce.setAttribute("x", as->getVelocity().x());
    ce.setAttribute("y", as->getVelocity().y());
    ce.setAttribute("z", as->getVelocity().z());
    e.appendChild(ce);

    ce = doc.createElement("assignedbuffer");
    if (as->getAssignedBuffer() != NULL)
    {
     ce.appendChild(doc.createTextNode(as->getAssignedBufferName()));
    }
    e.appendChild(ce);

    ce = doc.createElement("gain");
    ce.appendChild(doc.createTextNode(QString::number(as->getGain())));
    e.appendChild(ce);

    ce = doc.createElement("pitch");
    ce.appendChild(doc.createTextNode(QString::number( as->getPitch())));
    e.appendChild(ce);

    ce = doc.createElement("distances");
    ce.setAttribute("ref", QString::number(as->getReferenceDistance()));
    float f;
    if ((f = as->getMaximumDistance()) != Audio::MAX_DISTANCE)
    {
     ce.setAttribute("max", QString::number(f));
    }
    e.appendChild(ce);

    ce = doc.createElement("loops");
    ce.setAttribute("min", as->getMinLoops());
    ce.setAttribute("max", as->getMaxLoops());
    //                    ce.setAttribute("mindelay", ""+as->getMinLoopDelay());
    //                    ce.setAttribute("maxdelay", ""+as->getMaxLoopDelay());
    e.appendChild(ce);

    ce = doc.createElement("fadetimes");
    ce.setAttribute("in",  as->getFadeIn());
    ce.setAttribute("out", as->getFadeOut());
    e.appendChild(ce);

    ce = doc.createElement("dopplerfactor");
    ce.appendChild(doc.createTextNode(QString::number(as->getDopplerFactor())));
    e.appendChild(ce);

    ce = doc.createElement("positionrelative");
    ce.appendChild(doc.createTextNode(as->isPositionRelative() ? "yes" : "no"));
    e.appendChild(ce);
   }

   log->debug("store Audio " + sname);
   audio.appendChild(e);

  }
 }
 return audio;
}

/**
 * Subclass provides implementation to create the correct top element,
 * including the type information. Default implementation is to use the
 * local class here.
 *
 * @param audio The top-level element being created
 */
/*abstract*/ /*public*/ void AbstractAudioManagerConfigXML::setStoreElementClass(QDomElement /*audio*/) {}

//@Override
/*public*/ void AbstractAudioManagerConfigXML::load(QDomElement /*element*/, QObject* /*o*/)  throw (Exception)
{
 log->error("Invalid method called");
}

/**
 * Create a AudioManager object of the correct class, then register and fill
 * it.
 *
 * @param audio Top level QDomElement to unpack.
 * @return true if successful
 */
//@Override
/*abstract*/ /*public*/ bool AbstractAudioManagerConfigXML::load(QDomElement /*audio*/) throw (Exception){return false;}

/**
 * Utility method to load the individual Audio objects. If there's no
 * additional info needed for a specific Audio type, invoke this with the
 * parent of the set of Audio elements.
 *
 * @param audio QDomElement containing the Audio elements to load.
 */
//@SuppressWarnings("unchecked")
/*public*/ void AbstractAudioManagerConfigXML::loadAudio(QDomElement audio)
{

 AudioManager* am = (AudioManager*)InstanceManager::getDefault("AudioManager");

 // Count number of loaded Audio objects
 int loadedObjects = 0;

 // Load buffers first
 QDomNodeList audioList = audio.elementsByTagName("audiobuffer");
 if (log->isDebugEnabled()) {
  log->debug("Found " + QString::number(audioList.size()) + " Audio Buffer objects");
 }

 for (int i = 0; i < audioList.size(); i++)
 {
  QDomElement e = audioList.at(i).toElement();

  QString sysName = getSystemName(e);
  if (sysName == NULL) {
   log->warn("unexpected NULL in systemName " + (e.tagName()) + " "/* + (e).attributes()*/);
   break;
  }

  QString userName = getUserName(e);

  if (log->isDebugEnabled()) {
   log->debug("create Audio: (" + sysName + ")(" + (userName == NULL ? "<NULL>" : userName) + ")");
  }
  try
  {
   AudioBuffer* ab = (AudioBuffer*) am->newAudio(sysName, userName);

   // load common parts
   loadCommon(ab, e);

   // load sub-type specific parts
   // Transient objects for reading child elements
   QDomElement ce;
   QString value;

   if ((ce = e.firstChildElement("url")) != QDomElement()) {
    ab->setURL(ce.text());
   }

   if ((ce = e.firstChildElement("looppoint")) != QDomElement())
   {
    if ((value = ce.attribute("start")) != NULL) {
     ab->setStartLoopPoint((value).toInt());
    }
    if ((value = ce.attribute("end")) != NULL) {
     ab->setEndLoopPoint((value).toInt());
    }
   }

   if ((ce = e.firstChildElement("streamed")) != QDomElement()) {
    ab->setStreamed(ce.text()==("yes"));
   }

  }
  catch (AudioException ex)
  {
   log->error("Error loading AudioBuffer (" + sysName + "): " + ex.getMessage());
  }
 }
 loadedObjects += audioList.size();

 // Now load sources
 audioList = audio.elementsByTagName("audiosource");
 if (log->isDebugEnabled())
 {
  log->debug("Found " + QString::number(audioList.size()) + " Audio Source objects");
 }

 for (int i = 0; i < audioList.size(); i++)
 {
  QDomElement e = audioList.at(i).toElement();

  QString sysName = getSystemName(e);
  if (sysName == NULL)
  {
   log->warn("unexpected NULL in systemName " + (e.tagName()) + " " /*+ (e).attributes()*/);
   break;
  }

  QString userName = getUserName(e);

  if (log->isDebugEnabled())
  {
   log->debug("create Audio: (" + sysName + ")(" + (userName == NULL ? "<NULL>" : userName) + ")");
  }
  try
  {
   AudioSource* as = (AudioSource*) am->newAudio(sysName, userName);

   // load common parts
   loadCommon(as, e);

   // load sub-type specific parts
   // Transient objects for reading child elements
   QDomElement ce;
   QString value;

   if (!(ce = e.firstChildElement("position")) .isNull())
   {
    as->setPosition(
       QVector3D(
        (ce.attribute("x").toFloat()),
        (ce.attribute("y").toFloat()),
        (ce.attribute("z").toFloat())));
   }

   if (!(ce = e.firstChildElement("velocity")) .isNull()) {
    as->setVelocity(
       QVector3D(
        (ce.attribute("x").toFloat()),
        (ce.attribute("y").toFloat()),
        (ce.attribute("z").toFloat())));
   }

   if (!(ce = e.firstChildElement("assignedbuffer")) .isNull())
   {
    if (ce.text().length() != 0 && !ce.isNull()) {
     as->setAssignedBuffer(ce.text());
    }
   }

   if ((ce = e.firstChildElement("gain")) != QDomElement() && ce.text().length() != 0) {
    as->setGain((ce.text().toFloat()));
   }

   if ((ce = e.firstChildElement("pitch")) != QDomElement() && ce.text().length() != 0) {
    as->setPitch((ce.text().toFloat()));
   }

   if ((ce = e.firstChildElement("distances")) != QDomElement())
   {
    if ((value = ce.attribute("ref")) != NULL) {
     as->setReferenceDistance((value.toFloat()));
    }
    if ((value = ce.attribute("max")) != NULL) {
     as->setMaximumDistance((value.toFloat()));
    }
   }

   if ((ce = e.firstChildElement("loops")) != QDomElement())
   {
    if ((value = ce.attribute("min")) != NULL)
    {
     as->setMinLoops((value).toInt());
    }
    if ((value = ce.attribute("max")) != NULL)
    {
     as->setMaxLoops((value).toInt());
    }
    //                    if ((value = ce.attribute("mindelay"))!=NULL)
    //                        as->setMinLoopDelay(Integer.parseInt(value));
    //                    if ((value = ce.attribute("maxdelay"))!=NULL)
    //                        as->setMaxLoopDelay(Integer.parseInt(value));
   }

   if ((ce = e.firstChildElement("fadetimes")) != QDomElement()) {
    if ((value = ce.attribute("in")) != NULL) {
     as->setFadeIn((value).toInt());
    }
    if ((value = ce.attribute("out")) != NULL) {
     as->setFadeOut((value).toInt());
    }
   }

   if ((ce = e.firstChildElement("dopplerfactor")) != QDomElement() && ce.text().length() != 0) {
    as->setDopplerFactor((ce.text().toFloat()));
   }

   if ((ce = e.firstChildElement("positionrelative")) != QDomElement()) {
    as->setPositionRelative(ce.text()==("yes"));
   }

  } catch (AudioException ex) {
   log->error("Error loading AudioSource (" + sysName + "): " + ex.getMessage());
  }
 }
 loadedObjects += audioList.size();

 // Finally, load Listeners if needed
 if (loadedObjects > 0) {
  audioList = audio.elementsByTagName("audiolistener");
  if (log->isDebugEnabled()) {
   log->debug("Found " + QString::number(audioList.size()) + " Audio Listener objects");
  }

  for (int i = 0; i < audioList.size(); i++) {
   QDomElement e = audioList.at(i).toElement();

   QString sysName = getSystemName(e);
   if (sysName == NULL) {
    log->warn("unexpected NULL in systemName " + (e.tagName()) + " " /*+ (e).attributes()*/);
    break;
   }

   QString userName = getUserName(e);

   if (log->isDebugEnabled()) {
    log->debug("create Audio: (" + sysName + ")(" + (userName == NULL ? "<NULL>" : userName) + ")");
   }
   try {
    AudioListener* al = (AudioListener*) am->newAudio(sysName, userName);

    // load common parts
    loadCommon(al, e);

    // load sub-type specific parts
    // Transient object for reading child elements
    QDomElement ce;

    if ((ce = e.firstChildElement("position")) != QDomElement()) {
     al->setPosition(
        QVector3D(
         (ce.attribute("x").toFloat()),
         (ce.attribute("y").toFloat()),
         (ce.attribute("z").toFloat())));
    }

    if ((ce = e.firstChildElement("velocity")) != QDomElement()) {
     al->setVelocity(
        QVector3D(
         (ce.attribute("x").toFloat()),
         (ce.attribute("y").toFloat()),
         (ce.attribute("z").toFloat())));
    }

    if ((ce = e.firstChildElement("orientation")) != QDomElement()) {
     al->setOrientation(
        QVector3D(
         (ce.attribute("atX").toFloat()),
         (ce.attribute("atY").toFloat()),
         (ce.attribute("atZ").toFloat())),
        QVector3D(
         (ce.attribute("upX").toFloat()),
         (ce.attribute("upY").toFloat()),
         (ce.attribute("upZ").toFloat())));
    }

    if ((ce = e.firstChildElement("gain")) != QDomElement()) {
     al->setGain((ce.text().toFloat()));
    }

    if ((ce = e.firstChildElement("metersperunit")) != QDomElement()) {
     al->setMetersPerUnit(((ce.text().toFloat())));
    }

   } catch (AudioException ex) {
    log->error("Error loading AudioListener (" + sysName + "): " + ex.getMessage());
   }
  }
  QString a;
  if ((a = audio.attribute("distanceattenuated")) != NULL) {
   am->getActiveAudioFactory()->setDistanceAttenuated(a==("yes"));
  }
 }
}

//@Override
/*public*/ int AbstractAudioManagerConfigXML::loadOrder() const {
 return ((AudioManager*)InstanceManager::getDefault("AudioManager"))->getXMLOrder();
}
