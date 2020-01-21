#include "sprogslotmonframe.h"
#include "loggerfactory.h"
#include "flowlayout.h"
#include <QBoxLayout>
#include <QTimer>
#include "sprogreply.h"
#include "sprogslotmondatamodel.h"
#include <QMenuBar>

using namespace Sprog;
/**
 * Frame providing a command station slot manager.
 * <P>
 * May-17 Modified to a SprogListener to handle status replies.
 *
 * Jan-18 Moved status request generation here, based on a timer.
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 * @author  Andrew Crosland (C) 2006 ported to SPROG 2008
 */
///*public*/ class SprogSlotMonFrame extends jmri.util.JmriJFrame implements SprogListener {
/*private*/ /*static*/ /*final*/ int SprogSlotMonFrame::STATUS_PERIOD = 500;


/*public*/ SprogSlotMonFrame::SprogSlotMonFrame(SprogSystemConnectionMemo* memo, QWidget* parent) : JmriJFrame(parent) {
   // super();
 /**
  * Controls whether not-in-use slots are shown.
  */
 showAllCheckBox = new QCheckBox();
 estopAllButton = new QPushButton(tr("EstopAll"));
 slotModel = NULL;
 status = new JTextArea(tr("Track Current%1").arg("---"));
 mShown = false;

 _memo = NULL;
 tc = NULL;

 timer = NULL;

    _memo = memo;

    tc = memo->getSprogTrafficController();
    tc->addSprogListener((SprogListener*)this);

    slotModel = new SprogSlotMonDataModel(SprogConstants::MAX_SLOTS, 8,_memo);

    slotTable = new JTable(slotModel);
//    slotTable->setRowSorter(new TableRowSorter<>(slotModel));
//    slotScroll = new JScrollPane(slotTable);

    // configure items for GUI
    showAllCheckBox->setText(tr("ButtonShowUnusedSlots"));
    showAllCheckBox->setVisible(true);
    showAllCheckBox->setChecked(true);
    showAllCheckBox->setToolTip(tr("ButtonShowSlotsTooltip"));

    slotModel->configureTable(slotTable);

    // add listener object so checkboxes function
//    showAllCheckBox.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            slotModel.showAllSlots(showAllCheckBox.isSelected());
//            slotModel.fireTableDataChanged();
//        }
//    });

    // add listener object so stop all button functions
//    estopAllButton.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            log->debug("Estop all button pressed");
//            _memo.getCommandStation().estopAll();
//        }
//    });

//    estopAllButton.addMouseListener(new MouseListener() {
//        //@Override
//        /*public*/ void mousePressed(MouseEvent e) {
//            _memo.getCommandStation().estopAll();
//        }

//        //@Override
//        /*public*/ void mouseExited(MouseEvent e) {
//        }

//        //@Override
//        /*public*/ void mouseEntered(MouseEvent e) {
//        }

//        //@Override
//        /*public*/ void mouseReleased(MouseEvent e) {
//        }

//        //@Override
//        /*public*/ void mouseClicked(MouseEvent e) {
//        }
//    });

    // adjust model to default settings
    slotModel->showAllSlots(showAllCheckBox->isChecked());

    // general GUI config
    setTitle(tr("Sprog SlotMonitor"));
    //getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
    QVBoxLayout* contentPaneLayout = new QVBoxLayout(getContentPane());

    // install items in GUI
    QWidget* pane1 = new QWidget();
    //pane1->setLayout(new FlowLayout());
    FlowLayout* pane1Layout = new FlowLayout(pane1);

    pane1Layout->addWidget(showAllCheckBox);
    pane1Layout->addWidget(estopAllButton);
    pane1Layout->addWidget(status);

    contentPaneLayout->addWidget(pane1);
    contentPaneLayout->addWidget(slotTable);

    setHelp();

    pack();
    pane1->setMaximumSize(pane1->size());
    pack();

    startTimer(STATUS_PERIOD);
}

/**
 * Define system-specific help item
 */
/*protected*/ void SprogSlotMonFrame::setHelp() {
    addHelpMenu("package.jmri.jmrix.sprog.sprogslotmon.SprogSlotMonFrame", true);  // NOI18N
}

