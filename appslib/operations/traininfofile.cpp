#include "traininfofile.h"
#include "fileutil.h"
#include "file.h"
#include "stringutil.h"
#include "traininfo.h"
#include "QDomElement"
#include "activetrain.h"

//TrainInfoFile::TrainInfoFile()
//{

//}
/**
 * Handles reading and writing of TrainInfo files to disk as an XML file to/from
 * the dispatcher/traininfo/ directory in the user's preferences area
 * <p>
 * This class manipulates the files conforming to the dispatcher-traininfo DTD
 * <p>
 * The file is written when the user requests that train information be saved. A
 * TrainInfo file is read when the user request it in the Activate New Train
 * window
 *
 * <P>
 * This file is part of JMRI.
 * <P>
 * JMRI is open source software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published by the
 * Free Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * @author	Dave Duchamp Copyright (C) 2009
 */
///*public*/ class TrainInfoFile extends jmri.jmrit.XmlFile {

//    static final ResourceBundle rb = ResourceBundle
//            .getBundle("jmri.jmrit.dispatcher.DispatcherBundle");

/*public*/ TrainInfoFile::TrainInfoFile() : XmlFile() {
    //super();
 log = new Logger("TrainInfoFile");
// operational variables
 fileLocation = FileUtil::getUserFilesPath()
     + "dispatcher" + File::separator + "traininfo" + File::separator;


}

/*public*/ void TrainInfoFile::setFileLocation(QString testLocation) {
    fileLocation = testLocation;
}
//private Document doc = NULL;
//private QDomElement root = NULL;

/*
 *  Reads Dispatcher TrainInfo from a file in the user's preferences directory
 *  If the file containing Dispatcher TrainInfo does not exist this routine returns quietly.
 *  "name" is assumed to have the .xml or .XML extension already included
 */
