#ifndef BUTTONTRIGGER_H
#define BUTTONTRIGGER_H
#include "trigger.h"
#include "libPr3_global.h"

class Logger;
class JActionEvent;
class QMouseEvent;
class LIBPR3SHARED_EXPORT ButtonTrigger : public Trigger
{
 Q_OBJECT
public:
 explicit ButtonTrigger(QObject *parent = 0);
 /*public*/ ButtonTrigger(QString name,QObject *parent = 0);
 /*public*/ ButtonTrigger(QString name, bool bv,QObject *parent = 0) ;
 /*public*/ void setMatchValue(bool bv) ;
 /*public*/ bool getMatchValue();
 // Button action functions called directly from the enclosing SoundEvent.
 /*public*/ void mouseDown() ;
 /*public*/ void mouseUp();
 /*public*/ void click(bool v);
 /*public*/ void mousePressed(QMouseEvent* e);
 /*public*/ void mouseReleased(QMouseEvent* e) ;
 /*public*/ void mouseEntered(QMouseEvent* e);
 /*public*/ void mouseExited(QMouseEvent* e) ;
 /*public*/ void mouseClicked(QMouseEvent* e);
 /*public*/ QDomElement getXml();
 /*public*/ void setXml(QDomElement e);

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* event);
 /*public*/ void actionPerformed(JActionEvent* e = 0) ;

private:
 enum ButtonAction
 {
 };

 bool match_value;
 bool state;
 Logger* log;
};

#endif // BUTTONTRIGGER_H
