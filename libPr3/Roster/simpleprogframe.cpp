#include "simpleprogframe.h"
#include "jtogglebutton.h"
#include "jtextfield.h"
#include <QRadioButton>
#include "progmodepane.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include "../../LayoutEditor/jseparator.h"
#include <QButtonGroup>
#include "slotmanager.h"
#include <QValidator>
#include "decvariablevalue.h"

//SimpleProgFrame::SimpleProgFrame(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
/**
 * Frame providing a simple command station programmer
 *
 * @author	Bob Jacobsen   Copyright (C) 2001, 2007
 * @author  Giorgio Terdina Copyright (C) 2007
 * @version			$Revision: 17977 $
 */
// /*public*/ class SimpleProgFrame extends jmri.util.JmriJFrame implements jmri.ProgListener {

/*public*/ SimpleProgFrame::SimpleProgFrame(QWidget *parent) : JmriJFrame(parent)
{
    //super();
    // GUI member declarations
 readButton 	= new JToggleButton();
 writeButton 	= new JToggleButton();
 addrField      = new JTextField(4);
 valField       = new JTextField(4);
 valField->setValidator(new QIntValidator);

 modePane       = new ProgModePane(QBoxLayout::LeftToRight);

 radixGroup     = new QButtonGroup();
 hexButton    	= new QRadioButton();
 decButton   	= new QRadioButton();
 decButton->setChecked(true);

 resultsField   = new QLabel(" ");


 // configure items for GUI
 readButton->setText(tr("Read CV"));
 readButton->setToolTip(tr("Read the value from the selected CV"));

 writeButton->setText(tr("Write CV"));
 writeButton->setToolTip(tr("Write the value to the selected CV"));

 hexButton->setText("Hexadecimal");
 decButton->setText("Decimal");
 decButton->setChecked(true);

 // add the actions to the buttons
// readButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            readPushed(e);
//        }
// });
 connect(readButton, SIGNAL(clicked()),this, SLOT(readPushed()));
//    writeButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            writePushed(e);
//        }
//    });
 connect(writeButton, SIGNAL(clicked()), this, SLOT(writePushed()));
//    decButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            decHexButtonChanged(e);
//        }
//    });
 connect(decButton, SIGNAL(toggled(bool)), this , SLOT(decHexButtonChanged()));
//    hexButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            decHexButtonChanged(e);
//        }
//    });


 resultsField->setAlignment(/*JLabel.CENTER_ALIGNMENT*/Qt::AlignCenter);

 // general GUI config
 setTitle(tr("Simple Programmer"));
 //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
 QWidget* contentPane = new QWidget;
 QVBoxLayout* layout = new QVBoxLayout;
 contentPane ->setLayout(layout);
 setCentralWidget(contentPane);

 // install items in GUI
 QWidget* tPane;  // temporary pane for layout
 QWidget* tPane2;

 tPane = new QWidget();
 QHBoxLayout* tPaneLayout;
 tPane->setLayout(tPaneLayout = new QHBoxLayout);//(tPane, BoxLayout.X_AXIS));
 tPaneLayout->addWidget(readButton);
 tPaneLayout->addWidget(writeButton);
 layout->addWidget(tPane);

 tPane = new QWidget();
 QGridLayout* g;
 tPane->setLayout(g = new QGridLayout(/*2,2*/));
 g->addWidget(new QLabel(tr("CV Number:")),0,0);
 g->addWidget(addrField,0,1);
 g->addWidget(new QLabel(tr("Value:")),1,0);
 g->addWidget(valField,1,1);
 layout->addWidget(tPane);

 layout->addWidget(new JSeparator(JSeparator::HORIZONTAL));

 tPane = new QWidget();
 tPane->setLayout(tPaneLayout = new QHBoxLayout);//(tPane, BoxLayout.X_AXIS));

 tPaneLayout->addWidget(modePane);

 tPaneLayout->addWidget(new JSeparator(JSeparator::VERTICAL));

 tPane2 = new QWidget();
 QVBoxLayout* tPane2Layout;
 tPane2->setLayout(tPane2Layout = new QVBoxLayout);//(tPane2, BoxLayout.Y_AXIS));
 radixGroup->addButton(decButton);
 radixGroup->addButton(hexButton);
 tPane2Layout->addWidget(new QLabel(tr("Value is:")));
 tPane2Layout->addWidget(decButton);
 tPane2Layout->addWidget(hexButton);
 tPaneLayout->addWidget(tPane2);

 layout->addWidget(tPane);

 layout->addWidget(new JSeparator());

 layout->addWidget(resultsField);

 if (modePane->getProgrammer()== NULL){
       readButton->setEnabled (false);
       // boudreau let system Programmer determine default mode
//         modePane.setDefaultMode();
   }
    // disable read button if non-functional
    if (modePane->getProgrammer()!= NULL)
        readButton->setEnabled(((SlotManager*)modePane->getProgrammer())->getCanRead());

 // add help menu to window
 addHelpMenu("package.jmri.jmrit.simpleprog.SimpleProgFrame", true);

 pack();
}