/*public*/ TrainInfo* TrainInfoFile::readTrainInfo(QString name) //throws org.jdom2.JDOMException, java.io.IOException
{
    log->debug(tr("entered readTrainInfo for %1").arg(name));
    TrainInfo* tInfo = NULL;
    // check if file exists
    if (checkFile(fileLocation + name)) {
        // file is present.
        tInfo = new TrainInfo();
        root = rootFromName(fileLocation + name);
        if (root != QDomElement()) {
            // there is a file
            QDomElement traininfo = root.firstChildElement("traininfo");
            if (traininfo != QDomElement()) {
                // there are train info options defined, read them
                if (traininfo.attribute("transitname") != NULL) {
                    // there is a transit name selected
                    tInfo->setTransitName(traininfo.attribute("transitname"));
                } else {
                    log->error("Transit name missing when reading TrainInfoFile " + name);
                }
                if (traininfo.attribute("trainname") != NULL) {
                    // there is a transit name selected
                    tInfo->setTrainName(traininfo.attribute("trainname"));
                } else {
                    log->error("Train name missing when reading TrainInfoFile " + name);
                }
                if (traininfo.attribute("dccaddress") != NULL) {
                    tInfo->setDCCAddress(traininfo.attribute("dccaddress"));
                } else {
                    log->error("DCC Address missing when reading TrainInfoFile " + name);
                }
                if (traininfo.attribute("trainintransit") != NULL) {
                    tInfo->setTrainInTransit(true);
                    if (traininfo.attribute("trainintransit") == ("no")) {
                        tInfo->setTrainInTransit(false);
                    }
                } else {
                    log->error("Train in Transit check box missing  when reading TrainInfoFile " + name);
                }
                if (traininfo.attribute("startblockname") != NULL) {
                    // there is a transit name selected
                    tInfo->setStartBlockName(traininfo.attribute("startblockname"));
                } else {
                    log->error("Start block name missing when reading TrainInfoFile " + name);
                }
                if (traininfo.attribute("endblockname") != NULL) {
                    // there is a transit name selected
                    tInfo->setDestinationBlockName(traininfo.attribute("endblockname"));
                } else {
                    log->error("Destination block name missing when reading TrainInfoFile " + name);
                }
                if (traininfo.attribute("trainfromroster") != NULL) {
                    tInfo->setTrainFromRoster(true);
                    if (traininfo.attribute("trainfromroster") == ("no")) {
                        tInfo->setTrainFromRoster(false);
                    }
                }
                if (traininfo.attribute("trainfromtrains") != NULL) {
                    tInfo->setTrainFromTrains(true);
                    if (traininfo.attribute("trainfromtrains") == ("no")) {
                        tInfo->setTrainFromTrains(false);
                    }
                }
                if (traininfo.attribute("trainfromuser") != NULL) {
                    tInfo->setTrainFromUser(true);
                    if (traininfo.attribute("trainfromuser") == ("no")) {
                        tInfo->setTrainFromUser(false);
                    }
                }
                if (traininfo.attribute("priority") != NULL) {
                    tInfo->setPriority(traininfo.attribute("priority").toInt());
                } else {
                    log->error("Priority missing when reading TrainInfoFile " + name);
                }
                if (traininfo.attribute("allocatealltheway") != NULL) {
                    tInfo->setAllocateAllTheWay(true);
                    if (traininfo.attribute("allocatealltheway") == ("no")) {
                        tInfo->setAllocateAllTheWay(false);
                    }
                }

                if (traininfo.attribute("resetwhendone") != NULL) {
                    tInfo->setResetWhenDone(true);
                    if (traininfo.attribute("resetwhendone") == ("no")) {
                        tInfo->setResetWhenDone(false);
                    }
                    if (traininfo.attribute("delayedrestart") != NULL) {
                        if (traininfo.attribute("delayedrestart") == ("no")) {
                            tInfo->setDelayedRestart(ActiveTrain::NODELAY);
                        } else if (traininfo.attribute("delayedrestart") == ("sensor")) {
                            tInfo->setDelayedRestart(ActiveTrain::SENSORDELAY);
                            if (traininfo.attribute("delayedrestartsensor") != NULL) {
                                tInfo->setRestartSensorName(traininfo.attribute("delayedrestartsensor"));
                            }
                        } else if (traininfo.attribute("delayedrestart") == ("timed")) {
                            tInfo->setDelayedRestart(ActiveTrain::TIMEDDELAY);
                            if (traininfo.attribute("delayedrestarttime") != NULL) {
                                tInfo->setRestartDelayMin((int) traininfo.attribute("delayedrestarttime").toInt());
                            }
                        }
                    }
                }
                if (traininfo.attribute("reverseatend") != NULL) {
                    tInfo->setReverseAtEnd(true);
                    if (traininfo.attribute("reverseatend") == ("no")) {
                        tInfo->setReverseAtEnd(false);
                    }
                }
                if (traininfo.attribute("delayedstart") != NULL) {
                    if (traininfo.attribute("delayedstart") == ("no")) {
                        tInfo->setDelayedStart(ActiveTrain::NODELAY);
                    } else if (traininfo.attribute("delayedstart") == ("sensor")) {
                        tInfo->setDelayedStart(ActiveTrain::SENSORDELAY);
                    } else { //This covers the old versions of the file with "yes"
                        tInfo->setDelayedStart(ActiveTrain::TIMEDDELAY);
                    }
                }
                if (traininfo.attribute("departuretimehr") != NULL) {
                    tInfo->setDepartureTimeHr(traininfo.attribute("departuretimehr").toInt());
                }
                if (traininfo.attribute("departuretimemin") != NULL) {
                    tInfo->setDepartureTimeMin(traininfo.attribute("departuretimemin").toInt());
                }
                if (traininfo.attribute("delayedSensor") != NULL) {
                    tInfo->setDelaySensorName(traininfo.attribute("delayedSensor"));
                }
                if (traininfo.attribute("traintype") != NULL) {
                    tInfo->setTrainType(traininfo.attribute("traintype"));
                }
                if (traininfo.attribute("autorun") != NULL) {
                    tInfo->setAutoRun(true);
                    if (traininfo.attribute("autorun") == ("no")) {
                        tInfo->setAutoRun(false);
                    }
                }
                if (traininfo.attribute("loadatstartup") != NULL) {
                    tInfo->setLoadAtStartup(true);
                    if (traininfo.attribute("loadatstartup") == ("no")) {
                        tInfo->setLoadAtStartup(false);
                    }
                }
                // here retrieve items related only to automatically run trains if present
                if (traininfo.attribute("speedfactor") != NULL) {
                    tInfo->setSpeedFactor(traininfo.attribute("speedfactor").toFloat());
                }
                if (traininfo.attribute("maxspeed") != NULL) {
                    tInfo->setMaxSpeed(traininfo.attribute("maxspeed").toFloat());
                }
                if (traininfo.attribute("ramprate") != NULL) {
                    tInfo->setRampRate(traininfo.attribute("ramprate"));
                }
                if (traininfo.attribute("resistancewheels") != NULL) {
                    tInfo->setResistanceWheels(true);
                    if (traininfo.attribute("resistancewheels") == ("no")) {
                        tInfo->setResistanceWheels(false);
                    }
                }
                if (traininfo.attribute("runinreverse") != NULL) {
                    tInfo->setRunInReverse(true);
                    if (traininfo.attribute("runinreverse") == ("no")) {
                        tInfo->setRunInReverse(false);
                    }
                }
                if (traininfo.attribute("sounddecoder") != NULL) {
                    tInfo->setSoundDecoder(true);
                    if (traininfo.attribute("sounddecoder") == ("no")) {
                        tInfo->setSoundDecoder(false);
                    }
                }
                if (traininfo.attribute("maxtrainlength") != NULL) {
                    tInfo->setMaxTrainLength(traininfo.attribute("maxtrainlength").toFloat());
                }
                if (traininfo.attribute("terminatewhendone") != NULL) {
                    tInfo->setTerminateWhenDone(false);
                    if (traininfo.attribute("terminatewhendone") == ("yes")) {
                        tInfo->setTerminateWhenDone(true);
                    }
                }
            }
        }
    }
    return tInfo;
}

