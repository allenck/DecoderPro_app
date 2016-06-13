#include "turnoutoperationconfig.h"
#include "turnoutoperation.h"
#include "nofeedbackturnoutoperationconfig.h"
#include "rawturnoutoperationconfig.h"
#include "sensorturnoutoperationconfig.h"

//TurnoutOperationConfig::TurnoutOperationConfig(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * configuration panel for TurnoutOperation class
 * Must be overridden to define specific panel details for class
 * Must have exactly one constructor like the one shown below
 * @author John Harper	Copyright 2005
 * @version $Revision: 17977 $
 */
// /*public*/ class TurnoutOperationConfig extends JPanel {


TurnoutOperationConfig::TurnoutOperationConfig(TurnoutOperation* op, QWidget *parent)  : QWidget(parent){
    myOperation = op;
    log = new Logger("TurnoutOperationConfig");
}

TurnoutOperation* TurnoutOperationConfig::getOperation() { return myOperation; }

//Boudreau 2009: Should not override isValid() causes contents to not be be displayed with Java 1.6
///*public*/ boolean isValid() { return valid; }

/*public*/ void TurnoutOperationConfig::endConfigure() {log->error("Should have been overridden!");}

/**
 * Given an instance of a concrete subclass of
 * the TurnoutOperation class, looks for a corresponding ...Config
 * class and creates an instance of it. If anything goes wrong (no such
 * class, wrong constructors, instantiation error, ....) just return null
 * @param op	operation for which configurator is required
 * @return	the configurator
 */
/*static*/ /*public*/ TurnoutOperationConfig* TurnoutOperationConfig::getConfigPanel(TurnoutOperation* op) {
    TurnoutOperationConfig* config = NULL;
    Logger log("TurnoutOperationConfig");
//    String[] path = jmri.util.StringUtil.split(op.getClass().getName(), ".");
//    String configName = "jmri.jmrit.turnoutoperations." + path[path.length-1] + "Config";
//    try {
//        Class<?> configClass = Class.forName(configName);
//        Constructor<?>[] constrs = configClass.getConstructors();
//        if (constrs.length==1) {
//            try {
//                config = (TurnoutOperationConfig)constrs[0].newInstance(new Object[]{op});
//            } catch (Throwable e) { }		// too many to list!
//        }
//    } catch (ClassNotFoundException e) { }
    QString configName = op->metaObject()->className();
    if(configName == "NoFeedbackTurnoutOperation")
     config = new NoFeedbackTurnoutOperationConfig(op);
    else if(configName == "RawTurnoutOperation")
     config = new RawTurnoutOperationConfig(op);
    else if(configName == "SensorTurnoutOperation")
     config = new SensorTurnoutOperationConfig(op);

    if (config==NULL) {
        //config = null;
        log.debug("could not create configurator for "+configName);
    }
    return config;
}