/**
 * Find the existing SprogSlotMonFrame object.
 * @deprecated JMRI Since 4.4 instance() shouldn't be used, convert to JMRI multi-system support structure
 */
//@Deprecated
/*static*/ /*public*/ /*final*/ SprogSlotMonFrame* instance() {
    return NULL;
}

/*public*/ void SprogSlotMonFrame::update() {
    slotModel->fireTableDataChanged();
}

/*public*/ void SprogSlotMonFrame::updateStatus(QString a) {
    status->setText(tr("Track Current %1").arg(a));
}


/**
 * Listen to outgoing messages.
 *
 * @param m the sprog message received
 */
//@Override
/*public*/ void SprogSlotMonFrame::notifyMessage(SprogMessage* /*m*/) {
    // Do nothing
}

/**
 * Listen for status replies.
 *
 * @param m The SprogReply to be handled
 */
//@Override
/*public*/ void SprogSlotMonFrame::notifyReply(SprogReply* m) {
    QVector<int> statusA = QVector<int>(4);
    QString s = m->toString();
    log->debug(tr("Reply received: %1").arg(s));
    if (s.indexOf('S') > -1) {
        // Handle a status reply
        log->debug("Status reply");
        int i = s.indexOf('h');
        // Double Check that "h" was found in the reply
        if (i > -1) {
         bool bok;
            int milliAmps = (int) ((("0x" + s.mid(i + 7, i + 11)).toInt(&bok,16)) *
                        tc->getAdapterMemo()->getSprogType()->getCurrentMultiplier());
            statusA[0] = milliAmps;
            QString ampString;
            ampString = QString::number((float) statusA[0] / 1000);
            updateStatus(ampString);
        }
    }
}

//@Override
/*public*/ void SprogSlotMonFrame::addNotify() {
    JmriJFrame::addNotify();

    if (mShown) {
        return;
    }

    // resize frame to account for menubar
    QMenuBar* jMenuBar =menuBar();
    if (jMenuBar != NULL) {
        int jMenuBarHeight = jMenuBar->sizeHint().height();
        QSize dimension = size();
        dimension.setHeight(size().height() + jMenuBarHeight);
        resize(dimension);
    }
    mShown = true;
}

//@Override
/*public*/ void SprogSlotMonFrame::dispose() {
    // deregister with the command station.
    stopTimer();
    slotModel->dispose();
    slotModel = NULL;
    slotTable = NULL;
    //slotScroll = NULL;
    JmriJFrame::dispose();
}

/**
 * Internal routine to handle a timeout
 */
/*synchronized*/ /*protected*/ void SprogSlotMonFrame::timeout() {
#if 0
    Runnable r = () -> {
        // Send a status request
        log->debug("Sending status request");
        tc.sendSprogMessage(SprogMessage.getStatus(), this);
    };
    javax.swing.SwingUtilities.invokeLater(r);
#endif
}

/**
 * Internal routine to handle timer starts {@literal &} restarts
 *
 * @param delay timer delay
 */
/*protected*/ void SprogSlotMonFrame::startTimer(int delay) {
    log->debug("Restart timer");
    if (timer == NULL)
    {
        timer = new QTimer(); //delay, (java.awt.event.ActionEvent e) -> {
//            timeout();
//        }//);
    }
    connect(timer, SIGNAL(timeout()),this, SLOT(timeout()));
    timer->stop();
    //timer->setInitialDelay(delay);
    timer->setSingleShot(false);
    timer->start(delay);
}

/**
 * Internal routine to handle timer stop
 */
/*protected*/ void SprogSlotMonFrame::stopTimer() {
    log->debug("Stop timer");
    if (timer != NULL) {
        timer->stop();
    }
}

/*public*/ QString SprogSlotMonFrame::getClassName()
{
 return "jmri.jmrix.sprog.sprogslotmon.SprogSlotMonFrame";
}


/*private*/ /*final*/ /*static*/ Logger* SprogSlotMonFrame::log = LoggerFactory::getLogger("SprogSlotMonFrame");
