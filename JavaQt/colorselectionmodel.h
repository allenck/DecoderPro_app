#ifndef COLORSELECTIONMODEL_H
#define COLORSELECTIONMODEL_H
#include <QObject>
#include <QColor>
#include "changelistener.h"

/*public*/ /*interface*/class ColorSelectionModel  {

public:
 /*public*/ virtual QColor getSelectedColor() {return QColor();}

 /*public*/ virtual void setSelectedColor(QColor color) {}

 /*public*/ virtual void addChangeListener(ChangeListener* listener) =0;

 /*public*/ virtual void removeChangeListener(ChangeListener* listener)=0;
};
Q_DECLARE_INTERFACE(ColorSelectionModel, "ColorSelectionModel")
#endif // COLORSELECTIONMODEL_H
