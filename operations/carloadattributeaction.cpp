#include "carloadattributeaction.h"
#include "carloadeditframe.h"
#include "logger.h"

namespace Operations
{
 /**
  * Frame for adding and editing the car roster for operations.
  *
  * @author Daniel Boudreau Copyright (C) 2009, 2010, 2011
  * @version $Revision: 28746 $
  */
 //final class CarLoadAttributeAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 8136064419213869243L;

 /*public*/ CarLoadAttributeAction::CarLoadAttributeAction(QString actionName, CarLoadEditFrame* clef) : AbstractAction(actionName,clef)
 {
  //super(actionName);
  log = new Logger("CarLoadAttributeAction");
  this->clef = clef;
  connect(this, SIGNAL(triggered()),this, SLOT(actionPerformed()));
 }


 /*public*/ void CarLoadAttributeAction::actionPerformed(ActionEvent* ae) {
     log->debug("Show attribute quanity");
     clef->toggleShowQuanity();
 }

}
