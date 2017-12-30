#include "nxframe.h"
#include "jtextfield.h"
#include <QRadioButton>
#include <qcheckbox.h>
#include <QBoxLayout>
#include "flowlayout.h"
#include <QPushButton>
#include "signalspeedmap.h"
#include "warrantframe.h"
#include <QButtonGroup>
#include <QMenuBar>
#include "QMessageBox"
#include "propertychangeevent.h"
#include "warranttableframe.h"
#include "warranttablemodel.h"
#include <QThread>
#include "blockorder.h"
#include "rosterentry.h"
#include "rosterspeedprofile.h"
#include "opath.h"
#include "oblock.h"
#include "calibrater.h"

//NXFrame::NXFrame(QWidget *parent) :
//  WarrantRoute(parent)
//{
//}
/**
 * Frame for defining and launching an entry/exit warrant. An NX warrant is a
 * warrant that can be defined on the run without a pre-recorded learn mode
 * session using a set script for ramping startup and stop throttle settings.
 * <P>
 * The route can be defined in a form or by mouse clicking on the OBlock
 * IndicatorTrack icons.
 * <P>
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author  Pete Cressman  Copyright (C) 2009, 2010, 2015
 */
///*public*/ class NXFrame extends WarrantRoute {

//    /*private*/ static final long serialVersionUID = -8971792418011219112L;


/*private*/ /*static*/ NXFrame* NXFrame::_instance = NULL;

/*static*/ /*public*/ NXFrame* NXFrame::getInstance()
{
 if (_instance == NULL)
 {
  _instance = new NXFrame();
 }
 if (!_instance->isVisible())
 {
  _instance->setAddress(  NULL);
  _instance->setTrainName(  NULL);
  _instance->_trainName->setText(  NULL);
  _instance->clearRoute();
 }
 return _instance;
}

/*private*/ NXFrame::NXFrame(QWidget *parent) :
  WarrantRoute(parent)
{
    //super();
 _scale = 87.1f;

 _trainName = new JTextField(6);
 _maxSpeedBox = new JTextField(6);
 _minSpeedBox = new JTextField(6);
 _forward = new   QRadioButton();
 _reverse = new   QRadioButton();
 _stageEStop = new   QCheckBox();
 _haltStartBox = new   QCheckBox();
 _calibrateBox = new   QCheckBox();
//     _addTracker = new   QCheckBox();
 _rampInterval = new JTextField(6);
 _runAuto = new   QRadioButton(  tr("Run Auto"));
 _runManual = new   QRadioButton(  tr("Run Manual"));
//  static bool _addTracker = false;
 _maxSpeed = 0.5f;
 _minSpeed = 0.05f;
 _intervalTime = 0.0f;     // milliseconds
 _throttleIncr = 0.0f;
 _controlPanel = NULL;
}
#if 1
/*public*/ void NXFrame::init()
{
    makeMenus();
    QWidget* mainPanel = new QWidget();
    QVBoxLayout* mainPanelLayout = new QVBoxLayout(mainPanel);
    //mainPanel->setLayout(new BorderLayout(10, 10));
    _controlPanel = new QWidget();
    controlPanelLayout = new QVBoxLayout(_controlPanel);
    //_controlPanel.setLayout(new BoxLayout(_controlPanel, BoxLayout.Y_AXIS));
//    controlPanelLayout->addWidget(Box.createVerticalGlue());
    controlPanelLayout->addWidget(makeBlockPanels());
    controlPanelLayout->addWidget(searchDepthPanel(false));

    _autoRunPanel = makeAutoRunPanel(SignalSpeedMap::getMap()->getInterpretation());
//    _maxSpeedBox.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            getBoxData();
//        }
//    });
    connect(_maxSpeedBox, SIGNAL(leaveField()), this, SLOT(getBoxData()));
    _manualPanel = new QWidget();
    QHBoxLayout* manualPanelLayout = new QHBoxLayout(_manualPanel);
    //_manualPanel.setLayout(new BoxLayout(_manualPanel, BoxLayout.X_AXIS));
    manualPanelLayout->addStrut(2 * STRUT_SIZE);
    manualPanelLayout->addWidget(makeTextBoxPanel(false, _trainName, "TrainName", "noTrainName"));
    manualPanelLayout->addStrut(2 * STRUT_SIZE);

    controlPanelLayout->addWidget(_autoRunPanel);
    controlPanelLayout->addWidget(_manualPanel);
    _manualPanel->setVisible(false);
    controlPanelLayout->addStrut(STRUT_SIZE);

    _forward->setChecked(true);
    _stageEStop->setChecked(false);
    _haltStartBox->setChecked(_haltStart);
    _calibrateBox->setChecked(false);
    _rampInterval->setText(QString::number(_intervalTime / 1000));
    QWidget* p = new QWidget();
    FlowLayout* pLayout = new FlowLayout(p);
    //Layout.add(Box.createGlue());
    QPushButton* button = new QPushButton(  tr("Run NX Warrant"));
//    button.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            makeAndRunWarrant();
//        }
//    });
    connect(button, SIGNAL(clicked()), this, SLOT(makeAndRunWarrant()));
    pLayout->addWidget(button);
    //pLayout->addStrut(2*STRUT_SIZE));
    button = new QPushButton(  tr("Cancel"));
//    button.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            closeFrame();
//        }
//    });
    connect(button, SIGNAL(clicked()), this, SLOT(closeFrame()));
    pLayout->addWidget(button);
    //p.add(Box.createGlue());
    controlPanelLayout->addWidget(p);

    controlPanelLayout->addStrut(STRUT_SIZE);
    controlPanelLayout->addWidget(makeSwitchPanel());

    mainPanelLayout->addWidget(_controlPanel);
    //getContentPane().add(mainPanel);
    QWidget* centralWidget = new QWidget;
    setCentralWidget(centralWidget);
    QVBoxLayout* centralWidgetLayout = new QVBoxLayout(centralWidget);
    centralWidgetLayout->addWidget(mainPanel);
//    addWindowListener(new java.awt.event.WindowAdapter() {
//        @Override
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            closeFrame();
//        }
//    });
    addWindowListener(new NXWindowListener(this));
    setAlwaysOnTop(true);
    adjustSize();
}

