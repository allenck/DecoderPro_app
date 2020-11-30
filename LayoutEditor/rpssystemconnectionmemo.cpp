#include "rpssystemconnectionmemo.h"
#include "instancemanager.h"
#include "rpscomponentfactory.h"
#include "loggerfactory.h"
#include <QStringList>
#include "rpssensormanager.h"
#include "rpsreportermanager.h"

/**
 * Minimal implementation of SystemConnectionMemo.
 *
 * @author Randall Wood randall.h.wood@alexandriasoftware.com
 */
///*public*/ class RpsSystemConnectionMemo extends SystemConnectionMemo {

/*public*/ RpsSystemConnectionMemo::RpsSystemConnectionMemo(/*@Nonnull*/ QString prefix, /*@Nonnull*/ QString name, QObject* parent)
: DefaultSystemConnectionMemo(prefix, name, parent){
    //super(prefix, name);
    _register(); // registers general type
    InstanceManager::store(this, "RpsSystemConnectionMemo"); // also register as specific type

    // create and register the ComponentFactory
    InstanceManager::store(new RpsComponentFactory(this),
            "ComponentFactory");

    log->debug(tr("Created RpsSystemConnectionMemo with prefix %1").arg(prefix));
}

/*public*/ RpsSystemConnectionMemo::RpsSystemConnectionMemo(QObject* parent) : DefaultSystemConnectionMemo("R", "RPS", parent)
{
    //this("R", "RPS"); // default connection prefix, default RPS product name NOI18N
    log->debug("Created nameless RpsSystemConnectionMemo");
}

//@Override
/*protected*/ ResourceBundle* RpsSystemConnectionMemo::getActionModelResourceBundle() {
    return nullptr;
}

/*public*/ void RpsSystemConnectionMemo::configureManagers() {
    InstanceManager::setSensorManager(getSensorManager());
    InstanceManager::setReporterManager(getReporterManager());
}


/*public*/ RpsSensorManager* RpsSystemConnectionMemo::getSensorManager() {
    if (getDisabled()) {
        return nullptr;
    }
    if (sensorManager == nullptr) {
        sensorManager = new RpsSensorManager(this);
    }
    return sensorManager;
}

