#ifndef THROTTLESTABLEMODEL_H
#define THROTTLESTABLEMODEL_H
#include "abstracttablemodel.h"
#include "addresslistener.h"

// Note: ThrottleWindow replaces ThrottleWindow
class PropertyChangeEvent;
class DccThrottle;
class DccLocoAddress;
class locoAddress;
class DccLocoAddress;
class ThrottleWindow;
class ThrottlesTableModel : public AbstractTableModel, public AddressListener
{
    Q_OBJECT
public:
    explicit ThrottlesTableModel(QObject *parent = 0);
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ QListIterator<ThrottleWindow*> iterator();
    /*public*/ void addThrottleFrame(ThrottleWindow* tf);
    /*public*/ void removeThrottleFrame(ThrottleWindow* tf, DccLocoAddress* la);
    QObject* self() {return (QObject*)this;}

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ void notifyAddressChosen(locoAddress* la) ;
    /*public*/ void notifyAddressReleased(locoAddress* addr);
    /*public*/ void notifyAddressThrottleFound(DccThrottle* throttle);
    /*public*/ void notifyConsistAddressChosen(int newAddress, bool isLong);
    /*public*/ void notifyConsistAddressReleased(int address, bool isLong);
    /*public*/ void notifyConsistAddressThrottleFound(DccThrottle* throttle) ;
    /*public*/ int getRowCount() {return rowCount(QModelIndex());}
    /*public*/ int getColumnCount() {return columnCount(QModelIndex());}

signals:

public slots:
private:
    /*private*/ QList<ThrottleWindow*> throttleFrames;// = new QList<ThrottleWindow*>(/*5*/);

};

#endif // THROTTLESTABLEMODEL_H
