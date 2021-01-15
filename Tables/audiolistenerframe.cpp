#include "audiolistenerframe.h"
#include <QLabel>
#include <QBoxLayout>
#include "flowlayout.h"
#include "jspinner.h"
#include "spinnernumbermodel.h"
#include <QPushButton>
#include "audiolistener.h"
#include "audiotableaction.h"
#include "jtextfield.h"
#include "instancemanager.h"
#include "abstractaudio.h"
#include <QScrollArea>
#include "joptionpane.h"
#include "borderfactory.h"

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

  /*private*/ /*final*/ /*static*/ QString AudioListenerFrame::PREFIX = "IAL";

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
 metersPerUnit = new JSpinner();
 metersPerUnitLabel = new QLabel(tr("meters/unit"));

 layoutFrame();
}

//@Override
/*public*/ void AudioListenerFrame::layoutFrame()
{
 AbstractAudioFrame::layoutFrame();
 JPanel* p;
 scrollLayout->addWidget(position);
 scrollLayout->addWidget(velocity);

 p = new JPanel();
 QVBoxLayout* pLayout;
 p->setLayout(pLayout = new QVBoxLayout); //(p, BoxLayout.Y_AXIS));
   p->setBorder(BorderFactory::createCompoundBorder(
           BorderFactory::createTitledBorder(tr("Orientation")),
           BorderFactory::createEmptyBorder(5, 5, 5, 5)));
 pLayout->addWidget(oriAtLabel);
 pLayout->addWidget(oriAt);
 pLayout->addWidget(oriUpLabel);
 pLayout->addWidget(oriUp);
 scrollLayout->addWidget(p);

 scrollLayout->addWidget(gain);

 p = new JPanel();
 FlowLayout* pFlowLayout;
 p->setLayout(pFlowLayout = new FlowLayout());
 p->setBorder(BorderFactory::createCompoundBorder(
           BorderFactory::createTitledBorder(tr("Meters Per Unit")),
           BorderFactory::createEmptyBorder(5, 5, 5, 5)));
 metersPerUnit->setMinimumSize(JTextField(8).getPreferredSize());
 metersPerUnit->setModel(
           new SpinnerNumberModel(0., 0., 65536., 0.0001f));
 //metersPerUnit->setEditor(new JSpinner.NumberEditor(metersPerUnit, "0.0000"));
 pFlowLayout->addWidget(metersPerUnit);
 pFlowLayout->addWidget(metersPerUnitLabel);
 scrollLayout->addWidget(p);

 JButton* apply;
 p->layout()->addWidget(apply = new JButton(tr("Apply")));
// apply.addActionListener((ActionEvent e) -> {
 connect(apply, &JButton::clicked, [=]{
     applyPressed(/*e*/);
 });
 JButton* ok = new JButton(tr("OK"));
// frame.getContentPane().add(ok = new JButton(rb.getString("ButtonOK")));
//   ok.addActionListener(new ActionListener() {
//       //@Override
//       /*public*/ void actionPerformed(ActionEvent e) {
 connect(ok, &JButton::clicked, [=]{
           applyPressed(/*e*/);
           frame->dispose();
//       }
 });
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

void  AudioListenerFrame::applyPressed(JActionEvent* /*e*/)
{
 QString sName = sysName->text();
 if (entryError(sName, PREFIX, "$")) { // no index for AudioListener
     return;
 }
 QString user = userName->text();
 if (user == ("")) {
     user = QString();
 }
 AudioListener* l;
 try
 {
  l = (AudioListener*) ((AudioManager*)InstanceManager::getDefault("AudioManager"))->provideAudio(sName);
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
  JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Error creating Audio object"), JOptionPane::ERROR_MESSAGE);
 }
}

/*public*/ QString AudioListenerFrame::getClassName()
{
 return "jmri.jmrit.audio.swing.AudioListenerFrame";
}
