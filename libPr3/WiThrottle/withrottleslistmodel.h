#ifndef WITHROTTLESLISTMODEL_H
#define WITHROTTLESLISTMODEL_H
#include "abstractlistmodel.h"

struct WiDevice;
class Logger;
class WiThrottlesListModel;
class DeviceServer;
class WiThrottlesListModel : public AbstractListModel
{
 Q_OBJECT
public:
 //WiThrottleListModel();
 WiThrottlesListModel(QVector<WiDevice*>* deviceList);
 /*public*/ int columnCount(const QModelIndex &parent) const;
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ void updateDeviceList(QVector<WiDevice*>* deviceList);

private:
     /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(WiThrottlesListModel.class.getName());
 QVector<WiDevice*>* deviceList;

};

#endif // WITHROTTLESLISTMODEL_H
