#include "autotrainsframe.h"
#include "dispatcherframe.h"
#include "autoactivetrain.h"
#include "throttle.h"
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QSlider>
#include "jseparator.h"
#include "activetrain.h"
#include "instancemanager.h"
#include "throttlemanager.h"
#include <QMenu>
#include <QMenuBar>
#include <QBoxLayout>
#include "flowlayout.h"
#include <QButtonGroup>
#include <QSignalMapper>


//AutoTrainsFrame::AutoTrainsFrame()
//{

//}
/**
 * AutoTrainsFrame provides a user interface to trains that are running
 * automatically under Dispatcher.
 * <P>
 * There is only one AutoTrains window. AutoTrains are added and deleted from
 * this window as they are added or terminated.
 * <P>
 * This file is part of JMRI.
 * <P>
 * JMRI is open source software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published by the
 * Free Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * @author	Dave Duchamp Copyright (C) 2010
 */
///*public*/ class AutoTrainsFrame extends jmri.util.JmriJFrame {

/*public*/ AutoTrainsFrame::AutoTrainsFrame(DispatcherFrame* disp) :JmriJFrame(false, true) {
 Logger* log = new Logger("AutoTrainsFrame");
 // instance variables
 _dispatcher = NULL;
 _autoTrainsList = new QList<AutoActiveTrain*>();
 _listeners = new QList<PropertyChangeListener*>();
 //Keep track of throttle and listeners to update frame with their current state.
 _throttles = new QList<Throttle*>();
 _throttleListeners = new QList<PropertyChangeListener*>();

 // variables for AutoTrains window
 autoTrainsFrame = NULL;
 contentPane = NULL;
 //This would be better refactored this all into a sub-class, rather than multiple arraylists.
 // note: the following array lists are synchronized with _autoTrainsList
 _JPanels = new QList<QWidget*>();
 _throttleStatus = new QList<QLabel*>();
 _trainLabels = new QList<QLabel*>();
 _stopButtons = new QList<QPushButton*>();
 _manualButtons = new QList<QPushButton*>();
 _resumeAutoRunningButtons = new QList<QPushButton*>();
 _forwardButtons = new QList<QRadioButton*>();
 _reverseButtons = new QList<QRadioButton*>();
 _speedSliders = new QList<QSlider*>();

 _separators = new QList<JSeparator*>();

 tStopMapper = new QSignalMapper();
 connect(tStopMapper,SIGNAL(mapped(QString)), this, SLOT(stopResume(QString)));
 tManualMapper = new QSignalMapper();
 connect(tManualMapper, SIGNAL(mapped(QString)), this, SLOT(manualAuto(QString)));
 tResumeAutoOperationMapper = new QSignalMapper();
 connect(tResumeAutoOperationMapper, SIGNAL(mapped(QString)), this, SLOT(resumeAutoOperation(QString)));
 fButMapper=new QSignalMapper();
 connect(fButMapper, SIGNAL(mapped(QString)), this, SLOT(directionButton(QString)));
 rButMapper=new QSignalMapper();
 connect(rButMapper, SIGNAL(mapped(QString)), this, SLOT(directionButton(QString)));
 connect(speedSlidersMapper, SIGNAL(mapped(QString)), this, SLOT(sliderChanged(QString)));

    //super(false, true);
    _dispatcher = disp;
    initializeAutoTrainsWindow();
}

//    static final ResourceBundle rb = ResourceBundle
//            .getBundle("jmri.jmrit.dispatcher.DispatcherBundle");

// accessor functions
/*public*/ QList<AutoActiveTrain*>* AutoTrainsFrame::getAutoTrainsList() {
    return _autoTrainsList;
}

