
#include "carsetframe.h"
#include <QComboBox>
#include "carloads.h"
#include "logger.h"
#include "car.h"
#include "carmanager.h"
#include <QMenu>
#include <QMenuBar>
#include <QBoxLayout>
#include "gridbaglayout.h"
#include <QGroupBox>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <propertychangesupport.h>
#include "locationmanager.h"
#include "trainmanager.h"
#include "vptr.h"
#include "train.h"
#include "location.h"
#include "carattributeeditframe.h"
#include "setup.h"
#include <QScrollArea>
//#include "carloadeditframe.h"
#include <QMessageBox>
#include "track.h"
#include "kernel.h"
#include "operationsxml.h"
#include "enabledestinationaction.h"
#include "carloadeditframe.h"
#include "schedule.h"

//CarSetFrame::CarSetFrame()
//{

//}
namespace Operations
{
/**
 * Frame for user to place car on the layout
 *
 * @author Dan Boudreau Copyright (C) 2008, 2010, 2011, 2013, 2014
 * @version $Revision: 29251 $
 */
///*public*/ class CarSetFrame extends RollingStockSetFrame implements java.beans.PropertyChangeListener {

    /**
     *
     */
    ///*private*/ static final long serialVersionUID = -2645258082248963991L;

//    /*protected*/ static final ResourceBundle rb = ResourceBundle
//            .getBundle("jmri.jmrit.operations.rollingstock.cars.JmritOperationsCarsBundle");




 /*public*/ CarSetFrame::CarSetFrame(QWidget* parent) : RollingStockSetFrame(tr("Car Set"), parent)
 {
     //super(tr("TitleCarSet"));
  log = new Logger("CarSetFrame");
  setObjectName("CarSetFrame");
  editActive = false;
  f = NULL;
  carManager = CarManager::instance();

  askKernelChange = true;
  destReturnWhenEmptyBox = LocationManager::instance()->getComboBox();
  trackReturnWhenEmptyBox = new QComboBox();
  loadReturnWhenEmptyBox = CarLoads::instance()->getComboBox();
  loadComboBox = CarLoads::instance()->getComboBox();
  kernelComboBox = carManager->getKernelComboBox();

  // buttons
  editLoadButton = new QPushButton(tr("Edit"));
  editKernelButton = new QPushButton(tr("Edit"));

  // check boxes
  ignoreRWECheckBox = new QCheckBox(tr("Ignore"));
  autoReturnWhenEmptyTrackCheckBox = new QCheckBox(tr("Auto"));
  ignoreLoadCheckBox = new QCheckBox(tr("Ignore"));
  ignoreKernelCheckBox = new QCheckBox(tr("Ignore"));

 }

