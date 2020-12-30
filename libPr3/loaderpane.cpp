#include "loaderpane.h"
#include <QLabel>
#include "jtextfield.h"
#include <QRadioButton>
#include <QPushButton>
#include <QProgressBar>
#include <QBoxLayout>
#include "flowlayout.h"
#include <QButtonGroup>
#include "jseparator.h"
#include <QFileDialog>
#include "fileutil.h"
#include <QMessageBox>
#include "loconetsystemconnectionmemo.h"
#include "memorycontents.h"
#include "file.h"
#include "jfilechooser.h"

LoaderPane::LoaderPane(QWidget *parent) :
  LnPanel(parent)
{
 log = new Logger("LoaderPane");
 inputFileName = new QLabel("");

 bootload = new JTextField();
 mfg = new JTextField();

 developer = new JTextField();
 product = new JTextField();
 hardware = new JTextField();
 software = new JTextField();
 delay = new JTextField();
 eestart = new JTextField();

 checkhardwareno = new QRadioButton(tr("Don't check hardware version"));
 checkhardwareexact = new QRadioButton(tr("Require hardware version exact match"));
 checkhardwaregreater = new QRadioButton(tr("Accept later hardware versions"));
 hardgroup = new QButtonGroup();

 checksoftwareno = new QRadioButton(tr("Don't check software version"));
 checksoftwareless = new QRadioButton(tr("Only overwrite earlier software versions"));
 softgroup = new QButtonGroup();

 address24bit = new QRadioButton(tr("24 bit"));
 address16bit = new QRadioButton(tr("16 bit"));
 addressSizeButtonGroup = new QButtonGroup();

 status = new QLabel("");

 inputContent = new MemoryContents();

}
/**
 * Pane for downloading .hex files and .dmf files to those LocoNet devices which
 * support firmware updates via LocoNet IPL messages.
 *
 * This version relies on the file contents interpretation mechanisms built into
 * the readHex() methods found in class jmri.jmrit.MemoryContents to
 * automatically interpret the file's addressing type - either 16-bit or 24-bit
 * addressing. The interpreted addressing type is reported in the pane after a
 * file is read. The user cannot select the addressing type.
 *
 * This version relies on the file contents checking mechanisms built into the
 * readHex() methods found in class jmri.jmrit.MemoryContents to check for a
 * wide variety of possible issues in the contents of the firmware update file.
 * Any exception thrown by at method is used to select an error message to
 * display in the status line of the pane.
 *
 * @author	Bob Jacobsen Copyright (C) 2005
 * @author B. Milhaupt Copyright (C) 2013, 2014
 * @version	$Revision: 28746 $
 */
///*public*/ class LoaderPane extends jmri.jmrix.loconet.swing.LnPanel
//        implements ActionListener {

// GUI member declarations
/**
 *
 */
// /*private*/ static final long serialVersionUID = 6862502901108992179L;


/*private*/ /*static*/ /*final*/ int LoaderPane::PXCT1DOWNLOAD = 0x40;
/*static*/ int LoaderPane::PXCT2SETUP = 0x00;
/*static*/ int LoaderPane::PXCT2SENDADDRESS = 0x10;
/*static*/ int LoaderPane::PXCT2SENDDATA = 0x20;
/*static*/ int LoaderPane::PXCT2VERIFYDATA = 0x30;
/*static*/ int LoaderPane::PXCT2ENDOPERATION = 0x40;


// some constant string declarations
/*private*/  /*static final*/ QString LoaderPane::MIN_VALUE_ZERO = "0";
/*private*/  /*static final*/ QString LoaderPane::MIN_EESTART_VALUE = "8";
/*private*/  /*static final*/ QString LoaderPane::MAX_VALUE_255 = "255";
/*private*/  /*static final*/ QString LoaderPane::MAX_VALUE_65535 = "65535";
/*private*/  /*static final*/ QString LoaderPane::MAX_EESTART_VALUE = "FFFFF8";
/*private*/  /*static final*/ QString LoaderPane::MIN_DELAY_VALUE = "5";
/*private*/  /*static final*/ QString LoaderPane::MAX_DELAY_VALUE = "500";

///*public*/ LoaderPane() {
//}

//@Override
/*public*/ QString LoaderPane::getHelpTarget() {
    return "package.jmri.jmrix.loconet.downloader.LoaderFrame";
}

//@Override
/*public*/ QString LoaderPane::getTitle() {
    return LnPanel::getTitle(tr("Firmware Downloader"));
}

