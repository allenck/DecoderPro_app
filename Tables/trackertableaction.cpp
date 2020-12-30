#include "trackertableaction.h"
#include "tracker.h"
#include <QPushButton>
#include "jtextfield.h"
#include "jtable.h"
#include <QSortFilterProxyModel>
#include "tablecolumnmodel.h"
#include "tablecolumn.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include "oblock.h"
#include <QLabel>
#include "jdialog.h"
#include "gridbagconstraints.h"
#include "instancemanager.h"
#include "oblockmanager.h"
#include <QMessageBox>
#include <picklistmodel.h>
#include "pickpanel.h"
#include "itempalette.h"
#include "warrant.h"
#include "inputdialog.h"
#include <QMenu>
#include "warranttableaction.h"

TrackerTableAction::TrackerTableAction(QObject *parent) :
  AbstractAction(tr("Trackers"), parent)
{
 common();
}

/**
 * This singleton class displays a table of the occupancy detection trackers
 *
 * @author Peter Cressman
 *
 */
///*public*/ class TrackerTableAction extends AbstractAction {

/**
 *
 */
///*private*/ static final long serialVersionUID = -3359499686576807040L;

/*static*/ int TrackerTableAction::STRUT_SIZE = 10;

/*private*/ /*static*/ TrackerTableAction* TrackerTableAction::_instance;
/*private*/ /*static*/ QList<Tracker*> TrackerTableAction::_trackerList =  QList<Tracker*>();
/*private*/ /*static*/ TableFrame* TrackerTableAction::_frame = NULL;
/*public*/ /*static*/ int TableFrame::_maxHistorySize = 20;


/*private*/ TrackerTableAction::TrackerTableAction(QString menuOption,QObject *parent) :
  AbstractAction(menuOption, parent) {
    //super(menuOption);
 common();
}
void TrackerTableAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ /*static*/ TrackerTableAction* TrackerTableAction::getInstance(QObject* parent) {
    if (_instance == NULL) {
        _instance = new TrackerTableAction(tr("Trackers"),parent);
    }
    return _instance;
}

/*public*/ void TrackerTableAction::actionPerformed(JActionEvent * /*e*/) {
    if (_frame != NULL) {
        _frame->setVisible(true);
    } else {
        _frame = new TableFrame();
    }
}

/*synchronized*/ /*static*/ /*public*/ bool TrackerTableAction:: mouseClickedOnBlock(OBlock* block) {
    if (_frame != NULL) {
        return _frame->mouseClickedOnBlock(block);
    }
    return false;
}

/*static*/ /*public*/ Tracker* TrackerTableAction::markNewTracker(OBlock* block, QString name) {
    if (_frame == NULL) {
        _frame = new TableFrame();
    }
    return _frame->addTracker(block, name);
}

/*static*/ /*public*/ void TrackerTableAction::stopTracker(Tracker* t) {
    if (_frame == NULL) {
        _frame = new TableFrame();
    }
    _frame->stopTrain(t);
}

/*static*/ /*public*/ void TrackerTableAction::stopTrackerIn(OBlock* block) {
 QListIterator<Tracker*> iter(_trackerList);
    while (iter.hasNext()) {
        Tracker* t = iter.next();
        if (t->getBlocksOccupied().contains(block)) {
            if (_frame == NULL) {
                _frame = new TableFrame();
            }
            _frame->stopTrain(t);
            return;
        }
    }
}

/**
 * Holds a table of Trackers that follow adjacent occupancy. Needs to be a
 * singleton to be opened and closed for trackers to report to it
 *
 * @author Peter Cressman
 *
 */
//static class TableFrame extends JmriJFrame implements PropertyChangeListener, MouseListener {

