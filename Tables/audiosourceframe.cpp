#include "audiosourceframe.h"
#include "audiotableaction.h"
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include "flowlayout.h"
#include "jtextfield.h"
#include <QPushButton>
#include <QLabel>
#include "audiosource.h"
#include "instancemanager.h"
#include <QGroupBox>
#include <QMessageBox>

//AudioSourceFrame::AudioSourceFrame(QWidget *parent) :
//  AbstractAudioFrame(parent)
//{
//}
/**
 * Defines a GUI for editing AudioSource objects.
 *
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
 * @author Matthew Harris copyright (c) 2009
 * @version $Revision: 28746 $
 */
// /*public*/ class AudioSourceFrame extends AbstractAudioFrame {

/*private*/ /*static*/ int AudioSourceFrame::counter = 1;

/**
 *
 */

//@SuppressWarnings("OverridableMethodCallInConstructor")
/*public*/ AudioSourceFrame::AudioSourceFrame(QString title, AudioTableDataModel* model, QWidget *parent) :
  AbstractAudioFrame(title, model, parent)
{
 //super(title, model);
 log = new Logger("AudioSourceFrame");
 lock = new QObject();

 // UI components for Add/Edit Source
 assignedBufferLabel = new QLabel(tr("Assigned Buffer"));
 assignedBuffer = new QComboBox();
 loopMinLabel = new QLabel(tr("Loop Min"));
 loopMin = new QSpinBox();
 loopMaxLabel = new QLabel(tr("Loop Max"));
 loopMax = new QSpinBox();
 //    QLabel* loopMinDelayLabel = new QLabel(tr("LabelLoopMin"));
 //    QSpinBox* loopMinDelay = new QSpinBox();
 //    QLabel* loopMaxDelayLabel = new QLabel(tr("LabelLoopMax"));
 //    QSpinBox* loopMaxDelay = new QSpinBox();
 //    QLabel* loopDelayUnitsLabel = new QLabel(tr("UnitMS"));
 loopInfinite = new QCheckBox(tr("Infinite"));
 position = new JPanelVector3f("",
         tr("UnitUnits"));
 positionRelative = new QCheckBox(tr("Relative position"));
 velocity = new JPanelVector3f(tr("Velocity"),
         tr("UnitU/S"));
 gain = new JPanelSliderf(tr("Gain"), 0.0, 1.0, 5, 4);
 pitch = new JPanelSliderf(tr("Pitch"), 0.5, 2.0, 6, 5);
 refDistanceLabel = new QLabel(tr("Reference Distance"));
 refDistance = new QSpinBox();
 maxDistanceLabel = new QLabel(tr("Maximum Distance"));
 maxDistance = new QSpinBox();
 distancesLabel = new QLabel(tr("Unit Units"));
 rollOffFactorLabel = new QLabel(tr("Roll Off Factor"));
 rollOffFactor = new QSpinBox();
 fadeInTimeLabel = new QLabel(tr("Fade In"));
 fadeInTime = new QSpinBox();
 fadeOutTimeLabel = new QLabel(tr("Fade Out"));
 fadeOutTime = new QSpinBox();
 fadeTimeUnitsLabel = new QLabel(tr("Unit MS"));

 layoutFrame();
}