//@Override
/*public*/ void LoaderPane::initComponents(LocoNetSystemConnectionMemo* memo)
{
 LnPanel::initComponents(memo);
 QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout); //(this, BoxLayout.Y_AXIS));
 {
  //resize(600, 600);
  /* Create panels for displaying a filename and for providing a file
   * seleciton pushbutton
   */
  //inputFileNamePanel = new QWidget();
  FlowLayout* inputFileNamePanelLayout = new FlowLayout();
  //inputFileNamePanel->setLayout(inputFileNamePanelLayout =new FlowLayout());
  QLabel* l = new QLabel(tr("Input file:"));
  inputFileLabelWidth = l->minimumSize().width();
//  l->setAlignment(Qt::AlignHCenter);
  inputFileNamePanelLayout->addWidget(l);
//  inputFileNamePanelLayout->addWidget(new Box.Filler(new java.awt.Dimension(5, 20),
//          new java.awt.Dimension(5, 20),
//          new java.awt.Dimension(5, 20)));
  inputFileNamePanelLayout->addWidget(inputFileName);

  thisLayout->addLayout(inputFileNamePanelLayout);

  //QWidget* p = new QWidget();
  FlowLayout* pLayout = new FlowLayout;
  //p->setLayout(pLayout = new FlowLayout());
  QPushButton* selectButton = new QPushButton(tr("Select"));
//  selectButton.addActionListener(new ActionListener() {
//      @Override
//      /*public*/ void actionPerformed(ActionEvent e) {
//          inputContent = new MemoryContents();
//          setDefaultFieldValues();
//          updateDownloadVerifyButtons();
//          selectInputFile();
//          doRead();
//      }
//  });
  connect(selectButton, SIGNAL(clicked()), this, SLOT(on_selectButton_clicked()));
  pLayout->addWidget(selectButton);

  thisLayout->addLayout(pLayout);
 }

 {
  // Create a panel for displaying the addressing type, via radio buttons
//  QWidget* p = new QWidget();
  QHBoxLayout* pLayout = new QHBoxLayout;
//  p->setLayout(pLayout = new QHBoxLayout); //(p, BoxLayout.X_AXIS));
  QLabel* l = new QLabel(tr("File format: ") + " ");
  l->setEnabled(false);
  pLayout->addWidget(l);
  pLayout->addWidget(address16bit);
  pLayout->addWidget(address24bit);
  addressSizeButtonGroup->addButton(address16bit);
  addressSizeButtonGroup->addButton(address24bit);
  //addressSizeButtonGroup->clearSelection();
  address16bit->setEnabled(false);
  address24bit->setEnabled(false);
  thisLayout->addLayout(pLayout);
 }

 setDefaultFieldValues();

 thisLayout->addWidget(new JSeparator());

 {
     // create a panel for displaying/modifying the bootloader version
//  QWidget* p = new QWidget();
  QHBoxLayout* pLayout = new QHBoxLayout;
//  p->setLayout(pLayout = new QHBoxLayout); //(p, BoxLayout.X_AXIS));
  pLayout->addWidget(new QLabel(tr("Bootloader Version Number:") + " "));
  pLayout->addWidget(bootload);
  bootload->setToolTip(tr("Value between %1 and %2").arg(
          MIN_VALUE_ZERO).arg( MAX_VALUE_255));
//  bootload.addFocusListener(new FocusListener() {
//      @Override
//      /*public*/ void focusGained(FocusEvent e) {
//      }

//      @Override
//      /*public*/ void focusLost(FocusEvent e) {
//          intParameterIsValid(bootload, 0, 255);
//          updateDownloadVerifyButtons();
//      }
//  });
  connect(bootload, SIGNAL(leaveField()), this, SLOT(on_bootload_focusLost()));
  thisLayout->addLayout(pLayout);
 }

 {
  // create a panel for displaying/modifying the manufacturer number
//  QWidget* p = new QWidget();
  QHBoxLayout* pLayout = new QHBoxLayout;
//  p->setLayout(pLayout = new QHBoxLayout); //(p, BoxLayout.X_AXIS));
  pLayout->addWidget(new QLabel(tr("Manufacturer Number:") + " "));
  mfg->setToolTip(tr("Value between %1 and %2").arg(
          MIN_VALUE_ZERO).arg( MAX_VALUE_255));
  pLayout->addWidget(mfg);
//  mfg.addFocusListener(new FocusListener() {
//      @Override
//      /*public*/ void focusGained(FocusEvent e) {
//      }

//      @Override
//      /*public*/ void focusLost(FocusEvent e) {
//          intParameterIsValid(mfg, 0, 255);
//          updateDownloadVerifyButtons();
//      }
//  });
  connect(mfg, SIGNAL(leaveField()), this, SLOT(on_mfg_focusLost()));
  thisLayout->addLayout(pLayout);
 }

 {
  // create a panel for displaying/modifying the developer number
//  QWidget* p = new QWidget();
  QHBoxLayout* pLayout = new QHBoxLayout;
//  p->setLayout(pLayout = new QHBoxLayout); //(p, BoxLayout.X_AXIS));
  pLayout->addWidget(new QLabel(tr("Developer Number:")
          + " ")); //NOI18N
  developer->setToolTip(tr("Value between %1 and %2").arg(
          MIN_VALUE_ZERO).arg( MAX_VALUE_255));
  pLayout->addWidget(developer);
//  developer->addFocusListener(new FocusListener() {
//      @Override
//      /*public*/ void focusGained(FocusEvent e) {
//      }

//      @Override
//      /*public*/ void focusLost(FocusEvent e) {
//          intParameterIsValid(developer, 0, 255);
//          updateDownloadVerifyButtons();
//      }
//  });
  connect(developer, SIGNAL(leaveField()), this, SLOT(on_developer_focusLost()));
  thisLayout->addLayout(pLayout);
 }

 {
  // create a panel for displaying/modifying the product number
//  QWidget* p = new QWidget();
  QHBoxLayout* pLayout = new QHBoxLayout;
//  p->setLayout(pLayout = new QHBoxLayout); //(p, BoxLayout.X_AXIS));
  pLayout->addWidget(new QLabel(tr("Product Code:") + " "));
  product->setToolTip(tr("Value between %1 and %2").arg(
          MIN_VALUE_ZERO).arg( MAX_VALUE_65535));
  pLayout->addWidget(product);
//  product->addFocusListener(new FocusListener() {
//      @Override
//      /*public*/ void focusGained(FocusEvent e) {
//      }

//      @Override
//      /*public*/ void focusLost(FocusEvent e) {
//          intParameterIsValid(product, 0, 65535);
//          updateDownloadVerifyButtons();
//      }
//  });
  connect(product, SIGNAL(leaveField()), this, SLOT(on_product_focusLost()));
  thisLayout->addLayout(pLayout);
 }

 {
  // create a panel for displaying/modifying the hardware version
//  QWidget* p = new QWidget();
  QHBoxLayout* pLayout = new QHBoxLayout;
//  p->setLayout(pLayout = new QHBoxLayout); //(p, BoxLayout.X_AXIS));
  hardware->setToolTip(tr("Value between %1 and %2").arg(
          MIN_VALUE_ZERO).arg( MAX_VALUE_255));
  pLayout->addWidget(new QLabel(tr("Hardware Version Number:") + " "));
  pLayout->addWidget(hardware);
//  hardware->addFocusListener(new FocusListener() {
//      @Override
//      /*public*/ void focusGained(FocusEvent e) {
//      }

//      @Override
//      /*public*/ void focusLost(FocusEvent e) {
//          intParameterIsValid(hardware, 0, 255);
//          updateDownloadVerifyButtons();
//      }
//  });
  connect(hardware, SIGNAL(leaveField()), this, SLOT(on_hardware_focusLost()));

  thisLayout->addLayout(pLayout);
 }

 {
  // create a panel for displaying/modifying the hardware options
//  QWidget* p = new QWidget();
  QVBoxLayout* pLayout = new QVBoxLayout;
//  p->setLayout(pLayout = new FlowLayout); //(p, BoxLayout.Y_AXIS));
  pLayout->addWidget(checkhardwareno);
  pLayout->addWidget(checkhardwareexact);
  pLayout->addWidget(checkhardwaregreater);

  hardgroup->addButton(checkhardwareno);
  hardgroup->addButton(checkhardwareexact);
  hardgroup->addButton(checkhardwaregreater);

//            checkhardwareno.addFocusListener(new FocusListener() {
//                @Override /*public*/ void focusGained(FocusEvent e) {
//                }
//                @Override /*public*/ void focusLost(FocusEvent e) {
//                    updateDownloadVerifyButtons();
//                }
//            });
//            checkhardwareexact.addFocusListener(new FocusListener() {
//                @Override /*public*/ void focusGained(FocusEvent e) {
//                }
//                @Override /*public*/ void focusLost(FocusEvent e) {
//                    updateDownloadVerifyButtons();
//                }
//            });
//            checkhardwaregreater.addFocusListener(new FocusListener() {
//                @Override /*public*/ void focusGained(FocusEvent e) {
//                }
//                @Override /*public*/ void focusLost(FocusEvent e) {
//                    updateDownloadVerifyButtons();
//                }
//            });
  //checkhardwareno->addActionListener(this);
  connect(checkhardwareno, SIGNAL(clicked()), this, SLOT(actionPerformed()));
  //checkhardwareexact->addActionListener(this);
  connect(checkhardwareexact, SIGNAL(clicked()), this, SLOT(actionPerformed()));
  //checkhardwaregreater->addActionListener(this);
  connect(checkhardwaregreater, SIGNAL(clicked()), this, SLOT(actionPerformed()));
  thisLayout->addLayout(pLayout);
 }

 {
  // create a panel for displaying/modifying the software version
//  QWidget* p = new QWidget();
  QHBoxLayout* pLayout = new QHBoxLayout;
//  p->setLayout(pLayout = new QHBoxLayout); //(p, BoxLayout.X_AXIS));
  pLayout->addWidget(new QLabel(tr("Software Version Number:") + " "));
  software->setToolTip(tr("Value between %1 and %2").arg(
          MIN_VALUE_ZERO).arg( MAX_VALUE_255));
  pLayout->addWidget(software);
//  software.addFocusListener(new FocusListener() {
//      @Override
//      /*public*/ void focusGained(FocusEvent e) {
//      }

//      @Override
//      /*public*/ void focusLost(FocusEvent e) {
//          intParameterIsValid(software, 0, 255);
//          updateDownloadVerifyButtons();
//      }
//  });
  connect(software, SIGNAL(leaveField()), this, SLOT(on_software_focusLost()));

  thisLayout->addLayout(pLayout);
 }

 {
  // create a panel for displaying/modifying the software options
//  QWidget* p = new QWidget();
  FlowLayout* pLayout  = new FlowLayout;
//  p->setLayout(pLayout = new FlowLayout); //(p, BoxLayout.Y_AXIS));
  pLayout->addWidget(checksoftwareno);
  pLayout->addWidget(checksoftwareless);

  softgroup->addButton(checksoftwareno);
  softgroup->addButton(checksoftwareless);

  //checksoftwareno->addActionListener(this);
  connect(checksoftwareno, SIGNAL(clicked()), this, SLOT(actionPerformed()));
  //checksoftwareless->addActionListener(this);
  connect(checksoftwareless, SIGNAL(clicked()), this, SLOT(actionPerformed()));

  thisLayout->addLayout(pLayout);
 }

 {
  // create a panel for displaying/modifying the delay value
//  QWidget* p = new QWidget();
  QHBoxLayout* pLayout = new QHBoxLayout;
//  p->setLayout(pLayout = new QHBoxLayout); //(p, BoxLayout.X_AXIS));
  pLayout->addWidget(new QLabel(tr("Delay (msec):") + " "));
  delay->setToolTip(tr("Value between %1 and %2").arg(
                        MIN_DELAY_VALUE).arg( MAX_DELAY_VALUE));

  pLayout->addWidget(delay);
//  delay.addFocusListener(new FocusListener() {
//      @Override
//      /*public*/ void focusGained(FocusEvent e) {
//      }

//      @Override
//      /*public*/ void focusLost(FocusEvent e) {
//          intParameterIsValid(hardware,
//                  Integer.parseInt(MIN_DELAY_VALUE),
//                  Integer.parseInt(MAX_DELAY_VALUE));
//          updateDownloadVerifyButtons();
//      }
//  });
  connect(delay, SIGNAL(leaveField()), this, SLOT(on_delay_focusLost()));

  thisLayout->addLayout(pLayout);
 }

 {
  // create a panel for displaying/modifying the EEPROM start address
//  QWidget* p = new QWidget();
  QHBoxLayout* pLayout = new QHBoxLayout;
  //  p->setLayout(pLayout = new QHBoxLayout); //(p, BoxLayout.X_AXIS));
  pLayout->addWidget(new QLabel(tr("Start of EEPROM addresses (hex):") + " "));
  eestart->setToolTip(tr("Value between %1 and %2").arg(
          MIN_EESTART_VALUE).arg( MAX_EESTART_VALUE));
  pLayout->addWidget(eestart);
//  eestart->addFocusListener(new FocusListener() {
//      @Override
//      /*public*/ void focusGained(FocusEvent e) {
//      }

//      @Override
//      /*public*/ void focusLost(FocusEvent e) {
//          updateDownloadVerifyButtons();
//      }
//  });
  connect(eestart, SIGNAL(leaveField()), this, SLOT(updateDownloadVerifyButtons()));

  thisLayout->addLayout(pLayout);
 }

 thisLayout->addWidget(new JSeparator());

 {
  // create a panel for the upload, verify, and abort buttons
//  QWidget* p = new QWidget();
  FlowLayout* pLayout = new FlowLayout;
//  p->setLayout(pLayout = new FlowLayout());

  loadButton = new QPushButton(tr("Load"));
  loadButton->setEnabled(false);
  loadButton->setToolTip(tr("Button disabled until you read a data file"));
  pLayout->addWidget(loadButton);
//  loadButton->addActionListener(new ActionListener() {
//      @Override
//      /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//          doLoad();
//      }
//  });
  connect(loadButton, SIGNAL(clicked()), this, SLOT(doLoad()));

  verifyButton = new QPushButton(tr("Verify"));
  verifyButton->setEnabled(false);
  verifyButton->setToolTip(tr("Button disabled until you read a data file"));
  pLayout->addWidget(verifyButton);
//  verifyButton->addActionListener(new ActionListener() {
//      @Override
//      /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//          doVerify();
//      }
//  });
  connect(verifyButton, SIGNAL(clicked()), this, SLOT(doVerify()));

//  thisLayout->addLayout(pLayout);

  abortButton = new QPushButton(tr("Abort"));
  abortButton->setEnabled(false);
  abortButton->setToolTip(tr("Button disabled until a download or verify operation"));
  pLayout->addWidget(abortButton);
//  abortButton.addActionListener(new ActionListener() {
//      @Override
//      /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//          setOperationAborted(true);
//      }
//  });
  connect(abortButton,SIGNAL(clicked()), this, SLOT(setOperationAborted()));

  thisLayout->addLayout(pLayout);

  thisLayout->addWidget(new JSeparator());

  // create progress bar
  bar = new QProgressBar(/*0, 100*/);
  bar->setMinimum(0);
  bar->setMaximum(100);
  //bar->setStringPainted(true);
  thisLayout->addWidget(bar);

  thisLayout->addWidget(new JSeparator());

  {
   // create a panel for displaying a status message
//   p = new QWidget();
   FlowLayout* pLayout = new FlowLayout();
//   p->setLayout(pLayout = new FlowLayout());
   status->setText(tr("Click Select to pick the firmware file"));
   status->setAlignment(Qt::AlignLeft);
   pLayout->addWidget(status);
   thisLayout->addLayout(pLayout);
  }
 }
}

