#include "ctcmanagerxml.h"
#include "loggerfactory.h"
#include "codebuttonhandlerdata.h"
#include "ctcserialdata.h"
#include "programproperties.h"
#include "otherdata.h"
#include "codebuttonhandlerdataroutines.h"
#include <QMetaEnum>
/**
 * Provides the functionality for persistence of the CTC tool data.  The data is stored
 * in the PanelPro data xml file using the standard Load/Store process.
 *
 * @author Dave Sand Copyright (c) 2020
 */
// /*public*/ class CtcManagerXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/ CtcManagerXml::CtcManagerXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent) {
    }

    /**
     * Implementation for storing the contents of the CTC configuration.
     *
     * @param o Object to store, of type CtcManager
     * @return  QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement CtcManagerXml::store(QObject o) {
         QDomElement ctcdata =  doc.createElement("ctcdata");
        setStoreElementClass(ctcdata);

        ctcdata.appendChild(storeProperties(cm));
        ctcdata.appendChild(storeOtherData(cm));
        for (CodeButtonHandlerData* cbhd : cm->getCTCSerialData()->getCodeButtonHandlerDataArrayList()) {
             QDomElement cbhdElement =  doc.createElement("ctcCodeButtonData");

            cbhdElement.appendChild(storeInt("UniqueID", cbhd->_mUniqueID));
            cbhdElement.appendChild(storeInt("SwitchNumber", cbhd->_mSwitchNumber));
            cbhdElement.appendChild(storeInt("SignalEtcNumber", cbhd->_mSignalEtcNumber));
            cbhdElement.appendChild(storeInt("GUIColumnNumber", cbhd->_mGUIColumnNumber));

            // Code section
            cbhdElement.appendChild(storeSensor("CodeButtonInternalSensor", cbhd->_mCodeButtonInternalSensor));
            cbhdElement.appendChild(storeSensor("OSSectionOccupiedExternalSensor", cbhd->_mOSSectionOccupiedExternalSensor));
            cbhdElement.appendChild(storeSensor("OSSectionOccupiedExternalSensor2", cbhd->_mOSSectionOccupiedExternalSensor2));
            cbhdElement.appendChild(storeInt("OSSectionSwitchSlavedToUniqueID", cbhd->_mOSSectionSwitchSlavedToUniqueID));
            cbhdElement.appendChild(storeBoolean("GUIGeneratedAtLeastOnceAlready", cbhd->_mGUIGeneratedAtLeastOnceAlready));
            cbhdElement.appendChild(storeInt("CodeButtonDelayTime", cbhd->_mCodeButtonDelayTime));

            // SIDI section
            cbhdElement.appendChild(storeBoolean("SIDI_Enabled", cbhd->_mSIDI_Enabled));
            cbhdElement.appendChild(storeSensor("SIDI_LeftInternalSensor", cbhd->_mSIDI_LeftInternalSensor));
            cbhdElement.appendChild(storeSensor("SIDI_NormalInternalSensor", cbhd->_mSIDI_NormalInternalSensor));
            cbhdElement.appendChild(storeSensor("SIDI_RightInternalSensor", cbhd->_mSIDI_RightInternalSensor));
            cbhdElement.appendChild(storeInt("SIDI_CodingTimeInMilliseconds", cbhd->_mSIDI_CodingTimeInMilliseconds));
            cbhdElement.appendChild(storeInt("SIDI_TimeLockingTimeInMilliseconds", cbhd->_mSIDI_TimeLockingTimeInMilliseconds));
            QMetaEnum metaEnum = QMetaEnum::fromType<CodeButtonHandlerData::TRAFFIC_DIRECTION>();
            QString s = metaEnum.valueToKey(cbhd->_mSIDI_TrafficDirection);
            cbhdElement.appendChild(storeString("SIDI_TrafficDirection", s));//cbhd->_mSIDI_TrafficDirection.toString()));
            cbhdElement.appendChild(storeSignalList("SIDI_LeftRightTrafficSignals", cbhd->_mSIDI_LeftRightTrafficSignals));
            cbhdElement.appendChild(storeSignalList("SIDI_RightLeftTrafficSignals", cbhd->_mSIDI_RightLeftTrafficSignals));

            // SIDL section
            cbhdElement.appendChild(storeBoolean("SIDL_Enabled", cbhd->_mSIDL_Enabled));
            cbhdElement.appendChild(storeSensor("SIDL_LeftInternalSensor", cbhd->_mSIDL_LeftInternalSensor));
            cbhdElement.appendChild(storeSensor("SIDL_NormalInternalSensor", cbhd->_mSIDL_NormalInternalSensor));
            cbhdElement.appendChild(storeSensor("SIDL_RightInternalSensor", cbhd->_mSIDL_RightInternalSensor));

            // SWDI section
            cbhdElement.appendChild(storeBoolean("SWDI_Enabled", cbhd->_mSWDI_Enabled));
            cbhdElement.appendChild(storeSensor("SWDI_NormalInternalSensor", cbhd->_mSWDI_NormalInternalSensor));
            cbhdElement.appendChild(storeSensor("SWDI_ReversedInternalSensor", cbhd->_mSWDI_ReversedInternalSensor));
            cbhdElement.appendChild(storeTurnout("SWDI_ExternalTurnout", cbhd->_mSWDI_ExternalTurnout));
            cbhdElement.appendChild(storeInt("SWDI_CodingTimeInMilliseconds", cbhd->_mSWDI_CodingTimeInMilliseconds));
            cbhdElement.appendChild(storeBoolean("SWDI_FeedbackDifferent", cbhd->_mSWDI_FeedbackDifferent));
            cbhdElement.appendChild(storeInt("SWDI_GUITurnoutType", cbhd->_mSWDI_GUITurnoutType.getInt()));
            cbhdElement.appendChild(storeBoolean("SWDI_GUITurnoutLeftHand", cbhd->_mSWDI_GUITurnoutLeftHand));
            cbhdElement.appendChild(storeBoolean("SWDI_GUICrossoverLeftHand", cbhd->_mSWDI_GUICrossoverLeftHand));

            // SWDL section
            cbhdElement.appendChild(storeBoolean("SWDL_Enabled", cbhd->_mSWDL_Enabled));
            cbhdElement.appendChild(storeSensor("SWDL_InternalSensor", cbhd->_mSWDL_InternalSensor));

            // CO section
            cbhdElement.appendChild(storeBoolean("CO_Enabled", cbhd->_mCO_Enabled));
            cbhdElement.appendChild(storeSensor("CO_CallOnToggleInternalSensor", cbhd->_mCO_CallOnToggleInternalSensor));
            cbhdElement.appendChild(storeCallOnList("CO_GroupingsList", cbhd->_mCO_GroupingsList));

            // TRL section
            cbhdElement.appendChild(storeBoolean("TRL_Enabled", cbhd->_mTRL_Enabled));
            cbhdElement.appendChild(storeTRLRules("TRL_LeftRules", cbhd->_mTRL_LeftTrafficLockingRules));
            cbhdElement.appendChild(storeTRLRules("TRL_RightRules", cbhd->_mTRL_RightTrafficLockingRules));

            // TUL section
            cbhdElement.appendChild(storeBoolean("TUL_Enabled", cbhd->_mTUL_Enabled));
            cbhdElement.appendChild(storeSensor("TUL_DispatcherInternalSensorLockToggle", cbhd->_mTUL_DispatcherInternalSensorLockToggle));
            cbhdElement.appendChild(storeTurnout("TUL_ExternalTurnout", cbhd->_mTUL_ExternalTurnout));
            cbhdElement.appendChild(storeBoolean("TUL_ExternalTurnoutFeedbackDifferent", cbhd->_mTUL_ExternalTurnoutFeedbackDifferent));
            cbhdElement.appendChild(storeSensor("TUL_DispatcherInternalSensorUnlockedIndicator", cbhd->_mTUL_DispatcherInternalSensorUnlockedIndicator));
            cbhdElement.appendChild(storeBoolean("TUL_NoDispatcherControlOfSwitch", cbhd->_mTUL_NoDispatcherControlOfSwitch));
            cbhdElement.appendChild(storeBoolean("TUL_ndcos_WhenLockedSwitchStateIsClosed", cbhd->_mTUL_ndcos_WhenLockedSwitchStateIsClosed));
            cbhdElement.appendChild(storeBoolean("TUL_GUI_IconsEnabled", cbhd->_mTUL_GUI_IconsEnabled));
            cbhdElement.appendChild(storeInt("TUL_LockImplementation", cbhd->_mTUL_LockImplementation.getInt()));
            cbhdElement.appendChild(storeTULAdditionalTurnouts("TUL_AdditionalExternalTurnouts", cbhd));

            // IL section
            cbhdElement.appendChild(storeBoolean("IL_Enabled", cbhd->_mIL_Enabled));
            cbhdElement.appendChild(storeSignalList("IL_Signals", cbhd->_mIL_Signals));

            ctcdata.appendChild(cbhdElement);
        }

        return (ctcdata);
    }

    /**
     * Subclass provides implementation to create the correct top element,
     * including the type information. Default implementation is to use the
     * local class here.
     *
     * @param ctcdata The top-level  QDomElement being created
     */
    /*public*/ void CtcManagerXml::setStoreElementClass( QDomElement ctcdata) {
        ctcdata.setAttribute("class", "jmri.jmrit.ctc.configurexml.CtcManagerXml");
    }

     QDomElement CtcManagerXml::storeProperties(CtcManager* cm) {
        ProgramProperties* pp = cm->getProgramProperties();

         QDomElement properties =  doc.createElement("ctcProperties");
        properties.appendChild(storeString("CodeButtonInternalSensorPattern", pp->_mCodeButtonInternalSensorPattern));
        properties.appendChild(storeInt("SIDI_CodingTimeInMilliseconds", pp->_mSIDI_CodingTimeInMilliseconds));
        properties.appendChild(storeString("SIDI_LeftInternalSensorPattern", pp->_mSIDI_LeftInternalSensorPattern));
        properties.appendChild(storeString("SIDI_NormalInternalSensorPattern", pp->_mSIDI_NormalInternalSensorPattern));
        properties.appendChild(storeString("SIDI_RightInternalSensorPattern", pp->_mSIDI_RightInternalSensorPattern));
        properties.appendChild(storeInt("SIDI_TimeLockingTimeInMilliseconds", pp->_mSIDI_TimeLockingTimeInMilliseconds));
        properties.appendChild(storeString("SIDL_LeftInternalSensorPattern", pp->_mSIDL_LeftInternalSensorPattern));
        properties.appendChild(storeString("SIDL_NormalInternalSensorPattern", pp->_mSIDL_NormalInternalSensorPattern));
        properties.appendChild(storeString("SIDL_RightInternalSensorPattern", pp->_mSIDL_RightInternalSensorPattern));
        properties.appendChild(storeInt("SWDI_CodingTimeInMilliseconds", pp->_mSWDI_CodingTimeInMilliseconds));
        properties.appendChild(storeString("SWDI_NormalInternalSensorPattern", pp->_mSWDI_NormalInternalSensorPattern));
        properties.appendChild(storeString("SWDI_ReversedInternalSensorPattern", pp->_mSWDI_ReversedInternalSensorPattern));
        properties.appendChild(storeString("SWDL_InternalSensorPattern", pp->_mSWDL_InternalSensorPattern));
        properties.appendChild(storeString("CO_CallOnToggleInternalSensorPattern", pp->_mCO_CallOnToggleInternalSensorPattern));
        properties.appendChild(storeString("TUL_DispatcherInternalSensorLockTogglePattern", pp->_mTUL_DispatcherInternalSensorLockTogglePattern));
        properties.appendChild(storeString("TUL_DispatcherInternalSensorUnlockedIndicatorPattern", pp->_mTUL_DispatcherInternalSensorUnlockedIndicatorPattern));
        properties.appendChild(storeInt("CodeButtonDelayTime", pp->_mCodeButtonDelayTime));

        return properties;
    }

     QDomElement CtcManagerXml::storeOtherData(CtcManager* cm) {
        OtherData* od = cm->getOtherData();

         QDomElement otherData =  doc.createElement("ctcOtherData");

        otherData.appendChild(storeString("CtcVersion", OtherData::CTC_VERSION));

//  Fleeting:
        otherData.appendChild(storeSensor("FleetingToggleInternalSensor", od->_mFleetingToggleInternalSensor));
        otherData.appendChild(storeBoolean("DefaultFleetingEnabled", od->_mDefaultFleetingEnabled));

//  Global startup:
        otherData.appendChild(storeBoolean("TUL_EnabledAtStartup", od->_mTUL_EnabledAtStartup));
        otherData.appendChild(storeInt("SignalSystemType", od->_mSignalSystemType.getInt()));
        otherData.appendChild(storeInt("TUL_SecondsToLockTurnouts", od->_mTUL_SecondsToLockTurnouts));

//  Next unique # for each created Column:
        otherData.appendChild(storeInt("NextUniqueNumber", od->_mNextUniqueNumber));

//  CTC Debugging:
        otherData.appendChild(storeSensor("CTCDebugSystemReloadInternalSensor", od->_mCTCDebugSystemReloadInternalSensor));
        otherData.appendChild(storeSensor("CTCDebug_TrafficLockingRuleTriggeredDisplayInternalSensor", od->_mCTCDebug_TrafficLockingRuleTriggeredDisplayInternalSensor));

//  GUI design:
        otherData.appendChild(storeInt("GUIDesign_NumberOfEmptyColumnsAtEnd", od->_mGUIDesign_NumberOfEmptyColumnsAtEnd));
        otherData.appendChild(storeInt("GUIDesign_CTCPanelType", od->_mGUIDesign_CTCPanelType.getRadioGroupValue()));
        otherData.appendChild(storeBoolean("GUIDesign_BuilderPlate", od->_mGUIDesign_BuilderPlate));
        otherData.appendChild(storeInt("GUIDesign_SignalsOnPanel", od->_mGUIDesign_SignalsOnPanel.getRadioGroupValue()));
        otherData.appendChild(storeBoolean("GUIDesign_FleetingToggleSwitch", od->_mGUIDesign_FleetingToggleSwitch));
        otherData.appendChild(storeBoolean("GUIDesign_AnalogClockEtc", od->_mGUIDesign_AnalogClockEtc));
        otherData.appendChild(storeBoolean("GUIDesign_ReloadCTCSystemButton", od->_mGUIDesign_ReloadCTCSystemButton));
        otherData.appendChild(storeBoolean("GUIDesign_CTCDebugOnToggle", od->_mGUIDesign_CTCDebugOnToggle));
        otherData.appendChild(storeBoolean("GUIDesign_CreateTrackPieces", od->_mGUIDesign_CreateTrackPieces));
        otherData.appendChild(storeInt("GUIDesign_VerticalSize", od->_mGUIDesign_VerticalSize.getRadioGroupValue()));
        otherData.appendChild(storeBoolean("GUIDesign_OSSectionUnknownInconsistentRedBlink", od->_mGUIDesign_OSSectionUnknownInconsistentRedBlink));
        otherData.appendChild(storeBoolean("GUIDesign_TurnoutsOnPanel", od->_mGUIDesign_TurnoutsOnPanel));

        return otherData;
    }

    // **** Create elements for simple objects ****

     QDomElement CtcManagerXml::storeString(QString elementName, QString elementValue) {
        QDomElement  element =  doc.createElement(elementName);
        //element.setText(elementValue);
        element.appendChild(doc.createTextNode(elementValue));
        return element;
    }

     QDomElement CtcManagerXml::storeInt(QString elementName, int elementValue) {
        QDomElement  element =  doc.createElement(elementName);
        //element.setText(QString::number(elementValue));
        element.appendChild(doc.createTextNode(QString::number(elementValue)));
        return element;
    }

     QDomElement CtcManagerXml::storeBoolean(QString elementName, bool elementValue) {
         QDomElement element =  doc.createElement(elementName);
        //element.setText(elementValue == true ? "true" : "false");
        element.appendChild(doc.createTextNode(elementValue == true ? "true" : "false"));
        return element;
    }

     QDomElement CtcManagerXml::storeSensor(QString elementName, NBHSensor* sensor) {
         QDomElement element =  doc.createElement(elementName);
        if (sensor != nullptr) {
            //element.setText(sensor.getHandleName());
         element.appendChild(doc.createTextNode(sensor->getHandleName()));
        }
        return element;
    }

     QDomElement CtcManagerXml::storeSignal(QString elementName, NBHSignal* signal) {
         QDomElement element =  doc.createElement(elementName);
        if (signal != nullptr) {
           //element.setText(signal.getHandleName());
         element.appendChild(doc.createTextNode(signal->getHandleName()));
        }
        return element;
    }

     QDomElement CtcManagerXml::storeTurnout(QString elementName, NBHTurnout* turnout) {
         QDomElement element =  doc.createElement(elementName);
        if (turnout != nullptr) {
            //element.setText(turnout.getHandleName());
         element.appendChild(doc.createTextNode(turnout->getHandleName()));
        }
        return element;
    }

     QDomElement CtcManagerXml::storeBlock(QString elementName, NamedBeanHandle<Block*>* block) {
         QDomElement element =  doc.createElement(elementName);
        if (block != nullptr) {
            //element.setText(block.getName());
         element.appendChild(doc.createTextNode(block->getName()));
        }
        return element;
    }

    // **** Create elements for ArrayList objects ****

     QDomElement CtcManagerXml::storeSensorList(QString elementName, QList<NBHSensor*>* sensors) {
         QDomElement element =  doc.createElement(elementName);
        //sensors.forEach(sensor ->
         foreach(NBHSensor* sensor, *sensors)
         {
            //element.appendChild(storeSensor("sensor", sensor));
          element.appendChild(storeSensor("sensor", sensor));
        }//);
        return element;
    }

     QDomElement CtcManagerXml::storeSignalList(QString elementName, QList<NBHSignal*>* _signals) {
         QDomElement element =  doc.createElement(elementName);
        //signals.forEach(signal ->
        foreach(NBHSignal* signal, *_signals)
        {
            //element.appendChild(storeSignal("signal", signal));
         element.appendChild(storeSignal("signal", signal));
        }//);
        return element;
    }

     QDomElement CtcManagerXml::storeCallOnList(QString elementName, QList<CallOnData*>* callOnList) {
         QDomElement element =  doc.createElement(elementName);
        //callOnList.forEach(row ->
         foreach(CallOnData* row, *callOnList)
        {
            QDomElement groupEntry =  doc.createElement("CO_GroupEntry");
            groupEntry.appendChild(storeSignal("ExternalSignal", row->_mExternalSignal));
            groupEntry.appendChild(storeString("SignalFacingDirection", row->_mSignalFacingDirection));
            groupEntry.appendChild(storeString("SignalAspectToDisplay", row->_mSignalAspectToDisplay));
            groupEntry.appendChild(storeSensor("CalledOnExternalSensor", row->_mCalledOnExternalSensor));
            groupEntry.appendChild(storeBlock("ExternalBlock", row->_mExternalBlock));
            groupEntry.appendChild(storeSensorList("SwitchIndicators", row->_mSwitchIndicators));
            element.appendChild(groupEntry);
        }//);
        return element;
    }

     QDomElement CtcManagerXml::storeTRLRules(QString elementName, QList<TrafficLockingData*>* trlList) {
         QDomElement element =  doc.createElement(elementName);
        //trlList.forEach(row ->
         foreach(TrafficLockingData* row, *trlList)
        {
             QDomElement ruleEntry =  doc.createElement("TRL_TrafficLockingRule");
            ruleEntry.appendChild(storeString("UserRuleNumber", row->_mUserRuleNumber));
            ruleEntry.appendChild(storeString("RuleEnabled", row->_mRuleEnabled));
            ruleEntry.appendChild(storeString("DestinationSignalOrComment", row->_mDestinationSignalOrComment));

            ruleEntry.appendChild(storeTRLSwitches("switches", row->_mSwitchAlignments));

            ruleEntry.appendChild(storeSensorList("OccupancyExternalSensors", row->_mOccupancyExternalSensors));
            ruleEntry.appendChild(storeSensorList("OptionalExternalSensors", row->_mOptionalExternalSensors));
            element.appendChild(ruleEntry);
        }//);
        return element;
    }

     QDomElement CtcManagerXml::storeTRLSwitches(QString elementName, QList<TrafficLockingData::TRLSwitch*>* trlSwitches) {
         QDomElement element =  doc.createElement(elementName);
        //trlSwitches.forEach(trlSwitch ->
        foreach(TrafficLockingData::TRLSwitch* trlSwitch, *trlSwitches)
        {
             QDomElement elSwitch =  doc.createElement("switch");
            elSwitch.appendChild(storeString("UserText", trlSwitch->_mUserText));
            elSwitch.appendChild(storeString("SwitchAlignment", trlSwitch->_mSwitchAlignment));
            elSwitch.appendChild(storeInt("UniqueID", trlSwitch->_mUniqueID));
            element.appendChild(elSwitch);
        }//);
        return element;
    }

     QDomElement CtcManagerXml::storeTULAdditionalTurnouts(QString elementName, CodeButtonHandlerData* cbhd) {
         QDomElement element =  doc.createElement(elementName);

         QDomElement elementRow = createAdditionalTurnoutEntry(cbhd->_mTUL_AdditionalExternalTurnout1, cbhd->_mTUL_AdditionalExternalTurnout1FeedbackDifferent);
        if (!elementRow.isNull()) element.appendChild(elementRow);
        elementRow = createAdditionalTurnoutEntry(cbhd->_mTUL_AdditionalExternalTurnout2, cbhd->_mTUL_AdditionalExternalTurnout2FeedbackDifferent);
        if (!elementRow.isNull()) element.appendChild(elementRow);
        elementRow = createAdditionalTurnoutEntry(cbhd->_mTUL_AdditionalExternalTurnout3, cbhd->_mTUL_AdditionalExternalTurnout3FeedbackDifferent);
        if (!elementRow.isNull()) element.appendChild(elementRow);

        return element;
    }

     QDomElement CtcManagerXml::createAdditionalTurnoutEntry(NBHTurnout* turnout, bool turnoutFeedback) {
         QDomElement element;;
        if (turnout->valid()) {
            element =  doc.createElement("TUL_AdditionalExternalTurnoutEntry");
            element.appendChild(storeTurnout("TUL_AdditionalExternalTurnout", turnout));
            element.appendChild(storeBoolean("TUL_AdditionalExternalTurnoutFeedbackDifferent", turnoutFeedback));
        }
        return element;
    }

    //@Override
    /*public*/ void CtcManagerXml::load( QDomElement element, QObject* o) throw (JmriConfigureXmlException) {
        log->error("Invalid method called");
    }

    /**
     * Implementation for loading the contents of the CTC configuration.
     *
     * @param sharedCtcData  QDomElement to loaded.
     * @param perNodeCtcData  QDomElement to loaded (same as sharedCtcData).
     * @return true for successful load.
     */
    //@Override
    /*public*/ bool CtcManagerXml::load( QDomElement sharedCtcData,  QDomElement perNodeCtcData) {
        QDomNodeList ctcList = sharedCtcData.childNodes();

        //for ( QDomElement lvl1 : ctcList)
        for(int i=0; i < ctcList.count(); i++)
        {
         QDomElement lvl1 = ctcList.at(i).toElement();
            if (lvl1.tagName() == ("ctcProperties")) {
                loadProperties(cm, lvl1);
                continue;
            }
            if (lvl1.tagName() == ("ctcOtherData")) {
                loadOtherData(cm, lvl1);
                continue;
            }
            if (lvl1.tagName() == ("ctcCodeButtonData")) {
                // Create basic CodeButtonHandlerData
    log->debug("------------- CBHD ------------");
                int _mUniqueID = loadInt(lvl1.firstChildElement("UniqueID"));
                int _mSwitchNumber = loadInt(lvl1.firstChildElement("SwitchNumber"));
                int _mSignalEtcNumber = loadInt(lvl1.firstChildElement("SignalEtcNumber"));
                int _mGUIColumnNumber = loadInt(lvl1.firstChildElement("GUIColumnNumber"));

                // Create a new CodeButtonHandlerData via CodeButtonHandlerDataRoutines which sets default values and empty NBH... objects
                CodeButtonHandlerData* cbhd = CodeButtonHandlerDataRoutines::createNewCodeButtonHandlerData(
                        _mUniqueID, _mSwitchNumber, _mSignalEtcNumber, _mGUIColumnNumber, cm->getProgramProperties());
                cm->getCTCSerialData()->addCodeButtonHandlerData(cbhd);

    log->debug("------------- Code ------------");

                // Code section
                cbhd->_mCodeButtonInternalSensor = loadSensor(lvl1.firstChildElement("CodeButtonInternalSensor"), true);
                cbhd->_mOSSectionOccupiedExternalSensor = loadSensor(lvl1.firstChildElement("OSSectionOccupiedExternalSensor"), false);
                cbhd->_mOSSectionOccupiedExternalSensor2 = loadSensor(lvl1.firstChildElement("OSSectionOccupiedExternalSensor2"), false);
                cbhd->_mOSSectionSwitchSlavedToUniqueID = loadInt(lvl1.firstChildElement("OSSectionSwitchSlavedToUniqueID"));
                cbhd->_mGUIGeneratedAtLeastOnceAlready = loadBoolean(lvl1.firstChildElement("GUIGeneratedAtLeastOnceAlready"));
                cbhd->_mCodeButtonDelayTime = loadInt(lvl1.firstChildElement("CodeButtonDelayTime"));
    log->debug("------------- SIDI ------------");

                // SIDI section
                cbhd->_mSIDI_Enabled = loadBoolean(lvl1.firstChildElement("SIDI_Enabled"));
                cbhd->_mSIDI_LeftInternalSensor = loadSensor(lvl1.firstChildElement("SIDI_LeftInternalSensor"), true);
                cbhd->_mSIDI_NormalInternalSensor = loadSensor(lvl1.firstChildElement("SIDI_NormalInternalSensor"), true);
                cbhd->_mSIDI_RightInternalSensor = loadSensor(lvl1.firstChildElement("SIDI_RightInternalSensor"), true);
                cbhd->_mSIDI_CodingTimeInMilliseconds = loadInt(lvl1.firstChildElement("SIDI_CodingTimeInMilliseconds"));
                cbhd->_mSIDI_TimeLockingTimeInMilliseconds = loadInt(lvl1.firstChildElement("SIDI_TimeLockingTimeInMilliseconds"));
                QMetaEnum metaEnum = QMetaEnum::fromType<CodeButtonHandlerData::TRAFFIC_DIRECTION>();
                //cbhd->_mSIDI_TrafficDirection = CodeButtonHandlerData::TRAFFIC_DIRECTION.valueOf(loadString(lvl1.firstChildElement("SIDI_TrafficDirection")));
//                cbhd->_mSIDI_TrafficDirection =metaEnum.keyToValue(loadString(lvl1.firstChildElement("SIDI_TrafficDirection")));
                cbhd->_mSIDI_LeftRightTrafficSignals = getSignalList(lvl1.firstChildElement("SIDI_LeftRightTrafficSignals"));
                cbhd->_mSIDI_RightLeftTrafficSignals = getSignalList(lvl1.firstChildElement("SIDI_RightLeftTrafficSignals"));

     log-> debug("------------- SIDL ------------");
                // SIDL section
                cbhd->_mSIDL_Enabled = loadBoolean(lvl1.firstChildElement("SIDL_Enabled"));
                cbhd->_mSIDL_LeftInternalSensor = loadSensor(lvl1.firstChildElement("SIDL_LeftInternalSensor"), true);
                cbhd->_mSIDL_NormalInternalSensor = loadSensor(lvl1.firstChildElement("SIDL_NormalInternalSensor"), true);
                cbhd->_mSIDL_RightInternalSensor = loadSensor(lvl1.firstChildElement("SIDL_RightInternalSensor"), true);

     log-> debug("------------- SWDI ------------");
                // SWDI section
                cbhd->_mSWDI_Enabled = loadBoolean(lvl1.firstChildElement("SWDI_Enabled"));
                cbhd->_mSWDI_NormalInternalSensor = loadSensor(lvl1.firstChildElement("SWDI_NormalInternalSensor"), true);
                cbhd->_mSWDI_ReversedInternalSensor = loadSensor(lvl1.firstChildElement("SWDI_ReversedInternalSensor"), true);
                cbhd->_mSWDI_ExternalTurnout = loadTurnout(lvl1.firstChildElement("SWDI_ExternalTurnout"), lvl1.firstChildElement("SWDI_FeedbackDifferent"));
                cbhd->_mSWDI_CodingTimeInMilliseconds = loadInt(lvl1.firstChildElement("SWDI_CodingTimeInMilliseconds"));
                cbhd->_mSWDI_FeedbackDifferent = loadBoolean(lvl1.firstChildElement("SWDI_FeedbackDifferent"));
                cbhd->_mSWDI_GUITurnoutType = CodeButtonHandlerData::TURNOUT_TYPE::getTurnoutType(loadInt(lvl1.firstChildElement("SWDI_GUITurnoutType")));
                cbhd->_mSWDI_GUITurnoutLeftHand = loadBoolean(lvl1.firstChildElement("SWDI_GUITurnoutLeftHand"));
                cbhd->_mSWDI_GUICrossoverLeftHand = loadBoolean(lvl1.firstChildElement("SWDI_GUICrossoverLeftHand"));

     log-> debug("------------- SWDL ------------");
                // SWDL section
                cbhd->_mSWDL_Enabled = loadBoolean(lvl1.firstChildElement("SWDL_Enabled"));
                cbhd->_mSWDL_InternalSensor = loadSensor(lvl1.firstChildElement("SWDL_InternalSensor"), true);

     log-> debug("-------------  CO  ------------");
                // CO section
                cbhd->_mCO_Enabled = loadBoolean(lvl1.firstChildElement("CO_Enabled"));
                cbhd->_mCO_CallOnToggleInternalSensor = loadSensor(lvl1.firstChildElement("CO_CallOnToggleInternalSensor"), true);
                cbhd->_mCO_GroupingsList = getCallOnList(lvl1.firstChildElement("CO_GroupingsList"));

     log-> debug("------------- TRL  ------------");
                // TRL section
                cbhd->_mTRL_Enabled = loadBoolean(lvl1.firstChildElement("TRL_Enabled"));
                cbhd->_mTRL_LeftTrafficLockingRules = getTrafficLocking(lvl1.firstChildElement("TRL_LeftRules"));
                cbhd->_mTRL_RightTrafficLockingRules = getTrafficLocking(lvl1.firstChildElement("TRL_RightRules"));

     log-> debug("------------- TUL  ------------");
                // TUL section
                cbhd->_mTUL_Enabled = loadBoolean(lvl1.firstChildElement("TUL_Enabled"));
                cbhd->_mTUL_DispatcherInternalSensorLockToggle = loadSensor(lvl1.firstChildElement("TUL_DispatcherInternalSensorLockToggle"), true);
                cbhd->_mTUL_ExternalTurnout = loadTurnout(lvl1.firstChildElement("TUL_ExternalTurnout"), lvl1.firstChildElement("TUL_ExternalTurnoutFeedbackDifferent"));
                cbhd->_mTUL_ExternalTurnoutFeedbackDifferent = loadBoolean(lvl1.firstChildElement("TUL_ExternalTurnoutFeedbackDifferent"));
                cbhd->_mTUL_DispatcherInternalSensorUnlockedIndicator = loadSensor(lvl1.firstChildElement("TUL_DispatcherInternalSensorUnlockedIndicator"), true);
                cbhd->_mTUL_NoDispatcherControlOfSwitch = loadBoolean(lvl1.firstChildElement("TUL_NoDispatcherControlOfSwitch"));
                cbhd->_mTUL_ndcos_WhenLockedSwitchStateIsClosed = loadBoolean(lvl1.firstChildElement("TUL_ndcos_WhenLockedSwitchStateIsClosed"));
                cbhd->_mTUL_GUI_IconsEnabled = loadBoolean(lvl1.firstChildElement("TUL_GUI_IconsEnabled"));
                cbhd->_mTUL_LockImplementation = CodeButtonHandlerData::LOCK_IMPLEMENTATION::getLockImplementation(loadInt(lvl1.firstChildElement("TUL_LockImplementation")));
                loadAdditionalTurnouts(lvl1.firstChildElement("TUL_AdditionalExternalTurnouts"), cbhd);

    log->debug("-------------  IL  ------------");
                // IL section
                cbhd->_mIL_Enabled = loadBoolean(lvl1.firstChildElement("IL_Enabled"));
                cbhd->_mIL_Signals = getSignalList(lvl1.firstChildElement("IL_Signals"));

// Debugging aid -- not active due to SpotBugs
//                  log-> info("CodeButtonHandlerData, {}/{}:", _mSwitchNumber, _mSignalEtcNumber);
//                 List<Field> fields = Arrays.asList(CodeButtonHandlerData.class.getFields());
//                 fields.forEach(field -> {
//                     try {
//                          log-> info("    CBHD: fld = {}, type = {}, val = {}", field.getName(), field.getType(), field.get(cbhd));
//                     } catch (Exception ex) {
//                          log-> info("    CBHD list exception: {}", ex.getMessage());
//                     }
//                 });
            }
        }
        convertCallOnSensorNamesToNBHSensors(cm);
        return true;
    }

    /**
     * Load the ProgramProperties class.
     * @param cm The CTC manager.
     * @param el The "ctcProperties" element.
     */
    void CtcManagerXml::loadProperties(CtcManager* cm, QDomElement el) {
        ProgramProperties* pp = cm->getProgramProperties();

        pp->_mCodeButtonInternalSensorPattern = loadString(el.firstChildElement("CodeButtonInternalSensorPattern"));
        pp->_mSIDI_CodingTimeInMilliseconds = loadInt(el.firstChildElement("SIDI_CodingTimeInMilliseconds"));
        pp->_mSIDI_LeftInternalSensorPattern = loadString(el.firstChildElement("SIDI_LeftInternalSensorPattern"));
        pp->_mSIDI_NormalInternalSensorPattern = loadString(el.firstChildElement("SIDI_NormalInternalSensorPattern"));
        pp->_mSIDI_RightInternalSensorPattern = loadString(el.firstChildElement("SIDI_RightInternalSensorPattern"));
        pp->_mSIDI_TimeLockingTimeInMilliseconds = loadInt(el.firstChildElement("SIDI_TimeLockingTimeInMilliseconds"));
        pp->_mSIDL_LeftInternalSensorPattern = loadString(el.firstChildElement("SIDL_LeftInternalSensorPattern"));
        pp->_mSIDL_NormalInternalSensorPattern = loadString(el.firstChildElement("SIDL_NormalInternalSensorPattern"));
        pp->_mSIDL_RightInternalSensorPattern = loadString(el.firstChildElement("SIDL_RightInternalSensorPattern"));
        pp->_mSWDI_CodingTimeInMilliseconds = loadInt(el.firstChildElement("SWDI_CodingTimeInMilliseconds"));
        pp->_mSWDI_NormalInternalSensorPattern = loadString(el.firstChildElement("SWDI_NormalInternalSensorPattern"));
        pp->_mSWDI_ReversedInternalSensorPattern = loadString(el.firstChildElement("SWDI_ReversedInternalSensorPattern"));
        pp->_mSWDL_InternalSensorPattern = loadString(el.firstChildElement("SWDL_InternalSensorPattern"));
        pp->_mCO_CallOnToggleInternalSensorPattern = loadString(el.firstChildElement("CO_CallOnToggleInternalSensorPattern"));
        pp->_mTUL_DispatcherInternalSensorLockTogglePattern = loadString(el.firstChildElement("TUL_DispatcherInternalSensorLockTogglePattern"));
        pp->_mTUL_DispatcherInternalSensorUnlockedIndicatorPattern = loadString(el.firstChildElement("TUL_DispatcherInternalSensorUnlockedIndicatorPattern"));
        pp->_mCodeButtonDelayTime = loadInt(el.firstChildElement("CodeButtonDelayTime"));

// Debugging aid -- not active due to SpotBugs
//              log-> debug("ProgramProperties:");
//             List<Field> fields = Arrays.asList(ProgramProperties.class.getFields());
//             fields.forEach(field -> {
//                 try {
//                      log-> info("    ProgramProperties: fld = {}, val = {}", field.getName(), field.get(pp));
//                 } catch (Exception ex) {
//                      log-> info("    ProgramProperties list exception: {}", ex.getMessage());
//                 }
//             });
    }

    /**
     * Load the OtherData class.
     * @param cm The CTC manager.
     * @param el The "ctcOtherData" element.
     */
    void CtcManagerXml::loadOtherData(CtcManager* cm,  QDomElement el) {
        OtherData* od = cm->getOtherData();

        QString xmlVersion = loadString(el.firstChildElement("CtcVersion"));
        xmlVersion = xmlVersion == "" ? "v2.0" : xmlVersion;   // v2.0 is the initial version
        if (xmlVersion != (OtherData::CTC_VERSION)) {
             log-> warn(tr("Update from version %1 to version %2 required").arg(xmlVersion).arg(OtherData::CTC_VERSION));
        }

//  Fleeting:
        od->_mFleetingToggleInternalSensor = loadSensor(el.firstChildElement("FleetingToggleInternalSensor"), true);
        od->_mDefaultFleetingEnabled = loadBoolean(el.firstChildElement("DefaultFleetingEnabled"));

//  Global startup:
        od->_mTUL_EnabledAtStartup = loadBoolean(el.firstChildElement("TUL_EnabledAtStartup"));
        od->_mSignalSystemType = OtherData::SIGNAL_SYSTEM_TYPE::getSignalSystemType(loadInt(el.firstChildElement("SignalSystemType")));
        od->_mTUL_SecondsToLockTurnouts = loadInt(el.firstChildElement("TUL_SecondsToLockTurnouts"));

//  Next unique # for each created Column:
        od->_mNextUniqueNumber = loadInt(el.firstChildElement("NextUniqueNumber"));

//  CTC Debugging:
        od->_mCTCDebugSystemReloadInternalSensor = loadSensor(el.firstChildElement("CTCDebugSystemReloadInternalSensor"), true);
        od->_mCTCDebug_TrafficLockingRuleTriggeredDisplayInternalSensor = loadSensor(el.firstChildElement("CTCDebug_TrafficLockingRuleTriggeredDisplayInternalSensor"), true);

//  GUI design:
        od->_mGUIDesign_NumberOfEmptyColumnsAtEnd = loadInt(el.firstChildElement("GUIDesign_NumberOfEmptyColumnsAtEnd"));
        od->_mGUIDesign_CTCPanelType = OtherData::CTC_PANEL_TYPE::getRadioGroupValue(loadInt(el.firstChildElement("GUIDesign_CTCPanelType")));
        od->_mGUIDesign_BuilderPlate = loadBoolean(el.firstChildElement("GUIDesign_BuilderPlate"));
        od->_mGUIDesign_SignalsOnPanel = OtherData::SIGNALS_ON_PANEL::getRadioGroupValue(loadInt(el.firstChildElement("GUIDesign_SignalsOnPanel")));
        od->_mGUIDesign_FleetingToggleSwitch = loadBoolean(el.firstChildElement("GUIDesign_FleetingToggleSwitch"));
        od->_mGUIDesign_AnalogClockEtc = loadBoolean(el.firstChildElement("GUIDesign_AnalogClockEtc"));
        od->_mGUIDesign_ReloadCTCSystemButton = loadBoolean(el.firstChildElement("GUIDesign_ReloadCTCSystemButton"));
        od->_mGUIDesign_CTCDebugOnToggle = loadBoolean(el.firstChildElement("GUIDesign_CTCDebugOnToggle"));
        od->_mGUIDesign_CreateTrackPieces = loadBoolean(el.firstChildElement("GUIDesign_CreateTrackPieces"));
        od->_mGUIDesign_VerticalSize = OtherData::VERTICAL_SIZE::getRadioGroupValue(loadInt(el.firstChildElement("GUIDesign_VerticalSize")));
        od->_mGUIDesign_OSSectionUnknownInconsistentRedBlink = loadBoolean(el.firstChildElement("GUIDesign_OSSectionUnknownInconsistentRedBlink"));
        od->_mGUIDesign_TurnoutsOnPanel = loadBoolean(el.firstChildElement("GUIDesign_TurnoutsOnPanel"));

// Debugging aid -- not active due to SpotBugs
//          log-> info("OtherData:");
//         List<Field> fields = Arrays.asList(OtherData.class.getFields());
//         fields.forEach(field -> {
//             try {
//                  log-> info("    OtherData: fld = {}, type = {}, val = {}", field.getName(), field.getType(), field.get(od));
//             } catch (Exception ex) {
//                  log-> info("    OtherData list exception: {}", ex.getMessage());
//             }
//         });
    }

    // **** Load simple objects ****

    QString CtcManagerXml::loadString( QDomElement element) {
        QString newString = QString();
        if ( !element.isNull()) {
            newString = element.text();
        }
        return newString;
    }

    int CtcManagerXml::loadInt( QDomElement element) {
        int newInt = 0;
        if ( !element.isNull()) {
            bool ok;
                newInt = element.text().toInt(&ok);
            if(!ok) {
                 log-> warn(tr("loadInt format exception:  QDomElement = %1, value = %2").arg(element.tagName()).arg(element.text()));
            }
        }
        return newInt;
    }

    bool CtcManagerXml::loadBoolean( QDomElement element) {
        bool newBoolean = false;
        if ( !element.isNull()) {
            newBoolean = element.text() == ("true") ? true : false;
        }
        return newBoolean;
    }

    NBHSensor* CtcManagerXml::loadSensor( QDomElement element, bool isInternal) {
        NBHSensor* sensor = nullptr;
        if ( !element.isNull() && element.text() != "" && !element.text().isEmpty()) {
            QString sensorName = element.text();
            sensor = cm->getNBHSensor(sensorName);
            if (sensor == nullptr) {
                if (isInternal) {
                    sensor = new NBHSensor("CtcManagerXml", "create internal = ", sensorName, sensorName);
                } else {
                    sensor = new NBHSensor("CtcManagerXml", "create standard = ", sensorName, sensorName, false);
                }
            }
        } else {
            sensor = new NBHSensor("CtcManagerXml", "", "Empty NBHSensor", "", true);
        }
        return sensor;
    }

    NBHSignal* CtcManagerXml::loadSignal( QDomElement element) {
        NBHSignal* signal = nullptr;
        if ( !element.isNull() && element.text() != "" && !element.text().isEmpty()) {
            QString signalName  = element.text();
            signal = cm->getNBHSignal(signalName);
            if (signal == nullptr) {
                signal = new NBHSignal(element.text());
            }
        } else {
            signal = new NBHSignal("");
        }
        return signal;
    }

    NBHTurnout* CtcManagerXml::loadTurnout( QDomElement element,  QDomElement feedback) {
        NBHTurnout* turnout = nullptr;
        bool feedBack = loadBoolean(feedback);
        if ( !element.isNull() && element.text() != "" && !element.text().isEmpty()) {
            QString turnoutName = element.text();

            turnout = cm->getNBHTurnout(turnoutName);
            if (turnout == nullptr) {
                turnout = new NBHTurnout("CtcManagerXml", "", element.text(), element.text(), feedBack);
            }
        } else {
            turnout = new NBHTurnout("CtcManagerXml", "Empty NBHTurnout", "");
        }
        return turnout;
    }

    NamedBeanHandle<Block*>* CtcManagerXml::loadBlock( QDomElement element) {
        NamedBeanHandle<Block*>* blockHandle = nullptr;
        if ( !element.isNull() && element.text() != "" && !element.text().isEmpty()) {
            blockHandle = cm->getBlock(element.text());
            if (blockHandle == nullptr) {
                Block* block = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBlock(element.text());
                if (block != nullptr) {
                    blockHandle = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(element.text(), block);
                    cm->putBlock(element.text(), blockHandle);
                }
            }
        }
        return blockHandle;
    }

    // **** Load ArrayList objects ****

    QList<NBHSensor*>* CtcManagerXml::getSensorList( QDomElement element) {
        QList<NBHSensor*>* sensorList = new QList<NBHSensor*>();
        if ( !element.isNull()) {
            //for ( QDomElement el : element.firstChildElement()) {
            QDomNodeList nl = element.childNodes();
            for(int i=0; i < nl.count(); i++)
            {
             QDomElement el = nl.at(i).toElement();
                NBHSensor* sensor = loadSensor(el, false);
                sensorList->append(sensor);
            }
        }
        return sensorList;
    }

    QList<NBHSignal*>* CtcManagerXml::getSignalList( QDomElement element) {
        QList<NBHSignal*>* signalList = new QList<NBHSignal*>();
        if ( !element.isNull()) {
            QDomNodeList nl = element.childNodes();
            //for ( QDomElement el : element.firstChildElement())
            for(int i=0; i < nl.count(); i++)
            {
             QDomElement el = nl.at(i).toElement();
                NBHSignal* signal = loadSignal(el);
                signalList->append(signal);
            }
        }
        return signalList;
    }

    QList<CallOnData*>* CtcManagerXml::getCallOnList( QDomElement element) {
        QList<CallOnData*>* callOnList = new QList<CallOnData*>();
        if ( !element.isNull()) {
//            for ( QDomElement elCallOn : element.firstChildElement())
//            {
               QDomNodeList nl = element.childNodes();
               //for ( QDomElement el : element.firstChildElement())
               for(int i=0; i < nl.count(); i++)
               {
                QDomElement elCallOn = nl.at(i).toElement();
                CallOnData* cod = new CallOnData();
                cod->_mExternalSignal = loadSignal(elCallOn.firstChildElement("ExternalSignal"));
                cod->_mSignalFacingDirection = loadString(elCallOn.firstChildElement("SignalFacingDirection"));
                cod->_mSignalAspectToDisplay = loadString(elCallOn.firstChildElement("SignalAspectToDisplay"));
                cod->_mCalledOnExternalSensor = loadSensor(elCallOn.firstChildElement("CalledOnExternalSensor"), false);
                cod->_mExternalBlock = loadBlock(elCallOn.firstChildElement("ExternalBlock"));
                cod->_mSwitchIndicators = new QList<NBHSensor*>();
                cod->_mSwitchIndicatorNames = getCallOnSensorNames(elCallOn.firstChildElement("SwitchIndicators"));
                callOnList->append(cod);
            }
        }
        return callOnList;
    }

   QList<QString> CtcManagerXml::getCallOnSensorNames( QDomElement element) {
        QList<QString> sensorList = QList<QString>();
        if ( !element.isNull()) {
            //for ( QDomElement el : element.firstChildElement()) {
            QDomNodeList nl = element.childNodes();
            //for ( QDomElement el : element.firstChildElement())
            for(int i=0; i < nl.count(); i++)
            {
             QDomElement el = nl.at(i).toElement();
                sensorList.append(el.text());
            }
        }
        return sensorList;
    }

    void CtcManagerXml::convertCallOnSensorNamesToNBHSensors(CtcManager* cm) {
        for (CodeButtonHandlerData* cbhd : cm->getCTCSerialData()->getCodeButtonHandlerDataArrayList()) {
            for (CallOnData* cod : *cbhd->_mCO_GroupingsList) {
                for (QString sensorName : cod->_mSwitchIndicatorNames) {
                    NBHSensor* sensor = cm->getNBHSensor(sensorName);
                    if (sensor != nullptr) {
                        cod->_mSwitchIndicators->append(sensor);
                    }
                }
            }
        }
    }

    QList<TrafficLockingData*>* CtcManagerXml::getTrafficLocking( QDomElement element) {
        QList<TrafficLockingData*>* trlData = new QList<TrafficLockingData*>();
        if ( !element.isNull()) {
//            for ( QDomElement elRule : element.getChildren())
            QDomNodeList list = element.childNodes();
            for(int i=0; i<list.count(); i++ )
            {
             QDomElement elRule = list.at(i).toElement();
                TrafficLockingData* trl = new TrafficLockingData();
                trl->_mUserRuleNumber = loadString(elRule.firstChildElement("UserRuleNumber"));
                trl->_mRuleEnabled = loadString(elRule.firstChildElement("RuleEnabled"));
                trl->_mDestinationSignalOrComment = loadString(elRule.firstChildElement("DestinationSignalOrComment"));

                trl->_mSwitchAlignments = getTRLSwitchList(elRule.firstChildElement("switches"));

                trl->_mOccupancyExternalSensors = getSensorList(elRule.firstChildElement("OccupancyExternalSensors"));
                trl->_mOptionalExternalSensors = getSensorList(elRule.firstChildElement("OptionalExternalSensors"));
                trlData->append(trl);
            }
        }
        return trlData;
    }

    QList<TrafficLockingData::TRLSwitch*>* CtcManagerXml::getTRLSwitchList( QDomElement element) {
        QList<TrafficLockingData::TRLSwitch*>* trlSwitches = new QList<TrafficLockingData::TRLSwitch*>();
        if ( !element.isNull()) {
            //for ( QDomElement elSwitch : element.firstChildElement()) {
               QDomNodeList nl = element.childNodes();
               for(int i=0; i < nl.count(); i++)
               {
                QDomElement elSwitch = nl.at(i).toElement();
                QString userText = loadString(elSwitch.firstChildElement("UserText"));
                if (userText != "" && !userText.isEmpty()) {
                    TrafficLockingData::TRLSwitch* newSwitch = new TrafficLockingData::TRLSwitch(
                            userText,
                            loadString(elSwitch.firstChildElement("SwitchAlignment")),
                            loadInt(elSwitch.firstChildElement("UniqueID")));
                    trlSwitches->append(newSwitch);
                }
            }
        }
        return trlSwitches;
    }

    void CtcManagerXml::loadAdditionalTurnouts( QDomElement element, CodeButtonHandlerData* cbhd) {      // TUL_AdditionalExternalTurnouts
        if ( !element.isNull()) {
            int rowNumber = 0;
            //for ( QDomElement elTurnout : element.firstChildElement()) {       // TUL_AdditionalExternalTurnoutEntry
            QDomNodeList nl = element.childNodes();
            //for ( QDomElement el : element.firstChildElement())
            for(int i=0; i < nl.count(); i++)
            {
             QDomElement elTurnout = nl.at(i).toElement();
                rowNumber++;
                NBHTurnout* turnout = loadTurnout(elTurnout.firstChildElement("TUL_AdditionalExternalTurnout"), elTurnout.firstChildElement("TUL_AdditionalExternalTurnoutFeedbackDifferent"));
                bool feedback = loadBoolean(elTurnout.firstChildElement("TUL_AdditionalExternalTurnoutFeedbackDifferent"));

                if (rowNumber == 1) {
                    cbhd->_mTUL_AdditionalExternalTurnout1 = turnout;
                    cbhd->_mTUL_AdditionalExternalTurnout1FeedbackDifferent = feedback;
                }
                if (rowNumber == 2) {
                    cbhd->_mTUL_AdditionalExternalTurnout2 = turnout;
                    cbhd->_mTUL_AdditionalExternalTurnout2FeedbackDifferent = feedback;
                }
                if (rowNumber == 3) {
                    cbhd->_mTUL_AdditionalExternalTurnout3 = turnout;
                    cbhd->_mTUL_AdditionalExternalTurnout3FeedbackDifferent = feedback;
                }
            }
        }
    }

    //@Override
    /*public*/ int CtcManagerXml::loadOrder() {
        return ((CtcManager*)InstanceManager::getDefault("CtcManager"))->getXMLOrder();
    }

    /*private*/ /*final*/ /*static*/ Logger* CtcManagerXml::log = LoggerFactory::getLogger("CtcManagerXml");
