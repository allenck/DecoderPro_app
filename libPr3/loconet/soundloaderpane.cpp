#include "soundloaderpane.h"
#include <QPushButton>
#include "jtextfield.h"
#include <QProgressBar>
#include "loaderengine.h"
#include "spjfile.h"
#include <QLabel>
#include "QBoxLayout"
#include "flowlayout.h"
#include "jseparator.h"
#include "fileutil.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>
#include <file.h>
#include "jfilechooser.h"

//SoundLoaderPane::SoundLoaderPane(QWidget *parent) :
//  LnPanel(parent)
//{
//}
/**
 * Pane for downloading .hex files
 *
 * @author	Bob Jacobsen Copyright (C) 2005
 * @version	$Revision: 28746 $
 */
// /*public*/ class LoaderPane extends jmri.jmrix.loconet.swing.LnPanel {

/**
 *
 */
///*private*/ static final long serialVersionUID = 3466057573583241795L;

// GUI member declarations
//static ResourceBundle res = ResourceBundle.getBundle("jmri.jmrix.loconet.soundloader.Loader");


/*public*/ QString SoundLoaderPane::getHelpTarget() {
    return "package.jmri.jmrix.loconet.soundloader.LoaderFrame";
}

/*public*/ QString SoundLoaderPane::getTitle() {
    return LnPanel::getTitle(tr("Download Sounds"));
}

/*public*/ SoundLoaderPane::SoundLoaderPane(QWidget *parent) :
  LnPanel(parent)
{

 inputFileName = new QLabel("");
 comment = new JTextField(32);
 status = new QLabel("");
 statusText = "";
 engine = NULL;
 chooser = NULL;

 QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout);//(this, BoxLayout.Y_AXIS));

 {
//  QWidget* p = new QWidget();
//  p.setLayout(new BoxLayout(p, BoxLayout.X_AXIS));
  QHBoxLayout* pLayout = new QHBoxLayout;
  selectButton = new QPushButton(tr("Select"));
//  b.addActionListener(new AbstractAction() {
//      /**
//       *
//       */
//      /*private*/ static final long serialVersionUID = 2498146136992279361L;

//      /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//          selectInputFile();
//      }
//  });
  connect(selectButton, SIGNAL(clicked()),this, SLOT(selectInputFile()));
  pLayout->addWidget(selectButton);
  pLayout->addWidget(new QLabel(tr("Input file: ")));
  pLayout->addWidget(inputFileName);

  thisLayout->addLayout(pLayout);
 }

 thisLayout->addWidget(new JSeparator());

 {
//  QWidget* p = new QWidget();
//  p.setLayout(new FlowLayout());
  FlowLayout* pLayout = new FlowLayout;

  readButton = new QPushButton(tr("Read"));
  readButton->setEnabled(false);
  readButton->setToolTip(tr("Button disabled until you select an input file name"));
  pLayout->addWidget(readButton);
//  readButton.addActionListener(new AbstractAction() {
//      /**
//       *
//       */
//      /*private*/ static final long serialVersionUID = -1408564712471319146L;

//      /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//          doRead();
//      }
//  });
  connect(readButton, SIGNAL(clicked()), this, SLOT(doRead()));

  thisLayout->addLayout(pLayout);
 }

 {
//     QWidget* p = new QWidget();
//     p.setLayout(new FlowLayout());
  QHBoxLayout* pLayout = new QHBoxLayout;

  pLayout->addWidget(new QLabel(tr("File label: ")));
  comment->setEnabled(false);
  pLayout->addWidget(comment);
  thisLayout->addLayout(pLayout);
 }

 thisLayout->addWidget(new JSeparator());

 {
//  QWidget* p = new QWidget();
//  p.setLayout(new FlowLayout());
  FlowLayout* pLayout = new FlowLayout;

  loadButton = new QPushButton(tr("Load"));
  loadButton->setEnabled(false);
  loadButton->setToolTip(tr("Button disabled until you read a data file"));
  pLayout->addWidget(loadButton);
//  loadButton.addActionListener(new AbstractAction() {
//      /**
//       *
//       */
//      /*private*/ static final long serialVersionUID = -1042657057160985067L;

//      /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//          doLoad();
//      }
//  });
  connect(loadButton, SIGNAL(clicked()), this, SLOT(doLoad()));

  thisLayout->addLayout(pLayout);

  thisLayout->addWidget(new JSeparator());

  bar = new QProgressBar();
  thisLayout->addWidget(bar);

  thisLayout->addWidget(new JSeparator());

  {
//   p = new QWidget();
//   p.setLayout(new FlowLayout());
   FlowLayout* pLayout = new FlowLayout;
   status->setText(tr("Click \"Select\" and pick a .spj file"));
   status->setAlignment(Qt::AlignLeft);
   pLayout->addWidget(status);
   thisLayout->addLayout(pLayout);
  }
 }
}