void LoaderPane::on_selectButton_clicked()
{
 inputContent = new MemoryContents();
 setDefaultFieldValues();
 updateDownloadVerifyButtons();
 setCursor(Qt::WaitCursor);
 selectInputFile();
 doRead();
 setCursor(Qt::ArrowCursor);
}

void LoaderPane::on_bootload_focusLost()
{
 intParameterIsValid(bootload, 0, 255);
 updateDownloadVerifyButtons();
}

/*public*/ void LoaderPane::on_mfg_focusLost()
{
    intParameterIsValid(mfg, 0, 255);
    updateDownloadVerifyButtons();
}
/*public*/ void LoaderPane::on_developer_focusLost() {
    intParameterIsValid(developer, 0, 255);
    updateDownloadVerifyButtons();
}
/*public*/ void LoaderPane::on_product_focusLost() {
    intParameterIsValid(product, 0, 65535);
    updateDownloadVerifyButtons();
}
/*public*/ void LoaderPane::on_hardware_focusLost() {
    intParameterIsValid(hardware, 0, 255);
    updateDownloadVerifyButtons();
}
/*public*/ void LoaderPane::on_software_focusLost() {
    intParameterIsValid(software, 0, 255);
    updateDownloadVerifyButtons();
}
/*public*/ void LoaderPane::on_delay_focusLost() {
    intParameterIsValid(hardware,
                        MIN_DELAY_VALUE.toInt(),
            MAX_DELAY_VALUE.toInt());
    updateDownloadVerifyButtons();
}


