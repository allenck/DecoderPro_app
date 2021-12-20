#include "classmigration.h"
#include "loggerfactory.h"

ClassMigration::ClassMigration()
{

}

/*private*/ QMap<QString, QString> ClassMigration::map = { // see ClassMigration properties
 {"jmri.configurexml.AbstractLightManagerConfigXML","jmri.managers.configurexml.AbstractLightManagerConfigXML"},
 {"jmri.configurexml.AbstractMemoryManagerConfigXML","jmri.managers.configurexml.AbstractMemoryManagerConfigXML"},
 {"jmri.configurexml.AbstractReporterManagerConfigXML","jmri.managers.configurexml.AbstractReporterManagerConfigXML"},
 {"jmri.configurexml.AbstractSensorManagerConfigXML","jmri.managers.configurexml.AbstractSensorManagerConfigXML"},
 {"jmri.configurexml.AbstractSignalHeadManagerXml","jmri.managers.configurexml.AbstractSignalHeadManagerXml"},
 {"jmri.configurexml.AbstractTurnoutManagerConfigXML","jmri.managers.configurexml.AbstractTurnoutManagerConfigXML"},

 {"jmri.configurexml.DccSignalHeadXml","jmri.managers.configurexml.DccSignalHeadXml"},
 {"jmri.configurexml.DefaultConditionalManagerXml","jmri.managers.configurexml.DefaultConditionalManagerXml"},
 {"jmri.configurexml.DefaultLogixManagerXml","jmri.managers.configurexml.DefaultLogixManagerXml"},
 {"jmri.configurexml.DefaultMemoryManagerXml","jmri.managers.configurexml.DefaultMemoryManagerXml"},
 {"jmri.configurexml.DefaultRouteManagerXml","jmri.managers.configurexml.DefaultRouteManagerXml"},
 {"jmri.configurexml.DoubleTurnoutSignalHeadXml","jmri.managers.configurexml.DoubleTurnoutSignalHeadXml"},
 {"jmri.configurexml.GuiLafConfigPaneXml","jmri.managers.configurexml.GuiLafConfigPaneXml"},
 {"jmri.configurexml.LsDecSignalHeadXml","jmri.managers.configurexml.LsDecSignalHeadXml"},
 {"jmri.configurexml.TripleTurnoutSignalHeadXml","jmri.managers.configurexml.TripleTurnoutSignalHeadXml"},
 {"jmri.configurexml.VirtualSignalHeadXml","jmri.managers.configurexml.VirtualSignalHeadXml"},

 {"jmri.jmrit.display.configurexml.LayoutEditorXml","jmri.jmrit.display.layoutEditor.configurexml.LayoutEditorXml"},
 {"jmri.jmrit.display.configurexml.ControlPanelEditorXml","jmri.jmrit.display.controlPanelEditor.configurexml.ControlPanelEditorXml"},
 {"jmri.jmrit.display.configurexml.PanelEditorXml","jmri.jmrit.display.panelEditor.configurexml.PanelEditorXml"},

 {"jmri.jmrit.display.configurexml.LayoutBlockManagerXml","jmri.jmrit.display.layoutEditor.configurexml.LayoutBlockManagerXml"},

 {"jmri.jmrit.signalling.configurexml.EntryExitPairsXml","jmri.jmrit.entryexit.configurexml.EntryExitPairsXml"},

 {"jmri.managers.configurexml.InternalLightManagerXml","jmri.jmrix.internal.configurexml.InternalLightManagerXml"},
 {"jmri.managers.configurexml.InternalReporterManagerXml","jmri.jmrix.internal.configurexml.InternalReporterManagerXml"},
 {"jmri.managers.configurexml.InternalSensorManagerXml","jmri.jmrix.internal.configurexml.InternalSensorManagerXml"},
 {"jmri.managers.configurexml.InternalTurnoutManagerXml","jmri.jmrix.internal.configurexml.InternalTurnoutManagerXml"},


 //Added for May 2020 Layout Editor refactoring (also includes mapping of still-older classes)

 {"jmri.jmrit.display.layoutEditor.configurexml.TrackSegmentXml","jmri.jmrit.display.layoutEditor.configurexml.TrackSegmentViewXml"},
 {"jmri.jmrit.display.configurexml.TrackSegmentXml","jmri.jmrit.display.layoutEditor.configurexml.TrackSegmentViewXml"},

 {"jmri.jmrit.display.layoutEditor.configurexml.PositionablePointXml","jmri.jmrit.display.layoutEditor.configurexml.PositionablePointViewXml"},
 {"jmri.jmrit.display.configurexml.PositionablePointXml","jmri.jmrit.display.layoutEditor.configurexml.PositionablePointXml"},

 {"jmri.jmrit.display.layoutEditor.configurexml.LevelXingXml","jmri.jmrit.display.layoutEditor.configurexml.LevelXingViewXml"},

 {"jmri.jmrit.display.layoutEditor.configurexml.LayoutTurntableXml","jmri.jmrit.display.layoutEditor.configurexml.LayoutTurntableViewXml"},
 {"jmri.jmrit.display.configurexml.LayoutTurntableXml","jmri.jmrit.display.layoutEditor.configurexml.LayoutTurntableXml"},

 {"jmri.jmrit.display.layoutEditor.configurexml.LayoutTurnoutXml","jmri.jmrit.display.layoutEditor.configurexml.LayoutTurnoutViewXml"},
 {"jmri.jmrit.display.configurexml.LayoutTurnoutXml","jmri.jmrit.display.layoutEditor.configurexml.LayoutTurnoutXml"},

 {"jmri.jmrit.display.layoutEditor.configurexml.LayoutSlipXml","jmri.jmrit.display.layoutEditor.configurexml.LayoutSlipViewXml"},

 //#      Transient examples, may never have been written by a production file

 {"jmri.jmrit.display.layoutEditor.configurexml.LayoutDoubleSlipXml","jmri.jmrit.display.layoutEditor.configurexml.LayoutDoubleSlipViewXml"},
 {"jmri.jmrit.display.layoutEditor.configurexml.LayoutSingleSlipXml","jmri.jmrit.display.layoutEditor.configurexml.LayoutSingleSlipViewXml"},

 {"jmri.jmrit.display.layoutEditor.configurexml.LayoutLHTurnoutXml","jmri.jmrit.display.layoutEditor.configurexml.LayoutLHTurnoutViewXml"},
 {"jmri.jmrit.display.layoutEditor.configurexml.LayoutRHTurnoutXml","jmri.jmrit.display.layoutEditor.configurexml.LayoutRHTurnoutViewXml"},
 {"jmri.jmrit.display.layoutEditor.configurexml.LayoutWyeXml","jmri.jmrit.display.layoutEditor.configurexml.LayoutWyeViewXml"},

 {"jmri.jmrit.display.layoutEditor.configurexml.LayoutXOverXml","jmri.jmrit.display.layoutEditor.configurexml.LayoutXOverViewXml"},
 {"jmri.jmrit.display.layoutEditor.configurexml.LayoutRHXOverXml","jmri.jmrit.display.layoutEditor.configurexml.LayoutRHXOverViewXml"},
 {"jmri.jmrit.display.layoutEditor.configurexml.LayoutLHXOverXml","jmri.jmrit.display.layoutEditor.configurexml.LayoutLHXOverViewXml"},
 {"jmri.jmrit.display.layoutEditor.configurexml.LayoutDoubleXOverXml","jmri.jmrit.display.layoutEditor.configurexml.LayoutDoubleXOverViewXml"}

};

/*public*/ /*static*/ QString ClassMigration::migrateName(QString oldName){
 QString newName = oldName;
 if(map.contains(oldName)){
  newName = map.value(oldName);
  log->debug(QString("migrating %1 to %2").arg( oldName, newName));
 }
 return newName;
}

/*private*/ /*static*/ Logger* ClassMigration::log = LoggerFactory::getLogger("ClassMigration");
