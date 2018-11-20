#include "calibrater.h"
#include <QCheckBox>
#include <QButtonGroup>
#include <QVBoxLayout>
#include "box.h"
#include "oblock.h"
#include "throttlesetting.h"
#include "warrant.h"
#include "blockorder.h"
#include "opath.h"
#include "rosterentry.h"
#include <QMessageBox>
#include "roster.h"
#include "rosterspeedprofile.h"
#include "flowlayout.h"
#include "dccthrottle.h"
#include "signalspeedmap.h"
#include "instancemanager.h"

//Calibrater::Calibrater(QWidget *parent) :
//  JmriJFrame(parent)
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
///*public*/ class Calibrater extends jmri.util.JmriJFrame {

//    /*private*/ static final long serialVersionUID = 991792418011219112L;


Calibrater::Calibrater(Warrant* w, bool isForward, QPoint pt, QWidget *parent) :
JmriJFrame(false, false, parent)
{
    //super(false, false);
 _addBox = new QCheckBox(tr("Add data to Speed Profile"));
  _ignoreBox = new QCheckBox(tr("gnore this calibration run"));
  _clearBox = new QCheckBox(tr("Clear previous Speed Profile"));
  log = new Logger("Calibrater");

 _warrant = w;
 QButtonGroup* bg = new QButtonGroup();
 bg->addButton(_addBox);
 bg->addButton(_ignoreBox);
 _mainPanel = new QWidget();
 //_mainPanel.setLayout(new BoxLayout(_mainPanel, BoxLayout.PAGE_AXIS));
 _mainPanelLayout = new QVBoxLayout(_mainPanel);
 _mainPanelLayout->addWidget(Box::createRigidArea(QSize(350,10)));
 _mainPanelLayout->addWidget(makeEntryPanel("Calibrate a Train", isForward));
 _mainPanelLayout->addWidget(Box::createRigidArea(QSize(50,10)));
 _mainPanelLayout->addWidget(makeExitPanel(true));
//        mainPanelLayout->addWidget(Box.createRigidArea(new java.awt.Dimension(450,0)));
 _mainPanelLayout->addWidget(makeButtonPanel());
 _mainPanelLayout->addStrut(10);
 //QWidget* mainPanel = new QWidget();
 //mainPanel.setLayout(new BorderLayout(10, 10));
 QVBoxLayout* mainPanelLayout = new QVBoxLayout();
 //getContentPane().add(_mainPanel);
 setCentralWidget(_mainPanel);
 setLocation(pt.x(), pt.y());
 setAlwaysOnTop(true);
 adjustSize();
 setVisible(false);
}

/*protected*/ QString Calibrater::verifyCalibrate()
{
 _calibBlockOrder = _warrant->getViaOrder();
 if (_calibBlockOrder==NULL) {
     return  tr("noCalibBlock");
 }
 OBlock* calibBlock = _calibBlockOrder->getBlock();
 if (calibBlock==NULL) {
     return  tr("A Via Location block is required to calculate Speed Profile factors.");
 }
 _calibrateIndex = _warrant->getIndexOfBlock(calibBlock, 0);
 if (_calibrateIndex<=0 || _calibrateIndex>=_warrant->getThrottleCommands()->size()-1) {
     return  tr("Cannot use \"%1\" for Calibration Block.\nMake a route that provides room for ramp up and ramp down.  ").arg( calibBlock->getDisplayName());
 }
 if (_calibBlockOrder->getPath()->getLengthMm() <= 10.0) {
     return  tr("Length of Calibration Block \"%1\" is Too Small.").arg( calibBlock->getDisplayName());
 }
 QList <ThrottleSetting*>* cmds = _warrant->getThrottleCommands();
 float speed = 0.0f;
 QString beforeBlk = NULL;
 QString afterBlock = NULL;
 foreach (ThrottleSetting* ts, *cmds)
 {
  if (ts->getCommand().toUpper()==("SPEED"))
  {
   //try {
   bool bok;
   float s = ts->getValue().toFloat(&bok);
   // get last acceleration block
   if ( s>speed) {
       speed = s;
       beforeBlk = ts->getBlockName();
   }
   // get first deceleration block
   if ( s<speed) {
       afterBlock = ts->getBlockName();
       break;
   }
   if(!bok)
   {
    log->error(ts->toString()+" - "/*+nfe)*/+ "not a valid floating point number");
   }
  }
 }
 QString msg = NULL;
 if (_warrant->getIndexOfBlock(beforeBlk, 0) >= _calibrateIndex)
 {
  msg = tr("Warrant still making speed changes in block \"%1\".\nChange route to provide more room for ramp up and ramp down.").arg(beforeBlk);
} else if (_warrant->getIndexOfBlock(afterBlock, 0) <= _calibrateIndex) {
  msg = tr("Warrant still making speed changes in block \"%1\".\nChange route to provide more room for ramp up and ramp down.").arg(afterBlock);
 }
 else
 {
  _maxSpeed = speed;
  RosterEntry* ent = _warrant->getRosterEntry();
  if (ent!=NULL) {
      _speedProfile = ent->getSpeedProfile();
  }
 }
 return msg;
}

