#include "conditionaleditbase.h"
#include "userpreferencesmanager.h"
#include "instancemanager.h"
#include "joptionpane.h"
#include "picksinglepanel.h"
#include "warrant.h"
#include "destinationpoints.h"
#include "listselectionmodel.h"
#include "jmribeancombobox.h"
#include "oblockmanager.h"
#include "warrantmanager.h"
#include "signalmastmanager.h"
#include "signalheadmanager.h"
#include "conditionalvariable.h"
#include "proxylightmanager.h"
#include "lroutetableaction.h"
#include "defaultlistselectionmodel.h"
/**
 * This is the base class for the Conditional edit view classes. Contains shared
 * variables and methods.
 * <p>
 * @author Dave Sand copyright (c) 2017
 */
///*public*/ class ConditionalEditBase {

/**
 * Set the Logix and Conditional managers and set the selection mode.
 *
 * @param sName the Logix system name being edited
 */
/*public*/ ConditionalEditBase::ConditionalEditBase(QString sName, QObject *parent) : QObject(parent) {
 common();

//         _logixManager = InstanceManager::getNullableDefault("LogixManager);
//         _conditionalManager = InstanceManager::getNullableDefault("ConditionalManager);
 _logixManager = (LogixManager*)InstanceManager::getDefault("LogixManager");
 _conditionalManager = (ConditionalManager*)InstanceManager::getDefault("ConditionalManager");
 _curLogix = (Logix*)_logixManager->getBySystemName(sName);
 loadSelectionMode();
}

/*public*/ ConditionalEditBase::ConditionalEditBase(QObject* parent )  : QObject(parent){
 common();
}
void ConditionalEditBase::common()
{
 _conditionalManager = NULL;
 _logixManager = NULL;
 _curLogix = NULL;
 _numConditionals = 0;
 _inEditMode = false;

 _showReminder = false;
 _suppressReminder = false;
 _suppressIndirectRef = false;
 _pickTable = NULL;               // Current pick table
 _pickTabPane = NULL;        // The tabbed panel for the pick table
 _pickTables = NULL;

 _pickSingleFrame = NULL;
 _pickListener = NULL;
 logixData = new QMap<QString, QString>();
 listenerList = new QList<LogixEventListener*>();
}



/**
 * Get the saved mode selection, default to the tranditional tabbed pick
 * list.
 * <p>
 * During the menu build process, the corresponding menu item is set to
 * selected.
 *
 * @since 4.7.3
 */
void ConditionalEditBase::loadSelectionMode() {
    QVariant modeName = ((UserPreferencesManager*) InstanceManager::getDefault("UserPreferencesManager"))->getProperty("jmri.jmrit.beantable.LogixTableAction", "Selection Mode"); // NOI18N
    if (modeName == QVariant()) {
        _selectionMode = SelectionMode::USEMULTI;
    } else {
        QString currentMode =  modeName.toString();
        if(currentMode== "USEMULTI")        // NOI18N
                _selectionMode = SelectionMode::USEMULTI;
        else if(currentMode ==  "USESINGLE")       // NOI18N
                _selectionMode = SelectionMode::USESINGLE;
        else if(currentMode == "USECOMBO")       // NOI18N
                _selectionMode = SelectionMode::USECOMBO;
        else
        {
                log->warn(tr("Invalid Logix conditional selection mode value, '%1', returned").arg(currentMode));  // NOI18N
                _selectionMode = SelectionMode::USEMULTI;
        }
    }
}



// ------------ Logix Notifications ------------
// The Conditional views support some direct changes to the parent logix.
// This custom event is used to notify the parent Logix that changes are requested.
// When the event occurs, the parent Logix can retrieve the necessary information
// to carry out the actions.
//
// 1) Notify the calling Logix that the Logix user name has been changed.
// 2) Notify the calling Logix that the conditional view is closing
// 3) Notify the calling Logix that it is to be deleted
/**
 * Create a custom listener event
 */
///*public*/ interface LogixEventListener extends EventListener {

//    void logixEventOccurred();
//}
LogixEventListener::LogixEventListener(ConditionalEditBase *ceb) {this->ceb = ceb;}
void LogixEventListener::logixEventOccurred()
{
 // ???
}
/**
 * Add a listener
 *
 * @param listener The recipient
 */
/*public*/ void ConditionalEditBase::addLogixEventListener(LogixEventListener* listener) {
    listenerList->append(listener);
    connect(this, SIGNAL(logixEventOccurred()), listener, SLOT(logixEventOccurred()));
}

/**
 * Remove a listener -- not used
 *
 * @param listener The recipient
 */
/*public*/ void ConditionalEditBase::removeLogixEventListener(LogixEventListener* listener) {
    listenerList->removeOne(listener);
    disconnect(this, SIGNAL(logixEventOccurred()), listener, SLOT(logixEventOccurred()));

}

/**
 * Notify the listeners to check for new data
 */
void ConditionalEditBase::fireLogixEvent() {
//    for (LogixEventListener* l : *listenerList) {
//        l->logixEventOccurred();
//    }
    emit logixEventOccurred();
}

// ------------ Antecedent Methods ------------

/**
 * Create an antecedent string based on the current variables
 * <p>
 * The antecedent consists of all of the variables "in order"
 * combined with the current operator.
 * @since 4.11.5
 * @param variableList The current variable list
 * @return the resulting antecedent string
 */
QString ConditionalEditBase::makeAntecedent(QList<ConditionalVariable*> variableList) {
    QString antecedent;// = new StringBuilder(64);
    if (variableList.size() != 0) {
        QString row = "R"; //NOI18N
        if (variableList.at(0)->isNegated()) {
            antecedent.append("not ");
        }
        antecedent.append(row + "1");
        for (int i = 1; i < variableList.size(); i++) {
            ConditionalVariable* variable = variableList.at(i);
            switch (variable->getOpern()) {
                case Conditional::AND:
                    antecedent.append(" and ");
                    break;
                case Conditional::OR:
                    antecedent.append(" or ");
                    break;
                default:
                    break;
            }
            if (variable->isNegated()) {
                antecedent = antecedent.append("not ");
            }
            antecedent.append(row);
            antecedent.append(i + 1);
        }
    }
    return antecedent/*.toString()*/;
}