//@Override
/*public*/ void  AudioSourceFrame::layoutFrame()
{
 AbstractAudioFrame::layoutFrame();
 QWidget* p;

 //p = new QWidget();
 FlowLayout* pLayout= new FlowLayout();
 //p->setLayout(pLayout = new FlowLayout());
 pLayout->addWidget(assignedBufferLabel);
 pLayout->addWidget(assignedBuffer);
 scrollLayout->addLayout(pLayout);
 QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";

 {
  p = new QGroupBox(tr("Loop"));
  p->setLayout(pLayout = new FlowLayout());
  p->setStyleSheet(gbStyleSheet);
//    p.setBorder(BorderFactory.createCompoundBorder(
//            BorderFactory.createTitledBorder(tr("LabelLoop")),
//            BorderFactory.createEmptyBorder(5, 5, 5, 5)));
  pLayout->addWidget(loopMinLabel);
  loopMin->setMinimumSize(JTextField(8).getPreferredSize());
//    loopMin.setModel(new SpinnerNumberModel(0, 0, 65535, 1));
//    loopMin->addChangeListener(new ChangeListener() {
//        //@Override
//        /*public*/ void stateChanged(ChangeEvent e) {
//            loopMax->setValue(
//                    ( loopMin->value()
//                    <  loopMax->value())
//                            ? loopMax->value()
//                            : loopMin->value());
//        }
//    });
  connect(loopMin, SIGNAL(valueChanged(int)), this, SLOT(On_loopMin_valueChanged()));
  pLayout->addWidget(loopMin);
  pLayout->addWidget(loopMaxLabel);
  loopMax->setMinimumSize( JTextField(8).getPreferredSize());
 //loopMax.setModel(new SpinnerNumberModel(0, 0, 65535, 1));
  loopMax->setMinimum(0);
  loopMax->setValue(0);
  loopMax->setMaximum(65535);
  loopMax->setSingleStep(1);
// loopMax->addChangeListener(new ChangeListener() {
//     //@Override
//     /*public*/ void stateChanged(ChangeEvent e) {
//         loopMin->setValue(
//                 ( loopMax->value()
//                 <  loopMin->value())
//                         ? loopMax->value()
//                         : loopMin->value());
//     }
// });
  connect(loopMax, SIGNAL(valueChanged(int)), this, SLOT(On_loopMax_valueChanged()));
  pLayout->addWidget(loopMax);
// loopInfinite.addChangeListener(new ChangeListener() {
//     //@Override
//     /*public*/ void stateChanged(ChangeEvent e) {
//         loopMin.setEnabled(!loopInfinite->isChecked());
//         loopMax.setEnabled(!loopInfinite->isChecked());
//     }
// });
  connect(loopInfinite, SIGNAL(toggled(bool)), this, SLOT(On_loopInfinite_toggled()));
  pLayout->addWidget(loopInfinite);
  //mainLayout->addLayout(pLayout);
  scrollLayout->addWidget(p);
 }

//        p = new QWidget(); p.setLayout(new FlowLayout());
//        p.setBorder(BorderFactory.createCompoundBorder(
//                        BorderFactory.createTitledBorder(tr("LabelLoopDelay")),
//                        BorderFactory.createEmptyBorder(5, 5, 5, 5)));
//        pLayout->addWIdget(loopMinDelayLabel);
//        loopMinDelay.setPreferredSize(new JTextField(8).getPreferredSize());
//        loopMinDelay.setModel(new SpinnerNumberModel(0,0,Integer.MAX_VALUE,1));
//        loopMinDelay.addChangeListener(new ChangeListener() {
//            /*public*/ void stateChanged(ChangeEvent e) {
//                loopMaxDelay->setValue(
//                        (loopMinDelay->value()
//                        <loopMaxDelay->value())
//                        ?loopMaxDelay->value()
//                        :loopMinDelay->value());
//            }
//        });
//        pLayout->addWIdget(loopMinDelay);
//        pLayout->addWIdget(loopMaxDelayLabel);
//        loopMaxDelay.setPreferredSize(new JTextField(8).getPreferredSize());
//        loopMaxDelay.setModel(new SpinnerNumberModel(0,0,Integer.MAX_VALUE,1));
//        loopMaxDelay.addChangeListener(new ChangeListener() {
//            /*public*/ void stateChanged(ChangeEvent e) {
//                loopMinDelay->setValue(
//                        (loopMaxDelay->value()
//                        <loopMinDelay->value())
//                        ?loopMaxDelay->value()
//                        :loopMinDelay->value());
//            }
//        });
//        pLayout->addWIdget(loopMaxDelay);
//        pLayout->addWIdget(loopDelayUnitsLabel);
//        main.add(p);
//
 p = new QGroupBox(tr("Position"));
 QVBoxLayout* p2Layout;
 ((QGroupBox*)p)->setLayout(p2Layout = new QVBoxLayout);//(p, BoxLayout.Y_AXIS));
 p->setStyleSheet(gbStyleSheet);
//    p.setBorder(BorderFactory.createCompoundBorder(
//            BorderFactory.createTitledBorder(tr("LabelPosition")),
//            BorderFactory.createEmptyBorder(5, 5, 5, 5)));
 p2Layout->addWidget(position);
 p2Layout->addWidget(positionRelative);
 scrollLayout->addWidget(p);

 scrollLayout->addWidget(velocity);
 scrollLayout->addWidget(gain);
 scrollLayout->addWidget(pitch);

 p = new QGroupBox(tr("Distances"));
 QVBoxLayout* pLayoutb;
 ((QGroupBox*)p)->setLayout(pLayoutb = new QVBoxLayout);//(p, BoxLayout.Y_AXIS));
 p->setStyleSheet(gbStyleSheet);
//    p.setBorder(BorderFactory.createCompoundBorder(
//            BorderFactory.createTitledBorder(tr("LabelDistances")),
//            BorderFactory.createEmptyBorder(5, 5, 5, 5)));

 QWidget* p2;
 p2 = new QWidget();
 FlowLayout* p2FlowLayout;
 p2->setLayout(p2FlowLayout = new FlowLayout());
 p2FlowLayout->addWidget(refDistanceLabel);
 refDistance->setMinimumSize( JTextField(8).getPreferredSize());
//    refDistance.setModel(
//            new SpinnerNumberModel(new Float(0f), new Float(0f), new Float(Audio.MAX_DISTANCE), new Float(FLT_PRECISION)));
 //refDistance.setEditor(new QSpinBox.NumberEditor(refDistance, "0.00"));
// refDistance.addChangeListener(new ChangeListener() {
//     //@Override
//     /*public*/ void stateChanged(ChangeEvent e) {
//         maxDistance->setValue(
//                 ((Float) refDistance->value()
//                 < (Float) maxDistance->value())
//                         ? maxDistance->value()
//                         : refDistance->value());
//     }
// });
 connect(refDistance, SIGNAL(valueChanged(int)), this, SLOT(On_refDistance_valueChanged()));
 p2FlowLayout->addWidget(refDistance);

 p2FlowLayout->addWidget(maxDistanceLabel);
 maxDistance->setMinimumSize(JTextField(8).getPreferredSize());
//    maxDistance.setModel(
//            new SpinnerNumberModel(new Float(0f), new Float(0f), new Float(Audio.MAX_DISTANCE), new Float(FLT_PRECISION)));
 //maxDistance->setEditor(new QSpinBox.NumberEditor(maxDistance, "0.00"));
// maxDistance->addChangeListener(new ChangeListener() {
//     //@Override
//     /*public*/ void stateChanged(ChangeEvent e) {
//         refDistance->setValue(
//                 ((Float) maxDistance->value()
//                 < (Float) refDistance->value())
//                         ? maxDistance->value()
//                         : refDistance->value());
//     }
// });
 connect(maxDistance, SIGNAL(valueChanged(int)), this, SLOT(On_maxDistance_valueChanged()));
 p2FlowLayout->addWidget(maxDistance);
 p2FlowLayout->addWidget(distancesLabel);
 pLayoutb->addWidget(p2);

 p2 = new QWidget();
 p2->setLayout(p2FlowLayout = new FlowLayout());
 p2Layout->addWidget(rollOffFactorLabel);
 rollOffFactor->setMinimumSize( JTextField(8).getPreferredSize());
//    rollOffFactor.setModel(
//            new SpinnerNumberModel(new Float(0f), new Float(0f), new Float(Audio.MAX_DISTANCE), new Float(FLT_PRECISION)));
 //rollOffFactor->setEditor(new QSpinBox.NumberEditor(rollOffFactor, "0.00"));
 p2FlowLayout->addWidget(rollOffFactor);
 pLayout->addWidget(p2);
 scrollLayout->addWidget(p);

 p = new QGroupBox(tr("Fade Times"));
 ((QGroupBox*)p)->setLayout(p2FlowLayout = new FlowLayout());
 p->setStyleSheet(gbStyleSheet);
// p.setBorder(BorderFactory.createCompoundBorder(
//         BorderFactory.createTitledBorder(tr("LabelFadeTimes")),
//         BorderFactory.createEmptyBorder(5, 5, 5, 5)));

 p2FlowLayout->addWidget(fadeInTimeLabel);
 fadeInTime->setMinimumSize(JTextField(8).getPreferredSize());
 //fadeInTime->setModel(new SpinnerNumberModel(0, 0, Integer.MAX_VALUE, 1));
 fadeInTime->setRange(0, 65535);
 fadeInTime->setValue(0);
 p2FlowLayout->addWidget(fadeInTime);

 p2FlowLayout->addWidget(fadeOutTimeLabel);
 fadeOutTime->setMinimumSize(JTextField(8).getPreferredSize());
 //fadeOutTime.setModel(new SpinnerNumberModel(0, 0, 65535, 1));
 fadeOutTime->setRange(0, 65535);
 fadeOutTime->setValue(0);
 p2FlowLayout->addWidget(fadeOutTime);

 p2FlowLayout->addWidget(fadeTimeUnitsLabel);
 scrollLayout->addWidget(p);

 QPushButton* ok;
 QVBoxLayout* centralWidgetLayout;
 if(frame->getContentPane() == NULL)
 {
  QWidget* centralWidget = new QWidget();
  centralWidgetLayout = new QVBoxLayout;
  centralWidget->setLayout(centralWidgetLayout);
  frame->setCentralWidget(centralWidget);
 }
 else
  centralWidgetLayout = (QVBoxLayout*)frame->centralWidget()->layout();
centralWidgetLayout->addWidget(ok = new QPushButton(tr("OK")));
//    ok.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            okPressed(e);
//        }
//    });
 connect(ok, SIGNAL(clicked()), this, SLOT(okPressed()));
}

