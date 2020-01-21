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
#include "rampdata.h"

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
 _forward = new   QRadioButton();
 _reverse = new   QRadioButton();
 _noRamp = new QCheckBox();
 _noSound = new QCheckBox();
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
    p2Layout->addWidget(makeTextBoxPanel(_noSound, "NoSound", "ToolTipNoSound"));
    p2Layout->addWidget(makeTextBoxPanel(_stageEStop, "StageEStop", ""));
    p2Layout->addWidget(makeTextBoxPanel(_haltStartBox, "HaltAtStart", ""));
    p2Layout->addWidget(makeTextBoxPanel(_shareRouteBox, "ShareRoute", "ToolTipShareRoute"));

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
/*private*/ void NXFrame::updateAutoRunPanel() {
    _startDist = getPathLength(_orders->at(0)) / 2;
    _stopDist = getPathLength(_orders->at(_orders->size()-1)) / 2;
//        NumberFormat formatter = NumberFormat.getNumberInstance();
    if (_originUnits->text() == ("In")) {
        float num = qRound(_startDist * 100 / 25.4f);
        _originDist->setText(QString::number(num / 100.0f));
    } else {
        float num = qRound(_startDist * 100);
        _originDist->setText(QString::number(num / 1000.0f));
    }
    if (_destUnits->text() == ("In")) {
        float num = qRound(_stopDist * 100 / 25.4f);
        _destDist->setText(QString::number(num / 100.0f));
    } else {
        float num = qRound(_stopDist * 100);
        _destDist->setText(QString::number(num / 1000.0f));
    }
    _autoRunPanel->update();
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
 // TODO:
 QWidget* con = (QWidget*)getContentPane();//->getComponent(0);
 //con.removeAll();
 QList<QWidget*> widgets = con->findChildren<QWidget*>();
 foreach(QWidget* widget, widgets)
  con->layout()->removeWidget(widget);
 if (_runAuto->isChecked()) {
     con->layout()->addWidget(_autoRunPanel);
 } else {
     con->layout()->addWidget(_trainPanel);
 }
 con->layout()->addWidget(_switchPanel);
 updateAutoRunPanel();
 pack();
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

/*private*/ float NXFrame::adjustdistance(float fromSpeed, float toSpeed, float distance, BlockOrder* bo) throw (JmriException) {
        float pathLen = getPathLength(bo);
        if (pathLen <= 0) {
         throw JmriException(tr("Path %1 in block %2 has length zero. Cannot run NXWarrants or ramp speeds through blocks with zero length.").arg(bo->getPathName()).arg(bo->getBlock()->getDisplayName()));
        }
        int timeIncrement = _speedUtil->getRampTimeIncrement();
        float minDist = _speedUtil->getDistanceOfSpeedChange(fromSpeed, toSpeed, timeIncrement) +.1f;
        if (distance < minDist) {
            distance = minDist;
        } else if (distance > pathLen - minDist) {
            distance = pathLen - minDist;
        }
        return distance;
    }
/*
 * Return length of warrant route in mm.  Assume start and end is in the middle of first
 * and last blocks.  Use a default length for blocks with unspecified length.
 */
/*private*/ float NXFrame::getTotalLength() {
 float totalLen = 0.0f;
 QList<BlockOrder*>* orders = getOrders();
 float throttleIncrement = _speedUtil->getRampThrottleIncrement();
 try {
     _startDist = adjustdistance(0.0f, throttleIncrement, _startDist, orders->at(0));
     totalLen = _startDist;
     for (int i = 1; i < orders->size() - 1; i++) {
         BlockOrder* bo = orders->value(i);
         float pathLen = getPathLength(bo);
         if (pathLen <= 0) {
             throw JmriException(tr("Path %1 in block %2 has length zero. Cannot run NXWarrants or ramp speeds through blocks with zero length.").arg(bo->getPathName()).arg(bo->getBlock()->getDisplayName()));
         }
         totalLen += pathLen;
     }
     _stopDist = adjustdistance(throttleIncrement, 0.0f, _stopDist, orders->at(0));
     totalLen += _stopDist;
 } catch (JmriException je) {
     throw je;
 }
 return totalLen;
}
#if 0
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
#endif
/*private*/ QString NXFrame::makeCommands(Warrant* w) {

    int nextIdx = 0;        // block index - increment after getting a block order
    QList<BlockOrder*>* orders = getOrders();
    BlockOrder* bo = orders->at(nextIdx++);
    QString blockName = bo->getBlock()->getDisplayName();
    bool isForward = _forward->isChecked();
//        getProfileForDirection(isForward);  // establish a SpeedProfile and present anomaly dialog. if needed
    bool hasProfileSpeeds = _speedUtil->profileHasSpeedInfo();

    int cmdNum;
    w->addThrottleCommand(new ThrottleSetting(0, "F0", "true", blockName));
    if (_forward->isChecked())
    {
        w->addThrottleCommand(new ThrottleSetting(1000, "Forward", "true", blockName));
        if(!_noSound->isChecked())
        {
         w->addThrottleCommand(new ThrottleSetting(1000, "F2", "true", blockName));
         w->addThrottleCommand(new ThrottleSetting(2500, "F2", "false", blockName));
         w->addThrottleCommand(new ThrottleSetting(1000, "F2", "true", blockName));
         w->addThrottleCommand(new ThrottleSetting(2500, "F2", "false", blockName));
         cmdNum = 7;
        }
        else
        {
         cmdNum = 3;
        }
    } else {
        w->addThrottleCommand(new ThrottleSetting(1000, "Forward", "false", blockName));
        if(!_noSound->isChecked())
        {
            w->addThrottleCommand(new ThrottleSetting(2000, "F3", "true", blockName));
            w->addThrottleCommand(new ThrottleSetting(500, "F3", "false", blockName));
            w->addThrottleCommand(new ThrottleSetting(500, "F3", "true", blockName));
            w->addThrottleCommand(new ThrottleSetting(500, "F1", "true", blockName));
            cmdNum = 6;
        }
        else
        {
            cmdNum = 2;
        }

    }

    float totalLen;
    try {
        totalLen = getTotalLength();
    } catch (JmriException je) {
        return je.getMessage();
    }

    RampData* upRamp;
    RampData* downRamp;
    QListIterator<float> downIter = downRamp->speedIterator(false);
    float intervalDist;
    do {
        upRamp = _speedUtil->getRampForSpeedChange(0.f, _maxThrottle);
        downRamp = _speedUtil->getRampForSpeedChange(_maxThrottle, 0.f);
        downIter = downRamp->speedIterator(false);
        float prevSetting = downIter.previous();   // top value is _maxThrottle
        _maxThrottle -= prevSetting  - downIter.previous();    // last throttle increment
        // distance attaining final speed
        intervalDist = _speedUtil->getDistanceOfSpeedChange(_maxThrottle, prevSetting, downRamp->getRampTimeIncrement());
        log->debug(tr("Route length= %1, upRampLength= %2, dnRampLength= %3").arg(
                totalLen).arg(upRamp->getRampLength()).arg(downRamp->getRampLength()));
    } while ((upRamp->getRampLength() + intervalDist + downRamp->getRampLength()) > totalLen);
    _maxThrottle = downRamp->getMaxSpeed();

    if (log->isDebugEnabled()) {
        if (hasProfileSpeeds) {
            log->debug(tr("maxThrottle= %1 (%2 meters per sec), scale= %3").arg(
                    _maxThrottle).arg(_speedUtil->getTrackSpeed(_maxThrottle)).arg(_scale));
        } else {
            log->debug(tr("maxThrottle= %1 scale= %2 no SpeedProfile data").arg(_maxThrottle).arg(_scale));
        }
    }

    float blockLen = _startDist;    // length of path in current block

    // start train
    float speedTime = 0;    // ms time to complete speed step from last block
    float noopTime = 0;     // ms time for entry into next block
    QListIterator<float> iter = upRamp->speedIterator(true);
    float curThrottle = iter.next();  // throttle setting
    float nextThrottle = 0.0f;
    float curDistance = 0;  // current distance traveled mm
    float blkDistance = 0;  // distance traveled in current block mm
    float upRampLength = upRamp->getRampLength();
    float remRamp = upRampLength;
    float remTotal = totalLen;
    float dnRampLength = downRamp->getRampLength();
    int timeInterval = downRamp->getRampTimeIncrement();
    bool rampsShareBlock = false;

    if (log->isDebugEnabled()) {
        log->debug(tr("Start in block \"%1\" startDist= %2 stopDist= %3").arg(blockName).arg(_startDist).arg(_stopDist));
    }
    while (iter.hasNext()) {       // ramp up loop

        while (blkDistance < blockLen && iter.hasNext()) {
            nextThrottle = iter.next();
            float dist = _speedUtil->getDistanceOfSpeedChange(curThrottle, nextThrottle, timeInterval);
            if (blkDistance + dist <= blockLen) {
                blkDistance += dist;
                remRamp -= dist;
                curThrottle = nextThrottle;
                w->addThrottleCommand(new ThrottleSetting((int) speedTime, "Speed",
                        QString::number(curThrottle), blockName,
                        (hasProfileSpeeds ? _speedUtil->getTrackSpeed(curThrottle) : 0.0f)));
                if (log->isDebugEnabled()) {
                    log->debug(tr("%1. Ramp Up in block \"%2\" to speed %3 in %4ms to distance= {}mm, remRamp= %5").arg(
                            ++cmdNum).arg(blockName).arg(curThrottle).arg((int) speedTime).arg(blkDistance).arg(remRamp));
                }
                speedTime = timeInterval;
            } else {
                iter.previous();
                break;
            }
        }
        curDistance += blkDistance;

        if (blkDistance >= blockLen) {
            // Possible case where blkDistance can exceed the length of a block that was just entered.
            // Skip over block and move to next block and adjust the distance times into that block
            noopTime = _speedUtil->getTimeForDistance(curThrottle, blockLen);   // noop distance to run through block
            speedTime = _speedUtil->getTimeForDistance(curThrottle, blkDistance - blockLen);
            curDistance += blockLen;
        } else {
            // typical case where next speed change broke out of above loop
            noopTime = _speedUtil->getTimeForDistance(curThrottle, (blockLen - blkDistance));   // time to next block
            if (noopTime > timeInterval) {  // after last speed change
                speedTime = 0;  // irrelevant, loop will end
                if (!iter.hasNext()) {
                    noopTime += timeInterval;   // add time to complete last speed change
                }
            } else {
                speedTime = timeInterval - noopTime;   // time to next speed change
            }
            curDistance += blockLen - blkDistance;  // noop distance
        }

        // break out here if done or deceleration is to be started in this block
        if (!iter.hasNext() || remTotal - blockLen <= dnRampLength) {
            break;
        }

        remTotal -= blockLen;
        if (log->isDebugEnabled()) {
            log->debug(tr("Leave RampUp block \"%1\"  blkDistance= %2, blockLen= %3 remRamp= %4 curDistance= %5 remTotal=^").arg(
                    blockName).arg(blkDistance).arg(blockLen).arg(remRamp).arg(curDistance).arg(remTotal));
        }
        if (nextIdx < orders->size()) {
            bo = orders->value(nextIdx++);
            blockLen = getPathLength(bo);
            if (blockLen <= 0) {
                return tr("Path %1 in block %2 has length zero. Cannot run NXWarrants or ramp speeds through blocks with zero length.").arg(bo->getPathName()).arg(bo->getBlock()->getDisplayName());
             }
            blockName = bo->getBlock()->getDisplayName();
            w->addThrottleCommand(new ThrottleSetting((int) noopTime, "NoOp", "Enter Block", blockName,
                    (hasProfileSpeeds ? _speedUtil->getTrackSpeed(curThrottle) : 0.0f)));
            if (log->isDebugEnabled()) {
                log->debug(tr("%1. Enter RampUp block \"%2\" noopTime= %3, speedTime= %4 blockLen= %5, remTotal= %6").arg(
                    cmdNum++).arg(blockName).arg(noopTime).arg(speedTime).arg(blockLen).arg(remTotal));
            }
        }
        blkDistance = _speedUtil->getDistanceTraveled(curThrottle, Warrant::Normal, speedTime);
    }
    if (log->isDebugEnabled()) {
        log->debug(tr("Ramp Up done at block \"%1\" curThrottle=%2 blkDistance=%3 curDistance=%4 remTotal= %5 remRamp=%6").arg(
                blockName).arg(curThrottle).arg(blkDistance).arg(curDistance).arg(remTotal).arg(remRamp));
    }

    if (remTotal - blockLen > dnRampLength) {    // At maxThrottle, remainder of block at max speed
        if (nextIdx < orders->size()) {    // not the last block
            remTotal -= blockLen;
            bo = orders->value(nextIdx++);
            blockLen = getPathLength(bo);
            if (blockLen <= 0) {
                return tr("Path %1 in block %2 has length zero. Cannot run NXWarrants or ramp speeds through blocks with zero length.").arg(bo->getPathName()).arg(bo->getBlock()->getDisplayName());
             }
            blockName = bo->getBlock()->getDisplayName();
            w->addThrottleCommand(new ThrottleSetting((int) noopTime, "NoOp", "Enter Block", blockName,
                    (hasProfileSpeeds ? _speedUtil->getTrackSpeed(curThrottle) : 0.0f)));
            if (log->isDebugEnabled()) {
                log->debug(tr("%1. Enter block \"%2\" noopTime= %3).arg(blockLen= %4).arg(curDistance=%5").arg(
                        cmdNum++).arg(blockName).arg(noopTime).arg(blockLen).arg(curDistance));
            }
            blkDistance = 0;
        }

        // run through mid route at max speed
        while (nextIdx < orders->size() && remTotal - blockLen > dnRampLength) {
            remTotal -= blockLen;
            // constant speed, get time to next block
            noopTime = _speedUtil->getTimeForDistance(curThrottle, blockLen);   // time to next block
            curDistance += blockLen;
            if (log->isDebugEnabled()) {
                log->debug(tr("Leave MidRoute block \"%1\" noopTime= %2 blockLen= %3 curDistance=%4 remTotal= %5").arg(
                        blockName).arg(noopTime).arg(blockLen).arg(curDistance).arg(remTotal));
            }
            bo = orders->value(nextIdx++);
            blockLen = getPathLength(bo);
            if (blockLen <= 0) {
                return tr("Path %1 in block %2 has length zero. Cannot run NXWarrants or ramp speeds through blocks with zero length.").arg(bo->getPathName()).arg(bo->getBlock()->getDisplayName());
             }
            blockName = bo->getBlock()->getDisplayName();
            if (nextIdx == orders->size()) {
                blockLen = _stopDist;
            }
            w->addThrottleCommand(new ThrottleSetting((int) noopTime, "NoOp", "Enter Block", blockName,
                    (hasProfileSpeeds ? _speedUtil->getTrackSpeed(curThrottle) : 0.0f)));
            if (log->isDebugEnabled()) {
                log->debug(tr("%1. Enter MidRoute block \"%2\" noopTime= %3, blockLen= %4, curDistance=%5").arg(
                        cmdNum++).arg(blockName).arg(noopTime).arg(blockLen).arg(curDistance));
            }
         }
        blkDistance = 0;
   } else {
        // else Start ramp down in current block
        rampsShareBlock = true;
    }

    // Ramp down.
    remRamp = dnRampLength;
    iter = downRamp->speedIterator(false);
    iter.previous();   // discard, equals curThrottle
    float remMaxSpeedDist;
    if (!rampsShareBlock) {
        remMaxSpeedDist = remTotal - dnRampLength;
    } else {
        remMaxSpeedDist = totalLen - upRampLength - dnRampLength;
    }
    // distance in block where down ramp is started
    blkDistance += remMaxSpeedDist;
    // time to start down ramp
    speedTime = _speedUtil->getTimeForDistance(curThrottle, remMaxSpeedDist) + timeInterval;

    if (log->isDebugEnabled()) {
        log->debug(tr("Begin Ramp Down at block \"%1\" blockLen=%2, at distance= %3 curDistance = %4 remTotal= %5 curThrottle= %6 (%7)").arg(
                blockName).arg(blockLen).arg(blkDistance).arg(curDistance).arg(remTotal).arg(curThrottle).arg(remMaxSpeedDist));
    }

    while (iter.hasPrevious()) {
        bool atLastBlock = false;
        if (nextIdx == orders->size()) { // at last block
            atLastBlock = true;
            if (_stageEStop->isChecked()) {
                w->addThrottleCommand(new ThrottleSetting(50, "Speed", "-0.5", blockName,
                        (hasProfileSpeeds ? _speedUtil->getTrackSpeed(curThrottle) : 0.0f)));
                curThrottle = -0.5f;
                if (log->isDebugEnabled()) {
                    log->debug(tr("%1. At block \"%2\" EStop set speed= %3").arg(cmdNum++).arg(blockName).arg(-0.5));
                }
                break;
            }
        }

        do /*while (blkDistance < blockLen && iter.hasPrevious())*/ {
            bool hasPrevious = false;
            if (iter.hasPrevious()) {
                nextThrottle = iter.previous();
                hasPrevious = true;
            }
            float dist = _speedUtil->getDistanceOfSpeedChange(curThrottle, nextThrottle, timeInterval);
            blkDistance += dist;
            remRamp -= dist;
            curThrottle = nextThrottle;
            if (curThrottle <= 0.0f && !atLastBlock) {
                log->warn(tr("Set curThrottle = %1 in block \"%2\" (NOT the last block)!").arg(curThrottle).arg(blockName));
                break;
            }
            if (hasPrevious) {
                w->addThrottleCommand(new ThrottleSetting((int) speedTime, "Speed", QString::number(curThrottle), blockName,
                        (hasProfileSpeeds ? _speedUtil->getTrackSpeed(curThrottle) : 0.0f)));
                if (log->isDebugEnabled()) {
                    log->debug(tr("%1. Ramp Down in block \"%2\" to curThrottle %3 in %4ms to distance= %5mm, remRamp= %6").arg(
                            ++cmdNum).arg(blockName).arg(curThrottle).arg((int) speedTime).arg(blkDistance).arg(remRamp));
                }
            } else {
                if (curThrottle > 0.0f) {
                    log->warn(tr("No speed setting after command %1 in block \"%2\". curThrottle= %3 blkDistance= %4mm").arg(
                            cmdNum).arg(blockName).arg(curThrottle).arg(blkDistance));
                }
                break;
            }
            speedTime = timeInterval;
        } while (blkDistance < blockLen);
        curDistance += blkDistance;

        if (log->isDebugEnabled()) {
            log->debug(tr("Leave RampDown block \"%1\"  blkDistance= %2, blockLen= %3 remRamp= %4 curDistance= %5 remTotal= %6").arg(
                    blockName).arg(blkDistance).arg(blockLen).arg(remRamp).arg(curDistance).arg(remTotal));
        }
        if (blkDistance >= blockLen) {
            // typical case where next speed change broke out of above loop
            speedTime = _speedUtil->getTimeForDistance(curThrottle, blkDistance - blockLen); // time to run in next block
            if (speedTime > timeInterval) {
                noopTime = 0;
            } else {
                noopTime = timeInterval - speedTime;
            }
        } else {
            speedTime = timeInterval - noopTime;
        }

        remTotal -= blockLen;
        if (!atLastBlock) {
            curDistance += blockLen - blkDistance;  // noop distance
            bo = orders->value(nextIdx++);
            if (nextIdx == orders->size()) {
                blockLen = _stopDist;
            } else {
                blockLen = getPathLength(bo);
                if (blockLen <= 0) {
                 return tr("Path %1 in block %2 has length zero. Cannot run NXWarrants or ramp speeds through blocks with zero length.").arg(bo->getPathName()).arg(bo->getBlock()->getDisplayName());

                 }
            }
            blockName = bo->getBlock()->getDisplayName();
            w->addThrottleCommand(new ThrottleSetting((int) noopTime, "NoOp", "Enter Block", blockName,
                    (hasProfileSpeeds ? _speedUtil->getTrackSpeed(curThrottle) : 0.0f)));
            if (log->isDebugEnabled()) {
                log->debug(tr("%1. Enter block \"%2\" noopTime= %3ms, blockLen= %4, curDistance=%5").arg(
                        cmdNum++).arg(blockName).arg(noopTime).arg(blockLen).arg(curDistance));
            }
            blkDistance = _speedUtil->getDistanceTraveled(curThrottle, Warrant::Normal, speedTime);
        } else {
            blkDistance = 0.0f;
        }
    }

    // Ramp down finished
    log->debug(tr("Ramp down done at block \"%1\",  remRamp= %2, curDistance= %3 remRamp= %4").arg(
            blockName).arg(remRamp).arg(curDistance).arg(remTotal));
    if (!_noSound->isChecked()) {
        w->addThrottleCommand(new ThrottleSetting(500, "F1", "false", blockName));
        w->addThrottleCommand(new ThrottleSetting(1000, "F2", "true", blockName));
        w->addThrottleCommand(new ThrottleSetting(3000, "F2", "false", blockName));
    }
    w->addThrottleCommand(new ThrottleSetting(1000, "F0", "false", blockName));
    /*      if (_addTracker.isSelected()) {
        WarrantTableFrame._defaultAddTracker = true;
        w.addThrottleCommand(new ThrottleSetting(10, "START TRACKER", "", blockName));
    } else {
        WarrantTableFrame._defaultAddTracker = false;
    }*/
    return nullptr;
}

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
/*public*/ QString NXFrame::getClassName()
{
 return "jmri.jmrit.nixieclock.NXFrame";
}