TableFrame::TableFrame()
{
 log = new Logger("TableFrame");
 _trainNameBox = new JTextField(30);
 _trainLocationBox = new JTextField(30);
 JTextField* _status = new JTextField(80);
 QStringList _statusHistory =  QStringList();
 _appendStatus = false;
 _blocks =  QHash<OBlock*, QList<Tracker*> >();
 setTitle(tr("Tracker Table"));
 _model = new TrackerTableModel(this);
 //try {   // following might fail due to a missing method on Mac Classic
 QSortFilterProxyModel* sorter = new QSortFilterProxyModel(/*_model*/);
 sorter->setSourceModel(_model);
 JTable* table = new JTable(_model);
//     table = jmri.util.JTableUtil.sortableDataModel(sorter);
//     sorter.setTableHeader(table.getTableHeader());
//     // set model last so later casts will work
//     ((jmri.util.com.sun.TableSorter) table.getModel()).setTableModel(_model);
// } catch (Throwable e) { // NoSuchMethodError, NoClassDefFoundError and others on early JVMs
//     Logger::error("WarrantTable: Unexpected error: " + e);
//     table = new JTable(_model);
// }
// table->getColumnModel()->getColumn(TrackerTableModel::STOP_COL).setCellEditor(new ButtonEditor(new JButton()));
// table.getColumnModel().getColumn(TrackerTableModel.STOP_COL).setCellRenderer(new ButtonRenderer());
 for (int i = 0; i < _model->columnCount(QModelIndex()); i++) {
     int width = _model->getPreferredWidth(i);
     table->getColumnModel()->getColumn(i)->setPreferredWidth(width);
 }
 table->setDragEnabled(true);
// table.setTransferHandler(new jmri.util.DnDTableExportHandler());
 //JScrollPane tablePane = new JScrollPane(table);
// QSize dim = table->sizeHint();
// table.getRowHeight(new JButton("STOPIT").getPreferredSize().height);
// dim.height = table.getRowHeight() * 2;
// tablePane.getViewport().setPreferredSize(dim);

 QWidget* tablePanel = new QWidget();
 //tablePanel.setLayout(new BoxLayout(tablePanel, BoxLayout.Y_AXIS));
 QVBoxLayout* tablePanelLayout = new QVBoxLayout(tablePanel);
 QLabel* title = new QLabel(tr("TrackerTable"));
 tablePanelLayout->addWidget(title, /*BorderLayout.NORTH*/0, Qt::AlignTop);
 tablePanelLayout->addWidget(tablePanel, /*BorderLayout.CENTER*/0, Qt::AlignCenter);

 QWidget* panel = new QWidget();
 FlowLayout* panelLayout = new FlowLayout(panel);
 QWidget* p = new QWidget();
 FlowLayout* pLayout = new FlowLayout(p);
 pLayout->addWidget(new QLabel(tr("lastEvent")));
 pLayout->addWidget(_status);
 _status->setEnabled(false);
 _status->setBackground(QColor(Qt::white));
 //_status->addMouseListener(this);
 panelLayout->addWidget(p);

 {
 p = new QWidget();
 FlowLayout* pLayout = new FlowLayout(p);
 QPushButton* button = new QPushButton(tr("New Tracker"));
// button.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent a) {
//         newTrackerDialog();
//     }
// });
 connect(button, SIGNAL(clicked()), this, SLOT(newTrackerDialog()));
 tablePanelLayout->addWidget(p, /*BorderLayout.CENTER*/0, Qt::AlignCenter);
 pLayout->addWidget(button);

 button = new QPushButton(tr("Refresh"));
// button.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent a) {
//         _model->fireTableDataChanged();
//     }
// });
 connect(button, SIGNAL(clicked()), this,SLOT(on_refreshClicked()));
 tablePanelLayout->addWidget(p, /*BorderLayout.CENTER*/0, Qt::AlignCenter);
 pLayout->addWidget(button);

 button = new QPushButton(tr("OBlock Pick List"));
// button.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent a) {
//         openPickList();
//     }
// });
 connect(button, SIGNAL(clicked()), this, SLOT(openPickList()));
 tablePanelLayout->addWidget(p, /*BorderLayout.CENTER*/0, Qt::AlignCenter);
 pLayout->addWidget(button);
}
 panelLayout->addWidget(p);
 tablePanelLayout->addWidget(panel, /*BorderLayout.CENTER*/0, Qt::AlignCenter);

// addWindowListener(new java.awt.event.WindowAdapter() {
//     /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//         dispose();
//     }
// });
 addWindowListener(new TTAWindowListener(this));
 setCentralWidget(tablePanel);

 // TODO:
// addWindowListener(new java.awt.event.WindowAdapter() {
//     /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//         setDefaultCloseOperation(javax.swing.WindowConstants.HIDE_ON_CLOSE);
//         _model->fireTableDataChanged();
//     }
// });
 setLocation(0, 100);
 setVisible(true);
 adjustSize();
}