/*
 *  Writes out Dispatcher options to a file in the user's preferences directory
 */
/*public*/ void TrainInfoFile::writeTrainInfo(TrainInfo* tf, QString name) //throws java.io.IOException
{
    log->debug("entered writeTrainInfo");
#if 0
    root = doc.createElement("traininfofile");
    doc = newDocument(root, dtdLocation + "dispatcher-traininfo.dtd");
    // add XSLT processing instruction
    // <?xml-stylesheet type="text/xsl" href="XSLT/block-values.xsl"?>
    java.util.Map<String, String> m = new java.util.HashMap<String, String>();
    m.put("type", "text/xsl");
    m.put("href", xsltLocation + "dispatcher-traininfo.xsl");
    org.jdom2.ProcessingInstruction p = new org.jdom2.ProcessingInstruction("xml-stylesheet", m);
    doc.addContent(0, p);
#endif
    QDomDocument doc;
    QDomProcessingInstruction p = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
    doc.appendChild(p);
    p = doc.createProcessingInstruction("xml-stylesheet", QString("type=\"text/xsl\",href=\"%block-values.xsl\"").arg(xsltLocation));
    doc.appendChild(p);

    // create root element
    QDomElement root = doc.createElement("traininfofile");

    // save Dispatcher TrainInfo in xml format
    QDomElement traininfo = doc.createElement("traininfo");
    traininfo.setAttribute("transitname", tf->getTransitName());
    traininfo.setAttribute("trainname", tf->getTrainName());
    traininfo.setAttribute("dccaddress", tf->getDCCAddress());
    traininfo.setAttribute("trainintransit", tf->getTrainInTransit() ? "yes" : "no");
    traininfo.setAttribute("startblockname", tf->getStartBlockName());
    traininfo.setAttribute("endblockname", tf->getDestinationBlockName());
    traininfo.setAttribute("trainfromroster", (tf->getTrainFromRoster() ? "yes" : "no"));
    traininfo.setAttribute("trainfromtrains", (tf->getTrainFromTrains() ? "yes" : "no"));
    traininfo.setAttribute("trainfromuser", (tf->getTrainFromUser() ? "yes" : "no"));
    traininfo.setAttribute("priority", (tf->getPriority()));
    traininfo.setAttribute("resetwhendone", (tf->getResetWhenDone() ? "yes" : "no"));
    if (tf->getDelayedRestart() == ActiveTrain::SENSORDELAY) {
        traininfo.setAttribute("delayedrestart", "sensor");
        traininfo.setAttribute("delayedrestartsensor", tf->getRestartSensorName());
    } else if (tf->getDelayedRestart() == ActiveTrain::TIMEDDELAY) {
        traininfo.setAttribute("delayedrestart", "timed");
        traininfo.setAttribute("delayedrestarttime", (tf->getRestartDelayMin()));
    } else {
        traininfo.setAttribute("delayedrestart", "no");
    }

    traininfo.setAttribute("reverseatend",  (tf->getReverseAtEnd() ? "yes" : "no"));
    if (tf->getDelayedStart() == ActiveTrain::TIMEDDELAY) {
        traininfo.setAttribute("delayedstart", "timed");
    } else if (tf->getDelayedStart() == ActiveTrain::SENSORDELAY) {
        traininfo.setAttribute("delayedstart", "sensor");
        if (tf->getDelaySensorName() != NULL) {
            traininfo.setAttribute("delayedSensor", tf->getDelaySensorName());
        }
    }

    traininfo.setAttribute("terminatewhendone", (tf->getTerminateWhenDone() ? "yes" : "no"));
    traininfo.setAttribute("departuretimehr", (tf->getDepartureTimeHr()));
    traininfo.setAttribute("departuretimemin", (tf->getDepartureTimeMin()));
    traininfo.setAttribute("traintype", tf->getTrainType());
    traininfo.setAttribute("autorun",  (tf->getAutoRun() ? "yes" : "no"));
    traininfo.setAttribute("loadatstartup",  (tf->getLoadAtStartup() ? "yes" : "no"));
    traininfo.setAttribute("allocatealltheway",  (tf->getAllocateAllTheWay() ? "yes" : "no"));

    // here save items related to automatically running active trains
    traininfo.setAttribute("speedfactor", (tf->getSpeedFactor()));
    traininfo.setAttribute("maxspeed", (tf->getMaxSpeed()));
    traininfo.setAttribute("ramprate", tf->getRampRate());
    traininfo.setAttribute("resistancewheels",  (tf->getResistanceWheels() ? "yes" : "no"));
    traininfo.setAttribute("runinreverse",  (tf->getRunInReverse() ? "yes" : "no"));
    traininfo.setAttribute("sounddecoder",  (tf->getSoundDecoder() ? "yes" : "no"));
    traininfo.setAttribute("maxtrainlength", (tf->getMaxTrainLength()));

    root.appendChild(traininfo);

    // write out the file
    //try {
        if (!checkFile(fileLocation + name)) {
            // file does not exist, create it
            File* file = new File(fileLocation + name);
            if (!file->createNewFile()) // create file and check result
            {
                log->error("createNewFile failed");
            }
        }
        // write content to file
        writeXML(findFile(fileLocation + name), doc);
//    } catch (java.io.IOException ioe) {
//        log->error("IO Exception " + ioe);
//        throw (ioe);
//    }
}

