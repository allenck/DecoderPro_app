#include "sensorturnoutoperationconfig.h"
#include "turnoutoperation.h"

//SensorTurnoutOperationConfig::SensorTurnoutOperationConfig(QObject *parent) :
//    CommonTurnoutOperationConfig(parent)
//{
//}
/**
 * Configuration for NoFeedbackTurnoutOperation class
 * All the work is done by the Common... class
 * @author John Harper	Copyright 2005
 *
 */
// /*public*/ class SensorTurnoutOperationConfig extends CommonTurnoutOperationConfig {

/**
 * Create the config JPanel, if there is one, to configure this operation type
 */
/*public*/ SensorTurnoutOperationConfig::SensorTurnoutOperationConfig(TurnoutOperation* op, QWidget *parent) : CommonTurnoutOperationConfig(op, parent)
{
    //super(op);
}
