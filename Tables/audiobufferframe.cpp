#include "audiobufferframe.h"
#include <QLabel>
#include "jtextfield.h"
#include <QCheckBox>
#include <QSlider>
#include <QPushButton>
#include <QSpinBox>
#include "audiobuffer.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include <QPushButton>
#include "audiomanager.h"
#include "instancemanager.h"
#include "audiotableaction.h"
#include "fileutil.h"
#include <QFileDialog>

//AudioBufferFrame::AudioBufferFrame(QWidget *parent) :
//  AbstractAudioFrame(parent)
//{
//}
/**
 * Defines a GUI to edit AudioBuffer objects
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
///*public*/ class AudioBufferFrame extends AbstractAudioFrame {

/**
 *
 */
//    /*private*/ static final long serialVersionUID = 5309874433054867893L;

//    AudioWaveFormPanel waveForm = new AudioWaveFormPanel();
int AudioBufferFrame::counter = 1;

//@SuppressWarnings("OverridableMethodCallInConstructor")
/*public*/ AudioBufferFrame::AudioBufferFrame(QString title, AudioTableDataModel* model, QWidget *parent)
 : AbstractAudioFrame(title, model, parent)
{
 //super(title, model);
 log = new Logger("AudioBufferFrame");
 counter = 1;
 lock = new QObject();
 urlLabel = new QLabel(tr("URL"));
 url = new JTextField(40);
 buttonBrowse = new QPushButton(tr("Browse"));
 stream = new QCheckBox(tr("Stream"));
//    QLabel* formatLabel = new JLabel(tr("LabelFormat"));
//    JTextField format = new JTextField(20);
 loopStartLabel = new QLabel(tr("Loop Start"));
 loopStart = new QSpinBox();
 loopEndLabel = new QLabel(tr("Loop End"));
 loopEnd = new QSpinBox();

 layoutFrame();

 // For now, disable editing of loop points
 // TODO: enable editing of looping points
 loopStart->setEnabled(false);
 loopStartLabel->setEnabled(false);
 loopEnd->setEnabled(false);
 loopEndLabel->setEnabled(false);
}

//@Override
/*public*/ void AudioBufferFrame::layoutFrame()
{
 AbstractAudioFrame::layoutFrame();
 QGroupBox* p;

 QWidget* p2;
 p = new QGroupBox(tr("Sound Sample"));
 QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
 p->setStyleSheet(gbStyleSheet);
 QVBoxLayout* pLayout;
 p->setLayout(pLayout = new QVBoxLayout); //(p, BoxLayout.Y_AXIS));
//    p.setBorder(BorderFactory.createCompoundBorder(
//            BorderFactory.createTitledBorder(tr("LabelSample")),
//            BorderFactory.createEmptyBorder(5, 5, 5, 5)));
 p2 = new QWidget();
 FlowLayout* p2Layout;
 p2->setLayout(p2Layout = new FlowLayout());
 p2Layout->addWidget(urlLabel);
 p2Layout->addWidget(url);
// buttonBrowse.addActionListener(new ActionListener() {
//    //@Override
//     /*public*/ void actionPerformed(ActionEvent e) {
//         browsePressed(e);
//     }
// });
 connect(buttonBrowse, SIGNAL(clicked()), this, SLOT(browsePressed()));
 p2Layout->addWidget(buttonBrowse);
 pLayout->addWidget(p2);
 p2 = new QWidget();
 p2->setLayout(p2Layout = new FlowLayout());
 p2Layout->addWidget(stream);
 pLayout->addWidget(p2);
//        p2 = new QWidget(); p2.setLayout(new FlowLayout());
//        p2Layout->addWidget(formatLabel);
//        p2Layout->addWidget(format);
//        p.add(p2);
 scrollLayout->addWidget(p);

//        p = new QWidget();
//        p.setBorder(BorderFactory.createCompoundBorder(
//                        BorderFactory.createTitledBorder("Waveforms"),
//                        BorderFactory.createEmptyBorder(5, 5, 5, 5)));
//
//        QLabel* label = new JLabel("Whole sample");
//        label.setUI(new VerticalLabelUI());
//        p.add(label);
//
//        waveForm.setPreferredSize(new Dimension(400, 120));
//        p.add(waveForm);
//
//        label = new JLabel("Loop-point detail");
//        label.setUI(new VerticalLabelUI());
//        p.add(label);
//
//        AudioWaveFormPanel waveFormLoop = new AudioWaveFormPanel();
//        waveFormLoop.setPreferredSize(new Dimension(80, 120));
//        p.add(waveFormLoop);
//
//        main.add(p);
//
 p = new QGroupBox(tr("Loop Points"));
 p->setStyleSheet(gbStyleSheet);
 FlowLayout* pFlowLayout;
 p->setLayout(pFlowLayout = new FlowLayout());
//    p.setBorder(BorderFactory.createCompoundBorder(
//            BorderFactory.createTitledBorder(tr("LabelLoopPoints")),
//            BorderFactory.createEmptyBorder(5, 5, 5, 5)));
 pFlowLayout->addWidget(loopStartLabel);
 loopStart->setMinimumSize(JTextField(8).getPreferredSize());
// loopStart->setModel(
//            new SpinnerNumberModel((0), (0), (Long.MAX_VALUE), (1)));
 loopStart->setRange(0, 65535);
 loopStart->setValue(0);
//    loopStart->addChangeListener(new ChangeListener() {
//       //@Override
//        /*public*/ void stateChanged(ChangeEvent e) {
//            loopEnd->setValue(
//                    ( loopStart->getValue()
//                    <  loopEnd->getValue())
//                            ? loopEnd->getValue()
//                            : loopStart->getValue());
//        }
//    });
 connect(loopStart, SIGNAL(valueChanged(int)), this, SLOT(On_loopStart_valueChanged()));
pFlowLayout->addWidget(loopStart);
pFlowLayout->addWidget(loopEndLabel);
loopEnd->setMinimumSize(JTextField(8).getPreferredSize());
//    loopEnd->setModel(
//            new SpinnerNumberModel((0), (0), (Long.MAX_VALUE), (1)));
loopEnd->setRange(0, 65535);
loopEnd->setValue(0);
//    loopEnd->addChangeListener(new ChangeListener() {
//       //@Override
//        /*public*/ void stateChanged(ChangeEvent e) {
//            loopStart->setValue(
//                    ( loopEnd->getValue()
//                    <  loopStart->getValue())
//                            ? loopEnd->getValue()
//                            : loopStart->getValue());
//        }
//    });
 connect(loopEnd, SIGNAL(valueChanged(int)), this, SLOT(On_loopEnd_valueChanged()));
 pFlowLayout->addWidget(loopEnd);
 scrollLayout->addWidget(p);

 QPushButton* ok = new QPushButton(tr("OK"));

 QVBoxLayout* centralWidgetLayout;
 if(frame->centralWidget() == NULL)
 {
  QWidget* centralWidget = new QWidget;
  centralWidget->setLayout(centralWidgetLayout = new QVBoxLayout);
  setCentralWidget(centralWidget);
 }
 else
  centralWidgetLayout = (QVBoxLayout*)frame->centralWidget()->layout();

//    frame.getContentPane().add(ok = new JButton(rb.getString("ButtonOK")));
//    ok.addActionListener(new ActionListener() {
//       //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            okPressed(e);
//        }
//    });
 centralWidgetLayout->addWidget(ok, 0, Qt::AlignHCenter);
 connect(ok , SIGNAL(clicked()), this, SLOT(okPressed()));
}

void AudioBufferFrame::On_loopStart_valueChanged()
{
 loopEnd->setValue(
         ( loopStart->value()
         <  loopEnd->value())
                 ? loopEnd->value()
                 : loopStart->value());

}

void AudioBufferFrame::On_loopEnd_valueChanged()
{
 loopStart->setValue(
         ( loopEnd->value()
         <  loopStart->value())
                 ? loopEnd->value()
                 : loopStart->value());

}

/**
 * Method to populate the Edit Buffer frame with default values
 */
//@Override
/*public*/ void AudioBufferFrame::resetFrame()
{
 /*synchronized (lock)*/
 {
  sysName->setText("IAB" + QString::number(counter++));
 }
 userName->setText("");
 url->setText("");
//        format.setText(NULL);
 stream->setChecked(false);
 stream->setEnabled(false); //(true);
 loopStart->setValue((0));
 loopEnd->setValue((0));

 this->_newBuffer = true;
}

/**
 * Method to populate the Edit Buffer frame with current values
 */
//@Override
/*public*/ void AudioBufferFrame::populateFrame(Audio* a)
{
 AbstractAudioFrame::populateFrame(a);
 AudioBuffer* b = (AudioBuffer*) a;
 url->setText(b->getURL());
//        format.setText(b->toString());
 stream->setChecked(b->isStreamed());
 stream->setEnabled(false); //(!b.isStreamedForced());
 loopStart->setValue(b->getStartLoopPoint());
 loopEnd->setValue(b->getEndLoopPoint());
 loopStart->setEnabled(true);
 loopStartLabel->setEnabled(true);
 loopEnd->setEnabled(true);
 loopEndLabel->setEnabled(true);

 this->_newBuffer = false;
}

void AudioBufferFrame::browsePressed(JActionEvent* /*e*/)
{
//    if (fileChooser == NULL) {
//        fileChooser = new JFileChooser("resources" + File.separator + "sounds" + File.separator);
//        FileChooserFilter audioFileFilter = new FileChooserFilter("Audio Files (*.wav)");
//        audioFileFilter.addExtension("wav");
//        fileChooser.setFileFilter(audioFileFilter);
//    }

//    // Show dialog
//    fileChooser.rescanCurrentDirectory();
//    int retValue = fileChooser.showOpenDialog(this);
 this->setCursor(Qt::WaitCursor);
 QString selectedFilename = QFileDialog::getOpenFileName(this,tr("Select Audio File"),FileUtil::getProgramPath()+ "resources" + File::separator + "sounds" + File::separator, "Audio Files (*.wav)" );
 this->setCursor(Qt::ArrowCursor);
 // Process selection
 //if (retValue == JFileChooser.APPROVE_OPTION)
 if(selectedFilename.length() > 0)
 {
  //File file = fileChooser.getSelectedFile();
  File* file = new File(selectedFilename);
  QString fileName = FileUtil::getPortableFilename(file);
  if (url->text()!=(fileName))
  {
   url->setText(fileName);
//                try {
//                    WaveFileReader wfr = new WaveFileReader(FileUtil.getExternalFilename(fileName));
//                    JOptionPane.showMessageDialog(NULL, wfr.toString(), wfr.toString(), JOptionPane.INFORMATION_MESSAGE);
//                } catch (AudioException ex) {
//                    JOptionPane.showMessageDialog(NULL, ex.getMessage(), tr("TitleReadError"), JOptionPane.ERROR_MESSAGE);
//                }
        }
    }
}

void AudioBufferFrame::okPressed(JActionEvent* /*e*/)
{
 QString user = userName->text();
 if (user==(""))
 {
  user = "";
 }
 QString sName = sysName->text().toUpper();
 AudioBuffer* b;
 try
 {
  AudioManager* am = ((AudioManager*)InstanceManager::getDefault("AudioManager"));
  b = (AudioBuffer*) am->provideAudio(sName);
  if (b == NULL)
  {
   throw new AudioException("Problem creating buffer");
  }
  if (_newBuffer && am->getByUserName(user) != NULL)
  {
   am->deregister(b);
   counter--;
   throw new AudioException("Duplicate user name - please modify");
   }
   b->setUserName(user);
   b->setStreamed(stream->isChecked());
   if (_newBuffer || b->getURL()!=(url->text()))
   {
    b->setURL(url->text());
    log->debug("After load, end loop point = " + QString::number(b->getEndLoopPoint()));
       //b.setStartLoopPoint(loopStart->getValue());
       //b.setEndLoopPoint(loopEnd->getValue());
   }
   else
   {
    if (b->getURL()!=(url->text()))
    {
     log->debug("Sound changed from: " + b->getURL());
      b->setURL(url->text());
    }
   }

   // Update streaming checkbox if necessary
   stream->setChecked(b->isStreamed());
   stream->setEnabled(false); //(!b.isStreamedForced());

   // Notify changes
   model->fireTableDataChanged();
   this->setHidden(true);
 } catch (AudioException ex)
 {
//   JOptionPane.showMessageDialog(NULL, ex.getMessage(), rb.getString("AudioCreateErrorTitle"), JOptionPane.ERROR_MESSAGE);
 }
}
/*public*/ QString AudioBufferFrame::getClassName()
{
 return "jmri.jmrit.audio.swing.AudioBufferFrame";
}
