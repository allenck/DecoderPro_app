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
#include "box.h"
#include "warrantpreferences.h"
#include "speedutil.h"
#include "instancemanager.h"
#include "joptionpane.h"

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

/*public*/ /*static*/ float NXFrame::INCRE_RATE = 1.08f;  // multiplier to increase throttle increments

/*private*/ /*static*/ NXFrame* NXFrame::_instance = nullptr;

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
 _originDist = new JTextField(6);
 _destDist = new JTextField(6);
 _destUnits;_forward = new   QRadioButton();
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
 _maxThrottle = 0.75f;
 _maxThrottleBox = new JTextField(6);
 _noRamp = new QCheckBox();
 _shareRouteBox = new QCheckBox();
 _routePanel = new QWidget();
  __trainHolder = new QWidget();

}

/*private*/ WarrantPreferences* NXFrame::updatePreferences()
{
    WarrantPreferences* preferences = WarrantPreferences::getDefault();
    setScale(preferences->getLayoutScale());
    setTimeInterval(preferences->getTimeIncrement());
    setThrottleIncrement(preferences->getThrottleIncrement());
    if (log->isDebugEnabled()) log->debug(tr("Ramp parameters: deltaTime=%1 deltaThrottle=%2").arg(_intervalTime).arg(_throttleIncr));
    return preferences;
}

/*public*/ void NXFrame::init()
{
 if (log->isDebugEnabled()) log->debug("newInstance");
         updatePreferences();
 makeMenus();

 _routePanel = new QWidget();
 //_routePanel.setLayout(new BoxLayout(_routePanel, BoxLayout.PAGE_AXIS));
 QVBoxLayout* _routePanelLayout = new QVBoxLayout(_routePanel);
 _routePanelLayout->addWidget(Box::createVerticalGlue());
 _routePanelLayout->addWidget(makeBlockPanels(true));

 _forward->setChecked(true);
 _stageEStop->setChecked(false);
 _haltStartBox->setChecked(false);
 _runAuto->setChecked(true);

 _autoRunPanel = makeAutoRunPanel();
 _switchPanel = makeSwitchPanel();

 QWidget*  mainPanel = new QWidget();
 //mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.PAGE_AXIS));
 QVBoxLayout* mainPanelLayout = new QVBoxLayout(mainPanel);
 mainPanelLayout->addWidget(_routePanel);
 getContentPane()->layout()->addWidget(mainPanel);

#if 0 // TODO:
 addWindowListener(new WindowAdapter() {
     @Override
     public void windowClosing(java.awt.event.WindowEvent e) {
         closeFrame();
     }
 });
#endif
 setAlwaysOnTop(true);
 setVisible(true);
 pack();
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
    _autoRunPanel = makeAutoRunPanel();
    controlPanelLayout->insertWidget(i, _autoRunPanel);
}

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

/*private*/ QPushButton* NXFrame::getButton(QString text)
{
 QPushButton* button = new QPushButton();
 QFont f = QFont("sans_serif",12);
 button->setFont(f); //new Font(Font.SANS_SERIF, Font.PLAIN, 12));
 button->setText(text);
 button->setChecked(true);
 int bWidth =  JTextField(2).getPreferredSize().width();
 int bHeight =  JTextField(2).getPreferredSize().height();
 button->setMaximumSize(QSize(bWidth, bHeight));
 return button;
}

void NXFrame::on_runAuto()
{
 enableAuto(true);
}

void NXFrame::on_runManual()
{
 enableAuto(false);
}