/*public*/ void NXFrame::updatePanel(int interp) {
    if (_controlPanel==  NULL) {
        return;
    }
    //java.awt.Component[] list = _controlPanel.getComponents();
    QObjectList list = _controlPanel->children();
    int i = 0;
    while (i<list.length() && list[i]!=(_autoRunPanel)) {
        i++;
    }
    controlPanelLayout->removeWidget(_autoRunPanel);
    _autoRunPanel = makeAutoRunPanel(interp);
    controlPanelLayout->insertWidget(i, _autoRunPanel);
}
#endif

/*private*/ QWidget* NXFrame::makeSwitchPanel() {
    QButtonGroup* bg = new QButtonGroup();
    bg->addButton(_runAuto);
    bg->addButton(_runManual);
//    _runAuto.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent event) {
//            enableAuto(true);
//        }
//    });
    connect(_runAuto, SIGNAL(clicked()), this, SLOT(on_runAuto()));
//    _runManual.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent event) {
//            enableAuto(false);
//        }
//    });
    connect(_runManual, SIGNAL(clicked()), this, SLOT(on__runManual_clicked()));
    _runAuto->setChecked(true);
    QWidget* pp = new QWidget();
    //pp.setLayout(new BoxLayout(pp, BoxLayout.X_AXIS));
    QHBoxLayout* ppLayout = new QHBoxLayout(pp);
    ppLayout->addStrut(STRUT_SIZE);
    ppLayout->addWidget(_runAuto);
    ppLayout->addStrut(STRUT_SIZE);
    ppLayout->addWidget(_runManual);
    ppLayout->addStrut(STRUT_SIZE);
    return pp;
}

void NXFrame::on_runAuto()
{
 enableAuto(true);
}

void NXFrame::on_runManual()
{
 enableAuto(false);
}

