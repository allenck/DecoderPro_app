#include "abstractidtagreporter.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "reportermanager.h"
#include "matcher.h"
#include "QRegExp"
#include "vptr.h"
#include "rfid/transpondingtag.h"

/**
 * Extend AbstractReporter for IdTag reporters
 * <p>
 * This file is based on @{link jmri.jmrix.rfid.RfidReporter}
 *
 * @author Matthew Harris Copyright (c) 2011
 * @author Paul Bender Copyright (c) 2016, 2019
 * @since 4.15.3
 */
// /*public*/ class AbstractIdTagReporter extends AbstractReporter
//        implements IdTagListener, PhysicalLocationReporter {

/*public*/ AbstractIdTagReporter::AbstractIdTagReporter(QString systemName, QObject* parent) : AbstractReporter(systemName, parent){
    //super(systemName);
}

/*public*/ AbstractIdTagReporter::AbstractIdTagReporter(QString systemName, QString userName, QObject* parent) :AbstractReporter(systemName, userName, parent) {
    //super(systemName, userName);
}
#if 0
//@Override
/*public*/ void AbstractIdTagReporter::notify(DefaultIdTag* id)
{
 log->debug(tr("Notify: %1").arg(mSystemName));
 if (id != nullptr)
 {
  log->debug(tr("Tag: %1").arg(id->toString()));
  AbstractIdTagReporter* r;
  if ((r = (AbstractIdTagReporter*) id->getWhereLastSeen()) != nullptr)
  {
   log->debug(tr("Previous reporter: %1").arg(r->mSystemName));
   if (!(r->equals(this)) && r->getCurrentReport() == id->toString()) {
       log->debug("Notify previous");
       r->notify(nullptr);
   } else {
       log->debug(tr("Current report was: %1").arg(r->getCurrentReport().toString()));
   }
  }
  id->setWhereLastSeen(this);
  log->debug(tr("Seen here: %1").arg(this->mSystemName));
 }
 setReport(VPtr<TranspondingTag>::asQVariant((TranspondingTag*)id->self()));
 setState(id != nullptr ? IdTag::SEEN : IdTag::UNSEEN);
}
#endif
/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void AbstractIdTagReporter::notify(IdTag* id) {
    log->debug(tr("Notify: %1").arg(mSystemName));
    if (id != nullptr) {
        log->debug(tr("Tag: %1").arg(id->toString()));
        Reporter* r = id->getWhereLastSeen();
        if (r != nullptr) {
            notifyPreviousReporter(r,id);
        }
        id->setWhereLastSeen(this);
        log->debug(tr("Seen here: %1").arg(this->mSystemName));
    }
    setReport(VPtr<IdTag>::asQVariant(id));
    setState(id != nullptr ? IdTag::SEEN : IdTag::UNSEEN);
}

/*private*/ void AbstractIdTagReporter::notifyPreviousReporter(Reporter* r, IdTag* id) {
        log->debug(tr("Previous reporter: %1").arg(((NamedBean*)r->self())->getSystemName()));
        if ((r->self()!=(this)) && r->getCurrentReport() == VPtr<IdTag>::asQVariant(id)
           && (qobject_cast<IdTagListener*>(r->self()))) {
            log->debug("Notify previous");
            ((IdTagListener*)r)->notify(nullptr);
        } else {
            log->debug(tr("Current report was: %1").arg(r->getCurrentReport().toString()));
        }
    }

//@Override
/*public*/ void AbstractIdTagReporter::setState(int s) {
    state = s;
}

//@Override
/*public*/ int AbstractIdTagReporter::getState() {
    return state;
}

// Methods to support PhysicalLocationReporter interface
/**
 * getLocoAddress()
 *
 * get the locomotive address we're reporting about from the current report.
 *
 * Note: We ignore the string passed in, because IdTag Reporters don't send
 * String type reports.
 */
//@Override
/*public*/ LocoAddress* AbstractIdTagReporter::getLocoAddress(QString rep) {
    // For now, we assume the current report.
    // IdTag.getTagID() is a system-name-ized version of the loco address. I think.
    // Matcher.group(1) : loco address (I think)
    IdTag* cr = VPtr<IdTag>::asPtr( this->getCurrentReport());
    ReporterManager* rm = (ReporterManager*)InstanceManager::getDefault("ReporterManager");
#if 0 // ToDo:
    Pattern p = Pattern::compile("" + rm->getSystemPrefix() + rm->typeLetter() + "(\\d+)");
    Matcher m = p.matcher(cr->getTagID());
    if (m.find()) {
        if(log->isDebugEnabled()) {
            log->debug(tr("Parsed address: %1").arg(m->group(1)));
        }
        // I have no idea what kind of loco address an Ecos reporter uses,
        // so we'll default to DCC for now.
        return (new DccLocoAddress(m->group(1).toInt()), LocoAddress::Protocol::DCC);
    } else {
        return (nullptr);
    }
#else
    QRegExp regExp = QRegExp("" + rm->getSystemPrefix() + rm->typeLetter() + "(\\d+)");
    QStringList groups = cr->getTagID().split(regExp);
    if(groups.size() > 0)
    {
     if(log->isDebugEnabled()) {
         log->debug(tr("Parsed address: %1").arg(groups.at(1)));
     }
     // I have no idea what kind of loco address an Ecos reporter uses,
     // so we'll default to DCC for now.
     return (new DccLocoAddress(groups.at(1).toInt(), LocoAddress::Protocol::DCC));

    }
    return nullptr;
#endif
}

/**
 * getDirection()
 *
 * Gets the direction (ENTER/EXIT) of the report. Because of the way
 * IdTag Reporters work, all reports are ENTER type.
 */
//@Override
/*public*/ PhysicalLocationReporter::Direction AbstractIdTagReporter:: getDirection(QString rep) {
    // TEMPORARY:  Assume we're always Entering, if asked.
    return (PhysicalLocationReporter::Direction::ENTER);
}

/**
 * getPhysicalLocation()
 *
 * Returns the PhysicalLocation of the Reporter
 *
 * Reports its own location, for now. Not sure if that's the right thing or
 * not. NOT DONE YET
 */
//@Override
/*public*/ PhysicalLocation* AbstractIdTagReporter::getPhysicalLocation() {
    return (this->getPhysicalLocation(nullptr));
}

/**
 * getPhysicalLocation(String s)
 *
 * Returns the PhysicalLocation of the Reporter
 *
 * Does not use the parameter s
 */
//@Override
/*public*/ PhysicalLocation *AbstractIdTagReporter::getPhysicalLocation(QString s) {
    return (PhysicalLocation::getBeanPhysicalLocation(this));
}


/*private*/ /*static*/ /*final*/ Logger* AbstractIdTagReporter::log = LoggerFactory::getLogger("AbstractIdTagReporter");
