#include "exportcarrosteraction.h"
#include "exportcars.h"

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

 /*public*/ ExportCarRosterAction::ExportCarRosterAction(QString actionName, QWidget* frame)
    : AbstractAction(actionName, (QObject*)frame)
 {
     //super(actionName);
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void ExportCarRosterAction::actionPerformed(ActionEvent* ae) {
     ExportCars* ex = new ExportCars();
     ex->writeOperationsCarFile();
 }
}