/*private*/ QWidget* NXFrame::makeAutoRunPanel(int interpretation) {
    QWidget* p1 = new QWidget();
    //p1.setLayout(new BoxLayout(p1, BoxLayout.Y_AXIS));
    QVBoxLayout* p1Layout = new QVBoxLayout(p1);
    float maxSpeed;
    float throttleIncr;
    QString maxSpeedLabel;
    QString throttleIncrLabel;
    float factor;
    switch ( interpretation) {
        case SignalSpeedMap::PERCENT_NORMAL:
        case SignalSpeedMap::PERCENT_THROTTLE:
            maxSpeed = _maxSpeed;
            maxSpeedLabel = "MaxSpeed";
            throttleIncr = _throttleIncr;
            throttleIncrLabel = tr("Ramp Step throttle increment");
            break;
        case SignalSpeedMap::SPEED_MPH:
            factor =  SignalSpeedMap::getMap()->getDefaultThrottleFactor();
            maxSpeed = qRound(_maxSpeed*factor*_scale*2.2369363f*1000)/1000;
            maxSpeedLabel = "MaxMph";
            throttleIncr = qRound(_throttleIncr*factor*_scale*2.2369363f*1000)/1000;
            throttleIncrLabel = tr("Ramp Speed increment Mph");
            break;
        case SignalSpeedMap::SPEED_KMPH:
            factor =  SignalSpeedMap::getMap()->getDefaultThrottleFactor();
            maxSpeed = qRound(_maxSpeed*factor*_scale*3.6f*1000)/1000;
            maxSpeedLabel = "MaxKMph";
            throttleIncr = qRound(_throttleIncr*factor*_scale*3.6f*1000)/1000;
            throttleIncrLabel = tr("Ramp Speed increment KMph");
            break;
        default:
            maxSpeed = _maxSpeed;
            maxSpeedLabel =tr("Max Throttle Setting");
            throttleIncr = _throttleIncr;
            throttleIncrLabel = tr("Ramp Step throttle increment");
    }
    p1Layout->addWidget(WarrantFrame::makeTextBoxPanel(false, _maxSpeedBox, maxSpeedLabel,   NULL));
    p1Layout->addWidget(makeTextBoxPanel(false, _rampInterval, "rampInterval",   NULL));
    p1Layout->addWidget(makeTextBoxPanel(false, _minSpeedBox, throttleIncrLabel, "ToolTipRampIncrement"));
    _maxSpeedBox->setText(QString::number(maxSpeed));
    _minSpeedBox->setText(QString::number(throttleIncr));

    QWidget* p2 = makeTrainPanel();

    QWidget* autoRunPanel = new QWidget();
    //autoRunPanel.setLayout(new BoxLayout(autoRunPanel, BoxLayout.Y_AXIS));
    QVBoxLayout* autoRunPanelLayout = new QVBoxLayout(autoRunPanel);
    QWidget* pp = new QWidget();
   // pp.setLayout(new BoxLayout(pp, BoxLayout.X_AXIS));
    QHBoxLayout* ppLayout = new QHBoxLayout(pp);
    ppLayout->addStrut(STRUT_SIZE);
    ppLayout->addWidget(p1);
    ppLayout->addStrut(STRUT_SIZE);
    ppLayout->addWidget(p2);
    ppLayout->addStrut(STRUT_SIZE);
    autoRunPanelLayout->addWidget(pp);

    QButtonGroup* bg = new QButtonGroup();
    bg->addButton(_forward);
    bg->addButton(_reverse);
    {
     p1 = new QWidget();
     //p1.setLayout(new BoxLayout(p1, BoxLayout.X_AXIS));
     QVBoxLayout* p1Layout = new QVBoxLayout(p1);
     //p1Layout->addWidget(Box.createHorizontalGlue());
     p1Layout->addWidget(makeTextBoxPanel(false, _forward, "forward",   NULL));
    p1Layout->addWidget(makeTextBoxPanel(false, _reverse, "reverse",   NULL));
//     p1Layout->addWidget(Box.createHorizontalGlue());
     pp = new QWidget();
     //pp.setLayout(new BoxLayout(pp, BoxLayout.X_AXIS));
     QHBoxLayout* ppLayout = new QHBoxLayout(pp);
     ppLayout->addStrut(STRUT_SIZE);
     ppLayout->addWidget(p1);
     ppLayout->addStrut(STRUT_SIZE);
     ppLayout->addStrut(2*STRUT_SIZE);
     autoRunPanelLayout->addWidget(pp);
    }
    QWidget* ppp = new QWidget();
    //ppp.setLayout(new BoxLayout(ppp, BoxLayout.X_AXIS));
    QHBoxLayout* pppLayout = new QHBoxLayout(ppp);
    pppLayout->addStrut(STRUT_SIZE);
    pppLayout->addWidget(makeTextBoxPanel(false, _stageEStop, "StageEStop",   NULL));
    pppLayout->addStrut(STRUT_SIZE);
    pppLayout->addWidget(makeTextBoxPanel(false, _haltStartBox, "HaltAtStart",   NULL));
    pppLayout->addStrut(STRUT_SIZE);
    pppLayout->addWidget(makeTextBoxPanel(false, _calibrateBox, "Calibrate", "calibBlockMessage"));
    pppLayout->addStrut(STRUT_SIZE);
    autoRunPanelLayout->addWidget(ppp);
    return autoRunPanel;
}

/*private*/ void NXFrame::makeMenus()
{
 setTitle(  tr("Create eNtry/eXit Warrant"));
 QMenuBar* menuBar = new QMenuBar();
 setMenuBar(menuBar);
 addHelpMenu("package.jmri.jmrit.logix.NXWarrant", true);
}

/*private*/ void NXFrame::enableAuto(bool enable)
{
 if (enable)
 {
  _manualPanel->setVisible(false);
  _autoRunPanel->setVisible(true);
 }
 else
 {
  _manualPanel->setVisible(true);
  _autoRunPanel->setVisible(false);
 }
}

//@Override
/*public*/ void NXFrame::propertyChange(PropertyChangeEvent* e)
{
 QString property = e->getPropertyName();
//        if (log->isDebugEnabled()) log->debug("propertyChange \""+property+
//                                            "\" old= "+e.getOldValue()+" new= "+e.getNewValue()+
//                                            " source= "+e.getSource().getClass().getName());
 if (property==("DnDrop"))
 {
     doAction(e->getSource());
 }
}
#if 1
/**
 * Callback from RouteFinder.findRoute()
 * if all goes well, WarrantTableFrame.runTrain(warrant) will run the warrant
 */