/**
 * Method to populate the Edit Source frame with default values
 */
////@Override
/*public*/ void AudioSourceFrame::resetFrame() {
    /*synchronized (lock)*/ {
        sysName->setText("IAS" + QString::number(counter++));
    }
    userName->setText("");
    assignedBuffer->setCurrentIndex(0);
    loopInfinite->setChecked(false);
    loopMin->setValue(AudioSource::LOOP_NONE);
    loopMax->setValue(AudioSource::LOOP_NONE);
//        loopMinDelay->setValue(0);
//        loopMaxDelay->setValue(0);
    position->setValue(QVector3D(0, 0, 0));
    positionRelative->setChecked(false);
    velocity->setValue(QVector3D(0, 0, 0));
    gain->setValue(1.0);
    pitch->setValue(1.0);
    refDistance->setValue(1.0);
    maxDistance->setValue(Audio::MAX_DISTANCE);
    rollOffFactor->setValue(1.0);
    fadeInTime->setValue(1000);
    fadeOutTime->setValue(1000);

    this->_newSource = true;
}

void AudioSourceFrame::On_loopMin_valueChanged()
{
 loopMax->setValue(
         ( loopMin->value()
         <  loopMax->value())
                 ? loopMax->value()
                 : loopMin->value());
}
void AudioSourceFrame::On_loopMax_valueChanged()
{
 loopMin->setValue(
         ( loopMax->value()
         <  loopMin->value())
                 ? loopMax->value()
                 : loopMin->value());
}

