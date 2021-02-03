#ifndef JSLIDER_H
#define JSLIDER_H

#include <QSlider>
#include "propertychangeevent.h"
#include "javaqt_global.h"
#include "jlabel.h"
#include <QBoxLayout>

class ChangeListener;
class BoundedRangeModel;
class JAVAQTSHARED_EXPORT JSlider : public QWidget
{
    Q_OBJECT
public:
    explicit JSlider(QWidget *parent = 0);
    /*public*/ JSlider(Qt::Orientation orientation, int min, int max, int value, QWidget* parent = 0);
    /*public*/ JSlider(int min, int max, QWidget* parent = 0);
    /*public*/ JSlider(BoundedRangeModel* brm, QWidget* parent = 0);

    /*public*/ void setModel(BoundedRangeModel* newModel);
    /*public*/ BoundedRangeModel* getModel();
    void setMinimum(int);
    void setMaximum(int);
    int getValue();
    void setValue(int);
    /*public*/ void addChangeListener(ChangeListener*);
    /*public*/ void removeChangeListener(ChangeListener*);
    /*public*/ void setVisible(bool b);
    /*public*/ bool getValueIsAdjusting();
    void setLabelTable(QHash<int,JLabel*> labelTable);
    void setMajorTickSpacing(int v);
    void setOrientation(Qt::Orientation);
    int value();
    int  maximum();
    int  minimum();
    void setTickInterval(int i);
    void setTickPosition(QSlider::TickPosition pos);
    void setPaintTicks(bool b);
    void setPaintLabels(bool b);
    void setSingleStep(int v);
    void  setEnabled(bool b);
    bool isEnabled();
    bool getPaintTicks();
    bool getPaintLabels();

 signals:
    void valueChanged(int);

public slots:
    void onValueChanged(int v);
    void sliderPressed();
    void sliderReleased();

private:
    /*private*/ void checkOrientation(int orientation);
    QVector<ChangeListener*> listeners;
    QHash<int,JLabel*> labelTable;
    bool isAdjusting;
    bool bSetPaintTicks = true;
    bool bSetPaintLabels = true;
    void resizeEvent(QResizeEvent *event);
    QVBoxLayout* verticalLayout_2;
    QHBoxLayout* horizontalLayout;
    int tickSpacing;
    Qt::Orientation orientation;
    void layoutWidget();
    QSlider* slider;
    int max;
    int min;
    int val;
    bool bPaintLabels;
    bool bPaintTicks;
    void common(Qt::Orientation orientation);

 protected:
    /**
     * The data model that handles the numeric maximum value,
     * minimum value, and current-position value for the slider.
     */
    /*protected*/ BoundedRangeModel* sliderModel;

};

#endif // JSLIDER_H