void TableFrame::on_refreshClicked()
{
 _model->fireTableDataChanged();
}

/*protected*/ bool TableFrame::mouseClickedOnBlock(OBlock* block) {
    if (_dialog != NULL) {
        _trainLocationBox->setText(block->getDisplayName());
        if (block->getValue() != QVariant()) {
            _trainNameBox->setText( block->getValue().toString());
        }
        return true;
    }
    if ((block->getState() & OBlock::OCCUPIED) != 0 && block->getValue() != QVariant()) {
        TrackerTableAction::markNewTracker(block, block->getValue().toString());
        return true;
    }
    return false;
}

/*private*/ void TableFrame::newTrackerDialog() {
    _dialog = new JDialog(this, tr("New Tracker"), false);
    QWidget* panel = new QWidget();
    //panel.setLayout(new BorderLayout(10, 10));
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);
    QWidget* mainPanel = new QWidget();
    QVBoxLayout* mainPanelLayout = new QVBoxLayout(mainPanel);
   // mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));

    mainPanelLayout->addStrut(TrackerTableAction::STRUT_SIZE);
    QWidget* p = new QWidget();
    FlowLayout* pLayout = new FlowLayout(p);
    pLayout->addWidget(new QLabel(tr("Create Tracker")));
    mainPanelLayout->addWidget(p);

    mainPanelLayout->addStrut(TrackerTableAction::STRUT_SIZE);
    mainPanelLayout->addWidget(makeTrackerNamePanel());
    mainPanelLayout->addStrut(TrackerTableAction::STRUT_SIZE);
    mainPanelLayout->addWidget(makeDoneButtonPanel());
    panelLayout->addWidget(mainPanel);
    //_dialog.getContentPane().add(panel);
    QVBoxLayout* dialogLayout = new QVBoxLayout(_dialog);
    dialogLayout->addWidget(panel);
    _dialog->setLocation(this->pos().x() + 100, this->pos().y() + 100);
    _dialog->adjustSize();
    _dialog->setVisible(true);
}

/*private*/ QWidget* TableFrame::makeTrackerNamePanel() {
    _trainNameBox->setText("");
    _trainLocationBox->setText("");
    QWidget* namePanel = new QWidget();
    //namePanel.setLayout(new BoxLayout(namePanel, BoxLayout.Y_AXIS));
    QVBoxLayout* namePanelLayout = new QVBoxLayout(namePanel);
    QWidget* p = new QWidget();
    //p.setLayout(new java.awt.GridBagLayout());
    QGridLayout* pLayout = new QGridLayout(p);
    GridBagConstraints c =  GridBagConstraints();
    c.gridwidth = 1;
    c.gridheight = 1;
    c.gridx = 0;
    c.gridy = 0;
    c.anchor = GridBagConstraints::EAST;
    pLayout->addWidget(new QLabel(tr("Train Name")), c.gridy, c.gridx, c.rowSpan(), c.colSpan());
    c.gridy = 1;
    pLayout->addWidget(new QLabel(tr("Train Location")), c.gridy, c.gridx, c.rowSpan(), c.colSpan());
    c.gridx = 1;
    c.gridy = 0;
    c.anchor = GridBagConstraints::WEST;
    c.weightx = 1.0;
    c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
    pLayout->addWidget(_trainNameBox, c.gridy, c.gridx, c.rowSpan(), c.colSpan());
    c.gridy = 1;
    pLayout->addWidget(_trainLocationBox, c.gridy, c.gridx, c.rowSpan(), c.colSpan());
    namePanelLayout->addWidget(p);
    return namePanel;
}