 /*public*/ void CarSetFrame::initComponents() {
     RollingStockSetFrame::initComponents();

     // build menu
     QMenuBar* menuBar = new QMenuBar();
     QMenu* toolMenu = new QMenu(tr("Tools"));
     toolMenu->addAction(new EnableDestinationAction(tr("Enable Destination"), this));
     menuBar->addMenu(toolMenu);
     setMenuBar(menuBar);
     addHelpMenu("package.jmri.jmrit.operations.Operations_CarsSet", true); // NOI18N

     // optional panel return when empty, load, and kernel
     //paneOptional->setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutOptional")));
     pOptional->setStyleSheet(gbStyleSheet);
     pOptional->setTitle("optional");
     //pOptional->setLayout(new BoxLayout(pOptional, BoxLayout.Y_AXIS));
     QWidget* pOptionalPane = new QWidget;
     QVBoxLayout* pOptionalLayout = new QVBoxLayout(pOptionalPane);
     paneOptional->setWidget(pOptionalPane);
     paneOptional->setWidgetResizable(true);

     // row 5
     QGroupBox* pReturnWhenEmpty = new QGroupBox();
     pReturnWhenEmpty->setLayout(new GridBagLayout());
     //pReturnWhenEmpty->setBorder(BorderFactory.createTitledBorder(Bundle
     //        .getMessage("BorderLayoutReturnWhenEmpty")));
     pReturnWhenEmpty->setStyleSheet(gbStyleSheet);
     pReturnWhenEmpty->setTitle(tr("Return wnen empty"));
     addItem(pReturnWhenEmpty, new QLabel(tr("Location")), 1, 0);
     addItem(pReturnWhenEmpty, new QLabel(tr("Track")), 2, 0);
     addItem(pReturnWhenEmpty, new QLabel(tr("Load")), 3, 0);
     addItemLeft(pReturnWhenEmpty, ignoreRWECheckBox, 0, 1);
     addItem(pReturnWhenEmpty, destReturnWhenEmptyBox, 1, 1);
     addItem(pReturnWhenEmpty, trackReturnWhenEmptyBox, 2, 1);
     addItem(pReturnWhenEmpty, loadReturnWhenEmptyBox, 3, 1);
     addItem(pReturnWhenEmpty, autoReturnWhenEmptyTrackCheckBox, 4, 1);
     pOptionalLayout->addWidget(pReturnWhenEmpty);

     // add load fields
     QGroupBox* pLoad = new QGroupBox();
     pLoad->setLayout(new GridBagLayout());
     //pLoad->setBorder(BorderFactory.createTitledBorder(tr("Load")));
     pLoad->setStyleSheet(gbStyleSheet);
     pLoad->setTitle(tr("Return wnen empty"));
     addItemLeft(pLoad, ignoreLoadCheckBox, 1, 0);
     addItem(pLoad, loadComboBox, 2, 0);
     addItem(pLoad, editLoadButton, 3, 0);
     pOptionalLayout->addWidget(pLoad);

     // add kernel fields
     QGroupBox* pKernel = new QGroupBox();
     pKernel->setLayout(new GridBagLayout());
     //pKernel->setBorder(BorderFactory.createTitledBorder(tr("Kernel")));
     pKernel->setStyleSheet(gbStyleSheet);
     pKernel->setTitle(tr("Return wnen empty"));
     addItemLeft(pKernel, ignoreKernelCheckBox, 1, 0);
     addItem(pKernel, kernelComboBox, 2, 0);
     addItem(pKernel, editKernelButton, 3, 0);
     pOptionalLayout->addWidget(pKernel);

     // don't show ignore checkboxes
     ignoreRWECheckBox->setVisible(false);
     ignoreLoadCheckBox->setVisible(false);
     ignoreKernelCheckBox->setVisible(false);

     autoReturnWhenEmptyTrackCheckBox->setChecked(autoReturnWhenEmptyTrackCheckBoxSelected);

     // setup combobox
     addComboBoxAction(destReturnWhenEmptyBox);
     addComboBoxAction(loadComboBox);

     // setup button
     addButtonAction(editLoadButton);
     addButtonAction(editKernelButton);

     // setup checkboxes
     addCheckBoxAction(ignoreRWECheckBox);
     addCheckBoxAction(autoReturnWhenEmptyTrackCheckBox);
     addCheckBoxAction(ignoreLoadCheckBox);
     addCheckBoxAction(ignoreKernelCheckBox);

     // tool tips
     ignoreRWECheckBox->setToolTip(tr("When checked, ignore this set of fields during change"));
     ignoreLoadCheckBox->setToolTip(tr("When checked, ignore this set of fields during change"));
     ignoreKernelCheckBox->setToolTip(tr("When checked, ignore this set of fields during change"));
     outOfServiceCheckBox->setToolTip(tr("When checked, ignore this set of fields during change"));
     autoReturnWhenEmptyTrackCheckBox->setToolTip(tr("NOT USED! Only here for eliminate warnings from i18n consistency check"));

     // get notified if combo box gets modified
     //CarLoads::instance().addPropertyChangeListener(this);
     connect(CarLoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarManager::addPropertyChangeListener(this);
     connect(carManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));

     packFrame();
 }

 /*public*/ void CarSetFrame::loadCar(Car* car) {
     _car = car;
     load(car);
     updateLoadComboBox();
     updateKernelComboBox();
 }

