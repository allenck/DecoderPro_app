#include "withrottleslistmodel.h"
#include "logger.h"
#include "loggerfactory.h"
#include "deviceserver.h"

//WiThrottleListModel::WiThrottleListModel()
//{

//}
/**
 *
 * WiThrottle
 *
 * @author Brett Hoffman Copyright (C) 2009
 * @author Created by Brett Hoffman on:
 * @author 11/11/09.
 */

///*public*/ class WiThrottlesListModel extends AbstractTableModel {

//DeviceServer[] deviceList;

//static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.withrottle.WiThrottleBundle");

WiThrottlesListModel::WiThrottlesListModel(QVector<WiDevice*>* deviceList) : AbstractListModel()
{

    this->deviceList = deviceList;

}

//@Override
/*public*/ int WiThrottlesListModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

//@Override
/*public*/ int WiThrottlesListModel::rowCount(const QModelIndex &/*parent*/) const
{
    return deviceList->size();
}

//@Override
/*public*/ QVariant WiThrottlesListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {
    QString title;
    switch (section) {
        case 0: {
            title = tr("Device Name");
            break;
        }
        case 1: {
            title = tr("Address");
            break;
        }
        default: {
            title = "";
        }
    }
    return title;
 }
 return QVariant();
}

//@Override
/*public*/ QVariant WiThrottlesListModel::data(const QModelIndex &index, int role) const
{
 int col = index.column();
 int row = index.row();
 if(role == Qt::DisplayRole)
 {
    if (deviceList->size() < 1) {
        return QVariant();
    }
    // some error checking
    if (row >= deviceList->size()) {
        log->debug("row is greater than device list size");
        return QVariant();
    }
    if (col == 0) {
        return deviceList->at(row)->name;
    } else {
        return deviceList->at(row)->address;
    }
 }
 return QVariant();
}

/*public*/ void WiThrottlesListModel::updateDeviceList(QVector<WiDevice*>* deviceList)
{
 if(deviceList->count() < rowCount(QModelIndex()))
 {
  beginResetModel();
  endResetModel();
  return;
 }
 int rows = rowCount(QModelIndex());
 this->beginInsertRows(QModelIndex(), rows, rows);
    this->deviceList = deviceList;
    this->endInsertRows();
}

/*private*/ /*final*/ /*static*/ Logger* WiThrottlesListModel::log = LoggerFactory::getLogger("WiThrottlesListModel");
