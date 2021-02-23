#include "timetablexml.h"
#include "loggerfactory.h"
#include "timetabledatamanager.h"
#include "fileutil.h"
#include "file.h"
#include "scale.h"
#include "ttschedule.h"
#include "tttrain.h"

namespace TimeTable
{

TimeTableXml::TimeTableXml(QObject *parent) : QObject(parent)
{

}

/**
 * Load and store the timetable data file: TimeTableData.xml
 * @author Dave Sand Copyright (C) 2018
 */
// /*public*/ class TimeTableXml {

    /*public*/ /*static*/ bool TimeTableXml::doStore() {
        TimeTableDataManager* dataMgr = TimeTableDataManager::getDataManager();
        TimeTableXmlFile* x = new TimeTableXmlFile();
        File* file = x->getFile(true);
        try {
            FileUtil::rotate(file, 4, "bup");  // NOI18N
        } catch (IOException ex) {
            log->warn("Rotate failed, reverting to xml backup");  // NOI18N
            x->makeBackupFile(TimeTableXmlFile::getDefaultFileName());
        }

        // Create root element
        QDomDocument doc = QDomDocument();

        QDomElement root = doc.createElement("timetable-data");  // NOI18N
//        root.setAttribute("noNamespaceSchemaLocation",  // NOI18N
//                "http://jmri.org/xml/schema/timetable.xsd",  // NOI18N
//                org.jdom2.Namespace.getNamespace("xsi",
//                        "http://www.w3.org/2001/XMLSchema-instance"));  // NOI18N
        root.setAttribute("xsi:noNamespaceSchemaLocation",  // NOI18N
                "http://jmri.org/xml/schema/scale.xsd");  // NOI18N
        root.setAttribute( "xmlns:xsi",
                        "http://www.w3.org/2001/XMLSchema-instance");  // NOI18N
        doc.appendChild(root);
        QDomElement values;

        root.appendChild(values = doc.createElement("layouts"));  // NOI18N
        for (Layout* layout : dataMgr->getLayouts(false)) {
            QDomElement e = doc.createElement("layout");  // NOI18N
            QDomElement e1;
            e.appendChild(e1=doc.createElement("layout_id")); e1.appendChild(doc.createTextNode(QString::number(layout->getLayoutId())));  // NOI18N
            e.appendChild(e1=doc.createElement("layout_name")); e1.appendChild(doc.createTextNode(layout->getLayoutName()));  // NOI18N
            e.appendChild(e1=doc.createElement("scale")); e1.appendChild(doc.createTextNode(layout->getScale()->getScaleName()));  // NOI18N
            e.appendChild(e1=doc.createElement("fast_clock")); e1.appendChild(doc.createTextNode(QString::number(layout->getFastClock())));  // NOI18N
            e.appendChild(e1=doc.createElement("throttles")); e1.appendChild(doc.createTextNode(QString::number(layout->getThrottles())));  // NOI18N
            e.appendChild(e1=doc.createElement("metric")); e1.appendChild(doc.createTextNode((layout->getMetric()) ? "yes" : "no"));  // NOI18N
            values.appendChild(e);
        }

        root.appendChild(values = doc.createElement("train_types"));  // NOI18N
        for (TrainType* type : dataMgr->getTrainTypes(0, false)) {
            QDomElement e = doc.createElement("train_type");  // NOI18N
            QDomElement e1;
            e.appendChild(e1=doc.createElement("type_id")); e1.appendChild(doc.createTextNode(QString::number(type->getTypeId())));  // NOI18N
            e.appendChild(e1=doc.createElement("layout_id")); e1.appendChild(doc.createTextNode(QString::number(type->getLayoutId())));  // NOI18N
            e.appendChild(e1=doc.createElement("type_name")); e1.appendChild(doc.createTextNode(type->getTypeName()));  // NOI18N
            e.appendChild(e1=doc.createElement("type_color")); e1.appendChild(doc.createTextNode(type->getTypeColor()));  // NOI18N
            values.appendChild(e);
        }

        root.appendChild(values = doc.createElement("segments"));  // NOI18N
        for (Segment* segment : dataMgr->getSegments(0, false)) {
            QDomElement e = doc.createElement("segment");  // NOI18N
            QDomElement e1;
            e.appendChild(e1=doc.createElement("segment_id")); e1.appendChild(doc.createTextNode(QString::number(segment->getSegmentId())));  // NOI18N
            e.appendChild(e1=doc.createElement("layout_id")); e1.appendChild(doc.createTextNode(QString::number(segment->getLayoutId())));  // NOI18N
            e.appendChild(e1=doc.createElement("segment_name")); e1.appendChild(doc.createTextNode(segment->getSegmentName()));  // NOI18N
            values.appendChild(e);
        }

        root.appendChild(values = doc.createElement("stations"));  // NOI18N
        for (Station* station : dataMgr->getStations(0, false)) {
            QDomElement e = doc.createElement("station");  // NOI18N
            QDomElement e1;
            e.appendChild(e1=doc.createElement("station_id")); e1.appendChild(doc.createTextNode(QString::number(station->getStationId())));  // NOI18N
            e.appendChild(e1=doc.createElement("segment_id")); e1.appendChild(doc.createTextNode(QString::number(station->getSegmentId())));  // NOI18N
            e.appendChild(e1=doc.createElement("station_name")); e1.appendChild(doc.createTextNode(station->getStationName()));  // NOI18N
            e.appendChild(e1=doc.createElement("distance")); e1.appendChild(doc.createTextNode(QString::number(station->getDistance())));  // NOI18N
            e.appendChild(e1=doc.createElement("double_track")); e1.appendChild(doc.createTextNode((station->getDoubleTrack()) ? "yes" : "no"));  // NOI18N
            e.appendChild(e1=doc.createElement("sidings")); e1.appendChild(doc.createTextNode(QString::number(station->getSidings())));  // NOI18N
            e.appendChild(e1=doc.createElement("staging")); e1.appendChild(doc.createTextNode(QString::number(station->getStaging())));  // NOI18N
            values.appendChild(e);
        }

        root.appendChild(values = doc.createElement("schedules"));  // NOI18N
        for (TTSchedule* schedule : dataMgr->getSchedules(0, false)) {
            QDomElement e = doc.createElement("schedule");  // NOI18N
            QDomElement e1;
            e.appendChild(e1=doc.createElement("schedule_id")); e1.appendChild(doc.createTextNode(QString::number(schedule->getScheduleId())));  // NOI18N
            e.appendChild(e1=doc.createElement("layout_id")); e1.appendChild(doc.createTextNode(QString::number(schedule->getLayoutId())));  // NOI18N
            e.appendChild(e1=doc.createElement("schedule_name")); e1.appendChild(doc.createTextNode(schedule->getScheduleName()));  // NOI18N
            e.appendChild(e1=doc.createElement("eff_date")); e1.appendChild(doc.createTextNode(schedule->getEffDate()));  // NOI18N
            e.appendChild(e1=doc.createElement("start_hour")); e1.appendChild(doc.createTextNode(QString::number(schedule->getStartHour())));  // NOI18N
            e.appendChild(e1=doc.createElement("duration")); e1.appendChild(doc.createTextNode(QString::number(schedule->getDuration())));  // NOI18N
            values.appendChild(e);
        }

        root.appendChild(values = doc.createElement("trains"));  // NOI18N
        for (TTTrain* train : dataMgr->getTrains(0, 0, false)) {
            QDomElement e = doc.createElement("train");  // NOI18N
            QDomElement e1;
            e.appendChild(e1=doc.createElement("train_id")); e1.appendChild(doc.createTextNode(QString::number(train->getTrainId())));  // NOI18N
            e.appendChild(e1=doc.createElement("schedule_id")); e1.appendChild(doc.createTextNode(QString::number(train->getScheduleId())));  // NOI18N
            e.appendChild(e1=doc.createElement("type_id")); e1.appendChild(doc.createTextNode(QString::number(train->getTypeId())));  // NOI18N
            e.appendChild(e1=doc.createElement("train_name")); e1.appendChild(doc.createTextNode(train->getTrainName()));  // NOI18N
            e.appendChild(e1=doc.createElement("train_desc")); e1.appendChild(doc.createTextNode(train->getTrainDesc()));  // NOI18N
            e.appendChild(e1=doc.createElement("default_speed")); e1.appendChild(doc.createTextNode(QString::number(train->getDefaultSpeed())));  // NOI18N
            e.appendChild(e1=doc.createElement("start_time")); e1.appendChild(doc.createTextNode(QString::number(train->getStartTime())));  // NOI18N
            e.appendChild(e1=doc.createElement("throttle")); e1.appendChild(doc.createTextNode(QString::number(train->getThrottle())));  // NOI18N
            e.appendChild(e1=doc.createElement("route_duration")); e1.appendChild(doc.createTextNode(QString::number(train->getRouteDuration())));  // NOI18N
            e.appendChild(e1=doc.createElement("train_notes")); e1.appendChild(doc.createTextNode(train->getTrainNotes()));  // NOI18N
            values.appendChild(e);
        }

        root.appendChild(values = doc.createElement("stops"));  // NOI18N
        for (Stop* stop : dataMgr->getStops(0, 0, false)) {
            QDomElement e = doc.createElement("stop");  // NOI18N
            QDomElement e1;
            e.appendChild(e1=doc.createElement("stop_id")); e1.appendChild(doc.createTextNode(QString::number(stop->getStopId())));  // NOI18N
            e.appendChild(e1=doc.createElement("train_id")); e1.appendChild(doc.createTextNode(QString::number(stop->getTrainId())));  // NOI18N
            e.appendChild(e1=doc.createElement("station_id")); e1.appendChild(doc.createTextNode(QString::number(stop->getStationId())));  // NOI18N
            e.appendChild(e1=doc.createElement("seq")); e1.appendChild(doc.createTextNode(QString::number(stop->getSeq())));  // NOI18N
            e.appendChild(e1=doc.createElement("duration")); e1.appendChild(doc.createTextNode(QString::number(stop->getDuration())));  // NOI18N
            e.appendChild(e1=doc.createElement("next_speed")); e1.appendChild(doc.createTextNode(QString::number(stop->getNextSpeed())));  // NOI18N
            e.appendChild(e1=doc.createElement("arrive_time")); e1.appendChild(doc.createTextNode(QString::number(stop->getArriveTime())));  // NOI18N
            e.appendChild(e1=doc.createElement("depart_time")); e1.appendChild(doc.createTextNode(QString::number(stop->getDepartTime())));  // NOI18N
            e.appendChild(e1=doc.createElement("staging_track")); e1.appendChild(doc.createTextNode(QString::number(stop->getStagingTrack())));  // NOI18N
            e.appendChild(e1=doc.createElement("stop_notes")); e1.appendChild(doc.createTextNode(stop->getStopNotes()));  // NOI18N
            values.appendChild(e);
        }

        try {
            x->writeXML(file, doc);
        } catch (FileNotFoundException ex) {
            log->error("File not found when writing: " + ex.getMessage());  // NOI18N
            return false;
        } catch (IOException ex) {
            log->error("IO Exception when writing: " + ex.getMessage());  // NOI18N
            return false;
        }

        log->debug("...done");  // NOI18N
        return true;
    }

