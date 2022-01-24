#include "rawturnoutoperationxml.h"
#include "rawturnoutoperation.h"
#include "exceptions.h"
#include "loggerfactory.h"
#include "class.h"

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
     RawTurnoutOperation* myOpClass = (RawTurnoutOperation*)Class::forName("RawTurnoutOperation");
    //RawTurnoutOperation* myOpClass = new RawTurnoutOperation();
#if 0 // TODO:
        return CommonTurnoutOperationXml::loadOne(e, myOpClass->getConstructor(new Class[]{"String", "int", "int"}),
                    RawTurnoutOperation::getDefaultIntervalStatic(),
                    RawTurnoutOperation::getDefaultMaxTriesStatic());
        } catch (ClassNotFoundException* e1) {
            log->error("while creating NoFeedbackTurnoutOperation", e1);
            return nullptr;
        } catch (NoSuchMethodException* e2) {
            log->error("while creating NoFeedbackTurnoutOperation", e2);
            return nullptr;
        }
#endif
    return (TurnoutOperation*)myOpClass;
    }
/*private*/ /*final*/ /*static*/ Logger* RawTurnoutOperationXml::log = LoggerFactory::getLogger("RawTurnoutOperationXml");
