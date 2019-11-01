#include "carssetframe.h"
#include "carstablemodel.h"
#include <QSortFilterProxyModel>
#include "jtable.h"
#include <QPushButton>
#include "car.h"
#include "kernel.h"
#include <QCheckBox>
#include <QMessageBox>
#include "logger.h"

namespace Operations
{
/**
 * Frame for user to place a group of cars on the layout
 *
 * @author Dan Boudreau Copyright (C) 2011, 2013
 * @version $Revision: 28746 $
 */
///*public*/ class CarsSetFrame extends CarSetFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -3962047189679581L;

 /*public*/ CarsSetFrame::CarsSetFrame(QWidget* parent) : CarSetFrame(parent){
     //super();
  toggle = true;
  log = new Logger("CarsSetFrame");
 }

 // Ignore checkbox states
 /*private*/ /*static*/ bool CarsSetFrame::ignoreStatusCheckBoxSelected = false;
 /*private*/ /*static*/ bool CarsSetFrame::ignoreLocationCheckBoxSelected = false;
 /*private*/ /*static*/ bool CarsSetFrame::ignoreRWECheckBoxSelected = false;
 /*private*/ /*static*/ bool CarsSetFrame::ignoreLoadCheckBoxSelected = false;
 /*private*/ /*static*/ bool CarsSetFrame::ignoreKernelCheckBoxSelected = false;
 /*private*/ /*static*/ bool CarsSetFrame::ignoreDestinationCheckBoxSelected = false;
 /*private*/ /*static*/ bool CarsSetFrame::ignoreFinalDestinationCheckBoxSelected = false;
 /*private*/ /*static*/ bool CarsSetFrame::ignoreTrainCheckBoxSelected = false;

 /*public*/ void CarsSetFrame::initComponents(JTable* carsTable) {
     _carsTable = carsTable;
     _carsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
     _carsTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
     _sorter = (QSortFilterProxyModel*) carsTable->getModel();
     _carsTableModel = (CarsTableModel*) _sorter->sourceModel();

     CarSetFrame::initComponents();

     setTitle(tr("Set Cars"));
     addHelpMenu("package.jmri.jmrit.operations.Operations_SetCars", true); // NOI18N
     // modify Save button text to "Change"
     saveButton->setText(tr("Change"));
     // disable edit load button if no cars selected
     editLoadButton->setEnabled(false);
     // show ignore checkboxes
     ignoreStatusCheckBox->setVisible(true);
     ignoreLocationCheckBox->setVisible(true);
     ignoreRWECheckBox->setVisible(true);
     ignoreLoadCheckBox->setVisible(true);
     ignoreKernelCheckBox->setVisible(true);
     ignoreDestinationCheckBox->setVisible(true);
     ignoreFinalDestinationCheckBox->setVisible(true);
     ignoreTrainCheckBox->setVisible(true);
     ignoreAllButton->setVisible(true);

     // set the last state
     ignoreStatusCheckBox->setChecked(ignoreStatusCheckBoxSelected);
     ignoreLocationCheckBox->setChecked(ignoreLocationCheckBoxSelected);
     ignoreRWECheckBox->setChecked(ignoreRWECheckBoxSelected);
     ignoreLoadCheckBox->setChecked(ignoreLoadCheckBoxSelected);
     ignoreKernelCheckBox->setChecked(ignoreKernelCheckBoxSelected);
     ignoreDestinationCheckBox->setChecked(ignoreDestinationCheckBoxSelected);
     ignoreFinalDestinationCheckBox->setChecked(ignoreFinalDestinationCheckBoxSelected);
     ignoreTrainCheckBox->setChecked(ignoreTrainCheckBoxSelected);

     QVector<int>* rows = _carsTable->getSelectedRows();
     if (rows->length() > 0)
     {
      QModelIndex src = _sorter->mapFromSource(_sorter->index(rows->at(0),0));
         Car* car = _carsTableModel->getCarAtIndex(/*_sorter->modelIndex(rows[0])*/src.row());
         CarSetFrame::loadCar(car);
     }
 }

 /*public*/ void CarsSetFrame::buttonActionPerformed(QWidget* ae) {
     CarSetFrame::buttonActionPerformed(ae);

     if ((QPushButton*) ae == ignoreAllButton) {
         ignoreAll(toggle);
     }
 }


 /*protected*/ void CarsSetFrame::ignoreAll(bool b) {
     ignoreStatusCheckBox->setChecked(!locationUnknownCheckBox->isChecked() & b);
     ignoreLocationCheckBox->setChecked(b);
     ignoreRWECheckBox->setChecked(b);
     ignoreLoadCheckBox->setChecked(b);
     ignoreKernelCheckBox->setChecked(b);
     ignoreDestinationCheckBox->setChecked(b);
     ignoreFinalDestinationCheckBox->setChecked(b);
     ignoreTrainCheckBox->setChecked(b);
     enableComponents(!locationUnknownCheckBox->isChecked());
     toggle = !b;
 }

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*protected*/ bool CarsSetFrame::save() {
     // save ignore states
     ignoreStatusCheckBoxSelected = ignoreStatusCheckBox->isChecked();
     ignoreLocationCheckBoxSelected = ignoreLocationCheckBox->isChecked();
     ignoreRWECheckBoxSelected = ignoreRWECheckBox->isChecked();
     ignoreLoadCheckBoxSelected = ignoreLoadCheckBox->isChecked();
     ignoreKernelCheckBoxSelected = ignoreKernelCheckBox->isChecked();
     ignoreDestinationCheckBoxSelected = ignoreKernelCheckBox->isChecked();
     ignoreFinalDestinationCheckBoxSelected = ignoreFinalDestinationCheckBox->isChecked();
     ignoreTrainCheckBoxSelected = ignoreTrainCheckBox->isChecked();

     QVector<int>* rows = _carsTable->getSelectedRows();
     if (rows->length() == 0) {
//         JOptionPane.showMessageDialog(this, tr("selectCars"), Bundle
//                 .getMessage("carNoneSelected"), JOptionPane.WARNING_MESSAGE);
      QMessageBox::warning(this, tr("No cars selected!"), tr("You need to select the cars you want to change!"));
     }

     askKernelChange = true;

     for (int i = 0; i < rows->length(); i++)
     {
      QModelIndex src = _sorter->mapFromSource(_sorter->index(rows->at(0),0));
         Car* car = _carsTableModel->getCarAtIndex(/*_sorter->modelIndex(rows[i]*/src.row());
         if (_car == NULL) {
             CarSetFrame::loadCar(car);
             continue;
         }
         if (i == 0 && car != _car) {
             log->debug("Default car isn't the first one selected");
//             if (JOptionPane.showConfirmDialog(this, MessageFormat.format(Bundle
//                     .getMessage("doYouWantToChange"), new Object[]{car.toString()}), Bundle
//                     .getMessage("changeDefaultCar"), JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
             if(QMessageBox::question(this, tr("Change the default car?"), tr("Do you want to change the default car to %1?").arg(car->toString()), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
             {
                 CarSetFrame::loadCar(car); // new default car
                 break; // done, don't modify any of the cars selected
             }
         }
         if (!CarSetFrame::change(car)) {
             return false;
         } else if (car->getKernel() != NULL && !ignoreKernelCheckBox->isChecked()) {
             askKernelChange = false;
         }
     }
     return true;
 }
}