    /*public*/ /*static*/ bool TimeTableXml::doLoad() {
        TimeTableDataManager* dataMgr = TimeTableDataManager::getDataManager();
        TimeTableXmlFile* x = new TimeTableXmlFile();
        File* file = x->getFile(false);

        if (file == nullptr) {
            log->debug("Nothing to load");  // NOI18N
            return false;
        }

        // Validate foreign keys
        QList<int> checkLayoutIds = QList<int>();
        QList<int> checkTypeIds = QList<int>();
        QList<int> checkSegmentIds = QList<int>();
        QList<int> checkStationIds = QList<int>();
        QList<int> checkScheduleIds = QList<int>();
        QList<int> checkTrainIds = QList<int>();

        log->debug("Start loading timetable data...");  // NOI18N

        // Find root
        QDomElement root;
        try {
            root = x->rootFromFile(file);
            if (root.isNull()) {
                log->debug("File could not be read");  // NOI18N
                return false;
            }

            // Layouts
            QDomElement layouts = root.firstChildElement("layouts");  // NOI18N
            if (layouts.isNull()) {
                log->error("Unable to find a layout entry");  // NOI18N
                return false;
            }
            //for (QDomNode node, layouts.elementsByTagName("layout"))
            QDomNodeList nl = layouts.elementsByTagName("layout");
            for(int i=0; i < nl.size(); i++)
            {  // NOI18N
             QDomElement layout = nl.at(i).toElement();
                QDomElement layout_id = layout.firstChildElement("layout_id");  // NOI18N
                int layoutId = (layout_id.isNull()) ? 0 : layout_id.text().toInt();
                QDomElement layout_name = layout.firstChildElement("layout_name");  // NOI18N
                QString layoutName = (layout_name.isNull()) ? "" : layout_name.text();
                QDomElement scaleE = layout.firstChildElement("scale");  // NOI18N
                Scale* scale = (scaleE.isNull()) ? ScaleManager::getScale("HO") : ScaleManager::getScale(scaleE.text());  // NOI18N
                QDomElement fast_clock = layout.firstChildElement("fast_clock");  // NOI18N
                int fastClock = (fast_clock.isNull()) ? 1 : fast_clock.text().toInt();
                QDomElement throttlesE = layout.firstChildElement("throttles");  // NOI18N
                int throttles = (throttlesE.isNull()) ? 0 : throttlesE.text().toInt();
                QDomElement metricE = layout.firstChildElement("metric");  // NOI18N
                bool metric = (metricE.isNull()) ? false : metricE.text()== ("yes");  // NOI18N
                log->debug(tr("  Layout: %1 - %2 - %3 - %4 - %5 - %6").arg(  // NOI18N
                    layoutId).arg(layoutName).arg(scale->getScaleName()).arg(fastClock).arg(throttles).arg(metric));

                // Create a Layout
                Layout* newLayout = new Layout(layoutId, layoutName, scale, fastClock, throttles, metric);
                dataMgr->addLayout(layoutId, newLayout);
                checkLayoutIds.append(layoutId);
            }

            // Train Types
            QDomElement train_types = root.firstChildElement("train_types");  // NOI18N
            if (train_types.isNull()) {
                log->error("Unable to find train types");  // NOI18N
                return false;
            }
            //for (QDomNode node : train_types.elementsByTagName("train_type")) {  // NOI18N
            nl = train_types.elementsByTagName("train_type");
            for(int i=0; i < nl.size(); i++)
            {  // NOI18N
             QDomElement train_type = nl.at(i).toElement();
                QDomElement type_id = train_type.firstChildElement("type_id");  // NOI18N
                int typeId = (type_id.isNull()) ? 0 : type_id.text().toInt();
                QDomElement layout_id = train_type.firstChildElement("layout_id");  // NOI18N
                int layoutId = (layout_id.isNull()) ? 0 : layout_id.text().toInt();
                QDomElement type_name = train_type.firstChildElement("type_name");  // NOI18N
                QString typeName = (type_name.isNull()) ? "" : type_name.text();
                QDomElement type_color = train_type.firstChildElement("type_color");  // NOI18N
                QString typeColor = (type_color.isNull()) ? "#000000" : type_color.text();  // NOI18N
                log->debug(tr("    Type: %1 - %2- %3").arg(typeId).arg(typeName).arg(typeColor));  // NOI18N

                // Validate layoutId
                if (!checkLayoutIds.contains(layoutId)) {
                    log->warn(tr("TrainType %1 layout id not found").arg(typeName));  // NOI18N
                    continue;
                }

                // Create a train type
                TrainType* newType = new TrainType(typeId, layoutId, typeName, typeColor);
                dataMgr->addTrainType(typeId, newType);
                checkTypeIds.append(typeId);
            }

            // Segments
            QDomElement segments = root.firstChildElement("segments");  // NOI18N
            if (segments.isNull()) {
                log->error("Unable to find segments");  // NOI18N
                return false;
            }
            //for (QDomElement segment : segments.firstChildElementren("segment")) {  // NOI18N
            nl = segments.elementsByTagName("segment");
            for(int i=0; i < nl.size(); i++)
            {  // NOI18N
             QDomElement segment = nl.at(i).toElement();
                QDomElement segment_id = segment.firstChildElement("segment_id");  // NOI18N
                int segmentId = (segment_id.isNull()) ? 0 : segment_id.text().toInt();
                QDomElement layout_id = segment.firstChildElement("layout_id");  // NOI18N
                int layoutId = (layout_id.isNull()) ? 0 : layout_id.text().toInt();
                QDomElement segment_name = segment.firstChildElement("segment_name");  // NOI18N
                QString segmentName = (segment_name.isNull()) ? "" : segment_name.text();
                log->debug(tr("    Segment: %1 - %2 - %3").arg(segmentId).arg(layoutId).arg(segmentName));  // NOI18N

                // Validate layoutId
                if (!checkLayoutIds.contains(layoutId)) {
                    log->warn("Segment {} layout id not found", segmentName);  // NOI18N
                    continue;
                }

                // Create a segment
                Segment* newSegment = new Segment(segmentId, layoutId, segmentName);
                dataMgr->addSegment(segmentId, newSegment);
                checkSegmentIds.append(segmentId);
            }

            // Stations
            QDomElement stations = root.firstChildElement("stations");  // NOI18N
            if (stations.isNull()) {
                log->error("Unable to find stations");  // NOI18N
                return false;
            }
            //for (QDomElement station : stations.firstChildElement("station")) {  // NOI18N
            nl = stations.elementsByTagName("station");
            for(int i=0; i < nl.size(); i++)
            {  // NOI18N
            QDomElement station = nl.at(i).toElement();
                QDomElement station_id = station.firstChildElement("station_id");  // NOI18N
                int stationId = (station_id.isNull()) ? 0 : station_id.text().toInt();
                QDomElement segment_id = station.firstChildElement("segment_id");  // NOI18N
                int segmentId = (segment_id.isNull()) ? 0 : segment_id.text().toInt();
                QDomElement station_name = station.firstChildElement("station_name");  // NOI18N
                QString stationName = (station_name.isNull()) ? "" : station_name.text();
                QDomElement distanceE = station.firstChildElement("distance");  // NOI18N
                double distance = (distanceE.isNull()) ? 1.0 : distanceE.text().toDouble();
                QDomElement double_track = station.firstChildElement("double_track");  // NOI18N
                bool doubleTrack = (double_track.isNull()) ? false : double_track.text()==("yes");  // NOI18N
                QDomElement sidingsE = station.firstChildElement("sidings");  // NOI18N
                int sidings = (sidingsE.isNull()) ? 0 : sidingsE.text().toInt();
                QDomElement stagingE = station.firstChildElement("staging");  // NOI18N
                int staging = (stagingE.isNull()) ? 0 : stagingE.text().toInt();
                log->debug(tr("      Station: %1 - %2 - %3 - %4 - %5 - %6").arg(stationId).arg(stationName).arg(distance).arg(doubleTrack).arg(sidings).arg(staging));  // NOI18N

                // Validate segmentId
                if (!checkSegmentIds.contains(segmentId)) {
                    log->warn(tr("Station %1 segment id not found").arg(stationName));  // NOI18N
                    continue;
                }

                // Create a station
                Station* newStation = new Station(stationId, segmentId, stationName, distance, doubleTrack, sidings, staging);
                dataMgr->addStation(stationId, newStation);
                checkStationIds.append(stationId);
            }

            QDomElement schedules = root.firstChildElement("schedules");  // NOI18N
            if (schedules.isNull()) {
                log->error("Unable to find schedules");  // NOI18N
                return false;
            }
            //for (QDomElement schedule : schedules.firstChildElementren("schedule")) {  // NOI18N
            nl = schedules.elementsByTagName("schedule");
            for(int i=0; i < nl.size(); i++)
            {  // NOI18N
            QDomElement schedule = nl.at(i).toElement();
                QDomElement schedule_id = schedule.firstChildElement("schedule_id");  // NOI18N
                int scheduleId = (schedule_id.isNull()) ? 0 : schedule_id.text().toInt();
                QDomElement layout_id = schedule.firstChildElement("layout_id");  // NOI18N
                int layoutId = (layout_id.isNull()) ? 0 : layout_id.text().toInt();
                QDomElement schedule_name = schedule.firstChildElement("schedule_name");  // NOI18N
                QString scheduleName = (schedule_name.isNull()) ? "" : schedule_name.text();
                QDomElement eff_date = schedule.firstChildElement("eff_date");  // NOI18N
                QString effDate = (eff_date.isNull()) ? "" : eff_date.text();
                QDomElement start_hour = schedule.firstChildElement("start_hour");  // NOI18N
                int startHour = (start_hour.isNull()) ? 0 : start_hour.text().toInt();
                QDomElement durationE = schedule.firstChildElement("duration");  // NOI18N
                int duration = (durationE.isNull()) ? 0 : durationE.text().toInt();
                log->debug(tr("    Schedule: %1 - %2 - %3 - %4 - %5 - %6").arg(scheduleId).arg(layoutId).arg(scheduleName).arg(effDate).arg(startHour).arg(duration));  // NOI18N

                // Validate layoutId
                if (!checkLayoutIds.contains(layoutId)) {
                    log->warn("Schdule {} layout id not found", scheduleName);  // NOI18N
                    continue;
                }

                // Create a schedule
                TTSchedule* newSchedule = new TTSchedule(scheduleId, layoutId, scheduleName, effDate, startHour, duration);
                dataMgr->addSchedule(scheduleId, newSchedule);
                checkScheduleIds.append(scheduleId);
            }

            QDomElement trains = root.firstChildElement("trains");  // NOI18N
            if (trains.isNull()) {
                log->error("Unable to find trains");  // NOI18N
                return false;
            }
            //for (QDomElement train : trains.firstChildElementren("train")) {  // NOI18N
            nl = trains.elementsByTagName("train");
            for(int i=0; i < nl.size(); i++)
            {  // NOI18N
            QDomElement train = nl.at(i).toElement();
                QDomElement train_id = train.firstChildElement("train_id");  // NOI18N
                int trainId = (train_id.isNull()) ? 0 : train_id.text().toInt();
                QDomElement schedule_id = train.firstChildElement("schedule_id");  // NOI18N
                int scheduleId = (schedule_id.isNull()) ? 0 : schedule_id.text().toInt();
                QDomElement type_id = train.firstChildElement("type_id");  // NOI18N
                int typeId = (type_id.isNull()) ? 0 : type_id.text().toInt();
                QDomElement train_name = train.firstChildElement("train_name");  // NOI18N
                QString trainName = (train_name.isNull()) ? "" : train_name.text();
                QDomElement train_desc = train.firstChildElement("train_desc");  // NOI18N
                QString trainDesc = (train_desc.isNull()) ? "" : train_desc.text();
                QDomElement default_speed = train.firstChildElement("default_speed");  // NOI18N
                int defaultSpeed = (default_speed.isNull()) ? 1 : default_speed.text().toInt();
                QDomElement start_time = train.firstChildElement("start_time");  // NOI18N
                int startTime = (start_time.isNull()) ? 0 : start_time.text().toInt();
                QDomElement throttleE = train.firstChildElement("throttle");  // NOI18N
                int throttle = (throttleE.isNull()) ? 0 : throttleE.text().toInt();
                QDomElement route_duration = train.firstChildElement("route_duration");  // NOI18N
                int routeDuration = (route_duration.isNull()) ? 0 : route_duration.text().toInt();
                QDomElement train_notes = train.firstChildElement("train_notes");  // NOI18N
                QString trainNotes = (train_notes.isNull()) ? "" : train_notes.text();
                log->debug(tr("      Train: %1 - %2 - %3 - %4 - %5 - %6 - %7 - %8 - %9").arg( // NOI18N
                        trainId).arg(scheduleId).arg(typeId).arg(trainName).arg(trainDesc).arg(defaultSpeed).arg(startTime).arg(throttle).arg(routeDuration).arg(trainNotes));

                // Validate scheduleId
                if (!checkScheduleIds.contains(scheduleId)) {
                    log->warn(tr("Train %1 schedule id not found").arg(trainName));  // NOI18N
                    continue;
                }
                // Validate typeId
                if (!checkTypeIds.contains(typeId)) {
                    log->warn(tr("Train %1 type id not found").arg(trainName));  // NOI18N
                    continue;
                }

                // Create a train
                TTTrain* newTrain = new TTTrain(trainId, scheduleId, typeId, trainName, trainDesc,
                        defaultSpeed, startTime, throttle, routeDuration, trainNotes);
                dataMgr->addTrain(trainId, newTrain);
                checkTrainIds.append(trainId);
            }

            QDomElement stops = root.firstChildElement("stops");  // NOI18N
            if (stops.isNull()) {
                log->error("Unable to find stops");  // NOI18N
                return false;
            }
            //for (QDomElement stop : stops.firstChildElementren("stop")) {  // NOI18N
             nl = stops.elementsByTagName("stop");
             for(int i=0; i < nl.size(); i++)
             {  // NOI18N
              QDomElement stop = nl.at(i).toElement();
                QDomElement stop_id = stop.firstChildElement("stop_id");  // NOI18N
                int stopId = (stop_id.isNull()) ? 0 : stop_id.text().toInt();
                QDomElement train_id = stop.firstChildElement("train_id");  // NOI18N
                int trainId = (train_id.isNull()) ? 0 : train_id.text().toInt();
                QDomElement station_id = stop.firstChildElement("station_id");  // NOI18N
                int stationId = (station_id.isNull()) ? 0 : station_id.text().toInt();
                QDomElement seqE = stop.firstChildElement("seq");  // NOI18N
                int seq = (seqE.isNull()) ? 0 : seqE.text().toInt();
                QDomElement durationE = stop.firstChildElement("duration");  // NOI18N
                int duration = (durationE.isNull()) ? 0 : durationE.text().toInt();
                QDomElement next_speed = stop.firstChildElement("next_speed");  // NOI18N
                int nextSpeed = (next_speed.isNull()) ? 0 : next_speed.text().toInt();
                QDomElement arrive_time = stop.firstChildElement("arrive_time");  // NOI18N
                int arriveTime = (arrive_time.isNull()) ? 0 : arrive_time.text().toInt();
                QDomElement depart_time = stop.firstChildElement("depart_time");  // NOI18N
                int departTime = (depart_time.isNull()) ? 0 : depart_time.text().toInt();
                QDomElement staging_track = stop.firstChildElement("staging_track");  // NOI18N
                int stagingTrack = (staging_track.isNull()) ? 0 : staging_track.text().toInt();
                QDomElement stop_notes = stop.firstChildElement("stop_notes");  // NOI18N
                QString stopNotes = (stop_notes.isNull()) ? "" : stop_notes.text();

                log->debug(tr("        Stop: %1 - %2 - %3 - %4 - %5 - %6 - %7 - %8- %9 - %10").arg( // NOI18N
                        stopId).arg(trainId).arg(stationId).arg(seq).arg(duration).arg(nextSpeed).arg(arriveTime).arg(departTime).arg(stagingTrack).arg(stopNotes));

                // Validate trainId
                if (!checkTrainIds.contains(trainId)) {
                    log->warn("Stop train id not found");  // NOI18N
                    continue;
                }
                // Validate stationId
                if (!checkStationIds.contains(stationId)) {
                    log->warn("Stop station id not found");  // NOI18N
                    continue;
                }

                // Create a stop
                Stop* newStop = new Stop(stopId, trainId, stationId, seq, duration,
                        nextSpeed, arriveTime, departTime, stagingTrack, stopNotes);
                dataMgr->addStop(stopId, newStop);
            }
        } catch (JDOMException ex) {
            log->error("File invalid: " + ex.getMessage());  // NOI18N
            return false;
        } catch (IOException ex) {
            log->error("Error reading file: " + ex.getMessage());  // NOI18N
            return false;
        }

        log->debug("...done");  // NOI18N
        return true;
    }


//    /*public*/ static class TimeTableXmlFile extends XmlFile {
        /*private*/ /*static*/ QString TimeTableXmlFile::fileLocation = nullptr;//FileUtil::getUserFilesPath() + "timetable/";  // NOI18N
        /*private*/ /*static*/ QString TimeTableXmlFile::demoLocation = nullptr;// FileUtil::getProgramPath() + "xml/demoTimetable/";  // NOI18N
        /*private*/ /*static*/ QString TimeTableXmlFile::baseFileName = "TimeTableData.xml";  // NOI18N

