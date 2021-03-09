#include "rollingstockattributeeditframe.h"
#include "loggerfactory.h"
#include "gridbaglayout.h"
#include "joptionpane.h"
#include "operationsxml.h"
#include "carload.h"
#include "traincommon.h"
#include "carroads.h"
#include "instancemanager.h"
#include "carowners.h"
#include "setup.h"
#include "propertychangeevent.h"
#include "control.h"

namespace Operations
{
    /**
     * Frame for editing a rolling stock attribute.
     *
     * @author Daniel Boudreau Copyright (C) 2020
     */
    ///*public*/ class RollingStockAttributeEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {



    // ROAD and OWNER are the only two attributes shared between Cars and Engines
    /*public*/ /*static*/ /*final*/ QString RollingStockAttributeEditFrame::ROAD = tr("Road");
    /*public*/ /*static*/ /*final*/ QString RollingStockAttributeEditFrame::OWNER = tr("Owner");
    // only here for name checking
    /*public*/ /*static*/ /*final*/ QString RollingStockAttributeEditFrame::TYPE = tr("Type");

    /*protected*/ /*static*/ bool RollingStockAttributeEditFrame::showDialogBox = true;

    // property change
    /*public*/ /*static*/ /*final*/ QString RollingStockAttributeEditFrame::DISPOSE = "dispose"; // NOI18N

    /*public*/RollingStockAttributeEditFrame::RollingStockAttributeEditFrame(QObject *parent)  {
    }


    /*public*/ void RollingStockAttributeEditFrame::initComponents(QString attribute, QString name) {
        getContentPane()->removeAll();

        // track which attribute is being edited
        _attribute = attribute;
        loadCombobox();
        comboBox->setCurrentText(name);

        // general GUI config
        getContentPane()->setLayout(new GridBagLayout());

        textAttribute->setText(attribute);
        quanity->setVisible(showQuanity);

        // row 1
        addItem(textAttribute, 2, 1);
        // row 2
        addItem(addTextBox, 2, 2);
        addItem(addButton, 3, 2);

        // row 3
        addItem(quanity, 1, 3);
        addItem(comboBox, 2, 3);
        addItem(deleteButton, 3, 3);

        // row 4
        addItem(replaceButton, 3, 4);

        addButtonAction(addButton);
        addButtonAction(deleteButton);
        addButtonAction(replaceButton);

        deleteButton->setToolTip(tr("Delete Selected %1 Name").arg(attribute ));
        addButton->setToolTip(tr("Add %1 Name").arg(attribute ));
        replaceButton->setToolTip(tr("Replace Selected %1 Name").arg(attribute ));

        initMinimumSize(QSize(Control::panelWidth400, Control::panelHeight250));
    }

    // add, delete, or replace button
    //@Override
    //@SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD", justification = "GUI ease of use")
    /*public*/ void RollingStockAttributeEditFrame::buttonActionPerformed(QWidget *ae) {
        log->debug("edit frame button activated");
        if (ae == addButton) {
            QString addItem = addTextBox->text().trimmed();
            if (!checkItemName(addItem, tr("Can not add %1"))) {
                return;
            }
            addAttributeName(addItem);
        }
        if (ae == deleteButton) {
            deleteAttributeName(comboBox->currentText());
        }
        if (ae == replaceButton) {
            QString newItem = addTextBox->text().trimmed();
            if (!checkItemName(newItem, tr("Can not replace %1"))) {
                return;
            }
            QString oldItem =  comboBox->currentText();
            if (JOptionPane::showConfirmDialog(this,
                    tr("Replace \"%1\" with \"%2\"").arg(oldItem).arg(newItem ),
                    tr("Replace All?"), JOptionPane::YES_NO_OPTION) != JOptionPane::YES_OPTION) {
                return;
            }
            if (newItem == (oldItem)) {
                return;
            }
            // don't show dialog, save current state
            bool oldShow = showDialogBox;
            showDialogBox = false;
            addAttributeName(newItem);
            showDialogBox = oldShow;
            replaceItem(oldItem, newItem);
            deleteAttributeName(oldItem);
        }
    }

    /*protected*/ bool RollingStockAttributeEditFrame::checkItemName(QString itemName, QString errorMessage) {
        if (itemName.isEmpty()) {
            return false;
        }
        if (_attribute ==(ROAD)) {
            if (!OperationsXml::checkFileName(itemName)) { // NOI18N
                JOptionPane::showMessageDialog(this,
                        tr("Name must not contain reserved characters") + NEW_LINE + tr(". < > : \" / \\ | ? *"),
                        QString(errorMessage).arg(_attribute ), JOptionPane::ERROR_MESSAGE);
                return false;
            }
        }
        //String[] item = { itemName };
        QVariantList item = {itemName};
        if (_attribute == (TYPE)) {
            // can't have the " & " as part of the type name
            if (itemName.contains(CarLoad::SPLIT_CHAR)) {
                JOptionPane::showMessageDialog(this,
                        tr("Can''t have the characters \"%1\" in the name").arg(CarLoad::SPLIT_CHAR ),
                        QString(errorMessage).arg(_attribute ), JOptionPane::ERROR_MESSAGE);
                return false;
            }
            QStringList sl = itemName.split(TrainCommon::HYPHEN);
            item.clear();
            foreach(QString s, sl)
             item.append(s);
        }
        if (item.at(0).toString().length() > Control::max_len_string_attibute) {
            JOptionPane::showMessageDialog(this,
                    tr("Attribute names must be %1 characters or less").arg(Control::max_len_string_attibute ),
                    QString(errorMessage).arg(_attribute ), JOptionPane::ERROR_MESSAGE);
            return false;
        }
        return true;
    }

