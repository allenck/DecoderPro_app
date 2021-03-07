#include "rollingstockeditframe.h"
#include "loggerfactory.h"
#include "operationsxml.h"
#include "joptionpane.h"
#include "engine.h"
#include "cartypes.h"
#include "enginetypes.h"
#include "locationmanager.h"
#include "vptr.h"
#include "rollingstock.h"
#include "location.h"
#include "gridbaglayout.h"
#include "borderfactory.h"
#include <QScrollArea>
#include "setup.h"
#include "control.h"
#include "track.h"
#include "resourcebundle.h"

namespace Operations
{
 /**
  * Frame for edit of rolling stock. The common elements are: road, road number,
  * type, blocking, length, location and track, groups (Kernel or Consist)
  * weight, color, built, owner, comment.
  *
  * The edit engine frame currently doesn't show blocking or color.
  *
  * Engines and cars have different type, length, and group managers->
  *
  * @author Dan Boudreau Copyright (C) 2018
  */
 ///*public*/ abstract class RollingStockEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

     /*protected*/ /*static*/ /*final*/ bool RollingStockEditFrame::IS_SAVE = true;


     /*public*/ RollingStockEditFrame::RollingStockEditFrame(QString title, QObject* parent)
  : OperationsFrame(title) {
         //super(title);
         // InstanceManager = InstanceManger.getInstance();
     }

//     abstract /*protected*/ RollingStockAttribute getTypeManager();

//     abstract /*protected*/ RollingStockAttribute getLengthManager();

//     abstract /*protected*/ void buttonEditActionPerformed(java.awt.event.ActionEvent ae);

//     abstract /*protected*/ ResourceBundle getRb();

//     abstract /*protected*/ void save(boolean isSave);

//     abstract /*protected*/ void delete();