/*private*/ QWidget* TableFrame::makeDoneButtonPanel() {
    QWidget* buttonPanel = new QWidget();
    FlowLayout* buttonPanelLayout = new FlowLayout(buttonPanel);
    QWidget* panel0 = new QWidget();
    //panel0.setLayout(new FlowLayout());
    FlowLayout* panel0Layout = new FlowLayout;
    QPushButton* doneButton;
    doneButton = new QPushButton(tr("Done"));
//    doneButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            if (doDoneAction()) {
//                _dialog.dispose();
//                _dialog = NULL;
//            }
//        }
//    });
    connect(doneButton, SIGNAL(clicked()), this, SLOT(on_doneButton_clicked()));
    panel0Layout->addWidget(doneButton);
    buttonPanelLayout->addWidget(panel0);
    return buttonPanel;
}
void TableFrame::on_doneButton_clicked()
{
 if (doDoneAction())
 {
     _dialog->close();
     _dialog = NULL;
 }
}
/*private*/ bool TableFrame::doDoneAction() {
    bool retOK = false;
    QString blockName = _trainLocationBox->text();
    if (blockName != NULL) {
     OBlock* block = ((OBlockManager*) InstanceManager::getDefault("OBlockManager"))->getOBlock(blockName.trimmed());
        if (block == NULL) {
//            JOptionPane.showMessageDialog(this, tr("BlockNotFound", blockName),
//                    tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
         QMessageBox::warning(this, tr("Warning"),tr("Block \"%1\" not found.").arg(blockName));
        } else {
            retOK = (addTracker(block, _trainNameBox->text()) != NULL);
        }
    }
    return retOK;
}

/*public*/ Tracker* TableFrame::addTracker(OBlock* block, QString name) {
    if ((block->getState() & OBlock::OCCUPIED) == 0) {
//        JOptionPane.showMessageDialog(this, tr("blockUnoccupied", block->getDisplayName()),
//                tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(this, tr("Warning"),tr("Block \"%1\" is unoccupied.  Tracker must start on an occupied block.").arg(block->getDisplayName()));
        return NULL;
    } else if (name == NULL || name.length() == 0) {
//        JOptionPane.showMessageDialog(this, tr("noName"),
//                tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(this, tr("Warning"),tr("noName"));

        return NULL;
    } else if (nameInuse(name)) {
//        JOptionPane.showMessageDialog(this, tr("duplicateName", name),
//                tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(this, tr("Warning"),tr("Tracker name \"%1\" is in use.").arg(name));
        return NULL;
    } else {
        QString oldName = blockInUse(block);
        if (oldName != NULL && name!=(block->getValue())) {
//            JOptionPane.showMessageDialog(this, tr("blockInUse", oldName, block->getDisplayName()),
//                    tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
         QMessageBox::warning(this, tr("Warning"),tr("Block \"%2\" is currently occupied by Tracker \"%1\".").arg(oldName).arg(block->getDisplayName()));
            return NULL;
        }
        Tracker* newTracker = new Tracker(block, name);
        newTracker->setupCheck();
        TrackerTableAction::_trackerList.append(newTracker);
        addBlockListeners(newTracker);
        _model->fireTableDataChanged();
        setStatus(tr("Tracker begun for \"%1\" in block \"%2\".").arg( name).arg( block->getDisplayName()));
        return newTracker;
    }
}

/*static*/ /*protected*/ QString TableFrame::blockInUse(OBlock* b) {
 QListIterator<Tracker*> iter(TrackerTableAction::_trackerList);
    while (iter.hasNext()) {
        Tracker* t = iter.next();
        if (t->getBlocksOccupied().contains(b)) {
            return t->getTrainName();
        }
    }
    return NULL;
}

/*static*/ bool TableFrame::nameInuse(QString name) {
 QListIterator<Tracker*> iter(TrackerTableAction::_trackerList);
    while (iter.hasNext()) {
        Tracker* t = iter.next();
        if (name==(t->getTrainName())) {
            return true;
        }
    }
    return false;
}

