#include "locationeditframe.h"
#include "location.h"
#include "control.h"
#include "locationmanager.h"
#include <QPushButton>
#include <QCheckBox>
#include <QScrollArea>
#include <QRadioButton>
#include <QButtonGroup>
#include "jtextfield.h"
#include "jtextarea.h"
#include "jcombobox.h"
#include <QMenu>
#include <QMenuBar>
#include "setup.h"
#include "instancemanager.h"
#include "cartypes.h"
#include "enginetypes.h"
#include "yardtablemodel.h"
#include "spurtablemodel.h"
#include "interchangetablemodel.h"
#include "jtable.h"
#include "stagingtablemodel.h"
#include <QBoxLayout>
#include "gridbagconstraints.h"
#include "gridbaglayout.h"
#include <QGroupBox>
#include "reportermanager.h"
#include "namedbean.h"
#include <QList>
#include "editcartypeaction.h"
#include "flowlayout.h"
#include <QMessageBox>
#include "operationsxml.h"
#include "track.h"
#include "yardeditframe.h"
#include "spureditframe.h"
#include "stagingeditframe.h"
#include "interchangeeditframe.h"
#include "modifylocationsaction.h"
#include "changetrackstypeaction.h"
#include "trackcopyaction.h"
#include "printlocationsaction.h"
#include "showcarsbylocationaction.h"
#include "modifylocationscarloadsaction.h"
#include "showtrainsservinglocationaction.h"
#include "locationtrackblockingorderaction.h"

//LocationEditFrame::LocationEditFrame()
//{

//}
namespace Operations
{
/**
 * Frame for user edit of location
 *
 * @author Dan Boudreau Copyright (C) 2008, 2010, 2011, 2012, 2013
 * @version $Revision: 29638 $
 */
///*public*/ class LocationEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static /*final*/ long serialVersionUID = -820196357214001064L;

 /*public*/ /*static*/ /*final*/ QString LocationEditFrame::NAME = tr("Name");
 /*public*/ /*static*/ /*final*/ int LocationEditFrame::MAX_NAME_LENGTH = Control::max_len_string_location_name;
 /*public*/ /*static*/ /*final*/ QString LocationEditFrame::DISPOSE = "dispose"; // NOI18N

