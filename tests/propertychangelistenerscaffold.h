#ifndef PROPERTYCHANGELISTENERSCAFFOLD_H
#define PROPERTYCHANGELISTENERSCAFFOLD_H
#include "propertychangelistener.h"

class PropertyChangeListenerScaffold : public PropertyChangeListener
{
 Q_OBJECT
public:
 PropertyChangeListenerScaffold(QObject* parent = nullptr);
 /*public*/ void resetPropertyChanged();
 /*public*/ bool getPropertyChanged();
 /*public*/ int getCallCount();
 /*public*/ QString getLastProperty();
 /*public*/ QVariant getLastValue();
 /*public*/ void onChange(QString property, QVariant newValue);

public slots:
 //@Override
 /*public*/ void propertyChange(PropertyChangeEvent* propertyChangeEvent);

private:
 /*private*/ bool propertyChanged;
 /*private*/ int callCount;
 /*private*/ QString lastChange;
 /*private*/ QVariant lastValue;

 friend class WaitForChange;
};

#endif // PROPERTYCHANGELISTENERSCAFFOLD_H
