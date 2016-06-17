#include "exporttrainrosteraction.h"
#include "exporttrains.h"

namespace Operations
{
 /**
  * Export trains to a CSV file
  *
  * @author Dan Boudreau Copyright (C) 2015
  * @version $Revision: 28746 $
  */
 ///*public*/ class ExportTrainRosterAction extends AbstractAction {

 /**
  *
  */
// private static final long serialVersionUID = 4463124347780716468L;

 /*public*/ ExportTrainRosterAction::ExportTrainRosterAction(QObject* parent)
 : AbstractAction(tr("Export"),parent)
 {
     //super(Bundle.getMessage("MenuItemExport"));
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void ExportTrainRosterAction::actionPerformed(ActionEvent* ae) {
     ExportTrains* ex = new ExportTrains();
     ex->writeOperationsCarFile();
 }

}