     //@SuppressFBWarnings(value = "NP_NULL_ON_SOME_PATH_FROM_RETURN_VALUE", justification = "Checks for null")
     //@Override
     /*public*/ void RollingStockEditFrame::initComponents() {
      typeComboBox = getTypeManager()->getComboBox();
      lengthComboBox= getLengthManager()->getComboBox();

         // disable delete and save buttons
         deleteButton->setEnabled(false);
         saveButton->setEnabled(false);

         editRoadButton->setToolTip(tr("Add, delete or replace %1 names").arg(
                  tr("road") )); // initial caps for some languages i.e. German
         editTypeButton->setToolTip(tr("TipAddDeleteReplace").arg(
                 tr("type") )); // initial caps for some languages i.e. German
         editLengthButton->setToolTip(tr("Add, delete or replace %1 names").arg(
                 tr("length") )); // initial caps for some languages i.e. German
         editOwnerButton->setToolTip(tr("Add, delete or replace %1 names").arg(
                 tr("Owner").toLower() ));

         autoTrackCheckBox->setToolTip(tr("NOT USED! Only here to eliminate warnings from i18n consistency check"));

         // create panel
         JPanel* pPanel = new JPanel();
         pPanel->setLayout(new QVBoxLayout());//pPanel, BoxLayout.Y_AXIS));

         // Layout the panel by rows
         // row 1
         JPanel* pRoad = new JPanel();
         pRoad->setLayout(new GridBagLayout());
         pRoad->setBorder(BorderFactory::createTitledBorder(tr("Road")));
         addItem(pRoad, roadComboBox, 1, 0);
         addItem(pRoad, editRoadButton, 2, 0);
         pPanel->layout()->addWidget(pRoad);

         // row 2
         JPanel* pRoadNumber = new JPanel();
         pRoadNumber->setLayout(new GridBagLayout());
         pRoadNumber->setBorder(BorderFactory::createTitledBorder(tr("Road Number")));
         addItem(pRoadNumber, roadNumberTextField, 1, 0);
         addItem(pRoadNumber, clearRoadNumberButton, 2, 0);
         pPanel->layout()->addWidget(pRoadNumber);

         // only engines have a model name
         pPanel->layout()->addWidget(pModel);
         pModel->setVisible(false);

         // row 3
         JPanel* pType = new JPanel();
         pType->setLayout(new GridBagLayout());
         pType->setBorder(BorderFactory::createTitledBorder(tr("Type")));
         addItem(pType, typeComboBox, 0, 0);
         addItem(pType, editTypeButton, 1, 0);

         // type options dependent on car or engine rolling stock
         addItemWidth(pType, pTypeOptions, 3, 0, 1);
         pPanel->layout()->addWidget(pType);

         // row 4
         pBlocking->setLayout(new GridBagLayout());
         pBlocking->setBorder(BorderFactory::createTitledBorder(tr("Blocking Order")));
         addItem(pBlocking, blockingTextField, 0, 0);
         blockingTextField->setText("0");
         pPanel->layout()->addWidget(pBlocking);
         pBlocking->setVisible(false); // default is blocking order not shown

         // row 5
         JPanel* pLength = new JPanel();
         pLength->setLayout(new GridBagLayout());
         pLength->setBorder(BorderFactory::createTitledBorder(tr("Length")));
         addItem(pLength, lengthComboBox, 1, 0);
         addItem(pLength, editLengthButton, 2, 0);
         pPanel->layout()->addWidget(pLength);

         // row 6
         JPanel* pLocation = new JPanel();
         pLocation->setLayout(new GridBagLayout());
         pLocation->setBorder(BorderFactory::createTitledBorder(tr("Location and Track")));
         addItem(pLocation, locationBox, 1, 0);
         addItem(pLocation, trackLocationBox, 2, 0);
         addItem(pLocation, autoTrackCheckBox, 3, 0);
         pPanel->layout()->addWidget(pLocation);

         // optional panel
         JPanel* pOptional = new JPanel();
         pOptional->setLayout(new QVBoxLayout());//pOptional, BoxLayout.Y_AXIS));
         QScrollArea* optionPane = new QScrollArea(/*pOptional*/);
         optionPane->setWidget(pOptional);
         optionPane->setWidgetResizable(true);

         JPanel* borderScrollArea = new JPanel(new QVBoxLayout());
         //optionPane->setBorder(BorderFactory::createTitledBorder(tr("Optional")));
         borderScrollArea->layout()->addWidget(optionPane);
         borderScrollArea->setBorder(BorderFactory::createTitledBorder(tr("Optional")));

         // row 7
         JPanel* pWeight = new JPanel();
         pWeight->setLayout(new QVBoxLayout());//pWeight, BoxLayout.Y_AXIS));
         pWeight->setBorder(BorderFactory::createTitledBorder(tr("Weight")));

         // weight in oz only shown for cars
         pWeight->layout()->addWidget(pWeightOz);

         JPanel* pWeightTons = new JPanel();
         pWeightTons->setLayout(new GridBagLayout());
         addItem(pWeightTons, textWeightTons, 0, 0);
         addItem(pWeightTons, weightTonsTextField, 1, 0);
         addItem(pWeightTons, new JLabel(), 2, 0);
         addItem(pWeightTons, new JLabel(), 3, 0);
         addItem(pWeightTons, new JLabel(), 4, 0);
         pWeight->layout()->addWidget(pWeightTons);
         pOptional->layout()->addWidget(pWeight);

         // row 8 for cars
         pOptional->layout()->addWidget(pColor);
         pColor->setVisible(false);

         // row 9 for cars
         pOptional->layout()->addWidget(pLoad);
         pLoad->setVisible(false);

         // for engines
         pOptional->layout()->addWidget(pHp);
         pHp->setVisible(false);

         // row 10
         pGroup->setLayout(new GridBagLayout());
         addItem(pGroup, groupComboBox, 1, 0);
         addItem(pGroup, editGroupButton, 2, 0);
         pOptional->layout()->addWidget(pGroup);

         // row 11
         JPanel* pBuilt = new JPanel();
         pBuilt->setLayout(new GridBagLayout());
         pBuilt->setBorder(BorderFactory::createTitledBorder(tr("Built")));
         addItem(pBuilt, builtTextField, 1, 0);
         pOptional->layout()->addWidget(pBuilt);

         // row 12
         JPanel* pOwner = new JPanel();
         pOwner->setLayout(new GridBagLayout());
         pOwner->setBorder(BorderFactory::createTitledBorder(tr("Owner")));
         addItem(pOwner, ownerComboBox, 1, 0);
         addItem(pOwner, editOwnerButton, 2, 0);
         pOptional->layout()->addWidget(pOwner);

         // row 13
         if (Setup::isValueEnabled()) {
             JPanel* pValue = new JPanel();
             pValue->setLayout(new GridBagLayout());
             pValue->setBorder(BorderFactory::createTitledBorder(Setup::getValueLabel()));
             addItem(pValue, /*valueScroller*/valueTextArea, 1, 0);
             pOptional->layout()->addWidget(pValue);

             // adjust text area width based on window size
             //adjustTextAreaColumnWidth(valueScroller, valueTextArea);
         }

         // row 14
         IdTagManager* tagManager = (IdTagManager*)InstanceManager::getNullableDefault("IdTagManager");
         if (Setup::isRfidEnabled() && tagManager != nullptr) {
             JPanel* pRfid = new JPanel();
             pRfid->setLayout(new GridBagLayout());
             pRfid->setBorder(BorderFactory::createTitledBorder(Setup::getRfidLabel()));
             rfidComboBox = new NamedBeanComboBox/*<IdTag>*/(tagManager);
             rfidComboBox->setAllowNull(true);
             rfidComboBox->setToolTip(tr("Select the Associated IDTag."));
             addItem(pRfid, rfidComboBox, 0, 0);
             addItem(pRfid, textRfidSystemName, 1, 0);
             pOptional->layout()->addWidget(pRfid);
         }

         // row 15
         JPanel* pComment = new JPanel();
         pComment->setLayout(new GridBagLayout());
         pComment->setBorder(BorderFactory::createTitledBorder(tr("Comment")));
         addItem(pComment, commentTextField, 1, 0);
         pOptional->layout()->addWidget(pComment);

         // button panel
         JPanel* pButtons = new JPanel();
         pButtons->setLayout(new GridBagLayout());
         addItem(pButtons, deleteButton, 0, 25);
         addItem(pButtons, addButton, 1, 25);
         addItem(pButtons, saveButton, 3, 25);

         // add panels
         getContentPane()->setLayout(new QVBoxLayout());//getContentPane(), BoxLayout.Y_AXIS));
         getContentPane()->layout()->addWidget(pPanel);
         getContentPane()->layout()->addWidget(/*optionPane*/borderScrollArea);
         getContentPane()->layout()->addWidget(pButtons);

         // setup buttons
         addEditButtonAction(editRoadButton);
         addEditButtonAction(editTypeButton);
         addEditButtonAction(editLengthButton);
         addEditButtonAction(editGroupButton);
         addEditButtonAction(editOwnerButton);

         addButtonAction(clearRoadNumberButton);
         addButtonAction(deleteButton);
         addButtonAction(addButton);
         addButtonAction(saveButton);

         // setup combobox
         addComboBoxAction(typeComboBox);
         addComboBoxAction(lengthComboBox);
         addComboBoxAction(locationBox);

         addCheckBoxAction(autoTrackCheckBox);
         autoTrackCheckBox->setEnabled(false);

         // get notified if combo box gets modified
         addPropertyChangeListeners();

         initMinimumSize(QSize(Control::panelWidth500, Control::panelHeight500));
     }

