#ifndef JSLIDER_H
#define JSLIDER_H

#include <QSlider>
#include "propertychangeevent.h"
#include "javaqt_global.h"
class BoundedRangeModel;
class JAVAQTSHARED_EXPORT JSlider : public QSlider
{
    Q_OBJECT
public:
    explicit JSlider(QWidget *parent = 0);
    /*public*/ JSlider(int orientation, int min, int max, int value, QWidget* parent = 0);
    /*public*/ JSlider(int min, int max, QWidget* parent = 0);
    /*public*/ JSlider(BoundedRangeModel* brm, QWidget* parent = 0);

    /*public*/ void setModel(BoundedRangeModel* newModel);
    /*public*/ BoundedRangeModel* getModel();
    void setMinimum(int);
    void setMaximum(int);
    void setValue(int);
signals:

public slots:
    void On_valueChanged(int);
private:
    /*private*/ void checkOrientation(int orientation);
    int orientation;
protected:
    /**
     * The data model that handles the numeric maximum value,
     * minimum value, and current-position value for the slider.
     */
    /*protected*/ BoundedRangeModel* sliderModel;

};

#endif // JSLIDER_H
