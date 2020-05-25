#include "timetablecsvimport.h"
#include "loggerfactory.h"
#include "csvparser.h"
#include "file.h"
#include <QFile>
#include <QTextStream>
#include <QColor>
#include "ttschedule.h"
#include "tttrain.h"

namespace TimeTable
{
 TimeTableCsvImport::TimeTableCsvImport(QObject *parent) : QObject(parent)
 {

 }
 /**
  * CSV Record Types. The first field is the record type keyword (not I18N).
  * Most fields are optional.
  * <pre>
  * "Layout", "layout name", "scale", fastClock, throttles, "metric"
  *            Defaults:  "New Layout", "HO", 4, 0, "No"
  *            Occurs:  Must be first record, occurs once
  *
  * "TrainType", "type name", color number
  *            Defaults: "New Type", #000000
  *            Occurs:  Follows Layout record, occurs 0 to n times.  If none, a default train type is created which will be used for all trains.
  *            Notes:  #000000 is black.
  *                    If the type name is UseLayoutTypes, the train types for the current layout will be used.
  *
  * "Segment", "segment name"
  *            Default: "New Segment"
  *            Occurs: Follows last TrainType, if any.  Occurs 1 to n times.
  *
  * "Station", "station name", distance, doubleTrack, sidings, staging
  *            Defaults: "New Station", 1.0, No, 0, 0
  *            Occurs:  Follows parent segment, occurs 1 to n times.
  *            Note:  If the station name is UseSegmentStations, the stations for the current segment will be used.
  *
  * "Schedule", "schedule name", "effective date", startHour, duration
  *            Defaults:  "New Schedule", "Today", 0, 24
  *            Occurs: Follows last station, occurs 1 to n times.
  *
  * "Train", "train name", "train description", type, defaultSpeed, starttime, throttle, notes
  *            Defaults:  "NT", "New Train", 0, 1, 0, 0, ""
  *            Occurs:  Follows parent schedule, occurs 1 to n times.
  *            Note1:  The type is the relative number of the train type listed above starting with 1 for the first train type.
  *            Note2:  The start time is an integer between 0 and 1439, subject to the schedule start time and duration.
  *
  * "Stop", station, duration, nextSpeed, stagingTrack, notes
  *            Defaults:  0, 0, 0, 0, ""
  *            Required: station number.
  *            Occurs:  Follows parent train in the proper sequence.  Occurs 1 to n times.
  *            Notes:  The station is the relative number of the station listed above starting with 1 for the first station.
  *                    If more that one segment is used, the station number is cumulative.
  *
  * Except for Stops, each record can have one of three actions:
  *    1) If no name is supplied, a default object will be created.
  *    2) If the name matches an existing name, the existing object will be used.
  *    3) A new object will be created with the supplied name.  The remaining fields, if any, will replace the default values.
  *
  * Minimal file using defaults except for station names and distances:
  * "Layout"
  * "Segment"
  * "Station", "Station 1", 0.0
  * "Station", "Station 2", 25.0
  * "Schedule"
  * "Train"
  * "Stop", 1
  * "Stop", 2
  * </pre>
  * The import applies the changes to the data in memory.  At the end of the import
  * a dialog is displayed with the option to save the changes to the timetable data file.
  * @author Dave Sand Copyright (C) 2019
  * @since 4.15.3
  */
 ///*public*/ class TimeTableCsvImport {