/**
 * Add a variable R# entry to the antecedent string.
 * If not the first one, include <strong>and</strong> or <strong>or</strong> depending on the logic type
 * @since 4.11.5
 * @param logicType The current logic type.
 * @param varListSize The current size of the variable list.
 * @param antecedent The current antecedent
 * @return an extended antecedent
 */
QString ConditionalEditBase::appendToAntecedent(Conditional::AntecedentOperator logicType, int varListSize, QString antecedent) {
    if (varListSize > 1) {
        if (logicType.getIntValue() == Conditional::AntecedentOperator::ALL_OR) {
            antecedent = antecedent + " or ";   // NOI18N
        } else {
            antecedent = antecedent + " and ";  // NOI18N
        }
    }
    return antecedent + "R" + varListSize; // NOI18N
}

/**
 * Check the antecedent and logic type.
 * <p>
 * The antecedent text is translated and verified.  A new one is created if necessary.
 * @since 4.11.5
 * @param logicType The current logic type.  Types other than Mixed are ignored.
 * @param antecedentText The proposed antecedent string using the local language.
 * @param variableList The current variable list.
 * @param curConditional The current conditional.
 * @return false if antecedent can't be validated
 */
bool ConditionalEditBase::validateAntecedent(Conditional::AntecedentOperator logicType, QString antecedentText, QList<ConditionalVariable*> variableList, Conditional* curConditional) {
    if (logicType.getIntValue() != Conditional::AntecedentOperator::MIXED
            || LRouteTableAction::LOGIX_INITIALIZER ==(_curLogix->getSystemName())
            || antecedentText == ""
            || antecedentText.trimmed().length() == 0) {
        return true;
    }

    QString antecedent = translateAntecedent(antecedentText, true);
    if (antecedent.length() > 0) {
        QString message = curConditional->validateAntecedent(antecedent, variableList);
        if (message != "") {
            JOptionPane::showMessageDialog(nullptr,
                    message + tr("\nIf the above message is 'String index out of range:', the following number is the position in the antecedent where the error occurred."), // NOI18N
                    tr("Error"),            // NOI18N
                    JOptionPane::ERROR_MESSAGE);
            return false;
        }
    }
    return true;
}

/**
 * Translate an antecedent string between English and the current language
 * as determined by the Bundle classes.
 * <p>
 * The property files have Logic??? keys for translating to the target language.
 * @since 4.11.5
 * @param antecedent The antecedent string which can either local or English
 * @param isLocal True if the antecedent string has local words.
 * @return the translated antecedent string.
 */
/*public*/ /*static*/ QString ConditionalEditBase::translateAntecedent(QString antecedent, bool isLocal) {
    if (antecedent == "") {
        return "";
    }
    QString oldAnd, oldOr, oldNot;
    QString newAnd, newOr, newNot;
    if (isLocal) {
        // To English
        oldAnd = tr("AND").toLower();  // NOI18N
        oldOr = tr("OR").toLower();    // NOI18N
        oldNot = tr("NOT").toLower();  // NOI18N
        newAnd = "and";  // NOI18N
        newOr = "or";    // NOI18N
        newNot = "not";  // NOI18N
    } else {
        // From English
        oldAnd = "and";  // NOI18N
        oldOr = "or";    // NOI18N
        oldNot = "not";  // NOI18N
        newAnd = tr("AND").toLower();  // NOI18N
        newOr = tr("OR").toLower();    // NOI18N
        newNot = tr("NOT").toLower();  // NOI18N
    }
    log->debug(tr("translateAntecedent: before %1").arg(antecedent));
    antecedent = antecedent.replace(oldAnd, newAnd);
    antecedent = antecedent.replace(oldOr, newOr);
    antecedent = antecedent.replace(oldNot, newNot);
    log->debug(tr("translateAntecedent: after  %1").arg(antecedent));
    return antecedent;
}

// ------------ Shared Conditional Methods ------------
/**
 * Verify that the user name is not a duplicate for the selected Logix
 *
 * @param uName is the user name to be checked
 * @param logix is the Logix that is being updated
 * @return true if the name is unique
 */
bool ConditionalEditBase::checkConditionalUserName(QString uName, Logix* logix) {
    if (uName != NULL && uName.length() > 0) {
        Conditional* p = _conditionalManager->getByUserName(logix, uName);
        if (p != NULL) {
            // Conditional with this user name already exists
            log->error("Failure to update Conditional with Duplicate User Name: " // NOI18N
                    + uName);
            JOptionPane::showMessageDialog(
                    NULL, tr("New user name is already in use. Cannot update this Conditional.\nPlease change user name and try again."), // NOI18N
                    tr("Error"), // NOI18N
                    JOptionPane::ERROR_MESSAGE);
            return false;
        }
    } // else return true;
    return true;
}

/**
 * Create a combo name box for Variable and Action name selection.
 *
 * @param itemType The selected variable or action type
 * @return nameBox A combo box based on the item type
 */