/*private*/ void Calibrater::dofactor()
{
 if (_clearBox->isChecked())
 {
  if (_speedProfile != NULL)
  {
//   if (JOptionPane.YES_OPTION == JOptionPane.showConfirmDialog(this, tr(
//           "ClearSpeedProfile", _warrant.getTrainId(), _speedProfile.getProfileSize()),
//           tr("WarningTitle"), JOptionPane.YES_NO_OPTION, JOptionPane.WARNING_MESSAGE) )
   if(QMessageBox::warning(this, tr("Warrant Warning"), tr("SpeedProfile for engine \"%1\" has %2 entries.\nAre you sure you sure you want to delete them? ").arg(_warrant->getTrainId()).arg(_speedProfile->getProfileSize()), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
   {
    _speedProfile->clearCurrentProfile();
   }
  }
 }
 if (_addBox->isChecked())
 {
  RosterEntry* ent = _warrant->getRosterEntry();
  if (ent==NULL)
  {
//      JOptionPane.showMessageDialog(this, tr("trainInfo6", _warrant.getTrainId()),
//              tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
   QMessageBox::warning(this, tr("Warrant Warning"), tr("Roster does not have a Speed Profile for %1.").arg(_warrant->getTrainId()));
      return;
  }
  _warrant->getRosterEntry();
  if (_speedProfile == NULL) {
      _speedProfile = new RosterSpeedProfile(ent);
      ent->setSpeedProfile(_speedProfile);
  }
// _maxSpeed is now actual speedSetting
  if (_isForward) {
      _speedProfile->setForwardSpeed(_maxSpeed, _rawSpeed*1000);
  } else {
      _speedProfile->setReverseSpeed(_maxSpeed, _rawSpeed*1000);
  }
  if (log->isDebugEnabled()) log->debug("Made speed profile setting for "+ _warrant->getTrainId()+
          ": "+(_isForward ? "Forward":"Reverse")+" step= "+QString::number(qRound(_maxSpeed*1000))+", speed= "+QString::number(_rawSpeed*1000));
  _warrant->getRosterEntry()->updateFile();
  Roster::writeRoster();
 }
 dispose();
}

/*private*/ QWidget* Calibrater::makeButtonPanel() {
    QWidget* panel = new QWidget();
    //panel.setLayout(new BoxLayout(panel, BoxLayout.LINE_AXIS));
    QHBoxLayout* panelLayout = new QHBoxLayout(panel);
    panelLayout->addWidget(Box::createGlue());
    QPushButton* button = new QPushButton(tr("OK"));
//    button.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            dofactor();
//        }
//    });
    connect(button, SIGNAL(clicked()), this, SLOT(doFactor()));
    panelLayout->addWidget(button);
    panelLayout->addStrut((20));
    button = new QPushButton(tr("Cancel"));
//    button.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            dispose();
//        }
//    });
    connect(button, SIGNAL(clicked()), this, SLOT(dispose()));
    panelLayout->addWidget(button);
    panelLayout->addWidget(Box::createGlue());
    return panel;
}

/*private*/ QWidget* Calibrater::makeEntryPanel(QString name, bool isForward)
{
    QWidget* panel = new QWidget();
    panel->setObjectName("EntryPanel");
    //panel.setLayout(new BorderLayout(10, 10));
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);
    QWidget* p = new QWidget();
    //p.setLayout(new BoxLayout(p, BoxLayout.PAGE_AXIS));
    QVBoxLayout* pLayout = new QVBoxLayout(p);
    pLayout->addWidget(new QLabel(tr("Train \"%1\" with address %1 entered block \"%3\" ").arg( _warrant->getTrainName()).arg(
                _warrant->getDccAddress()->toString()).arg( name)));
    QString direction;
    if (isForward) {
        direction = tr("forward");
    } else {
        direction = tr("reverse");
    }
    pLayout->addWidget(new QLabel(tr("in a %1 direction with throttle set to %2").arg( direction).arg(_maxSpeed)));
    panelLayout->addWidget(p, /*BorderLayout.CENTER*/0, Qt::AlignVCenter);
    panelLayout->addWidget(Box::createRigidArea(QSize(10,10)), /*BorderLayout.WEST*/0, Qt::AlignLeft);
    return panel;
}

/*private*/ QWidget* Calibrater::makeExitPanel(bool init)
{
 float spFactor = 0.0f;
 float spSpeed = 0.0f;
 DccThrottle* throttle = _warrant->getThrottle();
 float scale = static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"))->getLayoutScale();
 float scaleSpeed = _rawSpeed*scale;          // prototype m/s
 if (!init)
 {
  float speedSetting = throttle->getSpeedSetting();
  int speedStep = 0;
  switch (throttle->getSpeedStepMode())
  {
   case DccThrottle::SpeedStepMode14:
       speedStep = qRound(speedSetting * 14);
       break;
   case DccThrottle::SpeedStepMode27:
       speedStep = qRound(speedSetting * 27);
       break;
   case DccThrottle::SpeedStepMode28:
       speedStep = qRound(speedSetting * 28);
       break;
   case DccThrottle::SpeedStepMode128:
       speedStep = qRound(speedSetting * 126);
       break;
  }
  speedSetting = throttle->getSpeedIncrement()*speedStep;      // actual speedSetting
  _factor = _rawSpeed/speedSetting;
//            _factor = speedSetting*25.4f/(_rawSpeed*100);
  _isForward = throttle->getIsForward();
  if (_speedProfile!=NULL)
  {
   if (_isForward)
   {
    spSpeed = _speedProfile->getForwardSpeed(speedSetting);
   }
   else
   {
    spSpeed = _speedProfile->getReverseSpeed(speedSetting);
   }
   spFactor = spSpeed/(speedSetting*1000);
  }
  if (log->isDebugEnabled()) log->debug("Throttle speedSetting= "+QString::number(speedSetting)+", Set from _maxSpeed= "+QString::number(_maxSpeed)+
          ", expected profile speed ="+QString::number(spSpeed)+", actual _rawSpeed= "+QString::number(_rawSpeed*1000)+"mm/sec, scale= "+QString::number(scale));
  _maxSpeed = speedSetting;     // now is the actual setting
 }
 QString speedUnits;
 if ( static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"))->getInterpretation() == SignalSpeedMap::SPEED_KMPH) {
     speedUnits = "kmph";
     scaleSpeed = 3.6f*scaleSpeed;
     spSpeed = spSpeed*scale*3.6f/1000;
 } else {
     speedUnits = "mph";
     scaleSpeed = scaleSpeed*3.6f*0.621371f;
     spSpeed = spSpeed*scale*3.6f*0.621371f/1000;
 }
 QWidget* panel = new QWidget();
 panel->setObjectName("ExitPanel");
 //panel.setLayout(new BorderLayout(10, 10));
 QVBoxLayout* panelLayout = new QVBoxLayout(panel);
 QWidget* p = new QWidget();
 //p.setLayout(new BoxLayout(p, BoxLayout.PAGE_AXIS));
 QVBoxLayout* pLayout = new QVBoxLayout(panel);
 pLayout->addWidget(new QLabel(tr("Actual throttle setting is %1 and scale speed is %2 %3").arg(_maxSpeed).arg( scaleSpeed).arg( speedUnits)));
 pLayout->addWidget(new QLabel(tr("Throttle factor for this run is %1").arg( _factor)));
 if (_speedProfile!=NULL) {
     pLayout->addWidget(new QLabel(tr("Speed Profile expects speed %1 %2 and factor %3 for this setting.").arg(spSpeed).arg(speedUnits).arg(spFactor)));
 }
 else {
     pLayout->addWidget(new QLabel(tr("Roster does not have a Speed Profile for %1.").arg(_warrant->getTrainId())));
 }
 panelLayout->addWidget(p, /*BorderLayout.CENTER*/0, Qt::AlignCenter);
 panelLayout->addWidget(Box::createRigidArea(QSize(10,100)), /*BorderLayout.WEST*/0, Qt::AlignLeft);
 {
  p = new QWidget();
  //p.setLayout(new BoxLayout(p, BoxLayout.PAGE_AXIS));
  QVBoxLayout* pLayout = new QVBoxLayout(p);
  pLayout->addWidget(_addBox);
  pLayout->addWidget(_ignoreBox);
  pLayout->addWidget(_clearBox);
  QWidget* pp = new QWidget();
  //pp.setLayout(new BoxLayout(pp, BoxLayout.LINE_AXIS));
  QHBoxLayout* ppLayout = new QHBoxLayout(pp);
  ppLayout->addWidget(Box::createRigidArea(QSize(10,100)));
  ppLayout->addWidget(p);
  panelLayout->addWidget(pp, /*BorderLayout.SOUTH*/0, Qt::AlignBottom);
 }
 return panel;
}

/**
 * Called from Warrant goingActive
 * Compute actual speed and set throttle factor
 * @param index
 */
/*protected*/ void Calibrater::calibrateAt(int index)
{
 if (_calibrateIndex == index)
 {
  QObjectList ol = _mainPanelLayout->children();
  //_mainPanel->remove(3);
  _mainPanelLayout->removeWidget((QWidget*)ol.at(3));
  //_mainPanel->remove(1);
  _mainPanelLayout->removeWidget((QWidget*)ol.at(1));
   _entryTime = _calibBlockOrder->getBlock()->_entryTime;
   _mainPanelLayout->addWidget(makeEntryPanel(_calibBlockOrder->getBlock()->getDisplayName(),
           _warrant->getThrottle()->getIsForward()), 1);
   setVisible(true);
 }
 else if (_calibrateIndex == index-1)
 {
   setVisible(false);
   BlockOrder* bo = _warrant->getBlockOrderAt(index);
   long eTime = bo->getBlock()->_entryTime - _entryTime;
   _rawSpeed = _calibBlockOrder->getPath()->getLengthMm()/eTime;    // layout mm/ms
   _mainPanelLayout->insertWidget(3, makeExitPanel(false));
   setVisible(true);
 }
}