 /*public*/ LocationEditFrame::LocationEditFrame(Location* location, QWidget* parent) : OperationsFrame(tr("Edit Location"), parent)
 {
     //super(tr("TitleLocationEdit"));
 log = new Logger("LocationEditFrame");

  yardModel = new YardTableModel();
  yardTable = new JTable(yardModel);
  spurModel = new SpurTableModel();
  spurTable = new JTable(spurModel);
  interchangeModel = new InterchangeTableModel();
  interchangeTable = new JTable(interchangeModel);
  stagingModel = new StagingTableModel();
  stagingTable = new JTable(stagingModel);
  locationManager = LocationManager::instance();

  _location = NULL;
  checkBoxes =  QList<QCheckBox*>();
  panelCheckBoxes = new QWidget();
  panelCheckBoxes->setLayout(new GridBagLayout()); //layout must be set before setting QScrollArea's widget.

  directionPanel = new QGroupBox();

     // major buttons
  clearButton = new QPushButton(tr("Clear"));
  setButton = new QPushButton(tr("Select"));
  autoSelectButton = new QPushButton(tr("Auto Select"));
  saveLocationButton = new QPushButton(tr("Save Location"));
  deleteLocationButton = new QPushButton(tr("DeleteLocation"));
  addLocationButton = new QPushButton(tr("Add Location"));
  addYardButton = new QPushButton(tr("Add Yard Track"));
  addSpurButton = new QPushButton(tr("Add Spur Track"));
  addInterchangeButton = new QPushButton(tr("Add C/I Track"));
  addStagingButton = new QPushButton(tr("Add Staging Track"));

     // check boxes
  northCheckBox = new QCheckBox(tr("North"));
  southCheckBox = new QCheckBox(tr("South"));
  eastCheckBox = new QCheckBox(tr("East"));
  westCheckBox = new QCheckBox(tr("West"));

     // radio buttons
  stageRadioButton = new QRadioButton(tr("Staging Only"));
  interchangeRadioButton = new QRadioButton(tr("Classification/Interchange"));
  yardRadioButton = new QRadioButton(tr("Yards"));
  spurRadioButton = new QRadioButton(tr("Spurs"));

     // text field
  locationNameTextField = new JTextField(Control::max_len_string_location_name);

     // text area
  commentTextArea = new JTextArea(2, 60);

  // Reader selection dropdown.
  readerSelector = new JComboBox();

  _location = location;
   chkBoxMapper = new QSignalMapper;
   connect(chkBoxMapper, SIGNAL(mapped(QWidget*)), this, SLOT(checkBoxActionTrainPerformed(QWidget*)));
   yef = NULL;
   sef = NULL;
   ief = NULL;
   stef = NULL;
   x = 0;
   y = 0; // vertical position in panel
   lctf = NULL;

   // Set up the jtable in a Scroll Pane..
   typePane = new QGroupBox();
   typePane->setLayout(new QVBoxLayout);
   QScrollArea* typePaneScroll = new QScrollArea(/*panelCheckBoxes*/);
   typePaneScroll->setWidget(panelCheckBoxes);
   typePaneScroll->setWidgetResizable(true);
//     typePane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
//     typePane->setBorder(BorderFactory.createTitledBorder(tr("Types")));
   typePane->setStyleSheet(gbStyleSheet);
   typePane->setTitle(tr("Types"));
   typePane->layout()->addWidget(typePaneScroll);

//     yardPane = new JScrollPane(yardTable);
//     yardPane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
//     yardPane->setBorder(BorderFactory.createTitledBorder(""));

//     spurPane = new JScrollPane(spurTable);
//     spurPane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
//     spurPane->setBorder(BorderFactory.createTitledBorder(""));

//     interchangePane = new JScrollPane(interchangeTable);
//     interchangePane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
//     interchangePane->setBorder(BorderFactory.createTitledBorder(""));

//     stagingPane = new JScrollPane(stagingTable);
//     stagingPane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
//     stagingPane->setBorder(BorderFactory.createTitledBorder(""));

  // button group
  QButtonGroup* opsGroup = new QButtonGroup();
  opsGroup->addButton(spurRadioButton);
  opsGroup->addButton(yardRadioButton);
  opsGroup->addButton(interchangeRadioButton);
  opsGroup->addButton(stageRadioButton);

  // Location name for tools menu
  QString locationName = "";

  if (_location != NULL)
  {
   enableButtons(true);
   locationNameTextField->setText(_location->getName());
   commentTextArea->setText(_location->getComment());
   yardModel->initTable(yardTable, location);
   spurModel->initTable(spurTable, location);
   interchangeModel->initTable(interchangeTable, location);
   stagingModel->initTable(stagingTable, location);
   //_location->addPropertyChangeListener(this);
   connect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   locationName = _location->getName();
   if (_location->getLocationOps() == Location::NORMAL)
   {
    if (spurModel->rowCount(QModelIndex()) > 0) {
        spurRadioButton->setChecked(true);
    } else if (yardModel->rowCount(QModelIndex()) > 0) {
        yardRadioButton->setChecked(true);
    } else if (interchangeModel->rowCount(QModelIndex()) > 0) {
        interchangeRadioButton->setChecked(true);
    } else if (stagingModel->rowCount(QModelIndex())> 0) {
        stageRadioButton->setChecked(true);
    } else {
        spurRadioButton->setChecked(true);
    }
   } else {
       stageRadioButton->setChecked(true);
   }
   setTrainDirectionBoxes();
   if (Setup::isRfidEnabled())
   {
    // setup the Reader dropdown.
    readerSelector->addItem(""); // add an empty entry.
    foreach (NamedBean* r, *((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->getNamedBeanList())
    {
     readerSelector->addItem(((Reporter*) r)->getDisplayName());
    }

    //try {
    readerSelector->setCurrentIndex(readerSelector->findText(_location->getReporter()->getDisplayName()));
//             } catch (NULLPointerException e) {
//                 // if there is no reader set, getReporter
//                 // will return NULL, so set a blank.
//             }
   }
  } else {
      enableButtons(false);
      spurRadioButton->setChecked(true);
  }

  setVisibleLocations();

  //getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
  // Layout the panel by rows
  // row 1
  QWidget* p1 = new QWidget();
  //p1->setLayout(new BoxLayout(p1, BoxLayout.X_AXIS));
  QHBoxLayout*  p1Layout = new QHBoxLayout(p1);
  QScrollArea* p1Pane = new QScrollArea(/*p1*/);
  p1Pane->setWidget(p1);
  p1Pane->setWidgetResizable(true);
//     p1Pane->setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
//     p1Pane->setMinimumSize(new Dimension(300, 3 * locationNameTextField.getPreferredSize().height));
//     p1Pane->setBorder(BorderFactory.createTitledBorder(""));

  // row 1a
  QGroupBox* pName = new QGroupBox();
  pName->setLayout(new GridBagLayout());
 // pName->setBorder(BorderFactory.createTitledBorder(tr("Name")));
  pName->setStyleSheet(gbStyleSheet);
  pName->setTitle(tr("Name"));

  addItem(pName, locationNameTextField, 0, 0);

  // row 1b
  directionPanel->setLayout(new GridBagLayout());
  //directionPanel->setBorder(BorderFactory.createTitledBorder(tr("TrainLocation")));
  directionPanel->setStyleSheet(gbStyleSheet);
  directionPanel->setTitle(tr("Train Location"));
  addItem(directionPanel, northCheckBox, 1, 0);
  addItem(directionPanel, southCheckBox, 2, 0);
  addItem(directionPanel, eastCheckBox, 3, 0);
  addItem(directionPanel, westCheckBox, 4, 0);

  p1Layout->addWidget(pName);
  p1Layout->addWidget(directionPanel);

  // row 5
  updateCheckboxes();

  // row 9
  QGroupBox* pOp = new QGroupBox();
  FlowLayout* pOpLayout;
  pOp->setLayout(pOpLayout = new FlowLayout());
  //pOp->setBorder(BorderFactory.createTitledBorder(tr("TracksAtLocation")));
  pOp->setStyleSheet(gbStyleSheet);
  pOp->setTitle(tr("Tracks at Location"));
  pOpLayout->addWidget(spurRadioButton);
  pOpLayout->addWidget(yardRadioButton);
  pOpLayout->addWidget(interchangeRadioButton);
  pOpLayout->addWidget(stageRadioButton);

  // row 11
  QGroupBox* pC = new QGroupBox();
  pC->setLayout(new GridBagLayout());
  //pC->setBorder(BorderFactory.createTitledBorder(tr("Comment")));
  pC->setStyleSheet(gbStyleSheet);
  pC->setTitle(tr("Comment"));
  addItem(pC, /*commentScroller*/commentTextArea, 0, 0);

  // adjust text area width based on window size
  adjustTextAreaColumnWidth(pC, commentTextArea);

  // reader row
  QGroupBox* readerPanel = new QGroupBox();
  readerPanel->setLayout(new GridBagLayout());
  //readerPanel->setBorder(BorderFactory.createTitledBorder(tr("IdTag Reader at this Location ")));
  readerPanel->setStyleSheet(gbStyleSheet);
  readerPanel->setTitle(tr("Comment"));
  addItem(readerPanel, readerSelector, 0, 0);

  readerPanel->setVisible(Setup::isRfidEnabled());

  // row 12
  QWidget* pB = new QWidget();
  pB->setLayout(new GridBagLayout());
  addItem(pB, deleteLocationButton, 0, 0);
  addItem(pB, addLocationButton, 1, 0);
  addItem(pB, saveLocationButton, 3, 0);

  thisLayout->addWidget(p1Pane);
  thisLayout->addWidget(typePane);
  thisLayout->addWidget(pOp);
  thisLayout->addWidget(/*yardPane*/yardTable);
  thisLayout->addWidget(addYardButton, 0, Qt::AlignHCenter);
  thisLayout->addWidget(/*spurPane*/spurTable);
  thisLayout->addWidget(addSpurButton, 0, Qt::AlignHCenter);
  thisLayout->addWidget(/*interchangePane*/interchangeTable);
  thisLayout->addWidget(addInterchangeButton, 0, Qt::AlignHCenter);
  thisLayout->addWidget(/*stagingPane*/stagingTable);
  thisLayout->addWidget(addStagingButton, 0, Qt::AlignHCenter);
  thisLayout->addWidget(pC);
  thisLayout->addWidget(readerPanel);
  thisLayout->addWidget(pB);

  // setup buttons
  addButtonAction(setButton);
  addButtonAction(clearButton);
  addButtonAction(autoSelectButton);
  addButtonAction(deleteLocationButton);
  addButtonAction(addLocationButton);
  addButtonAction(saveLocationButton);
  addButtonAction(addYardButton);
  addButtonAction(addSpurButton);
  addButtonAction(addInterchangeButton);
  addButtonAction(addStagingButton);

  // add tool tips
  autoSelectButton->setToolTip(tr("Only select rolling stock that is serviced by this location's tracks"));

  addRadioButtonAction(spurRadioButton);
  addRadioButtonAction(yardRadioButton);
  addRadioButtonAction(interchangeRadioButton);
  addRadioButtonAction(stageRadioButton);

  addCheckBoxTrainAction(northCheckBox);
  addCheckBoxTrainAction(southCheckBox);
  addCheckBoxTrainAction(eastCheckBox);
  addCheckBoxTrainAction(westCheckBox);

  // add property listeners
  //CarTypes.instance().addPropertyChangeListener(this);
  connect(CarTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //EngineTypes.instance().addPropertyChangeListener(this);
  connect(EngineTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

  // build menu
  QMenuBar* menuBar = new QMenuBar();
  QMenu* toolMenu = new QMenu(tr("Tools"));
  toolMenu->addAction(new TrackCopyAction(this));
  toolMenu->addAction(new ChangeTracksTypeAction(this));
  toolMenu->addAction(new ModifyLocationsAction(tr("Modify Location by Car Type"), _location, this));
  toolMenu->addAction(new ModifyLocationsCarLoadsAction(_location,this));
  if (_location != NULL && _location->getLocationOps() == Location::NORMAL) {
      toolMenu->addAction(new LocationTrackBlockingOrderAction(_location,this));
  }
  toolMenu->addAction(new ShowTrainsServingLocationAction(tr("Show Trains Location"), _location,
       NULL,this));
  toolMenu->addAction(new EditCarTypeAction(this));
  toolMenu->addAction(new ShowCarsByLocationAction(false, locationName, NULL,this));
  toolMenu->addAction(new PrintLocationsAction(tr("Print"), false, location,this));
  toolMenu->addAction(new PrintLocationsAction(tr("Preview"), true, location,this));
#if 0
  if (Setup::isVsdPhysicalLocationEnabled()) {
      toolMenu->addAction(new SetPhysicalLocationAction(tr("MenuSetPhysicalLocation"), _location));
  }
#endif
  menuBar->addMenu(toolMenu);
  setMenuBar(menuBar);
  addHelpMenu("package.jmri.jmrit.operations.Operations_AddLocation", true); // NOI18N

  adjustSize();
  setMinimumSize(QSize(Control::panelWidth500, Control::panelHeight500 +150));
  setVisible(true);
 }


 // Save, Delete, Add
 /*public*/ void LocationEditFrame::buttonActionPerformed(QWidget* ae) {
  QPushButton* source = (QPushButton*)ae;
     if (source == addYardButton) {
         yef = new YardEditFrame();
         yef->initComponents(_location, NULL);
         yef->setTitle(tr("Add Yard"));
     }

     if (source == addSpurButton) {
         sef = new SpurEditFrame();
         sef->initComponents(_location, NULL);
         sef->setTitle(tr("Add Spur Track"));
     }

     if (source == addInterchangeButton) {
         ief = new InterchangeEditFrame();
         ief->initComponents(_location, NULL);
         ief->setTitle(tr("Add Interchange Track"));
     }
     if (source == addStagingButton) {
         stef = new StagingEditFrame();
         stef->initComponents(_location, NULL);
         stef->setTitle(tr("Add Staging Track"));
     }

     if (source == saveLocationButton) {
         log->debug("location save button activated");
         Location* l = locationManager->getLocationByName(locationNameTextField->text());
         if (_location == NULL && l == NULL) {
             saveNewLocation();
         } else {
             if (l != NULL && l != _location) {
                 reportLocationExists(tr("save"));
                 return;
             }
             saveLocation();
             if (Setup::isCloseWindowOnSaveEnabled()) {
                 dispose();
             }
         }
     }
     if (source == deleteLocationButton) {
         log->debug("location delete button activated");
         Location* l = locationManager->getLocationByName(locationNameTextField->text());
         if (l == NULL) {
             return;
         }
         int rs = l->getNumberRS();
         if (rs > 0) {
//             if (JOptionPane.showConfirmDialog(this, MessageFormat.format(tr("ThereAreCars"),
//                     new Object[]{Integer.toString(rs)}), tr("deletelocation?"),
//                     JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION) {
          if(QMessageBox::question(this, tr(""), tr(""), QMessageBox::Yes | QMessageBox::No)== QMessageBox::Yes)
          {
                 return;
             }
         } else {
//             if (JOptionPane.showConfirmDialog(this, MessageFormat.format(Bundle
//                     .getMessage("DoYouWantToDeleteLocation"), new Object[]{locationNameTextField.getText()}),
//                     tr("deletelocation?"), JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION) {
      if(QMessageBox::question(this, tr(""), tr(""), QMessageBox::Yes | QMessageBox::No)== QMessageBox::Yes)
      {
                 return;
             }
         }

         yardModel->dispose();
         spurModel->dispose();
         interchangeModel->dispose();
         stagingModel->dispose();

         if (yef != NULL) {
             yef->dispose();
         }
         if (sef != NULL) {
             sef->dispose();
         }

         if (ief != NULL) {
             ief->dispose();
         }
         if (stef != NULL) {
             stef->dispose();
         }

         locationManager->deregister(l);
         _location = NULL;
         selectCheckboxes(false);
         enableCheckboxes(false);
         enableButtons(false);
         // save location file
         OperationsXml::save();
     }
     if (source == addLocationButton) {
         Location* l = locationManager->getLocationByName(locationNameTextField->text());
         if (l != NULL) {
             reportLocationExists(tr("add"));
             return;
         }
         saveNewLocation();
     }
     if (source == setButton) {
         selectCheckboxes(true);
     }
     if (source == clearButton) {
         selectCheckboxes(false);
     }
     if (source == autoSelectButton) {
         log->debug("auto select button pressed");
//         if (JOptionPane.showConfirmDialog(this, tr("autoSelectCarTypes?"), Bundle
//                 .getMessage("autoSelectLocations?"), JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION) {
         if(QMessageBox::question(this, tr(""), tr(""), QMessageBox::Yes | QMessageBox::No)== QMessageBox::Yes)
         {
             return;
         }
         autoSelectCheckboxes();
     }
 }

 /*private*/ void LocationEditFrame::saveNewLocation() {
     if (!checkName(tr("add"))) {
         return;
     }
     Location* location = locationManager->newLocation(locationNameTextField->text());
     yardModel->initTable(yardTable, location);
     spurModel->initTable(spurTable, location);
     interchangeModel->initTable(interchangeTable, location);
     stagingModel->initTable(stagingTable, location);
     _location = location;
     // enable check boxes
     updateCheckboxes();
     // enableCheckboxes(true);
     enableButtons(true);
     setTrainDirectionBoxes();
     saveLocation();
 }

 /*private*/ void LocationEditFrame::saveLocation() {
     if (!checkName(tr("save"))) {
         return;
     }
     _location->setName(locationNameTextField->text());
     _location->setComment(commentTextArea->toPlainText());
     if (Setup::isRfidEnabled() &&
             readerSelector->currentText() != NULL &&
             ( readerSelector->currentText())!=(""))
     {
      _location->setReporter(
                 ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))
                         ->getReporter( readerSelector->currentText()));
     } else if (Setup::isRfidEnabled() &&
             readerSelector->currentText() != NULL &&
             ( readerSelector->currentText())==(""))
     {
      _location->setReporter(NULL);
     }
     setLocationOps();
     // save location file
     OperationsXml::save();
 }

 /**
  *
  * @return true if name is less than 26 characters
  */
 /*private*/ bool LocationEditFrame::checkName(QString s) {
     if (locationNameTextField->text().trimmed()==("")) {
//         JOptionPane.showMessageDialog(this, tr("MustEnterName"), MessageFormat.format(Bundle
//                 .getMessage("CanNotLocation"), new Object[]{s}), JOptionPane.ERROR_MESSAGE);
//         QMessageBox::critical(this, tr("Can not %1 location!").arg(s), tr("Enter a name"));
      QMessageBox::critical(this, tr("Can not %1 location!").arg(s), tr("Enter a name"));
         return false;
     }
     if (locationNameTextField->text().length() > MAX_NAME_LENGTH) {
         // log->error("Location name must be less than "+ Integer.toString(MAX_NAME_LENGTH+1) +" characters");
//         JOptionPane.showMessageDialog(this, MessageFormat.format(tr("LocationNameLengthMax"),
//                 new Object[]{Integer.toString(MAX_NAME_LENGTH + 1)}), MessageFormat.format(Bundle
//                 .getMessage("CanNotLocation"), new Object[]{s}), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Can not %1 location!").arg(s), tr("Location name must be less than %1 characters").arg(MAX_NAME_LENGTH + 1));
         return false;
     }
     return true;
 }

 /*private*/ void LocationEditFrame::setLocationOps() {
     if (stageRadioButton->isChecked()) {
         _location->setLocationOps(Location::STAGING);
     } else {
         _location->setLocationOps(Location::NORMAL);
     }
 }

 /*private*/ void LocationEditFrame::reportLocationExists(QString s) {
     // log->info("Can not " + s + ", location already exists");
//     JOptionPane.showMessageDialog(this, tr("LocationAlreadyExists"), MessageFormat.format(Bundle
//             .getMessage("CanNotLocation"), new Object[]{s}), JOptionPane.ERROR_MESSAGE);
 QMessageBox::critical(this, tr("Can not %1 location!").arg(s), tr("Location with this name already exists"));
 }

 /*private*/ void LocationEditFrame::enableButtons(bool enabled)
 {
  northCheckBox->setEnabled(enabled);
  southCheckBox->setEnabled(enabled);
  eastCheckBox->setEnabled(enabled);
  westCheckBox->setEnabled(enabled);
  clearButton->setEnabled(enabled);
  setButton->setEnabled(enabled);
  autoSelectButton->setEnabled(enabled);
  addYardButton->setEnabled(enabled);
  addSpurButton->setEnabled(enabled);
  addInterchangeButton->setEnabled(enabled);
  addStagingButton->setEnabled(enabled);
  saveLocationButton->setEnabled(enabled);
  deleteLocationButton->setEnabled(enabled);
  // the inverse!
  addLocationButton->setEnabled(!enabled);
  // enable radio buttons
  spurRadioButton->setEnabled(enabled);
  yardRadioButton->setEnabled(enabled);
  interchangeRadioButton->setEnabled(enabled);
  stageRadioButton->setEnabled(enabled);
  //
  yardTable->setEnabled(enabled);
  // enable readerSelect.
  readerSelector->setEnabled(enabled && Setup::isRfidEnabled());
 }

 /*public*/ void LocationEditFrame::radioButtonActionPerformed(QWidget* /*ae*/)
 {
  setLocationOps();
  setVisibleLocations();
 }

 /*private*/ void LocationEditFrame::setVisibleLocations()
{
  setEnabledLocations();
  interchangeTable->setVisible(interchangeRadioButton->isChecked());
  addInterchangeButton->setVisible(interchangeRadioButton->isChecked());
  stagingTable->setVisible(stageRadioButton->isChecked());
  addStagingButton->setVisible(stageRadioButton->isChecked());
  yardTable->setVisible(yardRadioButton->isChecked());
  addYardButton->setVisible(yardRadioButton->isChecked());
  spurTable->setVisible(spurRadioButton->isChecked());
  addSpurButton->setVisible(spurRadioButton->isChecked());
 }

 /*private*/ void LocationEditFrame::setEnabledLocations()
{
  if (spurModel->rowCount(QModelIndex()) > 0 || yardModel->rowCount(QModelIndex()) > 0 || interchangeModel->rowCount(QModelIndex()) > 0)
  {
   if (stageRadioButton->isChecked())
   {
       spurRadioButton->setChecked(true);
   }
   stageRadioButton->setEnabled(false);
  }
  else if (stagingModel->rowCount(QModelIndex()) > 0)
  {
   stageRadioButton->setChecked(true);
   spurRadioButton->setEnabled(false);
   yardRadioButton->setEnabled(false);
   interchangeRadioButton->setEnabled(false);
  }
  else if (_location != NULL)
  {
   spurRadioButton->setEnabled(true);
   yardRadioButton->setEnabled(true);
   interchangeRadioButton->setEnabled(true);
   stageRadioButton->setEnabled(true);
  }
 }

 /*private*/ void LocationEditFrame::enableCheckboxes(bool enable) {
     for (int i = 0; i < checkBoxes.size(); i++) {
         checkBoxes.at(i)->setEnabled(enable);
     }
 }

 /*private*/ void LocationEditFrame::selectCheckboxes(bool select) {
     for (int i = 0; i < checkBoxes.size(); i++) {
         checkBoxes.at(i)->setChecked(select);
         if (_location != NULL) {
             if (select) {
                 _location->addTypeName(checkBoxes.at(i)->text());
             } else {
                 _location->deleteTypeName(checkBoxes.at(i)->text());
             }
         }
     }
 }

 /*private*/ void LocationEditFrame::updateCheckboxes() {
     x = 0;
     y = 0;
     checkBoxes.clear();
     //panelCheckBoxes->clear();
     QObjectList ol = panelCheckBoxes->layout()->children();
     foreach(QObject* o, ol)
     {
      if(qobject_cast<QWidget*>(o) != NULL)
      {
       panelCheckBoxes->layout()->removeWidget((QWidget*)o);
       delete o;
      }
     }
     loadTypes(CarTypes::instance()->getNames());
     loadTypes(EngineTypes::instance()->getNames());
     QWidget* p = new QWidget();
     QHBoxLayout* pLayout = new QHBoxLayout(p);
     pLayout->addWidget(clearButton);
     pLayout->addWidget(setButton);
     pLayout->addWidget(autoSelectButton);
     GridBagConstraints gc =  GridBagConstraints();
     gc.gridwidth = getNumberOfCheckboxesPerLine() + 1;
     gc.gridy = ++y;
     //panelCheckBoxes->add(p, gc);
     ((GridBagLayout*)panelCheckBoxes->layout())->addWidget(p, gc);
     panelCheckBoxes->update();
     update();
 }


 /*private*/ void LocationEditFrame::loadTypes(QStringList types)
{
  int numberOfCheckBoxes = getNumberOfCheckboxesPerLine();
  foreach (QString type, types)
  {
   QCheckBox* checkBox = new QCheckBox();
   checkBoxes.append(checkBox);
   checkBox->setText(type);
   addCheckBoxAction(checkBox);
   addItemLeft(panelCheckBoxes, checkBox, x++, y);
   if (_location != NULL)
   {
    if (_location->acceptsTypeName(type))
    {
     checkBox->setChecked(true);
    }
   }
   else
   {
    checkBox->setEnabled(false);
   }
   // default is seven types per row
   if (x > numberOfCheckBoxes)
   {
    y++;
    x = 0;
   }
  }
 }

 /**
  * Adjust the location's car service types to only reflect the car types
  * serviced by the location's tracks.
  */
 /*private*/ void LocationEditFrame::autoSelectCheckboxes() {
     for (int i = 0; i < checkBoxes.size(); i++) {
         checkBoxes.at(i)->setChecked(false);
         // check each track to determine which car types are serviced by this location
         QList<Track*> tracks = _location->getTrackList();
         foreach (Track* track, tracks) {
             if (track->acceptsTypeName(checkBoxes.at(i)->text())) {
                 checkBoxes.at(i)->setChecked(true);
             }
         }
         // this type of car isn't serviced by any of the tracks, so delete
         if (!checkBoxes.at(i)->isChecked()) {
             _location->deleteTypeName(checkBoxes.at(i)->text());
         }
     }
 }


 /*public*/ void LocationEditFrame::checkBoxActionPerformed(QWidget* ae) {
  QCheckBox* b = (QCheckBox*) ae;
     log->debug(tr("checkbox change %1").arg(b->text()));
     if (_location == NULL) {
         return;
     }
    // _location->removePropertyChangeListener(this);
     disconnect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     if (b->isChecked()) {
         _location->addTypeName(b->text());
         // show which tracks will service this car type
         if (CarTypes::instance()->containsName(b->text())) {
#if 0
             if (lctf != NULL) {
                 lctf.dispose();
             }
             lctf = new LocationsByCarTypeFrame();
             lctf.initComponents(_location, b.getText());
#endif
         }
     } else {
         _location->deleteTypeName(b->text());
     }
     //_location->addPropertyChangeListener(this);
     connect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

 /*private*/ void LocationEditFrame::addCheckBoxTrainAction(QCheckBox* b)
 {
//     b.addActionListener(new java.awt.event.ActionListener() {
//         /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//             checkBoxActionTrainPerformed(e);
//         }
//     });
  chkBoxMapper->setMapping(b,b);
  connect(b, SIGNAL(clicked(bool)), chkBoxMapper, SLOT(map()));
 }

 /*private*/ void LocationEditFrame::checkBoxActionTrainPerformed(QWidget* /*ae*/) {
     // save train directions serviced by this location
     if (_location == NULL) {
         return;
     }
     int direction = 0;
     if (northCheckBox->isChecked()) {
         direction += Location::NORTH;
     }
     if (southCheckBox->isChecked()) {
         direction += Location::SOUTH;
     }
     if (eastCheckBox->isChecked()) {
         direction += Location::EAST;
     }
     if (westCheckBox->isChecked()) {
         direction += Location::WEST;
     }
     _location->setTrainDirections(direction);

 }

 /*private*/ void LocationEditFrame::setTrainDirectionBoxes() {
     northCheckBox->setVisible((Setup::getTrainDirection() & Setup::NORTH) > 0);
     southCheckBox->setVisible((Setup::getTrainDirection() & Setup::SOUTH) > 0);
     eastCheckBox->setVisible((Setup::getTrainDirection() & Setup::EAST) > 0);
     westCheckBox->setVisible((Setup::getTrainDirection() & Setup::WEST) > 0);

     northCheckBox->setChecked((_location->getTrainDirections() & Location::NORTH) > 0);
     southCheckBox->setChecked((_location->getTrainDirections() & Location::SOUTH) > 0);
     eastCheckBox->setChecked((_location->getTrainDirections() & Location::EAST) > 0);
     westCheckBox->setChecked((_location->getTrainDirections() & Location::WEST) > 0);
 }

 /*public*/ void LocationEditFrame::dispose() {
     if (_location != NULL) {
         //_location->removePropertyChangeListener(this);
      disconnect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     //CarTypes::instance().removePropertyChangeListener(this);
     disconnect(CarTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //EngineTypes.instance().removePropertyChangeListener(this);
     disconnect(EngineTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     yardModel->dispose();
     spurModel->dispose();
     interchangeModel->dispose();
     stagingModel->dispose();
#if 0
     if (lctf != NULL) {
         lctf.dispose();
     }
#endif
     OperationsFrame::dispose();
 }

 /*public*/ void LocationEditFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
         log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
                 ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(CarTypes::CARTYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(EngineTypes::ENGINETYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(Location::TYPES_CHANGED_PROPERTY)) {
         updateCheckboxes();
     }
 }
 /*public*/ QString LocationEditFrame::getClassName()
 {
  return "jmri.jmrit.operations.locations.LocationEditFrame";
 }

}