/*public*/ void AutoTrainsFrame::addAutoActiveTrain(AutoActiveTrain* aat) {
    if (aat != NULL) {
        _autoTrainsList->append(aat);
#if 0
        java.beans.PropertyChangeListener throttleListener = new java.beans.PropertyChangeListener() {
            @Override
            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
                handleThrottleChange(e);
            }
        };
        _throttleListeners->append(throttleListener);

        _throttles->append(NULL); //adds a place holder
        //set up the throttle prior to attaching the listener to the ActiveTrain
        setupThrottle(aat);

        ActiveTrain* at = aat->(getActiveTrain();
        java.beans.PropertyChangeListener listener = NULL;
        at->addPropertyChangeListener(listener = new java.beans.PropertyChangeListener() {
            @Override
            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
                handleActiveTrainChange(e);
            }
        });
        _listeners.add(listener);

        displayAutoTrains();
#endif
    }
}

/*public*/ void AutoTrainsFrame::removeAutoActiveTrain(AutoActiveTrain* aat) {
    for (int i = 0; i < _autoTrainsList->size(); i++) {
        if (_autoTrainsList->at(i) == aat) {
            removeThrottleListener(aat);
            _autoTrainsList->removeAt(i);
            ActiveTrain* at =aat->getActiveTrain();
            at->removePropertyChangeListener(_listeners->at(i));
            _throttles->removeAt(i);
            _listeners->removeAt(i);
            _throttleListeners->removeAt(i);
            displayAutoTrains();
            return;
        }
    }
}
#if 0
/*private*/ void handleActiveTrainChange(java.beans.PropertyChangeEvent e) {
    if (e.getPropertyName().equals("mode")) {
        handleChangeOfMode(e);
    }
    displayAutoTrains();
}

