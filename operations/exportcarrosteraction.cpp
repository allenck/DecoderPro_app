#include "exportcarrosteraction.h"
#include "exportcars.h"
#include "carstablemodel.h"

namespace Operations
{
 /**
  * Starts the ImportCars thread
  *
  * @author Dan Boudreau Copyright (C) 2008
  * @version $Revision: 28746 $
  */
 ///*public*/ class ExportCarRosterAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 4463124347780716468L;

 /*public*/ ExportCarRosterAction::ExportCarRosterAction(CarsTableFrame* carsTableFrame)
    : AbstractAction(tr("Export"), (QObject*)carsTableFrame)
 {
     //super(actionName);
  _carsTableFrame = carsTableFrame;
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void ExportCarRosterAction::actionPerformed(JActionEvent* /*ae*/) {
  ExportCars* exportCars = new ExportCars(*_carsTableFrame->carsTableModel->getSelectedCarList());
          exportCars->writeOperationsCarFile();
 }
}
