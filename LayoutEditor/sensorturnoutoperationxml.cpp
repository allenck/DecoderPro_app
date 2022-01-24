#include "sensorturnoutoperationxml.h"
#include "sensorturnoutoperation.h"
#include "nofeedbackturnoutoperation.h"

SensorTurnoutOperationXml::SensorTurnoutOperationXml(QObject *parent) :
    CommonTurnoutOperationXml(parent)
{
    log = new Logger("SensorTurnoutOperationXml");
}
/**
 * Concrete subclass to save/restore SensorTurnoutOperation object
 * to/from XML. Most of the work is done by CommonTurnoutOperationXml
 * @author John Harper	Copyright 2005
 *
 */
///*public*/ class SensorTurnoutOperationXml extends CommonTurnoutOperationXml {

/**
 * called for a newly-constructed object to load it from an XML element
 * @param e the XML element of type "turnoutOperation"
 */
/*public*/ TurnoutOperation* SensorTurnoutOperationXml::loadOne(QDomElement e) {
    try {
        // TODO:
//        Class<?> myOpClass = Class.forName("SensorTurnoutOperation");
//        return super.loadOne(e, myOpClass.getConstructor(new Class[]{String.class, int.class, int.class}),
        return CommonTurnoutOperationXml::loadOne(e,
                NoFeedbackTurnoutOperation::getDefaultIntervalStatic(),
                NoFeedbackTurnoutOperation::getDefaultMaxTriesStatic());
    } catch (ClassNotFoundException* e1) {
        log->error("while creating NoFeedbackTurnoutOperation", e1);
        return NULL;
    }
//    catch (NoSuchMethodException* e2) {
//        log->error("while creating NoFeedbackTurnoutOperation", e2->getMessage());
//        return null;
//    }
}