void AudioSourceFrame::On_loopInfinite_toggled()
{
 loopMin->setEnabled(!loopInfinite->isChecked());
 loopMax->setEnabled(!loopInfinite->isChecked());
}

void AudioSourceFrame::On_refDistance_valueChanged()
{
  maxDistance->setValue(
          ( refDistance->value()
          < maxDistance->value())
                  ? maxDistance->value()
                  : refDistance->value());
}

void AudioSourceFrame::On_maxDistance_valueChanged()
{
 refDistance->setValue(
         ( maxDistance->value()
         <  refDistance->value())
                 ? maxDistance->value()
                 : refDistance->value());

}

/**
 * Method to populate the Edit Source frame with current values
 */
////@Override
/*public*/ void AudioSourceFrame::populateFrame(Audio* a)
{
 AbstractAudioFrame::populateFrame(a);
 AudioSource* s = (AudioSource*) a;
 AudioManager* am = ((AudioManager*)InstanceManager::getDefault("AudioManager"));
 QString ab = s->getAssignedBufferName();
 Audio* b = am->getAudio(ab);
 if (b != NULL)
 {
  assignedBuffer->setCurrentIndex(assignedBuffer->findText(b->getUserName() == NULL ? ab : b->getUserName()));
 }
 loopInfinite->setChecked((s->getMinLoops() == AudioSource::LOOP_CONTINUOUS));
 loopMin->setValue(loopInfinite->isChecked() ? 0 : s->getMinLoops());
 loopMax->setValue(loopInfinite->isChecked() ? 0 : s->getMaxLoops());
//        loopMinDelay->setValue(s.getMinLoopDelay());
//        loopMaxDelay->setValue(s.getMaxLoopDelay());
 position->setValue(s->getPosition());
 positionRelative->setChecked(s->isPositionRelative());
 velocity->setValue(s->getVelocity());
 gain->setValue(s->getGain());
 pitch->setValue(s->getPitch());
 refDistance->setValue(s->getReferenceDistance());
 maxDistance->setValue(s->getMaximumDistance());
 rollOffFactor->setValue(s->getRollOffFactor());
 fadeInTime->setValue(s->getFadeIn());
 fadeOutTime->setValue(s->getFadeOut());

 this->_newSource = false;
}