     /*protected*/ void RollingStockEditFrame::load(RollingStock* rs) {
         _rs = rs;

         // engines and cars share the same road database
         if (!((CarRoads*)InstanceManager::getDefault("CarRoads"))->containsName(rs->getRoadName())) {
             if (JOptionPane::showConfirmDialog(this,
                     tr("Road name \"%1\" does not exist in your roster, add?").arg(rs->getRoadName() ),
                     tr("Add road name?"), JOptionPane::YES_NO_OPTION) == JOptionPane::YES_OPTION) {
                 ((CarRoads*)InstanceManager::getDefault("CarRoads"))->addName(rs->getRoadName());
             }
         }
         roadComboBox->setSelectedItem(rs->getRoadName());

         roadNumberTextField->setText(rs->getNumber());

         if (!getTypeManager()->containsName(rs->getTypeName())) {
             if (JOptionPane::showConfirmDialog(this,
                     tr("Type \"%1\" does not exist in your roster, add?").arg(rs->getTypeName() ),
                     tr("Add Type?"), JOptionPane::YES_NO_OPTION) == JOptionPane::YES_OPTION) {
                 getTypeManager()->addName(rs->getTypeName());
             }
         }
         typeComboBox->setSelectedItem(rs->getTypeName());
         blockingTextField->setText(QString::number(rs->getBlocking()));

         if (!getLengthManager()->containsName(rs->getLength())) {
             if (JOptionPane::showConfirmDialog(this,
                     tr("Length \"%1\" does not exist in your roster, add?").arg(rs->getLength() ),
                     tr("Add Length?"), JOptionPane::YES_NO_OPTION) == JOptionPane::YES_OPTION) {
                 getLengthManager()->addName(rs->getLength());
             }
         }
         // }
         lengthComboBox->setSelectedItem(rs->getLength());

         weightTextField->setText(rs->getWeight());
         weightTonsTextField->setText(rs->getWeightTons());
         locationBox->setSelectedItem(rs->getLocation()->getName());
         updateTrackLocationBox();

         builtTextField->setText(rs->getBuilt());

         // Engines and cars share the owner database
         if (!((CarOwners*)InstanceManager::getDefault("CarOwners"))->containsName(rs->getOwner())) {
             if (JOptionPane::showConfirmDialog(this,
                     tr("Owner \"%1\" does not exist in your roster, add?").arg(rs->getOwner() ),
                     tr("Add Owner?"), JOptionPane::YES_NO_OPTION) == JOptionPane::YES_OPTION) {
                 ((CarOwners*)InstanceManager::getDefault("CarOwners"))->addName(rs->getOwner());
             }
         }
         ownerComboBox->setSelectedItem(rs->getOwner());

         commentTextField->setText(rs->getComment());
         valueTextArea->setText(rs->getValue());
         if (rfidComboBox != nullptr) {
             rfidComboBox->setSelectedItem(rs->getIdTag());
             textRfidSystemName->setText(rs->getRfid());
         }
         // enable delete and save buttons
         deleteButton->setEnabled(true);
         saveButton->setEnabled(true);
         autoTrackCheckBox->setEnabled(true);
     }