 /*protected*/ void CarSetFrame::updateComboBoxes() {
     RollingStockSetFrame::updateComboBoxes();

     locationManager->updateComboBox(destReturnWhenEmptyBox);

     updateFinalDestinationComboBoxes();
     updateReturnWhenEmptyComboBoxes();
 }

 /*protected*/ void CarSetFrame::enableComponents(bool enabled) {
     // If routing is disable, the RWE and Final Destination fields do not work
     if (!Setup::isCarRoutingEnabled()) {
         ignoreRWECheckBox->setChecked(true);
         ignoreFinalDestinationCheckBox->setChecked(true);
     }

     RollingStockSetFrame::enableComponents(enabled);

     ignoreRWECheckBox->setEnabled(Setup::isCarRoutingEnabled() & enabled);
     destReturnWhenEmptyBox->setEnabled(!ignoreRWECheckBox->isChecked() & enabled);
     trackReturnWhenEmptyBox->setEnabled(!ignoreRWECheckBox->isChecked() & enabled);
     loadReturnWhenEmptyBox->setEnabled(!ignoreRWECheckBox->isChecked() & enabled);
     autoReturnWhenEmptyTrackCheckBox->setEnabled(!ignoreRWECheckBox->isChecked() & enabled);

     ignoreLoadCheckBox->setEnabled(enabled);
     loadComboBox->setEnabled(!ignoreLoadCheckBox->isChecked() & enabled);
     editLoadButton->setEnabled(!ignoreLoadCheckBox->isChecked() & enabled & _car != NULL);

     ignoreKernelCheckBox->setEnabled(enabled);
     kernelComboBox->setEnabled(!ignoreKernelCheckBox->isChecked() & enabled);
     editKernelButton->setEnabled(!ignoreKernelCheckBox->isChecked() & enabled & _car != NULL);

     enableDestinationFields(enabled);
 }

/*private*/ /*static*/ bool CarSetFrame::enableDestination = false;

 /*private*/ void CarSetFrame::enableDestinationFields(bool enabled) {
     // if car in a built train, enable destination fields
     bool enableDest = enableDestination
             || destinationBox->currentText() != NULL
             || (_car != NULL && _car->getTrain() != NULL && _car->getTrain()->isBuilt());

     destinationBox->setEnabled(!ignoreDestinationCheckBox->isChecked() & enableDest & enabled);
     trackDestinationBox->setEnabled(!ignoreDestinationCheckBox->isChecked() & enableDest & enabled);
     autoDestinationTrackCheckBox->setEnabled(!ignoreDestinationCheckBox->isChecked() & enableDest
             & enabled);
 }

 // location combo box
 /*public*/ void CarSetFrame::comboBoxActionPerformed(QWidget* ae)
 {
  _disableComboBoxUpdate = true; // stop updates
  RollingStockSetFrame::comboBoxActionPerformed(ae);
  QComboBox* source = (QComboBox*)ae;

  if (source == finalDestinationBox) {
      updateFinalDestination();
  }
  if (source == destReturnWhenEmptyBox) {
      updateReturnWhenEmpty();
  }

  _disableComboBoxUpdate = false;
 }