/*public*/ void AudioSourceFrame::updateBufferList() {
    AudioManager* am = ((AudioManager*)InstanceManager::getDefault("AudioManager"));
    assignedBuffer->clear();
    assignedBuffer->addItem("Select buffer from list");
    foreach (QString s, am->getSystemNameList(Audio::BUFFER)) {
        QString u = am->getAudio(s)->getUserName();
        if (u != NULL) {
            assignedBuffer->addItem(u);
        } else {
            assignedBuffer->addItem(s);
        }
    }
}

void AudioSourceFrame::okPressed(JActionEvent* /*e*/)
{
 QString user = userName->text();
 if (user==(""))
 {
  user = "";
 }
 QString sName = sysName->text().toUpper();
 AudioSource* s;
 try
 {
  AudioManager* am = ((AudioManager*)InstanceManager::getDefault("AudioManager"));
  s = (AudioSource*) am->provideAudio(sName);
  if (s == NULL)
  {
   log->error("Problem creating source");
   //throw new AudioException("Problem creating source");
   return;
  }
  if (_newSource && am->getByUserName(user) != NULL)
  {
   am->deregister(s);
   counter--;
   log->error("Duplicate user name - please modify");
   //throw new AudioException("Duplicate user name - please modify");
   return;
  }
  s->setUserName(user);
  if (assignedBuffer->currentIndex() > 0) {
      Audio* a = am->getAudio( assignedBuffer->currentText());
      s->setAssignedBuffer(a->getSystemName());
  }
  s->setMinLoops(loopInfinite->isChecked() ? AudioSource::LOOP_CONTINUOUS :  loopMin->value());
  s->setMaxLoops(loopInfinite->isChecked() ? AudioSource::LOOP_CONTINUOUS :  loopMax->value());
//            s.setMinLoopDelay( loopMinDelay->value());
//            s.setMaxLoopDelay( loopMaxDelay->value());
  s->setPosition(position->getValue());
  s->setPositionRelative(positionRelative->isChecked());
  s->setVelocity(velocity->getValue());
  s->setGain(gain->getValue());
  s->setPitch(pitch->getValue());
  s->setReferenceDistance( refDistance->value());
  s->setMaximumDistance( maxDistance->value());
  s->setRollOffFactor( rollOffFactor->value());
  s->setFadeIn( fadeInTime->value());
  s->setFadeOut( fadeOutTime->value());

  // Notify changes
  model->fireTableDataChanged();

  this->setHidden(true);
 }
 catch (AudioException ex)
 {
//        JOptionPane.showMessageDialog(NULL, ex.getMessage(), tr("AudioCreateErrorTitle"), JOptionPane.ERROR_MESSAGE);
QMessageBox::critical(NULL, tr("Error creating Audio object"), ex.getMessage());
 }
}
/*public*/ QString AudioSourceFrame::getClassName()
{
 return "jmri.jmrit.auio.swing.AudioSourceFrame";
}
