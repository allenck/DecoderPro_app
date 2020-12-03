#include "whereusedcollectors.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "turnoutmanager.h"
#include "light.h"
#include "lightmanager.h"
#include "signalgroupmanager.h"
#include "signalmastlogicmanager.h"
#include "layoutblockmanager.h"
#include "blockbosslogic.h"
#include "oblockmanager.h"
#include "warrantmanager.h"
#include "entryexitpairs.h"
#include "logixmanager.h"
#include "transitmanager.h"
#include "editormanager.h"
#include "defaultsignalmastlogic.h"
#include "oblock.h"
#include "warrant.h"
#include "logix.h"
#include "switchboardeditor.h"
#include "destinationpoints.h"
#include "transit.h"
#include "defaultroute.h"

WhereUsedCollectors::WhereUsedCollectors(QObject *parent) : QObject(parent)
{

}
/**
 * Find references.  Each collector method calls a corresponding getUsageReport(NamedBean)
 * in the main implementation class for the object type.  The matches are returned in an
 * array list of NamedBeanUsageReport objects.
 *
 * Collectors:
 * <ul>
 * <li>checkTurnouts</li>
 * <li>checkLights</li>
 * <li>checkRoutes</li>
 * <li>checkBlocks</li>
 * <li>checkLayoutBlocks</li>
 * <li>checkSignalHeadLogic</li>
 * <li>checkSignalMastLogic</li>
 * <li>checkSignalGroups</li>
 * <li>checkOBlocks</li>
 * <li>checkWarrants</li>
 * <li>checkEntryExit</li>
 * <li>checkLogixConditionals</li>
 * <li>checkSections</li>
 * <li>checkTransits</li>
 * <li>checkPanels</li>
 * <li>checkCTC - TODO</li>
 * </ul>
 *
 * @author Dave Sand Copyright (C) 2020
 */

