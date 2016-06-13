#ifndef THROTTLESTABLEMODEL_H
#define THROTTLESTABLEMODEL_H
#include "abstracttablemodel.h"

// Note: ThrottleWindow replaces ThrottleWindow
class PropertyChangeEvent;
class DccThrottle;
class DccLocoAddress;
class LocoAddress;
class DccLocoAddress;
class ThrottleWindow;
class ThrottlesTableModel : public AbstractTableModel
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
    /*public*/ void notifyAddressChosen(LocoAddress* la) ;
    /*public*/ void notifyAddressReleased(LocoAddress* addr);
    /*public*/ void notifyAddressThrottleFound(DccThrottle* throttle);
    /*public*/ void notifyConsistAddressChosen(int newAddress, bool isLong);
    /*public*/ void notifyConsistAddressReleased(int address, bool isLong);
    /*public*/ void notifyConsistAddressThrottleFound(DccThrottle* throttle) ;
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);

signals:

public slots:
private:
    /*private*/ QList<ThrottleWindow*> throttleFrames;// = new QList<ThrottleWindow*>(/*5*/);

};

#endif // THROTTLESTABLEMODEL_H