// utility function to get value, handling radix
/*private*/ int SimpleProgFrame::getNewVal() {
    try {
        if (decButton->isChecked())
            return valField->text().toInt();
        else
            return valField->text().toInt(0, 16);
    } catch (NumberFormatException e) {
        valField->setText("");
        return 0;
    }
}
/*private*/ QString SimpleProgFrame::getNewAddr() {
        return addrField->text();
}

/*private*/ QString SimpleProgFrame::statusCode(int status) {
    SlotManager* p = (SlotManager*)modePane->getProgrammer();
    if (status == ProgListener::OK) return "OK";
    if (p == NULL) {
        return "No programmer connected";
    } else {
        return p->decodeErrorCode(status);
    }
}

// listen for messages from the Programmer object
/*public*/ void SimpleProgFrame::programmingOpReply(int value, int status)
{
 resultsField->setText(statusCode(status));

 //operation over, raise the buttons
 readButton->setChecked(false);
 writeButton->setChecked(false);

 // capture the read value
 if (value != -1)  // -1 implies nothing being returned
 {
  if (decButton->isChecked())
   valField->setText(QString::number(value,10));
  else
   valField->setText(QString::number(value,16));
 }
}

// handle the buttons being pushed
/*public*/ void SimpleProgFrame::readPushed(JActionEvent* /*e*/)
{
 SlotManager* p = (SlotManager*)modePane->getProgrammer();
 if (p == NULL)
 {
  resultsField->setText(tr("No programmer connected"));
  readButton->setChecked(false);
 }
 else
 {
  if (p->getCanRead())
  {
//            try {
   connect(p, SIGNAL(programmerException(QString)), this, SLOT(On_read_programmerException(QString)));
   resultsField->setText("programming...");
   p->readCV(getNewAddr(), (ProgListener*)this);
//            } catch (ProgrammerException ex) {
//                resultsField->setText("" + ex.getMessage());
//                readButton->setChecked(false);
//            }
  }
  else
  {
   resultsField->setText("can't read in this Mode");
   readButton->setSelected(false);
  }
 }
}

void SimpleProgFrame::On_read_programmerException(QString txt)
{
 resultsField->setText("" + txt);
 readButton->setChecked(false);
}

/*public*/ void SimpleProgFrame::writePushed(JActionEvent* /*e*/)
{
 SlotManager* p = (SlotManager*)modePane->getProgrammer();
 if (p == NULL)
 {
  resultsField->setText("No programmer connected");
  writeButton->setSelected(false);
 }
 else
 {
//        try {
  resultsField->setText("programming...");
  connect(p, SIGNAL(programmerException(QString)), this, SLOT(On_write_programmerException(QString)));
  p->writeCV(getNewAddr(),getNewVal(), (ProgListener*)this);
//        } catch (ProgrammerException ex) {
//            resultsField->setText(""+ex.getMessage());
//            writeButton->setSelected(false);
//        }
 }
}
void SimpleProgFrame::On_write_programmerException(QString txt)
{
 resultsField->setText(txt);
 writeButton->setSelected(false);
}

// provide simple data conversion if dec or hex button changed
/*public*/ void SimpleProgFrame::decHexButtonChanged(JActionEvent* /*e*/)
{
 resultsField->setText("OK");
 if (valField->text()==(""))
  return;
 int value = 0;
 try
 {
  if (decButton->isChecked())
  {
   // convert from hex to dec
   value = valField->text().toInt(0,16);
   QRegExp rx("[0-9A-Fa-f ]{1,8}");
   valField->setValidator(new QRegExpValidator(rx,0));
  }
  else
  {
   // convert from dec to hex
   value = valField->text().toInt(0, 10);
   valField->setValidator(new QIntValidator);
  }
 }
 catch (NumberFormatException ee)
 {
  resultsField->setText("error");
 }
 if (value != 0)
 {
  if (decButton->isChecked())
   valField->setText(QString::number(value));
  else
   valField->setText(QString::number(value,16));
 }
}

/*public*/ void SimpleProgFrame::dispose() {
    modePane->dispose();
    JmriJFrame::dispose();
}

/*public*/ QString SimpleProgFrame::getClassName()
{
 return "jmri.jmrit.simpleprog.SimpleProgFrame";
}