/*private*/ void LoaderPane::selectInputFile()
{
 QString name = inputFileName->text();
 if (name==(""))
 {
  name = FileUtil::getUserFilesPath();
 }
#if 1
 if (chooser == NULL)
 {
  chooser = new JFileChooser(name);
//  javax.swing.filechooser.FileNameExtensionFilter filter
//                = new javax.swing.filechooser.FileNameExtensionFilter(
//                        tr("FileFilterLabel",
//                                "*.dfm, *.hex"), // NOI18N
//                        "dmf", "hex");   // NOI18N
  QString filter = "Digitrax Mangled Firmware (*.dmf);;Intel Hex Format Firmware (*.hex)";

//  chooser->addChoosableFileFilter(
//                new javax.swing.filechooser.FileNameExtensionFilter(
//                        "Digitrax Mangled Firmware (*.dmf)", "dmf")); //NOI18N
//        chooser.addChoosableFileFilter(
//                new javax.swing.filechooser.FileNameExtensionFilter(
//                        "Intel Hex Format Firmware (*.hex)", "hex")); //NOI18N
 //chooser->addChoosableFileFilter(filter);

 // make the downloadable file filter the default active filter
 chooser->setFileFilter(filter);

 }

 inputFileName->setText("");  // clear out in case of failure
 int retVal = chooser->showOpenDialog(this);
 if (retVal != JFileChooser::APPROVE_OPTION) {
     return;  // give up if no file selected
 }
 QString newFileName = chooser->getSelectedFile()->getName();
#else
 QString newFileName = QFileDialog::getOpenFileName(this, tr("Select file"),name,tr("Digitrax Mangled Firmware (*.dmf);;Intel Hex Format Firmware (*.hex)"));
#endif
 inputFileName->setText(newFileName);
 // check to see if it fits on the screen
 double currentStringWidth = inputFileName->minimumSize().width();
 double allowedWidth;
 inputFileName->setToolTip(newFileName);
 //allowedWidth = inputFileNamePanel->size().width() * 4 / 5 - inputFileLabelWidth;
 allowedWidth = inputFileName->size().width() * 4 / 5 /*- inputFileLabelWidth*/;
 if (currentStringWidth > allowedWidth)
 {
  // Filename won't fit on the display.
  // need to shorten the string.
  double startPoint
          = (inputFileName->text().length()
          * (1.0 - (allowedWidth / currentStringWidth)));
  QString displayableName = "..." // NOI18N
          + inputFileName->text().mid((int) startPoint);
  log->info("Shortening display of filename " // NOI18N
          + inputFileName->text()
          + " to " + displayableName);   // NOI18N
  log->debug("Width required to display the full file name = " // NOI18N
          + QString::number(currentStringWidth));
  log->debug("Allowed width = " + QString::number(allowedWidth));  // NOI18N
  log->debug("Amount of text not displayed = " + QString::number(startPoint));  // NOI18N
  inputFileName->setText(displayableName);
 }
//    inputFileName->updateUI();
//    inputFileNamePanel->updateUI();
//    updateUI();

 loadButton->setEnabled(false);
 loadButton->setToolTip(tr("Button disabled until you read a data file"));
 verifyButton->setEnabled(false);
 verifyButton->setToolTip(tr("Button disabled until you read a data file"));
 status->setText(tr("Click Download to download new firmware"));
}

