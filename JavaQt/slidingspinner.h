#ifndef SLIDINGSPINNER_H
#define SLIDINGSPINNER_H

#include <QObject>
#include "changelistener.h"

class JSpinner;
class JSlider;
class ColorPanel;
class JComponent;
class SpinnerNumberModel;
class SlidingSpinner : public ChangeListener
{
 Q_OBJECT

public:
 explicit SlidingSpinner(QObject *parent = nullptr);
 SlidingSpinner(ColorPanel* panel, JComponent* label, QObject *parent = nullptr);

signals:

public slots:
 /*public*/ void stateChanged(ChangeEvent* event);

private:
 /*private*/ /*final*/ ColorPanel* panel;
 /*private*/ /*final*/ JComponent* label;
 /*private*/ /*final*/ SpinnerNumberModel* model;// = new SpinnerNumberModel();
 /*private*/ /*final*/ JSlider* slider;// = new JSlider();
 /*private*/ /*final*/ JSpinner* spinner;// = new JSpinner(this->model);
 /*private*/ float value;
 /*private*/ bool internal;
 JComponent* getLabel();
 JSlider* getSlider();
 JSpinner* getSpinner();
 float getValue() ;
 void setValue(float value);
 void setRange(int min, int max);
 void setVisible(bool visible);
 bool isVisible();

 friend class ColorPanel;
};

#endif // SLIDINGSPINNER_H