        /*public*/ /*static*/ QString TimeTableXmlFile::getDefaultFileName() {
            return getFileLocation() + getFileName();
        }

        /*public*/ File* TimeTableXmlFile::getFile(bool store) {
            // Verify that preference:timetable exists
            File* chkdir = new File(getFileLocation());
            if (!chkdir->exists()) {
                if (!chkdir->mkdirs()) {
                    TimeTableXml::log->error(tr("Create %1 failed").arg(chkdir->toString()));  // NOI18N
                    return nullptr;
                }
            }

            // Verify that the TimeTable data file exists
            File* chkfile = new File(getDefaultFileName());
            if (!chkfile->exists()) {
                // Copy the demo file
                if(demoLocation == nullptr)
                    demoLocation = FileUtil::getProgramPath() + "xml/demoTimetable/";
                File* demoFile = new File(demoLocation + baseFileName);
//                Path toPath = chkdir->toPath();
//                Path fromPath = demoFile->toPath();
                try {
                    //Files.copy(fromPath, toPath.resolve(fromPath.getFileName()), StandardCopyOption.REPLACE_EXISTING);
                 if(!QFile(demoFile->getPath()).copy(chkfile->getPath()))
                 {
                  log->error(tr("error copying %1 to %2").arg(demoFile->getPath()).arg(chkdir->getPath()));
                    throw IOException(tr("error copying %1 to %2").arg(demoFile->getPath()).arg(chkfile->getPath()));
                 }
                } catch (IOException ex) {
                    TimeTableXml::log->error("Copy TimeTable demo file failed");  // NOI18N
                    return nullptr;
                }
            }

            File* file = new File(findFile(getDefaultFileName())->fileName());
            if (file == nullptr && store) {
                TimeTableXml::log->info("create new file");  // NOI18N
                file = new File(getDefaultFileName());
            }
            return file;
        }

        /*public*/ /*static*/ QString TimeTableXmlFile::getFileName() {
            if(baseFileName.isNull()) {
               baseFileName = "TimeTableData.xml";  // NOI18N
            }
            return baseFileName;
        }

        /**
         * Absolute path to location of TimeTable files.
         *
         * @return path to location
         */
        /*public*/ /*static*/ QString TimeTableXmlFile::getFileLocation() {
            if(fileLocation.isNull()){
               fileLocation = FileUtil::getUserFilesPath() + "timetable/";  // NOI18N
            }
            return fileLocation;
        }


/*private*/ /*final*/ /*static*/ Logger* TimeTableXml::log = LoggerFactory::getLogger("TimeTableXml");
/*private*/ /*final*/ /*static*/ Logger* TimeTableXmlFile::log = LoggerFactory::getLogger("TimeTableXmlFile");


} // namespace TimeTable