    /*protected*/ void RollingStockAttributeEditFrame::deleteAttributeName(QString deleteItem) {
        log->debug(tr("delete attribute %1").arg(deleteItem));
        if (_attribute == (ROAD)) {
            // purge train and locations by using replace
            ((CarRoads*)InstanceManager::getDefault("CarRoads"))->replaceName(deleteItem, "");
        }
        if (_attribute == (OWNER)) {
            ((CarOwners*)InstanceManager::getDefault("CarOwners"))->deleteName(deleteItem);
        }
    }

    //@SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD", justification = "GUI ease of use")
    /*protected*/ void RollingStockAttributeEditFrame::addAttributeName(QString addItem) {
        if (_attribute == (ROAD)) {
            ((CarRoads*)InstanceManager::getDefault("CarRoads"))->addName(addItem);
        }
        if (_attribute == (OWNER)) {
            ((CarOwners*)InstanceManager::getDefault("CarOwners"))->addName(addItem);
        }
    }

    /*protected*/ void RollingStockAttributeEditFrame::replaceItem(QString oldItem, QString newItem) {
        if (_attribute == (ROAD)) {
            ((CarRoads*)InstanceManager::getDefault("CarRoads"))->replaceName(oldItem, newItem);
        }
        if (_attribute == (OWNER)) {
            ((CarOwners*)InstanceManager::getDefault("CarOwners"))->replaceName(oldItem, newItem);
        }
    }

    /*protected*/ void RollingStockAttributeEditFrame::loadCombobox() {
        if (_attribute == (ROAD)) {
            comboBox = ((CarRoads*)InstanceManager::getDefault("CarRoads"))->getComboBox();
            ((CarRoads*)InstanceManager::getDefault("CarRoads"))->addPropertyChangeListener((PropertyChangeListener*)this);
        }
        if (_attribute == (OWNER)) {
            comboBox = ((CarOwners*)InstanceManager::getDefault("CarOwners"))->getComboBox();
            ((CarOwners*)InstanceManager::getDefault("CarOwners"))->addPropertyChangeListener((PropertyChangeListener*)this);
        }
    }

    /*public*/ /*static*/ /*final*/ QString RollingStockAttributeEditFrame::FAILED = "failed";

    /*public*/ QString RollingStockAttributeEditFrame::convertLength(QString addItem) {
        // convert from inches to feet if needed
        if (addItem.endsWith("\"")) { // NOI18N
            addItem = addItem.mid(0, addItem.length() - 1);
            try {
             bool ok;
                double inches = addItem.toDouble(&ok);
                if(!ok) throw NumberFormatException();
                int feet = (int) (inches * Setup::getScaleRatio() / 12);
                addItem = QString::number(feet);
            } catch (NumberFormatException e) {
                JOptionPane::showMessageDialog(this, tr("Can not convert from inches to feet"),
                        tr("Rolling Stock length incorrect!"), JOptionPane::ERROR_MESSAGE);
                return FAILED;
            }
        }
        if (addItem.endsWith("cm")) { // NOI18N
            addItem = addItem.mid(0, addItem.length() - 2);
            try {
             bool ok;
                double cm = addItem.toDouble(&ok);
                if(!ok) throw NumberFormatException();
                int meter = (int) (cm * Setup::getScaleRatio() / 100);
                addItem = QString::number(meter);
            } catch (NumberFormatException e) {
                JOptionPane::showMessageDialog(this, tr("Can not convert from cm to meters"),
                        tr("Rolling Stock length incorrect!"), JOptionPane::ERROR_MESSAGE);
                return FAILED;
            }
        }
        // confirm that length is a number and less than 10000 feet
        try {
         bool ok;
            int length = addItem.toInt(&ok);
            if(!ok) throw NumberFormatException();
            if (length < 0) {
                log->error(tr("length (%1) has to be a positive number").arg(addItem));
                return FAILED;
            }
            if (addItem.length() > Control::max_len_string_length_name) {
                JOptionPane::showMessageDialog(this,
                        tr("Rolling Stock attribute names must be %1 characters or less").arg(Control::max_len_string_length_name ),
                        tr("Can not add %1").arg(_attribute ),
                        JOptionPane::ERROR_MESSAGE);
                return FAILED;
            }
        } catch (NumberFormatException e) {
            log->error(tr("length (%1) is not an integer").arg(addItem));
            return FAILED;
        }
        return addItem;
    }

    //@Override
    /*public*/ void RollingStockAttributeEditFrame::dispose() {
        ((CarRoads*)InstanceManager::getDefault("CarRoads"))->removePropertyChangeListener((PropertyChangeListener*)this);
        ((CarOwners*)InstanceManager::getDefault("CarOwners"))->removePropertyChangeListener((PropertyChangeListener*)this);
        //firePropertyChange(DISPOSE, _attribute, "");
        OperationsFrame::dispose();
    }

    //@Override
    /*public*/ void RollingStockAttributeEditFrame::propertyChange(PropertyChangeEvent* e) {
        if (Control::SHOW_PROPERTY) {
            log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(
                    e->getNewValue().toString()));
        }
        if (e->getPropertyName() == (CarRoads::CARROADS_CHANGED_PROPERTY)) {
            ((CarRoads*)InstanceManager::getDefault("CarRoads"))->updateComboBox(comboBox);
        }
        if (e->getPropertyName() == (CarOwners::CAROWNERS_CHANGED_PROPERTY)) {
            ((CarOwners*)InstanceManager::getDefault("CarOwners"))->updateComboBox(comboBox);
        }
    }

/*private*/ /*final*/ /*static*/ Logger* RollingStockAttributeEditFrame::log = LoggerFactory::getLogger("RollingStockAttributeEditFrame");
}