/*public*/ RpsReporterManager* RpsSystemConnectionMemo::getReporterManager() {
    if (getDisabled()) {
        return nullptr;
    }
    if (reporterManager == nullptr) {
        reporterManager = new RpsReporterManager(this);
    }
    return reporterManager;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool RpsSystemConnectionMemo::provides(/*Class<?>*/QString type) {
    if (getDisabled()) {
        return false;
    }

    if (type == ("SensorManager")) {
        return true;
    }
    if (type == ("ReporterManager")) {
        return true;
    }
    return SystemConnectionMemo::provides(type); // nothing, by default
}

//@SuppressWarnings("unchecked")
//@Override
/*public*/ Manager* RpsSystemConnectionMemo::get(QString T) {
    if (getDisabled()) {
        return nullptr;
    }
    if (T == ("SensorManager")) {
        return (Manager*) getSensorManager();
    }
    if (T == ("ReporterManager")) {
        return (Manager*) getReporterManager();
    }
    return (Manager*)SystemConnectionMemo::get(T);
}

/**
 * Validate RPS system name format.
 *
 * @param name    the name to validate
 * @param manager the manager requesting the validation
 * @param locale  the locale for user messages
 * @return name, unchanged
 */
/*public*/ QString RpsSystemConnectionMemo::validateSystemNameFormat(QString name, Manager* manager, QLocale locale) {
    manager->validateSystemNamePrefix(name, locale);
    QStringList points = name.mid(manager->getSystemNamePrefix().length()).split(";");
    if (points.length() < 3) {
     QString msg = tr("%1 needs at least 3 (x,y,z) point coordinates, but has only %2").arg(name).arg(points.length());
     
        throw NamedBean:: BadSystemNameException(
//                Bundle.getMessage(Locale.ENGLISH, "SystemNameInvalidMissingPoints", name, points.length),
//                Bundle.getMessage(locale, "SystemNameInvalidMissingPoints", name, points.length)
        QLocale(),msg,name);
    }
    for (int i = 0; i < points.length(); i++) {
        if (!points[i].startsWith("(") || !points[i].endsWith(")")) {
         QString msg = tr("Point \"%2\" in %1 needs to be in the format \"(x,y,z) where x, y, and z are numbers\"").arg(name).arg(points[i]);
            throw  NamedBean::BadSystemNameException(
//                    Bundle.getMessage(Locale.ENGLISH, "SystemNameInvalidPointInvalid", name, points[i]),
//                    Bundle.getMessage(locale, "SystemNameInvalidPointInvalid", name, points[i])
            QLocale(),msg,name);
        }
        QStringList coords = points[i].mid(1, points[i].length() - 1).split(",");
        if (coords.length() != 3) {
         QString msg = tr("Point \"%2\" in %1 needs to be in the format \"(x,y,z) where x, y, and z are numbers\"").arg(name).arg(points[i]);
            throw  NamedBean::BadSystemNameException(
//                    Bundle.getMessage(Locale.ENGLISH, "SystemNameInvalidPointInvalid", name, points[i]),
//                    Bundle.getMessage(locale, "SystemNameInvalidPointInvalid", name, points[i])
            QLocale(),msg,name);
        }
        for (int j = 0; j < 3; j++) {
            bool bok;
                coords[j].toDouble(&bok);
            if(!bok) {
             QString msg = tr("Coordinate \"%3\" in point \"%2\" in %1 needs to be a number").arg(name).arg(points[i]).arg(coords[i]);
            throw NamedBean::BadSystemNameException(
//                    Bundle.getMessage(Locale.ENGLISH, "SystemNameInvalidCoordInvalid", name, points[i], coords[j]),
//                    Bundle.getMessage(locale, "SystemNameInvalidCoordInvalid", name, points[i], coords[j])
                QLocale(),msg,name);
            }
        }
    }
    return name;
}

/**
 * Validate RPS system name format.
 *
 * @return VALID if system name has a valid format, else return INVALID
 */
/*public*/ Manager::NameValidity RpsSystemConnectionMemo::validSystemNameFormat(QString systemName, char type) {
    // validate the system Name leader characters
    if (!(systemName.startsWith(getSystemPrefix() + type))) {
        // here if an illegal format
        log->error(tr("invalid character in header field of system name: %1").arg(systemName));
        return Manager::NameValidity::INVALID;
    }
    QString s = systemName.mid(getSystemPrefix().length() + 1);
    QStringList pStrings = s.split(";");
    if (pStrings.length() < 3) {
        log->warn(tr("need to have at least 3 points in %1").arg(systemName));
        return Manager::NameValidity::INVALID;
    }
    for (int i = 0; i < pStrings.length(); i++) {
        if (!(pStrings[i].startsWith("(")) || !(pStrings[i].endsWith(")"))) {
            // here if an illegal format
            log->warn(tr("missing brackets in point %1: \"%2\"").arg(i).arg(pStrings[i]));
            return Manager::NameValidity::INVALID;
        }
        // remove leading ( and trailing )
        QString coords = pStrings[i].mid(1, pStrings[i].length() - 1);
        try {
            QStringList coord = coords.split(",");
            if (coord.length() != 3) {
                log->warn(tr("need to have three coordinates in point %1: \"%2\"").arg(i).arg(pStrings[i]));
                return Manager::NameValidity::INVALID;
            }
            double x = (coord.at(0).toDouble());
            double y = (coord[1].toDouble());
            double z = (coord[2].toDouble());
            log->debug(tr("succes converting systemName point %1 to %2,%3,%4").arg(i).arg(x).arg(y).arg(z));
            // valid, continue
        } catch (NumberFormatException e) {
            return Manager::NameValidity::INVALID;
        }
    }
    return Manager::NameValidity::VALID;
}

/*private*/ /*final*/ /*static*/ Logger* RpsSystemConnectionMemo::log = LoggerFactory::getLogger("RpsSystemConnectionMemo");
