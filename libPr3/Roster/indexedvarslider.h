#ifndef INDEXEDVARSLIDER_H
#define INDEXEDVARSLIDER_H

#include "jslider.h"
#include "indexedvariablevalue.h"
#include "changeevent.h"

class IndexedVariableValue;
class LIBPR3SHARED_EXPORT IndexedVarSlider : public JSlider
{
    Q_OBJECT
public:
   // explicit IndexedVarSlider(QWidget *parent = 0);;
    IndexedVarSlider(IndexedVariableValue* iVar, int min, int max, QWidget *parent = 0);
    /*public*/ void stateChanged(ChangeEvent* e);
    void originalPropertyChanged(PropertyChangeEvent* e);

signals:

public slots:
    void on_value_Changed(int);
    /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
    IndexedVariableValue* _iVar;
 Logger* log;

};

#endif // INDEXEDVARSLIDER_H
