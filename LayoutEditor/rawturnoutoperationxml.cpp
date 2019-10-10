#include "rawturnoutoperationxml.h"
#include "rawturnoutoperation.h"

RawTurnoutOperationXml::RawTurnoutOperationXml(QObject *parent) :
    CommonTurnoutOperationXml(parent)
{
}
/**
 * Concrete subclass to save/restore RawTurnoutOperation object
 * to/from XML. Most of the work is done by CommonTurnoutOperationXml
 * Based on NoFeedbackTurnoutOperationXml.
 * @author Paul Bender Copyright 2008
 *
 */
///*public*/ class RawTurnoutOperationXml extends CommonTurnoutOperationXml {

/**
 * called for a newly-constructed object to load it from an XML element
 * @param e the XML element of type "turnoutOperation"
 */
/*public*/ TurnoutOperation* RawTurnoutOperationXml::loadOne(QDomElement e)
{
 //try {
      //Class<?> myOpClass = Class.forName("jmri.RawTurnoutOperation");
    RawTurnoutOperation* myOpClass = new RawTurnoutOperation();
#if 0 // TODO:
        return CommonTurnoutOperationXml::loadOne(e, myOpClass.getConstructor(new Class[]{String.class, int.class, int.class}),
                    RawTurnoutOperation::getDefaultIntervalStatic(),
                    RawTurnoutOperation::getDefaultMaxTriesStatic());
        } catch (ClassNotFoundException e1) {
            log.error("while creating NoFeedbackTurnoutOperation", e1);
            return null;
        } catch (NoSuchMethodException e2) {
            log.error("while creating NoFeedbackTurnoutOperation", e2);
            return null;
        }
#endif
    return (TurnoutOperation*)myOpClass;
    }
