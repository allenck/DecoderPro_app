#include "printmoreoptionpanel.h"
#include "control.h"
#include <QBoxLayout>
#include "gridbaglayout.h"
#include <jtextfield.h>
#include <QPushButton>
#include <QGroupBox>
#include "setup.h"
#include "operationssetupxml.h"
#include "trainmanager.h"
#include <QIntValidator>

namespace Operations
{
 /**
  * Frame for user edit of additional manifest print options
  *
  * @author Dan Boudreau Copyright (C) 2012
  * @version $Revision: 21846 $
  */
 ///*public*/ class PrintMoreOptionPanel extends OperationsPreferencesPanel {

 /**
  *
  */
 //private static final long serialVersionUID = -5124421051550630914L;
 //private static final Logger log = LoggerFactory.getLogger(OperationsSetupFrame.class);

 /*public*/ PrintMoreOptionPanel::PrintMoreOptionPanel(QWidget* parent)
     : OperationsPanel(parent)
 {
  tab1TextField= new JTextField(2);
  tab1TextField->setValidator(new QIntValidator(1,9));
  tab2TextField= new JTextField(2);
  tab2TextField->setValidator(new QIntValidator(1,9));
  tab3TextField= new JTextField(2);
  tab3TextField->setValidator(new QIntValidator(1,9));

     // the following code sets the frame's initial state
     setLayout(new QVBoxLayout);//(this, BoxLayout.Y_AXIS));

     // row 1 font type and size
     QWidget* p1 = new QWidget();
     p1->setLayout(new QVBoxLayout);//(p1, BoxLayout.Y_AXIS));

     QGroupBox* pTab = new QGroupBox();
     pTab->setLayout(new QHBoxLayout);
    // pTab.setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutTab1")));
     pTab->setStyleSheet(gbStyleSheet);
     pTab->setTitle(tr("Tab Length"));
     pTab->layout()->addWidget(tab1TextField);
     p1->layout()->addWidget(pTab);

     QGroupBox* pTab2 = new QGroupBox();
     pTab2->setLayout(new QHBoxLayout);
     //pTab2.setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutTab2")));
     pTab2->setStyleSheet(gbStyleSheet);
     pTab2->setTitle(tr("Tab 2 Length"));
     pTab2->layout()->addWidget(tab2TextField);
     p1->layout()->addWidget(pTab2);

     QGroupBox* pTab3 = new QGroupBox();
     pTab3->setLayout(new QHBoxLayout);
    // pTab3.setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutTab3")));
     pTab3->setStyleSheet(gbStyleSheet);
     pTab3->setTitle(tr("Tab 3 Length"));
     pTab3->layout()->addWidget(tab3TextField);
     p1->layout()->addWidget(pTab3);

     tab1TextField->setText(QString::number(Setup::getTab1Length()));
     tab2TextField->setText(QString::number(Setup::getTab2Length()));
     tab3TextField->setText(QString::number(Setup::getTab3Length()));

     // add tool tips
     saveButton->setToolTip(tr("Writes this window's settings to file"));

     // row 11
     QGroupBox* pControl = new QGroupBox();
     //pControl.setBorder(BorderFactory.createTitledBorder(""));
     pControl->setStyleSheet(gbStyleSheet);
     //pControl->setTitle(tr("Tab Length"));
     pControl->setLayout(new GridBagLayout());
     addItem(pControl, saveButton, 0, 0);

     layout()->addWidget(p1);
     layout()->addWidget(pControl);

     // setup buttons
     addButtonAction(saveButton);

     initMinimumSize(QSize(Control::panelWidth300, Control::panelHeight400));
 }

 // Save buttons
 //@Override
 /*public*/ void PrintMoreOptionPanel::buttonActionPerformed(QWidget* ae) {
 QPushButton* source = (QPushButton*)ae;
     if (source == saveButton)
     {
         this->savePreferences();
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
 }

 //@Override
 /*public*/ QString PrintMoreOptionPanel::getTabbedPreferencesTitle() {
     return tr("Print More Options");
 }

 //@Override
 /*public*/ QString PrintMoreOptionPanel::getPreferencesTooltip() {
     return NULL;
 }

 //@Override
 /*public*/ void PrintMoreOptionPanel::savePreferences() {

     //try {
         Setup::setTab1length(tab1TextField->text().toInt());
         Setup::setTab2length(tab2TextField->text().toInt());
         Setup::setTab3length(tab3TextField->text().toInt());
//     } catch (Exception e) {
//         log.error("Tab wasn't a number");
//     }

     OperationsSetupXml::instance()->writeOperationsFile();

     // recreate all train manifests
     TrainManager::instance()->setTrainsModified();
 }

 //@Override
 /*public*/ bool PrintMoreOptionPanel::isDirty() {
     //try {
         return (Setup::getTab1Length() != tab1TextField->text().toInt()
                 || Setup::getTab2Length() != tab2TextField->text().toInt()
                 || Setup::getTab3Length() != tab3TextField->text().toInt());
//     } catch (Exception e) {
//         log->error("Tab wasn't a number");
//     }
     return true;
 }
}