/**
 * Get the names of all current TrainInfo files Returns names as an array of
 * Strings. Returns an empty array if no files are present. Note: Fill names
 * still end with .xml or .XML. (Modeled after a method in
 * RecreateRosterAction.java by Bob Jacobsen)
 */
/*public*/ QStringList TrainInfoFile::getTrainInfoFileNames() {
    // ensure preferences will be found for read
    FileUtil::createDirectory(fileLocation);
    // create an array of file names from roster dir in preferences, count entries
    int np = 0;
    QStringList sp = QStringList();
    if (log->isDebugEnabled()) {
        log->debug("directory of TrainInfoFiles - " + fileLocation);
    }
    File* fp = new File(fileLocation);
    if (fp->exists()) {
        sp = fp->list();
        for (int i = 0; i < sp.length(); i++) {
            if (sp[i].endsWith(".xml") || sp[i].endsWith(".XML")) {
                np++;
            }
        }
    }
    // Copy entries to the final array
    //String sbox[] = new String[np];
    QVector<QString> sbox = QVector<QString>(np);
    int n = 0;
    if ((!sp.isEmpty()) && (np > 0)) {
        for (int i = 0; i < sp.length(); i++) {
            if (sp[i].endsWith(".xml") || sp[i].endsWith(".XML")) {
                sbox.replace(n++, sp[i]);
            }
        }
    }
    // Sort the resulting array
    if ((!sp.isEmpty()) && sp.length() > 1) {
        StringUtil::sort(sbox.toList());
    }
// djd debugging - print list of TrainInfoFiles
//		log->error("TrainInfoFilename list:");
//		for (int j=0; j<sbox.length; j++) {
//			log->error("   "+(j+1)+" "+sbox[j]);
//        }
// end djd debugging
    return sbox.toList();
}

/**
 * Delete a specified TrainInfo file
 */
/*public*/ void TrainInfoFile::deleteTrainInfoFile(QString name) {
    // locate the file and delete it if it exists
    File* f = new File(fileLocation + name);
    if (!f->_delete()) // delete file and check success
    {
        log->error("failed to delete TrainInfo file - " + name);
    }
}