void TableFrame::openPickList() {
    _pickFrame = new JmriJFrameX("Pick");
    QWidget* content = new QWidget();
    //content.setLayout(new BoxLayout(content, BoxLayout.Y_AXIS));
    QVBoxLayout* contentLayout = new QVBoxLayout(content);

    QWidget* blurb = new QWidget();
    //blurb.setLayout(new BoxLayout(blurb, BoxLayout.Y_AXIS));
    QVBoxLayout* blurbLayout = new QVBoxLayout(blurb);
    blurbLayout->addStrut(ItemPalette::STRUT_SIZE);
//	        blurb.add(new QLabel(tr("DragOccupancyName")));
//	        blurb.add(new QLabel(tr("DragErrorName")));
    blurbLayout->addStrut(ItemPalette::STRUT_SIZE);
    QWidget* panel = new QWidget();
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);
    panelLayout->addWidget(blurb);
    contentLayout->addWidget(panel);
    QList<PickListModel*> models =  QList<PickListModel*>() << PickListModel::oBlockPickModelInstance();
    contentLayout->addWidget(new PickPanel(models));

    //_pickFrame.setContentPane(content);
    _pickFrame->setCentralWidget(content);
    /*	        _pickFrame.addWindowListener(new java.awt.event.WindowAdapter() {
     public void windowClosing(java.awt.event.WindowEvent e) {
     closePickList();
     }
     });*/
//    _pickFrame->setLocationRelativeTo(this);
    _pickFrame->toFront();
    _pickFrame->setVisible(true);
    _pickFrame->adjustSize();
}

/**
 * Adds listeners to all blocks in the range of a Tracker::
 * Called when a new tracker is created.
 *
 * @param newTracker
 */
/*private*/ void TableFrame::addBlockListeners(Tracker* tracker) {
    QList<OBlock*> range = tracker->getRange();
    if (log->isDebugEnabled()) {
        log->debug("addBlockListeners for tracker= \"" + tracker->getTrainName()
                + "\" has range of " + QString::number(range.size()) + " blocks.");
    }
    QListIterator<OBlock*> iter(range);
    while (iter.hasNext()) {
        addBlockListener(iter.next(), tracker);
    }
}

/**
 * Adds listener to a block when a tracker enters.
 */
/*private*/ void TableFrame::addBlockListener(OBlock* block, Tracker* tracker) {
    QList<Tracker*> trackers = _blocks.value(block);
    if (!trackers .isEmpty()) {
        trackers =  QList<Tracker*>();
        trackers.append(tracker);
        _blocks.insert(block, trackers);
        block->addPropertyChangeListener((PropertyChangeListener*)this);
        connect(block->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*())));
        if (log->isDebugEnabled()) {
            log->debug("\taddPropertyChangeListener for block " + block->getDisplayName());
        }
    } else {
        if (trackers.size() == 0) {
            block->addPropertyChangeListener((PropertyChangeListener*)this);
            connect(block->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*())));
            if (log->isDebugEnabled()) {
                log->debug("\taddPropertyChangeListener for block " + block->getDisplayName());
            }
        } else {
            if (log->isDebugEnabled()) {
                log->debug("\tassumed block " + block->getDisplayName() + "already has listener");
            }
        }
        if (!trackers.contains(tracker)) {
            trackers.append(tracker);
        }
    }
}

/**
 * Do Venn Diagram between the two sets. Keep listeners held in common.
 * Add new listeners. Remove old.
 */
/*private*/ void TableFrame::adjustBlockListeners(QList<OBlock*> oldRange, QList<OBlock*> newRange, Tracker* tracker) {
 QListIterator<OBlock*> iter(newRange);
    while (iter.hasNext()) {
        OBlock* b = iter.next();
        if (oldRange.contains(b)) {
            oldRange.removeOne(b);
            continue;	// held in common. keep listener
        }
        addBlockListener(b, tracker);       // new block->  Add Listener
    }
    // blocks left in oldRange were not found in newRange.  Remove Listeners
    iter = QListIterator<OBlock*>(oldRange);
    while (iter.hasNext()) {
        removeBlockListener(iter.next(), tracker);
    }

}

/*private*/ void TableFrame::removeBlockListeners(QList<OBlock*> range, Tracker* tracker) {
    if (log->isDebugEnabled()) {
        log->debug("removeBlockListeners for tracker= \"" + tracker->getTrainName()
                + "\" has " + QString::number(range.size()) + " blocks to remove.");
    }
    QListIterator<OBlock*> iter(range);
    while (iter.hasNext()) {
        removeBlockListener(iter.next(), tracker);
    }
}