//@Override
/*public*/ void NXFrame::selectedRoute(QList<BlockOrder*> orders)
{
 if (log->isDebugEnabled()) log->debug("NXFrame selectedRoute()");
 QString msg =  NULL;
 Warrant* warrant =   NULL;
 if (_runManual->isChecked())
 {
  runManual();
  return;
 }
 msg = checkLocoAddress();
 if (msg==  NULL)
 {
  QString name = getTrainName();
  if (name==  NULL || name.trimmed().length()==0)
  {
   name = getAddress();
  }
  QString s = QString::number(qrand()).mid(2);
  warrant = new Warrant("IW"+s, "NX("+getAddress()+")");
  warrant->setDccAddress(getTrainId());
  warrant->setTrainName(name);

  msg = getBoxData();
  if (msg==  NULL) {
      msg = makeCommands(warrant);
  }
  if (msg==  NULL) {
      warrant->setBlockOrders(getOrders());
      warrant->setOrders(getOrders());
  }
 }
 if (msg==  NULL && warrant!=  NULL)
 {
  Calibrater* calib =   NULL;
  if (_calibrateBox->isChecked())
  {
   warrant->setViaOrder(getViaBlockOrder());
   calib = new Calibrater(warrant, _forward->isChecked(), /*getLocation()*/pos());
   msg = calib->verifyCalibrate();
   if (msg!=  NULL)
   {
    calib =   NULL;
   }
  }
  warrant->setCalibrater(calib);
  WarrantTableFrame* tableFrame = WarrantTableFrame::getInstance();
  if (msg==  NULL)
  {
   tableFrame->getModel()->addNXWarrant(warrant);   //need to catch propertyChange at start
   if (log->isDebugEnabled()) log->debug("NXWarrant added to table");
   msg = tableFrame->runTrain(warrant);
   tableFrame->scrollTable();
  }
  if (msg!=  NULL)
  {
   if (log->isDebugEnabled()) log->debug("WarrantTableFrame run warrant. msg= "+msg+" Remove warrant "+warrant->getDisplayName());
   tableFrame->getModel()->removeNXWarrant(warrant);
  }
 }
 if (msg==  NULL)
 {
//            if (log->isDebugEnabled()) log->debug("Warrant "+warrant.getDisplayName()+" running.");
  if (_haltStartBox->isChecked())
  {
   _haltStart = true;
//      class Halter implements Runnable {
//          Warrant war;
//          Halter (Warrant w) {
//              war = w;
//          }
//          /*public*/ void run() {
//              int limit = 0;
//              try {
//                  // wait until _engineer is assigned so HALT can take effect
//                  while (!war.controlRunTrain(Warrant.HALT) && limit<3000) {
//                      Thread.sleep(200);
//                      limit += 200;
//                  }
//              } catch (InterruptedException e) {
//                  war.controlRunTrain(Warrant.HALT);
//              }
//          }
//      };
   Halter* h = new Halter(warrant, this);
   //new Thread(h).start();
   QThread* thread = new QThread();
   h->moveToThread(thread);
   connect(thread, SIGNAL(started()), h, SLOT(process()));

  }
  else
  {
   _haltStart = false;
  }
 }
 if (msg!=  NULL)
 {
//  JOptionPane.showMessageDialog(this, msg,
//            tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
  QMessageBox::warning(this, tr("WarningTitle"), msg);
  warrant =   NULL;
 }
 else
 {
  closeFrame();
  if (log->isDebugEnabled()) log->debug("Close Frame.");
 }
}
#endif
/*private*/ void NXFrame::runManual()
{
 QString name = _trainName->text();
 if (name ==   NULL || name.trimmed().length() == 0)
 {
//   JOptionPane.showMessageDialog(this,   tr("noTrainName"),
//                tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
  QMessageBox::warning(this, tr("Warrant Warning"), tr("Enter a name for this train."));
  return;
 }
 QString s = QString::number(qrand()).mid(2);
 Warrant* warrant = new Warrant("IW" + s, "NX(" + name + ")");
 warrant->setTrainName(name);
 warrant->setRoute(0, getOrders());
 WarrantTableFrame* tableFrame = WarrantTableFrame::getInstance();
 tableFrame->getModel()->addNXWarrant(warrant);
 warrant->setRunMode(Warrant::MODE_MANUAL,   NULL,   NULL,   NULL, false);
 tableFrame->scrollTable();
 closeFrame();
}

/*protected*/ void NXFrame::closeFrame()
{
 clearTempWarrant();
 _instance = NULL;
 dispose();
}

/*public*/ void NXFrame::setMaxSpeed(float s) {
    _maxSpeed = s;
}

/*public*/ float NXFrame::getMaxSpeed() {
    return _maxSpeed;
}