     //@Override
     /*public*/ void RollingStockEditFrame::comboBoxActionPerformed(QWidget* ae) {
         if (ae == typeComboBox && typeComboBox->getSelectedItem() != "") {
             // turn off auto for location tracks
             autoTrackCheckBox->setChecked(false);
             autoTrackCheckBox->setEnabled(false);
             updateTrackLocationBox();
         }
         if (ae == locationBox) {
             updateTrackLocationBox();
         }
     }

     //@Override
     /*public*/ void RollingStockEditFrame::checkBoxActionPerformed(QWidget* ae) {
         if (ae == autoTrackCheckBox) {
             updateTrackLocationBox();
         }
     }

     // Save, Delete, Add, Clear, Calculate, Edit Load buttons
     //@Override
     /*public*/ void RollingStockEditFrame::buttonActionPerformed(QWidget* ae) {
         if (ae == saveButton) {
             // log.debug("car save button pressed");
             if (!check(_rs)) {
                 return;
             }
             save(IS_SAVE);
             // save car file
             OperationsXml::save();
             if (Setup::isCloseWindowOnSaveEnabled()) {
                 dispose();
             }
         }
         if (ae== addButton) {
             if (!check(nullptr)) {
                 return;
             }

             // enable delete and save buttons
             deleteButton->setEnabled(true);
             saveButton->setEnabled(true);

             save(!IS_SAVE);
             // save car file
             OperationsXml::save();
         }
         if (ae == deleteButton) {
             log->debug("car delete button activated");
             // disable delete and save buttons
             deleteButton->setEnabled(false);
             saveButton->setEnabled(false);
             if (_rs != nullptr) {
                 _rs->removePropertyChangeListener(this);
             }
             _delete();
             _rs = nullptr;
             OperationsXml::save();
         }
         if (ae == clearRoadNumberButton) {
             roadNumberTextField->setText("");
             roadNumberTextField->requestFocus();
         }
     }

