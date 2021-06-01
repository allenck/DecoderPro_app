#include "lightcontroltablemodel.h"
#include "jtable.h"
#include "tablecolumn.h"
#include "tablecolumnmodel.h"
#include "lighttableaction.h"

/**
 * Table model for Light Controls in the Add/Edit Light windows.
 * No direct access to this class is normally required, access via
 * LightControlPane.java
 *
 * Code originally within LightTableAction.
 *
 * @author Dave Duchamp Copyright (C) 2004
 * @author Egbert Broerse Copyright (C) 2017
 * @author Steve Young Copyright (C) 2021
 */
// /*public*/ class LightControlTableModel extends javax.swing.table.AbstractTableModel {



/*protected*/ /*static final*/ QString LightControlTableModel::sensorControl = tr("LightSensorControl");
/*protected*/ /*static final*/ QString LightControlTableModel::fastClockControl = tr("LightFastClockControl");
/*protected*/ /*static final*/ QString LightControlTableModel::turnoutStatusControl = tr("LightTurnoutStatusControl");
/*protected*/ /*static final*/ QString LightControlTableModel::timedOnControl = tr("LightTimedOnControl");
/*protected*/ /*static final*/ QString LightControlTableModel::twoSensorControl = tr("LightTwoSensorControl");
/*protected*/ /*static final*/ QString LightControlTableModel::noControl = tr("LightNoControl");

/*protected*/ /*static*/ /*final*/ QVector<QString> LightControlTableModel::controlTypes = QVector<QString>{
    noControl,
    sensorControl,
    fastClockControl,
    turnoutStatusControl,
    timedOnControl,
    twoSensorControl };

/*protected*/ /*static*/ /*final*/ QList<QString> LightControlTableModel::getControlTypeTips(){
    QList<QString> typeTooltips = QList<QString>();
    typeTooltips.append(""); // no Control Type selected
    typeTooltips.append(tr("Light updated when the Sensor changes to Active or Inactive"));
    typeTooltips.append(tr("Light updated each FastClock minute"));
    typeTooltips.append(tr("Light updated when the Turnout changes to {0} or {1}").arg(
            InstanceManager::turnoutManagerInstance()->getClosedText(),
            InstanceManager::turnoutManagerInstance()->getThrownText()));
    typeTooltips.append(tr("Light set ON when the Sensor changes to Active\nLight set OFF after the time period"));
    typeTooltips.append(tr("Light updated when either Sensor changes state"));
    return typeTooltips;
}
/**
 * Get text showing the type of Light Control.
 *
 * @param type the type of Light Control
 * @return name of type or the description for {@link jmri.Light#NO_CONTROL}
 *         if type is not recognized
 */
/*public*/ /*static*/ QString LightControlTableModel::getControlTypeText(int type) {
    switch (type) {
        case Light::SENSOR_CONTROL:
            return sensorControl;
        case Light::FAST_CLOCK_CONTROL:
            return fastClockControl;
        case Light::TURNOUT_STATUS_CONTROL:
            return turnoutStatusControl;
        case Light::TIMED_ON_CONTROL:
            return timedOnControl;
        case Light::TWO_SENSOR_CONTROL:
            return twoSensorControl;
        case Light::NO_CONTROL:
        default:
            return noControl;
    }
}

/*public*/ LightControlTableModel::LightControlTableModel(LightControlPane* pane) : AbstractTableModel(){
    //super();
    controlList = QList<LightControl*>();
    lcp = pane;
}

/**
 * Get the Current Light Control List for the Table.
 * @return unmodifiable List of Light Controls.
 */
/*public*/ QList<LightControl*> LightControlTableModel::getControlList(){
    return QList<LightControl*>(controlList);
}

/*public*/ void LightControlTableModel::setTableToLight(Light* light){
    // Get a fresh copy of the LightControl list
    controlList.clear();
    //light->getLightControlList().forEach((lightControlList1) -> controlList.add(new DefaultLightControl(lightControlList1)));
    for(LightControl* lightControlList1: light->getLightControlList())
     controlList.append(lightControlList1);
    fireTableDataChanged();
}

/*public*/ void LightControlTableModel::addControl(LightControl* lc){
    controlList.append(lc);
    fireTableDataChanged();
}

