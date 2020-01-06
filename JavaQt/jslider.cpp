#include "jslider.h"
#include "defaultboundedrangemodel.h"
#include "exceptions.h"
#include <QDebug>
#include "changelistener.h"
#include "changeevent.h"

JSlider::JSlider(QWidget *parent) :
    QSlider(Qt::Horizontal, parent)
{
    sliderModel = new DefaultBoundedRangeModel(0,0,0,100);
    setMinimum(0);
    setMaximum(100);
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(On_valueChanged(int)));
    setValue(0);
    listeners = QVector<ChangeListener*>();
}

/**
 * Creates a slider with the specified orientation and the
 * specified minimum, maximum, and initial values.
 * The orientation can be
 * either <code>SwingConstants.VERTICAL</code> or
 * <code>SwingConstants.HORIZONTAL</code>.
 * <p>
 * The <code>BoundedRangeModel</code> that holds the slider's data
 * handles any issues that may arise from improperly setting the
 * minimum, initial, and maximum values on the slider.  See the
 * {@code BoundedRangeModel} documentation for details.
 *
 * @param orientation  the orientation of the slider
 * @param min  the minimum value of the slider
 * @param max  the maximum value of the slider
 * @param value  the initial value of the slider
 *
 * @throws IllegalArgumentException if orientation is not one of {@code VERTICAL}, {@code HORIZONTAL}
 *
 * @see BoundedRangeModel
 * @see #setOrientation
 * @see #setMinimum
 * @see #setMaximum
 * @see #setValue
 */
/*public*/ JSlider::JSlider(int orientation, int min, int max, int value, QWidget* parent) : QSlider(parent)
{
    checkOrientation(orientation);
    this->orientation = orientation;
    QSlider::setOrientation((Qt::Orientation)orientation);
    setModel(new DefaultBoundedRangeModel(value, 0, min, max));
    //updateUI();
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(On_valueChanged(int)));

    setMinimum(min);
    setMaximum(max);
    setValue(value);
    listeners = QVector<ChangeListener*>();

}

/*private*/ void JSlider::checkOrientation(int orientation)
{
 switch (orientation)
 {
 case Qt::Vertical:
 case Qt::Horizontal:
   break;
 default:
   throw new IllegalArgumentException("orientation must be one of: VERTICAL, HORIZONTAL");
 }
}
/**
 * Creates a horizontal slider using the specified min and max
 * with an initial value equal to the average of the min plus max.
 * <p>
 * The <code>BoundedRangeModel</code> that holds the slider's data
 * handles any issues that may arise from improperly setting the
 * minimum and maximum values on the slider.  See the
 * {@code BoundedRangeModel} documentation for details.
 *
 * @param min  the minimum value of the slider
 * @param max  the maximum value of the slider
 *
 * @see BoundedRangeModel
 * @see #setMinimum
 * @see #setMaximum
 */
/*public*/ JSlider::JSlider(int min, int max, QWidget* parent) :QSlider(parent)
{
 //this(HORIZONTAL, min, max, (min + max) / 2);
 setMinimum(min);
 sliderModel->setMinimum(min);
 setMaximum(max);
 sliderModel->setMaximum(max);
 connect(this, SIGNAL(valueChanged(int)), this, SLOT(On_valueChanged(int)));

}
/**
 * Creates a horizontal slider using the specified
 * BoundedRangeModel.
 */
/*public*/ JSlider::JSlider(BoundedRangeModel* brm, QWidget* parent) : QSlider(parent)
{
    this->orientation = Qt::Horizontal;
    setOrientation(Qt::Horizontal);
    setModel(brm);
    setMaximum(brm->getMaximum());
    setMinimum(brm->getMinimum());
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(On_valueChanged(int)));
    setValue(brm->getValue());
    //updateUI();
}

/**
 * Sets the {@code BoundedRangeModel} that handles the slider's three
 * fundamental properties: minimum, maximum, value.
 *<p>
 * Attempts to pass a {@code null} model to this method result in
 * undefined behavior, and, most likely, exceptions.
 *
 * @param  newModel the new, {@code non-null} <code>BoundedRangeModel</code> to use
 *
 * @see #getModel
 * @see    BoundedRangeModel
 * @beaninfo
 *       bound: true
 * description: The sliders BoundedRangeModel.
 */
/*public*/ void JSlider::setModel(BoundedRangeModel* newModel)
{
    BoundedRangeModel* oldModel = getModel();

//    if (oldModel != null) {
//        oldModel->removeChangeListener(changeListener);
//    }

    sliderModel = newModel;

//    if (newModel != null) {
//        newModel->addChangeListener(changeListener);
//    }

//    if (accessibleContext != NULL) {
//        accessibleContext.firePropertyChange(
//                                            AccessibleContext.ACCESSIBLE_VALUE_PROPERTY,
//                                            (oldModel == null
//                                             ? null : Integer.valueOf(oldModel.getValue())),
//                                            (newModel == null
//                                             ? null : Integer.valueOf(newModel.getValue())));
//    }

//    firePropertyChange("model", oldModel, sliderModel);
}
/**
 * Returns the {@code BoundedRangeModel} that handles the slider's three
 * fundamental properties: minimum, maximum, value.
 *
 * @return the data model for this component
 * @see #setModel
 * @see    BoundedRangeModel
 */
/*public*/ BoundedRangeModel* JSlider::getModel() {
    return sliderModel;
}
void JSlider::On_valueChanged(int value)
{
 sliderModel->setValue(value);
 foreach (ChangeListener* l, listeners) {
  l->stateChanged(new ChangeEvent(this));
 }
}

void JSlider::setMinimum(int i)
{
 sliderModel->setMinimum(i);
 QSlider::setMinimum(i);
}

void JSlider::setMaximum(int i)
{
 sliderModel->setMaximum(i);
 QSlider::setMaximum(i);
}
int JSlider::getValue() {return QSlider::value();}
void JSlider::setValue(int i)
{
 sliderModel->setValue(i);
 QSlider::setValue(i);
}

/*public*/ void JSlider::addChangeListener(ChangeListener* l)
{
 listeners.append(l);
}
/*public*/ void JSlider::removeChangeListener(ChangeListener* l)
{
 listeners.removeOne(l);
}
/*public*/ void JSlider::setVisible(bool b)
{
// QSlider::setVisible(b);
}
