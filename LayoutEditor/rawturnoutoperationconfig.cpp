#include "rawturnoutoperationconfig.h"
#include "turnoutoperation.h"

//RawTurnoutOperationConfig::RawTurnoutOperationConfig(QObject *parent) :
//    CommonTurnoutOperationConfig(parent)
//{
//}
/**
 * Configuration for RawTurnoutOperation class
 * All the work is done by the Common... class
 * Based on NoFeedbackTurountOperationConfig.java
 * @author Paul Bender Copyright 2008
 *
 */
// /*public*/ class RawTurnoutOperationConfig extends CommonTurnoutOperationConfig {

/**
 * Create the config JPanel, if there is one, to configure this operation type
 */
/*public*/ RawTurnoutOperationConfig::RawTurnoutOperationConfig(TurnoutOperation* op, QWidget *parent) : CommonTurnoutOperationConfig(op, parent)
{
    //super(op);
}