/*private*/ void handleChangeOfMode(java.beans.PropertyChangeEvent e) {
    for (AutoActiveTrain aat : _autoTrainsList) {
        if (aat->(getActiveTrain() == e.getSource()) {
            int newValue = ((Integer) e.getNewValue()).intValue();
            int oldValue = ((Integer) e.getOldValue()).intValue();
            if (newValue == ActiveTrain::DISPATCHED) {
                removeThrottleListener((AutoActiveTrain) e.getSource());
//                } else if (oldValue == ActiveTrain::DISPATCHED && newValue != ActiveTrain::DISPATCHED) {
            } else if (oldValue == ActiveTrain::DISPATCHED) {
                setupThrottle(aat);
            }
        }
    }
}

/*private*/ void setupThrottle(AutoActiveTrain aat) {
    if (aat->(getThrottle() != NULL) {
        int index = _autoTrainsList.indexOf(aat);
        if (_throttles->at(index) == NULL) {
            _throttles.add(index, aat->(getThrottle());
            addThrottleListener(aat);
        }
    }
}

/*private*/ void handleThrottleChange(java.beans.PropertyChangeEvent e) {
    if (!e.getPropertyName().equals("SpeedSetting") && !e.getPropertyName().equals("IsForward")) {
        return; //ignore if not speed or direction
    }
    int index = _throttles.indexOf(e.getSource());
    if (index == -1) {
        log.warn("handleThrottleChange - cannot find throttle index");
        return;
    }
    JLabel status = _throttleStatus->at(index);
    if (!status.isVisible()) {
        return;
    }
    jmri.DccLocoAddress addy = (jmri.DccLocoAddress) _throttles->at(index).getLocoAddress();
    updateStatusLabel(status, jmri.InstanceManager.throttleManagerInstance().getThrottleInfo(addy, "SpeedSetting"), jmri.InstanceManager.throttleManagerInstance().getThrottleInfo(addy, "IsForward"));
}

/*private*/ void updateStatusLabel(JLabel status, Object speed, Object forward) {
    StringBuilder sb = new StringBuilder();
    int spd = Math.round(((Float) speed).floatValue() * 100);
    sb.append("" + spd);
    sb.append("% ");
    if (((Boolean) forward).booleanValue()) {
        sb.append("(fwd)");
    } else {
        sb.append("(rev)");
    }
    //Only repack if the text size has increased.
    if (status.getText().length() < sb.toString().length()) {
        status->setText(sb.toString());
        autoTrainsFrame.pack();
    } else {
        status->setText(sb.toString());
    }
}

/*private*/ void addThrottleListener(AutoActiveTrain aat) {
    int index = _autoTrainsList.indexOf(aat);
    if (index == -1) {
        return;
    }
    if (_throttles->at(index) != NULL) {
        jmri.DccLocoAddress addy = (jmri.DccLocoAddress) _throttles->at(index).getLocoAddress();
        jmri.InstanceManager.throttleManagerInstance().attachListener(addy, _throttleListeners->at(index));
        JLabel status = _throttleStatus->at(index);
        updateStatusLabel(status, jmri.InstanceManager.throttleManagerInstance().getThrottleInfo(addy, "SpeedSetting"), jmri.InstanceManager.throttleManagerInstance().getThrottleInfo(addy, "IsForward"));
    }
}
#endif
/*private*/ void AutoTrainsFrame::removeThrottleListener(AutoActiveTrain* aat) {
    int index = _autoTrainsList->indexOf(aat);
    if (index == -1) {
        return;
    }
    if (_throttles->at(index) != NULL) {
        InstanceManager::throttleManagerInstance()->removeListener((DccLocoAddress*) _throttles->at(index)->getLocoAddress(), _throttleListeners->at(index));
    }
}


/*private*/ void AutoTrainsFrame::initializeAutoTrainsWindow() {
    autoTrainsFrame = this;
    autoTrainsFrame->setTitle(tr("Auto Trains"));
    QMenuBar* menuBar = new QMenuBar();
    setMenuBar(menuBar);
    autoTrainsFrame->addHelpMenu("package.jmri.jmrit.dispatcher.AutoTrains", true);
    contentPane = autoTrainsFrame->getContentPane();
    contentPane->setLayout(contentPaneLayout = new QVBoxLayout); //(contentPane, BoxLayout.Y_AXIS));
    // set up 6 auto trains to size the panel
#if 0
    for (int i = 0; i < 6; i++) {
        newTrainLine();
        if (i == 0) {
            _separators->at(i)->setVisible(false);
        }
    }
    contentPaneLayout->addWidget(new JSeparator());
    contentPaneLayout->addWidget(new JSeparator());
    QWidget* pB = new QWidget();
    pB->setLayout(new FlowLayout());
    JButton stopAllButton = new JButton(tr("StopAll"));
    pB.add(stopAllButton);
    stopAllButton.addActionListener(new ActionListener() {
        @Override
        /*public*/ void actionPerformed(ActionEvent e) {
            stopAllPressed(e);
        }
    });
    stopAllButton->setToolTip(tr("StopAllButtonHint"));
    contentPaneLayout->addWidget(pB);
    autoTrainsFrame.pack();
    placeWindow();
#endif
    displayAutoTrains();
    autoTrainsFrame->setVisible(true);
}

/*private*/ void AutoTrainsFrame::newSeparator() {
    JSeparator* sep = new JSeparator();
    _separators->append(sep);
    contentPaneLayout->addWidget(sep);
}

/*private*/ void AutoTrainsFrame::newTrainLine() {
    int i = _JPanels->size();
    /*final*/ QString s = QString::number(i);
    newSeparator();
    QWidget* px = new QWidget();
    FlowLayout* pxLayout;
    px->setLayout(pxLayout = new FlowLayout());
    _JPanels->append(px);
    QLabel* tLabel = new QLabel("      ");
    pxLayout->addWidget(tLabel);
    pxLayout->addWidget(tLabel);
    _trainLabels->append(tLabel);
    QPushButton* tStop = new QPushButton(tr("Resume"));
    pxLayout->addWidget(tStop);
    _stopButtons->append(tStop);
//    tStop.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            stopResume(s);
//        }
//    });
    tStopMapper->setMapping(tStop,s);
    connect(tStop, SIGNAL(clicked(bool)), tStopMapper, SLOT(map()));
    QPushButton* tManual = new QPushButton(tr("To Manual"));
    pxLayout->addWidget(tManual);
    _manualButtons->append(tManual);
//    tManual.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            manualAuto(s);
//        }
//    });
    tManualMapper->setMapping(tManual, s);
    connect(tManual, SIGNAL(clicked(bool)), tManualMapper, SLOT(map()));
    QPushButton* tResumeAuto = new QPushButton(tr("Resume Auto"));
    pxLayout->addWidget(tResumeAuto);
    _resumeAutoRunningButtons->append(tResumeAuto);
//    tResumeAuto.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            resumeAutoOperation(s);
//        }
//    });
    tResumeAutoOperationMapper->setMapping(tResumeAuto,s);
    connect(tResumeAuto, SIGNAL(clicked(bool)), tResumeAutoOperationMapper, SLOT(map()));
    tResumeAuto->setVisible(false);
    tResumeAuto->setToolTip(tr("Press to stop WORKING and resume automatic RUNNING of this train."));
    QButtonGroup* directionGroup = new QButtonGroup();
    QRadioButton* fBut = new QRadioButton(tr("Forward"));
    pxLayout->addWidget(fBut);
    _forwardButtons->append(fBut);
//    fBut.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            directionButton(s);
//        }
//    });
    fButMapper->setMapping(fBut, s);
    connect(fBut, SIGNAL(mapped(QString)), fButMapper, SLOT(map()));
    directionGroup->addButton(fBut);
    QRadioButton* rBut = new QRadioButton(tr("Reverse"));
    pxLayout->addWidget(rBut);
    _reverseButtons->append(rBut);
//    rBut.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            directionButton(s);
//        }
//    });
    rButMapper->setMapping(rBut, s);
    connect(rBut, SIGNAL(clicked(bool)), rButMapper, SLOT(map()));
    directionGroup->addButton(rBut);
    QSlider* sSlider = new QSlider(/*0, 100, 0*/);
    sSlider->setMinimum(0);
    sSlider->setMaximum(100);
    sSlider->setValue(0);
    pxLayout->addWidget(sSlider);
    _speedSliders->append(sSlider);
//    sSlider.addChangeListener(new ChangeListener() {
//        @Override
//        /*public*/ void stateChanged(ChangeEvent e) {
//            int val = ((JSlider) (e.getSource())).getValue();
//            sliderChanged(s, val);
//        }
//    });
    speedSlidersMapper->setMapping(sSlider,s);
    connect(sSlider, SIGNAL(valueChanged(int)), speedSlidersMapper, SIGNAL(mapped(QString)));
    QLabel* _throttle = new QLabel();
    _throttle->setText("Speed Unknown");
    _throttleStatus->append(_throttle);
    pxLayout->addWidget(_throttle);
    contentPaneLayout->addWidget(px);
}
#if 0
/*private*/ void placeWindow() {
    // get size and placement of Dispatcher Window, screen size, and window size
    Point dispPt = new Point(0, 0);
    Dimension dispDim = new Dimension(0, 0);

    if (_dispatcher.isShowing()) {
        dispPt = _dispatcher.getLocationOnScreen();
        dispDim = _dispatcher.getSize();
    }
    Dimension screenDim = Toolkit.getDefaultToolkit().getScreenSize();
    int screenHeight = screenDim.height - 120;
    int screenWidth = screenDim.width - 20;
    Dimension dim = getSize();
    int width = dim.width;
    int height = dim.height;
    // place AutoTrains window to the right of Dispatcher window, if it will fit.
    int upperLeftX = dispPt.x + dispDim.width;
    int upperLeftY = 0;
    if ((upperLeftX + width) > screenWidth) {
        // won't fit, place it below Dispatcher window, if it will fit.
        upperLeftX = 0;
        upperLeftY = dispPt.y + dispDim.height;
        if ((upperLeftY + height) > screenHeight) {
            // if all else fails, place it at the upper left of the screen, and let the user adjust placement
            upperLeftY = 0;
        }
    }
    setLocation(upperLeftX, upperLeftY);
}

/*public*/ void stopResume(String s) {
    int index = getTrainIndex(s);
    if (index >= 0) {
        AutoActiveTrain aat = _autoTrainsList->at(index);
        if (aat->(getAutoEngineer() != NULL) {
            ActiveTrain at = aat->(getActiveTrain();
            if (at->getStatus() == ActiveTrain::STOPPED) {
                // resume
                aat->(setEngineDirection();
                aat->(getAutoEngineer()->setHalt(false);
                aat->(restoreSavedSpeed();
                at->setStatus(aat->(getSavedStatus());
                if ((at->getStatus() == ActiveTrain::RUNNING)
                        || (at->getStatus() == ActiveTrain::WAITING)) {
                    aat->(setSpeedBySignal();
                }
            } else if (at->getStatus() == ActiveTrain::DONE) {
                // restart
                at->allocateAFresh();
                at->restart();
            } else {
                // stop
                aat->(getAutoEngineer()->setHalt(true);
                aat->(saveSpeed();
                aat->(setSavedStatus(at->getStatus());
                at->setStatus(ActiveTrain::STOPPED);
                if (at->getMode() == ActiveTrain::MANUAL) {
                    _speedSliders->at(index)->setValue(0);
                }
            }
        } else {
            log.error("unexpected NULL autoEngineer");
        }
    }
    displayAutoTrains();
}

/*public*/ void manualAuto(String s) {
    int index = getTrainIndex(s);
    if (index >= 0) {
        AutoActiveTrain aat = _autoTrainsList->at(index);
        ActiveTrain at = aat->(getActiveTrain();
        // if train is AUTOMATIC mode, change it to MANUAL
        if (at->getMode() == ActiveTrain::AUTOMATIC) {
            at->setMode(ActiveTrain::MANUAL);
            if (aat->(getAutoEngineer() != NULL) {
                aat->(saveSpeed();
                aat->(getAutoEngineer()->setHalt(true);
                aat->(setTargetSpeed(0.0f);
                aat->(waitUntilStopped();
                aat->(getAutoEngineer()->setHalt(false);

            }
        } else if (at->getMode() == ActiveTrain::MANUAL) {
            at->setMode(ActiveTrain::AUTOMATIC);
            aat->(restoreSavedSpeed();
            aat->(setForward(!aat->(getRunInReverse());
            if ((at->getStatus() == ActiveTrain::RUNNING)
                    || (at->getStatus() == ActiveTrain::WAITING)) {
                aat->(setSpeedBySignal();
            }
        }
    }
    displayAutoTrains();
}

/*public*/ void resumeAutoOperation(String s) {
    int index = getTrainIndex(s);
    if (index >= 0) {
        AutoActiveTrain aat = _autoTrainsList->at(index);
        aat->(resumeAutomaticRunning();
    }
    displayAutoTrains();
}

/*public*/ void directionButton(String s) {
    int index = getTrainIndex(s);
    if (index >= 0) {
        AutoActiveTrain aat = _autoTrainsList->at(index);
        ActiveTrain at = aat->(getActiveTrain();
        if (at->getMode() == ActiveTrain::MANUAL) {
            aat->(setForward(_forwardButtons->at(index).isSelected());
        } else {
            log.warn("unexpected direction button change on line " + s);
        }
    }
}

/*public*/ void sliderChanged(String s, int value) {
    int index = getTrainIndex(s);
    if (index >= 0) {
        AutoActiveTrain aat = _autoTrainsList->at(index);
        ActiveTrain at = aat->(getActiveTrain();
        if (at->getMode() == ActiveTrain::MANUAL) {
            float speedValue = value;
            speedValue = speedValue * 0.01f;
            aat->(getAutoEngineer()->setSpeedImmediate(speedValue);
        } else {
            log.warn("unexpected slider change on line " + s);
        }
    }
}

/*private*/ int getTrainIndex(String s) {
    int index = -1;
    try {
        index = Integer.parseInt(s);
    } catch (Exception e) {
        log.warn("exception when parsing index from AutoTrains window - " + s);
    }
    if ((index >= 0) && (index < _autoTrainsList.size())) {
        return index;
    }
    log.error("bad train index in auto trains table " + index);
    return (-1);
}

/*public*/ void stopAllPressed(ActionEvent e) {
    for (int i = 0; i < _autoTrainsList.size(); i++) {
        AutoActiveTrain aat = _autoTrainsList->at(i);
        ActiveTrain at = aat->(getActiveTrain();
        if ((at->getStatus() != ActiveTrain::STOPPED) && (aat->(getAutoEngineer() != NULL)) {
            aat->(getAutoEngineer()->setHalt(true);
            aat->(saveSpeed();
            aat->(setSavedStatus(at->getStatus());
            at->setStatus(ActiveTrain::STOPPED);
        }
    }
    displayAutoTrains();
}
#endif
/*protected*/ void AutoTrainsFrame::displayAutoTrains() {
    // set up AutoTrains to display
    while (_autoTrainsList->size() > _JPanels->size()) {
        newTrainLine();
    }
    for (int i = 0; i < _autoTrainsList->size(); i++) {
        AutoActiveTrain* aat = _autoTrainsList->at(i);
        if (aat != NULL) {
            if (i > 0) {
                JSeparator* sep = _separators->at(i);
                sep->setVisible(true);
            }
            QWidget* panel = _JPanels->at(i);
            panel->setVisible(true);
            ActiveTrain* at = aat->getActiveTrain();
            QLabel* tName = _trainLabels->at(i);
            tName->setText(at->getTrainName());
            QPushButton* stopButton = _stopButtons->at(i);
            if (at->getStatus() == ActiveTrain::STOPPED) {
                stopButton->setText(tr("Resume"));
                stopButton->setToolTip(tr("Press to resume running of this stopped train."));
                _resumeAutoRunningButtons->at(i)->setVisible(false);
            } else if (at->getStatus() == ActiveTrain::DONE) {
                stopButton->setText(tr("Restart"));
                stopButton->setToolTip(tr("Press to run this train again."));
                _resumeAutoRunningButtons->at(i)->setVisible(false);
            } else if (at->getStatus() == ActiveTrain::WORKING) {
                stopButton->setVisible(false);
            } else {
                stopButton->setText(tr("StopButton"));
                stopButton->setToolTip(tr("StopButtonHint"));
                stopButton->setVisible(true);
            }
            QPushButton* manualButton = _manualButtons->at(i);
            if (at->getMode() == ActiveTrain::AUTOMATIC) {
                manualButton->setText(tr("To Manual"));
                manualButton->setToolTip(tr("Press to change the mode of this train to Manual operation."));
                manualButton->setVisible(true);
                _resumeAutoRunningButtons->at(i)->setVisible(false);
                _forwardButtons->at(i)->setVisible(false);
                _reverseButtons->at(i)->setVisible(false);
                _speedSliders->at(i)->setVisible(false);
                _throttleStatus->at(i)->setVisible(true);
            } else if ((at->getMode() == ActiveTrain::MANUAL) && ((at->getStatus() == ActiveTrain::WORKING)
                    || (at->getStatus() == ActiveTrain::READY))) {
                manualButton->setVisible(false);
                _resumeAutoRunningButtons->at(i)->setVisible(true);
                _forwardButtons->at(i)->setVisible(false);
                _reverseButtons->at(i)->setVisible(false);
                _speedSliders->at(i)->setVisible(true);
                _throttleStatus->at(i)->setVisible(true);
            } else {
                manualButton->setText(tr("To Auto"));
                manualButton->setToolTip(tr("Press to resume automatic operation of this train currently in Manual mode."));
                _forwardButtons->at(i)->setVisible(true);
                _reverseButtons->at(i)->setVisible(true);
                _speedSliders->at(i)->setVisible(true);
                _throttleStatus->at(i)->setVisible(false);
                _forwardButtons->at(i)->setChecked(aat->getForward());
                _reverseButtons->at(i)->setChecked(!aat->getForward());
                int speedValue = (int) aat->getTargetSpeed() * 100.0;
                _speedSliders->at(i)->setValue(speedValue);
            }
        }
    }
    // clear unused item rows, if needed
    for (int j = _autoTrainsList->size(); j < _JPanels->size(); j++) {
        QWidget* panel = _JPanels->at(j);
        panel->setVisible(false);
        JSeparator* sep = _separators->at(j);
        sep->setVisible(false);
    }
    autoTrainsFrame->pack();
   // autoTrainsFrame->setAutoRequestFocus(false);
    autoTrainsFrame->setVisible(true);
}