/*private*/ void TableFrame::removeBlockListener(OBlock* b, Tracker* tracker) {
    QList<Tracker*> trackers = _blocks.value(b);
    if (!trackers.isEmpty()) {
        trackers.removeOne(tracker);
        if (trackers.size() == 0) {
            b->removePropertyChangeListener((PropertyChangeListener*)this);
            disconnect(b->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*())));
            if (log->isDebugEnabled()) {
                log->debug("removeBlockListener on block " + b->getDisplayName()
                        + " for tracker= " + tracker->getTrainName());
            }
        }
    } else {
        Logger::error("Block \"" + b->getDisplayName() + "\" has no listeners.  Tracker for train "
                + tracker->getTrainName() + " expected a listener");
    }
}

/*public*/ void TableFrame::propertyChange(PropertyChangeEvent* evt)
{
    if (evt->getPropertyName()==("state")) {
        OBlock* b = (OBlock*) evt->getSource();
        int state =  evt->getNewValue().toInt();
        int oldState =  evt->getOldValue().toInt();
        if (log->isDebugEnabled()) {
            log->debug("propertyChange to block= "+b->getDisplayName()+" state= "+state+" oldstate= "+oldState);
        }
        // The "jiggle" (see tracker->showBlockValue() causes some state changes to be duplicated.
        // The following washes out the extra notifications
/*                if ((state & (OBlock::UNOCCUPIED | OBlock::RUNNING)) == (OBlock::UNOCCUPIED | OBlock::RUNNING)) {
            b.setState(state & ~OBlock::RUNNING);
            return;		// will do the tracker->move() on the next (repeat call
        } else if ((state & OBlock::RUNNING) != 0) {
            return;		// repeats previous call that was completed.
        }*/
        if ((state & (OBlock::UNOCCUPIED | OBlock::RUNNING)) == (oldState & (OBlock::UNOCCUPIED | OBlock::RUNNING)) &&
                (state & (OBlock::OCCUPIED | OBlock::RUNNING)) == (oldState & (OBlock::OCCUPIED | OBlock::RUNNING))) {
            return;
        }
        QList<Tracker*> trackers = _blocks.value(b);
        if (!trackers.isEmpty()) {
            Logger::error("No Trackers found for block " + b->getDisplayName() + " going to state= " + state);
            b->removePropertyChangeListener((PropertyChangeListener*)this);
            disconnect(b->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*())));

        } else {
            // perhaps several trackers listen for this block
            if ((state & OBlock::OCCUPIED) != 0) {
                // going occupied
             if (b->getValue() == QVariant()) {
                    //String[] trains = new String[trackers.size()];
                 QVector<QString> trains = QVector<QString>(trackers.size());
                    int i = 0;
                    Warrant* w = b->getWarrant();
                    if (w != NULL) {
                        int idx = w->getCurrentOrderIndex();
                        // Was it a warranted train that entered the block,
                        // is distance of 1 block OK?
                        // Can't tell who got notified first - tracker or warrant?
                        if (w->getIndexOfBlock(b, idx) - idx < 2) {
                            return;
                        }
                    }
                    QListIterator<Tracker*> iter(trackers);
                    while (iter.hasNext()) {
                        Tracker* t = iter.next();
                        trains.replace(i++, t->getTrainName());
                    }
                    Tracker* t = trackers.at(0);
                    if (i > 1)
                    {
                     QVariant selection = QVariant();
                     // TODO: modify InputDialog
//                        Object selection = JOptionPane.showInputDialog(this, tr("MultipleTrackers",
//                                b->getDisplayName()), tr("WarningTitle"),
//                                JOptionPane.INFORMATION_MESSAGE, NULL, trains, NULL);
                     QMessageBox::warning(this, tr("Warning"), tr("Block \"%2\" may be entered by one of the following trains.\nPlease select which train has entered \"%1\"."));
                       if (selection != QVariant()) {
                            iter = QListIterator<Tracker*>(TrackerTableAction::_trackerList);
                            while (iter.hasNext()) {
                                t = iter.next();
                                if (((QString) selection.toString())==(t->getTrainName())) {
                                    break;
                                }
                            }
                        } else {
                            return;
                        }
                    }
                    processTrackerStateChange(t, b, state);
                } else {
                    log->warn("Block " + b->getDisplayName() + " going active with value= "
                            + b->getValue().toString() + " Wasup wi dat?");
                }
            } else if ((state & OBlock::UNOCCUPIED) != 0) {
                // b going unoccupied.
                // to avoid ConcurrentModificationException if a tracker is deleted, use a copy
                QVector<Tracker*> copy =  QVector<Tracker*>(trackers.size());
                  QListIterator<Tracker*> iter(trackers);
                int i = 0;
                while (iter.hasNext()) {
                    copy.replace(i++, iter.next());
                }
                for (int k = 0; k < i; k++) {
                    processTrackerStateChange(copy[k], b, state);
                }
            }
        }
