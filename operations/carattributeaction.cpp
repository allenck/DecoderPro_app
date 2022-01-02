#include "carattributeaction.h"
#include "carattributeeditframe.h"
#include "logger.h"

//CarAttributeAction::CarAttributeAction()
//{

//}
namespace Operations
{
/**
 * Frame for adding and editing the car roster for operations.
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2014
 * @version $Revision: 28746 $
 */
//final class CarAttributeAction extends AbstractAction {

    /**
     *
     */
    //private static final long serialVersionUID = -369749063288544953L;

    /*public*/ CarAttributeAction::CarAttributeAction(CarAttributeEditFrame* caef) : AbstractAction(tr("Car Quantity"), caef) {
        //super(actionName);
        this->caef = caef;
        log = new Logger("CarAttributeAction");
        connect(this, SIGNAL(triggered(bool)), this,SLOT(actionPerformed()));
    }


    /*public*/ void CarAttributeAction::actionPerformed(JActionEvent *ae) {
        log->debug("Show attribute quanity");
        caef->toggleShowQuanity();
    }

}
