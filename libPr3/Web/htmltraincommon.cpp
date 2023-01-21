#include "htmltraincommon.h"
#include "loggerfactory.h"
#include "file.h"
#include "fileutil.h"
#include <QTextStream>
#include "fileutil.h"
#include <QUrl>
#include "car.h"
#include "setup.h"
#include "../operations/engine.h"
#include "routelocation.h"
#include "track.h"
#include "location.h"
#include "trainschedulemanager.h"
#include "trainschedule.h"
#include "instancemanager.h"

/**
 *
 * @author rhwood
 */
///*public*/ class HtmlTrainCommon extends TrainCommon {
namespace Operations
{

/*static*/ /*private*/ /*final*/ Logger* HtmlTrainCommon::log = LoggerFactory::getLogger("HtmlTrainCommon");

/*public*/ HtmlTrainCommon::HtmlTrainCommon(QLocale locale, Operations::Train* train, QObject* parent) /*throw (IOException)*/  : TrainCommon(parent)
{
 this->locale = locale;
 this->train = train;
 //FileInputStream is = NULL;
 QFile f(FileUtil::findURL("web/servlet/operations/ManifestStrings.properties")->path());
 try
 {
  if(!f.open(QIODevice::ReadOnly))
  {
   log->error(tr("file not found %1").arg(f.fileName()));
   throw  new FileNotFoundException("file not found %1" + f.fileName());
  }
  QTextStream is(&f);
//        is = new FileInputStream(Bundle.getMessage(locale, "ManifestStrings.properties"));
  strings->load(&is);
  f.close();
 }
 catch (IOException* ex)
 {
//        if (is != NULL) {
  f.close();
//        }
  throw ex;
 }
}

/*public*/ QString HtmlTrainCommon::pickupUtilityCars(QList<Operations::Car*>* carList, Operations::Car* car,  bool isManifest) {
    // list utility cars by type, track, length, and load
     QStringList messageFormat;
    if (isManifest) {
        messageFormat = Operations::Setup::getPickupUtilityManifestMessageFormat();
    } else {
        messageFormat = Operations::Setup::getPickupUtilitySwitchListMessageFormat();
    }
    int count = countUtilityCars(messageFormat, carList, car, PICKUP);
    if (count == 0) {
        return ""; // already printed out this car type
    }
    return pickUpCar(car, count, messageFormat);
}

/*protected*/ QString HtmlTrainCommon::setoutUtilityCars(QList<Operations::Car*>* carList, Operations::Car* car,  bool isManifest) {
     bool isLocal = isLocalMove(car);
    if (Operations::Setup::isSwitchListFormatSameAsManifest()) {
        isManifest = true;
    }
     QStringList messageFormat = Operations::Setup::getDropUtilityManifestMessageFormat();
    if (isLocal && isManifest) {
        messageFormat = Operations::Setup::getLocalUtilityManifestMessageFormat();
    } else if (isLocal && !isManifest) {
        messageFormat = Operations::Setup::getLocalUtilitySwitchListMessageFormat();
    } else if (!isLocal && !isManifest) {
        messageFormat = Operations::Setup::getDropUtilitySwitchListMessageFormat();
    }
    int count = countUtilityCars(messageFormat, carList, car, !PICKUP);
    if (count == 0) {
        return ""; // already printed out this car type
    }
    return dropCar(car, count, messageFormat, isLocal);
}

/*protected*/ QString HtmlTrainCommon::pickUpCar(Operations::Car* car,  QStringList format) {
    return pickUpCar(car, 0, format);
}

/*protected*/ QString HtmlTrainCommon::pickUpCar(Operations::Car* car, int count,  QStringList format) {
    if (isLocalMove(car)) {
        return ""; // print nothing local move, see dropCar
    }
    QString builder;// = new StringBuilder();
    // count the number of utility cars
    if (count != 0) {
        builder.append(count);
    }
    for (QString attribute : format) {
        builder.append(
                String::format(locale, strings->getProperty("Attribute"), getCarAttribute(car, attribute, PICKUP,
                                !LOCAL), attribute.toLower())).append(" "); // NOI18N
    }
    log->debug(tr("Picking up car %1").arg(builder));
    return String::format(locale, strings->getProperty(this->resourcePrefix + "PickUpCar"), builder/*.toString()*/); // NOI18N
}

/*protected*/ QString HtmlTrainCommon::dropCar(Operations::Car* car,  QStringList format,  bool isLocal) {
    return dropCar(car, 0, format, isLocal);
}

/*protected*/ QString HtmlTrainCommon::dropCar(Operations::Car* car, int count,  QStringList format,  bool isLocal) {
    QString builder;// = new StringBuilder();
    // count the number of utility cars
    if (count != 0) {
        builder.append(count);
    }
    for (QString attribute : format) {
        builder.append(
                String::format(locale, strings->getProperty("Attribute"), getCarAttribute(car, attribute, !PICKUP,
                                isLocal), attribute.toLower())).append(" "); // NOI18N
    }
    log->debug(tr("Dropping %1 car %2").arg((isLocal) ? "local " : "").arg(builder));
    if (!isLocal) {
        return String::format(locale, strings->getProperty(this->resourcePrefix + "DropCar"), builder/*.toString()*/); // NOI18N
    } else {
        return String::format(locale, strings->getProperty(this->resourcePrefix + "LocalCar"), builder/*.toString()*/); // NOI18N
    }
}

/*protected*/ QString HtmlTrainCommon::engineChange(RouteLocation* location, int legOptions) {
    if ((legOptions & Train::HELPER_ENGINES) == Train::HELPER_ENGINES) {
        return String::format(strings->getProperty("AddHelpersAt"), splitString(location->getName())); // NOI18N
    } else if ((legOptions & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES
            && ((legOptions & Train::REMOVE_CABOOSE) == Train::REMOVE_CABOOSE || (legOptions & Train::ADD_CABOOSE) == Train::ADD_CABOOSE)) {
        return String::format(strings->getProperty("LocoAndCabooseChangeAt"), splitString(location->getName())); // NOI18N
    } else if ((legOptions & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES) {
        return String::format(strings->getProperty("LocoChangeAt"), splitString(location->getName())); // NOI18N
    } else if ((legOptions & Train::REMOVE_CABOOSE) == Train::REMOVE_CABOOSE
            || (legOptions & Train::ADD_CABOOSE) == Train::ADD_CABOOSE) {
        return String::format(strings->getProperty("CabooseChangeAt"), splitString(location->getName())); // NOI18N
    }
    return "";
}

/*protected*/ QString HtmlTrainCommon::dropEngines(QList<Engine*>* engines, RouteLocation* location) {
    QString builder;// = new StringBuilder();
    for (Engine* engine : *engines) {
        if (engine->getRouteDestination() == (location)) {
            builder.append(dropEngine(engine));
        }
    }
    return String::format(strings->getProperty("EnginesList"), builder/*.toString()*/);
}

//@Override
/*public*/ QString HtmlTrainCommon::dropEngine(Engine* engine) {
    QString builder;// = new StringBuilder();
    for (QString attribute : Operations::Setup::getDropEngineMessageFormat()) {
        builder.append(
                String::format(locale, strings->getProperty("Attribute"),
                        getEngineAttribute(engine, attribute, false), attribute.toLower())).append(" ");
    }
    log->debug(tr("Drop engine: %1").arg(builder));
    return String::format(locale, strings->getProperty(this->resourcePrefix + "DropEngine"), builder/*.toString()*/);
}

/*protected*/ QString HtmlTrainCommon::pickupEngines(QList<Engine*>* engines, RouteLocation* location) {
    QString builder;// = new StringBuilder();
    for (Engine* engine : *engines) {
        if (engine->getRouteLocation() == (location) && engine->getTrackName() != ("")) {
            builder.append(pickupEngine(engine));
        }
    }
    return String::format(locale, strings->getProperty("EnginesList"), builder/*.toString()*/);
}

//@Override
/*public*/ QString HtmlTrainCommon::pickupEngine(Engine* engine) {
    QString builder;// = new StringBuilder();
    for (QString attribute : Operations::Setup::getPickupEngineMessageFormat()) {
        builder.append(
                String::format(locale, strings->getProperty("Attribute"),
                        getEngineAttribute(engine, attribute, true), attribute.toLower())).append(" ");
    }
    log->debug(tr("Picking up engine: %1").arg(builder));
    return String::format(locale, strings->getProperty(this->resourcePrefix + "PickUpEngine"), builder/*.toString()*/);
}
#if 1
/*protected*/ QString HtmlTrainCommon::getCarAttribute(Car* car, QString attribute,  bool isPickup,  bool isLocal) {
    if (attribute == (Operations::Setup::LOAD)) {
        return (car->isCaboose() || car->isPassenger()) ? "" : QString(QUrl(car->getLoadName()).toEncoded()); // NOI18N
    } else if (attribute == (Operations::Setup::HAZARDOUS)) {
        return car->isHazardous() ? Operations::Setup::getHazardousMsg() : ""; // NOI18N
    } else if (attribute == (Operations::Setup::DROP_COMMENT)) {
        return car->getDropComment();
    } else if (attribute == (Operations::Setup::PICKUP_COMMENT)) {
        return car->getPickupComment();
    } else if (attribute == (Operations::Setup::KERNEL)) {
        return car->getKernelName();
    } else if (attribute == (Operations::Setup::RWE)) {
        if (car->getReturnWhenEmptyDestName() != ("")) {
            return String::format(locale, strings->getProperty("RWELocationAndTrack"), QString(QUrl(splitString(car->getReturnWhenEmptyDestinationName())).toEncoded()), QString(QUrl(splitString(car->getReturnWhenEmptyDestTrackName())).toEncoded()));
        }
        return ""; // NOI18N
    } else if (attribute == (Operations::Setup::FINAL_DEST)) {
        if (car->getFinalDestinationName() != ("")) {
            return String::format(locale, strings->getProperty("FinalDestinationLocation"), QString(QUrl(splitString(car->getFinalDestinationName())).toEncoded()));
        }
        return "";
    } else if (attribute == (Operations::Setup::FINAL_DEST_TRACK)) {
        if (car->getFinalDestinationName() != ("")) {
            return String::format(locale, strings->getProperty("FinalDestinationLocationAndTrack"), QString(QUrl(splitString(car->getFinalDestinationName())).toEncoded()), QString(QUrl(splitString(car->getFinalDestinationTrackName())).toEncoded()));
        }
        return "";
    }
    return getRollingStockAttribute(car, attribute, isPickup, isLocal);
}

/*protected*/ QString HtmlTrainCommon::getEngineAttribute(Engine* engine, QString attribute,  bool isPickup) {
    if (attribute == (Operations::Setup::MODEL)) {
        return engine->getModel();
    }
    if (attribute == (Operations::Setup::CONSIST)) {
        return engine->getConsistName();
    }
    return getRollingStockAttribute(engine, attribute, isPickup, false);
}

/*protected*/ QString HtmlTrainCommon::getRollingStockAttribute(RollingStock* rs, QString attribute,  bool isPickup,  bool isLocal) {
    if (attribute == (Operations::Setup::NUMBER)) {
        return splitString(rs->getNumber());
    } else if (attribute == (Operations::Setup::ROAD)) {
        return QString(QUrl(rs->getRoadName()).toEncoded());
    } else if (attribute == (Operations::Setup::TYPE)) {
         QStringList type = rs->getTypeName().split("-"); // second half of string
        // can be anything
        return type[0];
    } else if (attribute == (Operations::Setup::LENGTH)) {
        return rs->getLength();
    } else if (attribute == (Operations::Setup::COLOR)) {
        return rs->getColor();
    } else if (attribute == (Operations::Setup::LOCATION) && (isPickup || isLocal)
            || (attribute == (Operations::Setup::TRACK) && isPickup)) {
        if (rs->getTrack() != NULL) {
            return String::format(locale, strings->getProperty("FromTrack"), QString(QUrl(rs->getTrackName()).toEncoded()));
        }
        return "";
    } else if (attribute == (Operations::Setup::LOCATION) && !isPickup && !isLocal) {
        return ""; // we don't have the car's origin, so nothing to return
// Note that the JSON database does have the car's origin, so this could be fixed.
//			return String::format(locale, strings->getProperty("FromLocation"), StringEscapeUtils.escapeHtml4(rs
//					.getLocationName()));
    } else if (attribute == (Operations::Setup::DESTINATION) && isPickup) {
        return String::format(locale, strings->getProperty("ToLocation"), QString(QUrl(splitString(rs->getDestinationName())).toEncoded()));
    } else if ((attribute == (Operations::Setup::DESTINATION) || attribute == (Operations::Setup::TRACK)) && !isPickup) {
        return String::format(locale, strings->getProperty("ToTrack"), QString(QUrl(splitString(rs->getDestinationTrackName())).toEncoded()));
    } else if (attribute == (Operations::Setup::DEST_TRACK)) {
        return String::format(locale, strings->getProperty("ToLocationAndTrack"), QString(QUrl(splitString(rs->getDestinationName())).toEncoded()), QString(QUrl(splitString(rs->getDestinationTrackName())).toEncoded()));
    } else if (attribute == (Operations::Setup::OWNER)) {
        return QString(QUrl(rs->getOwner()).toEncoded());
    } else if (attribute == (Operations::Setup::COMMENT)) {
        return QString(QUrl(rs->getComment()).toEncoded());
    } else if (attribute == (Operations::Setup::BLANK) || attribute == (Operations::Setup::NO_NUMBER)
            || attribute == (Operations::Setup::NO_ROAD) || attribute == (Operations::Setup::NO_COLOR)
            || attribute == (Operations::Setup::NO_DESTINATION) || attribute == (Operations::Setup::NO_DEST_TRACK)
            || attribute == (Operations::Setup::NO_LOCATION) || attribute == (Operations::Setup::NO_TRACK)
            || attribute == (Operations::Setup::TAB) || attribute == (Operations::Setup::TAB2) || attribute == (Operations::Setup::TAB3)) {
        // attributes that don't print
        return "";
    }
    return String::format(locale, "ERROR PRINT ATTRIBUTE (%1$s)", attribute); // something is isn't right!
}
#endif
/*protected*/ QString HtmlTrainCommon::getTrackComments(RouteLocation* location, QList<Car*>* cars) {
    QString builder;// = new StringBuilder();
    if (location->getLocation() != NULL) {
        QList<Track*> tracks = location->getLocation()->getTracksByNameList(NULL);
        for (Track* track : tracks) {
            // any pick ups or set outs to this track?
             bool pickup = false;
             bool setout = false;
            for (Car* car : *cars) {
                if (car->getRouteLocation() == location && car->getTrack() != NULL && car->getTrack() == track) {
                    pickup = true;
                }
                if (car->getRouteDestination() == location && car->getDestinationTrack() != NULL
                        && car->getDestinationTrack() == track) {
                    setout = true;
                }
            }
            // print the appropriate comment if there's one
            if (pickup && setout && track->getCommentBoth() != ("")) {
                builder.append(String::format(locale, strings->getProperty("TrackComments"), QString(QUrl(track->getCommentBoth()).toEncoded())));
            } else if (pickup && !setout && track->getCommentPickup() != ("")) {
                builder.append(String::format(locale, strings->getProperty("TrackComments"), QString(QUrl(track->getCommentPickup()).toEncoded())));
            } else if (!pickup && setout && track->getCommentSetout() != ("")) {
                builder.append(String::format(locale, strings->getProperty("TrackComments"), QString(QUrl(track->getCommentSetout()).toEncoded())));
            }
        }
    }
    return builder/*.toString()*/;
}
#if 1
/*public*/ QString HtmlTrainCommon::getValidity()
{
 if (Operations::Setup::isPrintTimetableNameEnabled()) {
     return String::format(locale, strings->getProperty("ManifestValidityWithSchedule"), getDate(true),
             ((TrainScheduleManager*)InstanceManager::getDefault("Operations::TrainScheduleManager"))->getScheduleById(train->getId())->toString());
 } else {
     return String::format(locale, strings->getProperty("ManifestValidity"), getDate(true));
 }
}
#endif
}
/*static*/ QString String::format(QString format, QString arg0, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6, QString arg7, QString arg8, QString arg9, QString arg10, QString arg11, QString arg12, QString arg13, QString arg14, QString arg15)
{
 return String::format(QLocale(), format, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15);
}

/*static*/ QString String::format(QLocale ,QString format, QString arg0, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6, QString arg7, QString arg8, QString arg9, QString arg10, QString arg11, QString arg12, QString arg13, QString arg14, QString arg15)
{
 //if(!arg0.isNull())
  format = format.replace("%1$s", arg0);
 //if(!arg1.isNull())
  format = format.replace("%2$s", arg1);
 //if(!arg2.isNull())
  format = format.replace("%3$s", arg2);
 //if(!arg3.isNull())
  format = format.replace("%4$s", arg3);
 //if(!arg4.isNull())
  format = format.replace("%5$s", arg4);
 //if(!arg5.isNull())
  format = format.replace("%6$s", arg5);
 //if(!arg6.isNull())
  format = format.replace("%7$s", arg6);
 //if(!arg7.isNull())
  format = format.replace("%8$s", arg7);
 //if(!arg8.isNull())
  format = format.replace("%9$s", arg8);
 //if(!arg9.isNull())
  format = format.replace("%10$s", arg9);
 //if(!arg10.isNull())
  format = format.replace("%11$s", arg10);
 //if(!arg11.isNull())
  format = format.replace("%12$s", arg11);
 //if(!arg12.isNull())
  format = format.replace("%13$s", arg12);
 //if(!arg13.isNull())
  format = format.replace("%14$s", arg13);
 //if(!arg14.isNull())
  format = format.replace("%15$s", arg14);
 //if(!arg15.isNull())
  format = format.replace("%16$s", arg15);

 return format;
}