/*public*/ void NXFrame::setTimeInterval(float s) {
    _intervalTime = s;
    _rampInterval->setText(QString::number(_intervalTime/1000));
}
/*public*/ void NXFrame::setRampIncrement(float throttleIncr) {
    _throttleIncr = throttleIncr;
}

/*public*/ void NXFrame::setStartHalt(bool s) {
    _haltStart = s;
}

/*public*/ bool NXFrame::getStartHalt() {
    return _haltStart;
}

/*public*/ void NXFrame::setScale(float s) {
    _scale = s;
}
/*public*/ float NXFrame::getScale() {
    return _scale;
}
#if 1
/*private*/ QString NXFrame::getBoxData()
{
 QString text =   NULL;
 float maxSpeed = _maxSpeed;
 float minSpeed = _minSpeed;
 //try {
 bool bok, bOK = true;
 text = _maxSpeedBox->text();
 maxSpeed = text.toFloat(&bok);
 if(!bok) bOK = false;
 text = _minSpeedBox->text();
 minSpeed = text.toFloat(&bok);
 if(!bok) bOK = false;
 if(!bOK)
 {
  return   tr("%1 Parameter must be a decimal number. ").arg(text);
 }
 QString speedErr;
 float factor;
 switch ( SignalSpeedMap::getMap()->getInterpretation())
 {
  case SignalSpeedMap::SPEED_MPH:
       factor =  SignalSpeedMap::getMap()->getDefaultThrottleFactor();
      _maxSpeed = maxSpeed/(factor*_scale*2.2369363f);
      _minSpeed = minSpeed/(factor*_scale*2.2369363f);
      speedErr =   tr("Miles per hour");
      break;
  case SignalSpeedMap::SPEED_KMPH:
      factor =  SignalSpeedMap::getMap()->getDefaultThrottleFactor();
      _maxSpeed = maxSpeed/(factor*_scale*3.6f);
      _minSpeed = minSpeed/(factor*_scale*3.6f);
      speedErr =   tr("Kilometers per hour");
      break;
  default:
      _maxSpeed = maxSpeed;
      _minSpeed = minSpeed;
      speedErr = "";      //   tr("throttlesetting");
 }
 if (_maxSpeed>1.0 || _maxSpeed<0.008)
 {
  return   tr("%1 %2 speed setting cannot be made.").arg(maxSpeed).arg(speedErr);
 }
 if (_minSpeed>0.8 || _minSpeed<0.002|| _minSpeed>=_maxSpeed)
 {
  return   tr("%1 %2 speed setting cannot be made.").arg( minSpeed).arg(speedErr);
 }
 //try {
 text = _rampInterval->text();
 _intervalTime = text.toFloat(&bok)*1000;
 if (_intervalTime>30000 || _intervalTime<300)
 {
     return   tr("%1 is not a valid time interval.").arg( text);
 }
 if(!bok)
 {
 return   tr("%1 is not a valid time interval.").arg(text);
 }
 return   NULL;
}

/*
 * Return length of warrant route in mm.  Assume start and end is in the middle of first
 * and last blocks.  Use a default length for blocks with unspecified length.
 */
 /*private*/ float NXFrame::getTotalLength(float defaultBlockLen)
{
 QList<BlockOrder*>* orders = getOrders();
 BlockOrder* bo = orders->at(0);
 float len = bo->getPath()->getLengthMm();
 if (len<=0) {
     len = defaultBlockLen;
 }
 float totalLen = len/2;      // estimated distance of the route
 for (int i=1; i<orders->size()-1; i++) {
     len =  orders->at(i)->getPath()->getLengthMm();
     if (len<=0) {
         // intermediate blocks should not be zero
         log->warn("Route through block \""+orders->at(i)->getBlock()->getDisplayName()+"\" has length zero. Using "+
                 QString::number(defaultBlockLen)+ " for actual length.");
         len = defaultBlockLen;
     }
     totalLen += len;
 }
 bo = orders->at(orders->size()-1);
 len = bo->getPath()->getLengthMm();
 if (len<=0) {
     len = defaultBlockLen;
 }
 totalLen += len/2;
 if (log->isDebugEnabled()) log->debug("Route length= "+QString::number(totalLen));
 return totalLen;
}
/*private*/ float NXFrame::getRampLength(float totalLen, RosterSpeedProfile* speedProfile) {
    float speed = 0.0f;
    float rampLength = 0.0f;
    int numSteps = 0;
    float factor =  SignalSpeedMap::getMap()->getDefaultThrottleFactor();
    while (speed<=_maxSpeed) {
        float dist;
        if (speedProfile !=   NULL) {
            dist = speedProfile->getSpeed((speed + _minSpeed/2), _forward->isChecked())*_intervalTime/1000;
        } else {
            dist = (speed + _minSpeed/2)*_intervalTime*factor;
        }
        if (rampLength + dist <= totalLen/2) {
            if ((speed + _minSpeed)>_maxSpeed) {
                dist = dist*(_maxSpeed-speed)/_minSpeed;
            }
            rampLength += dist;
            speed += _minSpeed;
            numSteps++;
        } else {
            // cannot get to _maxSpeed and have enough length to decelerate
            _maxSpeed = speed;      // modify
            break;
        }
    }
    // add the smidge of distance needed to reach _maxSpeed
//        rampLength += (_maxSpeed - speed)*_intervalTime*scaleFactor;
    if (log->isDebugEnabled()) log->debug(numSteps+" speed steps of delta= "+
            QString::number(_minSpeed)+" for rampLength = "+QString::number(rampLength)+" to reach speed "+ QString::number(_maxSpeed));
    return rampLength;
}

