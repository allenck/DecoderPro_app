#include "enginesetframe.h"
#include "operationsxml.h"
#include "engine.h"
#include <QMessageBox>
#include "enginemanager.h"
#include "enginemanagerxml.h"
#include <QCheckBox>
#include <QScrollArea>
#include <QGroupBox>
#include "consist.h"
#include "instancemanager.h"

//EngineSetFrame::EngineSetFrame()
//{

//}
namespace Operations
{
/**
 * Frame for user to place engine on the layout
 *
 * @author Dan Boudreau Copyright (C) 2008, 2010
 * @version $Revision: 28746 $
 */
///*public*/ class EngineSetFrame extends RollingStockSetFrame implements
//        java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = -7608591085014836578L;

 ///*protected*/ static final ResourceBundle rb = ResourceBundle
//         .getBundle("jmri.jmrit.operations.rollingstock.engines.JmritOperationsEnginesBundle");


 /*public*/ EngineSetFrame::EngineSetFrame(QObject* parent) : RollingStockSetFrame(tr("Set Locomotive")) {
  setFrameRef(getClassName());
     //super(Bundle.getMessage("TitleEngineSet"));
  manager = ((EngineManager*)InstanceManager::getDefault("Operations::EngineManager"));
  managerXml = ((EngineManagerXml*)InstanceManager::getDefault("EngineManagerXml"));
 }

 /*public*/ void EngineSetFrame::initComponents()
{
  RollingStockSetFrame::initComponents();

  // build menu
  addHelpMenu("package.jmri.jmrit.operations.Operations_LocomotivesSet", true); // NOI18N

  // disable location unknown, return when empty, final destination fields
  locationUnknownCheckBox->setVisible(false);
  paneOptional->setVisible(false);
  pFinalDestination->setVisible(false);
  autoTrainCheckBox->setVisible(false);

  // tool tips
  outOfServiceCheckBox->setToolTip(tr("When checked, ignore this loco when building trains"));

  packFrame();
 }

 /*public*/ void EngineSetFrame::loadEngine(Engine* engine) {
     _engine = engine;
     load(engine);
 }

 /*protected*/ ResourceBundle* EngineSetFrame::getRb() {
     return rb;
 }

 /*protected*/ bool EngineSetFrame::save()
 {
  if (!RollingStockSetFrame::save())
  {
      return false;
  }
  // check for train change
  checkTrain(_engine);
  // is this engine part of a consist?
  if (_engine->getConsist() != NULL)
  {
//         if (JOptionPane.showConfirmDialog(this, Bundle.getMessage("engineInConsist"),
//                 Bundle.getMessage("enginePartConsist"), JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
   if(QMessageBox::question(this, tr("Locomotive is part of a consist"),tr("This loco is part of a consist, do you want the other locomotives to also have the same settings?"), QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes)
   {
    // convert cars list to rolling stock list
    QList<RollingStock*> list = _engine->getConsist()->getGroup();
    if (!updateGroup(list))
    {
        return false;
    }
   }
  }
  OperationsXml::save();
  return true;
 }

 /*public*/ QString EngineSetFrame::getClassName()
 {
  return "jmri.jmrit.operations.rollingstock.engines.EngineSetFrame";
 }

 ESResourceBundle::ESResourceBundle()
 {
  map.insert("rsType", "Locomotive");
  map.insert("rsNeedToRemoveStaging", tr(""));
  map.insert("rsInStaging", tr(""));
  map.insert("rsTrainNotServType", tr(""));
  map.insert("rsNotMove", tr(""));
 }
}