 /*public*/ QList<QString> TimeTableCsvImport::importCsv(File* file, QObject* parent) throw (IOException) {
        tdm->setLockCalculate(true);
        errorOccurred = false;
        try {
//            fileReader = new FileReader(file);
//            bufferedReader = new BufferedReader(fileReader);
         QFile* f = QFile(file->getPath());
         if(! f->open(QIODevice::ReadOnly))
          throw FileNotFoundException();
         bufferedReader = new QTextStream(f);
            csvFile = new CSVParser(bufferedReader, CSVFormat::DEFAULT);
            for (CSVRecord* record : csvFile->getRecords()) {
                if (errorOccurred) {
                    break;
                }
                recordNumber += 1;
                if (record.size() > 0) {
                    QStringList list = QStringList();
                    record.forEach(list::add);
                    QStringList values = list.toArray(new String[record.size()]);
                    QString recd = values[0];

                    if (recd == ("Layout") && layoutId == 0) {
                        doLayout(values);
                    } else if (recd == ("TrainType") && layoutId != 0) {
                        doTrainType(values);
                    } else if (recd == ("Segment") && layoutId != 0) {
                        doSegment(values);
                    } else if (recd == ("Station") && segmentId != 0) {
                        doStation(values);
                    } else if (recd == ("Schedule") && layoutId != 0) {
                        doSchedule(values);
                    } else if (recd == ("Train") && scheduleId != 0) {
                        doTrain(values);
                    } else if (recd == ("Stop") && trainId != 0) {
                        doStop(values);
                    } else {
                        log->warn(tr("Unable to process record %1, content = %2").arg(recordNumber).arg(values));
//                        importFeedback.add(String.format("Unable to process record %d, content = %s",
//                                recordNumber, record.toString()));
                        errorOccurred = true;
                    }
                }
            }
            csvFile->close();
        } catch (IOException ex) {
            log->error("CSV Import failed: ", ex);
//            importFeedback.add(String.format("CSV Import failed: %s", ex.getMessage()));
            errorOccurred = true;
        }
        /*finally*/ {
            if(bufferedReader != nullptr) {
               bufferedReader->device()->close();
            }
//            if(fileReader != null) {
//               fileReader.close();
//            }
        }
        tdm->setLockCalculate(false);
        if (!errorOccurred) {
            // Force arrive/depart calculations
            Layout* layout = tdm.getLayout(layoutId);
            if (layout != nullptr) {
                int fastClock = layout.getFastClock();
                try {
                    layout->setFastClock(fastClock + 1);
                    layout->setFastClock(fastClock);
                } catch (IllegalArgumentException ex) {
                    log->error("Calculation error occured: ", ex);
//                    importFeedback.add(String.format("Calculation error occured: %s", ex.getMessage()));
                }
            }
        }
        return importFeedback;
    }

    void TimeTableCsvImport::doLayout(QStringList values) {
        if (recordNumber != 1) {
            log->error("Invalid file structure");
//            importFeedback.add("Invalid file structure, the first record must be a layout record.");
            errorOccurred = true;
            return;
        }
        log->debug(tr("Layout values: %1", /*Arrays.toString(values)*/pack(values)));
        if (values.length() == 1) {
            // Create default layout
            Layout* defaultLayout = new Layout();
            layoutId = defaultLayout->getLayoutId();
            return;
        }

        QString layoutName = values[1];
        for (Layout* layout : tdm->getLayouts(false)) {
            if (layout->getLayoutName() == (layoutName)) {
                // Use existing layout
                layoutId = layout->getLayoutId();
                return;
            }
        }

        // Create a new layout and set the name
        Layout* newLayout = new Layout();
        layoutId = newLayout->getLayoutId();
        newLayout->setLayoutName(layoutName);

        // Change the defaults to the supplied values if available
        QString scaleName = (values.length() > 2) ? values[2] : "HO";
        Scale* scale = ScaleManager::getScale(scaleName);
        if (scale != nullptr) {
            newLayout->setScale(scale);
        }

        QString clockString = (values.length() > 3) ? values[3] : "4";
        int clock = convertToInteger(clockString);
        if (clock > 0) {
            newLayout->setFastClock(clock);
        }

        QString throttlesString = (values.length() > 4) ? values[4] : "0";
        int throttles = convertToInteger(throttlesString);
        if (throttles >= 0) {
            newLayout->setThrottles(throttles);
        }

        QString metric = (values.length() > 5) ? values[5] : "No";
        if (metric == ("Yes") || metric == ("No")) {
            newLayout->setMetric((metric == ("Yes")));
        }
    }

