#include "audiolistenerframe.h"
#include <QLabel>
#include <QBoxLayout>
#include "flowlayout.h"
#include <QSpinBox>
#include <QPushButton>
#include "audiolistener.h"
#include "audiotableaction.h"
#include "jtextfield.h"
#include "instancemanager.h"
#include "abstractaudio.h"
#include <QScrollArea>

//AudioListenerFrame::AudioListenerFrame(QWidget *parent) :
//  AbstractAudioFrame(parent)
//{
//}
/**
 * Define a GUI to edit AudioListener objects
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
// /*public*/ class AudioListenerFrame extends AbstractAudioFrame {

   /**
    *
    */

//@SuppressWarnings("OverridableMethodCallInConstructor")
/*public*/ AudioListenerFrame::AudioListenerFrame(QString title, AudioTableDataModel* model, QWidget *parent) :
AbstractAudioFrame(title, model, parent)
{
 //super(title, model);
 position = new JPanelVector3f(tr("Position"),
            tr("units"));
 velocity = new JPanelVector3f(tr("Velocity"),
            tr("units/sec"));
 oriAtLabel = new QLabel(tr("Look At"));
 oriAt = new JPanelVector3f("", tr("units"));
 oriUpLabel = new QLabel(tr("look Up"));
 oriUp = new JPanelVector3f("", tr("units"));
 gain = new JPanelSliderf(tr("Gain"), 0.0f, 1.0f, 5, 4);
 metersPerUnit = new QSpinBox();
 metersPerUnitLabel = new QLabel(tr("meters/unit"));

 layoutFrame();
}

//@Override
/*public*/ void AudioListenerFrame::layoutFrame()
{
 AbstractAudioFrame::layoutFrame();
 QWidget* p;
 scrollLayout->addWidget(position);
 scrollLayout->addWidget(velocity);

 p = new QGroupBox(tr("Orientation"));
 QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
 p->setStyleSheet(gbStyleSheet);
 QVBoxLayout* pLayout;
 p->setLayout(pLayout = new QVBoxLayout); //(p, BoxLayout.Y_AXIS));
//   p.setBorder(BorderFactory.createCompoundBorder(
//           BorderFactory.createTitledBorder(tr("LabelOrientation")),
//           BorderFactory.createEmptyBorder(5, 5, 5, 5)));
 pLayout->addWidget(oriAtLabel);
 pLayout->addWidget(oriAt);
 pLayout->addWidget(oriUpLabel);
 pLayout->addWidget(oriUp);
 scrollLayout->addWidget(p);

 scrollLayout->addWidget(gain);

 p = new QGroupBox(tr("Meters Per Unit"));
 FlowLayout* pFlowLayout;
 p->setLayout(pFlowLayout = new FlowLayout());
//   p.setBorder(BorderFactory.createCompoundBorder(
//           BorderFactory.createTitledBorder(tr("LabelMetersPerUnit")),
//           BorderFactory.createEmptyBorder(5, 5, 5, 5)));
 metersPerUnit->setMinimumSize(JTextField(8).getPreferredSize());
 //metersPerUnit.setModel(
//           new SpinnerNumberModel(new Float(0f), new Float(0f), new Float(65536f), new Float(0.0001f)));
 metersPerUnit->setRange(0, 65535);
 metersPerUnit->setValue(0);
//   metersPerUnit.setEditor(new JSpinner.NumberEditor(metersPerUnit, "0.0000"));
 pFlowLayout->addWidget(metersPerUnit);
 pFlowLayout->addWidget(metersPerUnitLabel);
 scrollLayout->addWidget(p);

 QPushButton* ok = new QPushButton(tr("OK"));
// frame.getContentPane().add(ok = new JButton(rb.getString("ButtonOK")));
//   ok.addActionListener(new ActionListener() {
//       //@Override
//       /*public*/ void actionPerformed(ActionEvent e) {
//           okPressed(e);
//       }
//   });
 QVBoxLayout* centralWidgetLayout;
 if(frame->centralWidget() == NULL)
 {
  QWidget* centralWidget = new QWidget;
  centralWidgetLayout = new QVBoxLayout;
  centralWidget->setLayout(centralWidgetLayout);
  frame->setCentralWidget(centralWidget);
 }
 else
  centralWidgetLayout = (QVBoxLayout*)centralWidget()->layout();
 centralWidgetLayout->addWidget(ok);
}

//@Override
/*public*/ void AudioListenerFrame::resetFrame() {
   // Not required
}

/**
* Method to populate the Edit Listener frame with current values
*/
//@Override
/*public*/ void AudioListenerFrame::populateFrame(Audio* a)
{
 AbstractAudioFrame::populateFrame(a);
 AudioListener* l = (AudioListener*) a;
 position->setValue(l->getPosition());
 velocity->setValue(l->getVelocity());
 oriAt->setValue(l->getOrientation(Audio::AT));
 oriUp->setValue(l->getOrientation(Audio::UP));
 gain->setValue(l->getGain());
 metersPerUnit->setValue(l->getMetersPerUnit());
}

void  AudioListenerFrame::okPressed(ActionEvent* /*e*/)
{
 QString user = userName->text();
 if (user==("")) {
  user = "";
 }
 QString sName = sysName->text().toUpper();
 AudioListener* l;
 try
 {
  l = (AudioListener*) InstanceManager::audioManagerInstance()->provideAudio(sName);
  l->setUserName(user);
  l->setPosition(position->getValue());
  l->setVelocity(velocity->getValue());
  l->setOrientation(oriAt->getValue(), oriUp->getValue());
  l->setGain(gain->getValue());
  l->setMetersPerUnit(AbstractAudio::roundDecimal( metersPerUnit->value(), 4));

  // Notify changes
  model->fireTableDataChanged();

  this->setHidden(true);
 }
 catch (AudioException ex)
 {
//       JOptionPane.showMessageDialog(null, ex.getMessage(), rb.getString("AudioCreateErrorTitle"), JOptionPane.ERROR_MESSAGE);
 }
}
