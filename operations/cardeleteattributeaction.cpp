#include "cardeleteattributeaction.h"
#include "carattributeeditframe.h"
#include "logger.h"

//CarDeleteAttributeAction::CarDeleteAttributeAction()
//{

//}
namespace Operations
{
//final class CarDeleteAttributeAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 6118522896008395241L;

 /*public*/ CarDeleteAttributeAction::CarDeleteAttributeAction(CarAttributeEditFrame* caef)
: AbstractAction(tr("Delete unused attribute names"), caef)
{
     //super(actionName);
     this->caef = caef;
  log = new Logger("CarDeleteAttributeAction");
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }


 /*public*/ void CarDeleteAttributeAction::actionPerformed(ActionEvent* ae) {
     log->debug("Delete unused attributes");
     caef->deleteUnusedAttributes();
 }
}