JmriBeanComboBox* ConditionalEditBase::createNameBox(int itemType) {
    JmriBeanComboBox* nameBox;
    switch (itemType) {
        case Conditional::ITEM_TYPE_SENSOR:      // 1
            nameBox = new JmriBeanComboBox((SensorManager*)
                    InstanceManager::getDefault("SensorManager"), NULL, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
            break;
        case Conditional::ITEM_TYPE_TURNOUT:     // 2
            nameBox = new JmriBeanComboBox((TurnoutManager*)
                    InstanceManager::getDefault("TurnoutManager"), NULL, JmriBeanComboBox::DISPLAYNAME);
            break;
        case Conditional::ITEM_TYPE_LIGHT:       // 3
            nameBox = new JmriBeanComboBox((LightManager*)
                    InstanceManager::getDefault("LightManager"), NULL, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
            break;
        case Conditional::ITEM_TYPE_SIGNALHEAD:  // 4
            nameBox = new JmriBeanComboBox((Manager*)
                    InstanceManager::getDefault("SignalHeadManager"), NULL, JmriBeanComboBox::DISPLAYNAME);
            break;
        case Conditional::ITEM_TYPE_SIGNALMAST:  // 5
            nameBox = new JmriBeanComboBox((Manager*)
                    InstanceManager::getDefault("SignalMastManager"), NULL, JmriBeanComboBox::DISPLAYNAME);
            break;
        case Conditional::ITEM_TYPE_MEMORY:      // 6
            nameBox = new JmriBeanComboBox((MemoryManager*)
                    InstanceManager::getDefault("MemoryManager"), NULL, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
            break;
        case Conditional::ITEM_TYPE_LOGIX:       // 7
            nameBox = new JmriBeanComboBox((LogixManager*)
                    InstanceManager::getDefault("LogixManager"), NULL, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
            break;
        case Conditional::ITEM_TYPE_WARRANT:     // 8
            nameBox = new JmriBeanComboBox((Manager*)
                    InstanceManager::getDefault("WarrantManager"), NULL, JmriBeanComboBox::DISPLAYNAME);
            break;
        case Conditional::ITEM_TYPE_OBLOCK:      // 10
            nameBox = new JmriBeanComboBox((Manager*)
                    InstanceManager::getDefault("OBlockManager"), NULL, JmriBeanComboBox::DISPLAYNAME);
            break;
        case Conditional::ITEM_TYPE_ENTRYEXIT:   // 11
            nameBox = new JmriBeanComboBox((EntryExitPairs*)
                    InstanceManager::getDefault("EntryExitPairs"), NULL, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
            break;
        case Conditional::ITEM_TYPE_OTHER:   // 14
            nameBox = new JmriBeanComboBox((RouteManager*)
                    InstanceManager::getDefault("RouteManager"), NULL, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
            break;
        default:
            return NULL;             // Skip any other items.
    }
    nameBox->setFirstItemBlank(true);
//    JComboBoxUtil.setupComboBoxMaxRows(nameBox);
    return nameBox;
}

/**
 * Listen for name combo box selection events.
 * <p>
 * When a combo box row is selected, the user/system name is copied to the
 * Action or Variable name field.
 *
 * @since 4.7.3
 */

// ------------ Single Pick List Table Methods ------------
/**
 * Create a single panel picklist JFrame for choosing action and variable
 * names.
 *
 * @since 4.7.3
 * @param itemType   The selected variable or action type
 * @param listener   The listener to be assigned to the picklist
 * @param actionType True if Action, false if Variable.
 */
void ConditionalEditBase::createSinglePanelPickList(int itemType, PickSingleListener* listener, bool actionType) {
    if (_pickListener != NULL) {
        int saveType = _pickListener->getItemType();
        if (saveType != itemType) {
            // The type has changed, need to start over
            closeSinglePanelPickList();
        } else {
            // The pick list has already been created
            return;
        }
    }

    PickSinglePanel* _pickSingle;

    switch (itemType) {
        case Conditional::ITEM_TYPE_SENSOR:      // 1
            _pickSingle = new PickSinglePanel/*<Sensor>*/(PickListModel::sensorPickModelInstance());
            break;
        case Conditional::ITEM_TYPE_TURNOUT:     // 2
            _pickSingle = new PickSinglePanel/*<Turnout>*/(PickListModel::turnoutPickModelInstance());
            break;
        case Conditional::ITEM_TYPE_LIGHT:       // 3
            _pickSingle = new PickSinglePanel/*<Light>*/(PickListModel::lightPickModelInstance());
            break;
        case Conditional::ITEM_TYPE_SIGNALHEAD:  // 4
            _pickSingle = new PickSinglePanel/*<SignalHead>*/(PickListModel::signalHeadPickModelInstance());
            break;
        case Conditional::ITEM_TYPE_SIGNALMAST:  // 5
            _pickSingle = new PickSinglePanel/*<SignalMast>*/(PickListModel::signalMastPickModelInstance());
            break;
        case Conditional::ITEM_TYPE_MEMORY:      // 6
            _pickSingle = new PickSinglePanel/*<Memory>*/(PickListModel::memoryPickModelInstance());
            break;
        case Conditional::ITEM_TYPE_LOGIX:      // 7 -- can be either Logix or Conditional
            if (!actionType) {
                // State Variable
                return;
            }
            _pickSingle = new PickSinglePanel/*<Logix>*/(PickListModel::logixPickModelInstance());
            break;
        case Conditional::ITEM_TYPE_WARRANT:     // 8
            _pickSingle = new PickSinglePanel/*<Warrant*>*/(PickListModel::warrantPickModelInstance());
            break;
        case Conditional::ITEM_TYPE_OBLOCK:      // 10
            _pickSingle = new PickSinglePanel/*<OBlock>*/(PickListModel::oBlockPickModelInstance());
            break;
        case Conditional::ITEM_TYPE_ENTRYEXIT:   // 11
            _pickSingle = new PickSinglePanel/*<DestinationPoints>*/(PickListModel::entryExitPickModelInstance());
            break;
        default:
            return;             // Skip any other items.
    }

    // Create the JFrame
    _pickSingleFrame = new JmriJFrameX(("Single Pick List"));  // NOI18N
    _pickSingleFrame->setCentralWidget(_pickSingle);
    _pickSingleFrame->pack();
    _pickSingleFrame->setVisible(true);
    _pickSingleFrame->toFront();

    // Set the table selection listener
    _pickListener = listener;
    _pickTable = _pickSingle->getTable();
    _pickTable->getSelectionModel()->addListSelectionListener(_pickListener);
}

/**
 * Close a single panel picklist JFrame and related items.
 *
 * @since 4.7.3
 */
void ConditionalEditBase::closeSinglePanelPickList() {
    if (_pickSingleFrame != NULL) {
        _pickSingleFrame->setVisible(false);
        _pickSingleFrame->dispose();
        _pickSingleFrame = NULL;
        _pickListener = NULL;
        _pickTable = NULL;
    }
}

/**
 * Listen for Pick Single table click events.
 * <p>
 * When a table row is selected, the user/system name is copied to the
 * Action or Variable name field.
 *
 * @since 4.7.3
 */
//class PickSingleListener : public ListSelectionListener {

    /**
     * @param textField The target field object when an entry is selected
     * @param itemType  The current selected table type number
     */
    /*public*/PickSingleListener:: PickSingleListener(JTextField* textField, int itemType, ConditionalEditBase* base) {
        saveItemType = itemType;
        saveTextField = textField;
        this->base = base;
    }

//    JTextField saveTextField;
//    int saveItemType;          // Current table type

    //@Override
    /*public*/ void PickSingleListener::valueChanged(ListSelectionEvent* e) {
        int selectedRow = base->_pickTable->getSelectedRow();
        if (selectedRow >= 0) {
            int selectedCol = base->_pickTable->getSelectedColumn();
            QString newName = base->_pickTable->getModel()->data(base->_pickTable->getModel()->index( selectedRow, selectedCol)).toString();
            if (base->log->isDebugEnabled()) {
                base->log->debug(tr("Pick single panel row event: row = '%1', column = '%2', selected name = '%3'").arg( // NOI18N
                        selectedRow).arg(selectedCol).arg(newName));
            }
            saveTextField->setText(newName);
        }
    }

    /*public*/ int PickSingleListener::getItemType() {
        return saveItemType;
    }
//}

// ------------ Pick List Table Methods ------------
/**
 * Open a new drag-n-drop Pick List to drag Variable and Action names from
 * to form Logix Conditionals.
 */
void ConditionalEditBase::openPickListTable() {
    if (_pickTables == NULL) {
        _pickTables = new PickFrame(tr("Pick List"));  // NOI18N
    } else {
        _pickTables->setVisible(true);
    }
    _pickTables->toFront();
}

/**
 * Hide the drag-n-drop Pick List if the last detail edit is closing
 */
void ConditionalEditBase::hidePickListTable() {
    if (_pickTables != NULL) {
        _pickTables->setVisible(false);
    }
}

/**
 * Set the pick list tab based on the variable or action type If there is
 * not a corresponding tab, hide the picklist
 *
 * @param curType    is the current type
 * @param actionType True if Action, false if Variable.
 */
void ConditionalEditBase::setPickListTab(int curType, bool actionType) {
    bool tabSet = true;
    if (_pickTables == NULL) {
        return;
    }
    if (_pickTabPane == NULL) {
        findPickListTabPane(_pickTables->children(), 1);
    }
    if (_pickTabPane != NULL) {
        // Convert variable/action type to the corresponding tab index
        int tabIndex = 0;
        switch (curType) {
            case Conditional::ITEM_TYPE_SENSOR:    // 1
                tabIndex = 1;
                break;
            case Conditional::ITEM_TYPE_TURNOUT:   // 2
                tabIndex = 0;
                break;
            case Conditional::ITEM_TYPE_LIGHT:     // 3
                tabIndex = 6;
                break;
            case Conditional::ITEM_TYPE_SIGNALHEAD:            // 4
                tabIndex = 2;
                break;
            case Conditional::ITEM_TYPE_SIGNALMAST:            // 5
                tabIndex = 3;
                break;
            case Conditional::ITEM_TYPE_MEMORY:    // 6
                tabIndex = 4;
                break;
            case Conditional::ITEM_TYPE_LOGIX:     // 7 Conditional (Variable) or Logix (Action)
                if (actionType) {
                    tabIndex = 10;
                } else {
                    // State Variable
                    tabSet = false;
                }
                break;
            case Conditional::ITEM_TYPE_WARRANT:   // 8
                tabIndex = 7;
                break;
            case Conditional::ITEM_TYPE_OBLOCK:    // 10
                tabIndex = 8;
                break;
            case Conditional::ITEM_TYPE_ENTRYEXIT: // 11
                tabIndex = 9;
                break;
            default:
                // No tab found
                tabSet = false;
        }
        if (tabSet) {
            _pickTabPane->setCurrentIndex(tabIndex);
        }
    }
    _pickTables->setVisible(tabSet);
    return;
}

/**
 * Recursive search for the tab panel
 *
 * @param compList The components for the current Level
 * @param level    The current level in the structure
 */
void ConditionalEditBase::findPickListTabPane(QObjectList compList, int level) {
    for (QObject* compItem : compList) {
        // Safety catch
        if (level > 10) {
            log->warn("findPickListTabPane: safety breaker reached");  // NOI18N
            return;
        }

        //if (compItem instanceof JTabbedPane)
        if(qobject_cast<QTabWidget*>(compItem))
        {
            _pickTabPane = (QTabWidget*) compItem;
        } else {
            int nextLevel = level + 1;
            QWidget* nextItem = (QWidget*) compItem;
            QObjectList nextList = nextItem->children();
            findPickListTabPane(nextList, nextLevel);
        }
    }
    return;
}

// ------------ Manage Conditional Reference map ------------
/**
 * Build a tree set from conditional references.
 *
 * @since 4.7.4
 * @param varList The ConditionalVariable list that might contain
 *                conditional references
 * @param treeSet A tree set to be built from the varList data
 */
void ConditionalEditBase::loadReferenceNames(QList<ConditionalVariable*> varList, QSet<QString> treeSet)
{
 treeSet.clear();
 for (ConditionalVariable* var : varList) {
     if (var->getType() == Conditional::TYPE_CONDITIONAL_TRUE || var->getType() == Conditional::TYPE_CONDITIONAL_FALSE) {
         treeSet.insert(var->getName());
     }
 }
}

/**
 * Check for conditional references
 *
 * @since 4.7.4
 * @param logixName The Logix under consideration
 * @return true if no references
 */
bool ConditionalEditBase::checkConditionalReferences(QString logixName) {
    Logix* x = _logixManager->getLogix(logixName);
    int numConditionals = x->getNumConditionals();
    for (int i = 0; i < numConditionals; i++) {
        QString csName = x->getConditionalByNumberOrder(i);

        // If the conditional is a where used target, check scope
        QList<QString> refList = ((ConditionalManager*) InstanceManager::getDefault("ConditionalManager"))->getWhereUsed(csName);
        if (!refList.isEmpty()) {
            for (QString refName : refList) {
                Logix* xRef = _conditionalManager->getParentLogix(refName);
                QString xsName = xRef->getSystemName();
                if (logixName == (xsName)) {
                    // Member of the same Logix
                    continue;
                }

                // External references have to be removed before the Logix can be deleted.
                Conditional* c = x->getConditional(csName);
                Conditional* cRef = xRef->getConditional(refName);
                JOptionPane::showMessageDialog(NULL,
                        tr("Conditional \"%1\" (%2) is a Conditional Variable in the Conditional, \"%3\" (%4), of Logix, \"%5\" (%6).\nPlease remove that variable first.").arg(c->getUserName()).arg(c->getSystemName()).arg(cRef->getUserName()).arg(cRef->getSystemName()).arg(xRef->getUserName()).arg(xRef->getSystemName()), // NOI18N
                        tr("Error"),JOptionPane::ERROR_MESSAGE);        // NOI18N
                return false;
            }
        }
    }
    return true;
}

/**
 * Update the conditional reference where used.
 * <p>
 * The difference between the saved target names and new target names is
 * used to add/remove where used references.
 *
 * @since 4.7.4
 * @param oldTargetNames The conditional target names before updating
 * @param newTargetNames The conditional target names after updating
 * @param refName        The system name for the referencing conditional
 */
void ConditionalEditBase::updateWhereUsed(QStringList oldTargetNames, QStringList newTargetNames, QString refName) {
    QStringList deleteNames = QStringList(oldTargetNames);
    //deleteNames.removeAll(newTargetNames);
    foreach (QString s, newTargetNames) {
     deleteNames.removeAll(s);
    }
    for (QString deleteName : deleteNames) {
        ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->removeWhereUsed(deleteName, refName);
    }

    QStringList addNames = QStringList(newTargetNames);
    //addNames.removeAll(oldTargetNames);
    foreach (QString s, oldTargetNames) {
     addNames.removeAll(s);
    }

    for (QString addName : addNames) {
        ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->addWhereUsed(addName, refName);
    }
}

// ------------ Utility Methods - Data Validation ------------
/**
 * Display reminder to save.
 */
void ConditionalEditBase::showSaveReminder()
{
 if (_showReminder)
 {
  if (InstanceManager::getNullableDefault("UserPreferencesManager") != NULL)
  {
   if (InstanceManager::getNullableDefault("UserPreferencesManager") != NULL)
   {
       ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->showInfoMessage(tr("Reminder"), tr("ReminderSaveString"), tr("MenuItemLogixTable %1").arg(getClassName()),
                       "remindSaveLogix"); // NOI18N
   }
  }
 }
}

/**
 * Check if String is an integer or references an integer.
 *
 * @param actionType   Conditional action to check for, i.e.
 *                     ACTION_SET_LIGHT_INTENSITY
 * @param intReference string referencing a decimal for light intensity or
 *                     the name of a memory
 * @return true if either correct decimal format or a memory with the given
 *         name is present
 */
bool ConditionalEditBase::validateIntensityReference(int actionType, QString intReference) {
    if (intReference == NULL || intReference.trimmed().length() == 0) {
        displayBadNumberReference(actionType);
        return false;
    }
    try {
        return validateIntensity((intReference).toInt());
    } catch (NumberFormatException e) {
        QString intRef = intReference;
        if (intReference.length() > 1 && intReference.at(0) == '@') {
            intRef = intRef.mid(1);
        }
        if (!confirmIndirectMemory(intRef)) {
            return false;
        }
        intRef = validateMemoryReference(intRef);
        if (intRef != NULL) // memory named 'intReference' exists
        {
            Memory* m = (Memory*)InstanceManager::memoryManagerInstance()->getByUserName(intRef);
            if (m == NULL) {
                m = (Memory*)InstanceManager::memoryManagerInstance()->getBySystemName(intRef);
            }
            try {
                if (m == NULL || m->getValue().toInt() == NULL) {
                    throw new NumberFormatException();
                }
                validateIntensity( m->getValue().toInt());
            } catch (NumberFormatException ex) {
                JOptionPane::showMessageDialog(
                        NULL,tr("Memory variable \"%1\" currently does not contain a numeric value.\nWhen triggered the action cannot be performed until this value is corrected!").arg(intReference), tr("Warning"), JOptionPane::WARNING_MESSAGE); // NOI18N
            }
            return true;    // above is a warning to set memory correctly
        }
        displayBadNumberReference(actionType);
    }
    return false;
}

/**
 * Check if text represents an integer is suitable for percentage w/o
 * NumberFormatException.
 *
 * @param time value to use as light intensity percentage
 * @return true if time is an integer in range 0 - 100
 */
bool ConditionalEditBase::validateIntensity(int time) {
    if (time < 0 || time > 100) {
        JOptionPane::showMessageDialog(
                NULL, tr("%1 is an unreasonable amount to %2./nPlease enter a positive percentage, and try again.").arg(time).arg(tr("et Light Intensity action")), tr("Error"), JOptionPane::ERROR_MESSAGE);   // NOI18N
        return false;
    }
    return true;
}

/**
 * Check if a string is decimal or references a decimal.
 *
 * @param actionType integer representing the Conditional action type being
 *                   checked, i.e. ACTION_DELAYED_TURNOUT
 * @param ref        entry to check
 * @return true if ref is itself a decimal or user will provide one from a
 *         Memory at run time
 */
bool ConditionalEditBase::validateTimeReference(int actionType, QString ref) {
#if 0
    if (ref == NULL || ref.trimmed().length() == 0) {
        displayBadNumberReference(actionType);
        return false;
    }
    try {
        return validateTime(actionType, Float.valueOf(ref).floatValue());
        // return true if ref is decimal within allowed range
    } catch (NumberFormatException e) {
        String memRef = ref;
        if (ref.length() > 1 && ref.charAt(0) == '@') {
            memRef = ref.substring(1);
        }
        if (!confirmIndirectMemory(memRef)) {
            return false;
        }
        memRef = validateMemoryReference(memRef);
        if (memRef != NULL) // memory named 'intReference' exists
        {
            Memory m = InstanceManager::memoryManagerInstance().getByUserName(memRef);
            if (m == NULL) {
                m = InstanceManager::memoryManagerInstance().getBySystemName(memRef);
            }
            try {
                if (m == NULL || m.getValue() == NULL) {
                    throw new NumberFormatException();
                }
                validateTime(actionType, Float.valueOf((String) m.getValue()).floatValue());
            } catch (NumberFormatException ex) {
                JOptionPane::showMessageDialog(
                        NULL, java.text.MessageFormat.format(tr("Error24"), // NOI18N
                                memRef), tr("WarningTitle"), JOptionPane::WARNING_MESSAGE);   // NOI18N
            }
            return true;    // above is a warning to set memory correctly
        }
        displayBadNumberReference(actionType);
    }
#endif
    return false;
}
#if 0
/**
 * Range check time entry (assumes seconds).
 *
 * @param actionType integer representing the Conditional action type being
 *                   checked, i.e. ACTION_DELAYED_TURNOUT
 * @param time       value to be checked
 * @return false if time &gt; 3600 (seconds) or too small
 */
bool validateTime(int actionType, float time) {
    float maxTime = 3600;     // more than 1 hour
    float minTime = 0.020f;
    if (time < minTime || time > maxTime) {
        String errorNum = " ";
        switch (actionType) {
            case Conditional::ACTION_DELAYED_TURNOUT:
                errorNum = "Error39";       // NOI18N
                break;
            case Conditional::ACTION_RESET_DELAYED_TURNOUT:
                errorNum = "Error41";       // NOI18N
                break;
            case Conditional::ACTION_DELAYED_SENSOR:
                errorNum = "Error23";       // NOI18N
                break;
            case Conditional::ACTION_RESET_DELAYED_SENSOR:
                errorNum = "Error27";       // NOI18N
                break;
            case Conditional::ACTION_SET_LIGHT_TRANSITION_TIME:
                errorNum = "Error29";       // NOI18N
                break;
            default:
                break;
        }
        JOptionPane::showMessageDialog(
                NULL, java.text.MessageFormat.format(tr("Error38"), // NOI18N
                        time, tr(errorNum)), tr("ErrorTitle"), JOptionPane::ERROR_MESSAGE);       // NOI18N
        return false;
    }
    return true;
}
#endif
/**
 * Display an error message to user when an invalid number is provided in
 * Conditional set up.
 *
 * @param actionType integer representing the Conditional action type being
 *                   checked, i.e. ACTION_DELAYED_TURNOUT
 */
void ConditionalEditBase::displayBadNumberReference(int actionType) {
    QString errorNum = " ";
    if (actionType ==  Conditional::ACTION_DELAYED_TURNOUT)
        {
            errorNum = "Error39";       // NOI18N
        }
        else if(actionType ==   Conditional::ACTION_RESET_DELAYED_TURNOUT)
        {
            errorNum = "Error41";       // NOI18N
    }
    else if(actionType ==Conditional::ACTION_DELAYED_SENSOR)
        {
            errorNum = "Error23";       // NOI18N
    }
    else if(actionType == Conditional::ACTION_RESET_DELAYED_SENSOR)
        {
            errorNum = "Error27";       // NOI18N
    }
    else if(actionType ==Conditional::ACTION_SET_LIGHT_INTENSITY)
        {
            JOptionPane::showMessageDialog(
                    NULL, tr("Enter an integer (digits only) or a Memory variable containing\nan integer to Set Light Intensity."), // NOI18N
                    tr("Error"), JOptionPane::ERROR_MESSAGE);       // NOI18N
            return;
    }
    else if(actionType == Conditional::ACTION_SET_LIGHT_TRANSITION_TIME)
        {
            errorNum = "Set Light Transition Time";       // NOI18N
        }

            log->warn(tr("Unexpected action type {} in displayBadNumberReference").arg( actionType));  // NOI18N

    JOptionPane::showMessageDialog(
            NULL, tr("Enter a decimal number or a Memory variable containing\na decimal number for the number of seconds to %1.").arg( // NOI18N
                    errorNum), tr("ErrorTitle"), JOptionPane::ERROR_MESSAGE);       // NOI18N
}

/**
 * Check Memory reference of text.
 * <p>
 * Show a message if not found.
 *
 * @param name the name to look for
 * @return the system or user name of the corresponding Memory, NULL if not
 *         found
 */
QString ConditionalEditBase::validateMemoryReference(QString name) {
    Memory* m = NULL;
    if (name != NULL) {
        if (name.length() > 0) {
            m = (Memory*)InstanceManager::memoryManagerInstance()->getByUserName(name);
            if (m != NULL) {
                return name;
            }
        }
        m = (Memory*)InstanceManager::memoryManagerInstance()->getBySystemName(name);
    }
    if (m == NULL) {
        messageInvalidActionItemName(name, "Memory"); // NOI18N
        return NULL;
    }
    return name;
}

/**
 * Check if user will provide a valid item name in a Memory variable
 *
 * @param memName Memory location to provide item name at run time
 * @return false if user replies No
 */
bool ConditionalEditBase::confirmIndirectMemory(QString memName) {
    if (!_suppressIndirectRef) {
        int response = JOptionPane::showConfirmDialog(NULL, tr("Press \"YES\" if at run time Memory location \"%1\" will contain a valid item name for this action.\nPress \"NO\" if you want to enter the item name directly.\nPress \"CANCEL\" if you want to suppress this warning.\n").arg(memName), // NOI18N
                tr("Confirm"), JOptionPane::YES_NO_CANCEL_OPTION, // NOI18N
                JOptionPane::QUESTION_MESSAGE);
        if (response == JOptionPane::NO_OPTION) {
            return false;
        } else if (response == JOptionPane::CANCEL_OPTION) {
            _suppressIndirectRef = true;
        }
    }
    return true;
}

/**
 * Check Turnout reference of text.
 * <p>
 * Show a message if not found.
 *
 * @param name the name to look for
 * @return the system or user name of the corresponding Turnout, NULL if not
 *         found
 */
QString ConditionalEditBase::validateTurnoutReference(QString name) {
    Turnout* t = NULL;
    if (name != NULL) {
        if (name.length() > 0) {
            t = (Turnout*)InstanceManager::turnoutManagerInstance()->getByUserName(name);
            if (t != NULL) {
                return name;
            }
        }
        t = (Turnout*)InstanceManager::turnoutManagerInstance()->getBySystemName(name);
    }
    if (t == NULL) {
        messageInvalidActionItemName(name, "Turnout"); // NOI18N
        return NULL;
    }
    return name;
}

/**
 * Check SignalHead reference of text.
 * <p>
 * Show a message if not found.
 *
 * @param name the name to look for
 * @return the system or user name of the corresponding SignalHead, NULL if
 *         not found
 */
QString ConditionalEditBase::validateSignalHeadReference(QString name) {
    SignalHead* h = NULL;
    if (name != NULL) {
        if (name.length() > 0) {
            h = (SignalHead*)((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getByUserName(name);
            if (h != NULL) {
                return name;
            }
        }
        h = (SignalHead*)((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getBySystemName(name);
    }
    if (h == NULL) {
        messageInvalidActionItemName(name, "SignalHead"); // NOI18N
        return NULL;
    }
    return name;
}

/**
 * Check SignalMast reference of text.
 * <p>
 * Show a message if not found.
 *
 * @param name the name to look for
 * @return the system or user name of the corresponding Signal Mast, NULL if
 *         not found
 */
QString ConditionalEditBase::validateSignalMastReference(QString name) {
    SignalMast* h = NULL;
    if (name != NULL) {
        if (name.length() > 0) {
            h = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName(name);
            if (h != NULL) {
                return name;
            }
        }
        try {
            h = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->provideSignalMast(name);
        } catch (IllegalArgumentException ex) {
            h = NULL; // tested below
        }
    }
    if (h == NULL) {
        messageInvalidActionItemName(name, "SignalMast"); // NOI18N
        return NULL;
    }
    return name;
}

/**
 * Check Warrant reference of text.
 * <p>
 * Show a message if not found.
 *
 * @param name the name to look for
 * @return the system or user name of the corresponding Warrant, NULL if not
 *         found
 */
QString ConditionalEditBase::validateWarrantReference(QString name) {
    Warrant* w = NULL;
    if (name != NULL) {
        if (name.length() > 0) {
            w = (Warrant*)((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getByUserName(name);
            if (w != NULL) {
                return name;
            }
        }
        w = (Warrant*)((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getBySystemName(name);
    }
    if (w == NULL) {
        messageInvalidActionItemName(name, "Warrant"); // NOI18N
        return NULL;
    }
    return name;
}

/**
 * Check OBlock reference of text.
 * <p>
 * Show a message if not found.
 *
 * @param name the name to look for
 * @return the system or user name of the corresponding OBlock, NULL if not
 *         found
 */
QString ConditionalEditBase::validateOBlockReference(QString name) {
    OBlock* b = NULL;
    if (name != NULL) {
        if (name.length() > 0) {
            b = (OBlock*)((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getByUserName(name);
            if (b != NULL) {
                return name;
            }
        }
        b = (OBlock*)((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getBySystemName(name);
    }
    if (b == NULL) {
        messageInvalidActionItemName(name, "OBlock"); // NOI18N
        return NULL;
    }
    return name;
}

/**
 * Check Sensor reference of text.
 * <p>
 * Show a message if not found.
 *
 * @param name the name to look for
 * @return the system or user name of the corresponding Sensor, NULL if not
 *         found
 */
QString ConditionalEditBase::validateSensorReference(QString name) {
    Sensor* s = NULL;
    if (name != NULL) {
        if (name.length() > 0) {
            s = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->getByUserName(name);
            if (s != NULL) {
                return name;
            }
        }
        s = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->getBySystemName(name);
    }
    if (s == NULL) {
        messageInvalidActionItemName(name, "Sensor"); // NOI18N
        return NULL;
    }
    return name;
}

/**
 * Check Light reference of text.
 * <p>
 * Show a message if not found.
 *
 * @param name the name to look for
 * @return the system or user name of the corresponding Light, NULL if not
 *         found
 */
QString ConditionalEditBase::validateLightReference(QString name) {
    Light* l = NULL;
    if (name != NULL) {
        if (name.length() > 0) {
            l = (Light*)InstanceManager::lightManagerInstance()->getByUserName(name);
            if (l != NULL) {
                return name;
            }
        }
        l = (Light*)InstanceManager::lightManagerInstance()->getBySystemName(name);
    }
    if (l == NULL) {
        messageInvalidActionItemName(name, "Light"); // NOI18N
        return NULL;
    }
    return name;
}

/**
 * Check Conditional reference of text.
 * <p>
 * Show a message if not found.
 *
 * @param name the name to look for
 * @return the system or user name of the corresponding Conditional, NULL if
 *         not found
 */
QString ConditionalEditBase::validateConditionalReference(QString name) {
    Conditional* c = NULL;
    if (name != NULL) {
        if (name.length() > 0) {
            c = _conditionalManager->getByUserName(name);
            if (c != NULL) {
                return name;
            }
        }
        c = _conditionalManager->getBySystemName(name);
    }
    if (c == NULL) {
        messageInvalidActionItemName(name, "Conditional"); // NOI18N
        return NULL;
    }
    return name;
}

/**
 * Check Logix reference of text.
 * <p>
 * Show a message if not found.
 *
 * @param name the name to look for
 * @return the system or user name of the corresponding Logix, NULL if not
 *         found
 */
QString ConditionalEditBase::validateLogixReference(QString name) {
    Logix* l = NULL;
    if (name != NULL) {
        if (name.length() > 0) {
            l = (Logix*)_logixManager->getByUserName(name);
            if (l != NULL) {
                return name;
            }
        }
        l = (Logix*)_logixManager->getBySystemName(name);
    }
    if (l == NULL) {
        messageInvalidActionItemName(name, "Logix"); // NOI18N
        return NULL;
    }
    return name;
}

/**
 * Check Route reference of text.
 * <p>
 * Show a message if not found.
 *
 * @param name the name to look for
 * @return the system or user name of the corresponding Route, NULL if not
 *         found
 */
QString ConditionalEditBase::validateRouteReference(QString name) {
    Route* r = NULL;
    if (name != NULL) {
        if (name.length() > 0) {
            r = (Route*)((RouteManager*)InstanceManager::getDefault("RouteManager"))->getByUserName(name);
            if (r != NULL) {
                return name;
            }
        }
        r = (Route*)((RouteManager*)InstanceManager::getDefault("RouteManager"))->getBySystemName(name);
    }
    if (r == NULL) {
        messageInvalidActionItemName(name, "Route"); // NOI18N
        return NULL;
    }
    return name;
}

/**
 * Check an Audio reference of text.
 * <p>
 * Show a message if not found.
 *
 * @param name the name to look for
 * @return the system or user name of the corresponding AudioManager, NULL
 *         if not found
 */
QString ConditionalEditBase::validateAudioReference(QString name) {
    Audio* a = NULL;
    if (name != NULL) {
        if (name.length() > 0) {
            a = ((AudioManager*)InstanceManager::getDefault("AudioManager"))->getByUserName(name);
            if (a != NULL) {
                return name;
            }
        }
        a = ((AudioManager*)InstanceManager::getDefault("AudioManager"))->getBySystemName(name);
    }
    if (a == NULL || (a->getSubType() != Audio::SOURCE && a->getSubType() != Audio::LISTENER)) {
        messageInvalidActionItemName(name, "Audio"); // NOI18N
        return NULL;
    }
    return name;
}

/**
 * Check an EntryExit reference of text.
 * <p>
 * Show a message if not found.
 *
 * @param name the name to look for
 * @return the system name of the corresponding EntryExit pair, NULL if not
 *         found
 */
QString ConditionalEditBase::validateEntryExitReference(QString name) {
    NamedBean* nb = NULL;
    if (name != NULL) {
        if (name.length() > 0) {
            nb = ((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))->getNamedBean(name);
            if (nb != NULL) {
                return name;
            }
        }
    }
    messageInvalidActionItemName(name, "EntryExit"); // NOI18N
    return NULL;
}

/**
 * Get Light instance.
 * <p>
 * Show a message if not found.
 *
 * @param name user or system name of an existing light
 * @return the Light object
 */
Light* ConditionalEditBase::getLight(QString name) {
    if (name == NULL) {
        return NULL;
    }
    Light* l = NULL;
    if (name.length() > 0) {
        l = (Light*)((ProxyLightManager*)InstanceManager::lightManagerInstance())->getByUserName(name);
        if (l != NULL) {
            return l;
        }
        l = (Light*)((ProxyLightManager*)InstanceManager::lightManagerInstance())->getBySystemName(name);
    }
    if (l == NULL) {
        messageInvalidActionItemName(name, "Light"); //NOI18N
    }
    return l;
}

int ConditionalEditBase::parseTime(QString s) {
    int nHour = 0;
    int nMin = 0;
    bool error = false;
    int index = s.indexOf(':');
    QString hour = NULL;
    QString minute = NULL;
    try {
        if (index > 0) { // : after start
            hour = s.mid(0, index);
            if (index + 1 < s.length()) { // check for : at end
                minute = s.mid(index + 1);
            } else {
                minute = "0";
            }
        } else if (index == 0) { // : at start
            hour = "0";
            minute = s.mid(index + 1);
        } else {
            hour = s;
            minute = "0";
        }
    } catch (IndexOutOfBoundsException ioob) {
        error = true;
    }
    if (!error) {
        try {
            nHour = (hour).toInt();
            if ((nHour < 0) || (nHour > 24)) {
                error = true;
            }
            nMin = (minute).toInt();
            if ((nMin < 0) || (nMin > 59)) {
                error = true;
            }
        } catch (NumberFormatException e) {
            error = true;
        }
    }
    if (error) {
        // if unsuccessful, print error message
        JOptionPane::showMessageDialog(NULL,
                tr("Invalid time entry \"{0}\"\nTime must be entered in hh:mm format (e.g. 01:30, 16:00)\nfor a 24-hour clock. Please reenter in correct format, and try again.").arg(s), tr("Error"), // NOI18N
                JOptionPane::ERROR_MESSAGE);
        return (-1);
    }
    // here if successful
    return ((nHour * 60) + nMin);
}

/**
 * Format time to hh:mm given integer hour and minute.
 *
 * @param hour   value for time hours
 * @param minute value for time minutes
 * @return Formatted time string
 */
/*public*/ /*static*/ QString ConditionalEditBase::formatTime(int hour, int minute) {
    QString s = "";
    QString t = QString::number(hour);
    if (t.length() == 2) {
        s = t + ":";
    } else if (t.length() == 1) {
        s = "0" + t + ":";
    }
    t = QString::number(minute);
    if (t.length() == 2) {
        s = s + t;
    } else if (t.length() == 1) {
        s = s + "0" + t;
    }
    if (s.length() != 5) {
        // input error
        s = "00:00";
    }
    return s;
}

// ------------ Error Dialogs ------------
/**
 * Send an Invalid Conditional SignalHead state message for Edit Logix pane.
 *
 * @param name       proposed appearance description
 * @param appearance to compare to
 */
void ConditionalEditBase::messageInvalidSignalHeadAppearance(QString name, QString appearance) {
    JOptionPane::showMessageDialog(NULL,
            tr("\"%2\" is not a valid appearance for Signal Head \"%1\".").arg(name).arg(appearance), tr("Error"), // NOI18N
            JOptionPane::ERROR_MESSAGE);
}

/**
 * Send an Invalid Conditional Action name message for Edit Logix pane.
 *
 * @param name     user or system name to look up
 * @param itemType type of Bean to look for
 */
void ConditionalEditBase::messageInvalidActionItemName(QString name, QString itemType) {
    JOptionPane::showMessageDialog(NULL,
            tr("The name \"%1\" does not match an existing \"%2\".\nPlease correct or create as required, and try again.").arg(name).arg(tr("BeanName") + itemType), tr("Error"), // NOI18N
            JOptionPane::ERROR_MESSAGE);
}

/**
 * Send a duplicate Conditional user name message for Edit Logix pane.
 *
 * @param svName proposed name that duplicates an existing name
 */
void ConditionalEditBase::messageDuplicateConditionalUserName(QString svName) {
    JOptionPane::showMessageDialog(NULL,
            tr("Duplicate user name error. Entered user name is already in use by Conditional \"%1\".\nPlease enter a different user name from others in this table.").arg(svName), tr("Error"), // NOI18N
            JOptionPane::ERROR_MESSAGE);
}

/*protected*/ QString ConditionalEditBase::getClassName() {
    //return ConditionalEditBase::getName();
 return "jmri.jmrit.condtional.ConditionalEditBase";
}

/*private*/ /*final*/ /*static*/ Logger* ConditionalEditBase::log = LoggerFactory::getLogger("ConditionalEditBase");
