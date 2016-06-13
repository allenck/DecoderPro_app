#include "nofeedbackturnoutoperationconfig.h"
#include "turnoutoperation.h"

//NoFeedbackTurnoutOperationConfig::NoFeedbackTurnoutOperationConfig(QObject *parent) :
//    CommonTurnoutOperationConfig(parent)
//{
//}
/**
 * Configuration for NoFeedbackTurnoutOperation class
 * All the work is done by the Common... class
 * @author John Harper	Copyright 2005
 *
 */
// /*public*/ class NoFeedbackTurnoutOperationConfig extends CommonTurnoutOperationConfig {

/**
 * Create the config JPanel, if there is one, to configure this operation type
 */
/*public*/ NoFeedbackTurnoutOperationConfig::NoFeedbackTurnoutOperationConfig(TurnoutOperation* op, QWidget *parent) :
    CommonTurnoutOperationConfig(op, parent){
    //super(op);
}
