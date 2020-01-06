#ifndef DEFAULTCOLORSELECTIONMODEL_H
#define DEFAULTCOLORSELECTIONMODEL_H

#include <QObject>
#include "colorselectionmodel.h"

class EventListenerList;
class DefaultColorSelectionModel : public QObject, public ColorSelectionModel
{
 Q_OBJECT
 Q_INTERFACES(ColorSelectionModel)
public:
 explicit DefaultColorSelectionModel(QObject *parent = nullptr);
 /*public*/ DefaultColorSelectionModel(QColor color,QObject *parent= nullptr);
 /*public*/ QColor getSelectedColor();
 /*public*/ void setSelectedColor(QColor color);
 /*public*/ void addChangeListener(ChangeListener* l);
 /*public*/ void removeChangeListener(ChangeListener* l);
 /*public*/ QVector<EventListener *> getChangeListeners();



signals:
 void stateChanged(ChangeEvent*);

public slots:
private:

 /*private*/ QColor selectedColor;
 ChangeEvent* changeEvent = nullptr;
protected:
// /*protected*/ /*transient*/ ChangeEvent changeEvent = null;

 /*protected*/ EventListenerList* listenerList;// = new EventListenerList();
 /**
  * Runs each <code>ChangeListener</code>'s
  * <code>stateChanged</code> method.
  *
  * <!-- @see #setRangeProperties    //bad link-->
  * @see EventListenerList
  */
 /*protected*/ void fireStateChanged();
};

#endif // DEFAULTCOLORSELECTIONMODEL_H
