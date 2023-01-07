#ifndef LEARNSPEEDPANEL_H
#define LEARNSPEEDPANEL_H
#include "jinternalframe.h"
#include "warrant.h"
#include "jlabel.h"

class LearnSpeedPanel : public JInternalFrame
{
  Q_OBJECT

 public:
  LearnSpeedPanel(Warrant* w, QObject* parent = nullptr);
  /*public*/ void notifyAddressThrottleFound(DccThrottle* t);
  /*public*/ void destroy();
  virtual QFontMetrics getFontMetrics(QFont f) {return QFontMetrics (f);}
   QFontMetrics getFontMetrics() {return QFontMetrics (getFont());}
   void setEnabled(bool) {}
   void setSize(int, int) {}
   QString toString() {
    if(!jself()->objectName().isEmpty()) return jself()->objectName();
    else return jself()->metaObject()->className();
   }
 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  static Logger* log;
  /*private*/ Warrant* _warrant;
  /*private*/ DccThrottle* _throttle;
  /*private*/ float _currentThrottleValue = 0.0;
  /*private*/ JLabel* _scaleSpeed;
  /*private*/ void initGUI();
  /*private*/ QString setSpeed();

};

#endif // LEARNSPEEDPANEL_H
