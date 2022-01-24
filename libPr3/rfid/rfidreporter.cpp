#include "rfidreporter.h"
#include "reportermanager.h"
#include "dcclocoaddress.h"
#include "instancemanager.h"
#include <QRegExp>
#include "abstractidtag.h"
#include "defaultidtag.h"
#include "rosterentry.h"

//RfidReporter::RfidReporter(QObject *parent) :
//    AbstractReporter(parent)
//{
//}
/**
 * Extend AbstractReporter for RFID systems
 * <P>
 * System names are "FRpppp", where ppp is a
 * representation of the RFID reader.
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author      Matthew Harris  Copyright (c) 2011
 * @version     $Revision: 22000 $
 * @since       2.11.4
 */
///*public*/ class RfidReporter extends AbstractReporter
//    implements RfidTagListener, PhysicalLocationReporter {

/*public*/ RfidReporter::RfidReporter(QString systemName, QObject *parent)
    : AbstractIdTagReporter(systemName, parent)
{
    //super(systemName);
//    init();
}

/*public*/ RfidReporter::RfidReporter(QString systemName, QString userName, QObject *parent)
    : AbstractIdTagReporter(systemName, userName, parent)
{
 //super(systemName, userName);
// init();
}
#if 0
void RfidReporter::init()
{
 log = new Logger("RfidReporter");
 state = PhysicalLocationReporter::UNKNOWN;

}

/*public*/ void RfidReporter::notify(DefaultIdTag* id)
{
 log->debug("Notify: "+this->mSystemName);
 if (id!=NULL)
 {
  log->debug("Tag: "+((AbstractIdTag*)id->self())->getDisplayName());
  RfidReporter* r;
  if ((r = (RfidReporter*) ((AbstractIdTag*)id->self())->getWhereLastSeen())!=NULL)
  {
   log->debug("Previous reporter: "+r->mSystemName);
   if (r!=this && r->getCurrentReport() == VPtr<DefaultIdTag>::asQVariant( id))
   {
    log->debug("Notify previous");
    r->notify(NULL);
   }
   else
   {
 // TODO:   log->debug(tr("Current report was: ")+ VPtr<IdTag*>::asPtr(r->getCurrentReport())->getDisplayName());
   }
  }
  ((DefaultIdTag*)id->self())->setWhereLastSeen((Reporter*)this);
  log->debug("Seen here: "+this->mSystemName);
 }
 setReport(VPtr<DefaultIdTag>::asQVariant(id));
 setState(id!=NULL?IdTag::SEEN:IdTag::UNSEEN);
}


/*public*/ void RfidReporter::setState(int s) {
    state = s;
}

/*public*/ int RfidReporter::getState() {
    return state;
}

// Methods to support PhysicalLocationReporter interface

/** getLocoAddress()
 *
 * get the locomotive address we're reporting about from the
 * current report.
 *
 * Note: We ignore the string passed in, because rfid Reporters
 * don't send QString type reports.
 */
/*public*/ LocoAddress* RfidReporter::getLocoAddress(QString /*rep*/)
{
 // For now, we assume the current report.
 // IdTag.getTagID() is a system-name-ized version of the loco address. I think.
 // Matcher.group(1) : loco address (I think)
    AbstractIdTag* cr = (AbstractIdTag*) VPtr<AbstractIdTag>::asPtr(this->getCurrentReport());
 ReporterManager* rm = qobject_cast<ReporterManager*>(InstanceManager::getDefault("ReporterManager"));
 //Pattern p = Pattern.compile(""+rm->getSystemPrefix()+rm->typeLetter()+"(\\d+)");
 //Matcher m = p.matcher(cr.getTagID());
 QRegExp regExp(rm->getSystemPrefix()+rm->typeLetter()+"(\\d+)");
 //if (m.find())

 if(regExp.exactMatch(cr->getTagID()))
 {
     QString sAddr = cr->getTagID().mid(regExp.pos());
    log->debug("Parsed address: " + /*m.group(1)*/sAddr);
    // I have no idea what kind of loco address an Ecos reporter uses,
    // so we'll default to DCC for now.
    //return(new DccLocoAddress(Integer.parseInt(m.group(1)), LocoAddress::DCC));
    bool bOk = false;
    return(new DccLocoAddress(sAddr.toInt(&bOk,16), LocoAddress::DCC));
 }
 else
 {
  return(NULL);
 }
}

/** getDirection()
 *
 * Gets the direction (ENTER/EXIT) of the report.  Because of the
 * way rfid Reporters work (or appear to), all reports are ENTER type.
 */
/*public*/ PhysicalLocationReporter::Direction RfidReporter::getDirection(QString /*rep*/)
{
// TEMPORARY:  Assume we're always Entering, if asked.
return(PhysicalLocationReporter::ENTER);
}

/** getPhysicalLocation()
 *
 * Returns the PhysicalLocation of the Reporter
 *
 * Reports its own location, for now.  Not sure if that's the right thing or not.
 * NOT DONE YET
 */
/*public*/ PhysicalLocation* RfidReporter::getPhysicalLocation()
{
return(this->getPhysicalLocation(NULL));
}

/** getPhysicalLocation(QString s)
 *
 * Returns the PhysicalLocation of the Reporter
 *
 * Does not use the parameter s
 */
/*public*/ PhysicalLocation* RfidReporter::getPhysicalLocation(QString /*s*/) {
return(PhysicalLocation::getBeanPhysicalLocation(this));
}

//    private static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(RfidReporter.class.getName());

//}
#endif
