#ifndef COLORSELECTIONMODEL_H
#define COLORSELECTIONMODEL_H
#include <QObject>
#include <QColor>

/*public*/ /*interface*/class ColorSelectionModel : QObject {
Q_OBJECT
public:
 /*public*/ virtual QColor getSelectedColor() {return QColor();}

 /*public*/ virtual void setSelectedColor(QColor color) {}

//    public void addChangeListener(ChangeListener listener);

//    public void removeChangeListener(ChangeListener listener);
};

#endif // COLORSELECTIONMODEL_H