/*private*/ QWidget* NXFrame::makeAutoRunPanel()
{
 QWidget* p1 = new QWidget();
 //p1.setLayout(new BoxLayout(p1, BoxLayout.Y_AXIS));
 QVBoxLayout* p1Layout = new QVBoxLayout(p1);
 _speedUnits = getButton("Mph");
// _maxThrottleBox.addActionListener((ActionEvent evt)-> {
//     maxThrottleEventAction();
// });
 connect(_maxThrottleBox, SIGNAL(leaveField()), this, SLOT(maxThrottleEventAction()));

// _maxSpeedBox.addActionListener((ActionEvent evt)-> {
//     boolean isForward = _forward.isSelected();
//     RosterSpeedProfile profile = _speedUtil.getSpeedProfile();
//     if (profile != null) {
//         NumberFormat formatter = NumberFormat.getNumberInstance();
//         float num = 0;
//         try {
//             num =  formatter.parse(_maxSpeedBox.getText()).floatValue();
//         } catch (java.text.ParseException pe) {
//             _maxSpeedBox.setText("");
//             return;
//         }
//         if (_speedUnits.getText().equals("Mph")) {
//             num = num * 447.04f / _scale;
//         } else {
//             num = num * 277.7778f / _scale;
//         }
//         float throttle = profile.getThrottleSetting(num, isForward);
//         if (throttle > 0.0f) {
//             _maxThrottleBox.setText(formatter.format(throttle));
//             return;
//         }
//     }
//     _maxSpeedBox.setText(Bundle.getMessage("NoData"));
// });
 connect(_maxSpeedBox, SIGNAL(leaveField()), this, SLOT(onMaxSpeed()));

// _speedUnits.addActionListener((ActionEvent evt)-> {
//     NumberFormat formatter = NumberFormat.getNumberInstance();
//     float num = 0;
//     try {
//         num =  formatter.parse(_maxSpeedBox.getText()).floatValue();
//     } catch (java.text.ParseException pe) {
//         return;
//     }
//     if (_speedUnits.getText().equals("Mph")) {
//         _speedUnits.setText("Kmph");
//         num = Math.round(num * 160.9344f);
//         _maxSpeedBox.setText(formatter.format(num / 100));
//     } else {
//         num = Math.round(num * 62.137119f);
//         _speedUnits.setText("Mph");
//         _maxSpeedBox.setText(formatter.format(num / 100));
//     }
// });
 connect(_speedUnits, SIGNAL(clicked(bool)), this, SLOT(onSpeedUnits()));

 p1Layout->addWidget(makeTextBoxPanel(false, _maxThrottleBox, tr("Max Throttle Setting"), ""));
 p1Layout->addWidget(makeTextAndButtonPanel(_maxSpeedBox, _speedUnits, tr("Scale Speed"), tr("If speed Profile data exists for the selected direction, this will be the maximum scale speed.")));

 _originUnits = getButton("In");
 _destUnits = getButton("In");

// _originUnits.addActionListener((ActionEvent evt)-> {
//     NumberFormat formatter = NumberFormat.getNumberInstance();
//     float num = 0;
//     try {
//         num =  formatter.parse(_originDist.getText()).floatValue();
//     } catch (java.text.ParseException pe) {
//         // errors reported later
//     }
//     if (_originUnits.getText().equals("In")) {
//         _originUnits.setText("Cm");
//         num = Math.round(num * 254f);
//         _originDist.setText(formatter.format(num / 100));
//     } else {
//         num = Math.round(num * 100f / 2.54f);
//         _originUnits.setText("In");
//         _originDist.setText(formatter.format(num / 100));
//     }
// });
 connect(_originUnits, SIGNAL(clicked(bool)), this, SLOT(onOriginUnits()));

 //_destUnits.setActionCommand("In");
 _destUnits->setText(tr("In"));
// _destUnits.addActionListener((ActionEvent evt)-> {
//     NumberFormat formatter = NumberFormat.getNumberInstance();
//     float num = 0;
//     try {
//         num =  formatter.parse(_destDist.getText()).floatValue();
//     } catch (java.text.ParseException pe) {
//         // errors reported later
//     }
//     if (_destUnits.getText().equals("In")) {
//         _destUnits.setText("Cm");
//         _destDist.setText(formatter.format(num * 2.54f));
//     } else {
//         _destUnits.setText("In");
//         _destDist.setText(formatter.format(num / 2.54f));
//     }
// });
connect(_destUnits, SIGNAL(clicked(bool)), this, SLOT(onDestUnits()));

 p1Layout->addWidget(makeTextAndButtonPanel(_originDist, _originUnits, "startDistance", "ToolTipStartDistance"));
 p1Layout->addWidget(makeTextAndButtonPanel(_destDist, _destUnits, "stopDistance", tr("Distance from where the train enters the entry portal of the destination block to its stopping point.")));

 //__trainHolder.setLayout(new BoxLayout(__trainHolder, BoxLayout.PAGE_AXIS));
   QVBoxLayout* __trainHolderLayout = new QVBoxLayout(__trainHolder);
 _trainPanel = makeTrainIdPanel(nullptr);
 __trainHolderLayout->addWidget(_trainPanel);

    QWidget* autoRunPanel = new QWidget();
    //autoRunPanel.setLayout(new BoxLayout(autoRunPanel, BoxLayout.Y_AXIS));
    QVBoxLayout* autoRunPanelLayout = new QVBoxLayout(autoRunPanel);
    QWidget* pp = new QWidget();
   // pp.setLayout(new BoxLayout(pp, BoxLayout.X_AXIS));
    QHBoxLayout* ppLayout = new QHBoxLayout(pp);
    ppLayout->addStrut(STRUT_SIZE);
    ppLayout->addWidget(p1);
    ppLayout->addWidget(Box::createHorizontalGlue());
    ppLayout->addWidget(__trainHolder);
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
    p1Layout->addWidget(Box::createHorizontalGlue());

    QWidget* p2 = new QWidget();
    //p2.setLayout(new BoxLayout(p2, BoxLayout.LINE_AXIS));
    QHBoxLayout* p2Layout = new QHBoxLayout(p2);
    p2Layout->addWidget(Box::createHorizontalGlue());
    p2Layout->addWidget(makeTextBoxPanel(_noRamp, tr("Don't Ramp Speed Changes"), "Warrant makes immediate speed changes when entering the approach block"));

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

void NXFrame::onMaxSpeed()
{
 bool isForward = _forward->isChecked();
 RosterSpeedProfile* profile = _speedUtil->getSpeedProfile();
 if (profile != nullptr) {
     //NumberFormat formatter = NumberFormat.getNumberInstance();
     float num = 0;
     try {
         num =  _maxSpeedBox->text().toFloat();
     } catch (ParseException pe) {
         _maxSpeedBox->setText("");
         return;
     }
     if (_speedUnits->text()==("Mph")) {
         num = num * 447.04f / _scale;
     } else {
         num = num * 277.7778f / _scale;
     }
     float throttle = profile->getThrottleSetting(num, isForward);
     if (throttle > 0.0f) {
         _maxThrottleBox->setText(QString::number(throttle, 'g', 2));
         return;
     }
 }
 _maxSpeedBox->setText(tr("No data"));
}

void NXFrame::onSpeedUnits()
{
 //NumberFormat formatter = NumberFormat.getNumberInstance();
 float num = 0;
 try {
     num =  _maxSpeedBox->text().toFloat();
 } catch (ParseException pe) {
     return;
 }
 if (_speedUnits->text() == ("Mph")) {
     _speedUnits->setText("Kmph");
     num = qRound(num * 160.9344f);
     _maxSpeedBox->setText(QString::number(num / 100,'g',2));
 } else {
     num = qRound(num * 62.137119f);
     _speedUnits->setText("Mph");
     _maxSpeedBox->setText(QString::number(num / 100, 'g',2));
 }

}

void NXFrame::onOriginUnits()
{
 //NumberFormat formatter = NumberFormat.getNumberInstance();
 float num = 0;
 try {
     num =  _originDist->text().toFloat();
 } catch (ParseException pe) {
     // errors reported later
 }
 if (_originUnits->text() == ("In")) {
     _originUnits->setText("Cm");
     num = qRound(num * 254.0);
     _originDist->setText(QString::number(num / 100, 'g', 2));
 } else {
     num = qRound(num * 100.0 / 2.54);
     _originUnits->setText("In");
     _originDist->setText(QString::number(num / 100, 'g',2));
 }

}

void NXFrame::onDestUnits()
{
 //NumberFormat formatter = NumberFormat.getNumberInstance();
 float num = 0;
 try {
     num =  _destDist->text().toFloat();
 } catch (ParseException pe) {
     // errors reported later
 }
 if (_destUnits->text()==("In")) {
     _destUnits->setText("Cm");
     _destDist->setText(QString::number(num * 2.54,'g', 2));
 } else {
     _destUnits->setText("In");
     _destDist->setText(QString::number(num / 2.54,'g',2));
 }
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

/**
 * Callback from RouteFinder.findRoute()
 * if all goes well, WarrantTableFrame.runTrain(warrant) will run the warrant
 */
//@Override
/*public*/ void NXFrame::selectedRoute(QList<BlockOrder*> /*orders*/)
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

/**
 * for the convenience of testing
 * @param increment the throttle increment
 */
/*protected*/ void NXFrame::setThrottleIncrement(float increment) {
    this->_throttleIncr = increment;
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
 switch ( static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"))->getInterpretation())
 {
  case SignalSpeedMap::SPEED_MPH:
       factor =  static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"))->getDefaultThrottleFactor();
      _maxSpeed = maxSpeed/(factor*_scale*2.2369363f);
      _minSpeed = minSpeed/(factor*_scale*2.2369363f);
      speedErr =   tr("Miles per hour");
      break;
  case SignalSpeedMap::SPEED_KMPH:
      factor =  static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"))->getDefaultThrottleFactor();
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

/*private*/ float NXFrame::getPathLength(BlockOrder* bo) {
    float len = bo->getPath()->getLengthMm();
    if (len <= 0) {
        QString sLen = JOptionPane::showInputDialog(this,
                tr("Path %1 in block %2 has length zero.\n Cannot run NXWarrants or ramp speeds through blocks with zero length.").arg(bo->getPathName()).arg(bo->getBlock()->getDisplayName())
                + tr("\nPlease enter a length in millimeters for path %1 in block %2.").arg(bo->getPathName()).arg(bo->getBlock()->getDisplayName()),
                tr("Warning"), JOptionPane::WARNING_MESSAGE);
        try {
            //len = NumberFormat.getNumberInstance().parse(sLen).floatValue();
         bool bok;
         len = sLen.toFloat(&bok);
         if(!bok) throw ParseException("parse error on block length");
        } catch (ParseException  pe) {
            len = -1.0f;
        } catch (NullPointerException  npe) {
            len = -1.0f;
        }
    }
   return len;
}

/*
 * Return length of warrant route in mm.  Assume start and end is in the middle of first
 * and last blocks.  Use a default length for blocks with unspecified length.
 */
/*private*/ QString NXFrame::getTotalLength() {
    _totalLen = 0.0f;
    QList<BlockOrder*>* orders = getOrders();
    _totalLen = _startDist;
    for (int i = 1; i < orders->size() - 1; i++) {
        BlockOrder* bo = orders->at(i);
        float len = getPathLength(bo);
        if (len <= 0) {
            return tr("Path %1 in block %2 has length zero.\nCannot run NXWarrants or ramp speeds through blocks with zero length.").arg(bo->getPathName()).arg(bo->getBlock()->getDisplayName());
         }
        _totalLen += len;
    }
    _totalLen += _stopDist;
    return nullptr;
}
/*private*/ float NXFrame::getUpRampLength() {
    float speed = 0.0f;     // throttle setting
    float rampLength = 0.0f;
    int numSteps = 0;
    float incre = _throttleIncr;
    float momentumTime = _speedUtil->getMomentumTime(incre, true);
    while (speed < _maxThrottle) {
        float dist = _speedUtil->getTrackSpeed(speed + incre/2,  _forward->isChecked()) * momentumTime;
        if (_intervalTime > momentumTime) {
            dist += _speedUtil->getTrackSpeed(speed + incre, _forward->isChecked()) * (_intervalTime - momentumTime);
        }
        if (rampLength + dist <= _totalLen / 2) {
            if ((speed + incre) > _maxThrottle) {
                dist = dist * (_maxThrottle - speed) / incre;
                speed = _maxThrottle;
            } else {
                speed += incre;
            }
            rampLength += dist;
            numSteps++;
            if (log->isDebugEnabled()) {
                log->debug(tr("step %1 incr= %2, dist= %3 upRampLength= %4 ").arg(numSteps).arg(incre).arg(dist).arg(rampLength));
            }
            incre *= INCRE_RATE;
        } else {
            if (log->isDebugEnabled()) {
                log->debug(tr("cannot reach max Speed and have enough length to decelerate. _maxThrottle set to %1").arg(
                        _maxThrottle));
                _maxThrottle = speed;      // modify
            }
            break;
        }
    }
    if (log->isDebugEnabled()) {
        log->debug(tr("%1 speed steps of delta= %2 for upRampLength= %3 to maxThrottle= %4").arg(
                numSteps).arg(_throttleIncr).arg(rampLength).arg(_maxThrottle));
    }
    return rampLength;
}

/*private*/ float NXFrame::getDownRampLength() {

    float speed = 0;     // throttle setting
    float rampLength = 0.0f;
    int numSteps = 0;
    float incre = _throttleIncr;
    bool isForward = _forward->isChecked();
    float momentumTime = _speedUtil->getMomentumTime(incre, false);
    while (speed + incre <= _maxThrottle) {
        speed += incre;
        incre *= INCRE_RATE;
    }
    speed = _maxThrottle;     // throttle setting
    float maxIncre = incre;
    while (speed > 0.0f) {
        float dist = _speedUtil->getTrackSpeed(speed - incre/2, isForward) * momentumTime;
        if (_intervalTime > momentumTime) {
            dist += _speedUtil->getTrackSpeed(speed - incre, isForward) * (_intervalTime - momentumTime);
        }
       if (dist <= 0.0f) {
           break;
       }
       if (rampLength + dist >= _totalLen / 2) {
           // remove first step's distance
           float d = _speedUtil->getTrackSpeed(_maxThrottle, isForward) * momentumTime;
                   if (_intervalTime > momentumTime) {
                       d += _speedUtil->getTrackSpeed(_maxThrottle - incre, isForward) * (_intervalTime - momentumTime);
                   }
           if (rampLength >= d) {
               rampLength -= d;
           } else {
               rampLength = 0.0f;
           }
          _maxThrottle -= maxIncre;      // modify
          maxIncre /= INCRE_RATE;
          numSteps--;
          if (log->isDebugEnabled()) {
              log->debug(tr("cannot reach max Speed and have enough length to decelerate. _maxThrottle set to %1").arg(
                      _maxThrottle));
          }
       }
       if (speed >= 0.0f) {
           rampLength += dist;
       } else {
           rampLength += (speed + incre) * dist / incre;
           speed = 0.0f;
       }
       speed -= incre;
       numSteps++;
       if (log->isDebugEnabled()) {
                log->debug(tr("step %1 incr= %2, to speed= %3, dist= %4 dnRampLength= %5").arg(
                        numSteps).arg(incre).arg(speed).arg(dist).arg(rampLength));
       }
       incre /= INCRE_RATE;
    }
    if (log->isDebugEnabled()) {
        log->debug(tr("%1 speed steps of delta= %2 for dnRampLength= %3 from maxThrottle= %4").arg(
                numSteps).arg(_throttleIncr).arg(rampLength).arg(_maxThrottle));
    }
    return rampLength;
}

/*private*/ float NXFrame::getRampLength(float totalLen, RosterSpeedProfile* speedProfile) {
    float speed = 0.0f;
    float rampLength = 0.0f;
    int numSteps = 0;
    float factor =  static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"))->getDefaultThrottleFactor();
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
    bool isForward = _forward->isChecked();
//        getProfileForDirection(isForward);  // establish a SpeedProfile and present anomaly dialog. if needed
    bool hasProfileSpeeds = _speedUtil->profileHasSpeedInfo();

    w->addThrottleCommand(new ThrottleSetting(0, "F0", "true", blockName));
    if (isForward) {
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

    QString msg = getTotalLength();
    if (msg != "") {
        return msg;
    }
    float increment = _throttleIncr;
    float momentumTime = _speedUtil->getMomentumTime(increment, false);
    float upRampLength;
    float dnRampLength ;
    if (_intervalTime >= momentumTime) {   // do longer ramp first
        dnRampLength = getDownRampLength();
        upRampLength = getUpRampLength();
    } else {
        upRampLength = getUpRampLength();
        dnRampLength = getDownRampLength();
    }

    if (log->isDebugEnabled()) {
        if (hasProfileSpeeds) {
            log->debug(tr("maxThrottle= %1 (%2 meters per sec), scale= %3").arg(
                    _maxThrottle).arg(_speedUtil->getTrackSpeed(_maxThrottle,isForward)).arg(_scale));
        } else {
            log->debug(tr("maxThrottle= %1 scale= %2 no SpeedProfile data").arg(_maxThrottle).arg(_scale));
        }
        log->debug(tr("Route length= %1, upRampLength= %2, dnRampLength= %3, startDist=#4, stopDist=%5").arg(
                _totalLen).arg(upRampLength).arg(dnRampLength).arg(_startDist).arg(_stopDist));
    }

    // estimate for blocks of zero length - an estimate of ramp length
    float scaleFactor =  static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"))->getDefaultThrottleFactor();
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

