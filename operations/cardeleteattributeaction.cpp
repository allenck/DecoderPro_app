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

 /*public*/ CarDeleteAttributeAction::CarDeleteAttributeAction(QString actionName, CarAttributeEditFrame* caef)
: AbstractAction(actionName, caef)
{
     //super(actionName);
     this->caef = caef;
  log = new Logger("CarDeleteAttributeAction");
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }


 /*public*/ void CarDeleteAttributeAction::actionPerformed(ActionEvent* ae) {
     log->debug("Delete unused attributes");
     caef->deleteUnusedAttribures();
 }
}
