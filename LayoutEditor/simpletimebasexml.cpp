#include "simpletimebasexml.h"
#include "timebase.h"
#include "instancemanager.h"
#include "simpletimebase.h"

// Conversion format for dates created by Java Date.toString().
// The Locale needs to be always US, irrelevant from computer's and program's settings!
/*static*/ /*final*/ /*SimpleDateFormat*/ QString SimpleTimebaseXml::format =  "ddd MMM dd hh:mm:ss yyyy";

SimpleTimebaseXml::SimpleTimebaseXml(QObject *parent) :
    AbstractXmlAdapter(parent)
{
 log = new Logger("SimpleTimebaseXml");
 setObjectName("SimpleTimebaseXml");
}

SimpleTimebaseXml::~SimpleTimebaseXml()
{
 delete log;
}

/**
 * Handle XML persistance of SimpleTimebase objects
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003, 2008
 * @version $Revision: 18102 $
 */
///*public*/ class SimpleTimebaseXml extends jmri.configurexml.AbstractXmlAdapter {

//    /*public*/ SimpleTimebaseXml() {
//    }

/**
 * Default implementation for storing the contents of
 * a SimpleTimebase.
 * <P>
 *
 * @param o Object to start process, but not actually used
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement SimpleTimebaseXml::store(QObject* /*o*/) {

    Timebase* clock = static_cast<Timebase*>(InstanceManager::getDefault("Timebase"));

    QDomElement elem = doc.createElement("timebase");
    elem.setAttribute("class", /*getClass().getName()*/"jmri.jmrit.simpleclock.configurexml.SimpleTimebaseXml");

    if (!clock->getStartTime().isNull())
        elem.setAttribute("time", clock->getStartTime().toString());
    elem.setAttribute("rate", clock->userGetRate());
    elem.setAttribute("run", (!clock->getStartStopped()?"yes":"no"));
    elem.setAttribute("master", (clock->getInternalMaster()?"yes":"no"));
    if (!clock->getInternalMaster())
        elem.setAttribute("mastername",clock->getMasterName());
    elem.setAttribute("sync", (clock->getSynchronize()?"yes":"no"));
    elem.setAttribute("correct", (clock->getCorrectHardware()?"yes":"no"));
    elem.setAttribute("display", (clock->use12HourDisplay()?"yes":"no"));
    elem.setAttribute("startstopped", (clock->getStartStopped()?"yes":"no"));
    elem.setAttribute("startsettime", (clock->getStartSetTime()?"yes":"no"));
    elem.setAttribute("startclockoption",clock->getStartClockOption());

    return elem;
}

/**
 * Update static data from XML file
 * @param element Top level blocks QDomElement to unpack.
 * @return true if successful
  */
/*public*/ bool SimpleTimebaseXml::load(QDomElement element) throw (Exception)
{
 bool result = true;
 Timebase* clock = static_cast<Timebase*>(InstanceManager::getDefault("Timebase"));
 QString val,val2;
 if (element.attribute("master")!="")
 {
  val = element.attribute("master");
  if (val==("yes")) clock->setInternalMaster(true,false);
  if (val==("no"))
  {
   clock->setInternalMaster(false,false);
      if (element.attribute("mastername")!="")
    clock->setMasterName(element.attribute("mastername"));
  }
 }
 if (element.attribute("sync")!="")
 {
  val = element.attribute("sync");
  if (val==("yes")) clock->setSynchronize(true,false);
  if (val==("no")) clock->setSynchronize(false,false);
 }
 if (element.attribute("correct")!="")
 {
  val = element.attribute("correct");
  if (val==("yes")) clock->setCorrectHardware(true,false);
  if (val==("no")) clock->setCorrectHardware(false,false);
 }
 if (element.attribute("display")!="")
 {
  val = element.attribute("display");
  if (val==("yes")) clock->set12HourDisplay(true,false);
  if (val==("no")) clock->set12HourDisplay(false,false);
 }
 if (element.attribute("run")!="")
 {
  val = element.attribute("run");
  if (val==("yes"))
  {
   clock->setRun(true);
   clock->setStartStopped(false);
  }
  if (val==("no"))
  {
   clock->setRun(false);
   clock->setStartStopped(true);
  }
 }
 if (element.attribute("rate")!="")
 {
  //try {
  bool bOk;
  double r = element.attribute("rate").toDouble(&bOk);
  if(!bOk)
  {
   log->error("Cannot convert rate: "/*+e2*/);
   result = false;
  }
  else
   clock->userSetRate(r);
//   try {
//                clock->userSetRate(r);
//            } catch (jmri.TimebaseRateException e1) {
//                log->error("Cannot restore rate: "+r+" "+e1);
//                result = false;
//            }
//        } catch (org.jdom.DataConversionException e2) {
//            log->error("Cannot convert rate: "+e2);
//            result = false;
//        }
//    }
  }
  if (element.attribute("startsettime")!="")
  {
   val = element.attribute("startsettime");
   if (val==("yes"))
   {
    if (element.attribute("time")!="")
    {
     val2 = element.attribute("time");
     //try {
     QDateTime t = QDateTime::fromString(removeTimeZone(val2), format);
     if(t.isValid())
     {
      clock->setStartSetTime(true, t);
      clock->setTime(t);
     }
     //} catch(ParseException e) {
     else
     {
      // if non-invertable date format, just skip
      log->warn("Cannot set date using value stored in file: "+val2);
      result = false;
     }
    }
   }
   else if (val==("no"))
   {
    if (element.attribute("time")!="")
    {
     val2 = element.attribute("time");
     //try {
     QDateTime t = QDateTime::fromString(removeTimeZone(val2), format);
     log->debug("input datetime = " + t.toString());
     if(t.isValid())
      clock->setStartSetTime(false, t);
     //} catch(ParseException e) {
     else
    {
     // if non-invertable date format, just skip
     log->warn("Cannot set date using value stored in file: "+val2);
     result = false;
    }
   }
  }
 }
 else if (element.attribute("time")!="")
 {
  // this only to preserve previous behavior for preexisting files
  val2 = element.attribute("time");
  //try {
  QDateTime t = QDateTime::fromString(removeTimeZone(val2), format);
  if(t.isValid())
  {
   clock->setStartSetTime(true, t);
   clock->setTime(t);
  }
  else
  {
   //} catch (ParseException e) {
   // if non-invertable date format, just skip
   log->warn("Cannot set date using value stored in file: "+val2);
   result = false;
  }
 }
 if (element.attribute("startclockoption")!="")
 {
  bool bOk;
  int option = element.attribute("startclockoption").toInt(&bOk);
  clock->setStartClockOption(option);
  clock->initializeClock();
 }
 clock->initializeHardwareClock();
 return result;
}


/**
 * Update static data from XML file
 * @param element Top level QDomElement to unpack.
 * @param o  ignored
 */
/*public*/ void SimpleTimebaseXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    log->error("load(QDomElement, Object) called unexpectedly");
}

/*public*/ int SimpleTimebaseXml::loadOrder() const{
    return Manager::TIMEBASE;
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SimpleTimebaseXml.class.getName());

//}
/*private*/ QString SimpleTimebaseXml:: removeTimeZone(QString time)
{
 QStringList timezones =
   QStringList() << "EST " << "EDT " << "CDT " << "CST " << "MDT " << "MST " << "PDT " << "PST " << "CET " << "UTC ";
 foreach (QString tz, timezones)
 {
  if( time.contains(tz,Qt::CaseInsensitive))
  {
    QString newTime = time.remove(tz,Qt::CaseInsensitive);
    return newTime;
  }
 }
 return time;
}

