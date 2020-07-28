#include "trainstablesetcolorframe.h"
#include "control.h"
#include <QBoxLayout>
#include "gridbaglayout.h"
#include "jcombobox.h"
#include "trainmanager.h"
#include "train.h"
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QGroupBox>
#include "vptr.h"
#include "flowlayout.h"
#include "operationsxml.h"
#include "setup.h"
namespace Operations
{
 /**
  * Frame for setting up the Trains table colors in operations.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2014
  * @version $Revision: 17977 $
  */
 ///*public*/ class TrainsTableSetColorFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = -7242293868179247080L;



 /*public*/ TrainsTableSetColorFrame::TrainsTableSetColorFrame(Train* train, QWidget* parent)
    : OperationsFrame(parent)
 {
 trainManager = TrainManager::instance();

 // labels
 // text field
 // radio buttons
 manualRadioButton = new QRadioButton(tr("Manual"));
 autoRadioButton = new QRadioButton(tr("Auto"));

 // major buttons
 saveButton = new QPushButton(tr("Save"));

 // combo boxes
 trainBox = TrainManager::instance()->getTrainComboBox();
 colorBox = TrainManager::instance()->getRowColorComboBox();

 colorBuiltBox = TrainManager::instance()->getRowColorComboBox();
 colorBuildFailedBox = TrainManager::instance()->getRowColorComboBox();
 colorTrainEnRouteBox = TrainManager::instance()->getRowColorComboBox();
 colorTerminatedBox = TrainManager::instance()->getRowColorComboBox();

     // general GUI config

     //getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
// Layout the panel by rows
QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
     // row 1
     QGroupBox* pOption = new QGroupBox();
     pOption->setLayout(new GridBagLayout());
     //pOption->setBorder(BorderFactory.createTitledBorder(tr("Option")));
     pOption->setStyleSheet(gbStyleSheet);
     pOption->setTitle(tr("Option"));
     addItem(pOption, manualRadioButton, 0, 0);
     addItem(pOption, autoRadioButton, 1, 0);

     QButtonGroup* bGroup = new QButtonGroup();
     bGroup->addButton(manualRadioButton);
     bGroup->addButton(autoRadioButton);

     manualRadioButton->setChecked(trainManager->isRowColorManual());
     autoRadioButton->setChecked(!trainManager->isRowColorManual());

     pTrains = new QGroupBox();
     pTrains->setLayout(new GridBagLayout());
     //pTrains->setBorder(BorderFactory.createTitledBorder(tr("Train")));
     pTrains->setStyleSheet(gbStyleSheet);
     pTrains->setTitle(tr("Train"));
     addItem(pTrains, trainBox, 0, 0);

     trainBox->setCurrentIndex(trainBox->findData(VPtr<Train>::asQVariant(train)));

     pColor = new QGroupBox();
     pColor->setLayout(new GridBagLayout());
     //pColor->setBorder(BorderFactory.createTitledBorder(tr("SelectRowColor")));
     pColor->setStyleSheet(gbStyleSheet);
     pColor->setTitle(tr("Select Row Color"));
     addItem(pColor, colorBox, 0, 0);

     pColorBuilt = new QGroupBox();
     pColorBuilt->setLayout(new GridBagLayout());
     //pColorBuilt->setBorder(BorderFactory.createTitledBorder(tr("SelectRowColorBuilt")));
     pColorBuilt->setStyleSheet(gbStyleSheet);
     pColorBuilt->setTitle(tr("Select Row Color Train Built"));
     addItem(pColorBuilt, colorBuiltBox, 0, 0);

     colorBuiltBox->setCurrentIndex(colorBuiltBox->findText(trainManager->getRowColorNameForBuilt()));

     pColorBuildFailed = new QGroupBox();
     pColorBuildFailed->setLayout(new GridBagLayout());
     //pColorBuildFailed->setBorder(BorderFactory.createTitledBorder(tr("SelectRowColorBuildFailed")));
     pColorBuildFailed->setStyleSheet(gbStyleSheet);
     pColorBuildFailed->setTitle(tr("Select Row Color Train Build Failed"));
     addItem(pColorBuildFailed, colorBuildFailedBox, 0, 0);

     colorBuildFailedBox->setCurrentIndex(colorBuildFailedBox->findText(trainManager->getRowColorNameForBuildFailed()));

     pColorTrainEnRoute = new QGroupBox();
     pColorTrainEnRoute->setLayout(new GridBagLayout());
     //pColorTrainEnRoute->setBorder(BorderFactory.createTitledBorder(tr("SelectRowColorTrainEnRoute")));
     pColorTrainEnRoute->setStyleSheet(gbStyleSheet);
     pColorTrainEnRoute->setTitle(tr("Select Row Color Train En Route"));
     addItem(pColorTrainEnRoute, colorTrainEnRouteBox, 0, 0);

     colorTrainEnRouteBox->setCurrentIndex(colorTrainEnRouteBox->findText(trainManager->getRowColorNameForTrainEnRoute()));

     // row 5
     pColorTerminated = new QGroupBox();
     pColorTerminated->setLayout(new GridBagLayout());
     //pColorTerminated->setBorder(BorderFactory.createTitledBorder(tr("SelectRowColorTerminated")));
     pColorTerminated->setStyleSheet(gbStyleSheet);
     pColorTerminated->setTitle(tr("SelectRowColorTerminated"));
     addItem(pColorTerminated, colorTerminatedBox, 0, 0);

     colorTerminatedBox->setCurrentIndex(colorTerminatedBox->findText(trainManager->getRowColorNameForTerminated()));

     // row 4
     QWidget* pButton = new QWidget();
     pButton->setLayout(new FlowLayout);
     pButton->layout()->addWidget(saveButton);

     thisLayout->addWidget(pOption);
     thisLayout->addWidget(pTrains);
     thisLayout->addWidget(pColor);
     thisLayout->addWidget(pColorBuilt);
     thisLayout->addWidget(pColorBuildFailed);
     thisLayout->addWidget(pColorTrainEnRoute);
     thisLayout->addWidget(pColorTerminated);
     thisLayout->addWidget(pButton);

     // add help menu to window
     addHelpMenu("package.jmri.jmrit.operations.Operations_TrainsTableColors", true); // NOI18N

     adjustSize();
     setMinimumSize(QSize(Control::panelWidth400, Control::panelHeight400));

     setTitle(tr("Set Train Color"));

     // setup buttons
     addButtonAction(saveButton);
     addRadioButtonAction(manualRadioButton);
     addRadioButtonAction(autoRadioButton);

     makePanelsVisible();

     //trainManager->addPropertyChangeListener(this);
     connect(trainManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

 /*public*/ void TrainsTableSetColorFrame::buttonActionPerformed(QWidget* ae) {
 QPushButton* source = (QPushButton*)ae;
     if (source == saveButton) {
         // save option manual or auto
         trainManager->setRowColorsManual(manualRadioButton->isChecked());
         if (manualRadioButton->isChecked()) {
             Train* train = (Train*) VPtr<Train>::asPtr(trainBox->currentData());
             QString colorName =  colorBox->currentText();
             if (train != NULL) {
                 train->setTableRowColorName(colorName);
             }
         } else {
             trainManager->setRowColorNameForBuildFailed( colorBuildFailedBox->currentText());
             trainManager->setRowColorNameForBuilt( colorBuiltBox->currentText());
             trainManager->setRowColorNameForTrainEnRoute( colorTrainEnRouteBox->currentText());
             trainManager->setRowColorNameForTerminated( colorTerminatedBox->currentText());
         }
         // save train file
         OperationsXml::save();
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
         return;
     }
 }

 /*public*/ void TrainsTableSetColorFrame::radioButtonActionPerformed(QWidget* ae) {
     makePanelsVisible();
 }

 /**
  * If manual selected, show only trains and colors available. If auto, show
  * only the three automatic options; color for train built, build failed,
  * and terminated.
  */
 /*private*/ void TrainsTableSetColorFrame::makePanelsVisible()
 {
     pTrains->setVisible(manualRadioButton->isChecked());
     pColor->setVisible(manualRadioButton->isChecked());
     // the inverse
     pColorBuildFailed->setVisible(!manualRadioButton->isChecked());
     pColorBuilt->setVisible(!manualRadioButton->isChecked());
     pColorTrainEnRoute->setVisible(!manualRadioButton->isChecked());
     pColorTerminated->setVisible(!manualRadioButton->isChecked());
 }

 /*public*/ void TrainsTableSetColorFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(TrainManager::LISTLENGTH_CHANGED_PROPERTY)) {
         trainManager->updateTrainComboBox(trainBox);
     }
 }

 /*public*/ void TrainsTableSetColorFrame::dispose() {
     //trainManager->removePropertyChangeListener(this);
 disconnect(trainManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     OperationsFrame::dispose();
 }
/*public*/ QString TrainsTableSetColorFrame::getClassName()
{
 return "jmri.jmrit.operations.trains.tools.TrainsTableSetColorFrame";
}

}
