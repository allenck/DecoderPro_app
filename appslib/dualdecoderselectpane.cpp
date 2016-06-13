#include "dualdecoderselectpane.h"
#include "jlabel.h"
#include "jtogglebutton.h"
#include <QRadioButton>
#include <QBoxLayout>
#include "progmodepane.h"
#include <QGridLayout>
#include "jseparator.h"
#include <QButtonGroup>
#include <QSignalMapper>
#include "flowlayout.h"
#include "programmer.h"
#include "logger.h"

//DualDecoderSelectPane::DualDecoderSelectPane(QWidget *parent) :
//  QWidget(parent)
//{
//}
/**
 * Pane for selecting an active decoder from multiple ones in a loco
 *
 * @author Bob Jacobsen Copyright (C) 2003
 * @version $Revision: 28746 $
 */
///*public*/ class DualDecoderSelectPane extends javax.swing.JPanel implements jmri.ProgListener {

/**
 *
 */
//private static final long serialVersionUID = 1032342693614263212L;

/*public*/ DualDecoderSelectPane::DualDecoderSelectPane(QWidget *parent) :
  QWidget(parent)
{
 scanning = false;
 next = 0;

 NENTRIES = 8;

 labels = new QVector<JLabel*>(NENTRIES);
 buttons = new QVector<QRadioButton*>(NENTRIES);

 status = new JLabel("Idle");
 searchButton = new JToggleButton("Search");
 modePane = new ProgModePane(QBoxLayout::TopToBottom);
 // modes
 mode = SEARCH;

 // search, select operation states
 state = IDLE;
 log = new Logger("DualDecoderSelectPane");

 // general GUI config
 QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout); //(this, BoxLayout.Y_AXIS));
 QButtonGroup* g = new QButtonGroup();
 QSignalMapper* bMapper = new QSignalMapper();
 QWidget* pane1 = new QWidget();
 QGridLayout* pane1Layout;
 pane1->setLayout(pane1Layout = new QGridLayout); //(NENTRIES, 1));
 for (int i = 0; i < NENTRIES; i++)
 {
  //QWidget* p = new JPanel();
  QHBoxLayout* pLayout = new QHBoxLayout;
  QString name = "ID number " + QString::number(i);
  if (i == NENTRIES - 1)
  {
   name = "   Legacy ";
  }
  pLayout->addWidget(labels->at(i));
  labels->replace(i,new JLabel(name));
  QRadioButton* b = new QRadioButton();
  bMapper->setMapping(b, i);
  buttons->replace(i,  b);

  //b.setActionCommand("" + i);

//  b.addActionListener(new ActionListener() {
//      /*public*/ void actionPerformed(ActionEvent e) {
//          select(e.getActionCommand());
//      }
//  });
  connect(b, SIGNAL(clicked()), bMapper, SLOT(map()));

  pLayout->addWidget(b);
  g->addButton(b);
  pane1Layout->addLayout(pLayout, i, 0);
 }
 connect(bMapper, SIGNAL(mapped(int)), this, SLOT(select(int)));
 thisLayout->addLayout(pane1Layout);
 //add(new JSeparator(JSeparator.HORIZONTAL));
 thisLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));

 //QWidget* pane2 = new JPanel();
 FlowLayout* pane2Layout = new FlowLayout;
 QPushButton* t;
 pane2Layout->addWidget(searchButton);
// searchButton.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent e) {
//         search();
//     }
// });
 connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
 pane2Layout->addWidget(t = new QPushButton("Reset"));
// t.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent e) {
//         reset();
//     }
// });
 connect(t, SIGNAL(clicked()), this, SLOT(reset()));
 thisLayout->addLayout(pane2Layout);

 //QWidget* pane3 = new QWidget();
 FlowLayout* pane3Layout = new FlowLayout;
 pane3Layout->addWidget(t = new QPushButton("Init DH163 + Soundtraxx"));
 t->setToolTip("This will configure a loco contains a DH163 and a decoder not supporting the proposed protocol");
// t.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent e) {
//         doInit();
//     }
// });
 connect(t, SIGNAL(clicked()), this, SLOT(doInit()));
 thisLayout->addLayout(pane3Layout);
 thisLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));

 //QWidget* pane4 = new JPanel();
 QHBoxLayout* pane4Layout = new QHBoxLayout;
 pane4Layout->addWidget(status);
 thisLayout->addLayout(pane4Layout);
 thisLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));

 thisLayout->addWidget(modePane);
}

/*public*/ void DualDecoderSelectPane::dispose()
{
 modePane->dispose();
 buttons = NULL;
 labels = NULL;
 status = NULL;
 searchButton = NULL;
}

void DualDecoderSelectPane::reset()
{
 for (int i = 0; i < NENTRIES; i++)
 {
  labels->at(i)->setEnabled(true);
  buttons->at(i)->setChecked(false);
  buttons->at(i)->setEnabled(true);
 }
}

