#include "myslider.h"
#include <QResizeEvent>
#include "exceptions.h"
/*
 * Class to display a slider with tick marks and labels
 *
 */

MySlider::MySlider(QWidget *parent) : QWidget(parent)
{
 if(objectName().isEmpty())
  setObjectName("MySlider");
 resize(55, 600);
 tickSpacing = 0;
 orientation = Qt::Vertical;
 max = 1;
 min = 0;
 isAdjusting = false;
 labelTable = QVector<QLabel*>();
 slider = new QSlider();
 //slider->setMinimumHeight(200);
 verticalLayout_2 = NULL;
 horizontalLayout = NULL;
}
MySlider::MySlider(int min, int max, QWidget *parent) : QWidget(parent)
{
 if(objectName().isEmpty())
  setObjectName("MySlider");
 resize(55, 600);
 tickSpacing = 0;
 orientation = Qt::Vertical;
 max = 1;
 min = 0;
 isAdjusting = false;
 labelTable = QVector<QLabel*>();
 slider = new QSlider();
 //slider->setMinimumHeight(200);
 verticalLayout_2 = NULL;
 horizontalLayout = NULL;
 setMinimum(min);
 setMaximum(max);
}

void MySlider::setMaximum(int i)
{
 slider->setMaximum(i);
 max = i;
}

void MySlider::setMinimum(int i)
{
 slider->setMinimum(i);
 min = i;
}

void MySlider::setRange(int l, int h)
{
 slider->setRange(l,h);
 min = l;
 max = h;
}

void MySlider::setValue(int v)
{
 slider->setValue(v);
 val = v;
}
void MySlider::setSingleStep(int v) { slider->setSingleStep(v);}
void MySlider::onValueChanged(int v)
{
 emit valueChanged(v);
}

void MySlider::setLabelTable(QVector<QLabel*> labelTable)
{
 if(this->labelTable.isEmpty())
  this->labelTable = QVector<QLabel*>(labelTable);
 else
 {
  if(this->labelTable.count()== labelTable.count())
   return;
  throw Exception("MySlider layout has changed");
 }
 layoutWidget();
}

void MySlider::layoutWidget()
{
 if(labelTable.isEmpty())
  return;
 if(verticalLayout_2!= NULL)
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
 if(horizontalLayout!= NULL)
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
 slider->setOrientation(Qt::Vertical);
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

 for(int i = 0; i < labelTable.count(); i++)
 {
  QLabel* label = labelTable.at(i);
  label->setObjectName(tr("label_%1").arg(i));
  label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
  verticalLayout_2->addWidget(label);
 }
 for(int i = 0; i < labelTable.count(); i++)
 {
  verticalLayout_2->setStretch(1, i);
 }
 horizontalLayout->addWidget(widget_2);
}


void MySlider::setMajorTickSpacing(int v) { tickSpacing = v;}

int MySlider::value() { return slider->value();}

void MySlider::setOrientation(Qt::Orientation orientation)
{
 this->orientation = orientation;
}

int MySlider::maximum() { return slider->maximum();}
int MySlider::minimum() { return slider->minimum();}

void  MySlider::setEnabled(bool b)
{
 slider->setEnabled(b);
}

bool MySlider::isEnabled() { return slider->isEnabled();}

bool MySlider::getValueIsAdjusting() {return isAdjusting;}

void MySlider::sliderPressed(){isAdjusting = true;}
void MySlider::sliderReleased() {isAdjusting = false;}

void MySlider::resizeEvent(QResizeEvent* evt)
{
 QSize _size = evt->size();
// if(_size.height() < slider->minimumHeight())
//    slider->setMinimumHeight(_size.height());
// slider->setMaximumHeight(_size.height()-5);
 slider->resize(slider->size().width(),_size.height()-10);
}