     /*protected*/ void RollingStockEditFrame::updateTrackLocationBox()
     {
      if (locationBox->getSelectedItem() == "") {
          trackLocationBox->clear();
      }
      else {
       log->debug(tr("Update tracks for location: %1").arg(locationBox->getSelectedItem()));
       Location* loc;
       QVariant v = locationBox->currentData();
       if(v.isValid())
        loc = (/*(Location)*/ VPtr<Location>::asPtr(locationBox->currentData()));
       else
        loc = locationManager->getLocationByName(locationBox->currentText());
       loc->updateComboBox(trackLocationBox, _rs, autoTrackCheckBox->isChecked(), false);
       if (_rs != nullptr && _rs->getLocation() == loc) {
           //trackLocationBox->setSelectedItem(_rs->getTrack());
        trackLocationBox->setCurrentText(_rs->getTrack()->getName());
       }
      }
     }

     /*protected*/ bool RollingStockEditFrame::check(RollingStock* rs) {
         QString roadNum = roadNumberTextField->text();
         if (!OperationsXml::checkFileName(roadNum)) { // NOI18N
             JOptionPane::showMessageDialog(this,
                     tr("Name must not contain reserved characters") +"\n" + tr(". < > : \" / \\ | ? *"),
                     tr("Can't use road number!"), JOptionPane::ERROR_MESSAGE);
             return false;
         }
         if (roadNum.length() > Control::max_len_string_road_number) {
          JOptionPane::showMessageDialog(this,
                  getRb()->getString("RoadNumMustBeLess").arg( Control::max_len_string_road_number + 1 ),
                  getRb()->getString("RoadNumTooLong"), JOptionPane::ERROR_MESSAGE);
             return false;
         }
         // check rolling stock's weight in tons has proper format
         if (!weightTonsTextField ->text().trimmed().isEmpty()) {
             bool ok;
                 weightTonsTextField ->text().toUInt(&ok);
             if(!ok) {
              JOptionPane::showMessageDialog(this, getRb()->getString("WeightFormatTon"),
                      getRb()->getString("WeightTonError"), JOptionPane::ERROR_MESSAGE);
              return false;
                 return false;
             }
         }
         return true;
     }