/*private*/ void LoaderPane::doRead()
{
 if (inputFileName->text()==(""))
 {
//        JOptionPane.showMessageDialog(this, tr("ErrorNoInputFile"),
//                tr("ErrorTitle"),
//                JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(this, tr("Error"), tr("<html><font color=\"#FF0000\">You must select an input file.</html>") );
  return;
 }

 // force load, verify disabled in case read fails
 loadButton->setEnabled(false);
 loadButton->setToolTip(tr("Button disabled until you read a data file"));
 verifyButton->setEnabled(false);
 verifyButton->setToolTip(tr("Button disabled until you read a data file"));
 abortButton->setEnabled(false);
 abortButton->setToolTip(tr("Button disabled until a download or verify operation"));

 // clear the existing memory contents
 inputContent = new MemoryContents();
 connect(inputContent, SIGNAL(memoryContentsException(MemoryContentsException,QString)), this, SLOT(on_memoryContentsException(MemoryContentsException,QString)));

 bar->setValue(0);

 // load
 //try {
 QString fileName = inputFileName->text();
 if(!fileName.isEmpty())
 {
  File* file = new File(fileName);
  if(file->exists())
  {
   inputContent->readHex(file->getPath());
  }
  else
  {
   log->error(/*f.getLocalizedMessage()*/ tr("file name %1 not found").arg(file->getPath()));

//     JOptionPane.showMessageDialog(this, tr("ErrorFileNotFound"),
//             tr("ErrorTitle"),
//             JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(this, tr("Error"), tr("<html><font color=\"#FF0000\">File not found.</html>"));
     status->setText(tr("<html><font color=\"#FF0000\">Firmware file cannot be read.</html>"));
     this->disableDownloadVerifyButtons();
     return;
  }
 }
//  catch (MemoryContents.MemoryFileRecordLengthException f) {
//     log->error(f.getLocalizedMessage());
//     status->setText(tr("ErrorFileContentsError"));
//     this.disableDownloadVerifyButtons();
//     return;
// } catch (MemoryContents.MemoryFileChecksumException f) {
//     log->error(f.getLocalizedMessage());
//     status->setText(tr("ErrorFileContentsError"));
//     this.disableDownloadVerifyButtons();
//     return;
// } catch (MemoryContents.MemoryFileUnknownRecordType f) {
//     log->error(f.getLocalizedMessage());
//     status->setText(tr("ErrorFileContentsError"));
//     this.disableDownloadVerifyButtons();
//     return;
// } catch (MemoryContents.MemoryFileRecordContentException f) {
//     log->error(f.getLocalizedMessage());
//     status->setText(tr("ErrorFileContentsError"));
//     this.disableDownloadVerifyButtons();
//     return;
// } catch (MemoryContents.MemoryFileAddressingRangeException f) {
//     log->error(f.getLocalizedMessage());
//     status->setText(tr("ErrorFileContentsError"));
//     this.disableDownloadVerifyButtons();
//     return;
// } catch (MemoryContents.MemoryFileNoDataRecordsException f) {
//     log->error(f.getLocalizedMessage());
//     status->setText(tr("ErrorFileContentsError"));
//     this.disableDownloadVerifyButtons();
//     return;
// } catch (MemoryContents.MemoryFileNoEOFRecordException f) {
//     log->error(f.getLocalizedMessage());
//     status->setText(tr("ErrorFileContentsError"));
//     this.disableDownloadVerifyButtons();
//     return;
// } catch (MemoryContents.MemoryFileRecordFoundAfterEOFRecord f) {
//     log->error(f.getLocalizedMessage());
//     status->setText(tr("ErrorFileContentsError"));
//     this.disableDownloadVerifyButtons();
//     return;
// } catch (IOException e) {
//     log->error(e.getLocalizedMessage());
//     status->setText(tr("ErrorFileReadError"));
//     this.disableDownloadVerifyButtons();
//     return;
// }
 loadButton->setEnabled(true);
 loadButton->setToolTip(tr("Click here to download to the product"));
 verifyButton->setEnabled(true);
 verifyButton->setToolTip(tr("Click here to verify product memory"));
 status->setText(tr("Click Download to download new firmware"));

 // get some key/value pairs from the input file (if available)
 QString text = inputContent->extractValueOfKey("Bootloader Version");
 if (text != "")
 {
  bootload->setText(text);
 }

 text = inputContent->extractValueOfKey("Manufacturer Code");
 if (text != "") {
     mfg->setText(text);
 }

 text = inputContent->extractValueOfKey("Developer Code");
 if (text != "") {
     developer->setText(text);
 }

 text = inputContent->extractValueOfKey("Product Code");
 if (text != "") {
     product->setText(text);
 }

 text = inputContent->extractValueOfKey("Hardware Version");
 if (text != "") {
     hardware->setText(text);
 }

 text = inputContent->extractValueOfKey("Software Version");
 if (text != "") {
     software->setText(text);
 }

 text = inputContent->extractValueOfKey("Options");
 if (text != "")
 {
//     try {
  this->setOptionsRadiobuttons(text);
#if 0
     } catch (NumberFormatException ex) {
         JOptionPane.showMessageDialog(this,
                 tr("ErrorInvalidOptionInFile", text, "Options"),
                 tr("ErrorTitle"),
                 JOptionPane.ERROR_MESSAGE);
         this.disableDownloadVerifyButtons();
         return;
     }
#endif
 }

 text = inputContent->extractValueOfKey("Delay");
 if (text != "") {
     delay->setText(text);
 }

 text = inputContent->extractValueOfKey("EEPROM Start Address");
 if (text != "") {
     eestart->setText(text);
 }

 LoadOffsetFieldType addresstype = inputContent->getCurrentAddressFormat();
 address16bit->setEnabled(true);
 address24bit->setEnabled(true);
 if (addresstype == ADDRESSFIELDSIZE16BITS)
 {
     address16bit->setChecked(true);
     address24bit->setChecked(false);
 } else if (addresstype == ADDRESSFIELDSIZE24BITS)
 {
     address16bit->setChecked(false);
     address24bit->setChecked(true);
 }
 if (!parametersAreValid()) {
     status->setText(tr("<html><font color=\"#FF0000\">Invalid parameter(s) above.</html>"));
     disableDownloadVerifyButtons();
 } else if (!inputContent->isEmpty()) {
     enableDownloadVerifyButtons();
 }
}
void LoaderPane::on_memoryContentsException(MemoryContentsException , QString )
{
 status->setText(tr("<html><font color=\"#FF0000\">Firmware content in the file is not understood by this reader.</html>"));
 this->disableDownloadVerifyButtons();
 setCursor(Qt::ArrowCursor);
 disconnect(inputContent);
 return;

}

/*private*/ void LoaderPane::setOptionsRadiobuttons(QString text)//throws NumberFormatException
{
//    try {
 bool bOk;
 int control = text.toInt(&bOk);
 if(bOk)
 {
  switch (control & SW_FLAGS_MSK)
  {
      case CHECK_SOFTWARE_VERSION_LESS:
          checksoftwareless->setChecked(true);
          checksoftwareno->setChecked(false);
          break;
      case DO_NOT_CHECK_SOFTWARE_VERSION:
          checksoftwareless->setChecked(false);
          checksoftwareno->setChecked(true);
          break;
      default:
          throw new NumberFormatException("Invalid Software Options: "
                  + (control & SW_FLAGS_MSK));
  }
  switch (control & HW_FLAGS_MSK)
  {
      case DO_NOT_CHECK_HARDWARE_VERSION:
          checkhardwareno->setChecked(true);
          checkhardwareexact->setChecked(false);
          checkhardwaregreater->setChecked(false);
          break;
      case REQUIRE_HARDWARE_VERSION_EXACT_MATCH:
          checkhardwareno->setChecked(false);
          checkhardwareexact->setChecked(true);
          checkhardwaregreater->setChecked(false);
          break;
      case ACCEPT_LATER_HARDWARE_VERSIONS:
          checkhardwareno->setChecked(false);
          checkhardwareexact->setChecked(false);
          checkhardwaregreater->setChecked(true);
          break;
      default:
          throw new NumberFormatException("Invalid Hardware Options: "
                  + (control & HW_FLAGS_MSK));
  }
//    } catch (NumberFormatException ex) {
 }
 else
 {
  log->error("Invalid Option value: " + text);
  //throw new NumberFormatException(ex.getLocalizedMessage());
 }
}

void LoaderPane::doLoad() {
    status->setText(tr("Updating device firmware..."));
    loadButton->setEnabled(false);
    loadButton->setToolTip(tr("Button disabled during download"));
    verifyButton->setEnabled(false);
    verifyButton->setToolTip(tr("Button disabled during download"));
    abortButton->setEnabled(true);
    abortButton->setToolTip(tr("Click here to abort a download or verify operation"));

    // start the download itself
    setCursor(Qt::WaitCursor);
    operation = PXCT2SENDDATA;

    sendSequence();
}

void LoaderPane::doVerify()
{
 setCursor(Qt::WaitCursor);
 status->setText(tr("Verifying device firmware..."));
 loadButton->setEnabled(false);
 loadButton->setToolTip(tr("Button disabled during download"));
 verifyButton->setEnabled(false);
 verifyButton->setToolTip(tr("Button disabled during download"));
 abortButton->setEnabled(true);
 abortButton->setToolTip(tr("Click here to abort a download or verify operation"));

 // start the download itself
 operation = PXCT2VERIFYDATA;
 sendSequence();
 setCursor(Qt::ArrowCursor);
}

/**
 * Cleans up the GUI interface. Updates status line to a localized "done"
 * message or a localized "aborted" message depending on the value returned
 * by isOperationAborted() . Assumes that the file was properly read to
 * memory and is usable for firmware update and/or verify operations, and
 * configures the Load, and Verify GUI buttons as enabled, and the Abort GUI
 * button as disabled.
 *
 */