void SoundLoaderPane::selectInputFile()
{
 QString name = inputFileName->text();
 if (name==(""))
 {
  name = FileUtil::getUserFilesPath();
 }
 if (chooser == NULL)
 {
  chooser = new JFileChooser(name);
  chooser->setFileFilter("Sound files ( *.spj)");
 }
 inputFileName->setText("");  // clear out in case of failure
 int retVal = chooser->showOpenDialog(this);
 if (retVal != JFileChooser::APPROVE_OPTION)
 {
  return;  // give up if no file selected
 }
 inputFileName->setText(chooser->getSelectedFile()->getPath());
//    inputFileName->setText(QFileDialog::getOpenFileName(this, "Select Sound File", FileUtil::getUserFilesPath(),"Sound files ( *.spj)"));
 if(inputFileName->text() == "") return;

 readButton->setEnabled(true);
 readButton->setToolTip(tr("Click here to read the data file"));
 loadButton->setEnabled(false);
 loadButton->setToolTip(tr("Button disabled until you read a data file"));
 status->setText(tr("Click \"Read\" to read the file"));
}

void SoundLoaderPane::doRead()
{
 if (inputFileName->text() == "")
 {
//     JOptionPane.showMessageDialog(this, tr("ErrorNoInputFile"),
//             tr("ErrorTitle"),
//             JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(this, tr("Error"), tr("You must have selected an input file first"));
  return;
 }

 // force load, verify disabled in case read fails
 loadButton->setEnabled(false);
 loadButton->setToolTip(tr("Button disabled until you read a data file"));

 //try {
     file = new SpjFile(/*chooser.getSelectedFile()*/new File(inputFileName->text()));
     connect(file, SIGNAL(error(QString)), this, SLOT(onFileError(QString)));

     file->read();

// } catch (FileNotFoundException* f) {
//     JOptionPane.showMessageDialog(this, tr("ErrorFileNotFound"),
//             tr("ErrorTitle"),
//             JOptionPane.ERROR_MESSAGE);
//     return;
// } catch (IOException* f) {
//     JOptionPane.showMessageDialog(this, tr("ErrorIOError"),
//             tr("ErrorTitle"),
//             JOptionPane.ERROR_MESSAGE);
//     return;
// }

 // display contents
 comment->setText(file->getComment());

 // set up for next step
 loadButton->setEnabled(true);
 loadButton->setToolTip(tr("Click here to download to the decoder"));
 status->setText(tr("Click \"Download\" to start transfer"));

}

void SoundLoaderPane::doLoad()
{
 status->setText(tr("Downloading!"));
 readButton->setEnabled(false);
 readButton->setToolTip(tr("Button disabled during download"));
 loadButton->setEnabled(false);
 loadButton->setToolTip(tr("Button disabled during download"));
 selectButton->setEnabled(false);
 selectButton->setToolTip(tr("Button disabled during download"));


 // Create a loader to run in a separate thread
 // Override notify() method to do a swing-thread update of status field
 if (engine == NULL)
 {
  engine = new LoaderEngine(memo);
  engine ->setFile(file);
//     {
//         /*public*/ void notify(String s) {
//             javax.swing.SwingUtilities.invokeLater(new Notifier(s));
//         }
//     };
 }

// // start the download itself
// new Thread() {
//     /*public*/ void run() {
//         engine.runDownload(file);
//     }
// }.start();
 QThread* thread = new QThread;
 connect(engine, SIGNAL(error(QString)), this, SLOT(onFileError(QString)));
 connect(thread, SIGNAL(started()), engine, SLOT(process()));
 connect(engine, SIGNAL(finished()), thread, SLOT(quit()));
 connect(engine, SIGNAL(finished()), engine, SLOT(deleteLater()));
 connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
 connect(engine, SIGNAL(notify(QString)), this, SLOT(onNotified(QString)));
 connect(engine, SIGNAL(finished()), this, SLOT(onLoadFinished()));
 engine->moveToThread(thread);
 thread->start();
}

void SoundLoaderPane::onLoadFinished()
{
 selectButton->setEnabled(true);
}

///**
// * Define objects to update status JLabel in pane
// */
///*private*/ class Notifier implements Runnable {

//    /*public*/ Notifier(String msg) {
//        this.msg = msg;
//    }
//    String msg;

//    /*public*/ void run() {
//        status.setText(msg);
//    }
//}
void SoundLoaderPane::onNotified(QString s)
{
 status->setText(s);
}

void SoundLoaderPane::onFileError(QString s)
{
 status->setText(s);
}

/**
 * Get rid of any held resources
 */
/*public*/ void SoundLoaderPane::dispose()
{
 if (file != NULL)
 {
  file->dispose();
 }
 file = NULL;  // not for GC, this flags need to reinit

 if (engine != NULL)
 {
  engine->dispose();
 }
 engine = NULL;  // not for GC, this flags need to reinit
}
