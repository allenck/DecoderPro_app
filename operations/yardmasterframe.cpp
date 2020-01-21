#include "yardmasterframe.h"
#include <QMenuBar>
#include <QMenu>
#include "setup.h"
#include "location.h"
#include "control.h"
#include "yardmasterpanel.h"
#include "printswitchlistaction.h"
#include "yardmasterbytrackaction.h"

namespace Operations
{
/**
 * Yardmaster Frame. Shows work at one location.
 *
 * @author Dan Boudreau Copyright (C) 2013
 * @version $Revision: 18630 $
 */
//public class YardmasterFrame extends OperationsFrame {

 /*public*/ YardmasterFrame::YardmasterFrame(Location *location, QWidget* parent)
    : OperationsFrame(tr("Yardmaster"), parent)
 {
  setObjectName("YardmasterFrame");
     setContentPane(new YardmasterPanel(location, this));
     //super(tr("Yardmaster"), new YardmasterPanel(location));
     this->initComponents(location);
 }

 /*private*/ void YardmasterFrame::initComponents(Location* location)
 {
  OperationsFrame::initComponents();
  if (location != NULL)
  {
   // build menu
   QMenuBar* menuBar = new QMenuBar();
   QMenu* toolMenu = new QMenu(tr("Tools"));
   QAction *print= NULL, *preview =NULL;

   toolMenu->addAction(new YardmasterByTrackAction(location,this));
   toolMenu->addAction(print = new PrintSwitchListAction(tr("Print"), location,
           false, this));
   toolMenu->addAction(preview = new PrintSwitchListAction(tr("Preview"), location,
           true, this));
   menuBar->addMenu(toolMenu);
   setMenuBar(menuBar);

   // add tool tip if in consolidation mode: "Disabled when switch list is in consolidation mode"
   if (!Setup::isSwitchListRealTime()) {
       print->setToolTip(tr("Disabled when switch list is in consolidation mode"));
       preview->setToolTip(tr("Disabled when switch list is in consolidation mode"));
   }
   setTitle(tr("Yardmaster") + " (" + location->getName() + ")");
  }

  addHelpMenu("package.jmri.jmrit.operations.Operations_Locations", true); // NOI18N

  initMinimumSize(QSize(Control::panelWidth500, Control::panelHeight500));
 }
 /*public*/ QString YardmasterFrame::getClassName()
 {
  return "jmri.jmrit.operations.locations.YardmasterFrame";
 }

}