/*public*/ void LightControlTableModel::removeControl(LightControl* lc){
    controlList.removeOne(lc);
    fireTableDataChanged();
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString LightControlTableModel::getColumnClass(int c) const{
    switch (c) {
        case EDIT_COLUMN:
        case REMOVE_COLUMN:
            return "JButton";
        case TYPE_COLUMN:
        case DESCRIPTION_COLUMN:
        default:
            return "String";
    }
}

/**
 * {@inheritDoc}
 */
//@Override
///*public*/ int getColumnCount() {
/*public*/ int LightControlTableModel::columnCount(const QModelIndex&) const
{
    return REMOVE_COLUMN + 1;
}

/**
 * {@inheritDoc}
 */
//@Override
///*public*/ int getRowCount()
/*public*/ int LightControlTableModel::rowCount(const QModelIndex&) const{
    return controlList.size();
}

/**
 * {@inheritDoc}
 */
//@Override
///*public*/ bool isCellEditable(int r, int c)
/*public*/ Qt::ItemFlags LightControlTableModel::flags(const QModelIndex& index)const
{
    switch (index.column()) {
        case EDIT_COLUMN:
        case REMOVE_COLUMN:
            return Qt::ItemIsEditable | Qt::ItemIsEnabled;
        case TYPE_COLUMN:
        case DESCRIPTION_COLUMN:
        default:
            return Qt::ItemIsEnabled;
    }
}

/**
 * {@inheritDoc}
 */
//@Override
///*public*/ String getColumnName(int col)
/*public*/ QVariant LightControlTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    if (section == TYPE_COLUMN) {
        return tr("Controller Type:");
    } else if (section == DESCRIPTION_COLUMN) {
        return tr("Description");
    }
    return "";
}

/**
 * {@inheritDoc}
 */
//@Override
///*public*/ Object getValueAt(int r, int c)
/*public*/ QVariant LightControlTableModel::data(const QModelIndex& index, int role) const{
 if(role == Qt::DisplayRole)
 {
    LightControl* lc = controlList.at(index.row());
    switch (index.column()) {
        case TYPE_COLUMN:
            return (getControlTypeText(lc->getControlType()));
        case DESCRIPTION_COLUMN:
            return (LightTableAction::getDescriptionText(lc, lc->getControlType()));
        case EDIT_COLUMN:
            return tr("ButtonEdit");
        case REMOVE_COLUMN:
            return tr("ButtonDelete");
        default:
     break;;
    }
 }
 return QVariant();
}

/**
 * {@inheritDoc}
 */
//@Override
///*public*/ void setValueAt(Object value, int row, int col)
/*public*/ bool LightControlTableModel::setData(const QModelIndex& index, const QVariant& value, int role){
 if(role == Qt::EditRole)
 {
    if (index.column() == EDIT_COLUMN) {
        // set up to edit. Use separate Runnable so window is created on top
        //javax.swing.SwingUtilities.invokeLater(() -> {
            lcp->editControlAction(controlList.at(index.row()));
       // });
    }
    else if (index.column() == REMOVE_COLUMN) {
        controlList.removeAt(index.row());
        fireTableDataChanged();
    }
    return true;
 }
 return false;
}

/*protected*/ void LightControlTableModel::configureJTable(JTable* table){

    table->setRowSelectionAllowed(false);

    TableColumnModel* lightControlColumnModel = table->getColumnModel();
    TableColumn* typeColumn = lightControlColumnModel->getColumn(LightControlTableModel::TYPE_COLUMN);
    typeColumn->setResizable(true);
    typeColumn->setMinWidth(130);
    typeColumn->setMaxWidth(170);
    TableColumn* descriptionColumn = lightControlColumnModel->getColumn(
            LightControlTableModel::DESCRIPTION_COLUMN);
    descriptionColumn->setResizable(true);
    descriptionColumn->setMinWidth(270);
    descriptionColumn->setMaxWidth(380);

//    table.setDefaultRenderer(JButton.class, new ButtonRenderer());
//    table.setDefaultEditor(JButton.class, new ButtonEditor(new JButton()));

    JButton* testButton = new JButton(tr("Delete"));
    table->setRowHeight(testButton->sizeHint().height());
    TableColumn* editColumn = lightControlColumnModel->getColumn(LightControlTableModel::EDIT_COLUMN);
    editColumn->setResizable(false);
    editColumn->setMinWidth(JButton(tr("ButtonEdit")).sizeHint().width());
    TableColumn* removeColumn = lightControlColumnModel->getColumn(LightControlTableModel::REMOVE_COLUMN);
    removeColumn->setResizable(false);
    removeColumn->setMinWidth(testButton->sizeHint().width());

}
