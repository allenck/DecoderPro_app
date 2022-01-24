#include "learnfunctionpanel.h"
#include "loggerfactory.h"
#include "dccthrottle.h"
#include "rosterentry.h"
#include "learnthrottleframe.h"
#include "propertychangeevent.h"

/**
 * A JInternalFrame that contains buttons for each decoder function.
 */
// /*public*/ class FunctionPanel extends JInternalFrame implements FunctionListener, java.beans.PropertyChangeListener {


/**
 * Constructor.
 *
 * @param rosterEntry the associated roster entry
 * @param learnFrame  the window in which this window is embedded
 */
/*public*/ LearnFunctionPanel::LearnFunctionPanel(LearnThrottleFrame* learnFrame)
: FunctionPanel(){
    //super("Functions");
    _throttleFrame = learnFrame;
}


// update the state of this panel if any of the properties change
//@Override
/*public*/ void LearnFunctionPanel::propertyChange(PropertyChangeEvent* e) {
    QString functionName = e->getPropertyName();
    if (!functionName.startsWith("F")) {
        return;
    }
    bool isSet = (/*(Boolean)*/ e->getNewValue().toBool());

    for ( int i = 0; i< 29; i++ ) {
        if (functionName == (Throttle::getFunctionString(i))) {
            functionButton[i]->setState(isSet);
            break;
        }
        if (functionName == (Throttle::getFunctionMomentaryString(i))) {
            functionName = "Lock" + Throttle::getFunctionString(i);
            functionButton[0]->setIsLockable(isSet);
            _throttleFrame->setFunctionLock(functionName, isSet);
            return;
        }
    }
    _throttleFrame->setFunctionState(functionName, isSet);
}

/*private*/ /*final*/ /*static*/ Logger* LearnFunctionPanel::log = LoggerFactory::getLogger("FunctionPanel");
