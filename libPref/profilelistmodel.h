#ifndef PROFILELISTMODEL_H
#define PROFILELISTMODEL_H
#include "abstractlistmodel.h"
#include "libpref_global.h"
#include "propertychangelistener.h"

class PropertyChangeEvent;
class LIBPREFSHARED_EXPORT ProfileListModel : public AbstractListModel, public PropertyChangeListener
{
    Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)
public:
    explicit ProfileListModel(QObject *parent = 0);
    /*public*/ int getSize() const override;
    /*public*/ QVariant getElementAt(int index) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void reset();

    QObject* pself() override {return this;}

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent *evt)override;
private:
    /*private*/ void fireContentsChanged(int index0, int index1);
    /*private*/ void fireIntervalAdded(int index0, int index1);
    /*private*/ void fireIntervalRemoved(int index0, int index1);

};

#endif // PROFILELISTMODEL_H