void LoaderPane::enableDownloadVerifyButtons()
{
 if (log->isDebugEnabled()) {
     log->debug("enableGUI");
 }

 if (isOperationAborted()) {
     status->setText(tr("<html><font color=\"#FF0000\">Operation Aborted</html>"));
 } else {
     status->setText(tr("Operation Complete"));
 }
 setCursor(Qt::ArrowCursor);

 // remove the
 setOperationAborted(false);

 loadButton->setEnabled(true);
 loadButton->setToolTip(tr("Click here to download to the product"));
 verifyButton->setEnabled(true);
 verifyButton->setToolTip(tr("Click here to verify product memory"));
 abortButton->setEnabled(false);
 abortButton->setToolTip(tr("Button disabled until a download or verify operation"));
}

/**
 * Cleans up the GUI interface after a firmware file read fails. Assumes
 * that the invoking code will update the GUI status line as appropriate for
 * the particular cause of failure. Configures the Load, Verify and Abort
 * GUI buttons as disabled.
 *
 */
/*private*/ void LoaderPane::disableDownloadVerifyButtons()
{
 if (log->isDebugEnabled()) {
     log->debug("disableGUI");
 }

 setOperationAborted(false);

 loadButton->setEnabled(false);
 loadButton->setToolTip(tr("Button disabled until you read a data file"));
 verifyButton->setEnabled(false);
 verifyButton->setToolTip(tr("Button disabled until you read a data file"));
 abortButton->setEnabled(false);
 abortButton->setToolTip(tr("Button disabled until a download or verify operation"));

}


/*private*/ void LoaderPane::setOperationAborted(bool state)
{
 /*synchronized (this)*/ {
     abortOperation = state;
 }
}

/*private*/ bool LoaderPane::isOperationAborted()
{
 /*synchronized (this)*/ {
     return abortOperation;
 }
}


/*private*/ void LoaderPane::sendSequence()
{
 int mfgval;
 int developerval;
 int prodval;
 int hardval;
 int softval;
 int control;

 // before starting the send sequence, check for bad values in the
 // GUI text fields containing the parameters.
 if (!parametersAreValid())
 {
  disableDownloadVerifyButtons();
  status->setText(tr("<html><font color=\"#FF0000\">Invalid parameter(s) above.</html>"));
  setCursor(Qt::ArrowCursor);
  return;
 }
 if (inputContent->isEmpty())
 {
  disableDownloadVerifyButtons();
  status->setText(tr(">Do not have any firmware information to send.</html>"));
  setCursor(Qt::ArrowCursor);
  return;
 }

 // now know that the GUI text fields are valid and have some data to move.
 //try {
 bool bOk;
 mfgval = mfg->text().toInt(&bOk);
 if (!bOk || (mfgval < 0 || mfgval > 0xff) )
 {
//            throw new NumberFormatException("out of range");
//        }
//    } catch (NumberFormatException ex) {
  log->error("sendSequence() failed due to bad Manufacturer Number value " + mfg->text());
  mfg->setForeground(Qt::red);
  //mfg->requestFocusInWindow();
  mfg->setFocus();
  enableDownloadVerifyButtons();
  status->setText(tr("<html><font color=\"#FF0000\">Invalid <b>%1</b> </html><html><font color=\"#010101\">%2</html>").arg(
                      tr("Manufacturer Number:")).arg(
             mfg->text()));
  setCursor(Qt::ArrowCursor);

  return;
 }

 //try {
  developerval = developer->text().toInt(&bOk);
  if (!bOk ||(developerval < 0 || developerval > 0xff))
  {
//            throw new NumberFormatException("out of range");
//        }
//    } catch (NumberFormatException ex) {
  log->error("sendSequence() failed due to bad Developer Number value " + developer->text());
  developer->setForeground(Qt::red);
  //developer->requestFocusInWindow();
  developer->setFocus();
  enableDownloadVerifyButtons();
  status->setText(tr("<html><font color=\"#FF0000\">Invalid <b>%1</b> </html><html><font color=\"#010101\">%2</html>").arg(
          tr("Developer Number:")).arg(
          developer->text()));
  setCursor(Qt::ArrowCursor);

  return;
 }

//    try {
  prodval = product->text().toInt(&bOk);
  if (!bOk ||(prodval < 0 || prodval > 0xffff))
  {
//            throw new NumberFormatException("out of range");
//        }
//    } catch (NumberFormatException ex) {
  log->error("sendSequence() failed due to bad Product Code value " + product->text());
  product->setForeground(Qt::red);
  //product->requestFocusInWindow();
  product->setFocus();
  this->enableDownloadVerifyButtons();
  enableDownloadVerifyButtons();
  status->setText(tr("<html><font color=\"#FF0000\">Invalid <b>%1</b> </html><html><font color=\"#010101\">%2</html>").arg(
                   tr("Product Code:")).arg(
          product->text()));
  setCursor(Qt::ArrowCursor);

  return;
 }

//    try {
  hardval = hardware->text().toInt(&bOk);
  if (!bOk ||(hardval < 0 || hardval > 0xff))
  {
//            throw new NumberFormatException("out of range");
//        }
//    } catch (NumberFormatException ex) {
  log->error("sendSequence() failed due to bad Hardware Version value " + hardware->text());
  hardware->setForeground(Qt::red);
  //hardware->requestFocusInWindow();
  hardware->setFocus();
  enableDownloadVerifyButtons();
  status->setText(tr("<html><font color=\"#FF0000\">Invalid <b>%1</b> </html><html><font color=\"#010101\">%2</html>").arg(
                      tr("Hardware Version Number:")).arg(
          hardware->text()));
  setCursor(Qt::ArrowCursor);

  return;
 }

//    try {
  softval = software->text().toInt(&bOk);
  if (!bOk ||(softval < 0 || softval > 0xff))
  {
//            throw new NumberFormatException("out of range");
//        }
//    } catch (NumberFormatException ex) {
  log->error("sendSequence() failed due to bad Software Version value " + software->text());
  software->setForeground(Qt::red);
  //software->requestFocusInWindow();
  software->setFocus();
  enableDownloadVerifyButtons();
  status->setText(tr("<html><font color=\"#FF0000\">Invalid <b>%1</b> </html><html><font color=\"#010101\">%2</html>").arg(
          tr("Software Version Number:")).arg(
          software->text()));
  setCursor(Qt::ArrowCursor);

  return;
 }

 control = computeOptionsValFromRadiobuttons();

//    try {
     delayval = delay->text().toInt(&bOk);
     if (!bOk || ((delayval < MIN_DELAY_VALUE.toInt())
             || (delayval > MAX_DELAY_VALUE.toInt())))
     {
//            throw new NumberFormatException("out of range");
//        }
//    } catch (NumberFormatException ex) {
     log->error("sendSequence() failed due to bad Delay value " + delay->text());
     delay->setForeground(Qt::red);
     //delay->requestFocusInWindow();
     delay->setFocus();
     enableDownloadVerifyButtons();
     status->setText(tr("<html><font color=\"#FF0000\">Invalid <b>%1</b> </html><html><font color=\"#010101\">%2</html>").arg(
             tr("Delay (msec):"),
             delay->text()));
     setCursor(Qt::ArrowCursor);

     return;
 }

//    try {
     eestartval = eestart->text().toInt(&bOk, 16);
     if ((eestartval < MIN_EESTART_VALUE.toInt(0, 16))
             || (eestartval > MAX_EESTART_VALUE.toInt(0, 16)))
     {
//            throw new NumberFormatException("out of range");
//        }
//    } catch (NumberFormatException ex) {
     log->error("sendSequence() failed due to bad EESTART value " + eestart->text());
     eestart->setForeground(Qt::red);
     //eestart->requestFocusInWindow();
     eestart->setFocus();
     enableDownloadVerifyButtons();
     status->setText(tr("<html><font color=\"#FF0000\">Invalid <b>%1</b> </html><html><font color=\"#010101\">%2</html>").arg(
             tr("Start of EEPROM addresses (hex):"),
             eestart->text()));
     setCursor(Qt::ArrowCursor);

     return;
 }

 // send start
 sendOne(PXCT2SETUP, mfgval, prodval & 0xff, hardval, softval,
         control, 0, developerval, prodval / 256);

 // start transmission loop
 //new Thread(new Sender()).start();
 Sender* sender = new Sender(this);
 connect(sender, SIGNAL(setEnableGui()), this, SLOT(on_enableGui()));
 connect(sender, SIGNAL(setUpdateGui(int)), this, SLOT(on_updateGui(int)));
 sender->start();
}