    void TimeTableCsvImport::doTrainType(QStringList values) {
        log->debug(tr("TrainType values: %1").arg(/*Arrays.toString*/pack(values));
        if (values.length == 1) {
            // Create default train type
            TrainType* defaultType = new TrainType(layoutId);
            trainTypes.append(defaultType->getTypeId());
            return;
        }

        QString typeName = values[1];
        if (typeName == ("UseLayoutTypes")) {
            //tdm->getTrainTypes(layoutId, true).forEach((currType) ->
            foreach(TrainType* currType, tdm->getTrainTypes(layoutId, true))
            {
                trainTypes.append(currType->getTypeId());
            }//);
            return;
        }
        for (TrainType* trainType : tdm->getTrainTypes(layoutId, false)) {
            if (trainType->getTypeName() == (typeName)) {
                // Use existing train type
                trainTypes.append(trainType->getTypeId());
                return;
            }
        }

        // Create a new train type and set the name and color if available
        TrainType* newType = new TrainType(layoutId);
        trainTypes.append(newType->getTypeId());
        newType->setTypeName(typeName);

        QString typeColor = (values.length > 2) ? values[2] : "#000000";
        try {
            QColor checkColor = QColor(typeColor);
            log->debug(tr("Color = %1").arg(checkColor.name());
            newType->setTypeColor(typeColor);
        } catch (NumberFormatException ex) {
            log->error("Invalid color value");
        }
    }

    void TimeTableCsvImport::doSegment(QStringList values) {
        if (recordNumber == 2) {
            // No  train type, create one
            TrainType* trainType = new TrainType(layoutId);
            trainTypes.append(trainType->getTypeId());
        }

        log->debug(tr("Segment values: %1").arg(/*Arrays.toString*/pack(values));
        if (values.length() == 1) {
            // Create default segment
            Segment* defaultSegment = new Segment(layoutId);
            segmentId = defaultSegment->getSegmentId();
            return;
        }

        QString segmentName = values[1];
        for (Segment* segment : tdm->getSegments(layoutId, false)) {
            if (segment->getSegmentName() == (segmentName)) {
                // Use existing segment
                segmentId = segment->getSegmentId();
                return;
            }
        }

        // Create a new segment
        Segment* newSegment = new Segment(layoutId);
        newSegment->setSegmentName(segmentName);
        segmentId = newSegment->getSegmentId();
    }

    void TimeTableCsvImport::doStation(QStringList values) {
        log->debug(tr("Station values: %1").arg(/*Arrays.toString*/pack(values));
        if (values.length() == 1) {
            // Create default station
            Station* defaultStation = new Station(segmentId);
            stations.append(defaultStation->getStationId());
            return;
        }

        QString stationName = values[1];
        if (stationName == ("UseSegmentStations")) {
            //tdm.getStations(segmentId, true).forEach((currStation) -> {
            foreach(Station* currStation, tdm->getStations(segmentId, true))
            {
                stations.append(currStation->getStationId());
            }//);
            return;
        }
        for(Station* station : tdm->getStations(segmentId, false)) {
            if (station->getStationName() == (stationName)) {
                // Use existing station
                stations.append(station->getStationId());
                return;
            }
        }

        // Create a new station
        Station* newStation = new Station(segmentId);
        newStation->setStationName(stationName);
        stations.append(newStation->getStationId());

        // Change the defaults to the supplied values if available
        QString distanceString = (values.length() > 2) ? values[2] : "1.0";
        double distance = convertToDouble(distanceString);
        if (distance >= 0.0) {
            newStation->setDistance(distance);
        }

        QString doubleTrack = (values.length() > 3) ? values[3] : "No";
        if (doubleTrack == ("Yes") || doubleTrack == ("No")) {
            newStation->setDoubleTrack((doubleTrack == ("Yes")));
        }

        QString sidingsString = (values.length() > 4) ? values[4] : "0";
        int sidings = convertToInteger(sidingsString);
        if (sidings >= 0) {
            newStation->setSidings(sidings);
        }

        QString stagingString = (values.length() > 5) ? values[5] : "0";
        int staging = convertToInteger(stagingString);
        if (staging >= 0) {
            newStation->setStaging(staging);
        }
    }

    void TimeTableCsvImport::doSchedule(QStringList values) {
        log->debug(tr("Schedule values: %1").arg(/*Arrays.toString*/pack(values));
        if (values.length() == 1) {
            // Create default schedule
            TTSchedule* defaultSchedule = new TTSchedule(layoutId);
            scheduleId = defaultSchedule->getScheduleId();
            return;
        }

        QString scheduleName = values[1];
        for (TTSchedule* schedule : tdm->getSchedules(layoutId, false)) {
            if (schedule->getScheduleName() == (scheduleName)) {
                // Use existing schedule
                scheduleId = schedule->getScheduleId();
                return;
            }
        }

        // Create a new schedule
        TTSchedule* newSchedule = new TTSchedule(layoutId);
        newSchedule->setScheduleName(scheduleName);
        scheduleId = newSchedule->getScheduleId();

        // Change the defaults to the supplied values if available
        QString effectiveDate = (values.length() > 2) ? values[2] : "Today";
        if (!effectiveDate.isEmpty()) {
            newSchedule->setEffDate(effectiveDate);
        }

        QString startString = (values.length() > 3) ? values[3] : "0";
        int startHour = convertToInteger(startString);
        if (startHour >= 0 && startHour < 24) {
            newSchedule->setStartHour(startHour);
        }

        QString durationString = (values.length() > 4) ? values[4] : "24";
        int duration = convertToInteger(durationString);
        if (duration > 0 && duration < 25) {
            newSchedule->setDuration(duration);
        }
    }

    void TimeTableCsvImport::doTrain(QStringList values) {
        log->debug(tr("Train values: %1").arg(/*Arrays.toString*/pack(values));
        if (values.length() == 1) {
            // Create default train
            TTTrain* defaultTrain = new TTTrain(scheduleId);
            defaultTrain->setTypeId(trainTypes.at(0));  // Set default train type using first type
            trainId = defaultTrain->getTrainId();
            return;
        }

        QString trainName = values[1];
        for (TTTrain* train : tdm->getTrains(scheduleId, 0, false)) {
            if (train->getTrainName() == (trainName)) {
                // Use existing train
                trainId = train->getTrainId();
                return;
            }
        }

        // Create a new train
        TTTrain* newTrain = new TTTrain(scheduleId);
        newTrain->setTrainName(trainName);
        newTrain->setTypeId(trainTypes.at(0));  // Set default train type using first type
        trainId = newTrain->getTrainId();

        // Change the defaults to the supplied values if available
        QString description = (values.length() > 2) ? values[2] : "";
        if (!description.isEmpty()) {
            newTrain->setTrainDesc(description);
        }

        QString typeIndexString = (values.length() > 3) ? values[3] : "1";
        int typeIndex = convertToInteger(typeIndexString);
        typeIndex -= 1;      // trainTypes list is 0 to n-1
        if (typeIndex >= 0 && typeIndex < trainTypes.size()) {
            newTrain->setTypeId(trainTypes.at(typeIndex));
        }

        QString speedString = (values.length() > 4) ? values[4] : "1";
        int defaultSpeed = convertToInteger(speedString);
        if (defaultSpeed >= 0) {
            newTrain->setDefaultSpeed(defaultSpeed);
        }

        QString startTimeString = (values.length > 5) ? values[5] : "0";
        int startTime = convertToInteger(startTimeString);
        if (startTime >= 0 && startTime < 1440) {
            // Validate time
            TTSchedule* schedule = tdm->getSchedule(scheduleId);
            if (tdm->validateTime(schedule->getStartHour(), schedule->getDuration(), startTime)) {
                newTrain->setStartTime(startTime);
            } else {
                errorOccurred = true;
                log->error(tr("Train start time outside of schedule time: %1").arg(startTime));
//                importFeedback.add(String.format("Train start time outside of schedule time: %d", startTime));
            }
        }

        QString throttleString = (values.length > 6) ? values[6] : "0";
        int throttle = convertToInteger(throttleString);
        int throttles = tdm->getLayout(layoutId)->getThrottles();
        if (throttle >= 0 && throttle <= throttles) {
            newTrain->setThrottle(throttle);
        }

        QString trainNotes = (values.length > 7) ? values[7] : "";
        if (!trainNotes.isEmpty()) {
            newTrain->setTrainNotes(trainNotes);
        }
    }

    void TimeTableCsvImport::doStop(QStringList values) {
        // The stop sequence number is one higher than the last sequence number.
        // Each stop record creates a new stop.
        // Stops don't reuse any existing entries.
        log->debug(tr("Stop values: %1").arg(/*Arrays.toString*/pack(values));
        QString stopStationString = (values.length() > 1) ? values[1] : "-1";
        int stopStationIndex = convertToInteger(stopStationString);
        stopStationIndex -= 1;       // stations list is 0 to n-1
        if (stopStationIndex >= 0 && stopStationIndex < stations.size()) {
            QList<Stop*> stops = tdm->getStops(trainId, 0, false);
            Stop* newStop = new Stop(trainId, stops.size() + 1);
            newStop->setStationId(stations.at(stopStationIndex));

            // Change the defaults to the supplied values if available
            QString durationString = (values.length() > 2) ? values[2] : "0";
            int stopDuration = convertToInteger(durationString);
            if (stopDuration > 0) {
                newStop->setDuration(stopDuration);
            }

            QString nextSpeedString = (values.length() > 3) ? values[3] : "0";
            int nextSpeed = convertToInteger(nextSpeedString);
            if (nextSpeed > 0) {
                newStop->setNextSpeed(nextSpeed);
            }

            QString stagingString = (values.length() > 4) ? values[4] : "0";
            int stagingTrack = convertToInteger(stagingString);
            Station* station = tdm->getStation(stations.at(stopStationIndex));
            if (stagingTrack >= 0 && stagingTrack <= station->getStaging()) {
                newStop->setStagingTrack(stagingTrack);
            }

            QString stopNotes = (values.length() > 5) ? values[5] : "";
            if (!stopNotes.isEmpty()) {
                newStop->setStopNotes(stopNotes);
            }
        }
    }

    int TimeTableCsvImport::convertToInteger(QString number) {
        bool bok;
            return number.toInt(&bok);
        if(!bok) {
            return -1;
        }
    }

    double TimeTableCsvImport::convertToDouble(QString number) {
     bool bok;
         return number.toDouble(&bok);
     if(!bok) {
            return -1.0;
        }
    }

    QString pack(QStringList const& list)
    {
        return list.join('|');
    }
    /*private*/ /*final*/ /*static*/ Logger* TimeTableCsvImport::log = LoggerFactory::getLogger("TimeTableCsvImport");

