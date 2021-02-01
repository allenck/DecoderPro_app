#ifndef DECVARSLIDER_H
#define DECVARSLIDER_H

#include <QSlider>
#include "decvariablevalue.h"
#include "changeevent.h"
#include "jslider.h"

class LIBPR3SHARED_EXPORT DecVarSlider : public JSlider
{
 Q_OBJECT
public:
 //explicit DecVarSlider(QWidget *parent = 0);
 DecVarSlider(DecVariableValue* var, int min, int max, QWidget *parent = 0);
 /*public*/ void stateChanged(ChangeEvent* e);
 QColor getBackground();
 void setBackground(QColor c);

public slots:
 void on_value_Changed(int);
 void propertyChange(PropertyChangeEvent* e);
 void originalPropertyChanged(PropertyChangeEvent* e);

private:
 DecVariableValue* _var;
 Logger* logit;
};
class DVSPropertyChangeListener : public PropertyChangeListener
{
 Q_OBJECT
  DecVarSlider* self;
 public:
  DVSPropertyChangeListener(DecVarSlider* self);
 public slots:
  void propertyChange(PropertyChangeEvent*);
};

#endif // DECVARSLIDER_H