void LoaderPane::sendOne(int pxct2, int d1, int d2, int d3, int d4,
        int d5, int d6, int d7, int d8)
{
 LocoNetMessage* m = new LocoNetMessage(16);
 m->setOpCode(LnConstants::OPC_PEER_XFER);
 m->setElement(1, 0x10);
 m->setElement(2, 0x7F);
 m->setElement(3, 0x7F);
 m->setElement(4, 0x7F);

 int d1u = (d1 & 0x80) / 0x80;
 int d2u = (d2 & 0x80) / 0x40;
 int d3u = (d3 & 0x80) / 0x20;
 int d4u = (d4 & 0x80) / 0x10;
 int lowbits = d1u | d2u | d3u | d4u;

 m->setElement(5, (lowbits | PXCT1DOWNLOAD) & 0x7F);  // PXCT1
 m->setElement(6, d1 & 0x7F);  // D1
 m->setElement(7, d2 & 0x7F);  // D2
 m->setElement(8, d3 & 0x7F);  // D3
 m->setElement(9, d4 & 0x7F);  // D4

 int d5u = (d5 & 0x80) / 0x80;
 int d6u = (d6 & 0x80) / 0x40;
 int d7u = (d7 & 0x80) / 0x20;
 int d8u = (d8 & 0x80) / 0x10;
 lowbits = d5u | d6u | d7u | d8u;

 m->setElement(10, (lowbits | pxct2) & 0x7F);  // PXCT2
 m->setElement(11, d5 & 0x7F);  // D5
 m->setElement(12, d6 & 0x7F);  // D6
 m->setElement(13, d7 & 0x7F);  // D7
 m->setElement(14, d8 & 0x7F);  // D8

 memo->getLnTrafficController()->sendLocoNetMessage(m);

}
void LoaderPane::on_updateGui(int val)
{
 bar->setValue(100 * val);

}

void LoaderPane::on_enableGui()
{
 enableDownloadVerifyButtons();
}

///*private*/ class Sender implements Runnable {


//    int totalmsgs;
//    int sentmsgs;
Sender::Sender(LoaderPane *self)
{
 this->self = self;
}

// send the next data, and a termination record when done
//@Override
/*public*/ void Sender::run()
{
 // define range to be checked for download
 self->startaddr = 0x000000;
 self->endaddr = 0xFFFFFF;

 if ((self->startaddr & 0x7) != 0)
 {
  self->log->error("Can only start on an 8-byte boundary: " + self->startaddr);
 }

 // fast scan to count bytes to send
 int location = self->inputContent->nextContent(self->startaddr);
 totalmsgs = 0;
 sentmsgs = 0;
 location = location & 0x00FFFFF8;  // mask off bits to be multiple of 8
 do
 {
  location = location + 8;
  totalmsgs++;
  // update to the next location for data
  int next = self->inputContent->nextContent(location);
  if (next < 0)
  {
   break;   // no data left
  }
  location = next & 0x00FFFFF8;  // mask off bits to be multiple of 8

 } while (location <= self->endaddr);

 // find the initial location with data
 location = self->inputContent->nextContent(self->startaddr);
 if (location < 0)
 {
  self->log->info("No data, which seems odd");
  return;  // ends load process
 }
 location = location & 0x00FFFFF8;  // mask off bits to be multiple of 8

 setAddr(location);

 do
 {
  // wait for completion of last operation
  doWait(location);

  // send this data
  sentmsgs++;
  self->sendOne(self->operation, // either send or verify
  self->inputContent->getLocation(location++),
  self->inputContent->getLocation(location++),
  self->inputContent->getLocation(location++),
  self->inputContent->getLocation(location++),
  self->inputContent->getLocation(location++),
  self->inputContent->getLocation(location++),
  self->inputContent->getLocation(location++),
  self->inputContent->getLocation(location++));

  // update GUI intermittently
  if ((sentmsgs % 5) == 0)
  {
   // update progress bar via the queue to ensure synchronization
   updateGUI(100 * sentmsgs / totalmsgs);
  }

  // update to the next location for data
  int next = self->inputContent->nextContent(location);
  if (next < 0) {
      break;   // no data left
  }
  next = next & 0x00FFFFF8;  // mask off bits to be multiple of 8
  if (next != location) {
      // wait for completion
      doWait(next);
      // change to next location
      setAddr(next);
  }
  location = next;

 } while (!self->isOperationAborted() && (location <= self->endaddr));

 // send end (after wait)
 doWait(location);
 self->sendOne(LoaderPane::PXCT2ENDOPERATION, 0, 0, 0, 0, 0, 0, 0, 0);

 this->updateGUI(100); //draw bar to 100%

//        // signal end to GUI via the queue to ensure synchronization
//        Runnable r = new Runnable() {
//            //@Override
//            /*public*/ void run() {
//                enableGUI();
//            }
//        };
//        javax.swing.SwingUtilities.invokeLater(r);
 emit setEnableGui();
}

/**
 * Send a command to resume at another address
 */
void Sender::setAddr(int location)
{
 self->sendOne(LoaderPane::PXCT2SENDADDRESS,
            (location / 256 / 256) & 0xFF,
            (location / 256) & 0xFF,
            location & 0xFF,
            0, 0, 0, 0, 0);
}

/**
 * Wait the specified time.
 *
 * 16*10/16.44 = 14 msec is the time it takes to send the message.
 */
void Sender::doWait(int address)
{
//        try {
       /* synchronized (this) */
 {
  // make sure enough time in EEPROM address space
  int tdelay;
  if (address >= self->eestartval) {
      tdelay = self->delayval + 50 + 14;
  } else {
      tdelay = self->delayval + 4 + 14;
  }

  // do the actual wait
  wait(tdelay);
 }
//        } catch (InterruptedException e) {
//            Thread.currentThread().interrupt(); // retain if needed later
//        }
}

