#include "printcarrosteraction.h"
#include "jframe.h"
#include "hardcopywriter.h"
#include "carstableframe.h"
#include "rollingstock.h"
#include "car.h"
#include "carstablemodel.h"
#include "jcombobox.h"
#include <QBoxLayout>
#include <QCheckBox>
#include "jbutton.h"
#include "setup.h"
#include "locationmanager.h"
#include "control.h"
#include "jframe.h"
#include "carroads.h"
#include "cartypes.h"
#include "carcolors.h"
#include "carloads.h"
#include "carowners.h"
#include <QGroupBox>
#include "flowlayout.h"
#include "gridbaglayout.h"
#include <QScrollArea>
#include "carstablemodel.h"
#include <QRadioButton>
#include "instancemanager.h"
#include "borderfactory.h"

namespace Operations
{
 /**
  * Action to print a summary of the Roster contents
  * <P>
  * This uses the older style printing, for compatibility with Java 1.1.8 in
  * MacIntosh MRJ
  *
  * @author Bob Jacobsen Copyright (C) 2003
  * @author Dennis Miller Copyright (C) 2005
  * @author Daniel Boudreau Copyright (C) 2008, 2010, 2011, 2012, 2013, 2014
  * @version $Revision: 28843 $
  */
 ///*public*/ class PrintCarRosterAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 6012807784689139181L;

 /*public*/ PrintCarRosterAction::PrintCarRosterAction(QString actionName, JFrame* frame, bool preview, QWidget* pWho)
    : AbstractAction(actionName, (QObject*)pWho)
 {
     //super(actionName);
  cpof = NULL;
  mFrame = frame;
  isPreview = preview;
  panel = (CarsTableFrame*) pWho;
  sortByComboBox = new JComboBox();
  manifestOrientationComboBox = new JComboBox();
  fontSizeComboBox = new JComboBox();


  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }


 /*public*/ void PrintCarRosterAction::actionPerformed(ActionEvent* /*e*/) {
     if (cpof == NULL) {
         cpof = new CarPrintOptionFrame(this);
     } else {
         cpof->setVisible(true);
     }
     cpof->initComponents();
 }


