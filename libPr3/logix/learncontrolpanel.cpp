#include "learncontrolpanel.h"
#include "jslider.h"
#include "jspinner.h"
#include "spinnernumbermodel.h"
#include "speedstepmode.h"
#include "loggerfactory.h"
#include "learnthrottleframe.h"
#include "throttle.h"
#include <QButtonGroup>
#include "instancemanager.h"
#include "borderlayout.h"
#include <QVariant>
#include "vptr.h"

/**
 * A JInternalFrame that contains a JSlider to control loco speed, and buttons
 * for forward, reverse and STOP.
 * <p>
 * TODO: fix speed increments (14, 28)
 *
 * @author glen Copyright (C) 2002
 * @author Bob Jacobsen Copyright (C) 2007
 * @author Ken Cameron Copyright (C) 2008
 *
 */
///*public*/ class ControlPanel extends JInternalFrame implements java.beans.PropertyChangeListener {



    /**
     * Constructor.
     * @param ltf the main learn throttle frame.
     */
    /*public*/ LearnControlPanel::LearnControlPanel(LearnThrottleFrame* ltf) : ControlPanel(){
        //super("Speed");
        _throttleFrame = ltf;
   }


    // update the state of this panel if any of the properties change
    //@Override
    /*public*/ void LearnControlPanel::propertyChange(PropertyChangeEvent* e) {
        if (log->isDebugEnabled()) {
            log->debug(tr("propertyChange: %1, newValue= %2").arg(e->getPropertyName()).arg(e->getNewValue().toString()));
        }
        if (e->getPropertyName() == (Throttle::SPEEDSETTING)) {
            float speed = (/*(Float)*/ e->getNewValue()).toFloat();
            _throttleFrame->setSpeedSetting(speed);
        } else if (e->getPropertyName() == (Throttle::SPEEDSTEPS)) {
            SpeedStepMode* steps = /*(SpeedStepMode)*/VPtr<SpeedStepMode>::asPtr(e->getNewValue());
            _throttleFrame->setSpeedStepMode(steps->mode);
        } else if (e->getPropertyName() == (Throttle::ISFORWARD)) {
            bool Forward = (/*(Boolean)*/ e->getNewValue()).toBool();
            _throttleFrame->setButtonForward(Forward);
        }
    }



    // initialize logging
    /*private*/ /*static*/ /*final*/ Logger* LearnControlPanel::log = LoggerFactory::getLogger("ControlPanel");