     /*protected*/ /*<T extends RollingStock> */void RollingStockEditFrame::save(RollingStockManager/*<T>*/* manager, bool isSave) {
         // if the rolling stock's road or number changes, it needs a new id
         if (isSave &&
                 _rs != nullptr &&
                 (_rs->getRoadName() != (roadComboBox->getSelectedItem()) ||
                         _rs->getNumber() != (roadNumberTextField->text()))) {
             QString road = /*(String)*/ roadComboBox->getSelectedItem();
             QString number = roadNumberTextField->text();
             _rs->setRoadName(road);
             _rs->setNumber(number);
         }
         if (_rs == nullptr ||
                 _rs->getRoadName() != (roadComboBox->getSelectedItem()) ||
                 _rs->getNumber() != (roadNumberTextField->text())) {
             _rs = manager->newRS(/*(String)*/ roadComboBox->getSelectedItem(), roadNumberTextField ->text());
             _rs->addPropertyChangeListener(this);
         }
         // engine model must be set before type, length, weight and HP
         if (qobject_cast<Engine*>(_rs) && modelComboBox->getSelectedItem() != nullptr) {
             ((Engine*) _rs)->setModel(/*(String)*/ modelComboBox->getSelectedItem());
         }
         if (typeComboBox->getSelectedItem() != "") {
             _rs->setTypeName(/*(String)*/ typeComboBox->getSelectedItem());
         }

         int blocking = 0;
         bool ok;
             blocking = blockingTextField ->text().toInt(&ok);
             // only allow numbers between 0 and 100
             if (blocking < 0 || blocking > 100) {
                 blocking = 0;
             }
         if(!ok) {
             log->warn("Blocking must be a number between 0 and 100");
         }
         blockingTextField->setText(QString::number(blocking));

         if (lengthComboBox->getSelectedItem() != "") {
             _rs->setLength(/*(String)*/ lengthComboBox->getSelectedItem());
         }
         try {
//             _rs->setWeight(NumberFormat.getNumberInstance().parse(weightTextField ->text()).toString());
          _rs->setWeight(weightTextField ->text());
         } catch (ParseException e1) {
             log->debug("Weight not a number");
         }
         _rs->setWeightTons(weightTonsTextField ->text());
         _rs->setBuilt(builtTextField ->text());
         if (ownerComboBox->getSelectedItem() != "") {
             _rs->setOwner(/*(String)*/ ownerComboBox->getSelectedItem());
         }
         _rs->setComment(commentTextField ->text());
         _rs->setValue(valueTextArea ->toPlainText());
         if (rfidComboBox != nullptr) {
             // save the IdTag for this rolling stock
             _rs->setIdTag(VPtr<DefaultIdTag>::asPtr(rfidComboBox->currentData()));
             textRfidSystemName->setText(_rs->getRfid());
         }
         autoTrackCheckBox->setEnabled(true);

         if (locationBox->getSelectedItem() != "" && trackLocationBox->getSelectedItem() == "") {
             JOptionPane::showMessageDialog(this, tr("To place a car, you must select the car's location and track"), tr("Can not update car location"),
                     JOptionPane::ERROR_MESSAGE);
             // update location only if it has changed
         } else if (_rs->getLocation() == nullptr ||
                 _rs->getLocation() != (VPtr<Location>::asPtr(locationBox->currentData())) ||
                 _rs->getTrack() == nullptr ||
                 _rs->getTrack() != (VPtr<Track>::asPtr(trackLocationBox->currentData()))) {
             setLocationAndTrack(_rs);
         }
     }

     /*protected*/ void RollingStockEditFrame::setLocationAndTrack(RollingStock* rs) {
         if (locationBox->getSelectedItem() == "") {
             rs->setLocation(nullptr, nullptr);
         } else {
             rs->setLastRouteId(RollingStock::NONE); // clear last route id
             QString status = rs->setLocation(VPtr<Location>::asPtr(locationBox->currentData()),
                    VPtr<Track>::asPtr(trackLocationBox->currentData()));
             if (status != (Track::OKAY)) {
                 log->debug(tr("Can't set rolling stock's location because of %1").arg(status));
                 JOptionPane::showMessageDialog(this,
                         tr("Can''t set car (%1) location and track due to %2").arg(
                                rs->toString()).arg(status ),
                         tr("Can not update car location"), JOptionPane::ERROR_MESSAGE);
                 // does the user want to force the rolling stock to this track?
                 int results = JOptionPane::showOptionDialog(this,
                         tr("Do you want to force car (%1) to track (%2)?").arg(rs->toString()).arg(/*(Track)*/ trackLocationBox->getSelectedItem() ),
                         tr("Do you want to override track''s %1?").arg(status ),
                         JOptionPane::YES_NO_OPTION, JOptionPane::QUESTION_MESSAGE, QIcon(), QVariantList(), QVariant());
                 if (results == JOptionPane::YES_OPTION) {
                     log->debug("Force rolling stock to track");
                     rs->setLocation(VPtr<Location>::asPtr(locationBox->currentData()), VPtr<Track>::asPtr(trackLocationBox->currentData()),
                             RollingStock::FORCE);
                 }
             }
         }
     }