 /*private*/ void PrintCarRosterAction::printCars() {

     bool landscape = false;
     if (manifestOrientationComboBox->currentText() != NULL
             && manifestOrientationComboBox->currentText() == Setup::LANDSCAPE) {
         landscape = true;
     }

     int fontSize = (int) fontSizeComboBox->currentData().toInt();

     // obtain a HardcopyWriter to do this
     HardcopyWriter* writer = NULL;
     //try {
         writer = new HardcopyWriter(mFrame, tr("Car Roster"), fontSize, .5, .5, .5, .5, isPreview, "",
                 landscape, true, QSize());
//     } catch (HardcopyWriter.PrintCanceledException ex) {
//         log.debug("Print cancelled");
//         return;
//     }

     numberCharPerLine = writer->getCharactersPerLine();

     // Loop through the Roster, printing as needed
     QString location = "";
     QString number;
     QString road;
     QString type;
     QString length = "";
     QString weight = "";
     QString color = "";
     QString owner = "";
     QString built = "";
     QString load = "";
     QString kernel = "";
     QString train = "";
     QString destination = "";
     QString finalDestination = "";
     QString returnWhenEmpty = "";
     QString value = "";
     QString rfid = "";
     QString last = "";
     QString wait = "";
     QString schedule = "";
     QString comment = "";

     //try {
         printTitleLine(writer);
         QString previousLocation = NULL;
         QList<Car*>* cars = panel->carsTableModel->getCarList(sortByComboBox->currentIndex());
         foreach (Car* rs, *cars) {
             Car* car = (Car*) rs;
             if (cpof->printCarsWithLocation->isChecked() && car->getLocation() == NULL) {
                 continue; // car doesn't have a location skip
             }
             location = "";
             destination = "";
             finalDestination = "";
             returnWhenEmpty = "";

             if (cpof->printCarLocation->isChecked()) {
                 if (car->getLocation() != NULL) {
                     location = car->getLocationName().trimmed() + " - " + car->getTrackName().trimmed();
                 }
                 location = padAttribute(location, ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"))->getMaxLocationAndTrackNameLength() + 3);
             }
             // Page break between locations?
             if (previousLocation != NULL && car->getLocationName().trimmed()!=(previousLocation)
                     && cpof->printPage->isChecked()) {
                 writer->pageBreak();
                 printTitleLine(writer);
             } // Add a line between locations?
             else if (previousLocation != NULL && car->getLocationName().trimmed()!=(previousLocation)
                     && cpof->printSpace->isChecked()) {
                 writer->write(NEW_LINE);
             }
             previousLocation = car->getLocationName().trimmed();

             // car number
             number = padAttribute(car->getNumber().trimmed(), Control::max_len_string_print_road_number);
             // car road
             road = padAttribute(car->getRoadName().trimmed(), ((CarRoads*)InstanceManager::getDefault("Operations::CarRoads"))->getMaxNameLength());
             // car type
             type = padAttribute(car->getTypeName().trimmed(), ((CarTypes*)InstanceManager::getDefault("CarTypes"))->getMaxFullNameLength());

             if (cpof->printCarLength->isChecked()) {
                 length = padAttribute(car->getLength().trimmed(), Control::max_len_string_length_name);
             }
             if (cpof->printCarWeight->isChecked()) {
                 weight = padAttribute(car->getWeight().trimmed(), Control::max_len_string_weight_name);
             }
             if (cpof->printCarColor->isChecked()) {
                 color = padAttribute(car->getColor().trimmed(), ((CarColors*)InstanceManager::getDefault("Operations::CarColors"))->getMaxNameLength());
             }
             if (cpof->printCarLoad->isChecked()) {
                 load = padAttribute(car->getLoadName().trimmed(), ((CarLoads*)InstanceManager::getDefault("Operations::CarLoads"))->getMaxNameLength());
             }
             if (cpof->printCarKernel->isChecked()) {
                 kernel = padAttribute(car->getKernelName().trimmed(), Control::max_len_string_attibute);
             }
             if (cpof->printCarOwner->isChecked()) {
                 owner = padAttribute(car->getOwner().trimmed(), ((CarOwners*)InstanceManager::getDefault("Operations::CarOwners"))->getMaxNameLength());
             }
             if (cpof->printCarBuilt->isChecked()) {
                 built = padAttribute(car->getBuilt().trimmed(), Control::max_len_string_built_name);
             }
             if (cpof->printCarLast->isChecked()) {
                 last = padAttribute(car->getLastDate().split(" ")[0], 10);
             }
             if (cpof->printCarWait->isChecked()) {
                 wait = padAttribute(QString::number(car->getWait()), 4);
             }
             if (cpof->printCarPickup->isChecked()) {
                 schedule = padAttribute(car->getPickupScheduleName(), 10);
             }
             if (cpof->printCarValue->isChecked()) {
                 value = padAttribute(car->getValue().trimmed(), Control::max_len_string_attibute);
             }
             if (cpof->printCarRfid->isChecked()) {
                 rfid = padAttribute(car->getRfid().trimmed(), Control::max_len_string_attibute);
             }
             if (cpof->printCarTrain->isChecked()) // pad out train to half of its maximum
             {
                 train = padAttribute(car->getTrainName().trimmed(), Control::max_len_string_train_name / 2);
             }
             if (cpof->printCarDestination->isChecked()) {
                 if (car->getDestination() != NULL) {
                     destination = car->getDestinationName().trimmed() + " - " + car->getDestinationTrackName();
                 }
                 destination = padAttribute(destination, ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"))
                         ->getMaxLocationAndTrackNameLength() + 3);
             }
             if (cpof->printCarFinalDestination->isChecked()) {
                 if (car->getFinalDestination() != NULL) {
                     finalDestination = car->getFinalDestinationName().trimmed() + " - "
                             + car->getFinalDestinationTrackName().trimmed();
                 }
                 finalDestination = padAttribute(finalDestination, ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"))
                         ->getMaxLocationAndTrackNameLength() + 3);
             }
             if (cpof->printCarRWE->isChecked()) {
                 if (car->getReturnWhenEmptyDestination() != NULL) {
                     returnWhenEmpty = car->getReturnWhenEmptyDestinationName().trimmed() + " - "
                             + car->getReturnWhenEmptyDestTrackName().trimmed();
                 }
                 returnWhenEmpty = padAttribute(returnWhenEmpty, ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"))
                         ->getMaxLocationAndTrackNameLength() + 3);
             }
             if (cpof->printCarComment->isChecked()) {
                 comment = car->getComment().trimmed();
             }

             QString s = number + road + type + length + weight + color + load + kernel + owner + built + last + wait
                     + schedule + value + rfid + location + train + destination + finalDestination + returnWhenEmpty
                     + comment;

             if (s.length() > numberCharPerLine) {
                 s = s.mid(0, numberCharPerLine);
             }
             writer->write(s + NEW_LINE);
         }

         // and force completion of the printing
         writer->close();
//     } catch (IOException* we) {
//         log.error("Error printing car roster");
//     }
 }

 /*private*/ void PrintCarRosterAction::printTitleLine(HardcopyWriter* writer) //throws IOException
 {
     QString s = padAttribute(tr("Number"), Control::max_len_string_print_road_number)
             + padAttribute(tr("Road"), ((CarRoads*)InstanceManager::getDefault("Operations::CarRoads"))->getMaxNameLength())
             + padAttribute(tr("Type"), ((CarTypes*)InstanceManager::getDefault("CarTypes"))->getMaxFullNameLength())
             + (cpof->printCarLength->isChecked() ? tr("Len") + "  " : "")
             + (cpof->printCarWeight->isChecked() ? "     " : "")
             + (cpof->printCarColor->isChecked() ? padAttribute(tr("Color"), ((CarColors*)InstanceManager::getDefault("Operations::CarColors"))
                             ->getMaxNameLength()) : "")
             + (cpof->printCarLoad->isChecked() ? padAttribute(tr("Load"), ((CarLoads*)InstanceManager::getDefault("Operations::CarLoads"))
                             ->getMaxNameLength()) : "")
             + (cpof->printCarKernel->isChecked() ? padAttribute(("Kernel"), Control::max_len_string_attibute) : "")
             + (cpof->printCarOwner->isChecked() ? padAttribute(tr("Owner"), ((CarOwners*)InstanceManager::getDefault("Operations::CarOwners"))->getMaxNameLength()) : "")
             + (cpof->printCarBuilt->isChecked() ? tr("Built") + " " : "")
             + (cpof->printCarLast->isChecked() ? tr("LastMoved") + " " : "")
             + (cpof->printCarWait->isChecked() ? tr("Wait") + " " : "")
             + (cpof->printCarPickup->isChecked() ? padAttribute(tr("Pickup"), 10) : "")
             + (cpof->printCarValue->isChecked() ? Setup::getValueLabel() + "        " : "")
             + (cpof->printCarRfid->isChecked() ? Setup::getRfidLabel() + "        " : "")
             + (cpof->printCarLocation->isChecked() ? padAttribute(tr("Location"),
                                                                   ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"))->getMaxLocationAndTrackNameLength() + 3) : "")
             + (cpof->printCarTrain->isChecked() ? padAttribute(tr("Train"),
                             Control::max_len_string_train_name / 2) : "")
             + (cpof->printCarDestination->isChecked() ? padAttribute(tr("Destination"), ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"))->getMaxLocationAndTrackNameLength() + 3) : "")
             + (cpof->printCarFinalDestination->isChecked() ? padAttribute(tr("FinalDestination"),
                             ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"))->getMaxLocationAndTrackNameLength() + 3) : "")
             + (cpof->printCarRWE->isChecked() ? padAttribute(tr("ReturnWhenEmpty"), ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"))->getMaxLocationAndTrackNameLength() + 3) : "")
             + (cpof->printCarComment->isChecked() ? tr("Comment") : "");
     if (s.length() > numberCharPerLine) {
         s = s.mid(0, numberCharPerLine);
     }
     writer->write(s + NEW_LINE);
 }

 /*private*/ QString PrintCarRosterAction::padAttribute(QString attribute, int length) {
     if (attribute.length() > length) {
         attribute = attribute.mid(0, length);
     }
     QString buf = QString(attribute);
     for (int i = attribute.length(); i < length + 1; i++) {
         buf.append(" ");
     }
     return buf/*.toString()*/;
 }


 /*static*/ /*final*/ QString PrintCarRosterAction::NEW_LINE = "\n"; // NOI18N

 ///*public*/ class CarPrintOptionFrame extends OperationsFrame {

 /**
  *
  */
 //private static final long serialVersionUID = -7320807344781148331L;
 //PrintCarRosterAction pcr;

 /*public*/ CarPrintOptionFrame::CarPrintOptionFrame(PrintCarRosterAction* pcr)
  : OperationsFrame()
 {
     //super();
 printCarsWithLocation = new QCheckBox(tr("Only print cars with a location"));
 printCarLength = new QCheckBox(tr("Print car's length"));
 printCarWeight = new QCheckBox(tr("Print car's weight"));
 printCarColor = new QCheckBox(tr("Print car's color"));
 printCarOwner = new QCheckBox(tr("Print car's owner"));
 printCarBuilt = new QCheckBox(tr("Print car's built date"));
 printCarLoad = new QCheckBox(tr("Print car's load"));
 printCarKernel = new QCheckBox(tr("Print car's kernel"));
 printCarValue = new QCheckBox(tr("Print car's %1").arg(Setup
     ::getValueLabel()));
 printCarRfid = new QCheckBox(tr("Print car's %1").arg(Setup
     ::getRfidLabel()));
 printCarLast = new QCheckBox(tr("PrintCarLastMoved"));
 printCarWait = new QCheckBox(tr("Print car's wait count"));
 printCarPickup = new QCheckBox(tr("Print car's pickup schedule"));
 printCarLocation = new QCheckBox(tr("Print car's location"));
 printCarTrain = new QCheckBox(tr("Print car's train"));
 printCarDestination = new QCheckBox(tr("Print car's destination"));
 printCarFinalDestination = new QCheckBox(tr("Print car's final destination"));
 printCarRWE = new QCheckBox(tr("Print car's return when empty"));
 printCarComment = new QCheckBox(tr("Print car's comment"));
 printSpace = new QCheckBox(tr("Add line between locations"));
 printPage = new QCheckBox(tr("Start each location on a new page"));

 okayButton = new JButton(tr("OK"));this->pcr = pcr;
     // create panel
     JPanel* pSortBy = new JPanel();
     pSortBy->setLayout(new FlowLayout);
     pSortBy->setBorder(BorderFactory::createTitledBorder(tr("Sort By")));
     pSortBy->layout()->addWidget(pcr->sortByComboBox);
     addComboBoxAction(pcr->sortByComboBox);

     JPanel* pOrientation = new JPanel();
     pOrientation->setLayout(new FlowLayout);
     pOrientation->setBorder(BorderFactory::createTitledBorder(tr("Orientation")));
     pOrientation->layout()->addWidget(pcr->manifestOrientationComboBox);

     pcr->manifestOrientationComboBox->addItem(Setup::PORTRAIT);
     pcr->manifestOrientationComboBox->addItem(Setup::LANDSCAPE);

     JPanel* pFontSize = new JPanel();
     pFontSize->setLayout(new FlowLayout);
     pFontSize->setBorder(BorderFactory::createTitledBorder(tr("Font Size")));
     pFontSize->layout()->addWidget(pcr->fontSizeComboBox);

     // load font sizes 5 through 14
     for (int i = 5; i < 15; i++) {
         pcr->fontSizeComboBox->addItem(QString::number(i),i);
     }

     pcr->fontSizeComboBox->setCurrentIndex(pcr->fontSizeComboBox->findData(Control::reportFontSize));

     JPanel* pPanelFrame = new JPanel;
     pPanelFrame->setLayout(new QVBoxLayout);
     JPanel* pPanel = new JPanel();
     pPanel->setLayout(new GridBagLayout());
     QScrollArea* panePanel = new QScrollArea(/*pPanel*/);
     pPanelFrame->layout()->addWidget(panePanel);
     pPanelFrame->setBorder(BorderFactory::createTitledBorder(tr("Print Options")));
     addItemLeft(pPanel, printCarsWithLocation, 0, 0);
     addItemLeft(pPanel, printCarLength, 0, 1);
     addItemLeft(pPanel, printCarWeight, 0, 2);
     addItemLeft(pPanel, printCarColor, 0, 3);
     addItemLeft(pPanel, printCarLoad, 0, 4);
     addItemLeft(pPanel, printCarKernel, 0, 5);
     addItemLeft(pPanel, printCarOwner, 0, 6);
     addItemLeft(pPanel, printCarBuilt, 0, 7);
     addItemLeft(pPanel, printCarLast, 0, 8);
     addItemLeft(pPanel, printCarWait, 0, 9);
     addItemLeft(pPanel, printCarPickup, 0, 10);
     if (Setup::isValueEnabled()) {
         addItemLeft(pPanel, printCarValue, 0, 11);
     }
     if (Setup::isRfidEnabled()) {
         addItemLeft(pPanel, printCarRfid, 0, 12);
     }
     addItemLeft(pPanel, printCarLocation, 0, 13);
     addItemLeft(pPanel, printCarTrain, 0, 14);
     addItemLeft(pPanel, printCarDestination, 0, 15);
     addItemLeft(pPanel, printCarFinalDestination, 0, 16);
     addItemLeft(pPanel, printCarRWE, 0, 17);
     addItemLeft(pPanel, printCarComment, 0, 18);
     addItemLeft(pPanel, printSpace, 0, 19);
     addItemLeft(pPanel, printPage, 0, 20);

     // set defaults
     printCarsWithLocation->setChecked(false);
     printCarLength->setChecked(true);
     printCarWeight->setChecked(false);
     printCarColor->setChecked(true);
     printCarLoad->setChecked(false);
     printCarKernel->setChecked(false);
     printCarOwner->setChecked(false);
     printCarBuilt->setChecked(false);
     printCarLast->setChecked(false);
     printCarWait->setChecked(false);
     printCarPickup->setChecked(false);
     printCarValue->setChecked(false);
     printCarRfid->setChecked(false);
     printCarLocation->setChecked(true);
     printCarTrain->setChecked(false);
     printCarDestination->setChecked(false);
     printCarFinalDestination->setChecked(false);
     printCarRWE->setChecked(false);
     printCarComment->setChecked(false);
     printSpace->setChecked(false);
     printPage->setChecked(false);

     // add tool tips
     printSpace->setToolTip(tr("Select sort by location to enable"));
     printPage->setToolTip(tr("TipSelectSortByLoc"));

     JPanel* pButtons = new JPanel();
     pButtons->setLayout(new GridBagLayout());
     pButtons->layout()->addWidget(okayButton);
     pButtons->setBorder(BorderFactory::createTitledBorder(""));
     addButtonAction(okayButton);

     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
     QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
     thisLayout->addWidget(pSortBy);
     thisLayout->addWidget(pOrientation);
     thisLayout->addWidget(pFontSize);
     panePanel->setWidget(pPanel);
     thisLayout->addWidget(panePanel);
     thisLayout->addWidget(pButtons);

     initMinimumSize(QSize(Control::panelWidth300, Control::panelHeight500));
 }

 /*public*/ void CarPrintOptionFrame::initComponents() {
     if (pcr->isPreview) {
         setTitle(tr("Preview"));
     } else {
         setTitle(tr("Print"));
     }
     loadSortByComboBox(pcr->sortByComboBox);
     printSpace->setEnabled(pcr->panel->sortByLocation->isChecked());
     printPage->setEnabled(pcr->panel->sortByLocation->isChecked());
     if (!pcr->panel->sortByLocation->isChecked()) {
         printSpace->setChecked(false);
         printPage->setChecked(false);
     }
 }

 /*private*/ void CarPrintOptionFrame::loadSortByComboBox(JComboBox* box) {
     for (int i = pcr->panel->carsTableModel->SORTBY_NUMBER; i <= pcr->panel->carsTableModel->SORTBY_LAST; i++) {
         box->addItem(pcr->panel->carsTableModel->getSortByName(i));
     }
     box->setCurrentIndex(box->findText(pcr->panel->carsTableModel->getSortByName()));
 }

 /*public*/ void CarPrintOptionFrame::buttonActionPerformed(QWidget* ae) {
     setVisible(false);
     pcr->printCars();
 }

 /*public*/ void CarPrintOptionFrame::comboBoxActionPerformed(QWidget* ae) {
     if (pcr->sortByComboBox->currentText() != NULL && pcr->sortByComboBox->currentText()==(pcr->panel->carsTableModel->getSortByName(pcr->panel->carsTableModel->SORTBY_LOCATION))) {
         printSpace->setEnabled(true);
         printPage->setEnabled(true);
     } else {
         printSpace->setEnabled(false);
         printPage->setEnabled(false);
         printSpace->setChecked(false);
         printPage->setChecked(false);
     }
 }

 /*public*/ QString CarPrintOptionFrame::getClassName()
 {
  return "jmri.jmrit.operations.rollingstock.cars.tools.CarPrintOptionFrame";
 }

}
