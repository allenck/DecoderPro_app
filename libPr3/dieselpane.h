#ifndef DIESELPANE_H
#define DIESELPANE_H
#include "enginepane.h"

class JActionEvent;
class ChangeEvent;
class EventListenerList;
class EngineSoundEvent;
class JToggleButton;
class QSlider;
class DieselPane : public EnginePane
{
 Q_OBJECT
public:
 explicit DieselPane(QWidget *parent = 0);
 /*public*/ DieselPane(QString n,QWidget *parent =0);
 /*public*/ void initContext(QVariant context);
 /*public*/ void initComponents();
 /*public*/ bool engineIsOn();
 /*public*/ int throttleNotch();
 /*public*/ void setThrottle(int t);

signals:

public slots:
 /*public*/ void throttleChange(ChangeEvent* e = 0) ;
 /*public*/ void startButtonChange(JActionEvent*e = 0);

private:
 enum THROTTLES
 {
  THROTTLE_MIN = 1,
  THROTTLE_MAX = 8,
  THROTTLE_INIT = 1
 };

 QSlider* throttle_slider;
 JToggleButton* start_button;

 EngineSoundEvent* engine;

 int throttle_setting;
 bool engine_started;
 //EventListenerList* listenerList;
};

#endif // DIESELPANE_H