 /*public*/ void CarSetFrame::buttonActionPerformed(QWidget* ae)
 {
  RollingStockSetFrame::buttonActionPerformed(ae);
  QPushButton* source = (QPushButton*)ae;

  if (source == editLoadButton && _car != NULL)
  {
   if (lef != NULL)
   {
    lef->dispose();
   }
   lef = new CarLoadEditFrame();
   //lef->setLocationRelativeTo(this);
   lef->initComponents(_car->getTypeName(),  loadComboBox->currentText());
  }

  if (source == editKernelButton)
  {
   if (editActive)
   {
    f->dispose();
   }

   f = new CarAttributeEditFrame();
//         f->setLocationRelativeTo(this);
   //f.addPropertyChangeListener(this);
   connect(f->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   editActive = true;
   f->initComponents(tr("Kernel"),  kernelComboBox->currentText());
  }
 }

 /*protected*/ bool CarSetFrame::save()
 {
  if (change(_car))
  {
   OperationsXml::save();
   return true;
  }
  return false;
 }

 /*private*/ /*static*/ bool CarSetFrame::autoReturnWhenEmptyTrackCheckBoxSelected = false;

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*protected*/ bool CarSetFrame::change(Car* car)
 {
  // save the auto button
  autoReturnWhenEmptyTrackCheckBoxSelected = autoReturnWhenEmptyTrackCheckBox->isChecked();

  // car load
  if (!ignoreLoadCheckBox->isChecked() && loadComboBox->currentText() != NULL)
  {
   QString load = loadComboBox->currentText();
   if (car->getLoadName()!=(load))
   {
    if (CarLoads::instance()->containsName(car->getTypeName(), load))
    {
        car->setLoadName(load);
        updateComboBoxesLoadChange();
    }
    else
    {
//                 JOptionPane.showMessageDialog(this, MessageFormat.format(
//                         tr("carLoadNotValid"), new Object[]{load, car->getTypeName()}),
//                         tr("carCanNotChangeLoad"), JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(this, tr("Can't change load!"), tr("Load (%1) isn''t valid for car type ({%2)").arg(load).arg(car->getTypeName()));
    }
   }
  }
  // set final destination fields before destination in case there's a schedule at destination
  if (!ignoreFinalDestinationCheckBox->isChecked())
  {
   if (finalDestinationBox->currentText() == NULL)
   {
    car->setFinalDestination(NULL);
    car->setFinalDestinationTrack(NULL);
   }
   else
   {
    Track* finalDestTrack = NULL;
    if (finalDestTrackBox->currentText() != NULL)
    {
     finalDestTrack = (Track*) VPtr<Track>::asPtr(finalDestTrackBox->itemData(finalDestTrackBox->currentIndex()));
    }
    if (finalDestTrack != NULL && car->getFinalDestinationTrack() != finalDestTrack
            && finalDestTrack->getTrackType()==(Track::STAGING))
    {
     log->debug(tr("Destination track (%1) is staging").arg(finalDestTrack->getName()));
//                 JOptionPane.showMessageDialog(this, tr("rsDoNotSelectStaging"), Bundle
//                         .getMessage("rsCanNotFinal"), JOptionPane.ERROR_MESSAGE);
       QMessageBox::critical(this, tr("Final Destination"), tr("Do not select a staging track when sending a car to staging!"));
     return false;
    }
    QString status = car->testDestination((Location*) VPtr<Location>::asPtr(finalDestinationBox->itemData(finalDestinationBox->currentIndex())),
            finalDestTrack);
    if (status!=(Track::OKAY))
    {
//                 JOptionPane.showMessageDialog(this, MessageFormat.format(Bundle
//                         .getMessage("rsCanNotFinalMsg"), new Object[]{car->toString(), status}), Bundle
//                         .getMessage("rsCanNotFinal"), JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(this, tr("Final Destination"), tr("Car %1 may not be able to use Final Destination due to %2 ").arg(car->toString()).arg(status));
    }
    car->setFinalDestination((Location*) VPtr<Location>::asPtr(finalDestinationBox->itemData(finalDestinationBox->currentIndex())));
    car->setFinalDestinationTrack(finalDestTrack);
   }
  }
  // kernel
  if (!ignoreKernelCheckBox->isChecked() && kernelComboBox->currentText() != NULL)
  {
   if (kernelComboBox->currentText()==(CarManager::NONE))
   {
    car->setKernel(NULL);
   }
   else if (car->getKernelName()!=(kernelComboBox->currentText()))
   {
    car->setKernel(carManager->getKernelByName( kernelComboBox->currentText()));
    // if car has FRED or is caboose make lead
    if (car->hasFred() || car->isCaboose()) {
        car->getKernel()->setLead(car);
    }
    car->setBlocking(car->getKernel()->getSize());
   }
  }
  // save car's track
  Track* saveTrack = car->getTrack();
  if (!RollingStockSetFrame::change(car))
  {
      return false;
  }
  // return when empty fields
  if (!ignoreRWECheckBox->isChecked())
  {
   car->setReturnWhenEmptyLoadName(loadReturnWhenEmptyBox->currentText());
   if (destReturnWhenEmptyBox->currentText() == NULL) {
       car->setReturnWhenEmptyDestination(NULL);
       car->setReturnWhenEmptyDestTrack(NULL);
   }
   else
   {
    Location* locationRWE = (Location*) VPtr<Location>::asPtr(destReturnWhenEmptyBox->itemData(destReturnWhenEmptyBox->currentIndex()));
    if (trackReturnWhenEmptyBox->currentText() != NULL)
    {
     Track* trackRWE = (Track*) VPtr<Track>::asPtr(trackReturnWhenEmptyBox->itemData(trackReturnWhenEmptyBox->currentIndex()));
     // warn user if they selected a staging track
     if (trackRWE != NULL && trackRWE->getTrackType()==(Track::STAGING))
     {
      log->debug(tr("Return when empty track (%1) is staging").arg(trackRWE->getName()));
//                     JOptionPane.showMessageDialog(this, tr("rsDoNotSelectStaging"), Bundle
//                             .getMessage("rsCanNotRWE"), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Return When Empty"), tr("Do not select a staging track when sending a car to staging!"));
      return false;
     }
     // use a test car with a load of "E" and no length
     QString status = getTestCar(car)->testDestination(locationRWE, trackRWE);
     if (status!=(Track::OKAY)) {
//                     JOptionPane.showMessageDialog(this, MessageFormat.format(Bundle
//                             .getMessage("rsCanNotRWEMsg"), new Object[]{car->toString(), status}),
//                             tr("rsCanNotRWE"), JOptionPane.WARNING_MESSAGE);
      QMessageBox::warning(this, tr("Return When Empty"), tr("Car %1 may not be able to use Return When Empty due to %2").arg(car->toString()).arg(status));
     }
     car->setReturnWhenEmptyDestTrack(trackRWE);
    }
    else
    {
     car->setReturnWhenEmptyDestTrack(NULL);
    }
    car->setReturnWhenEmptyDestination(locationRWE);
   }
  }

  // check to see if there's a schedule when placing the car at a spur
  if (!ignoreLocationCheckBox->isChecked() && trackLocationBox->currentText() != NULL
          && saveTrack != VPtr<Track>::asPtr(trackLocationBox->currentData()))
  {
   Track* track = (Track*) VPtr<Track>::asPtr(trackLocationBox->itemData(trackLocationBox->currentIndex()));
   if (track->getSchedule() != NULL)
   {
//    if (JOptionPane.showConfirmDialog(this, MessageFormat.format(Bundle
//            .getMessage("rsDoYouWantSchedule"), new Object[]{car->toString()}), MessageFormat
//            .format(tr("rsSpurHasSchedule"), new Object[]{track.getName(),
//                    track.getScheduleName()}), JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
    if(QMessageBox::question(this, tr("Spur (%1) has schedule (%2)").arg(track->getName()).arg(track->getSchedule()->toString()), tr("Do you want the spur''s schedule to be applied to car (%1)?").arg(car->toString()), QMessageBox::Yes | QMessageBox::No)== QMessageBox::Yes)
    {
     QString results = track->checkSchedule(car);
     if (results!=(Track::OKAY))
     {
//         JOptionPane.showMessageDialog(this, MessageFormat.format(Bundle
//                 .getMessage("rsNotAbleToApplySchedule"), new Object[]{results}), Bundle
//                 .getMessage("rsApplyingScheduleFailed"), JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(this, tr("Applying schedule to car failed!"), tr("Not able to apply schedule because %1").arg(results));
      // restore previous location and track so we'll ask to test schedule again
      if (saveTrack != NULL) {
          car->setLocation(saveTrack->getLocation(), saveTrack);
      } else {
          car->setLocation(NULL, NULL);
      }
      return false;
     }
     // now apply schedule to car
     track->scheduleNext(car);
     car->loadNext(track);
    }
   }
  }

  // determine if train services this car's load
  if (car->getTrain() != NULL)
  {
   Train* train = car->getTrain();
   if (!train->acceptsLoad(car->getLoadName(), car->getTypeName()))
   {
//             JOptionPane.showMessageDialog(this, MessageFormat.format(Bundle
//                     .getMessage("carTrainNotServLoad"), new Object[]{car->getLoadName(), train.getName()}),
//                     tr("rsNotMove"), JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(this, tr("Car will not move!"), tr("Car''s load (%1) is not serviced by train (%2)").arg(car->getLoadName()).arg(train->getName()));

       return false;
   }
   if (car->getLocation() != NULL && car->getDestination() != NULL && !train->services(car))
   {
//             JOptionPane.showMessageDialog(this, MessageFormat.format(tr("carTrainNotService"),
//                     new Object[]{car->toString(), train.getName()}), tr("rsNotMove"),
//                     JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(this, tr("Car will not move!"), tr("Car (%1) can not be serviced by train ({%2)").arg(car->getLoadName()).arg(train->getName()));
       return false;
   }
  }
  checkTrain(car);
  // is this car part of a kernel?
  if (askKernelChange && car->getKernel() != NULL)
  {
   QList<RollingStock*> list = car->getKernel()->getGroup();
   if (list.size() > 1)
   {
//             if (JOptionPane.showConfirmDialog(this, MessageFormat.format(
//                     tr("carInKernel"), new Object[]{car->toString()}), MessageFormat
//                     .format(tr("carPartKernel"), new Object[]{car->getKernelName()}),
//                     JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
    if(QMessageBox::question(this, tr("Car is part of kernel (%1)").arg(car->getKernelName()), tr("Car (%1) is part of a kernel, do you want the other cars to also have the same settings?").arg(car->toString()), QMessageBox::Yes | QMessageBox::No)== QMessageBox::Yes)
    {
     if (!updateGroup(list))
     {
         return false;
     }
    } else if (outOfServiceCheckBox->isChecked())
    {
        car->setKernel(NULL); // don't leave car in kernel if out of service
    }
   }
  }
  return true;
 }

 /**
  * Update locations if load changes. New load could change which track are
  * allowed if auto selected. Return When Empty (RWE) always uses the default
  * empty load of "E".
  */
 /*protected*/ void CarSetFrame::updateComboBoxesLoadChange() {
     if (autoTrackCheckBox->isChecked()) {
         updateLocationTrackComboBox();
     }
     if (autoDestinationTrackCheckBox->isChecked()) {
         updateDestinationTrackComboBox();
     }
     if (autoFinalDestTrackCheckBox->isChecked()) {
         updateFinalDestination();
     }
 }

 /*protected*/ bool CarSetFrame::updateGroup(QList<RollingStock*> list) {
     foreach (RollingStock* rs, list) {
         Car* car = (Car*) rs;
         if (car == _car) {
             continue;
         }
         // make all cars in kernel the same
         if (!ignoreRWECheckBox->isChecked()) {
             car->setReturnWhenEmptyDestination(_car->getReturnWhenEmptyDestination());
             car->setReturnWhenEmptyDestTrack(_car->getReturnWhenEmptyDestTrack());
         }
         if (!ignoreFinalDestinationCheckBox->isChecked()) {
             car->setFinalDestination(_car->getFinalDestination());
             car->setFinalDestinationTrack(_car->getFinalDestinationTrack());
         }
         // update car load
         if (!ignoreLoadCheckBox->isChecked()
                 && CarLoads::instance()->containsName(car->getTypeName(), _car->getLoadName())) {
             car->setLoadName(_car->getLoadName());
         }
         // update kernel
         if (!ignoreKernelCheckBox->isChecked()) {
             car->setKernel(_car->getKernel());
         }
     }
     return RollingStockSetFrame::updateGroup(list);
 }

 /*public*/ void CarSetFrame::checkBoxActionPerformed(QWidget* ae)
{
 QCheckBox* source = (QCheckBox*)ae;
  _disableComboBoxUpdate = true; // stop updates
  RollingStockSetFrame::checkBoxActionPerformed(ae);
  if (source == autoFinalDestTrackCheckBox) {
      updateFinalDestination();
  }
  if (source == autoReturnWhenEmptyTrackCheckBox) {
      updateReturnWhenEmpty();
  }
  if (source == autoTrainCheckBox) {
      updateTrainComboBox();
  }
  if (source == ignoreRWECheckBox) {
      destReturnWhenEmptyBox->setEnabled(!ignoreRWECheckBox->isChecked());
      trackReturnWhenEmptyBox->setEnabled(!ignoreRWECheckBox->isChecked());
      loadReturnWhenEmptyBox->setEnabled(!ignoreRWECheckBox->isChecked());
      autoReturnWhenEmptyTrackCheckBox->setEnabled(!ignoreRWECheckBox->isChecked());
  }
  if (source == ignoreLoadCheckBox) {
      loadComboBox->setEnabled(!ignoreLoadCheckBox->isChecked());
      editLoadButton->setEnabled(!ignoreLoadCheckBox->isChecked() & _car != NULL);
  }
  if (source == ignoreKernelCheckBox) {
      kernelComboBox->setEnabled(!ignoreKernelCheckBox->isChecked());
      editKernelButton->setEnabled(!ignoreKernelCheckBox->isChecked());
  }
  _disableComboBoxUpdate = false;
 }

 /*protected*/ void CarSetFrame::updateReturnWhenEmptyComboBoxes() {
     if (_car != NULL) {
         log->debug(tr("Updating return when empty for car (%1)").arg(_car->toString()));
         destReturnWhenEmptyBox->setCurrentIndex(destReturnWhenEmptyBox->findData(VPtr<Location>::asQVariant(_car->getReturnWhenEmptyDestination())));
     }
     updateReturnWhenEmpty();
 }

 /*protected*/ void CarSetFrame::updateReturnWhenEmpty() {
     if (destReturnWhenEmptyBox->currentText() == NULL) {
         trackReturnWhenEmptyBox->clear();
     } else {
         log->debug(tr("CarSetFrame sees return when empty: %1").arg(destReturnWhenEmptyBox->currentText()));
         Location* l = (Location*) VPtr<Location>::asPtr(destReturnWhenEmptyBox->itemData(destReturnWhenEmptyBox->currentIndex()));
         l->updateComboBox(trackReturnWhenEmptyBox, getTestCar(_car),
                 autoReturnWhenEmptyTrackCheckBox->isChecked(), true);
         if (_car != NULL && _car->getReturnWhenEmptyDestination() != NULL
                 && _car->getReturnWhenEmptyDestination()==(l)
                 && _car->getReturnWhenEmptyDestTrack() != NULL) {
             trackReturnWhenEmptyBox->setCurrentIndex(trackReturnWhenEmptyBox->findData(VPtr<Track>::asQVariant(_car->getReturnWhenEmptyDestTrack())));
         }
     }
 }

 /*protected*/ void CarSetFrame::updateFinalDestinationComboBoxes() {
     if (_car != NULL) {
         log->debug(tr("Updating final destinations for car (%1)").arg(_car->toString()));
         finalDestinationBox->setCurrentIndex(finalDestinationBox->findData(VPtr<Location>::asQVariant(_car->getFinalDestination())));
     }
     updateFinalDestination();
 }

 /*protected*/ void CarSetFrame::updateFinalDestination() {
     if (finalDestinationBox->currentText() == NULL) {
         finalDestTrackBox->clear();
     } else {
         log->debug(tr("CarSetFrame sees final destination: %1").arg(finalDestinationBox->currentText()));
         Location* l = (Location*) VPtr<Location*>::asPtr(finalDestinationBox->itemData(finalDestinationBox->currentIndex()));
         l->updateComboBox(finalDestTrackBox, _car, autoFinalDestTrackCheckBox->isChecked(), true);
         if (_car != NULL && _car->getFinalDestination() != NULL && _car->getFinalDestination()==(l)
                 && _car->getFinalDestinationTrack() != NULL) {
             finalDestTrackBox->setCurrentIndex(finalDestTrackBox->findData(VPtr<Track>::asQVariant(_car->getFinalDestinationTrack())));
         }
     }
 }

 /*protected*/ void CarSetFrame::updateLoadComboBox() {
     if (_car != NULL) {
         log->debug(tr("Updating load box for car (%1)").arg(_car->toString()));
         CarLoads::instance()->updateComboBox(_car->getTypeName(), loadComboBox);
         loadComboBox->setCurrentIndex(loadComboBox->findText(_car->getLoadName()));
         CarLoads::instance()->updateRweComboBox(_car->getTypeName(), loadReturnWhenEmptyBox);
         loadReturnWhenEmptyBox->setCurrentIndex(loadReturnWhenEmptyBox->findText(_car->getReturnWhenEmptyLoadName()));
     }
 }

 /*protected*/ void CarSetFrame::updateKernelComboBox() {
     carManager->updateKernelComboBox(kernelComboBox);
     if (_car != NULL) {
         kernelComboBox->setCurrentIndex(kernelComboBox->findText(_car->getKernelName()));
     }
 }

 /*protected*/ void CarSetFrame::updateTrainComboBox() {
     log->debug("update train combo box");
     if (_car != NULL && autoTrainCheckBox->isChecked()) {
         log->debug(tr("Updating train box for car (%1)").arg(_car->toString()));
         trainManager->updateTrainComboBox(trainBox, _car);
     } else {
         trainManager->updateTrainComboBox(trainBox);
     }
     if (_car != NULL) {
         trainBox->setCurrentIndex(trainBox->findData(VPtr<Train>::asQVariant(_car->getTrain())));
     }
 }

 /*private*/ Car* CarSetFrame::getTestCar(Car* car) {
     Car* c = car;
     // clone car and set the load to default empty and a length of zero
     if (car != NULL) {
         c = car->copy();
         c->setLoadName(CarLoads::instance()->getDefaultEmptyName());
         c->setLength("0"); // ignore car length
     }
     return c;
 }

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*public*/ void CarSetFrame::setDestinationEnabled(bool enable) {
     enableDestination = !enableDestination;
     enableDestinationFields(!locationUnknownCheckBox->isChecked());
 }

 /*public*/ void CarSetFrame::dispose() {
     //CarLoads::instance().removePropertyChangeListener(this);
     disconnect(CarLoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarManager::removePropertyChangeListener(this);
     connect(carManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
     RollingStockSetFrame::dispose();
 }

 /*public*/ void CarSetFrame::propertyChange(PropertyChangeEvent* e) {
     log->debug(tr("PropertyChange (%1) new ({%2)").arg(e->getPropertyName()).arg(e->getNewValue().toString()));
     RollingStockSetFrame::propertyChange(e);
     if (e->getPropertyName()==(_car->FINAL_DESTINATION_CHANGED_PROPERTY)
             || e->getPropertyName()==(_car->FINAL_DESTINATION_TRACK_CHANGED_PROPERTY)) {
         updateFinalDestinationComboBoxes();
     }
     if (e->getPropertyName()==(CarLoads::LOAD_CHANGED_PROPERTY)
             || e->getPropertyName()==(CarLoads::LOAD_TYPE_CHANGED_PROPERTY)
             || e->getPropertyName()==(_car->LOAD_CHANGED_PROPERTY)) {
         updateLoadComboBox();
     }
     if (e->getPropertyName()==(_car->RETURN_WHEN_EMPTY_CHANGED_PROPERTY)) {
         updateReturnWhenEmptyComboBoxes();
     }
     if (e->getPropertyName()==(CarManager::KERNEL_LISTLENGTH_CHANGED_PROPERTY)
             || e->getPropertyName()==(_car->KERNEL_NAME_CHANGED_PROPERTY)) {
         updateKernelComboBox();
     }
     if (e->getPropertyName()==(_car->TRAIN_CHANGED_PROPERTY)) {
         enableDestinationFields(!locationUnknownCheckBox->isChecked());
     }
     if (e->getPropertyName()==(CarAttributeEditFrame::DISPOSE)) {
         editActive = false;
     }
 }
}
