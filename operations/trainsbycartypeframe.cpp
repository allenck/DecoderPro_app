#include "trainsbycartypeframe.h"
#include "trainmanager.h"
#include <QCheckBox>
#include "jcombobox.h"
#include <QBoxLayout>
#include "gridbaglayout.h"
#include "jbutton.h"
#include "control.h"
#include <propertychangeevent.h>
#include "setup.h"
#include "cartypes.h"
#include <QLabel>
#include <QScrollArea>
#include <QMenu>
#include <QMenuBar>
#include "logger.h"
#include <QMessageBox>
#include "train.h"
#include "operationsxml.h"
#include "printtrainsbycartypesaction.h"
#include "instancemanager.h"
#include "borderfactory.h"

namespace Operations
{
/**
 * Frame to display which trains service certain car types
 *
 * @author Dan Boudreau Copyright (C) 2009
 * @version $Revision: 29410 $
 */
///*public*/ class TrainsByCarTypeFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -4268396118355876227L;

 /*public*/ TrainsByCarTypeFrame::TrainsByCarTypeFrame(QWidget* parent) : OperationsFrame(parent) {
     //super();
  setFrameRef(getClassName());
 log = new Logger("TrainsByCarTypeFrame");
     Empty = "            ";
     trainList = QList<QCheckBox*>();
     trainCheckBoxes = new JPanel();
     clearButton = new JButton(tr("Clear"));
     setButton = new JButton(tr("Select"));
     saveButton = new JButton(tr("Save"));
     copyCheckBox = new QCheckBox(tr("Copy"));
     textCarType = new QLabel(Empty);
     typeComboBox = ((CarTypes*)InstanceManager::getDefault("CarTypes"))->getComboBox();
 }

