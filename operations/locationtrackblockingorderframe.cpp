#include "locationtrackblockingorderframe.h"
#include "locationmanager.h"
#include "location.h"
#include "jtable.h"
#include <QLabel>
#include "jbutton.h"
#include <QBoxLayout>
#include "gridbaglayout.h"
#include <QGroupBox>
#include "locationtrackblockingordertablemodel.h"
#include "control.h"
#include "trainmanager.h"
#include "operationsxml.h"
#include "setup.h"
#include "logger.h"
#include "instancemanager.h"
#include "borderfactory.h"

namespace Operations
{

/**
  * Frame for user edit of location
  *
  * @author Dan Boudreau Copyright (C) 2015
  * @version $Revision: 29365 $
  */
 ///*public*/ class LocationTrackBlockingOrderFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = -820196357214001064L;

 /*public*/ LocationTrackBlockingOrderFrame::LocationTrackBlockingOrderFrame(QWidget* parent)
     : OperationsFrame(tr("Track Blocking Order"), parent)
 {
     //super(tr("TitleTrackBlockingOrder"));
 log = new Logger("LocationTrackBlockingOrderTableModel");
     trackModel = new LocationTrackBlockingOrderTableModel();
     trackTable = new JTable(trackModel);
     //trackPane = new QScrollArea(/*trackTable*/);

     locationManager = ((LocationManager*)InstanceManager::getDefault("LocationManager"));

     _location = NULL;

     locationName = new QLabel();

     // major buttons
     saveButton = new JButton(tr("Save"));
     resetButton = new JButton(tr("Reset"));
 }

 /*public*/ void LocationTrackBlockingOrderFrame::initComponents(Location* location) {
     _location = location;

//     trackPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
//     trackPane.setBorder(BorderFactory.createTitledBorder(tr("ServiceOrderMessage")));
     JPanel* trackPaneFrame = new JPanel;
     trackPaneFrame->setLayout(new QVBoxLayout);
     trackPaneFrame->layout()->addWidget(trackTable);
     trackPaneFrame->setBorder(BorderFactory::createTitledBorder(tr("Higher Order Tracks Serviced Last for Westbound and Northbound Trains")));
     if (_location != NULL) {
         trackModel->initTable(trackTable, location);
         locationName->setText(_location->getName());
         enableButtons(true);
     } else {
         enableButtons(false);
     }

     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
     QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
     // Layout the panel by rows
     JPanel* pName = new JPanel();
     pName->setLayout(new GridBagLayout());
     pName->setBorder(BorderFactory::createTitledBorder(tr("Location")));
     addItem(pName, locationName, 0, 0);

     // row buttons
     JPanel* pB = new JPanel();
     pB->setLayout(new GridBagLayout());
     addItem(pB, resetButton, 0, 0);
     addItem(pB, saveButton, 1, 0);

     thisLayout->addWidget(pName);
     thisLayout->addWidget(trackPaneFrame);
     thisLayout->addWidget(pB);

     // setup buttons
     addButtonAction(resetButton);
     addButtonAction(saveButton);

     // add tool tips
     resetButton->setToolTip(tr("Resets the track blocking orders to default"));

     // build menu
//        JMenuBar menuBar = new JMenuBar();
//        JMenu toolMenu = new JMenu(tr("Tools"));
//        menuBar.add(toolMenu);
//        setJMenuBar(menuBar);
     addHelpMenu("package.jmri.jmrit.operations.Operations_TrackBlockingOrder", true); // NOI18N

     initMinimumSize(QSize(Control::panelWidth600, Control::panelHeight500));

 }

 // Reset and Save
 /*public*/ void LocationTrackBlockingOrderFrame::buttonActionPerformed(QWidget* ae) {
 JButton* source = (JButton*)ae;
     if (source == resetButton && _location != NULL) {
         _location->resetTracksByBlockingOrder();
     }
     if (source == saveButton) {
//         if (trackTable.isEditing()) {
//             log.debug("track table edit true");
//             trackTable.getCellEditor().stopCellEditing();
//         }
         _location->resequnceTracksByBlockingOrder();
         // recreate all train manifests
         ((TrainManager*)InstanceManager::getDefault("TrainManager"))->setTrainsModified();
         // save location file
         OperationsXml::save();
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
 }


 /*private*/ void LocationTrackBlockingOrderFrame::enableButtons(bool enabled) {
     resetButton->setEnabled(enabled);
     saveButton->setEnabled(enabled);
 }

 /*public*/ void LocationTrackBlockingOrderFrame::dispose() {
     if (_location != NULL) {
      _location->removePropertyChangeListener(this);
     }
     trackModel->dispose();
     OperationsFrame::dispose();
 }

 /*public*/ void LocationTrackBlockingOrderFrame::propertyChange(PropertyChangeEvent* e) {
 log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
         ->getNewValue().toString()));
 }
/*public*/ QString LocationTrackBlockingOrderFrame::getClassName()
{
 return "jmri.jmrit.operations.locations.tools.LocationTrackBlockingOrderFrame";
}

}

