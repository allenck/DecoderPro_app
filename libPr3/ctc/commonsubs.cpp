#include "commonsubs.h"
#include "loggerfactory.h"
#include "joptionpane.h"
#include "jtextfield.h"
#include "jframe.h"
#include "helputil.h"
#include "defaulttablemodel.h"
#include "codebuttonhandlerdata.h"
#include "ctcmanager.h"
#include "instancemanager.h"
#include "sensormanager.h"
#include "sensor.h"
#include "signalheadmanager.h"
#include "signalhead.h"
#include "signalmastmanager.h"
#include "signalmast.h"
#include <QMenuBar>
#include "ctcserialdata.h"
#include "blockmanager.h"
#include "block.h"

CommonSubs::CommonSubs(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
// /*public*/ class CommonSubs {

//  For GUI editor routines that need this:
    /*public*/ /*static*/ void CommonSubs::setMillisecondsEdit(JFormattedTextField* formattedTextField) {

#if 0
     NumberFormatter numberFormatter = (NumberFormatter) formattedTextField.getFormatter();
        numberFormatter.setMinimum(0);
        numberFormatter.setMaximum(120000);
        numberFormatter.setAllowsInvalid(false);
#endif
    }

//  This routine will return 0 if error encountered parsing string.  Since all GUI int fields that use this
//  routine already should have a NumberFormatter attached to it already (see "setMillisecondsEdit" above),
//  technically these should NEVER throw!
    /*public*/ /*static*/ int CommonSubs::getIntFromJTextFieldNoThrow(JTextField* textField) { return ProjectsCommonSubs::getIntFromStringNoThrow(textField->text(), 0); }

    /*public*/ /*static*/ bool CommonSubs::allowClose(JFrame* parentComponent, bool dataChanged) {
        if (dataChanged) {
            return JOptionPane::showConfirmDialog(parentComponent, tr("Data has been modified, do you really want to exit?"),
                    tr("Warning"), JOptionPane::YES_NO_OPTION) == JOptionPane::YES_OPTION;  // NOI18N
        }
        return true;    // NO change, ok to exit
    }

    /**
     * Add a standard help menu, including the window specific help item.
     *
     * @param frame  The frame receiving the help menu.
     * @param ref    JHelp reference for the desired window-specific help page
     * @param direct true if the help main-menu item goes directly to the help system,
     *               such as when there are no items in the help menu
     */
    /*public*/ /*static*/ void CommonSubs::addHelpMenu(JFrame* frame, QString ref, bool direct) {
        QMenuBar* bar = frame->menuBar();
        if (bar == nullptr) {
            bar = new QMenuBar();
        }
        HelpUtil::helpMenu(bar, ref, direct);
        frame->setMenuBar(bar);
    }

//  If the table model value is null, that is the same as "".  This also "compacts"
//  the entries also (i.e. blank line(s) between entries are removed):
    /*public*/ /*static*/ QString CommonSubs::getCSVStringFromDefaultTableModel(DefaultTableModel* defaultTableModel) {
        QList<QString> entries = QList<QString>();
        for (int sourceIndex = 0; sourceIndex < defaultTableModel->getRowCount(); sourceIndex++) {
            QVariant object = defaultTableModel->getValueAt(sourceIndex, 0);
            if (!object.isNull()) {
                QString entry = object.toString().trimmed();
                if (!entry.isEmpty()) { // Do a "compact" on the fly:
                    entries.append(entry);
                }
            }
        }
#if 0
        try (CSVPrinter printer = new CSVPrinter(new StringBuilder(), CSVFormat.DEFAULT.withQuote(null).withRecordSeparator(null))) {
            printer.printRecord(entries);
            return printer.getOut().toString();
        } catch (IOException ex) {
            log.error("Unable to create CSV", ex);
            return "";
        }
#endif
    }

//  If the table model value is null, that is the same as "".  This also "compacts"
//  the entries also (i.e. blank line(s) between entries are removed):
    /*public*/ /*static*/ QList<QString> CommonSubs::getStringArrayFromDefaultTableModel(DefaultTableModel* defaultTableModel) {
        QList<QString> entries = QList<QString>();
        for (int sourceIndex = 0; sourceIndex < defaultTableModel->getRowCount(); sourceIndex++) {
            QVariant object = defaultTableModel->getValueAt(sourceIndex, 0);
            if (!object.isNull()) {
                QString entry = object.toString().trimmed();
                if (!entry.isEmpty()) { // Do a "compact" on the fly:
                    entries.append(entry);
                }
            }
        }
        return entries;
    }

    /*public*/ /*static*/ int CommonSubs::compactDefaultTableModel(DefaultTableModel* defaultTableModel) {
        int destIndex = 0;
        int lastSourceIndexNonEmpty = -1;   // Indicate none found
        int count = 0;
        for (int sourceIndex = 0; sourceIndex < defaultTableModel->getRowCount(); sourceIndex++) {
            QVariant object = defaultTableModel->getValueAt(sourceIndex, 0);
            if (!object.isNull()) {
                QString entry = object.toString().trimmed();
                entry = entry.trimmed();
                if (!entry.isEmpty()) {
                    lastSourceIndexNonEmpty = sourceIndex;
                    defaultTableModel->setValueAt(entry, destIndex++, 0);
                    count++;
                }
            }
        }
        if (-1 != lastSourceIndexNonEmpty) { // Something in table, MAY need to clear out rows at end:
            while (destIndex <= lastSourceIndexNonEmpty) {
                defaultTableModel->setValueAt("", destIndex++, 0);
            }
        }
        return count; // Return number of entries encountered.
    }

//  This creates a sorted ArrayList (so that we can easily load it into a "DefaultComboBoxModel") containing all
//  Switch Direction Indicators:
    /*public*/ /*static*/ QList<QString> CommonSubs::getArrayListOfSelectableSwitchDirectionIndicators(QList<CodeButtonHandlerData*> codeButtonHandlerDataList) {
        QList<QString> returnValue = QList<QString>();
        for (CodeButtonHandlerData* codeButtonHandlerData : codeButtonHandlerDataList) {
            if (!codeButtonHandlerData->_mSWDI_NormalInternalSensor->getHandleName().isEmpty()) {
                returnValue.append(codeButtonHandlerData->_mSWDI_NormalInternalSensor->getHandleName());
            }
            if (!codeButtonHandlerData->_mSWDI_ReversedInternalSensor->getHandleName().isEmpty()) {
                returnValue.append(codeButtonHandlerData->_mSWDI_ReversedInternalSensor->getHandleName());
            }
        }
//      Collections.sort(returnValue);
        return returnValue;
    }

    /*public*/ /*static*/ QList<int> CommonSubs::getArrayListOfSelectableOSSectionUniqueIDs(QList<CodeButtonHandlerData*> codeButtonHandlerDataList) {
        QList<int> returnValue = QList<int>();
        for (CodeButtonHandlerData* codeButtonHandlerData : codeButtonHandlerDataList) {
            returnValue.append(codeButtonHandlerData->_mUniqueID);
        }
        return returnValue;
    }

    /*public*/ /*static*/ void CommonSubs::populateJComboBoxWithColumnDescriptionsAndSelectViaUniqueID(JComboBox/*<String>*/* jComboBox, CTCSerialData* ctcSerialData, int uniqueID) {
        populateJComboBoxWithColumnDescriptions(jComboBox, ctcSerialData);
        setSelectedIndexOfJComboBoxViaUniqueID(jComboBox, ctcSerialData, uniqueID);
    }

//  A blank entry will ALWAYS appear as the first selection.
    /*public*/ /*static*/ void CommonSubs::populateJComboBoxWithColumnDescriptions(JComboBox/*<String>*/* jComboBox, CTCSerialData* ctcSerialData) {
        QList<QString> userDescriptions = QList<QString>();
        userDescriptions.append("");   // None can be specified.
        QList<int> arrayListOfSelectableOSSectionUniqueIDs = getArrayListOfSelectableOSSectionUniqueIDs(ctcSerialData->getCodeButtonHandlerDataArrayList());
        for (int uniqueID : arrayListOfSelectableOSSectionUniqueIDs) {
            userDescriptions.append(ctcSerialData->getMyShortStringNoCommaViaUniqueID(uniqueID));
        }
//      Collections.sort(userDescriptions);
        //jComboBox->setModel(new DefaultComboBoxModel<>(new Vector<>(userDescriptions)));
        jComboBox->addItems(userDescriptions);
    }

//  NO blank entry as the first selection, returns true if any in list, else false.
//  Also populates "uniqueIDS" with corresponding values.
    /*public*/ /*static*/ bool CommonSubs::populateJComboBoxWithColumnDescriptionsExceptOurs(JComboBox/*<String>*/* jComboBox, CTCSerialData* ctcSerialData, int ourUniqueID, QList<int>* uniqueIDS) {
        QList<QString> userDescriptions = QList<QString>();
        uniqueIDS->clear();
        QList<int> arrayListOfSelectableOSSectionUniqueIDs = getArrayListOfSelectableOSSectionUniqueIDs(ctcSerialData->getCodeButtonHandlerDataArrayList());
        for (int uniqueID : arrayListOfSelectableOSSectionUniqueIDs) {
            if (ourUniqueID != uniqueID) {
                userDescriptions.append(ctcSerialData->getMyShortStringNoCommaViaUniqueID(uniqueID));
                uniqueIDS->append(uniqueID);
            }
        }
//      Collections.sort(userDescriptions);
        //jComboBox.setModel(new DefaultComboBoxModel<>(new Vector<>(userDescriptions)));
        jComboBox->addItems(userDescriptions);
        return !userDescriptions.isEmpty();
    }

    /**
     * Populate a combo box with bean names using getDisplayName().
     * <p>
     * If a panel xml file has not been loaded, the combo box will behave as a
     * text field (editable), otherwise it will behave as standard combo box (not editable).
     * @param jComboBox The string based combo box to be populated.
     * @param beanType The bean type to be loaded.  It has to be in the switch list.
     * @param currentSelection The current item to be selected, none if null.
     * @param firstRowBlank True to create a blank row. If the selection is null or empty, the blank row will be selected.
     */
    /*public*/ /*static*/ void CommonSubs::populateJComboBoxWithBeans(JComboBox/*<String>*/* jComboBox, QString beanType, QString currentSelection, bool firstRowBlank) {
        jComboBox->clear();
        jComboBox->setEditable(false);
        QList<QString> list = QList<QString>();
        if(beanType =="Sensor")  // NOI18N
        {
                //((SensorManager*>InstanceManager::getDefault("SensorManager")).getNamedBeanSet().forEach((s) -> {
                foreach(NamedBean* s, ((SensorManager*)InstanceManager::getDefault("SensorManager"))->getNamedBeanSet())
                {
                    list.append(((Sensor*)s)->getDisplayName());
                }//);
        }
        else  if(beanType == "Turnout") // NOI18N
        {
                foreach(NamedBean* t, ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getNamedBeanSet()) //.forEach((t) ->
                {
                    list.append(((Turnout*)t)->getDisplayName());
                }//);
        }
        else  if(beanType =="SignalHead")  // NOI18N
        {
                foreach(NamedBean* h, ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getNamedBeanSet()) //.forEach((h) ->
                {
                    list.append(((SignalHead*)h)->getDisplayName());
                }//);
        }
        else  if(beanType =="SignalMast")  // NOI18N
        {
                foreach(NamedBean* m, ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getNamedBeanSet()) //.forEach((m) ->
                {
                    list.append(((SignalMast*)m)->getDisplayName());
                }//);
        }
        else  if(beanType =="Block")   // NOI18N
        {
                foreach(NamedBean* b, ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getNamedBeanSet()) //.forEach((b) ->
                {
                    list.append(((Block*)b)->getDisplayName());
                }//);
         }
         else
        {
                log->error(tr("CommonSBean type, '%1', is not validubsBeanType").arg(beanType));   // NOI18N
        }
//        list.sort(new AlphanumComparator());
//        list.forEach((item) ->
//        {
//            jComboBox.addItem(item);
//        });
        jComboBox->addItems(list);
//        JComboBoxUtil::setupComboBoxMaxRows(jComboBox);
        jComboBox->setSelectedItem(currentSelection);
        if (firstRowBlank) {
            jComboBox->insertItem(0, "");
            if (currentSelection.isNull()|| currentSelection.isEmpty()) {
                jComboBox->setCurrentIndex(0);
            }
        }
    }

    /*public*/ /*static*/ void CommonSubs::setSelectedIndexOfJComboBoxViaUniqueID(JComboBox/*<String>*/* jComboBox, CTCSerialData* ctcSerialData, int uniqueID) {
        int index = ctcSerialData->getIndexOfUniqueID(uniqueID) + 1;   // Can be -1 if not found, index becomes 0, which is spaces!
        jComboBox->setCurrentIndex(index);
    }

/*  Someday I'll create a better "ButtonGroup" than provided.  Until then:

    Cheat: We know that the implementation of ButtonGroup uses a Vector when elements
    are added to it.  Therefore the order is guaranteed.  Check your individual order
    by searching for all X.add (where X is the ButtonGroup variable name).
    This routine will "number" each button in order using the "setActionCommand".
    Then you can switch on either this string by doing:
    switch (getButtonSelectedString(X))
        case "0":
            break;
        case "1":
    ....
    Or faster CPU wise:
    switch (getButtonSelectedInt(X))
        case 0:
    ....
*/
    /*public*/ /*static*/ void CommonSubs::numberButtonGroup(QButtonGroup* buttonGroup) {
        int entry = 0;
        //Enumeration<AbstractButton> buttons = buttonGroup.getElements();
        QListIterator<QAbstractButton*> buttons(buttonGroup->buttons());
        while (buttons.hasNext()) {
            QAbstractButton* button = buttons.next();
            button->setText(QString::number(entry++));
        }
    }

    /*public*/ /*static*/ void CommonSubs::setButtonSelected(QButtonGroup* buttonGroup, int selected) {
        QList<QAbstractButton*> buttons = /*Collections.list(*/buttonGroup->buttons();//.getElements());
        if (buttons.isEmpty()) return;    // Safety: The moron forgot to put radio buttons into this group!  Don't select any!
        if (selected < 0 || selected >= buttons.size()) selected = 0;   // Default is zero if you pass an out of range value.
        QAbstractButton* buttonSelected = buttons.at(selected);
        buttonSelected->setChecked(true);
//  Be consistent, when set, do this also:
//        ActionEvent actionEvent = new ActionEvent(buttonSelected, ActionEvent::ACTION_PERFORMED, buttonSelected.getActionCommand());
//        for (ActionListener actionListener : buttonSelected.getActionListeners()) {
//            actionListener.actionPerformed(actionEvent);
//        }
        foreach (QAbstractButton* button, buttons) {
         button->click();
        }
    }

//  If the passed errors array has entries, put up a dialog and return true, if not no dialog, and return false.
    /*public*/ /*static*/ bool CommonSubs::missingFieldsErrorDialogDisplayed(JFrame* parentComponent, QList<QString> errors, bool isCancel) {
        if (errors.isEmpty()) return false;
        QString stringBuffer = QString(errors.size() > 1 ? tr("The following field(s) are required:\n") : tr("The following field is required:\n"));     // NOI18N
        //errors.forEach(error -> stringBuffer.append(error).append("\n")); // NOI18N
        foreach(QString error, errors)
         stringBuffer.append(error);
        if (!isCancel) {
            stringBuffer.append(tr("Please fix before pressing \"Save and close\"\nor you may exit the editor screen without saving.")); // NOI18N
        } else {
            stringBuffer.append(tr("Please fix before pressing \"Save and close\"\nor you may press cancel.")); // NOI18N
        }
        JOptionPane::showMessageDialog(parentComponent, stringBuffer/*.toString()*/,
                tr("Error"), JOptionPane::ERROR_MESSAGE);   // NOI18N
        return true;
    }

//  Simple sub to see if field is not empty.  If empty, then it takes the prompt text and adds it to the end of the errors array.
    /*public*/ /*static*/ void CommonSubs::checkJTextFieldNotEmpty(JTextField* field, JLabel* promptName, QList<QString> errors) {
        if (!isJTextFieldNotEmpty(field)) errors.append(promptName->text());
    }

    /*public*/ /*static*/ bool CommonSubs::isJTextFieldNotEmpty(JTextField* field) {
        return !(field->text().trimmed().isEmpty());
    }

//  Simple sub to see if combo selection is not empty.  If empty, then it takes the prompt text and adds it to the end of the errors array.
    /*public*/ /*static*/ void CommonSubs::checkJComboBoxNotEmpty(JComboBox/*<String>*/* combo, JLabel* promptName, QList<QString> errors) {
        if (!isJComboBoxNotEmpty(combo)) errors.append(promptName->text());
    }

    /*public*/ /*static*/ bool CommonSubs::isJComboBoxNotEmpty(JComboBox/*<String>*/* combo) {
        return !( combo->getSelectedItem()).trimmed().isEmpty();
    }

    /**
     * Get a NBHSensor from the CtcManager NBHSensor map or create a new one.
     * @param newName The new name to be retrieved from the map or created.
     * @param isInternal True if an internal sensor is being requested.  Internal will create the sensor if necessary using provide(String).
     * @return a NBHSensor or null.
     */
    /*public*/ /*static*/ NBHSensor* CommonSubs::getNBHSensor(QString newName, bool isInternal) {
        NBHSensor* sensor = nullptr;
        if (!ProjectsCommonSubs::isNullOrEmptyString(newName)) {
            sensor = ((CtcManager*)InstanceManager::getDefault("CtcManager"))->getNBHSensor(newName);
            if (sensor == nullptr) {
                if (isInternal) {
                    sensor = new NBHSensor("CommonSubs", "new sensor = ", newName, newName);
                } else {
                    sensor = new NBHSensor("CommonSubs", "new sensor = ", newName, newName, false);
                }
            }
        }
        return sensor;
    }

    /**
     * Get a NBHTurnout from the CtcManager NBHTurnout map or create a new one.
     * @param newName The new name to be retrieved from the map or created.
     * @param feedbackDifferent The feedback different state.
     * @return a valid NBHTurnout or an empty NBHTurnout.
     */
    /*public*/ /*static*/ NBHTurnout* CommonSubs::getNBHTurnout(QString newName, bool feedbackDifferent) {
        NBHTurnout* turnout = nullptr;
        if (!ProjectsCommonSubs::isNullOrEmptyString(newName)) {
            turnout = ((CtcManager*)InstanceManager::getDefault("CtcManager"))->getNBHTurnout(newName);
            if (turnout == nullptr) {
                turnout = new NBHTurnout("CommonSubs", "new turnout = ", newName, newName, feedbackDifferent);
            }
        }
        if (turnout == nullptr) {
            // Create a dummy NBHTurnout
            turnout = new NBHTurnout("CommonSubs", "Empty turnout", "");
        }
        return turnout;
    }

    /**
     * Get a NBHSignal from the CtcManager NBHSignal map or create a new one.
     * @param newName The new name to be retrieved from the map or created.
     * @return a valid NBHSignal or null.
     */
    /*public*/ /*static*/ NBHSignal* CommonSubs::getNBHSignal(QString newName) {
        NBHSignal* signal = nullptr;
        if (!ProjectsCommonSubs::isNullOrEmptyString(newName)) {
            signal = ((CtcManager*)InstanceManager::getDefault("CtcManager"))->getNBHSignal(newName);
            if (signal == nullptr) {
                signal = new NBHSignal(newName);
            }
        }
        return signal;
    }

    /**
     * Add a valid NBHSensor entry to an ArrayList.  The sensor name has to match an existing
     * sensor in the JMRI sensor table.
     * @param list The NBHSensor array list.
     * @param sensorName The proposed sensor name.
     */
    /*public*/ /*static*/ void CommonSubs::addSensorToSensorList(QList<NBHSensor*>* list, QString sensorName) {
        NBHSensor* sensor = getNBHSensor(sensorName, false);
        if (sensor != nullptr && sensor->valid()) list->append(sensor);
    }

    /*private*/ /*static*/ /*final*/ Logger* CommonSubs::log = LoggerFactory::getLogger("CommonSubs");