 /*public*/ void TrainsByCarTypeFrame::initComponents(QString carType) {

     // load managers
     manager = ((TrainManager*)InstanceManager::getDefault("Operations::TrainManager"));

     // general GUI config
     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
     QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

     // Set up the panels
     JPanel* pCarType = new JPanel();
     pCarType->setLayout(new GridBagLayout());
     pCarType->setBorder(BorderFactory::createTitledBorder(tr("Type")));
     addItem(pCarType, typeComboBox, 0, 0);
     addItem(pCarType, copyCheckBox, 1, 0);
     addItem(pCarType, textCarType, 2, 0);
     typeComboBox->setCurrentIndex(typeComboBox->findText(carType));
     copyCheckBox->setToolTip(tr("First select the car type you want to copy, then select Copy, then the car type you want to copy to, then Save"));

     JPanel* pTrainsFrame = new JPanel();
     pTrainsFrame->setLayout(new QVBoxLayout);
     pTrains = new JPanel();
     pTrains->setLayout(new GridBagLayout());
     QScrollArea* trainPane = new QScrollArea(/*pTrains*/);
     //trainPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
     pTrainsFrame->setBorder(BorderFactory::createTitledBorder(tr("Trains")));
     updateTrains();

     JPanel* pButtons = new JPanel();
     pButtons->setLayout(new GridBagLayout());
     pButtons->setBorder(BorderFactory::createEtchedBorder());

     addItem(pButtons, clearButton, 0, 0);
     addItem(pButtons, setButton, 1, 0);
     addItem(pButtons, saveButton, 2, 0);

     thisLayout->addWidget(pCarType);
     trainPane->setWidget(pTrains);
     thisLayout->addWidget(/*trainPane*/pTrainsFrame);
     thisLayout->addWidget(pButtons);

     // setup combo box
     addComboBoxAction(typeComboBox);

     // setup buttons
     addButtonAction(setButton);
     addButtonAction(clearButton);
     addButtonAction(saveButton);

     // setup checkbox
     addCheckBoxAction(copyCheckBox);

     //manager.addPropertyChangeListener(this);
     connect(manager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarTypes::instance().addPropertyChangeListener(this);
     connect(((CarTypes*)InstanceManager::getDefault("CarTypes")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     // build menu
     QMenuBar* menuBar = new QMenuBar();
     QMenu* toolMenu = new QMenu(tr("Tools"));
     toolMenu->addAction(new PrintTrainsByCarTypesAction(tr("Print By Type"), new JFrame(), false, this));
     toolMenu->addAction(new PrintTrainsByCarTypesAction(tr("Preview By Type"), new JFrame(), true,
             this));
     menuBar->addMenu(toolMenu);
     setMenuBar(menuBar);
     addHelpMenu("package.jmri.jmrit.operations.Operations_ModifyTrainsByCarType", true); // NOI18N

     resize(QSize());
     adjustSize();
     setMinimumSize(QSize(Control::panelWidth300, Control::panelHeight250));
     setTitle(tr("Modify Trains by Car Type"));
     setVisible(true);
 }

 /*public*/ void TrainsByCarTypeFrame::comboBoxActionPerformed(QWidget* ae) {
     log->debug("combo box action");
     updateTrains();
 }

 // Save, Delete, Add
 /*public*/ void TrainsByCarTypeFrame::buttonActionPerformed(JButton* ae) {
 JButton* source = (JButton*)ae;
     if (source == saveButton) {
         save();
     }
     if (source == setButton) {
         selectCheckboxes(true);
     }
     if (source == clearButton) {
         selectCheckboxes(false);
     }
 }

 /**
  * Update the car types that trains and tracks service. Note that the
  * checkbox name is the id of the train or track.
  */
 /*private*/ void TrainsByCarTypeFrame::save() {
//     if (copyCheckBox.isSelected() && JOptionPane.showConfirmDialog(this, MessageFormat.format(tr("CopyCarType"),
//             new Object[]{typeComboBox.getSelectedItem(), textCarType.getText()}), tr("CopyCarTypeTitle"),
//             JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION) {
  if(copyCheckBox->isChecked() && QMessageBox::question(this, tr("Copy car type?"), tr("Do you want car type (%1) to service the same trains as car type (%2)?").arg(typeComboBox->currentText()).arg(textCarType->text()), QMessageBox::Yes, QMessageBox::No)== QMessageBox::Yes)
  {
         return;
     }
     log->debug(tr("Save %1 trains").arg(trainList.size()));
     removePropertyChangeTrains();
     for (int i = 0; i < trainList.size(); i++) {
         QCheckBox* cb = trainList.at(i);
         Train* train = manager->getTrainById(cb->objectName());
         if (cb->isChecked()) {
             train->addTypeName( typeComboBox->currentText());
         } else {
             train->deleteTypeName(typeComboBox->currentText());
         }
     }
     OperationsXml::save(); // save files
     updateTrains();
     if (Setup::isCloseWindowOnSaveEnabled()) {
         dispose();
     }
 }

 /*private*/ void TrainsByCarTypeFrame::updateTrains() {
     log->debug("update trains");
     removePropertyChangeTrains();
     trainList.clear();
     int x = 0;
     //pTrains.removeAll();
     QLayoutItem* item;
     while ( ( item = pTrains->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
     QString carType =  typeComboBox->currentText();
     if (copyCheckBox->isChecked()) {
         carType = textCarType->text();
     }
     QList<Train*> trains = manager->getTrainsByNameList();
     foreach (Train* train, trains) {
         //train.addPropertyChangeListener(this);
      connect(train, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         QCheckBox* cb = new QCheckBox(train->getName());
         cb->setObjectName(train->getId());
         cb->setToolTip(tr("Select this train if it services car type %1").arg(carType));
         addCheckBoxAction(cb);
         trainList.append(cb);
         bool trainAcceptsType = train->acceptsTypeName(carType);
         cb->setChecked(trainAcceptsType);
         addItemLeft(pTrains, cb, 0, x);
         QLabel* description = new QLabel(train->getDescription());
         addItemLeft(pTrains, description, 1, x++);
     }
     pTrains->update();
     update();
 }

 /*private*/ void TrainsByCarTypeFrame::updateComboBox() {
     log->debug("update combobox");
     ((CarTypes*)InstanceManager::getDefault("CarTypes"))->updateComboBox(typeComboBox);
 }

 /*private*/ void TrainsByCarTypeFrame::selectCheckboxes(bool b) {
     for (int i = 0; i < trainList.size(); i++) {
         trainList.at(i)->setChecked(b);
     }
 }

 /*public*/ void TrainsByCarTypeFrame::checkBoxActionPerformed(QWidget* ae) {
     // copy checkbox?
 QCheckBox* source = (QCheckBox*)ae;
     if (source == copyCheckBox) {
         if (copyCheckBox->isChecked()) {
             textCarType->setText( typeComboBox->currentText());
         } else {
             textCarType->setText(Empty);
             updateTrains();
         }
     } else {
         QCheckBox* cb =  source;
         log->debug("Checkbox " + cb->objectName() + " text: " + cb->text());
         if (trainList.contains(cb)) {
             log->debug("Checkbox train " + cb->text());
         } else {
             log->error("Error checkbox not found");
         }
     }
 }

 /*private*/ void TrainsByCarTypeFrame::removePropertyChangeTrains() {
     if (!trainList.isEmpty()) {
         for (int i = 0; i < trainList.size(); i++) {
             // if object has been deleted, it's not here; ignore it
             Train* train = manager->getTrainById(trainList.at(i)->objectName());
             if (train != NULL) {
                 //train.removePropertyChangeListener(this);
              disconnect(train, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             }
         }
     }
 }

 /*public*/ void TrainsByCarTypeFrame::dispose() {
     //manager.removePropertyChangeListener(this);
 disconnect(manager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarTypes.instance().removePropertyChangeListener(this);
 disconnect(((CarTypes*)InstanceManager::getDefault("CarTypes")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     removePropertyChangeTrains();
     OperationsFrame::dispose();
 }

 /*public*/ void TrainsByCarTypeFrame::propertyChange(PropertyChangeEvent* e) {
     if (log->isDebugEnabled()) {
      log->debug(tr("PropertyChange (%1) new ({%2)").arg(e->getPropertyName()).arg(e->getNewValue().toString()));
     }
     if (e->getPropertyName()==(TrainManager::LISTLENGTH_CHANGED_PROPERTY)
             || e->getPropertyName()==(Train::TYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(Train::NAME_CHANGED_PROPERTY)
             || e->getPropertyName()==(Train::DESCRIPTION_CHANGED_PROPERTY)) {
         updateTrains();
     }
     if (e->getPropertyName()==(CarTypes::CARTYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(CarTypes::CARTYPES_NAME_CHANGED_PROPERTY)) {
         updateComboBox();
     }
 }

 /*public*/ QString TrainsByCarTypeFrame::getClassName()
 {
  return "jmri.jmrit.operations.trains.tools.TrainsByCarTypeFrame";
 }

}

