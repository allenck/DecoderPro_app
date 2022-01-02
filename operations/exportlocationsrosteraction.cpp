#include "exportlocationsrosteraction.h"
#include "exportlocations.h"
namespace Operations {

 /**
  * Starts the export locations action
  *
  * @author Dan Boudreau Copyright (C) 2018
  */
 ///*public*/ class ExportLocationsRosterAction : public AbstractAction {

     /*public*/ ExportLocationsRosterAction::ExportLocationsRosterAction(QObject* parent) : AbstractAction(tr("Export Locations"), parent){
         //super(Bundle.getMessage("TitleExportLocations"));
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
     }

     //@Override
     /*public*/ void ExportLocationsRosterAction::actionPerformed(JActionEvent* /*ae*/) {
         (new ExportLocations())->writeOperationsLocationFile();
     }

} // namespace Operations