/*private*/ QString NXFrame::makeCommands(Warrant* w) {

    int nextIdx = 0;        // block index - increment after getting a block order
    QList<BlockOrder*>* orders = getOrders();
    BlockOrder* bo = orders->at(nextIdx++);
    QString blockName = bo->getBlock()->getDisplayName();

    w->addThrottleCommand(new ThrottleSetting(0, "F0", "true", blockName));
    if (_forward->isChecked()) {
        w->addThrottleCommand(new ThrottleSetting(1000, "Forward", "true", blockName));
        w->addThrottleCommand(new ThrottleSetting(1000, "F2", "true", blockName));
        w->addThrottleCommand(new ThrottleSetting(2500, "F2", "false", blockName));
        w->addThrottleCommand(new ThrottleSetting(1000, "F2", "true", blockName));
        w->addThrottleCommand(new ThrottleSetting(2500, "F2", "false", blockName));
    } else {
        w->addThrottleCommand(new ThrottleSetting(1000, "Forward", "false", blockName));
        w->addThrottleCommand(new ThrottleSetting(2000, "F3", "true", blockName));
        w->addThrottleCommand(new ThrottleSetting(500, "F3", "false", blockName));
        w->addThrottleCommand(new ThrottleSetting(500, "F3", "true", blockName));
        w->addThrottleCommand(new ThrottleSetting(500, "F1", "true", blockName));
    }

    // estimate for blocks of zero length - an estimate of ramp length
    bool isForward = _forward->isChecked();
    float scaleFactor =  SignalSpeedMap::getMap()->getDefaultThrottleFactor();
    RosterEntry* ent = getTrain();
    RosterSpeedProfile* speedProfile =   NULL;
    if (ent!=  NULL) {
        speedProfile = ent->getSpeedProfile();
        if (speedProfile!=  NULL) {
            float s = speedProfile->getSpeed(_maxSpeed, isForward);
            if (log->isDebugEnabled()) log->debug("SpeedProfile _maxSpeed setting= "+QString::number(_maxSpeed)+" speed= "+QString::number(s)+"mps");
            if (s<=0.0f) {
                speedProfile =   NULL;
            } else {
                scaleFactor = s/(_maxSpeed*1000);
            }
        }
    }
    if (log->isDebugEnabled()) log->debug("scaleFactor= "+QString::number(scaleFactor)+" from "+(speedProfile!=  NULL?"SpeedProfile":"Default"));

    float defaultBlockLen = 6*_maxSpeed*_intervalTime/scaleFactor;      // just a wild guess
    float totalLen = getTotalLength(defaultBlockLen);
    float rampLength = getRampLength(totalLen, speedProfile);

    float blockLen = bo->getPath()->getLengthMm();    // length of path in current block
    if (blockLen<=0) {
        blockLen = defaultBlockLen;
    }
    blockLen /=2;

    // start train
    float speedTime = 500;      // ms time to complete speed step from last block
    float noopTime = 0;         // ms time for entry into next block
    float curSpeed = 0;
    // each speed step will last for _intervalTime ms
    float curDistance = 0;          // distance traveled in current block
    float remRamp = rampLength;
    if (log->isDebugEnabled()) log->debug("Start Ramp Up in block \""+blockName+ "\" in "
            +(int)speedTime+"ms, remRamp= "+remRamp+", blockLen= "+blockLen);

    while (remRamp > 0.0f) {       // ramp up loop

        if (speedProfile !=   NULL) {
            curDistance = speedProfile->getSpeed(curSpeed, isForward)*speedTime/1000;
        } else {
            curDistance = curSpeed*speedTime*scaleFactor;
        }
        while (curDistance < blockLen && remRamp > 0.0f) {
            float dist;
            if (speedProfile !=   NULL) {
                dist = speedProfile->getSpeed((curSpeed + _minSpeed/2), isForward)*_intervalTime/1000;
            } else {
                dist = (curSpeed + _minSpeed/2)*_intervalTime*scaleFactor;
            }
            if (curDistance + dist <= blockLen && remRamp > 0.0f) {
                curDistance += dist;
                float remSpeed = _maxSpeed - curSpeed;
                if (0<remSpeed && remSpeed < _minSpeed) {
                    curSpeed += remSpeed;
                    remRamp = -1;   // insure we break out of loop
                } else {
                    curSpeed += _minSpeed;
                }
                remRamp -= dist;
                w->addThrottleCommand(new ThrottleSetting((int)speedTime, "Speed", QString::number(curSpeed), blockName));
                if (log->isDebugEnabled()) log->debug("Ramp Up in block \""+blockName+ "\" to speed "+curSpeed+" in "
                       +(int)speedTime+"ms to reach curDistance= "+curDistance+", remRamp= "+remRamp);
                speedTime = _intervalTime;
            } else {
                break;
            }
        }

        // Possible case where curDistance can exceed the length of a very short block that was just entered.
        // Move to next block and adjust the distance times into that block
        if (speedProfile !=   NULL) {
            if (curDistance>=blockLen) {
                noopTime = qRound(1000*speedProfile->getDurationOfTravelInSeconds(isForward, curSpeed, qRound(blockLen)));  // time to next block
                speedTime = qRound(1000*speedProfile->getDurationOfTravelInSeconds(isForward, curSpeed, qRound(curDistance-blockLen)));
            } else {
                noopTime = qRound(1000*speedProfile->getDurationOfTravelInSeconds(isForward, curSpeed, qRound(blockLen-curDistance)));
                speedTime = _intervalTime - noopTime;   // time to next speed change
            }
        } else {
            if (curDistance>=blockLen) {
                noopTime = (blockLen)/(curSpeed*scaleFactor);  // time to next block
                speedTime = (curDistance-blockLen)/(curSpeed*scaleFactor);
            } else {
                noopTime = (blockLen-curDistance)/(curSpeed*scaleFactor);  // time to next block
                speedTime = _intervalTime - noopTime;   // time to next speed change
            }
        }

        // break out here if deceleration is to be started in this block
        if (totalLen - blockLen <= rampLength) {
            break;
        }
        if (nextIdx < orders->size()) {    // not the last block
            totalLen -= blockLen;
            if (log->isDebugEnabled()) log->debug("Leave RampUp block \""+blockName+"\" noopTime= "+noopTime+
                    ", in distance="+curSpeed*noopTime*scaleFactor+", blockLen= "+blockLen+
                    ", remRamp= "+remRamp);
            bo = orders->at(nextIdx++);
            blockName = bo->getBlock()->getDisplayName();
            blockLen = bo->getPath()->getLengthMm();
            if (blockLen<=0)  {
                blockLen = defaultBlockLen;
            }
            w->addThrottleCommand(new ThrottleSetting((int)noopTime, "NoOp", "Enter Block", blockName));
            if (log->isDebugEnabled()) log->debug("Enter block \""+blockName+"\" noopTime= "+
                    noopTime+", blockLen= "+blockLen);
        }
    }
    if (log->isDebugEnabled()) log->debug("Ramp Up done at block \""+blockName+"\" curSpeed=" +
            QString::number(curSpeed)+", blockLen= "+QString::number(blockLen)+" totalLen= "+QString::number(totalLen)+", rampLength= "+
            QString::number(rampLength)+", remRamp= "+QString::number(remRamp));

    // run through mid route at max speed
    while (nextIdx < orders->size()) {
        if (totalLen-blockLen <= rampLength) {
            // Start ramp down in current block
            break;
        }
        totalLen -= blockLen;
        // constant speed, get time to next block
        if (speedProfile !=   NULL) {
            noopTime = qRound(1000*speedProfile->getDurationOfTravelInSeconds(isForward, curSpeed, qRound(blockLen-curDistance)));
        } else {
            noopTime = (blockLen-curDistance)/(curSpeed*scaleFactor);
        }
        if (log->isDebugEnabled()) log->debug("Leave MidRoute block \""+blockName+"\" noopTime= "+noopTime+
                ", curDistance="+curDistance+", blockLen= "+blockLen+", totalLen= "+totalLen);
        bo = orders->at(nextIdx++);
        blockName = bo->getBlock()->getDisplayName();
        blockLen = bo->getPath()->getLengthMm();
        if (nextIdx == orders->size()) {
            blockLen /= 2;
        } else if (blockLen<=0) {
            blockLen = defaultBlockLen;
        }
        w->addThrottleCommand(new ThrottleSetting((int)noopTime, "NoOp", "Enter Block", blockName));
        if (log->isDebugEnabled()) log->debug("Enter block \""+blockName+"\" noopTime= "+noopTime);
        curDistance = 0;
    }

    // Ramp down.  use negative delta
    remRamp = rampLength;
    speedTime = (totalLen-rampLength)/(curSpeed*scaleFactor);
    curDistance = totalLen - rampLength;
    if (log->isDebugEnabled()) log->debug("Begin Ramp Down at block \""+blockName+"\" curDistance= "
            +curDistance+" SpeedTime= "+(int)speedTime+"ms, blockLen= "+blockLen+", totalLen= "+totalLen+
            ", rampLength= "+rampLength+" curSpeed= "+curSpeed);

    while (curSpeed >= _minSpeed) {
        if (nextIdx == orders->size()) { // at last block
            if (_stageEStop->isChecked()) {
                w->addThrottleCommand(new ThrottleSetting(0, "Speed", "-0.5", blockName));
                _intervalTime = 0;
                break;
            }
        }

        while (curDistance < blockLen && curSpeed >= _minSpeed) {
            float dist;
            if (speedProfile !=   NULL) {
                dist = speedProfile->getSpeed((curSpeed - _minSpeed/2), isForward)*_intervalTime/1000;
            } else {
                dist = (curSpeed - _minSpeed/2)*_intervalTime*scaleFactor;
            }
            if (curDistance + dist <= blockLen) {
                curDistance += dist;
                curSpeed -= _minSpeed;
                remRamp -= dist;
                w->addThrottleCommand(new ThrottleSetting((int)speedTime, "Speed", QString::number(curSpeed), blockName));
                if (log->isDebugEnabled()) log->debug("Ramp Down in block \""+blockName+"\" to speed "+
                        curSpeed+" in "+(int)speedTime+"ms to reach curDistance= "+curDistance+" where blockLen= "+blockLen+", remRamp= "+remRamp);
                speedTime = _intervalTime;
            } else {
                break;
            }
        }

        if (nextIdx < orders->size()) {
            if (speedProfile !=   NULL) {
                noopTime = qRound(1000*speedProfile->getDurationOfTravelInSeconds(isForward, curSpeed, qRound(blockLen-curDistance)));
            } else {
                noopTime = (blockLen-curDistance)/(curSpeed*scaleFactor);
            }
            if (noopTime<0 || _intervalTime<noopTime) {
                log->error("Ramp Down NoOp time invalid! noopTime= "+QString::number(noopTime));
                noopTime = _intervalTime/2;
            }
            speedTime = _intervalTime - noopTime;
            totalLen -= blockLen;
            if (log->isDebugEnabled()) log->debug("Leave RampDown block \""+blockName+"\" noopTime= "+noopTime+
                    ", in distance="+curSpeed*noopTime*scaleFactor+", blockLen= "+blockLen+
                    ", totalLen= "+totalLen+", remRamp= "+remRamp);
            bo = orders->at(nextIdx++);
            blockName = bo->getBlock()->getDisplayName();
            blockLen = bo->getPath()->getLengthMm();
            if (blockLen<=0)  {
                blockLen = defaultBlockLen;
            }
            w->addThrottleCommand(new ThrottleSetting((int)noopTime, "NoOp", "Enter Block", blockName));
            if (log->isDebugEnabled()) log->debug("Enter block \""+blockName+"\" noopTime= "+noopTime);
            if (speedProfile !=   NULL) {
                curDistance = speedProfile->getSpeed(curSpeed, isForward)*speedTime/1000;
            } else {
                curDistance = curSpeed*speedTime*scaleFactor;
            }
        } else {
            if (blockLen==0) {
                speedTime = 0;
            }
            break;
        }
    }
    if (log->isDebugEnabled()) {
        curDistance += curSpeed*speedTime*scaleFactor;
        remRamp -=  curSpeed*speedTime*scaleFactor;
        log->debug("Ramp down last speed change in block \""+blockName+"\" to speed "+curSpeed+
                " after "+(int)_intervalTime+"ms. at curDistance= "+curDistance+", remRamp= "+remRamp);
    }
    w->addThrottleCommand(new ThrottleSetting((int)speedTime, "Speed", "0.0", blockName));
    w->addThrottleCommand(new ThrottleSetting(500, "F1", "false", blockName));
    w->addThrottleCommand(new ThrottleSetting(1000, "F2", "true", blockName));
    w->addThrottleCommand(new ThrottleSetting(3000, "F2", "false", blockName));
    w->addThrottleCommand(new ThrottleSetting(1000, "F0", "false", blockName));
/*      if (_addTracker.isSelected()) {
        WarrantTableFrame._defaultAddTracker = true;
        w.addThrottleCommand(new ThrottleSetting(10, "START TRACKER", "", blockName));
    } else {
        WarrantTableFrame._defaultAddTracker = false;
    }*/
    return   NULL;
}
#endif
/*private*/ bool NXFrame::makeAndRunWarrant()
{
 QString msg = checkLocoAddress();
 if (msg ==   NULL) {
     if (log->isDebugEnabled()) log->debug("NXWarrant makeAndRunWarrant calls findRoute()");
     msg = findRoute();
 }
 if (msg !=   NULL) {
//     JOptionPane.showMessageDialog(this, msg,
//               tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
  QMessageBox::warning(this, tr("Warning"), msg);
     return false;
 }
 return true;
}

