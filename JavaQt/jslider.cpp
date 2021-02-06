#include "jslider.h"
#include "defaultboundedrangemodel.h"
#include "exceptions.h"
#include <QDebug>
#include "changelistener.h"
#include "changeevent.h"
#include <QResizeEvent>

JSlider::JSlider(QWidget *parent) :
    QWidget(parent)
{
 common(Qt::Vertical);
}

void JSlider::common(Qt::Orientation orientation)
{
 if(objectName().isEmpty())
  setObjectName("MySlider");
 resize(55, 600);
 checkOrientation(orientation);
 tickSpacing = 0;
 this->orientation = orientation;
 max = 1;
 min = 0;
 isAdjusting = false;
 labelTable = QHash<int,JLabel*>();
 slider = new QSlider(orientation);
 //slider->setMinimumHeight(200);
 verticalLayout_2 = NULL;
 horizontalLayout = NULL;

 sliderModel = new DefaultBoundedRangeModel(0,0,0,100);
 setMinimum(0);
 setMaximum(100);
 connect(slider, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
 setValue(0);
 listeners = QVector<ChangeListener*>();

 setLayout(verticalLayout_2 = new QVBoxLayout());
 verticalLayout_2->addWidget(slider, 1);
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
/*public*/ JSlider::JSlider(Qt::Orientation orientation, int min, int max, int value, QWidget* parent) : QWidget(parent)
{
 common(orientation);
    slider->setOrientation((Qt::Orientation)orientation);
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
   throw IllegalArgumentException("orientation must be one of: VERTICAL, HORIZONTAL");
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
/*public*/ JSlider::JSlider(int min, int max, QWidget* parent) : QWidget(parent)
{
 common(Qt::Horizontal);
 //this(HORIZONTAL, min, max, (min + max) / 2);
 setOrientation(Qt::Horizontal);
 setMinimum(min);
 sliderModel->setMinimum(min);
 setMaximum(max);
 sliderModel->setMaximum(max);
 //connect(this, SIGNAL(valueChanged(int)), this, SLOT(On_valueChanged(int)));

}
/**
 * Creates a horizontal slider using the specified
 * BoundedRangeModel.
 */
/*public*/ JSlider::JSlider(BoundedRangeModel* brm, QWidget* parent) : QWidget(parent)
{
 common(Qt::Horizontal);
    //this->orientation = Qt::Horizontal;
    setModel(brm);
    setMaximum(brm->getMaximum());
    setMinimum(brm->getMinimum());
    //connect(this, SIGNAL(valueChanged(int)), this, SLOT(On_valueChanged(int)));
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

    if (oldModel != nullptr) {
//        oldModel->removeChangeListener(changeListener);
    }

    sliderModel = newModel;

    if (newModel != nullptr) {
//        newModel->addChangeListener(changeListener);
        setMaximum(newModel->getMaximum());
        setMinimum(newModel->getMinimum());
        setValue(newModel->getValue());

    }

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
//void JSlider::valueChanged(int value)
//{
// sliderModel->setValue(value);
// foreach (ChangeListener* l, listeners) {
//  l->stateChanged(new ChangeEvent(this));
// }
//}

void JSlider::setMinimum(int i)
{
 sliderModel->setMinimum(i);
 slider->setMinimum(i);
}

void JSlider::setMaximum(int i)
{
 sliderModel->setMaximum(i);
 slider->setMaximum(i);
}

int JSlider::getValue() {return slider->value();}

void JSlider::setValue(int i)
{
 sliderModel->setValue(i);
 slider->setValue(i);
}
void JSlider::setSingleStep(int v) { slider->setSingleStep(v);}
void JSlider::onValueChanged(int v)
{
 emit valueChanged(v);
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
 slider->setVisible(b);
 QWidget::setVisible(b);
}

void JSlider::setLabelTable(QHash<int,JLabel*> labelTable)
{
 if(this->labelTable.isEmpty())
  this->labelTable = QHash<int,JLabel*>(labelTable);
 else
 {
  if(this->labelTable.count()== labelTable.count())
   return;
  throw Exception("MySlider layout has changed");
 }
 layoutWidget();
}

void JSlider::layoutWidget()
{
 if(labelTable.isEmpty())
  return;
 if(verticalLayout_2 != NULL)
 {
  QObjectList ol = verticalLayout_2->children();
  foreach(QObject* o, ol)
  {
   if(qobject_cast<QWidget*>(o) != NULL)
    verticalLayout_2->removeWidget((QWidget*)o);
  }
  delete verticalLayout_2;
  verticalLayout_2 = NULL;
 }
 if(horizontalLayout != NULL)
 {
  QObjectList ol = horizontalLayout->children();
  foreach(QObject* o, ol)
  {
   if(qobject_cast<QWidget*>(o) != NULL)
    horizontalLayout->removeWidget((QWidget*)o);
  }
  delete horizontalLayout;
  horizontalLayout = NULL;
 }


// thisLayout->removeWidget(slider);
// delete slider;

// slider= new QSlider(orientation);
// slider->setMinimumHeight(100);
// QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
// sizePolicy.setHorizontalStretch(0);
// sizePolicy.setVerticalStretch(2);
// sizePolicy.setHeightForWidth(false);
// slider->setSizePolicy(sizePolicy);

// thisLayout->addWidget(slider, 0, 0, labelTable.count(), 1);
// slider->setTickPosition(QSlider::TicksBothSides);
// for(int i = 0; i < labelTable.count(); i++)
//  thisLayout->addWidget(labelTable.at(i), i, 1, 1,1);
 horizontalLayout = new QHBoxLayout(this);
 horizontalLayout->setContentsMargins(0,0,0,0);
 horizontalLayout->setObjectName("horizontalLayout");
 QWidget* widget = new QWidget(this);
 widget->setObjectName("widget");
 QVBoxLayout* verticalLayout = new QVBoxLayout(widget);
 verticalLayout->setObjectName("verticalLayout");
 verticalLayout->setContentsMargins(-1, -1, 0, -1);
 //slider = new QSlider(Qt::Vertical, widget);
 slider->setParent(widget);
 slider->setObjectName("slider");
 //slider->setOrientation(Qt::Vertical);
 slider->setTickPosition(QSlider::TicksBothSides);
 //slider-> resize(55, 350);
// slider->setMaximumHeight(450);
// slider->setMinimumHeight(150);
 connect(slider, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
 connect(slider, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
 connect(slider, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));

 verticalLayout->addWidget(slider,1,Qt::AlignCenter);

 horizontalLayout->addWidget(widget);

 QWidget* widget_2 = new QWidget(this);
 widget_2->setObjectName("widget_2");
 verticalLayout_2 = new QVBoxLayout(widget_2);
 verticalLayout_2->setObjectName("verticalLayout_2");
 verticalLayout_2->setContentsMargins(0, -1, -1, -1);

 QHashIterator<int, JLabel*> iter(labelTable);
 while(iter.hasNext())
 {
  iter.next();
  JLabel* label = iter.value();
  label->setObjectName(tr("label_%1").arg(iter.key()));
  label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
  verticalLayout_2->addWidget(label);
 }
 //for(int i = 0; i < labelTable.count(); i++)
 iter.toFront();
 while(iter.hasNext())
 {
  iter.next();
  verticalLayout_2->setStretch(1, iter.key());
 }
 horizontalLayout->addWidget(widget_2);
}


void JSlider::setMajorTickSpacing(int v) { tickSpacing = v;}

int JSlider::value() { return slider->value();}

void JSlider::setOrientation(Qt::Orientation orientation)
{
 this->orientation = orientation;
 slider->setOrientation(orientation);
}
int JSlider::maximum() { return slider->maximum();}
int JSlider::minimum() { return slider->minimum();}
void JSlider::setTickInterval(int i) {slider->setTickInterval(i);}
void JSlider::setTickPosition(QSlider::TickPosition pos)
{
 slider->setTickPosition(pos);
 switch (pos) {
 case QSlider::NoTicks:
  bSetPaintTicks = false;
  break;
 default:
  bSetPaintTicks = true;
  break;
 }
}
void JSlider::setPaintTicks(bool b) {bPaintTicks = b;}
void JSlider::setPaintLabels(bool b) {bPaintLabels = b;}

void  JSlider::setEnabled(bool b)
{
 slider->setEnabled(b);
 QWidget::setEnabled(b);
}

bool JSlider::isEnabled() { return slider->isEnabled();}

bool JSlider::getValueIsAdjusting() {return isAdjusting;}

void JSlider::sliderPressed(){isAdjusting = true;}
void JSlider::sliderReleased() {isAdjusting = false;}

bool JSlider::getPaintTicks() {return bSetPaintTicks;}
bool JSlider::getPaintLabels() {return bSetPaintLabels;}


void JSlider::resizeEvent(QResizeEvent* evt)
{
 QSize _size = evt->size();
// if(_size.height() < slider->minimumHeight())
//    slider->setMinimumHeight(_size.height());
// slider->setMaximumHeight(_size.height()-5);
 slider->resize(slider->size().width(),_size.height()-10);
}
