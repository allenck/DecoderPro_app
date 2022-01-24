#ifndef SENSORTABLEMODEL_H
#define SENSORTABLEMODEL_H
#include "beantablemodel.h"
#include <QStringList>
#include "propertychangelistener.h"

class PropertyChangeEvent;
class SensorTableModel : public BeanTableModel, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
 explicit SensorTableModel(QObject *parent = 0);
 /*public*/ void dispose();
 /*public*/ Manager* getManager() const override;
 /*public*/ int rowCount(const QModelIndex &parent) const override;
 /*public*/ QVariant data(const QModelIndex &index, int role) const override;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  QObject* self() override {return (QObject*)this;}

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e) override;

private:

 QStringList _sysNameList;
 QList<bool> _includedSensors;
 /*private*/ void init();
 Logger* log;
};

#endif // SENSORTABLEMODEL_H