/**
 * Signal GUI that it's the end of the download
 * <P>
 * Should be invoked on the Swing thread
 */
void Sender::enableGUI()
{
//        LoaderPane::enableDownloadVerifyButtons();
 emit setEnableGui();
}

/**
 * Update the GUI for progress
 */
void Sender::updateGUI(/*final*/ int value) {
//        javax.swing.SwingUtilities.invokeLater(new Runnable() {
//            //@Override
//            /*public*/ void run() {
//                if (log->isDebugEnabled()) {
//                    log->debug("updateGUI with " + value);
//                }
//                // update progress bar
//                bar->setValue(100 * sentmsgs / totalmsgs);
//            }
//        });
 emit setUpdateGui(sentmsgs / totalmsgs);
}

//};

/*private*/ void LoaderPane::setDefaultFieldValues()
{
//    addressSizeButtonGroup.clearSelection();
 bootload->setText("1");
 mfg->setText("1");
 developer->setText("1");
 product->setText("1");
 hardware->setText("1");
 software->setText("1");
 delay->setText("200");
 eestart->setText("C00000");

//    try {
 setOptionsRadiobuttons(QString::number((DO_NOT_CHECK_SOFTWARE_VERSION + REQUIRE_HARDWARE_VERSION_EXACT_MATCH)));
//    } catch (NumberFormatException ex) {
//        throw (new java.lang.Error("SetCheckboxes Failed to update the GUI for known-good parameters"));
//    }
 parametersAreValid();
}

/**
 * Checks the values in the GUI text boxes to determine if any are invalid.
 * Intended for use immediately after reading a firmware file for the
 * purpose of validating any key/value pairs found in the file. Also
 * intended for use immediately before a "verify" or "download" operation to
 * check that the user has not changed any of the GUI text values to ones
 * that are unsupported.
 *
 * Note that this method cannot guarantee that the values are suitable for
 * the hardware being updated and/or for the particular firmware information
 * which was read from the firmware file.
 *
 * @return false if one or more GUI text box contains an invalid value
 */
/*public*/ bool LoaderPane::parametersAreValid()
 {
  bool allIsOk;
  allIsOk = true; // assume that all GUI values are ok.
  QString text;    // temporary variable to hold text from GUI element
  int junk;       // temporary variable to hold interpreted GUI value

  bool temp;
  temp = intParameterIsValid(bootload, 0, 255);
  allIsOk &= temp;
  if (!temp) {
      log->info("Bootloader Version Number is not valid: " + bootload->text());
  }
  temp = intParameterIsValid(mfg, 0, 255);
  allIsOk &= temp;
  if (!temp) {
      log->info("Manufacturer Number is not valid: " + mfg->text());
  }
  temp = intParameterIsValid(developer, 0, 255);
  allIsOk &= temp;
  if (!temp) {
      log->info("Developer Number is not valid: " + bootload->text());
  }
  temp = intParameterIsValid(product, 0, 65535);
  allIsOk &= temp;
  if (!temp) {
      log->info("Product Code is not valid: " + product->text());
  }
  temp = intParameterIsValid(hardware, 0, 255);
  allIsOk &= temp;
  if (!temp) {
      log->info("Hardware Version Number is not valid: " + hardware->text());
  }
  temp = intParameterIsValid(software, 0, 255);
  allIsOk &= temp;
  if (!temp) {
      log->info("Software Version Number is not valid: " + software->text());
  }
  temp = intParameterIsValid(delay,
          MIN_DELAY_VALUE.toInt(),
          MAX_DELAY_VALUE.toInt());
  allIsOk &= temp;
  if (!temp) {
      log->info("Delay is not valid: " + delay->text());
  }
  temp = (hardgroup->checkedButton() != NULL);
  allIsOk &= temp;
  if (!temp) {
      log->info("No hardware version check radio button is selected.");
  }
  temp = (softgroup->checkedButton() != NULL);
  allIsOk &= temp;
  if (!temp) {
      log->info("No software version check radio button is selected.");
  }
  temp = true;
  eestart->setForeground(Qt::black);
  text = eestart->text();
  if (text==("")) {
      eestart->setText("0");
      eestart->setForeground(Qt::red);
      temp = false;
  } else {
  //        try {
   bool bOk;
          junk = text.toInt(&bOk, 16);
  //        } catch (NumberFormatException ex) {
          if(!bOk)
          junk = -1;
  //        }
      if ((junk < MIN_EESTART_VALUE.toInt(0, 16))
              || ((junk % 8) != 0)
              || (junk > MAX_EESTART_VALUE.toInt(0, 16))) {
          eestart->setForeground(Qt::red);
          temp = false;
      } else {
          eestart->setForeground(Qt::black);
          temp = true;
      }
 }
 //eestart->updateUI();

 allIsOk &= temp;
 if (allIsOk == true)
 {
  log->debug("No problems found when checking parameter values.");
 }

 return allIsOk;
}

/*private*/ bool LoaderPane::intParameterIsValid(JTextField* jtf, int minOk, int maxOk)
{
 QString text;
 int junk;
 bool allIsOk = true;
 jtf->setForeground(Qt::black);
 text = jtf->text();
 if (text==(""))
 {
  jtf->setText("0");
  jtf->setForeground(Qt::red);
  allIsOk = false;
 } else
 {
//        try {
  bool bOk;
         junk = text.toInt(&bOk);
//        } catch (NumberFormatException ex) {
  if(!bOk)
         junk = -1;
//     }
     if ((junk < minOk) || (junk > maxOk)) {
         jtf->setForeground(Qt::red);
         allIsOk = false;
     } else {
         jtf->setForeground(Qt::black);
     }
 }
 //jtf->updateUI();
 return allIsOk;
}

/*private*/ int LoaderPane::computeOptionsValFromRadiobuttons()
{
 int control = 0;
 if (checksoftwareless->isChecked()) {
     control |= CHECK_SOFTWARE_VERSION_LESS;
 }

 if (checkhardwareexact->isChecked()) {
     control |= REQUIRE_HARDWARE_VERSION_EXACT_MATCH;
 } else if (checkhardwaregreater->isChecked()) {
     control |= ACCEPT_LATER_HARDWARE_VERSIONS;
 }
 return control;
}

/**
 * Conditionally enables or disables the Download and Verify GUI buttons
 * based on the validity of the parameter values in the GUI and the state of
 * the memory contents object.
 */
/*private*/ void LoaderPane::updateDownloadVerifyButtons()
{
 if (parametersAreValid() && !inputContent->isEmpty()) {
     enableDownloadVerifyButtons();
 } else {
     disableDownloadVerifyButtons();
 }
}

/*public*/ void LoaderPane::actionPerformed(JActionEvent* /*e*/)
{
 updateDownloadVerifyButtons();
 log->info("ActionListener");
}
//    static Logger log = LoggerFactory.getLogger(LoaderPane.class.getName());

//}