/*               if ((state & OBlock::UNOCCUPIED) != 0) {
            b.setValue(NULL);
        }*/
    }
    _model->fireTableDataChanged();
}

/**
 * Called when a state change has occurred for one the blocks listened
 * to for this tracker-> Trackcr.move makes the changes to OBlocks to
 * indicate the new occupancy positions of the train. Upon return,
 * update the listeners for the trains next move
 *
 * @param tracker
 * @param block
 * @param state
 */
/*private*/ void TableFrame::processTrackerStateChange(Tracker* tracker, OBlock* block, int state)
{
 QList<OBlock*> oldRange = tracker->getRange();// range in effect when state change was detected
 switch (tracker->move(block, state))
 {
  case Tracker::NO_BLOCK:
  {
   adjustBlockListeners(oldRange, tracker->getRange(), tracker);
   QString msg = tr("\%1\" unknown. Its last known location at \"%2\" is unoccupied.").arg(tracker->getTrainName()).arg(
           block->getDisplayName()) + "\n" + tr("Tracking Stopped.");
//            JOptionPane.showMessageDialog(this, msg,
//                    tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
   QMessageBox::warning(this, tr("Warning"), msg);
   stopTrain(tracker);
   setStatus(msg);
   break;
 }
     case Tracker::ENTER_BLOCK:
  {
         block->_entryTime = QDateTime::currentMSecsSinceEpoch();
         adjustBlockListeners(oldRange, tracker->getRange(), tracker);
         setStatus(tr("Train \"%1}\" entering block \"%2\".").arg(tracker->getTrainName()).arg(
                 block->getDisplayName()));
         break;
  }
     case Tracker::LEAVE_BLOCK:
  {
         adjustBlockListeners(oldRange, tracker->getRange(), tracker);
         long et = (QDateTime::currentMSecsSinceEpoch() - block->_entryTime) / 1000;
         setStatus(tr("Train \"%1\" leaving block \"%2\". Occupied block for %3 minutes %4 seconds.").arg( tracker->getTrainName()).arg(
                 block->getDisplayName()).arg(et / 60).arg( et % 60));
         break;
  }
  case Tracker::ERROR_BLOCK:
  {
   // tracker wrote error message
    break;
  }
 }
}

/*protected*/ void TableFrame::stopTrain(Tracker* t)
{
    QList<OBlock*> list0 = t->getRange();
    removeBlockListeners(list0, t);
    QListIterator<OBlock*> iter0(list0);
    while (iter0.hasNext())
    {
        OBlock* b = iter0.next();
        t->removeBlock(b);
    }
    QLinkedList<OBlock*> list = t->getBlocksOccupied();
//			removeBlockListeners(list, t);
    QLinkedListIterator<OBlock*> iter(list);
    while (iter.hasNext()) {
        OBlock* b = iter.next();
        long et = (QDateTime::currentMSecsSinceEpoch() - b->_entryTime) / 1000;
        setStatus(tr("Train \"%1\" Occupied block \"%2\" for %3 minutes %4 seconds.").arg(t->getTrainName()).arg(
                b->getDisplayName()).arg( et / 60).arg(et % 60));
    }
    TrackerTableAction::_trackerList.removeOne(t);
    setStatus(tr("Tracking ended for train \"%1\".").arg(t->getTrainName()));
}

