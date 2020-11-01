#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>
#include <QVector>

class MySlider : public QWidget
{
 Q_OBJECT
public:
 explicit MySlider(QWidget *parent = nullptr);
  MySlider(int min, int max, QWidget *parent = nullptr);
 void setMaximum(int);
 void setMinimum(int);
 void setRange(int, int);
 void setValue(int);
 void setSingleStep(int v);
 void setLabelTable(QVector<QLabel*> labelTable);
 void setMajorTickSpacing(int v);
 int  value();
 void setOrientation(Qt::Orientation);
 int  maximum();
 int  minimum();
 void setEnabled(bool);
 bool isEnabled();
 bool getValueIsAdjusting();
 void setPaintTicks(bool) {}
 void setPaintLabels(bool) {}

signals:
void valueChanged(int);

public slots:
 void onValueChanged(int);


private:
 QVector<QLabel*> labelTable;
 QSlider* slider;
 int tickSpacing;
 Qt::Orientation orientation;
 void layoutWidget();
 int max;
 int min;
 int val;
 bool isAdjusting;
 void resizeEvent(QResizeEvent *event);
 QVBoxLayout* verticalLayout_2;
 QHBoxLayout* horizontalLayout;

private slots:
 void sliderPressed();
 void sliderReleased();
};

#endif // MYSLIDER_H
