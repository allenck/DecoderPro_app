#include "entryexittesttools.h"
#include "destinationpoints.h"
#include "pointdetails.h"
#include "source.h"
#include "entryexitpairs.h"
#include "instancemanager.h"
#include "source.h"
#include "configxmlmanager.h"
#include "file.h"
#include "panelmenu.h"
#include "layouteditor.h"

EntryExitTestTools::EntryExitTestTools(QObject *parent) : QObject(parent)
{

}
//class EntryExitTestTools {
/*static*/ QMap<QString, LayoutEditor*>* EntryExitTestTools::getPanels() throw (Exception) {
    QMap<QString, LayoutEditor*>* panels = new QMap<QString, LayoutEditor*>();
    ConfigXmlManager* cm = new ConfigXmlManager();
    File* f = new File("java/test/jmri/jmrit/entryexit/load/EntryExitTest.xml");
    cm->load(f);

    for (LayoutEditor* panel : *((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getLayoutEditorPanelList()) {
        if(panel->getLayoutName()== "Alpha")
        {
         panels->insert("Alpha", panel);
        }
        else if(panel->getLayoutName()== "Beta")
        {
         panels->insert("Beta", panel);
        }
    }

    ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->getSensor("Reset")->setKnownState(Sensor::ACTIVE);
    ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->initializeLayoutBlockPaths();
    return panels;
}

PointDetails* EntryExitTestTools::getPoint(Sensor* sensor, LayoutEditor* panel, EntryExitPairs* eep) {
    return (sensor == nullptr) ? nullptr : eep->providePoint(sensor, panel);
}

Source* EntryExitTestTools::getSourceInstance(Sensor* sensor, LayoutEditor* panel, EntryExitPairs* eep) {
    PointDetails* pd = getPoint(sensor, panel, eep);
    return (pd == nullptr) ? nullptr : eep->getSourceForPoint(pd);
}

DestinationPoints* EntryExitTestTools::getDestinationPoint(Sensor* srcSensor, Sensor* destSensor, LayoutEditor* panel,  EntryExitPairs* eep) {
    Source* src = getSourceInstance(srcSensor, panel, eep);
    PointDetails* pd = getPoint(destSensor, panel, eep);
    return (src == nullptr || pd == nullptr) ? nullptr : src->getDestForPoint(pd);
}
