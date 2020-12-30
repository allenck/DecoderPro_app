#ifndef STOPALLBUTTON_H
#define STOPALLBUTTON_H
#include <QPushButton>

class JActionEvent;
class StopAllButton : public QPushButton
{
 Q_OBJECT
public:
 StopAllButton();
public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0) ;

};

#endif // STOPALLBUTTON_H