     // for the AttributeEditFrame edit buttons
     /*protected*/ void RollingStockEditFrame::addEditButtonAction(JButton* b) {
        // b.addActionListener(new java.awt.event.ActionListener() {
        connect(b, &JButton::clicked, [=]{

             //@Override
//             /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
                 buttonEditActionPerformed(nullptr);
//             }
         });
     }

     //@Override
     /*public*/ void RollingStockEditFrame::dispose() {
         removePropertyChangeListeners();
         OperationsFrame::dispose();
     }

     /*protected*/ void RollingStockEditFrame::addPropertyChangeListeners() {
         ((CarRoads*)InstanceManager::getDefault("CarRoads"))->addPropertyChangeListener(this);
         getTypeManager()->addPropertyChangeListener(this);
         getLengthManager()->addPropertyChangeListener(this);
         ((CarOwners*)InstanceManager::getDefault("CarOwners"))->addPropertyChangeListener(this);
         locationManager->addPropertyChangeListener(this);
     }

     /*protected*/ void RollingStockEditFrame::removePropertyChangeListeners() {
         ((CarRoads*)InstanceManager::getDefault("CarRoads"))->removePropertyChangeListener(this);
         getTypeManager()->removePropertyChangeListener(this);
         getLengthManager()->removePropertyChangeListener(this);
         ((CarOwners*)InstanceManager::getDefault("CarOwners"))->removePropertyChangeListener(this);
         locationManager->removePropertyChangeListener(this);
     }

     //@Override
     /*public*/ void RollingStockEditFrame::propertyChange(PropertyChangeEvent* e) {
         if (e->getPropertyName() == (CarRoads::CARROADS_CHANGED_PROPERTY)) {
             ((CarRoads*)InstanceManager::getDefault("CarRoads"))->updateComboBox(roadComboBox);
             if (_rs != nullptr) {
                 roadComboBox->setSelectedItem(_rs->getRoadName());
             }
         }
         if (e->getPropertyName() == (CarTypes::CARTYPES_CHANGED_PROPERTY) ||
                 e->getPropertyName() == (EngineTypes::ENGINETYPES_CHANGED_PROPERTY)) {
             getTypeManager()->updateComboBox(typeComboBox);
             if (_rs != nullptr) {
                 typeComboBox->setSelectedItem(_rs->getTypeName());
             }
         }
         if (e->getPropertyName() == (CarOwners::CAROWNERS_CHANGED_PROPERTY)) {
             ((CarOwners*)InstanceManager::getDefault("CarOwners"))->updateComboBox(ownerComboBox);
             if (_rs != nullptr) {
                 ownerComboBox->setSelectedItem(_rs->getOwner());
             }
         }
         if (e->getPropertyName() == (LocationManager::LISTLENGTH_CHANGED_PROPERTY) ||
                 e->getPropertyName() == (RollingStock::TRACK_CHANGED_PROPERTY)) {
             ((LocationManager*)InstanceManager::getDefault("LocationManager"))->updateComboBox(locationBox);
             updateTrackLocationBox();
             if (_rs != nullptr && _rs->getLocation() != nullptr) {
                 locationBox->setSelectedItem(_rs->getLocation()->getName());
             }
         }
     }

    /*private*/ /*final*/ /*static*/ Logger* RollingStockEditFrame::log = LoggerFactory::getLogger("RollingStockEditFrame");
}