// /*public*/ class WhereUsedCollectors {

    /**
     * Create the Turnout usage string.
     * Usage keys:
     * <ul>
     * <li>TurnoutFeedback1</li>
     * <li>TurnoutFeedback2</li>
     * </ul>
     * @param bean The requesting bean:  Sensor.
     * @return usage string
     */
    /*static*/ QString WhereUsedCollectors::checkTurnouts(NamedBean* bean) {
        QString sb;// = new StringBuilder();
        //InstanceManager::getDefault(TurnoutManager)->getNamedBeanSet().forEach((turnout) ->
        foreach(NamedBean* nb, ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getNamedBeanSet())
        {
         Turnout* turnout = (Turnout*)nb;
            int feedback = turnout->getFeedbackMode();
            if (feedback == Turnout::ONESENSOR || feedback == Turnout::TWOSENSOR) {
                //turnout.getUsageReport(bean).forEach((report) ->
             foreach(NamedBeanUsageReport* report, turnout->getUsageReport(bean))
             {
                 if (report->usageKey.startsWith("TurnoutFeedback")) {  // NOI18N
                     QString name = turnout->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME);
                     sb.append(tr("\n%1	").arg(name));  // NOI18N
                 }
             }//);
            }
        }//);
        return addHeader(sb, "ReferenceFeedback");  // NOI18N
    }

    /**
     * Create the Light usage string.
     * Usage keys:
     * <ul>
     * <li>LightControlSensor1</li>
     * <li>LightControlSensor2</li>
     * <li>LightControlSensorTimed</li>
     * <li>LightControlTurnout</li>
     * </ul>
     * @param bean The requesting bean:  Sensor, Turnout.
     * @return usage string
     */
    /*static*/ QString WhereUsedCollectors::checkLights(NamedBean* bean) {
        QString sb;// = new StringBuilder();
        //InstanceManager.getDefault(LightManager.class).getNamedBeanSet().forEach((light) -> {
        foreach(NamedBean* nb, ((LightManager*)InstanceManager::getDefault("LightManager"))->getNamedBeanSet())
        {
         Light* light = (Light*)nb;
         //light.getUsageReport(bean).forEach((report) -> {
         foreach(NamedBeanUsageReport* report, light->getUsageReport(bean))
         {
              if (report->usageKey.startsWith("LightControl")) {  // NOI18N
                    QString name = light->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME);
                                         sb.append(tr("\n%1	").arg(name));  // NOI18N
              }
            }//);
        }//);
        return addHeader(sb, "ReferenceLightControl");  // NOI18N
    }

    /**
     * Create the Route usage string.
     * Usage keys:
     * <ul>
     * <li>RouteTurnoutOutput</li>
     * <li>RouteSensorOutput</li>
     * <li>RouteSensorControl</li>
     * <li>RouteSensorAligned</li>
     * <li>RouteTurnoutControl</li>
     * <li>RouteTurnoutLock</li>
     * </ul>
     * @param bean The requesting bean:  Sensor, Turnout.
     * @return usage string
     */
    /*static*/ QString WhereUsedCollectors::checkRoutes(NamedBean* bean) {
        QString sb; // = new StringBuilder();
        //InstanceManager.getDefault(RouteManager.class).getNamedBeanSet().forEach((route) -> {
        foreach(NamedBean* nb, ((RouteManager*)InstanceManager::getDefault("RouteManager"))->getNamedBeanSet())
        {
         Route* route = (Route*)nb;
            //route.getUsageReport(bean).forEach((report) -> {
         foreach(NamedBeanUsageReport* report, ((DefaultRoute*)route)->getUsageReport(bean))
         {
                if (report->usageKey.startsWith("Route")) {  // NOI18N
                    QString name = ((DefaultRoute*)route)->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME);
                    sb.append(tr("\n%1	").arg(name));  // NOI18N
                }
            }//);
        }//);
        return addHeader(sb, "ReferenceRoutes");  // NOI18N
    }

    /**
     * Create the Block usage string.
     * Usage keys:
     * <ul>
     * <li>BlockSensor</li>
     * <li>BlockReporter</li>
     * <li>BlockPathNeighbor</li>
     * <li>BlockPathTurnout</li>
     * </ul>
     * @param bean The requesting bean:  Block (Path neighbor), Sensor, Reporter, Turnout (Path).
     * @return usage string
     */
    /*static*/ QString WhereUsedCollectors::checkBlocks(NamedBean* bean) {
        QString sb; // = new StringBuilder();
        //InstanceManager.getDefault(BlockManager.class).getNamedBeanSet().forEach((block) -> {
        foreach(NamedBean* nb, ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getNamedBeanSet())
        {
         Block* block = (Block*)nb;
            //block.getUsageReport(bean).forEach((report) -> {
         foreach(NamedBeanUsageReport* report, block->getUsageReport(bean))
         {
                if (report->usageKey.startsWith("Block")) {  // NOI18N
                    QString name = block->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME);
                    sb.append(tr("\n%1	").arg(name));  // NOI18N
                }
            }//);
        }//);
        return addHeader(sb, "ReferenceBlock");  // NOI18N
    }

    /**
     * Create the LayoutBlock usage string.
     * Usage keys:
     * <ul>
     * <li>LayoutBlockBlock</li>
     * <li>LayoutBlockMemory</li>
     * <li>LayoutBlockSensor</li>
     * <li>LayoutBlockNeighbor</li>
     * </ul>
     * @param bean The requesting bean:  Block, Memory, Sensor.
     * @return usage string
     */
    /*static*/ QString WhereUsedCollectors::checkLayoutBlocks(NamedBean* bean) {
        QString sb; // = new StringBuilder();
        //InstanceManager.getDefault(LayoutBlockManager.class).getNamedBeanSet().forEach((layoutBlock) -> {
        foreach(NamedBean* nb, ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getNamedBeanSet())
        {
         LayoutBlock* layoutBlock = (LayoutBlock*)nb;
            //layoutBlock.getUsageReport(bean).forEach((report) -> {
         foreach(NamedBeanUsageReport* report, layoutBlock->getUsageReport(bean))
         {
                if (report->usageKey.startsWith("LayoutBlock")) {  // NOI18N
                    QString name = layoutBlock->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME);
                    sb.append(tr("\n%1 %2	").arg(name).arg(report->usageData));  // NOI18N
                }
            }//);
        }//);
        return addHeader(sb, "ReferenceLayoutBlock");  // NOI18N
    }

    /**
     * Create the Signal Head Logic usage string.
     * Usage keys:
     * <ul>
     * <li>SSLSignal</li>
     * <li>SSLSensor1-5</li>
     * <li>SSLTurnout</li>
     * <li>SSLSignal1</li>
     * <li>SSLSignal1Alt</li>
     * <li>SSLSignal2</li>
     * <li>SSLSignal2Alt</li>
     * <li>SSLSensorWatched1</li>
     * <li>SSLSensorWatched1Alt</li>
     * <li>SSLSensorWatched2</li>
     * <li>SSLSensorWatched2Alt</li>
     * <li>SSLSensorApproach</li>
     * </ul>
     * @param bean The requesting bean:  Sensor, Signal Head, Turnout.
     * @return usage string
     */
    /*static*/ QString WhereUsedCollectors::checkSignalHeadLogic(NamedBean* bean) {
        QString sb; // = new StringBuilder();
        QListIterator<BlockBossLogic*> e = BlockBossLogic::entries();
        while (e.hasNext()) {
            BlockBossLogic* ssl = e.next();
            //ssl.getUsageReport(bean).forEach((report) -> {
            foreach(NamedBeanUsageReport* report, ssl->getUsageReport(bean))
            {
                if (report->usageKey.startsWith("SSL")) {  // NOI18N
                    QString name = report->usageBean->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME);
                    sb.append(tr("\n%1	").arg(name));  // NOI18N
                }
            }//);
        }
        return addHeader(sb, "ReferenceHeadSSL");  // NOI18N
    }

    /**
     * Create the Signal Mast Logic usage string.
     * Usage keys:
     * <ul>
     * <li>SMLSourceMast</li>
     * <li>SMLDestinationMast</li>
     * <li>SMLBlockAuto</li>
     * <li>SMLBlockUser</li>
     * <li>SMLTurnoutAuto</li>
     * <li>SMLTurnoutUser</li>
     * <li>SMLSensor</li>
     * <li>SMLMastAuto</li>
     * <li>SMLMastUser</li>
     * </ul>
     * @param bean The requesting bean:  Block, Turnout, Sensor, Signal Mast.
     * @return usage string
     */
    /*static*/ QString WhereUsedCollectors::checkSignalMastLogic(NamedBean* bean) {
        QString sb; // = new StringBuilder();
        //InstanceManager.getDefault(SignalMastLogicManager.class).getNamedBeanSet().forEach((sml) -> {
        foreach(NamedBean* nb, ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->getNamedBeanSet())
        {
         DefaultSignalMastLogic* sml = (DefaultSignalMastLogic*)nb;
         //sml.getUsageReport(bean).forEach((report) -> {
         foreach(NamedBeanUsageReport* report, sml->getUsageReport(bean))
         {
                QString name = bean->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME);
                if (report->usageKey.startsWith("SMLSource")) {  // NOI18N
                    sb.append(tr("\n%1%2	").arg(name).arg(tr("Source")));  // NOI18N
                    //return;
                }
                if (report->usageKey.startsWith("SMLDest")) {  // NOI18N
                    sb.append(tr("\n%1%2	").arg(name).arg(tr("Destination")));  // NOI18N
                    //return;
                }
                if (report->usageKey.startsWith("SML")) {  // NOI18N
                    sb.append(tr("\n%1 -> %2	").arg(sml->getSourceMast()->getDisplayName()).arg(report->usageBean->getDisplayName()));  // NOI18N
                }
            }//);
        }//);
        return addHeader(sb, "ReferenceMastSML");  // NOI18N
    }

    /**
     * Create the Signal Group usage string.
     * Usage keys:
     * <ul>
     * <li>SignalGroupMast</li>
     * <li>SignalGroupHead</li>
     * <li>SignalGroupHeadSensor</li>
     * <li>SignalGroupHeadTurnout</li>
     * </ul>
     * @param bean The requesting bean:  Sensor, Signal Head, Signal Mast, Turnout.
     * @return usage string
     */
    /*static*/ QString WhereUsedCollectors::checkSignalGroups(NamedBean* bean) {
        QString sb; // = new StringBuilder();
        //InstanceManager.getDefault(SignalGroupManager.class).getNamedBeanSet().forEach((group) -> {
        foreach(NamedBean* nb, ((SignalGroupManager*)InstanceManager::getDefault("SignalGroupManager"))->getNamedBeanSet())
        {
         SignalGroup* group = (SignalGroup*)nb;
            //group.getUsageReport(bean).forEach((report) -> {
         foreach(NamedBeanUsageReport* report, group->getUsageReport(bean))
         {
                if (report->usageKey.startsWith("SignalGroup")) {  // NOI18N
                    QString name = group->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME);
                    sb.append(tr("\n%1	").arg(name));  // NOI18N
                }
            }//);
        }//);
        return addHeader(sb, "ReferenceSignalGroup");  // NOI18N
    }

    /**
     * Create the OBlock usage string.
     * Usage keys:
     * <ul>
     * <li>OBlockSensor</li>
     * <li>OBlockSensorError</li>
     * <li>OBlockPortalNeighborOBlock</li>
     * <li>OBlockPortalSignal</li>
     * <li>OBlockPortalPathTurnout</li>
     * <li>OBlockWarrant</li>
     * </ul>
     * @param bean The requesting bean:  OBlock (Neightbor), Sensor, SignalHead, SignalMast, Turnout, Warrant.
     * @return usage string
     */
    /*static*/ QString WhereUsedCollectors::checkOBlocks(NamedBean* bean) {
        QString sb; // = new StringBuilder();
        //InstanceManager.getDefault(OBlockManager.class).getNamedBeanSet().forEach((oblock) -> {
        foreach(NamedBean* nb, ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getNamedBeanSet())
        {
         OBlock* oblock = (OBlock*)nb;
            //oblock.getUsageReport(bean).forEach((report) -> {
         foreach(NamedBeanUsageReport* report, oblock->getUsageReport(bean))
         {
                if (report->usageKey.startsWith("OBlock")) {  // NOI18N
                    QString name = oblock->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME);
                    sb.append(tr("\n%1 %2	").arg(name).arg(report->usageData));  // NOI18N
                }
            }//);
        }//);
        return addHeader(sb, "ReferenceOBlock");  // NOI18N
    }

    /**
     * Create the Warrant usage string.
     * Usage keys:
     * <ul>
     * <li>WarrantBlocking</li>
     * <li>WarrantBlock</li>
     * <li>WarrantSignal</li>
     * </ul>
     * @param bean The requesting bean:  OBlock SignalHead, SignalMast, Warrant.
     * @return usage string
     */
    /*static*/ QString WhereUsedCollectors::checkWarrants(NamedBean* bean) {
        QString sb; // = new StringBuilder();
        //InstanceManager.getDefault(WarrantManager.class).getNamedBeanSet().forEach((warrant) -> {
        foreach(NamedBean* nb, ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getNamedBeanSet())
        {
         Warrant* warrant = (Warrant*)nb;
            //warrant.getUsageReport(bean).forEach((report) -> {
         foreach(NamedBeanUsageReport* report, warrant->getUsageReport(bean))
         {
                if (report->usageKey.startsWith("Warrant")) {  // NOI18N
                    QString name = warrant->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME);
                    sb.append(tr("\n%1	").arg(name));  // NOI18N
                }
            }//);
        }//);
        return addHeader(sb, "ReferenceWarrant");  // NOI18N
    }

    /**
     * Create the Entry/Exit usage string.
     * Usage keys:
     * <ul>
     * <li>EntryExitSourceSensor</li>
     * <li>EntryExitSourceSignal</li>
     * <li>EntryExitDestinationSensor</li>
     * <li>EntryExitDestinationSignal</li>
     * </ul>
     * @param bean The requesting bean:  Sensor SignalHead, SignalMast.
     * @return usage string
     */
    /*static*/ QString WhereUsedCollectors::checkEntryExit(NamedBean* bean) {
        QString sb; // = new StringBuilder();
        //InstanceManager.getDefault(EntryExitPairs.class).getNamedBeanSet().forEach((destPoint) -> {
        foreach(NamedBean* nb, ((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))->getNamedBeanSet())
        {
         DestinationPoints* destPoint = (DestinationPoints*)nb;
            //destPoint.getUsageReport(bean).forEach((report) -> {
         foreach(NamedBeanUsageReport* report, destPoint->getUsageReport(bean))
         {
                if (report->usageKey.startsWith("EntryExit")) {  // NOI18N
                    QString name = destPoint->getDisplayName();
                    sb.append(tr("\n%1	").arg(name));  // NOI18N
                }
            }//);
        }//);
        return addHeader(sb, "ReferenceEntryExit");  // NOI18N
    }

    /**
     * Create the Logix/Conditional usage string.
     * Usage keys:
     * <ul>
     * <li>ConditionalAction</li>
     * <li>ConditionalVariable</li>
     * <li>ConditionalVariableData</li>
     * </ul>
     * @param bean The requesting bean:  Many.
     * @return usage string
     */
    /*static*/ QString WhereUsedCollectors::checkLogixConditionals(NamedBean* bean) {
        QString sb; // = new StringBuilder();
        //InstanceManager.getDefault(LogixManager.class).getNamedBeanSet().forEach((logix) -> {
        foreach(NamedBean* nb, ((LogixManager*)InstanceManager::getDefault("LogixManager"))->getNamedBeanSet())
        {
         Logix* logix = (Logix*)nb;
            //logix.getUsageReport(bean).forEach((report) -> {
         foreach(NamedBeanUsageReport* report, logix->getUsageReport(bean))
         {
                if (report->usageKey.startsWith("ConditionalVariable") || report->usageKey.startsWith("ConditionalAction")) {  // NOI18N
                    QString name = logix->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME);
                    QString cdlName = report->usageBean->getDisplayName();
                    sb.append(tr("\n%1, %2, %3: %4	").arg(name).arg(cdlName).arg(report->usageKey).arg(report->usageData));  // NOI18N
                }
            }//);
        }//);
        return addHeader(sb, "ReferenceConditionals");  // NOI18N
    }

    /**
     * Create the Section usage string.
     * Usage keys:
     * <ul>
     * <li>SectionBlock</li>
     * <li>SectionSensorForwardBlocking</li>
     * <li>SectionSensorForwardStopping</li>
     * <li>SectionSensorReverseBlocking</li>
     * <li>SectionSensorReverseStopping</li>
     * </ul>
     * @param bean The requesting bean:  Block, Sensor.
     * @return usage string
     */
    /*static*/ QString WhereUsedCollectors::checkSections(NamedBean* bean) {
        QString sb; // = new StringBuilder();
        //InstanceManager.getDefault(SectionManager.class).getNamedBeanSet().forEach((section) -> {
        foreach(NamedBean* nb, ((SectionManager*)InstanceManager::getDefault("SectionManager"))->getNamedBeanSet())
        {
         Section* section = (Section*)nb;
         //section.getUsageReport(bean).forEach((report) -> {
         foreach(NamedBeanUsageReport* report, section->getUsageReport(bean))
         {
                if (report->usageKey.startsWith("SectionSensor")) {  // NOI18N
                    QString name = section->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME);
                    sb.append(tr("\n%1	").arg(name));  // NOI18N
                }
            }//);
        }//);
        return addHeader(sb, "ReferenceSections");  // NOI18N
    }

    /**
     * Create the Transit usage string.
     * Usage keys:
     * <ul>
     * <li>TransitSection</li>
     * <li>TransitSensorStopAllocation</li>
     * <li>TransitActionSensorWhen</li>
     * <li>TransitActionSensorWhat</li>
     * <li>TransitActionSignalHeadWhat</li>
     * <li>TransitActionSignalMastWhat</li>
     * </ul>
     * @param bean The requesting bean:  Section, Sensor, Signal Head, Signal Mast.
     * @return usage string
     */
    /*public*/ QString WhereUsedCollectors::checkTransits(NamedBean* bean) {
        QString sb; // = new StringBuilder();
        //InstanceManager.getDefault(TransitManager.class).getNamedBeanSet().forEach((transit) -> {
        foreach(NamedBean* nb, ((TransitManager*)InstanceManager::getDefault("TransitManager"))->getNamedBeanSet())
        {
         Transit* transit = (Transit*)nb;
            //transit.getUsageReport(bean).forEach((report) -> {
         foreach(NamedBeanUsageReport* report, transit->getUsageReport(bean))
         {
                QString name = transit->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME);
                if (report->usageKey.startsWith("TransitSensor") || report->usageKey.startsWith("TransitSection")) {  // NOI18N
                    sb.append(tr("\n%1	").arg(name));  // NOI18N
                }
                if (report->usageKey.startsWith("TransitAction")) {  // NOI18N
                    sb.append(tr("\n\t\t\t%1, action for \%2\" section	LineAction").arg(name).arg(report->usageBean->getDisplayName()));  // NOI18N
                }
            }//);
        }//);
        return addHeader(sb, "ReferenceTransits");  // NOI18N
    }

    /**
     * Create the Panel usage string.  The string includes the icon class name.
     * Usage keys:
     * <ul>
     * <li>PositionalIcon</li>
     * <li>LayoutEditorTurnout</li>
     * <li>LayoutEditorTurnout2</li>
     * <li>LayoutEditorTurnoutBlock</li>
     * <li>LayoutEditorTurnoutSensor</li>
     * <li>LayoutEditorTurnoutSignalHead</li>
     * <li>LayoutEditorTurnoutSignalMast</li>
     * <li>LayoutEditorPointSensor</li>
     * <li>LayoutEditorPointSignalHead</li>
     * <li>LayoutEditorPointSignalMast</li>
     * <li>LayoutEditorSegmentBlock</li>
     * <li>LayoutEditorXingBlock</li>
     * <li>LayoutEditorXingOther (sensor, head, mast)</li>
     * <li>Switchboard (sensor, turnout, light)</li>
     * </ul>
     * Note:  The getUsageReport is invoked at either Editor or LayoutEditor depending on the
     * panel type.  The LayoutEditor version does a super call and then does special turnout
     * checking since LE turnouts are not icons.
     * @param bean The requesting bean:  Many.
     * @return usage string
     */
    /*static*/ QString WhereUsedCollectors::checkPanels(NamedBean* bean) {
        QString sb; // = new StringBuilder();
        //InstanceManager.getDefault(jmri.jmrit.display.EditorManager.class).getEditorsList().forEach((panel) -> {
        foreach(Editor* panel, ((EditorManager*)InstanceManager::getDefault("EditorManager"))->getEditorsList())
        {
            //panel->getUsageReport(bean).forEach((report) -> {
         foreach(NamedBeanUsageReport* report, panel->getUsageReport(bean))
         {
                if (qobject_cast<SwitchboardEditor*>(panel)) {
                    sb.append(tr("\n%1	").arg(report->usageData));  // NOI18N
                } else {
                    sb.append(tr("\n%1::%2	").arg(panel->getTitle()).arg(report->usageData));  // NOI18N
                }
            }//);
        }//);
        return addHeader(sb, "ReferencePanels");  // NOI18N
    }

    /**
     * Create the CTC usage string.
     * Usage keys:  None yet.
     * @param bean The requesting bean:  Block, Sensor, Signal Head, Signal Mast, Turnout.
     * @return usage string
     */
    /*static*/ QString WhereUsedCollectors::checkCTC(NamedBean* bean) {
        log->debug(tr("CTC process pending: bean = %1").arg(bean->getDisplayName()));  // NOI18N
        return "";
    }

    /**
     * Add the specified section to the beginning of the string builder if there is data.
     * @param sb The current string builder.
     * @param bundleKey The key for the section header.
     * @return the resulting string.
     */
    /*static*/ QString WhereUsedCollectors::addHeader(QString sb, QString bundleKey) {
        if (sb.length() > 0) {
            sb.insert(0, tr("\n%1	").arg(bundleKey));  // NOI18N
            sb.append("\n");
        }
        return sb/*.toString()*/;
    }

    /*private*/ /*static*/ Logger* WhereUsedCollectors::log = LoggerFactory::getLogger("WhereUsedCollectors");
