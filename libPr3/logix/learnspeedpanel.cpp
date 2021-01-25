#include "learnspeedpanel.h"
#include "loggerfactory.h"
#include "jpanel.h"
#include "jframe.h"
#include "dccthrottle.h"
#include "speedutil.h"
#include "oblock.h"
#include "instancemanager.h"
#include "signalspeedmap.h"

/**
 * A JInternalFrame that contains a JSlider to control loco speed, and buttons
 * for forward, reverse and STOP.
 *
 * @author Pete Cressman Copyright 2020
 */
///*public*/ class LearnSpeedPanel extends JInternalFrame implements java.beans.PropertyChangeListener {


    LearnSpeedPanel::LearnSpeedPanel(Warrant* w, QObject* parent) {
        _warrant = w;
        initGUI();
    }

    /*private*/ void LearnSpeedPanel::initGUI() {
        JPanel* mainPanel = new JPanel();
        this->setContentPane(mainPanel);
        mainPanel->setLayout(new QVBoxLayout());//BorderLayout());
        this->setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);

        JPanel* panel = new JPanel();
        QFont f = QFont();
        f.setPointSize(32);
        panel->setFont(f);//new Font("", Font.PLAIN, 32));
        panel->setLayout(new QHBoxLayout());//panel, BoxLayout.X_AXIS));
        panel->setOpaque(false);
        OBlock* blk = _warrant->getBlockAt(0);
        QString name;
        if (blk != nullptr) {
            name = blk->getDisplayName();
        } else {
            name = _warrant->getDisplayName();
        }
        _scaleSpeed = new JLabel(tr("Train '%1' ready to start\nin block '%2'").arg(_warrant->getTrainName()).arg(name));
        panel->layout()->addWidget(_scaleSpeed);

        mainPanel->layout()->addWidget(panel/*, BorderLayout.CENTER*/);
    }

    /*public*/ void LearnSpeedPanel::notifyAddressThrottleFound(DccThrottle* t) {
        if (log->isDebugEnabled()) {
            log->debug("control panel received new throttle");
        }
        _throttle = t;
        _warrant->getSpeedUtil()->setIsForward(_throttle->getIsForward());

        _throttle->addPropertyChangeListener((PropertyChangeListener*)this);
        if (log->isDebugEnabled()) {
            DccLocoAddress* Address = (DccLocoAddress*) _throttle->getLocoAddress();
            log->debug(tr("new address is %1").arg(Address->toString()));
        }
    }

    /**
     * update the state of this panel if direction or speed change
     */
    //@Override
    /*public*/ void LearnSpeedPanel::propertyChange(PropertyChangeEvent* e) {
        if (e->getPropertyName() == (Throttle::SPEEDSETTING)) {
            _currentThrottleValue = (e->getNewValue()).toFloat();
            _scaleSpeed->setText(setSpeed());
        } else if (e->getPropertyName() == (Throttle::ISFORWARD)) {
            _warrant->getSpeedUtil()->setIsForward( e->getNewValue().toBool());
            _scaleSpeed->setText(setSpeed());
        }
        if (log->isDebugEnabled()) {
            log->debug(tr("Property change event received %1 / %2").arg(e->getPropertyName()).arg(e->getNewValue().toString()));
        }
    }

    /**
     * @return a string for displaying speed if available
     */
    /*private*/ QString LearnSpeedPanel::setSpeed() {
        float trackSpeed = _warrant->getSpeedUtil()->getTrackSpeed(_currentThrottleValue);
        float speed = 0;
        QString units;
        SignalSpeedMap* speedMap = (SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap");
        switch (speedMap->getInterpretation()) {
            case SignalSpeedMap::PERCENT_NORMAL:
            case SignalSpeedMap::PERCENT_THROTTLE:
                units = tr("% Throttle");
                speed = _currentThrottleValue * 100;
                break;
            case SignalSpeedMap::SPEED_MPH:
                units = tr("Miles per hour");
                speed = trackSpeed * speedMap->getLayoutScale() * 2.2369363f;
                break;
            case SignalSpeedMap::SPEED_KMPH:
                units = tr("Kilometers per hour");
                speed = trackSpeed * speedMap->getLayoutScale() * 3.6f;
                break;
            default:
                units = "Error";
                log->error(tr("Unknown speed interpretation %1").arg(speedMap->getInterpretation()));
        }
        return tr("%1 (%2 %3)").arg(
                tr("speedmm").arg(qRound(trackSpeed*1000))).arg(
                qRound(speed)).arg(units);
    }

    /**
     * "Destructor"
     */
    /*public*/ void LearnSpeedPanel::destroy() {
        if (_throttle != nullptr) {
            _throttle->removePropertyChangeListener((PropertyChangeListener*)this);
            if (log->isDebugEnabled()) {
                DccLocoAddress* Address = (DccLocoAddress*) _throttle->getLocoAddress();
                log->debug(tr("Address %1 destroyed").arg(Address->toString()));
            }
            _throttle = nullptr;
        }
    }


    /*private*/ /*static*/ /*final*/ Logger* LearnSpeedPanel::log = LoggerFactory::getLogger("LearnSpeedPanel");