void DualDecoderSelectPane::search() {
    mode = SEARCH;
    reset();
    searchButton->setChecked(true);
    scanning = true;
    next = 0;
    select(0);
}

void DualDecoderSelectPane::select(int number) {
    mode = SEARCH;
    next = number;
    // write that CV value
    state = WROTECV15;
    writeCV15(next);
}

void DualDecoderSelectPane::writeCV15(int value) {
    writeCV(15, value);
}

void DualDecoderSelectPane::writeCV16(int value) {
    writeCV(16, value);
}

void DualDecoderSelectPane::writeCV(int cv, int value) {
    Programmer* p = modePane->getProgrammer();
    if (p == NULL) {
        state = IDLE;
        status->setText("No programmer connected");
    } else {
        try {
            status->setText("writing...");
            p->writeCV(cv, value, (ProgListener*)this);
        } catch (ProgrammerException ex) {
            state = IDLE;
            status->setText("" + ex.getMessage());
        }
    }
}

void DualDecoderSelectPane::readCV16() {
    Programmer* p = modePane->getProgrammer();
    if (p == NULL) {
        state = IDLE;
        status->setText("No programmer connected");
    } else {
        try {
            status->setText("reading...");
            state = READCV16;
            p->readCV(16, (ProgListener*)this);
        } catch (ProgrammerException ex) {
            state = IDLE;
            status->setText("" + ex.getMessage());
        }
    }
}


/*public*/ void DualDecoderSelectPane::programmingOpReply(int value, int retcode) {
    switch (mode) {
        case SEARCH:
            searchReply(value, retcode);
            break;
        case INIT:
            initReply(value, retcode);
            break;
        default:
            log->warn("unexpected mode: " + mode);
            break;
    }
}

void DualDecoderSelectPane::searchReply(int value, int retcode) {
    switch (state) {
        case IDLE:
        default:
            // shouldn't happen, reset and ignore
            log->warn("Unexpected search programming reply: " + QString::number(value) + " " + QString::number(retcode));
            state = IDLE;
            break;
        case WROTECV15:
            //confirm OK
            readCV16();
            break;
        case READCV16:
            // was it OK?
            QString result = "OK";
            if (retcode != ProgListener::OK) {
                log->debug("Readback error: " + QString::number(retcode) + " " + QString::number(value));
                labels->at(next)->setEnabled(false);
                buttons->at(next)->setEnabled(false);
                result = "Could not confirm: " + modePane->getProgrammer()->decodeErrorCode(retcode);
            } else if (value != next) {
                log->debug("Readback error: " + QString::number(retcode) + " " + QString::number(value));
                if (scanning) {
                    labels->at(next)->setEnabled(false);
                    buttons->at(next)->setEnabled(false);
                }
                result = "Unexpected ID read: " +QString::number(value);
            }
            // go on to next?
            if (scanning) {
                next++;
                if (next >= NENTRIES) {
                    state = IDLE;
                    next = 0;
                    scanning = false;
                    status->setText("Idle");
                    searchButton->setChecked(false);
                    break;
                }
                select(next);
                break;
            } else {
                status->setText(result);
                break;
            }
    }
}

/**
 * Start process of initializing a Digitrax and legacy decoder. Operations
 * are:
 * <ol>
 * <li>Write 1 to CV16, which will write both decoders
 * <li>Write 7 to CV15, which will turn off Digitrax
 * <LI>Write 7 to CV16, which will be stored in the legacy decoder only
 * </ol>
 */
void DualDecoderSelectPane::doInit() {
    mode = INIT;
    state = FIRSTCV16;
    writeCV16(1);
}

void DualDecoderSelectPane::initReply(int value, int retcode) {
    switch (state) {
        case IDLE:
        default:
            // shouldn't happen, reset and ignore
            log->warn("Unexpected init programming reply: " + QString::number(value) + " " + QString::number(retcode));
            state = IDLE;
            break;
        case FIRSTCV16:
            state = FIRSTCV15;
            if (retcode != ProgListener::OK) {
                log->debug("Readback error: " + QString::number(retcode) + " " + QString::number(value));
                status->setText("Write CV15=7 failed!");
                state = IDLE;
            } else { // is OK
                writeCV15(7);
            }
            break;
        case FIRSTCV15:
            state = SECONDCV16;
            if (retcode != ProgListener::OK) {
                log->debug("Readback error: " + QString::number(retcode) + " " + QString::number(value));
                status->setText("Write CV16=7 failed!");
                state = IDLE;
            } else { // is OK
                writeCV16(7);
            }
            break;
        case SECONDCV16:
            if (retcode != ProgListener::OK) {
                log->debug("Readback error: " + QString::number(retcode) + " " + QString::number(value));
                status->setText("Write CV16=1 failed!");
                state = IDLE;
            } else { // is OK
                state = IDLE;
                status->setText("Initialized");
            }
            break;
    }
}

//static Logger log = LoggerFactory.getLogger(DualDecoderSelectPane.class.getName());

//}
