#include "importcarrosteraction.h"
#include "importcars.h"
namespace Operations
{
/**
 * Starts the ImportCars thread
 *
 * @author Dan Boudreau Copyright (C) 2008
 * @version $Revision$
 */
//public class ImportCarRosterAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -8894977271081874448L;

 /*public*/ ImportCarRosterAction::ImportCarRosterAction(QString actionName, QWidget* frame)
                              : AbstractAction(actionName, (QObject*)frame)
 {

     //(actionName);
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 //@Override
 /*public*/ void ImportCarRosterAction::actionPerformed(ActionEvent* ae) {
#if 0
     Thread mb = new ImportCars();
     mb.setName("Import Cars"); // NOI18N
     mb.start();
#endif
 }

}