/*public*/ void TableFrame::mouseClicked(QMouseEvent* /*event*/) {
    QMenu* popup = new QMenu();
    for (int i = _statusHistory.size() - 1; i >= 0; i--)
    {
        //popupLayout()->addWidget(_statusHistory.at(i));
     popup->addAction(new QAction (_statusHistory.at(i), this));
    }
    //popup.show(_status, 0, 0);
    popup->exec(QCursor::pos());
}

/*public*/ void TableFrame::mousePressed(QMouseEvent* /*event*/) {
}

/*public*/ void TableFrame::mouseEntered(QMouseEvent* /*event*/) {
}

/*public*/ void TableFrame::mouseExited(QMouseEvent* /*event*/) {
}

/*public*/ void TableFrame::mouseReleased(QMouseEvent* /*event*/) {
}

/*private*/ void TableFrame::setStatus(QString msg) {
    _status->setText(msg);
    if (msg != NULL && msg.length() > 0) {
        WarrantTableAction::getDefault()->writetoLog(msg);
        _statusHistory.append(msg);
        while (_statusHistory.size() > _maxHistorySize) {
            _statusHistory.removeAt(0);
        }
    }
}
//};

//static class TrackerTableModel extends AbstractTableModel {

///*private*/ static final long serialVersionUID = -8320710926680330134L;
///*public*/ static final int NAME_COL = 0;
///*public*/ static final int STATUS_COL = 1;
///*public*/ static final int STOP_COL = 2;
///*public*/ static final int NUMCOLS = 3;

//TableFrame _parent;

/*public*/ TrackerTableModel::TrackerTableModel(TableFrame* f) {
    //super();
    _parent = f;
}

/*public*/ int TrackerTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return NUMCOLS;
}

/*public*/ int TrackerTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return TrackerTableAction::_trackerList.size();
}

/*public*/ QVariant TrackerTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
     if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
     {
    switch (section) {
        case NAME_COL:
            return tr("TrainName");
        case STATUS_COL:
            return tr("status");
    }
    return "";
     }
     return QVariant();
}

/*public*/ QVariant TrackerTableModel::data(const QModelIndex &index, int role) const
{
     if(role == Qt::DisplayRole)
     {
      int columnIndex = index.column();
      int rowIndex = index.row();

    switch (columnIndex) {
        case NAME_COL:
            return TrackerTableAction::_trackerList.at(rowIndex)->getTrainName();
        case STATUS_COL:
            return TrackerTableAction::_trackerList.at(rowIndex)->getStatus();
        case STOP_COL:
            return tr("Stop");
    }
    return "";
     }
     return QVariant();
}

/*public*/ bool TrackerTableModel::setData(const QModelIndex &index, const QVariant &/*value*/, int role)
    {
     if(role == Qt::EditRole)
     {
      int col = index.column();
      int row = index.row();
    if (col == STOP_COL) {
        Tracker* t = TrackerTableAction::_trackerList.at(row);
        _parent->stopTrain(t);
        fireTableDataChanged();
        return true;
    }
     }
     return false;
}

/*public*/ Qt::ItemFlags  TrackerTableModel::flags(const QModelIndex &index) const
    {
    if (index.column() == STOP_COL) {
        return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

///*public*/ Class<?> getColumnClass(int col) {
//    if (col == STOP_COL) {
//        return JButton.class;
//    }
//    return String.class;
//}

/*public*/ int TrackerTableModel::getPreferredWidth(int col) {
    switch (col) {
        case NAME_COL:
     return  JTextField(20).sizeHint().width();
        case STATUS_COL:
     return  JTextField(60).sizeHint().width();
        case STOP_COL:
     return  QPushButton("STOPIT").sizeHint().width();
    }
    return 5;
}

//}; // end TrackerTableModel
//    static Logger log = LoggerFactory.getLogger(TrackerTableAction.class.getName());
//}
/*public*/ QString TableFrame::getClassName()
{
 return "jmri.jmrit.logix.TableFrame";
}
