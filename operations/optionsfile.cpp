#include "optionsfile.h"
#include "loggerfactory.h"
#include "fileutil.h"
#include "layouteditor.h"
#include "panelmenu.h"
#include "dispatcherframe.h"
#include "scalemanager.h"
/**
 * Handles reading and writing of Dispatcher options to disk as an XML file
 * called "dispatcher-options.xml" in the user's preferences area.
 * <p>
 * This class manipulates the files conforming to the dispatcher-options DTD
 * <p>
 * The file is written when the user requests that options be saved. If the
 * dispatcheroptions.xml file is present when Dispatcher is started, it is read
 * and options set accordingly
 * <p>
 * This file is part of JMRI.
 * <p>
 * JMRI is open source software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published by the
 * Free Software Foundation. See the "COPYING" file for a copy of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * @author Dave Duchamp Copyright (C) 2008
 */

// /*public*/ class OptionsFile extends jmri.jmrit.XmlFile implements InstanceManagerAutoDefault {

    /*public*/ OptionsFile::OptionsFile(QObject* parent) : XmlFile(parent) {
        //super();
     setProperty("InstanceManagerAutoDefault", "yes");

    }

    // operational variables
    /*private*/ /*static*/ QString OptionsFile::defaultFileName = FileUtil::getUserFilesPath() + "dispatcheroptions.xml";

    /*public*/ /*static*/ void OptionsFile::setDefaultFileName(QString testLocation) {
        defaultFileName = testLocation;
    }

    /**
     * Read Dispatcher Options from a file in the user's preferences directory.
     * If the file containing Dispatcher Options does not exist, this routine returns quietly.
     * @param f   The dispatcher instance.
     * @throws org.jdom2.JDOMException  if dispatcher parameter logically incorrect
     * @throws java.io.IOException    if dispatcher parameter not found
     */
    /*public*/ void OptionsFile::readDispatcherOptions(DispatcherFrame* f) //throw (JDOMException, IOException)
    {
        // check if file exists
        if (checkFile(defaultFileName)) {
            // file is present,
            log->debug(tr("Reading Dispatcher options from file %1").arg(defaultFileName));
            root = rootFromName(defaultFileName);
            dispatcher = f;
            if (!root.isNull()) {
                // there is a file
                QDomElement options = root.firstChildElement("options");
                if (!options.isNull()) {
                    // there are options defined, read and set Dispatcher options
                    if (options.attribute("lename") != "") {
                        // there is a layout editor name selected
                        QString leName = options.attribute("lename");
                        // get list of Layout Editor panels
                        QList<LayoutEditor*>* layoutEditorList = ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getLayoutEditorPanelList();
                        if (layoutEditorList->isEmpty()) {
                            log->warn("Dispatcher options specify a Layout Editor panel that is not present.");
                        } else {
                            bool found = false;
                            for (int i = 0; i < layoutEditorList->size(); i++) {
                                if (leName == (layoutEditorList->at(i)->getTitle())) {
                                    found = true;
                                    dispatcher->setLayoutEditor(layoutEditorList->at(i));
                                }
                            }
                            if (!found) {
                                log->warn(tr("Layout Editor panel - %1 - not found.").arg(leName));
                            }
                        }
                    }
                    if (options.attribute("usesignaltype") != "") {
                        dispatcher->setSignalType(0x00);
                        if (options.attribute("usesignaltype") == ("signalmast")) {
                            dispatcher->setSignalType(0x01);
                        }
                    }
                    if (options.attribute("useconnectivity") != "") {
                        dispatcher->setUseConnectivity(true);
                        if (options.attribute("useconnectivity") == ("no")) {
                            dispatcher->setUseConnectivity(false);
                        }
                    }
                    if (options.attribute("trainsfromroster") != "") {
                        dispatcher->setTrainsFromRoster(true);
                        if (options.attribute("trainsfromroster") == ("no")) {
                            dispatcher->setTrainsFromRoster(false);
                        }
                    }
                    if (options.attribute("trainsfromtrains") != "") {
                        dispatcher->setTrainsFromTrains(true);
                        if (options.attribute("trainsfromtrains") == ("no")) {
                            dispatcher->setTrainsFromTrains(false);
                        }
                    }
                    if (options.attribute("trainsfromuser") != "") {
                        dispatcher->setTrainsFromUser(true);
                        if (options.attribute("trainsfromuser") == ("no")) {
                            dispatcher->setTrainsFromUser(false);
                        }
                    }
                    if (options.attribute("autoallocate") != "") {
                        dispatcher->setAutoAllocate(false);
                        if (options.attribute("autoallocate") == ("yes")) {
                            dispatcher->setAutoAllocate(true);
                        }
                    }
                    if (options.attribute("autoturnouts") != "") {
                        dispatcher->setAutoTurnouts(true);
                        if (options.attribute("autoturnouts") == ("no")) {
                            dispatcher->setAutoTurnouts(false);
                        }
                    }
                    if (options.attribute("trustknownturnouts") != "") {
                        dispatcher->setTrustKnownTurnouts(false);
                        if (options.attribute("trustknownturnouts") == ("yes")) {
                            dispatcher->setTrustKnownTurnouts(true);
                        }
                    }
                    if (options.attribute("minthrottleinterval") != "") {
                        QString s = (options.attribute("minthrottleinterval"));
                        dispatcher->setMinThrottleInterval((s.toInt()));
                    }
                    if (options.attribute("fullramptime") != "") {
                        QString s = (options.attribute("fullramptime"));
                        dispatcher->setFullRampTime(s.toInt());
                    }
                    if (options.attribute("hasoccupancydetection") != "") {
                        dispatcher->setHasOccupancyDetection(true);
                        if (options.attribute("hasoccupancydetection") == ("no")) {
                            dispatcher->setHasOccupancyDetection(false);
                        }
                    }
                    if (options.attribute("shortactivetrainnames") != "") {
                        dispatcher->setShortActiveTrainNames(true);
                        if (options.attribute("shortactivetrainnames") == ("no")) {
                            dispatcher->setShortActiveTrainNames(false);
                        }
                    }
                    if (options.attribute("shortnameinblock") != "") {
                        dispatcher->setShortNameInBlock(true);
                        if (options.attribute("shortnameinblock") == ("no")) {
                            dispatcher->setShortNameInBlock(false);
                        }
                    }
                    if (options.attribute("extracolorforallocated") != "") {
                        dispatcher->setExtraColorForAllocated(true);
                        if (options.attribute("extracolorforallocated") == ("no")) {
                            dispatcher->setExtraColorForAllocated(false);
                        }
                    }
                    if (options.attribute("nameinallocatedblock") != "") {
                        dispatcher->setNameInAllocatedBlock(true);
                        if (options.attribute("nameinallocatedblock") == ("no")) {
                            dispatcher->setNameInAllocatedBlock(false);
                        }
                    }
                    if (options.attribute("supportvsdecoder") != "") {
                        dispatcher->setSupportVSDecoder(true);
                        if (options.attribute("supportvsdecoder") == ("no")) {
                            dispatcher->setSupportVSDecoder(false);
                        }
                    }
                    if (options.attribute("layoutscale") != "") {
                        QString s = (options.attribute("layoutscale"));
                        dispatcher->setScale(ScaleManager::getScale(s));
                    }
                    if (options.attribute("usescalemeters") != "") {
                        dispatcher->setUseScaleMeters(true);
                        if (options.attribute("usescalemeters") == ("no")) {
                            dispatcher->setUseScaleMeters(false);
                        }
                    }
                    if (options.attribute("userosterentryinblock") != "") {
                        dispatcher->setRosterEntryInBlock(false);
                        if (options.attribute("userosterentryinblock") == ("yes")) {
                            dispatcher->setRosterEntryInBlock(true);
                        }
                    }
                    if (options.attribute("stoppingspeedname") != "") {
                        dispatcher->setStoppingSpeedName((options.attribute("stoppingspeedname")));
                    }
                }
            }
        } else {
            log->debug(tr("No Dispatcher options file found at %1, using defaults").arg(defaultFileName));
        }
    }

    /**
     * Write out Dispatcher options to a file in the user's preferences directory.
     * @param f Dispatcher instance.
     * @throws java.io.IOException Thrown if dispatcher option file not found
     */
    /*public*/ void OptionsFile::writeDispatcherOptions(DispatcherFrame* f) //throw (IOException)
    {
        log->debug(tr("Saving Dispatcher options to file %1").arg(defaultFileName));
        dispatcher = f;
        doc = QDomDocument();

#if 1
        root = doc.createElement("dispatcheroptions");
//        doc = newDocument(root, dtdLocation + "dispatcher-options.dtd");
        // add XSLT processing instruction
        // <?xml-stylesheet type="text/xsl" href="XSLT/block-values.xsl"?>
//        java.util.Map<String, String> m = new java.util.HashMap<>();
//        m.put("type", "text/xsl");
//        m.put("href", xsltLocation + "dispatcheroptions.xsl");
//        org.jdom2.ProcessingInstruction p = new org.jdom2.ProcessingInstruction("xml-stylesheet", m);
//        doc.addContent(0, p);
        doc.appendChild(root);

        // save Dispatcher Options in xml format
        QDomElement options = doc.createElement("options");
        LayoutEditor* le = dispatcher->getLayoutEditor();
        if (le != nullptr) {
            options.setAttribute("lename", le->getTitle());
        }
        options.setAttribute("useconnectivity", (dispatcher->getUseConnectivity() ? "yes" : "no"));
        options.setAttribute("trainsfromroster", (dispatcher->getTrainsFromRoster() ? "yes" : "no"));
        options.setAttribute("trainsfromtrains", (dispatcher->getTrainsFromTrains() ? "yes" : "no"));
        options.setAttribute("trainsfromuser", (dispatcher->getTrainsFromUser() ? "yes" : "no"));
        options.setAttribute("autoallocate", (dispatcher->getAutoAllocate() ? "yes" : "no"));
        options.setAttribute("autoturnouts", (dispatcher->getAutoTurnouts() ? "yes" : "no"));
        options.setAttribute("trustknownturnouts", (dispatcher->getTrustKnownTurnouts() ? "yes" : "no"));
        options.setAttribute("minthrottleinterval", (dispatcher->getMinThrottleInterval()));
        options.setAttribute("fullramptime", (dispatcher->getFullRampTime()));
        options.setAttribute("hasoccupancydetection", (dispatcher->getHasOccupancyDetection() ? "yes" : "no"));
        options.setAttribute("shortactivetrainnames", (dispatcher->getShortActiveTrainNames() ? "yes" : "no"));
        options.setAttribute("shortnameinblock", (dispatcher->getShortNameInBlock() ? "yes" : "no"));
        options.setAttribute("extracolorforallocated", (dispatcher->getExtraColorForAllocated() ? "yes" : "no"));
        options.setAttribute("nameinallocatedblock", (dispatcher->getNameInAllocatedBlock() ? "yes" : "no"));
        options.setAttribute("supportvsdecoder", (dispatcher->getSupportVSDecoder() ? "yes" : "no"));
        options.setAttribute("layoutscale", dispatcher->getScale()->getScaleName());
        options.setAttribute("usescalemeters", (dispatcher->getUseScaleMeters() ? "yes" : "no"));
        options.setAttribute("userosterentryinblock", (dispatcher->getRosterEntryInBlock() ? "yes" : "no"));
        options.setAttribute("stoppingspeedname", dispatcher->getStoppingSpeedName());
        if (dispatcher->getSignalType() == 0x00) {
            options.setAttribute("usesignaltype", "signalhead");
        } else {
            options.setAttribute("usesignaltype", "signalmast");
        }
        root.appendChild(options);

        // write out the file
        try {
            if (!checkFile(defaultFileName)) {
                // file does not exist, create it
                File* file = new File(defaultFileName);
                if (!file->createNewFile()) // create new file and check result
                {
                    log->error("createNewFile failed");
                }
            }
            // write content to file
            writeXML(findFile(defaultFileName), doc);
        } catch (IOException ioe) {
            log->error(tr("IO Exception %1").arg(ioe.getMessage()));
            throw (ioe);
        }
#endif
    }

    /*private*/ /*final*/ /*static*/ Logger* OptionsFile::log = LoggerFactory::getLogger("OptionsFile");
