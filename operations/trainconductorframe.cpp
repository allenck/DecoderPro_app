#include "trainconductorframe.h"
#include "control.h"
#include <QMenu>
#include <QMenuBar>
#include "train.h"
#include "trainconductorpanel.h"
#include "showcarsintrainaction.h"

namespace Operations
{
/**
 * Conductor Frame. Shows work for a train one location at a time.
 *
 * @author Dan Boudreau Copyright (C) 2011, 2013
 * @version $Revision: 18630 $
 */
//public*/ class TrainConductorFrame extends OperationsFrame {

 /*public*/ TrainConductorFrame::TrainConductorFrame(Train* train, QWidget* parent)
   : OperationsFrame(/*new TrainConductorPanel(),*/ parent)
 {
  //super(new TrainConductorPanel(train));
  setContentPane(new TrainConductorPanel(train, this));
  this->initComponents(train);
 }

 /*private*/ void TrainConductorFrame::initComponents(Train* train)
 {
  OperationsFrame::initComponents();

  if (train != NULL) {
      setTitle(tr("Train Conductor") + " (" + train->getName() + ")");
  }

  // build menu
  QMenuBar* menuBar = new QMenuBar();
  if (train != NULL)
  {
   QMenu* toolMenu = new QMenu(tr("Tools"));
   toolMenu->addAction(new ShowCarsInTrainAction(tr("Show Cars In Train"), train,this));
   menuBar->addMenu(toolMenu);
  }
  setMenuBar(menuBar);
  addHelpMenu("package.jmri.jmrit.operations.Operations_Trains", true); // NOI18N

  initMinimumSize(QSize(Control::panelWidth500, Control::panelHeight500));
 }

 /*public*/ QString TrainConductorFrame::getClassName()
 {
  return "jmri.jmrit.operations.trains.TrainConductorFrame";
 }


}
