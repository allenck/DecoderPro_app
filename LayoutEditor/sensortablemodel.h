#ifndef SENSORTABLEMODEL_H
#define SENSORTABLEMODEL_H
#include "beantablemodel.h"
#include <QStringList>

class PropertyChangeEvent;
class SensorTableModel : public BeanTableModel
{
 Q_OBJECT
public:
 explicit SensorTableModel(QObject *parent = 0);
 /*public*/ void dispose();
 /*public*/ Manager* getManager();
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);

private:

 QStringList _sysNameList;
 QList<bool> _includedSensors;
 /*private*/ void init();
 Logger* log;
};

#endif // SENSORTABLEMODEL_H
